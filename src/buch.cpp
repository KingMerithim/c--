/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#include "string.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "buch.h"

#define PATH_BUCH_LISTE "../listen/buchliste.dat"
/*
 * short MediumType;
	String MediumName;
	String MediumAutor;
 * 
 */
using namespace std;

Buch::Buch():Medium()
{
	
	//cout<<"BuchKonstruktor"<<endl;
	this->Exemplare=1;
	this->MediumName="Unknown";
	this->MediumAutor="Unknown";
	this->MediumNummer=0;
}
Buch::Buch(int Mednr,String MedNam, String MedAut):Medium()
{
	
	//cout<<"BuchKonstruktor_2"<<endl;
	this->Exemplare=1;
	
	//cout<<"Mednam Laenge"<<MedNam.getLaenge()<<endl;
	this->MediumAutor=MedAut;
	
	this->MediumName=MedNam;
	this->MediumNummer=Mednr;
}
Buch::Buch(const Buch& rhs)
{
	 this->MediumAutor = rhs.MediumAutor;
	 this->MediumName = rhs.MediumName;
	 this->Exemplare= rhs.Exemplare;
	 this->MediumNummer=rhs.MediumNummer;
}
short Buch::getExemplare(void)
{
	return this->Exemplare;
}
void Buch::Exemplar_ausleihen(void)
{
	this->Exemplare=0;
}
void Buch::Exemplar_zurueckgeben(void)
{

			this->Exemplare=1;

}
int Buch::getMediumNummer()
{
	return this->MediumNummer;
}
String Buch::getMediumName(void)
{
	return this->MediumName;
}
String Buch::getMediumAutor(void)
{
	return this->MediumAutor;
}
bool Buch::vergleich(int nummer)
{
	return this->MediumNummer==nummer;

}
Buch& Buch::operator= (const Buch& rhs)
{
	if(this != &rhs)
	{
		this->Exemplare=rhs.Exemplare;
		this->MediumName=rhs.MediumName;
		this->MediumAutor=rhs.MediumAutor;
		this->MediumNummer=rhs.MediumNummer;
    }
	return *this; //Referenz auf das Objekt selbst zurückgeben
}
bool Buch::vergl(Buch* rhs)
{
	return strlen(this->getMediumName().getInhalt())<strlen(rhs->getMediumName().getInhalt());
}
bool Buch::show(bool int_exempl)
{
	if(!int_exempl  || this->getExemplare())
	{
		cout<<"Buchnummer: "<<this->MediumNummer<<"Buchtitel: "<<this->MediumName<<" | Autor: "<<this->MediumAutor<<endl;
		return true;
	}
	return false;
}
long int Buch::laden(long int curpos)
{


			FILE* pFile=NULL;
			long int endpos;
			char* ctemp;
			//short type;
			int gr_inhalt;
			//long nummer;

			pFile=fopen(PATH_BUCH_LISTE,"rb");
			if(pFile==NULL)
			{
				cerr<<"Buchliste konnte nicht geladen werden"<<endl;
				
				return -1;
			}

			fseek(pFile,curpos,SEEK_SET);

			//mediumname auslesen
			fread(&(this->MediumNummer),sizeof(int),1,pFile);
			//exemplare auslesen
			fread(&(this->Exemplare),sizeof(short),1,pFile);
			//name auslesen

			fread(&gr_inhalt,sizeof(int),1,pFile);
			ctemp=new char[gr_inhalt+1];
			fread(ctemp,gr_inhalt,1,pFile);
			ctemp[gr_inhalt]=0;
			this->MediumName=ctemp;
			delete ctemp;
			//autor auslesen
			fread(&gr_inhalt,sizeof(int),1,pFile);
			ctemp=new char[gr_inhalt+1];
			fread(ctemp,gr_inhalt,1,pFile);
			ctemp[gr_inhalt]=0;
			this->MediumAutor=ctemp;
			delete ctemp;

			//herausfinden wo er gerade ist
			curpos=ftell(pFile);
			//gucken wo ende ist
			fseek(pFile,0,SEEK_END);
			endpos=ftell(pFile);
			fseek(pFile,0,curpos);
			//überprüfunen ob er am ende angekommen ist
			if(curpos>=endpos)
			{
				return 0;
			}

			fclose(pFile);
	return curpos;
}
long int Buch::speichern(long int curpos)
{
	FILE* pFile=NULL;
	//long int endpos;
	char * ctemp;
	//short type;
	int gr_inhalt;
	//long nummer;
	if(curpos==0)
	{
		pFile=fopen(PATH_BUCH_LISTE,"wb");
	}
	else
	{
		pFile=fopen(PATH_BUCH_LISTE,"a+b");
	}

	if (pFile==NULL)
	{
		cerr<<"konnte Datei nicht zum speichern nutzen"<<endl;
		return -1;
	}
	//Nummer gespeichert
	fwrite(&this->MediumNummer,sizeof(int),1,pFile );

	//Exemplare gespeichert
	fwrite(&this->Exemplare,sizeof(short),1,pFile );

	//Name gespeichert
	gr_inhalt=strlen(this->MediumName.getInhalt());
	ctemp=new char[gr_inhalt+1];
	strcpy(ctemp,this->MediumName.getInhalt());

	fwrite(&gr_inhalt,sizeof(int),1,pFile );
	fwrite(ctemp,gr_inhalt,1,pFile);
	delete[] ctemp;
	//Autor gespeichert
	gr_inhalt=strlen(this->MediumAutor.getInhalt());
	ctemp=new char[gr_inhalt+1];
	strcpy(ctemp,this->MediumAutor.getInhalt());

	fwrite(&gr_inhalt,sizeof(int),1,pFile );
	fwrite(ctemp,gr_inhalt,1,pFile);
	//cout<<"Buchautor: "<<this->MediumAutor<<" länge: "<<gr_inhalt<<endl;
	delete[] ctemp;

	curpos=ftell(pFile);
	fclose (pFile);
	return curpos;
}
Buch::~Buch()
{
	//cout<<"BuchDekonstruktor"<<endl;
}
