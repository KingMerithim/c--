/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

 #include "person.h"
 #include "string.h"
 #include <iostream>
 #include <string.h>
#include <cstdio>
#include <cstdlib>
 
#define PATH_BENUTZER_BUCH "../benutzer/%i.buch"
#define PATH_BENUTZER_VIDEO "../benutzer/%i.video"
#define PATH_PERSON_LISTE "../listen/personenliste.dat"
 using namespace std;
 
 
 /*String VorZuName;
String Anschrift;
Liste<Video> ausgelieheneVideo;
Liste<Buch> ausgelieheneBuch;
  * 
  * 
  */
 Person::Person()
 {
	 	this->Nachname="Unknown";
	 	this->Vorname="Unknown";
	 	this->benutzernummer=0;
 }
Person::Person(int nummer,String Vorname,String Nachname)
{
	this->benutzernummer=nummer;
	this->Vorname=Vorname;
	this->Nachname=Nachname;
}

void Person::leihenBuch(Buch* Leih)
{
	FILE * pFile=NULL;
	char vbuf[128];
	//char input[1000];
	sprintf(vbuf,PATH_BENUTZER_BUCH,this->benutzernummer);


	pFile=fopen(vbuf,"at");

	fprintf(pFile,"%i;%s;%s;\n",
			Leih->getMediumNummer(),
			Leih->getMediumName().getInhalt(),
			Leih->getMediumAutor().getInhalt()
			);
	fclose(pFile);
}
void Person::leihenVideo(Video* Leih)
{
	FILE * pFile=NULL;
	char vbuf[128];
	//char input[1000];
	sprintf(vbuf,PATH_BENUTZER_VIDEO,this->benutzernummer);



	pFile=fopen(vbuf,"at");

	fprintf(pFile,"%i;%s;%s;\n",
			Leih->getMediumNummer(),
			Leih->getMediumName().getInhalt(),
			Leih->getMediumAutor().getInhalt()
			);
	fclose(pFile);
}
int Person::zurueckgebenBuch(void)// zurück ist referenz aus dergleichen liste
{
		FILE * pFile=NULL;
		Buch* temp;
		Element<Buch>* e_temp,*e_first;
		Liste<Buch> ausgel_buch;
		char vbuf[1280], *split,*titel,*autor;
		int nummer=0;
		sprintf(vbuf,PATH_BENUTZER_BUCH,this->benutzernummer);
		
		if(!exist_file(vbuf))
		{
			cout<<"Noch kein Buch ausgeliehen"<<endl;
			return -1;
		}
		pFile=fopen(vbuf,"rt");
		while(fgets(vbuf, 1279, pFile)!=NULL)
		{
			  split = strtok(vbuf,";");
			  nummer=atoi(split);
			  split = strtok (NULL, ";");
			  titel=split;
			  split = strtok (NULL, ";");
			  autor=split;
			  temp=new Buch(nummer,titel,autor);
			  ausgel_buch.add(temp);
		}
		fclose(pFile);
		if(ausgel_buch.show()==-1)
		{
			cout<<"Noch kein Buch ausgeliehen"<<endl;
			return -1;
		}
		cout<<"Bitte Nummer eingeben was wiedergegeben wird"<<endl;
		cin.getline(vbuf,128);
		if(strlen(vbuf)==0)
		{
			cout<<"Sie haben nichts eingegeben"<<endl;
			return -1;
		}
		nummer=atoi(vbuf);
		temp=ausgel_buch.search(nummer);
		if(temp==NULL)
		{
			cout<<"Unter dieser Nummer konnte kein Medium gefunden werden"<<endl;
			return -1;
		}
		//cout<<"vor gelöscht"<<endl;
		ausgel_buch.show();
		ausgel_buch.remove(temp);
		//cout<<"nach gelöscht"<<endl;
		ausgel_buch.show();
		ausgel_buch.setCurrentFirst();
		e_temp=e_first=ausgel_buch.getCurrent();
		sprintf(vbuf,PATH_BENUTZER_BUCH,this->benutzernummer);
		pFile=fopen(vbuf,"wt");
		fclose(pFile);
		if(e_first!=NULL)
		{
			ausgel_buch.goNext();
			e_temp=ausgel_buch.getCurrent();
			while(e_temp!=e_first)
			{
				//cout<<"durchlauf"<<endl;
				e_temp=ausgel_buch.getCurrent();
				this->leihenBuch(e_temp->getData());
				ausgel_buch.goNext();
			}
			this->leihenBuch(e_temp->getData());
			//buchliste für ausgeliehende medien erzeugt
			//anzeigen und auswählen lassen
			//aktualisieren in medienliste und wieder in datei schreiben
		}
	return nummer; //die buchnummer
}
int Person::zurueckgebenVideo(void)
{
	FILE * pFile=NULL;
		Video* temp;
		Element<Video>* e_temp,*e_first;
		Liste<Video> ausgel_video;
		char vbuf[1280], *split,*titel,*autor;
		int nummer=0;
		sprintf(vbuf,PATH_BENUTZER_VIDEO,this->benutzernummer);
		if(!exist_file(vbuf))
		{
			cout<<"Noch kein Video ausgeliehen"<<endl;
			return -1;
		}
		pFile=fopen(vbuf,"rt");
		while(fgets(vbuf, 1279, pFile)!=NULL)
		{
			  split = strtok(vbuf,";");
			  nummer=atoi(split);
			  split = strtok (NULL, ";");
			  titel=split;
			  split = strtok (NULL, ";");
			  autor=split;
			  temp=new Video(nummer,titel,autor);
			  ausgel_video.add(temp);
		}
		fclose(pFile);
		if(ausgel_video.show()==-1)
		{
			cout<<"Noch kein Video ausgeliehen"<<endl;
			return -1;
		}
		cout<<"Bitte Nummer eingeben was wiedergegeben wird"<<endl;
		cin.getline(vbuf,128);
		if(strlen(vbuf)==0)
		{
			cout<<"Sie haben nichts eingegeben"<<endl;
			return -1;
		}
		nummer=atoi(vbuf);
		temp=ausgel_video.search(nummer);
		if(temp==NULL)
		{
			cout<<"Unter dieser Nummer konnte kein Medium gefunden werden"<<endl;
			return -1;
		}
		ausgel_video.remove(temp);
		ausgel_video.setCurrentFirst();
		e_temp=e_first=ausgel_video.getCurrent();
		sprintf(vbuf,PATH_BENUTZER_VIDEO,this->benutzernummer);
		pFile=fopen(vbuf,"wt");
		fclose(pFile);
		if(e_first!=NULL)
		{
			ausgel_video.goNext();
			e_temp=ausgel_video.getCurrent();
			while(e_temp!=e_first)
			{
			//cout<<"durchlauf"<<endl;
				e_temp=ausgel_video.getCurrent();
				this->leihenVideo(e_temp->getData());
				ausgel_video.goNext();
			}
			this->leihenVideo(e_temp->getData());
			//buchliste für ausgeliehende medien erzeugt
			//anzeigen und auswählen lassen
			//aktualisieren in medienliste und wieder in datei schreiben
		}
	return nummer; //die buchnummer
}

