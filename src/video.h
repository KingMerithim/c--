/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#ifndef _VIDEO_
#define _VIDEO_
#include <iostream>
#include "medium.h"
using namespace std;
class Video : public Medium
{
public:
   Video();
   Video(int Mednr,String MedNam, String MedReg);
   Video(const  Video& rhs);
   
  short getExemplare(void);
  void Exemplar_ausleihen(void);
  void Exemplar_zurueckgeben(void);
  String getMediumName(void);
  String getMediumAutor(void);
  int getMediumNummer();
  bool vergleich(int nummer);
  bool vergl(Video* rhs);
  bool laden();
  Video& operator= (const Video& rhs);
  long int laden(long int curpos);
  long int speichern(long int curpos);
  
  bool show(bool int_exempl=false);
  ~Video();
private:
//evtl noch Inventarnummer oder Regalordnung...
  int MediumNummer;
short Exemplare;
String MediumName;
String MediumRegisseur;
};
#endif
