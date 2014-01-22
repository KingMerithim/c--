/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#ifndef _LISTE_
#define _LISTE_

#include <iostream>
#include <stdio.h>

#include "element.h"
#include "string.h"
#include "buch.h"
#include "video.h"
#include "person.h"
#include "dateiarbeit.h"

//ringverkettung
 template<typename M> class Liste
 {
	 public:
	 Liste();
	 
	 int add( M* data);
	 //bekommt das neu einzutragende datenpaket und die beschreibung 
	 //weche parameter die funktion vergleich bracuht und was sie zurückgibt
	 
	 //int remove(void);// löscht current
	 int remove (M* toremove=NULL);
	 M* getData(void);//daten vom Current
	 M* search(int krit);
	 Element<M>* getCurrent(void);
	 //änderung der Zeiger
	 int goNext(void);
	 int setCurrentFirst(void);
	 
	 int save(Dateiarbeit<M>& datarb);
	 int load(String vsd);
	 
	 int show(bool int_exempl=false); //zeigt alle anhängenden Datensätze in der Liste
	 ~Liste();
	 
	 private:
	// Dateiarbeit<M> datarb;
	 Element<M>* first;
	 //dem ersten element muss das jeweils letzte elemet als vorgänger gegeben werdem
	 Element<M>* current;
	 
 };

 template <typename M>
 Liste<M>::Liste()
 {

 	this->first=NULL;
 	  this->current=NULL;
 }
 template <typename M>
 int Liste<M>::add( M* data)
 {
 	//aufpassen das das temporäre element nciht gelscht wird wenn cih nur die pointer weiterreiche
 	Element<M>* pEle=new Element<M>(data);
 	if(this->first==NULL)
 	{
 		this->first=pEle;
 		this->first->setNext(this->first);
 		this->current=pEle;
 	}
 	else
 	{
 		short rundherum=0;
 		this->current=this->first;
 		/*
 		 * 0=hier einfügen
 		 * 1=eins weiterschieben
 		 *
 		 * vergleichsfunktion guckt nur ob current<data ist zb
 		 */
 		while(!this->current->getData()->vergl(data) && rundherum!=1)
 		{
 			goNext();
 			if(this->current==this->first)
 			{
 				rundherum=1;
 			}
 		}
 		//ab dierser stelle wird hier nun eingefügt

 		//der vorgänger gesucht
 		 Element<M>* vorg=this->first;
 		 do
 		 {
 			 vorg=vorg->getNext();
 		 }while(this->current!=vorg->getNext());

 		 //das neue Element wird zwischen dem derzeitigen und dessen vorgänger geschoben
 		 vorg->setNext(pEle);
 		 pEle->setNext(this->current);
 	}
 	return 0;
 }
 template <typename M>
 int Liste<M>::remove (M* toremove)
 {
 	 //löscht an der current position
 	if(toremove==NULL)
 	{
 		toremove=this->current->getData();
 	}
 		 if(this->current==NULL)
 		 {
 			 return -1;
 		 }
 		 else if(this->current->getNext()==this->current && this->current->getData()==toremove)
 		 {	 //wenn nur noch ein element übrig ist und dieses mit dem zu löschenden pointer übereinstimmt

 			 this->first=NULL;
 			 //wenn toremove == first ist

 			 delete this->current;
 			 this->current=NULL;
 		 }
 		 else
 		 {
 			 Element<M>* vorg=this->current=this->first;
 			 this->current=this->current->getNext();
 			 //wenn toremove== first+1 (nachfolger) ist
 			 while(!(this->current->getData()==toremove))
 			 {
 				 //wenn toremove== first+ x ist
 				 vorg=this->current;
 				this->current=this->current->getNext();
 				if(this->current==this->first)//wenn er einmal rum ist
 				{
 					break;
 				}
 			 }
 			 if(!(this->current->getData()==toremove))
 			 {//wenn nix getroffen wurde
 				 return -1;
 			 }
 			 if(this->current==this->first)
 			 {
 				 this->first=this->first->getNext();
 			 }
 			 vorg->setNext(this->current->getNext());
 			 vorg=this->current->getNext();
 			 delete this->current;
 			 this->current=vorg->getNext();
 		 }


 		 return 0;
 }
 template <typename M>
  M* Liste<M>::getData(void)
  {
 	 if(this->current==NULL)
 	 {
 		 cout<<"Element existiert nicht. Somit Fehler beim Datenholen"<<endl;
 	 }
 	 return this->current->getData();
  }
  template <typename M>
  Element<M>* Liste<M>::getCurrent(void)
  {
	  if(this->current==NULL)
	  {
		  return NULL;
	  }
 	 return this->current;
  }
  //änderung der Zeiger
 template <typename M>
  int Liste<M>::goNext(void)
  {
 	 if(this->current->getNext()!=NULL)// ==NULL sollte nur bei schlechter implementation vorkommen
 	 {
 		this->current=this->current->getNext();
 		return 0;
      }
      return 1;
  }
  template <typename M>
   int Liste<M>::setCurrentFirst(void)
   {
 	  this->current=this->first;
 	  return 0;
   }

  template <typename M>
  int Liste<M>::show(bool int_exempl)
  {
	 bool is_show=false;//ob uberhaupt etwas angezeigt wird
 	 if(this->first==NULL)
 	 {
 		// cout<<"Kein Element vorhanden für show()"<<endl;
 		 return -1;
 	 }
 	 Element<M>* tempcur=this->current;

 	 this->current=this->first;
 	 do
 	 {
 		 if(this->current->getData()->show(int_exempl))
 		 {
 			 is_show=true;
 		 }

 		 goNext();
 	 }while(this->current!=this->first);//wenn eine Runde abgeschlossen
 	 this->current=tempcur;
 	 if(!is_show)
 	 {
 		 return -1;
 	 }
 	 return 0;
  }
  template <typename M>
  int Liste<M>::save(Dateiarbeit<M>& datarb)
  {

 	 if(this->first!=NULL)
 	 {
 		 this->current=this->first;
 		 do
 		 {
 			datarb.sichern(this->current->getData());
 			 goNext();//wenn nur ein Element geht er zu sich selbst und bricht dann ab
 		 }while(this->current != this->first);
 	 }
 	 return 0;
  }

  template <typename M>
  M* Liste<M>::search(int such)
  {
 	 this->current=this->first;
 	 if(this->current==NULL)
 	 {
 		 return NULL;
 	 }
 	 do
 	 {
 		 if(this->current->getData()->vergleich(such)) //nimm das angehangene Datenobjekt und nutze die eigene vergleichsfunktion
 		 {
 			 return this->current->getData();
 		 }
 		 this->current=this->current->getNext();
 	 }while(this->current!=this->first);
 	 return NULL;
  }
  template <typename M>
  int Liste<M>::load(String vsd)
  {

 		return 0;
  }
 template <typename M>
  Liste<M>::~Liste()
  {
 	 if(this->first!=NULL)
 	 {
 		 this->current=this->first;
 		 do
 		 {
 			 remove();
 		 }while(this->first !=NULL);
 	 }


  }
#endif
