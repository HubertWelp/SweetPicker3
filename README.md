# SweetPicker3

Die Dateien für die Objekterkennung sind unter folgendem Link zu finden:

https://1drv.ms/u/s!AsSJrMhfn7Kiiu5hDljnQ3TNRI7_dQ?e=oSSy6u

Die Ordnerstrukur aus dem Tutorial (https://tensorflow-object-detection-api-tutorial.readthedocs.io/en/latest/training.html) wurde beibehalten.

Die im Jupyter Notebook auszuführende Datei ist "object_detection_tutorial-SP3". Dazu braucht man das Model aus dem Ordner "trained-inference-graphs" und die Label Map aus dem Ordner "annotations".

Außerdem befinden sich im Ornder "images" die Bilder, mit denen das Model traininert wurde.

# Hinweis

- Man muss den Pfad zum SP3Objekterkenner im Quellcode händisch ändern, wenn sich die Umgebung ändert
- Die Schnittstelle zwischen SP3Objekterkenner und SP3Bildanalysator funktioniert so nicht -> ich werde einen UDP-Node im SP3Objekterkenner implementieren
