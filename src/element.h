/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#ifndef _ELEMENT_
#define _ELEMENT_
#include "string.h"
#include "buch.h"
#include "video.h"
#include <iostream>
//#include "person.h"
//einfache verkettung
//pointer sind nur auf orginaldaten zeigend --> kein neuer speicherplatz geholt
template <typename T> class Element
{
	public:
	Element();
	Element( T*  newdat);//neues element  mit Datenpaket erzeugen
	Element( T & newdat,Element<T>* n);//neues element  mit Datenpaket erzeugen
	
	T* getData(void); //datenpaket ausgeben
	Element<T>* getNext(void); //nachfolger ausgeben
	
	int setData(T* newdat); //datenpaket setzen
	int setNext(Element<T>* n); //nachfolger setzen
	
	~Element();
	
	private:
	T * Data;
	Element<T> * next;
	
};

template <typename T>
Element<T>::Element(void)
{
	this->Data=NULL;
	this->next=NULL;

}
template <typename T>
Element<T>::Element( T * newdat)
{
	this->Data=newdat;
	this->next=NULL;
}
template <typename T>
Element<T>::Element( T & newdat,Element<T>* n)
{
	this->Data=&newdat;
	this->next=n;
}
template <typename T>
T* Element<T>::getData(void)
{
	return this->Data;
}
template <typename T>
Element<T>* Element<T>::getNext(void)
{
	return this->next;
}
template <typename T>
int Element<T>::setData(T* newdat)
{
	this->Data=newdat;
	return 0;
}
template <typename T>
int Element<T>::setNext(Element<T>* n)
{
	this->next=n;
	return 0;
}
template <typename T>
Element<T>::~Element()
{
	delete this->Data;
	this->next=NULL;
	//cout<<"Element gelöscht"<<endl;
}
#endif
