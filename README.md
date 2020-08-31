# SweetPicker3

Die Dateien für die Objekterkennung sind unter folgendem Link zu finden:

https://1drv.ms/u/s!AsSJrMhfn7Kiiu5hDljnQ3TNRI7_dQ?e=oSSy6u

Die Ordnerstrukur aus dem Tutorial (https://tensorflow-object-detection-api-tutorial.readthedocs.io/en/latest/training.html) wurde beibehalten.

Die im Jupyter Notebook auszuführende Datei ist "object_detection_tutorial-SP3". Dazu braucht man das Model aus dem Ordner "trained-inference-graphs" und die Label Map aus dem Ordner "annotations".

Außerdem befinden sich im Ornder "images" die Bilder, mit denen das Model traininert wurde.

# Hinweis

- Man muss nur noch das Skript (ohne Parameter) ausführen, weil SP3Objekterkenner jetzt unabhängig von SP3Bildanalysator startet.
- Man muss den Pfad zum SP3Objekterkenner im Quellcode händisch ändern, wenn sich die Umgebung ändert
- Man muss SP3Bildanalysator und SP3Objekterkenner einzeln ausführen
- Die Schnittstelle zwischen SP3Objekterkenner und SP3Bildanalysator ist eine UDP-Verbindung<br>dabei hat SP3Objekterkenner die Port-Nummer 5850
- Tabulatoren führen in Python-Skripten zu Problemen und sollten deswegen vermieden werden.

# Probleme

keine
