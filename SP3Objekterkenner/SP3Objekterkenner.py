# -*- coding: utf-8 -*-
"""
Created on Thu Feb 27 11:50:49 2020
Modified on Wed Jul 22 15:10:48 2020

@author: Welp
@editor: Alkhooli
"""

import numpy as np
import os
import sys
import tensorflow as tf


from distutils.version import StrictVersion
from PIL import Image
import time
import utils


# This is needed since the notebook is stored in the object_detection folder.
sys.path.append("..")
from object_detection.utils import ops as utils_ops

if StrictVersion(tf.__version__) < StrictVersion('1.12.0'):
  raise ImportError('Please upgrade your TensorFlow installation to v1.12.*.')

print(tf.__version__)
# This is needed to display the images.
#%matplotlib inline
#plt.plot([0,0],[1,1],linewidth=4,label='random diagonal')
#plt.show()


from object_detection.utils import label_map_util

from object_detection.utils import visualization_utils as vis_util



# What model to download.
#MODEL_NAME = 'ssd_mobilenet_v1_coco_2017_11_17'
WORKING_PATH = '/home/Student/git/SP3/SweetPicker3/SP3Objekterkenner/'
MODEL_NAME = 'trained-inference-graphs'


# Path to frozen detection graph. This is the actual model that is used for the object detection.
PATH_TO_FROZEN_GRAPH = WORKING_PATH + MODEL_NAME + '/frozen_inference_graph_SP3.pb'

# List of the strings that is used to add correct label for each box.
PATH_TO_LABELS = WORKING_PATH + 'data' + '/label_map_SP3.pbtxt'

detection_graph = tf.Graph()
with detection_graph.as_default():
  od_graph_def = tf.compat.v1.GraphDef()
  with tf.io.gfile.GFile(PATH_TO_FROZEN_GRAPH, 'rb') as fid:
    serialized_graph = fid.read()
    od_graph_def.ParseFromString(serialized_graph)
    tf.import_graph_def(od_graph_def, name='')
    
category_index = label_map_util.create_category_index_from_labelmap(PATH_TO_LABELS, use_display_name=True)

def load_image_into_numpy_array(image):
  (im_width, im_height) = image.size
  return np.array(image.getdata()).reshape(
      (im_height, im_width, 3)).astype(np.uint8)


# Size, in inches, of the output images.
IMAGE_SIZE = (12, 8)
# Determine filepaths for scene image and output files
file_path = os.path.abspath(sys.argv[1])
image_path = os.path.join(file_path, sys.argv[2])
image_path_detected = os.path.join(file_path, "gefundeneObjekte.jpg")
text_path_detected = os.path.join(file_path, "gefundeneObjekte.txt")


def run_inference_for_single_image(image, graph):
  with graph.as_default():
    with tf.compat.v1.Session() as sess:
      # Get handles to input and output tensors
      ops = tf.compat.v1.get_default_graph().get_operations()
      all_tensor_names = {output.name for op in ops for output in op.outputs}
      tensor_dict = {}
      for key in [
          'num_detections', 'detection_boxes', 'detection_scores',
          'detection_classes', 'detection_masks'
      ]:
        tensor_name = key + ':0'
        if tensor_name in all_tensor_names:
          tensor_dict[key] = tf.compat.v1.get_default_graph().get_tensor_by_name(
              tensor_name)
      if 'detection_masks' in tensor_dict:
        # The following processing is only for single image
        detection_boxes = tf.squeeze(tensor_dict['detection_boxes'], [0])
        detection_masks = tf.squeeze(tensor_dict['detection_masks'], [0])
        # Reframe is required to translate mask from box coordinates to image coordinates and fit the image size.
        real_num_detection = tf.cast(tensor_dict['num_detections'][0], tf.int32)
        detection_boxes = tf.slice(detection_boxes, [0, 0], [real_num_detection, -1])
        detection_masks = tf.slice(detection_masks, [0, 0, 0], [real_num_detection, -1, -1])
        detection_masks_reframed = utils_ops.reframe_box_masks_to_image_masks(
            detection_masks, detection_boxes, image.shape[1], image.shape[2])
        detection_masks_reframed = tf.cast(
            tf.greater(detection_masks_reframed, 0.5), tf.uint8)
        # Follow the convention by adding back the batch dimension
        tensor_dict['detection_masks'] = tf.expand_dims(
            detection_masks_reframed, 0)
      image_tensor = tf.compat.v1.get_default_graph().get_tensor_by_name('image_tensor:0')

      # Run inference
      output_dict = sess.run(tensor_dict,
                             feed_dict={image_tensor: image})

      # all outputs are float32 numpy arrays, so convert types as appropriate
      output_dict['num_detections'] = int(output_dict['num_detections'][0])
      output_dict['detection_classes'] = output_dict[
          'detection_classes'][0].astype(np.int64)
      output_dict['detection_boxes'] = output_dict['detection_boxes'][0]
      output_dict['detection_scores'] = output_dict['detection_scores'][0]
      if 'detection_masks' in output_dict:
        output_dict['detection_masks'] = output_dict['detection_masks'][0]
  return output_dict


if(os.path.isfile(image_path)):
    print('gefunden')
    image=Image.open(image_path)
    image_np = load_image_into_numpy_array(image)
    # detect objects in image
    # Expand dimensions since the model expects images to have shape: [1, None, None, 3]
    image_np_expanded = np.expand_dims(image_np, axis=0)
    # Actual detection.
    output_dict = run_inference_for_single_image(image_np_expanded, detection_graph)
    print(output_dict['detection_classes'])
    print(output_dict['detection_scores'])
    print(output_dict['detection_boxes'])
    # Visualization of the results of a detection.
    vis_util.visualize_boxes_and_labels_on_image_array(
        image_np,
        output_dict['detection_boxes'],
        output_dict['detection_classes'],
        output_dict['detection_scores'],
        category_index,
        instance_masks=output_dict.get('detection_masks'),
        use_normalized_coordinates=True,
        line_thickness=8)
    # save gefundeneObjekte.jpg
    im = Image.fromarray(image_np)
    im.save(image_path_detected)
    # save gefundeneObjekte.txt
    file = open(text_path_detected,"w")
    file.write("detection_classes\n")
    file.write(str(output_dict['detection_classes']))
    file.write(" \ndetection_scores\n")
    file.write(str(output_dict['detection_scores']))
    file.write("\ndetection_boxes\n")
    file.write(str(output_dict['detection_boxes']))
    file.close()
    # remove aktuelleSzene.jpg
    # os.remove(image_path)
else:
    print('nicht gefunden')
    # warte 1 Sekunde
    time.sleep(1)    
