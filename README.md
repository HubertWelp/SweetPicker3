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

# Schritte

1. **Richtige Pfade:** Man muss sicherstellen, dass die Dateien in den richtigen Verzeichnissen liegen.<br>Dafür kann man entweder alle Pfade so machen, wie im Programm geschrieben ist, oder die Pfad im Programm in der Header-Datei `Ressourcen.h` anpassen.
2. **Betriebsbereite Kamera:** Man muss sicherstellen, dass ein Kamera angeschlossen ist und auch funktioniert.
3. **SP3Objekterkenner starten:** Dabei kann man das in der Anaconda-Umgebung machen oder auch ohne. Man sollte ein Terminal öffnen und am besten zum Skript-Verzeichnis navigieren dann das Skript ausführen.<br>In der Anaconda-Umgebung geht das mit Python V2 `python` und auch mit Python V3 `python3`, danach folgt der Skriptname `SP3Objekterkenner.py`<br>Ohne Umgebung geht das nur mit Python V3 `python3` und dem Skriptnamen `SP3Objekterkenner-Rami.py`<br>Dann wird der SP3Objekterkenner das Model reinladen und danach eine Meldung ausgeben, dass er bereit ist.
> Zur Skriptausführung ohne Umgebung sollte man mit `pip show tensorflow-gpu | grep Location` überprüfen, mit wo TensorFlow installiert ist und mit welcher Python-Version es kompatibel ist.
4. **SP3Bildanalysator starten:** Man kann es entweder von der Qt-IDE erstellen und laufen lassen oder erstellen und dann vom build-Verzeichnis das Programm im Terminal starten.
5. **SP3Koordinator (oder chatGUI) starten:** Weil das Projekt ohne den SP3Koordinator ergänzt wurde, musste der SP3Koordinator durch chatGUI ersetzt werden. Diese Anwendung ist im SP3-Verzeichnis vorhanden und kann ebenfalls von der Qt-IDE gestartet werden.
> Eingabe: 1 für Maoam | 2 für Snickers | 3 für MilkyWay | 4 für Schockoriegel | 0 zum Abbrechen | alle anderen Eingaben werden ignoriert

# Anmerkung
Ohne die virtuelle Anaconda-Umgebung wird deutlich schneller das Model reingeladen und die Bilderkennung durchgeführt.

# Stand
07.09.2020
