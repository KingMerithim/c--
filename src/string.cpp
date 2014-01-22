/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#include "string.h"
#include <iostream>
#include <string.h>
using namespace std;

	String::String()
	{
		//cout<<"StringKonstruktor "<<endl;
		this->inhalt= new char[1];
		strcpy(this->inhalt,"\0");
		this->laenge=0;
	}
  String::String(const char * in)
  {
	  //cout<<"StringKonstruktor_2 "<<endl;
	  this->laenge=strlen(in);
	  //cout<<"String_2: Inhalt"<<in<<" Laenge" <<this->laenge<<endl;
	  this->inhalt= new char[(this->laenge+1)];//terminierende null
	  strcpy(this->inhalt,in);
	  strcat(this->inhalt,"\0");
	  // cout<<"String_2: KlassenInhalt"<<this->inhalt<<" Laenge: "<<this->laenge<<endl;
  }
  String::String(char * in)
  {
	  //cout<<"StringKonstruktor_2 "<<endl;
	  this->laenge=strlen(in);
	  //cout<<"String_2: Inhalt"<<in<<" Laenge" <<this->laenge<<endl;
	  this->inhalt= new char[(this->laenge+1)];//terminierende null
	  strcpy(this->inhalt,in);
	  strcat(this->inhalt,"\0");
	  // cout<<"String_2: KlassenInhalt"<<this->inhalt<<" Laenge: "<<this->laenge<<endl;
  }

  String::String(const String & rhs) // Üblicherweise rhs: "Right Hand Side"
    {
      this->inhalt = new char[strlen(rhs.inhalt)+ 1];
      this->laenge=rhs.laenge;
      strcpy(this->inhalt, rhs.inhalt);
    }

  char* String::getInhalt(void)
  {
	  return this->inhalt;
  }
  void String::setInhalt(const char * in)
  {
	  //da es einen Kostruktor genutzt haben muss,
	  // gibt es auch einen speicherbereich;
	  delete[] this->inhalt; 
	  this->laenge=strlen(in);
	  this->inhalt= new char[this->laenge+1];//terminierende null
	  strcpy(this->inhalt,in);
	  strcat(this->inhalt,"\0");
  }
  long String::getLaenge(void)
  {
	  return this->laenge;
  }
  String& String::operator= (const String& rhs)
  {
    if(this != &rhs)
	{
    delete[] this->inhalt;
    this->laenge=rhs.laenge;
    //cout<<"=Operator: RHS Inhalt"<<rhs.getInhalt()<<" RHS Laenge" <<this->laenge<<endl;
    this->inhalt= new char[this->laenge+1];//terminierende null
	strcpy(this->inhalt,rhs.inhalt);
	strcat(this->inhalt,"\0");
   }
	return *this; //Referenz auf das Objekt selbst zurückgeben
  }		
  String& String::operator= (const char* rhs)
  {
	if(this->inhalt!=rhs)
	{
	delete[] this->inhalt;
    this->laenge=strlen(rhs);
   this->inhalt= new char[this->laenge+1];//terminierende null
	strcpy(this->inhalt,rhs);
	strcat(this->inhalt,"\0");
	}
	return *this;
  }
  String::~String()
  {
	  
	// cout<<"StringDekonstruktor "<<this->inhalt<<endl;
	  delete[] this->inhalt;
  }
  
  
  
  bool operator!= (const String& lhs, const String& rhs)
   {
	   return ! strcmp(lhs.inhalt,rhs.inhalt);
   }
  bool operator!= (const String& lhs, const char* rhs)
  {
	   return ! strcmp(lhs.inhalt,rhs);
  }
  bool operator== (const String& lhs, const String& rhs)
  {
	   return  strcmp(lhs.inhalt,rhs.inhalt);
  }
  bool operator== (const String& lhs, const char* rhs)
  {
	   return  strcmp(lhs.inhalt,rhs);
  }
  
  ostream &operator<< (ostream &ostr, const String &a)
  {
	  ostr << a.inhalt;
   return ostr;
  }

