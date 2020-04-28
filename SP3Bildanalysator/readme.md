# SP3Bildanalysator

## Aufgaben:
- [x] Warten auf ein Zeichen vom SP3Koordinator über den UDP-Node
- [x] altes Bild und alte Ergebnisse löschen
- [x] neues Bild aufnehmen
- [x] das Bild im gewünschten Verzeichnis ablegen
- [x] ein Python-Skript bereitstellen (Name des Programms und Parameter einfügen)
- [x] das Python-Skript ausführen
- [x] wiederholte Abfrage in Intervallen, ob Objekterkenner fertig ist und die Textdatei gefundeneObjekte zur Verfügung steht
- [x] die Textdatei auswerten und die wichtigen Informationen zusammenfassen
- [x] die wichtigen Informationen an SP3Koordinator schicken

## Status:
in Bearbeitung aber lauffähig

## Probleme:
- Man muss nur die gewünschten Infos empfangen und verschicken (also Strings entsprechend ändern)

## Hinweise:
- 1,2,3,4 stellen die Auswahl dar. 0 beendet das Programm. negative Zahlen stellen Fehlerfälle dar.
- Es wird 2 Sekunden gewartet, nachdem die alten Dateien gelöscht werden und nachdem das Skript ausgeführt wird
- SP3Bildanalysator öffnet die Textdatei der Ergebnisse und sucht nach dem Wort "aktuell" mit strstr()
daher muss nur die Struktur der Textdatei gefundeneObjekete klar sein, damit es richtig analysiert wird
- Als Ergebnis der Analyse stellt er ein char-Array zur Verfügung, das über den UDP-Node geschickt werden kann
- noch ist zu tun, die Eingaben über die Tastatur und Ausgaben auf dem Terminal durch die Kommunikation mit UDP zu ersetzen.
- in der zum Testzweck hinzugefügten Textdatei testAusgabe.txt stehen 3 Schlagwörter (detection_classes, detection_scores, detection_boxes)

## Quellen:
- [Kamera](https://www.opencv-srf.com/2010/09/object-detection-using-color-seperation.html)
- [Timer](https://stackoverflow.com/questions/4184468/sleep-for-milliseconds)
- [OpenCV Kontrast](https://www.opencv-srf.com/2018/02/change-contrast-of-images-and-videos.html)
- [OpenCV SW-Bild](https://docs.opencv.org/4.2.0/de/d25/imgproc_color_conversions.html)
- [OpenCV Bildgröße](https://docs.opencv.org/4.2.0/d6/d50/classcv_1_1Size__.html)
- [QtAnwendung beenden](https://stackoverflow.com/questions/8026101/correct-way-to-quit-a-qt-program)
