/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#ifndef _MEDIUM_
#define _MEDIUM_
#include "string.h"
#include <iostream>
using namespace std;
class  Medium //abstrakte Klasse
{
public:
  Medium(){/*cout<<"MediumKonstruktor"<<endl;*/};
  virtual short getExemplare(void)=0;
  virtual void Exemplar_ausleihen(void)=0;
  virtual void Exemplar_zurueckgeben(void)=0;
  virtual String getMediumName() =0;
  virtual String getMediumAutor() =0;
  virtual int getMediumNummer() =0;
  virtual bool vergleich(int nummer) =0;

  virtual ~Medium(){/*cout<<"Mediumdekonstruktor"<<endl;*/};
};

#endif