void  Person::showAusgeliehen(void)
{
	FILE * pFile=NULL;
	char vbuf[128];
	char input[1000];
	sprintf(vbuf,PATH_BENUTZER_BUCH,this->benutzernummer);

	if(!exist_file(vbuf))
	{
		cout<<"Keine Buecher ausgeliehen"<<endl;
		return;
	}

	pFile=fopen(vbuf,"rt");
	while(fgets (input , 1000 , pFile) != NULL)
	{
		cout<<input<<endl;
	}
	fclose(pFile);



	sprintf(vbuf,PATH_BENUTZER_VIDEO,this->benutzernummer);
	if(!exist_file(vbuf))
	{
		cout<<"Keine Videos ausgeliehen"<<endl;
		return;
	}

	pFile=fopen(vbuf,"rt");
	while(fgets (input , 1000 , pFile) != NULL)
	{
		cout<<input<<endl;
	}
	fclose(pFile);
}
bool Person::exist_file(char * medium)
{
		FILE * pFile=NULL;

		pFile=fopen(medium,"rt");
		//Test ob datei exisitert sonst angelegt und wieder geschlossen
		if(pFile!=NULL)
		{
			//datei exisitert
			fclose(pFile);
			return true;
		}
		else
		{
			return false;

		}
}
bool Person::vergl(Person* rhs)
{
	return strlen(this->getNachname().getInhalt())<strlen(rhs->getNachname().getInhalt());
}
bool  Person::show(bool int_ben)
{
  cout<<endl<<"Benutzernummer: "<<this->benutzernummer<<endl;
  cout<<"Vorname: "<<this->Vorname<<endl;
  cout<<"Nachname: "<<this->Nachname<<endl;
  return true;
}

