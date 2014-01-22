/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#include "string.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "video.h"

#define PATH_VIDEO_LISTE "../listen/videoliste.dat"
/*
 * short MediumType;
	String MediumName;
	String MediumAutor;
 * 
 */
using namespace std;

Video::Video():Medium()
{
	
	//cout<<"VideoKonstruktor"<<endl;
	this->Exemplare=1;
	this->MediumName="Unknown";
	this->MediumRegisseur="Unknown";
	this->MediumNummer=0;
}
Video::Video(int Mednr, String MedNam, String MedReg):Medium()
{
	
	//cout<<"VideoKonstruktor_2"<<endl;
	this->Exemplare=1;
	
	////cout<<"Mednam Laenge"<<MedNam.getLaenge()<<endl;
	this->MediumRegisseur=MedReg;
	this->MediumName=MedNam;
	this->MediumNummer=Mednr;
}
Video::Video(const Video& rhs)
{
	 this->MediumRegisseur = rhs.MediumRegisseur;
	 this->MediumName = rhs.MediumName;
	 this->Exemplare= rhs.Exemplare;
	 this->MediumNummer=rhs.MediumNummer;
}
short Video::getExemplare(void)
{
	return this->Exemplare;
}
void Video::Exemplar_ausleihen(void)
{
	this->Exemplare=0;


}
void Video::Exemplar_zurueckgeben(void)
{

	this->Exemplare=1;

}
int Video::getMediumNummer()
{
	return this->MediumNummer;
}
String Video::getMediumName(void)
{
	return this->MediumName;
}
String Video::getMediumAutor(void)
{
	return this->MediumRegisseur;
}
bool Video::vergleich(int nummer)
{
	return this->MediumNummer==nummer;

}
bool Video::vergl(Video* rhs)
{
	return strlen(this->getMediumName().getInhalt())<strlen(rhs->getMediumName().getInhalt());
}

bool Video::show(bool int_exempl)
{
	if(!int_exempl || this->getExemplare())
	{
		cout<<"Videonummer: "<<this->MediumNummer<<" Videoname: "<<this->MediumName<<" | Regisseur: "<<this->MediumRegisseur<<endl;
		return true;
	}
	return false;
}

Video& Video::operator= (const Video& rhs)
{
	if(this != &rhs)
	{
		this->Exemplare=rhs.Exemplare;
		this->MediumName=rhs.MediumName;
		this->MediumRegisseur=rhs.MediumRegisseur;
		this->MediumNummer=rhs.MediumNummer;
    }
	return *this; //Referenz auf das Objekt selbst zurückgeben
}
long int Video::laden(long int curpos)
{


			FILE* pFile=NULL;
			long int endpos;
			char* ctemp;
			//short type;
			int gr_inhalt;
			//long nummer;

			pFile=fopen(PATH_VIDEO_LISTE,"rb");
			if(pFile==NULL)
			{
				cerr<<"VideoListe konnte nicht geladen werden"<<endl;
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
			delete[] ctemp;
			//cout<<this->MediumName<<endl;
			//autor auslesen
			fread(&gr_inhalt,sizeof(int),1,pFile);
			ctemp=new char[gr_inhalt+1];
			fread(ctemp,gr_inhalt,1,pFile);
			ctemp[gr_inhalt]=0;
			this->MediumRegisseur=ctemp;
			delete[] ctemp;
			//cout<<this->MediumAutor<<endl;

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
long int Video::speichern(long int curpos)
{
	FILE* pFile=NULL;
	//long int endpos;
	char * ctemp;
	//short type;
	int gr_inhalt;
	//long nummer;
	if(curpos==0)
	{
		pFile=fopen(PATH_VIDEO_LISTE,"wb");
	}
	else
	{
		pFile=fopen(PATH_VIDEO_LISTE,"a+b");
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
	//cout<<"videoname: "<<this->MediumName<<" länge: "<<gr_inhalt<<endl;
	delete[] ctemp;
	//Autor gespeichert
	gr_inhalt=strlen(this->MediumRegisseur.getInhalt());
	ctemp=new char[gr_inhalt+1];
	strcpy(ctemp,this->MediumRegisseur.getInhalt());

	fwrite(&gr_inhalt,sizeof(int),1,pFile );
	fwrite(ctemp,gr_inhalt,1,pFile);
	//cout<<"video: "<<this->MediumRegisseur<<" länge: "<<gr_inhalt<<endl;
	delete[] ctemp;

	curpos=ftell(pFile);
	fclose (pFile);
	return curpos;
}
Video::~Video()
{
	//cout<<"VideoDekonstruktor"<<endl;
}
