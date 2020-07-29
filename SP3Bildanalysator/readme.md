# SP3Bildanalysator
Stand 29.07.2020

## Aufgaben:
- [x] Warten auf ein Zeichen vom SP3Koordinator über den UDP-Node
- [x] altes Erkennungsbild, alte Bildaufnahme und alte Text-Ergebnisse löschen
- [x] neues Bild aufnehmen
- [x] das Bild im gewünschten Verzeichnis ablegen
- [x] Eine Nachricht über einen UDP-Node an den SP3Objekterkenner senden, um mit der Objekterkennung zu starten
- [x] wiederholte Abfrage jede Sekunde für insgesamt 20 Sekunden, ob Objekterkenner fertig ist und die Textdatei gefundeneObjekte zur Verfügung steht
- [x] die Textdatei auswerten und die wichtigen Informationen zusammenfassen
- [x] die wichtigen Informationen an SP3Koordinator schicken
- [x] Nachricht an den SP3Objekterkenner senden

## Status:
lauffähig

## Probleme:

- Manchmal wird kein neues Foto aufgenommen sondern das alte übernommen
- Manchmal gibt der SP3Objekterkenner falsche Ergebnisse zurück (Koordinate 2.593521e-7)

## Hinweise:
- Die Textverarbeitung erfolgt mit Hilfe von Qt-Bibliotheken und nicht mit Standard c-Bibliotheken.
- 1,2,3,4 stellen die Auswahl dar. 0 beendet sowohl SP3Bildanalysator als auch SP3Objekterkenner. Alle andere Zahlen bzw. Zeichen werden ignoriert.
- Es wird 2 Sekunden gewartet, nachdem die alten Dateien gelöscht werden und nachdem das Skript ausgeführt wird.
- Als Ergebnis der Analyse stellt er ein char-Array zur Verfügung, das über den UDP-Node geschickt werden kann.
- Die Anwendung ermittelt die Box der Klasse mit der höchsten Wahrscheinlichkeit und muss nun dies in Koordinaten umrechnen.
- Der SP3Bildanalysator gibt die Koordinaten der gesuchten Süßigkeit zurück. Dabei ist der Bezugspunkt (Nullpunkt) der Punkt in der oberen linken Ecke im aufgenommenen Foto.
- Es spielt keine Rolle, wo und in welcher Reihenfolge die gesuchten Sätze in der Text-Datei stehen. Die Suche ist adaptiv.
- Das Model ist für Objekterkennung mit CPU sowie GPU trainiert worden (also es muss nicht für Bearbeitung mit der GPU neu trainiert werden).
- Wenn SP3Objekterkenner noch nicht gestartet hat bzw. nicht antwortet, verwirft SP3Bildanalysator die Anfrage und wartet auf eine neue.

## Quellen:
- [Kamera](https://www.opencv-srf.com/2010/09/object-detection-using-color-seperation.html)
- [Timer](https://stackoverflow.com/questions/4184468/sleep-for-milliseconds)
- [OpenCV Kontrast](https://www.opencv-srf.com/2018/02/change-contrast-of-images-and-videos.html)
- [OpenCV SW-Bild](https://docs.opencv.org/4.2.0/de/d25/imgproc_color_conversions.html)
- [OpenCV Bildgröße](https://docs.opencv.org/4.2.0/d6/d50/classcv_1_1Size__.html)
- [QtAnwendung beenden](https://stackoverflow.com/questions/8026101/correct-way-to-quit-a-qt-program)
- [Erklärung detection_boxes](https://stackoverflow.com/questions/48915003/get-the-bounding-box-coordinates-in-the-tensorflow-object-detection-api-tutorial): Die Reihenfolge ist [obenY% linksX% untenY% rechtsX%]
