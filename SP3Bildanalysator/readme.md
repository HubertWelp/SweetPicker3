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
- [ ] die wichtigen Informationen an SP3Koordinator schicken

## Status:
in Bearbeitung aber lauffähig

## Probleme:
- Die Rückmeldung an den SP3Koordinator muss noch implementiert und ausgeführt werden

## Hinweise:
- 1,2,3,4 stellen die Auswahl dar. 0 beendet das Programm. negative Zahlen stellen Fehlerfälle dar.
- Es wird 2 Sekunden gewartet, nachdem die alten Dateien gelöscht werden und nachdem das Skript ausgeführt wird
- SP3Bildanalysator öffnet die Textdatei der Ergebnisse und sucht nach dem Wort "aktuell" mit strstr()
daher muss nur die Struktur der Textdatei gefundeneObjekete klar sein, damit es richtig analysiert wird
- Als Ergebnis der Analyse stellt er ein char-Array zur Verfügung, das über den UDP-Node geschickt werden kann
- noch ist zu tun, die Eingaben über die Tastatur und Ausgaben auf dem Terminal durch die Kommunikation mit UDP zu ersetzen.

## Quellen:
- [Kamera](https://www.opencv-srf.com/2010/09/object-detection-using-color-seperation.html)
- [Timer](https://stackoverflow.com/questions/4184468/sleep-for-milliseconds)
