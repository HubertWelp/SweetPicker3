# SP3Textanalysator

## Ziel
Die Erg�nzung von SP3Bildanalysator auf dem privaten Rechner zu Hause ist schwierig, da keine Kamera angeschlossen ist und SP3Koordinator nicht lauff�hig ist (auf dem privaten Rechner).
Daher wird eine Klasse zur Textauswertung erstellt und sp�ter in SP3Bildanalysator integriert.

## Status
<img src="http://clipart-library.com/images/8iE7qe8ia.png" width="20" title="Projekt-Status" />

## Anmerkungen
- Die Zahl 40 f�r die Anzahl der einzulesenden Zeichen aus einer Zeile "MAXLESEN" war zu klein .. Wir nehmen 100
- Eine Anpassung der Auswertung ist einfach und zentral in der Header-Datei der Klasse Textauswerter durchzuf�hren
- Es spielt keine Rolle, wo und in welcher Reihenfolge die gesuchten S�tze in der Text-Datei stehen. Die Suche ist adaptiv.
- Eine globale Member-Variable anzulegen und sie w�hrend des Auswertungsprozesses entsprechend zu belegen hat nicht funktioniert. Deswegen wird diese Member-Variable als Parameter an die jeweilige Funktion �bergeben.
- Die Anwendung kann die gesuchten Daten in Arrays abspeichern. Nun m�ssen die sortiert und ausgewertet werden
- Die Anwendung ermittelt die Box der Klasse mit der h�chsten Wahrscheinlichkeit und muss nun dies in Koordinaten umrechnen.
- [Erkl�rung detection_boxes](https://stackoverflow.com/questions/48915003/get-the-bounding-box-coordinates-in-the-tensorflow-object-detection-api-tutorial): Die Reihenfolge ist [obenY% linksX% untenY% rechtsX%]

## Stand
06.04.2020
