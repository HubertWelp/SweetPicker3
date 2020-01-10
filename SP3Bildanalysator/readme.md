# SP3Bildanalysator

## Aufgaben:
- [ ] Warten auf ein Zeichen vom SP3Koordinator über den UDP-Node
- [x] altes Bild und alte Ergebnisse löschen
- [x] neues Bild aufnehmen
- [ ] das neue Bild zuschneiden, skalieren, verarbeiten .. etc
- [x] das Bild im gewünschten Verzeichnis ablegen
- [x] ein Python-Skript bereitstellen (Name des Programms und Parameter einfügen)
- [x] das Python-Skript ausführen
- [x] wiederholte Abfrage in Intervallen, ob Objekterkenner fertig ist und die Textdatei gefundeneObjekte zur Verfügung steht
- [ ] die Textdatei auswerten und die wichtigen Informationen zusammenfassen
- [ ] die wichtigen Informationen an SP3Koordinator schicken

## Status:
in Bearbeitung aber lauffähig

## Probleme:
keine

## Hinweise:
- Die UDP-Klasse muss noch eingebettet werden
- Schnittstelle zum SP3Koordinator ist noch zu implementieren
- Schnittstelle zum SP3Objekterkenner ist noch zu implementieren

## Quellen:
- [Kamera](https://www.opencv-srf.com/2010/09/object-detection-using-color-seperation.html)
- [Timer](https://stackoverflow.com/questions/4184468/sleep-for-milliseconds)
