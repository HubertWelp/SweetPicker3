# SP3Textanalysator

## Ziel
Die Erg�nzung von SP3Bildanalysator auf dem privaten Rechner zu Hause ist schwierig, da keine Kamera angeschlossen ist und SP3Koordinator nicht lauff�hig ist (auf dem privaten Rechner).
Daher wird eine Klasse zur Textauswertung erstellt und sp�ter in SP3Bildanalysator integriert.

## Status
<img src="https://www.utahmortgage.co/img/user_images/25974.png" width="20" title="Projekt-Status" />

## Anmerkungen
- Die Zahl 40 f�r die Anzahl der einzulesenden Zeichen aus einer Zeile "MAXLESEN" war zu klein .. Wir nehmen 100
- Eine Anpassung der Auswertung ist einfach und zentral in der Header-Datei der Klasse Textauswerter durchzuf�hren
- Es spielt keine Rolle, wo und in welcher Reihenfolge die gesuchten S�tze in der Text-Datei stehen. Die Suche ist adaptiv.
- Eine globale Member-Variable anzulegen und sie w�hrend des Auswertungsprozesses entsprechend zu belegen hat nicht funktioniert. Deswegen wird diese Member-Variable als Parameter an die jeweilige Funktion �bergeben.

## Stand
05.04.2020
