/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#ifndef _PERSON_
#define _PERSON_
#include <iostream>
#include "liste.h"
#include "buch.h"
#include "video.h"
using namespace std;
// um die synchronität zwischen der medienliste und den kleinen ausleihlsiten zu gewährleisten
// kann zwar die referenz des auszuliehenden mediums zurücggeben werden aber nur um deren
// inhalt auszulesen und das objekt in der hauptmedienlsite zu finden
// ansonsten keine garantie das die referenz auf das objekt der hauptliste zeigt...
class Person
{
public:
   
	Person();
	Person(int nummer,String Vorname,String Nachname);
  
	void leihenBuch(Buch* Leih);
	void leihenVideo(Video* Leih);
  
	int zurueckgebenBuch(void);
	int zurueckgebenVideo(void);
	void showAusgeliehen(void);
	bool show(bool int_ben=false);
	bool exist_file(char * medium);
	bool vergleich(int nummer);
	bool vergl(Person* rhs);
	String getVorname(void);
	String getNachname(void);
	int getBenNr(void);
	long int laden(long int curpos);
	 long int speichern(long int curpos);

	~Person();// die ausleihdateien werden NICHT gelöscht, aber beim löschen einer Person muss die Liste leer sein !!
  
private:
	int benutzernummer;
	// Variablennamen sollten mit Kleinbuchstaben beginnen
	String Vorname;
	String Nachname;
};
#endif

