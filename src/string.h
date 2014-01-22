/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#ifndef _STRING_
#define _STRING_
#include <iostream>
class String
{
public:
	String();
  String(const char* in);
  String(char* in);
  String(const String& rhs); //KopierKonstruktor
  char* getInhalt(void);
  void setInhalt(const char* in);
  long getLaenge(void);
  
  String& operator= (const String& rhs);
  String& operator= (const char* rhs);
  
 friend bool operator!= (const String& lhs, const String& rhs);
 friend bool operator!= (const String& lhs, const char* rhs);
  
 friend bool operator== (const String& lhs, const String& rhs);
 friend bool operator== (const String& lhs, const char* rhs);
 
 friend std::ostream &operator<< (std::ostream &ostr, const String &a);
  ~String();
private:
  char* inhalt;
  long laenge;
};

#endif
