/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */
 
#ifndef _BUCH_
#define _BUCH_
#include <iostream>
#include "medium.h"
using namespace std;
class Buch : public Medium
{
public:
  Buch();
  Buch(int Mednr,String MedNam, String MedAut);
  Buch(const Buch& rhs);
  
  short getExemplare(void);
  void Exemplar_ausleihen(void);
  void Exemplar_zurueckgeben(void);
  String getMediumName(void);
  String getMediumAutor(void);
  int getMediumNummer();
  bool vergleich(int nummer);
  bool vergl(Buch* rhs);
  long int laden(long int curpos);
  long int speichern(long int curpos);
  
  Buch& operator= (const Buch& rhs);
  bool show(bool int_exempl=false);
  ~Buch();
private:
//evtl noch Inventarnummer oder Regalordnung...
int MediumNummer;
short Exemplare;
String MediumName;
String MediumAutor;
};
#endif