bool Person::vergleich(int nummer)
{
	return this->benutzernummer==nummer;
}
int Person::getBenNr(void)
{
	return this->benutzernummer;
}
String Person::getVorname(void)
{
	return this->Vorname;
}
String Person::getNachname(void)
{
	return this->Nachname;
}
long int Person::laden(long int curpos)
{


			FILE* pFile=NULL;
			long int endpos;
			char* ctemp;
			//short type;
			int gr_inhalt;
			//long nummer;

			pFile=fopen(PATH_PERSON_LISTE,"rb");
			if(pFile==NULL)
			{
				cerr<<"Personenliste konnte nicht geladen werden"<<endl;
				return -1;
			}

			fseek(pFile,curpos,SEEK_SET);

			//mediumname auslesen
			fread(&(this->benutzernummer),sizeof(int),1,pFile);
			//name auslesen

			fread(&gr_inhalt,sizeof(int),1,pFile);
			ctemp=new char[gr_inhalt+1];
			fread(ctemp,gr_inhalt,1,pFile);
			ctemp[gr_inhalt]=0;
			this->Nachname=ctemp;
			delete[] ctemp;
			//cout<<this->MediumName<<endl;
			//autor auslesen
			fread(&gr_inhalt,sizeof(int),1,pFile);
			ctemp=new char[gr_inhalt+1];
			fread(ctemp,gr_inhalt,1,pFile);
			ctemp[gr_inhalt]=0;
			this->Vorname=ctemp;
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
long int Person::speichern(long int curpos)
{
	FILE* pFile=NULL;
	//long int endpos;
	char * ctemp;
	//short type;
	int gr_inhalt;
	//long nummer;
	if(curpos==0)
	{
		pFile=fopen(PATH_PERSON_LISTE,"wb");
	}
	else
	{
		pFile=fopen(PATH_PERSON_LISTE,"a+b");
	}

	if (pFile==NULL)
	{
		cerr<<"konnte Datei nicht zum speichern nutzen"<<endl;
		return -1;
	}
	//Nummer gespeichert
	fwrite(&this->benutzernummer,sizeof(int),1,pFile );

	//Name gespeichert
	gr_inhalt=strlen(this->Nachname.getInhalt());
	ctemp=new char[gr_inhalt+1];
	strcpy(ctemp,this->Nachname.getInhalt());
	
	fwrite(&gr_inhalt,sizeof(int),1,pFile );
	fwrite(ctemp,gr_inhalt,1,pFile);
	
	//cout<<"Nachname: "<<this->Nachname<<" länge: "<<gr_inhalt<<endl;
	delete[] ctemp;
	//Vorname gespeichert
	gr_inhalt=strlen(this->Vorname.getInhalt());
	ctemp=new char[gr_inhalt+1];
	strcpy(ctemp,this->Vorname.getInhalt());

	fwrite(&gr_inhalt,sizeof(int),1,pFile );
	fwrite(ctemp,gr_inhalt,1,pFile);
	//cout<<"Vorname: "<<this->Vorname<<" länge: "<<gr_inhalt<<endl;
	delete[] ctemp;

	curpos=ftell(pFile);
	fclose (pFile);
	return curpos;
}

Person::~Person()
{


}
