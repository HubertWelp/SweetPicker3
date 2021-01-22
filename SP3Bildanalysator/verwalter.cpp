#include "verwalter.h"

Verwalter::Verwalter()
{
    cam = new Kamera(ressourcen::PWD.c_str());
    textAuswerter = new Textauswerter;
    node = new UDPNode(5840);
    orientierungsErmittler = new OrientierungsErmittler;
    konfig = new Konfig(); //Standardpfad
}

void Verwalter::loescheAlt()
{
    //Setze Ordnerpfad
    char* pfad = new char [256];
    strcpy(pfad,ressourcen::PWD.c_str());
    strcat(pfad,BILDABLAGE);

    //Öffne Ordner
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(pfad)) != nullptr)
    {
        while((ent = readdir(dir)) != nullptr)
        {
            //Lese Dateien im Ordner & Lösche
            char* datei = new char [256];
            strcpy(datei,pfad);
            strcat(datei,ent->d_name);
            remove(datei);
            //std::cout << datei << std::endl;
            delete [] datei;
        }
        closedir(dir);
    }
    delete [] pfad;
}

void Verwalter::fuehreSkriptAus()
{
    node->sendmessage("run","127.0.0.1",5850);
}

bool Verwalter::warte()
{
    int i;
    QString pfad = QString(QString::fromStdString(ressourcen::PWD));
    pfad.append(QString(TEXTABLAGE));
    QFile datei(pfad);

    /*20 Prüfe für 20 Sekunden ob die Datei vorhanden ist */
    for(i = 0; !(QFileInfo::exists(pfad)) && !datei.open(QIODevice::ReadOnly) && (i < 200); i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    /*Datei vorhanden oder 20 Sekunden vergangen*/

    if(i<200)
    {
        datei.close();
       return true;
    }
    else
    {
        datei.close();
        return false;
    }
}

const char* Verwalter::verarbeiteText(void)
{
    FILE* datei;
    char inhalt[500];
    char* pfad = new char [256];

    strcpy(pfad,ressourcen::PWD.c_str());
    strcat(pfad,TEXTABLAGE);

    datei = fopen(pfad,"r");
    if (!datei) printf("\n---------------\nFehler beim Öffnen der Textdatei\n---------------\n");
    fgets(inhalt,90,datei);

    delete []  pfad;

    return  strstr(inhalt,"aktuell");
}


void Verwalter::messageReceived(std::string msg)
{
    wahl = atoi(msg.c_str());

    ressourcen::BILDHHE = konfig->getBildhoehe();
    ressourcen::BILDBRT = konfig->getBildbreite();
    //ressourcen::PWD = konfig->getAblageort();
    int maxObjekte;
    for(maxObjekte = 1; konfig->getObjektname(maxObjekte)!="";maxObjekte++);
    maxObjekte--;

    if(wahl>0 && wahl<= maxObjekte)
    {
        // altes Bild und alte Ergebnisse löschen
        loescheAlt();
        // aktuelles Bild aufnehmen und im folgenden relativen Verzeichnis ablegen
        char* pfad = new char [256];
        strcpy(pfad,BILDABLAGE);
        strcat(pfad,BILD);
        cam->setzeKameraID(konfig->getKameraID());
        cam->nehmeAuf(pfad);
        delete [] pfad;
        // Ein Python-Skript vom SP3Objekterkenner ausführen (python programmname TEXTABLAGE wahl)
        fuehreSkriptAus();
        // warten, bis SP3Objektereknner  fertig ist
        if(warte())
        {
            // Erkennungsergebnis einlesen und auswerten
            int erg = textAuswerter->liesEin(QString(QString::fromStdString(ressourcen::PWD))+QString(TEXTABLAGE));
            //std::cout << erg << std::endl;
            if(erg == 3)
            {
                //Rahmen und Mittelpunkt auswerten
                std::tie(yMin,xMin,yMax,xMax,xMittelpunkt,yMittelpunkt) = textAuswerter->werteAus3(wahl);
                //std::cout << "setze koordinaten" << std::endl;
                orientierungsErmittler->setzeKoordinaten(yMin,xMin,yMax,xMax);
                orientierungsErmittler->setzeWahl(wahl);
                //Ermittle Orientierung
                //std::cout << "ermittle orientierung" << std::endl;
                std::tie(erfolg,winkel,breite) = orientierungsErmittler->ermittleOrientierung();
                std::string ergebnis;
                //Erzeuge Nachrichtenstring für den Roboter
                //Erzeuge AusschnittErgebnis.csv für Admin Komponente
                std::ofstream ausschnittErgebnis;
                ausschnittErgebnis.open(std::string(ressourcen::PWD).append(BILDABLAGE).append("ausschnittErgebnis.csv"));
                if(erfolg <= -1)
                {
                    ergebnis = "Fehler";
                    ausschnittErgebnis << -1 << ";" << -1 << ";" << -1 << ";" << -1 << ";" << -1;
                }
                else
                {
                    ergebnis = std::to_string(xMittelpunkt) + " " + std::to_string(yMittelpunkt) + " " + std::to_string(0) + " " + std::to_string(winkel) + " " + std::to_string(breite);
                    ausschnittErgebnis << msg << ";" << winkel << ";" << breite << ";" << xMittelpunkt << ";" << yMittelpunkt;
                }
                ausschnittErgebnis.close();
                //Sende Nachrichtenstring für den Roboter
                std::cout << ergebnis << std::endl;
                sendmessage(ergebnis,"127.0.0.1",5843);

            }
            else
            {
                std::string ergebnis;
                std::ofstream ausschnittErgebnis;
                ausschnittErgebnis.open(std::string(ressourcen::PWD).append(BILDABLAGE).append("ausschnittErgebnis.csv"));
                ergebnis = "Fehler";
                ausschnittErgebnis << -1 << ";" << -1 << ";" << -1 << ";" << -1 << ";" << -1;
                ausschnittErgebnis.close();
                std::cout << ergebnis << std::endl;
                sendmessage(ergebnis,"127.0.0.1",5843);
                std::cout << "fehlermeldung - textauswerter - " << erg << std::endl;
            }
        }
    }
    else if(wahl == 0)
    {
        loescheAlt();
        node->sendmessage("stop","127.0.0.1",5850);
        QApplication::quit();
    }
}

void Verwalter::testTextauswerter()
{
    int i, ii;

    for(i=1;i<5;i++)
    {
        for(ii=0;ii<100;ii++)
        {
            this->messageReceived(std::to_string(i));
            std::cout << i << " " << ii << std::endl;
        }
    }
}

