#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>
#include "konfig.h"
#include "objektinformation.h"

namespace Ui {
class Monitor;
}

class Monitor : public QMainWindow
{
    Q_OBJECT

public:
    Monitor(QWidget *parent = nullptr);
    ~Monitor() override;

public slots:
    /** @brief Speichert alle Parameter
    *
    * Diese Methode speichert alle Parameter in der Konfig.ini Datei und setzt alle Variablen
    * auf den aktuellen Wert, sodass bei Veränderung der GUI Werte die gespeicherten Werte
    * wieder geladen werden können.
    *
    * Bei Erfolg erscheint ein Fenster mit dem Hinweis, dass die Parameter gespeichert wurden.
    * Bei Misserfolg erscheint ein kleines Fnester mit dem Hinweis, dass die Parameter nicht gespeichert wurden.
    *
    * @return  void
    *
    */
    void parameterSpeichern();

    /** @brief Setzt die Bildbreite auf die vorherige Bildbreite zurück
    *
    * Diese Methode setzt den Wert der zu speichernden Bildbreite auf den vorherigen Wert zurück
    *
    * @return  void
    *
    */
    void erodeZuruecksetzen();

    /** @brief Setzt die Bildhöhe auf die vorherige Bildhöhe zurück
    *
    * Diese Methode setzt den Wert der zu speichernden Bildhöhe auf den vorherigen Wert zurück
    *
    * @return  void
    *
    */
    void dillateZuruecksetzen();

    /** @brief Setzt die KameraID auf die vorherige KameraID zurück
    *
    * Diese Methode setzt den Wert der zu speichernden KameraID auf den vorherigen Wert zurück
    *
    * @return  void
    *
    */
    void kameraIDZuruecksetzen();

    /** @brief Setzt die Rahmendicke auf die vorherige Rahmendicke zurück
    *
    * Diese Methode setzt den Wert der zu speichernden Rahmendicke auf den vorherigen Wert zurück
    *
    * @return  void
    *
    */
    void rahmendickeZuruecksetzen();

    /** @brief Setzt die Farbe auf die vorherige Farbe zurück
    *
    * Diese Methode setzt die Farbe des Knopfes und die der zu speichernden Variable auf die vorherige Farbe zurück
    *
    * @return  void
    *
    */
    void rahmenfarbeZuruecksetzen();

    /** @brief Zeigt ein Fenster mit einer Farbpalette an und setzt die Farbe des Knopfes auf die gewählte Farbe
    *
    * Diese Methode öffnet ein Fenser mit einer Farbpalette und setzt die Farbe des Knopfes auf die gewählte Farbe
    * Wird keine Farbe ausgewählt oder das Fenster anderweitig geschlossen, wird keine neue Farbe gesetzt.
    *
    * @return  void
    *
    */
    void zeigeFarbpalette();

    /** @brief Holt sich die neusten Informationen/Dateien und zeigt diese an
    *
    * Diese Methode lässt den Inhalt des Objekts info aktualisieren und schreibt diese Infos in die GUI
    * Falls nicht alle Dateien verfügbar sind, wird ein Fehlerfenster geöffnet.
    *
    * @return  void
    *
    */
    void aktualisieren();

    /** @brief Checkt bei jeder Tastatureingabe, ob Enter oder Escape gedrückt wurde und reagiert entsprechend
    *
    * Falls F5 gedrückt wird, wird die Methode aktualisieren gestartet
    * Falls Escape gedrückt wird, wird das Fenster geschlosssen
    *
    * @return  void
    *
    */
    void keyPressEvent(QKeyEvent* pe) override;

    /** @brief Horcht, ob das Fenster in der Größe verändert wird
    *
    * Falls das Fenster in der Größe verändert wird, wird die Methode zeichneInfo() aufgerufen,
    * damit sich die Bilder in der Anzeige mit der Größe des Fensters skalieren.
    *
    * @return  void
    *
    */
    void resizeEvent(QResizeEvent*) override;

private:
    Ui::Monitor *ui;

    KonfigAdmin k;
    Objektinformation info;
    int previousBildbreite;
    int previousBildhoehe;
    int previousKameraID;
    int previousRahmendicke;
    QColor previousRahmenfarbe;
    QColor nextRahmenfarbe;
    void zeichneInfo();
};

#endif // MONITOR_H
