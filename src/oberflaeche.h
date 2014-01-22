/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#ifndef _OBERFLAECHE_
#define _OBERFLAECHE_
#include "string.h"
#include "liste.h"
class Oberflaeche
{
public:
  Oberflaeche();
  void menue();
  
  void benutzer_anlegen();
  void benutzer_loeschen();
  Person* benutzer_suchen();
  void medien_hinzufuegen();
  void medien_anzeigen();
  void medien_loeschen();
  void medien_ausleihen();
  void medien_zurueckgeben();
  void laden();
  void speichern();
 signed int getzahl(short whnr);
 void setzahl(int buchnr,int vidnr,int kundnr);
  ~Oberflaeche();
  
private:

  Liste<Person> personenliste;
  Liste<Video> videoliste;
  Liste<Buch> buchliste;
  int akt_buchnr;
  int akt_kundnr;
  int akt_videonr;
};
#endif
