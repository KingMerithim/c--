/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#ifndef _DATEIARBEIT_
#define _DATEIARBEIT_
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <typeinfo>

#include "buch.h"
#include "video.h"
#include "person.h"
#include "dateiarbeit.h"
#include "string.h"

using namespace std;
/*
dateiarbeit wie folgt:
klasse bekommt datensatz und zahl wie viele bytes das sind
innerhalb des datensatzes stehen die einzelnden daten udn davor jeweils wie lang ein datum ist
*/
template<class S>
class Dateiarbeit
{
public:
	Dateiarbeit();
	char* getSpeicherort(void);
	void setSpeicherort(const char* speich);
	int sichern(S* med);

	S laden(void)
	{
		if(this->eof)
		{
			cout<<"Ende der Datei erreicht!"<<endl;
		}

		FILE* pFile=NULL;
		long int endpos;

		short type;
		int gr_inhalt;
		long nummer;

		pFile=fopen(this->dateiname,"r+b");
		if(pFile==NULL)
		{
			cout<<"Datei existiert nicht"<<endl;
		}

		fseek(pFile,this->curpos,SEEK_SET);
		fread(&nummer,sizeof(long),1,pFile);
		//exemplare auslesen
		fread(&type,sizeof(short),1,pFile);
		//name auslesen
		fread(&gr_inhalt,sizeof(int),1,pFile);
		//name=new char(gr_inhalt+0);
		char* name=new char[gr_inhalt];
		fread(name,gr_inhalt,1,pFile);
		//cout<<name<<strlen(name)<<endl;
		//autor auslesen
		fread(&gr_inhalt,sizeof(int),1,pFile);
		char* autor=new char[gr_inhalt];
		fread(autor,gr_inhalt,1,pFile);
		//cout<<autor<<strlen(autor)<<endl;

		S hans(nummer,name,autor);

		//herausfinden wo er gerade ist
		this->curpos=ftell(pFile);
		//gucken wo ende ist
		fseek(pFile,0,SEEK_END);
		endpos=ftell(pFile);
		fseek(pFile,0,this->curpos);
		//überprüfunen ob er am ende angekommen ist
		if(this->curpos>=endpos)
		{
			this->eof=true;
			this->curpos=0;
		}

		fclose(pFile);
		return hans;

	}
	bool isEOF(void);
	void setEOF(bool nev);
	bool isBeschrieben(void);
	void setBeschrieben(bool nev);
	int getElemente(void)
	{
		int anz=0,gr_inhalt=0;
		long int endpos;
		char* buf=new char[132];
		FILE* pFile;

		pFile=fopen(this->dateiname,"r+b");
		this->curpos=0;

		if(pFile==NULL)
		{
			cout<<"Datei konnte nicht geöffnet werden <<endl";
			return 0;
		}

		do
		{
		//1 element

		fread(buf,sizeof(long),1,pFile);
		fread(buf,sizeof(short),1,pFile);
		fread(&gr_inhalt,sizeof(int),1,pFile);
		fread(buf,gr_inhalt,1,pFile);
		fread(&gr_inhalt,sizeof(int),1,pFile);
		fread(buf,gr_inhalt,1,pFile);
		////////
		anz++;

		//herausfinden wo er gerade ist
		this->curpos=ftell(pFile);
		//gucken wo ende ist
		fseek(pFile,0,SEEK_END);
		endpos=ftell(pFile);
		fseek(pFile,this->curpos,SEEK_SET);

		}while(this->curpos<endpos);

		//rücksetzen der werte
		this->curpos=0;
		fclose(pFile);
		return anz;
	}
	bool isDateiexisting();
	~Dateiarbeit();
	
private:
	char* dateiname;
	bool beschrieben;
	bool eof;
	long int curpos;
	char* getDruckbare(char* nonsense);
};

template<typename S>
Dateiarbeit<S>::Dateiarbeit()
{
	this->curpos=0;
	this->eof=false;
	this->beschrieben=false;
	this->dateiname=new char[strlen("test.dat")+1];
	strcpy(this->dateiname,"test.dat");
}
template<typename S>
void Dateiarbeit<S>::setSpeicherort(const char* speich)
{
	delete[] this->dateiname;
	this->dateiname=new char[strlen(speich)+1];
	strcpy(this->dateiname,speich);
}
template<typename S>
char* Dateiarbeit<S>::getSpeicherort(void)
{
	return this->dateiname;
}
template<typename S>
int Dateiarbeit<S>::sichern(S* med)
{
		FILE * pFile;
		char * name,*autor;
		short type;
		int gr_inhalt;
		long nummer;
		if(!this->beschrieben)
		{
			pFile = fopen (this->dateiname,"wb");
		}
		else
		{
			pFile = fopen (this->dateiname,"ab");
		}
	  if (pFile!=NULL)
	  {
		 //gespeichert wird Typ-->Laenge Name -->Name -->Laenge Autor --> Autor
		  //nummer gespeichert
		  nummer=med->getMediumNummer();
		  fwrite(&nummer,sizeof(long),1,pFile );
		 //Exemplare gespeichert
		  type=med->getExemplare();
		 fwrite(&type,sizeof(short),1,pFile );
		 //Name gespeichert
		 gr_inhalt=strlen(med->getMediumName().getInhalt());
		 name=new char[gr_inhalt+1];
		 strcpy(name,med->getMediumName().getInhalt());
		 fwrite(&gr_inhalt,sizeof(int),1,pFile );
	     fwrite(name,gr_inhalt,1,pFile );
		 //Autor gespeichert
		 gr_inhalt=strlen(med->getMediumAutor().getInhalt());
		 autor=new char[gr_inhalt+1];
		 strcpy(autor,med->getMediumAutor().getInhalt());
		 fwrite(&gr_inhalt,sizeof(int),1,pFile );
	     fwrite(autor,gr_inhalt,1,pFile );

		// cout<<"MEdName: "<<*name<<" | strlen: "<<strlen(name)<<endl;


	    this->beschrieben=true;
	    fclose (pFile);
	  };
	 return 0;
	}
template<typename S>
bool Dateiarbeit<S>::isDateiexisting()
{
	FILE * pFile;
	pFile = fopen (this->dateiname,"rb");

	  if (pFile!=NULL)
	  {
		  fclose(pFile);
		  return true;
	  }
	  return false;
}
template<typename S>
bool Dateiarbeit<S>::isEOF(void)
{
	return this->eof;
}
template<typename S>
char* Dateiarbeit<S>::getDruckbare(char* nonsense)
{
	char * bla=new char(strlen(nonsense)+1);
	bool firsttime=true;
	//cout<<strlen(bla)<<endl;
    unsigned int d;
    for (d=0; d<strlen(nonsense); d++)
    {
        if (isprint(nonsense[d]))
        {
			char hust=nonsense[d];
			//cout<<hust<<endl;
			if(firsttime)
			{
			strcpy(bla,&hust);
			}
			else
			{
			strcat(bla,&hust);
			}
			firsttime=false;
		}
		strcat(bla,"\0");

	}
return bla;
}

template<typename S>
void Dateiarbeit<S>::setEOF(bool nev)
{
	this->eof=nev;
}
template<typename S>
bool Dateiarbeit<S>::isBeschrieben(void)
{
	return this->beschrieben;
}
template<typename S>
void Dateiarbeit<S>::setBeschrieben(bool nev)
{
	this->beschrieben=nev;
}
template<typename S>
Dateiarbeit<S>::~Dateiarbeit()
{
	delete[] this->dateiname;
}

#endif
