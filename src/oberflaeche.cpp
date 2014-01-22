/*
 * Name: Martin Tzschoppe
 * Makrikelnr: 34339
 * Studiengang: 12/041/61
 * 
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "oberflaeche.h"
#include "buch.h"
#include "video.h"
#include "string.h"
#include "liste.h"
#include "element.h"
#include "person.h"

#ifdef __unix__
#define clearscreen() system( "clear" )
#elif __WIN32__
#define clearscreen() system("cls")
#endif

#ifdef __unix__
#define pause() printf("Beliebige Taste zum Fortfahren drücken"); getchar()
#elif __WIN32__
#define pause() system("PAUSE")
#endif


Oberflaeche::Oberflaeche()
{
	// Bei der Initalisierung werden ggf gespeicherte medien geladen

	laden();
	this->akt_buchnr=getzahl(1);
	this->akt_videonr=getzahl(2);
	this->akt_kundnr=getzahl(3);


}
void Oberflaeche::speichern()
{
	Buch* btemp;
	Video* vtemp;
	Person* ptemp;
	Element<Buch>* bfirst,*bcurrent;
	Element<Video>* vfirst,*vcurrent;
	Element<Person>* pfirst,*pcurrent;
	long int filepos=0;

	buchliste.setCurrentFirst();
	bcurrent=bfirst=buchliste.getCurrent();
	if(bcurrent!=NULL)
	{	//Element in Liste
		do
		{	//speichern seiner eigenen daten;
			btemp=bcurrent->getData();
			filepos=btemp->speichern(filepos);//if filepos==0 => fopen(...,wb) else fopen(..,ab);
			if(filepos==-1)
			{
				break;
			}
			buchliste.goNext();
			bcurrent=buchliste.getCurrent();
		}while(bcurrent!=bfirst);
	}
	filepos=0;
	videoliste.setCurrentFirst();
	vcurrent=vfirst=videoliste.getCurrent();
	if(vcurrent!=NULL)
	{	//Element in Liste
		do
		{	//speichern seiner eigenen daten;
			vtemp=vcurrent->getData();
			filepos=vtemp->speichern(filepos);//if filepos==0 => fopen(...,wb) else fopen(..,ab);
			if(filepos==-1)
			{
				break;
			}
			videoliste.goNext();
			vcurrent=videoliste.getCurrent();
		}while(vcurrent!=vfirst);
	}
	filepos=0;
	personenliste.setCurrentFirst();
	pcurrent=pfirst=personenliste.getCurrent();
	if(pcurrent!=NULL)
	{	//Element in Liste
		do
		{	//speichern seiner eigenen daten;
			ptemp=pcurrent->getData();
			filepos=ptemp->speichern(filepos);//if filepos==0 => fopen(...,wb) else fopen(..,ab);
			if(filepos==-1)
			{
				break;
			}
			personenliste.goNext();
			pcurrent=personenliste.getCurrent();
		}while(pcurrent!=pfirst);
	}
}
void Oberflaeche::laden()
{
		Buch* btemp;
		Video* vtemp;
		Person* ptemp;
		long int filepos=0;

		do
		{
			btemp=new Buch();//anfang buch leer, wird dann gefüllt mit daten
			filepos=btemp->laden(filepos);//bei ende -1
			if(filepos==-1)
			{
				break;
			}
			buchliste.add(btemp);
		}while(filepos!=0);
		filepos=0;
		do
		{
			vtemp=new Video();//anfang buch leer, wird dann gefüllt mit daten
			filepos=vtemp->laden(filepos);//bei ende -1
			if(filepos==-1)
			{
				break;
			}
			videoliste.add(vtemp);
		}while(filepos!=0);
		filepos=0;
		do
		{
			ptemp=new Person();//anfang buch leer, wird dann gefüllt mit daten
			filepos=ptemp->laden(filepos);//bei ende -1
			if(filepos==-1)
			{
				break;
			}
			personenliste.add(ptemp);
		}while(filepos!=0);

}
void Oberflaeche::menue()
{
// funktion um die trolleingaben des users mit haufen leerzeichen zu tilgen HINZUFÜGEN
	char menue[128];
	int eingabe1=0;
	do
	{
	clearscreen();
	cout<<"(1) Benutzer anlegen"<<endl;
	cout<<"(2) Benutzer loeschen"<<endl;
	cout<<"(3) Benutzer suchen"<<endl;
	cout<<"(4) Medien hinzufuegen"<<endl;
	cout<<"(5) Medien anzeigen"<<endl;

	cout<<"(6) Medien loeschen"<<endl;
	cout<<"(7) Medien ausleihen"<<endl;
	cout<<"(8) Medien zurueckgeben"<<endl;
	cout<<"(0) Beenden"<<endl;

    cout <<"Eingabe: ";
    cin.getline(menue, 128);
    eingabe1=atoi(menue);

/*verarbeitung der eingabe in switch-anweisung*/
    switch(eingabe1)
    {
      case 1: benutzer_anlegen()         ;pause(); break;
      case 2: benutzer_loeschen()          ;pause(); break;
      case 3: benutzer_suchen()          ;pause(); break;
      case 4: medien_hinzufuegen()          ;pause(); break;
      case 5: medien_anzeigen()  ;pause();  break;
      case 6: medien_loeschen()  ;pause();  break;
      case 7: medien_ausleihen()  ;pause();  break;
      case 8: medien_zurueckgeben();pause(); break;
      case 0: cout<<endl<<"Auf Wiedersehen"<<endl;pause(); break;

      default: cout<<"falsche eingabe" <<endl; break;
    }
  }
  while((eingabe1<9)&&(eingabe1>=1));
}
void Oberflaeche::benutzer_anlegen()
{
		 char buf1[128];
		 char buf2[128];
		 clearscreen();

		 cout<<"Vorname"<<endl;
		 cin.getline(buf1,127);
		 if(strlen(buf1)==0)
		{
			cout<<"Sie haben nichts eingegeben"<<endl;
			return;
		}
		 cout<<"Nachname"<<endl;
		 cin.getline(buf2,127);
		 if(strlen(buf2)==0)
		{
			cout<<"Sie haben nichts eingegeben"<<endl;
			return;
		}
		 this->akt_kundnr++;
		 Person* p=new Person(this->akt_kundnr,buf1,buf2);
		 p->show();
		 personenliste.add(p);
}
 void Oberflaeche::benutzer_loeschen()
 {
	 clearscreen();
	 char vbuf[128];
	 	 int zahl=0;
	 	 clearscreen();
	 	 personenliste.show();
	 	 cout<<"Bitte eine der Zahlen eingeben"<<endl;
	 	 cin.getline(vbuf,127);
	 	if(strlen(vbuf)==0)
		{
			cout<<"Sie haben nichts eingegeben"<<endl;
			return;
		}
	 	 zahl=atoi(vbuf);
	 	Person* temp= personenliste.search(zahl);
	 	if(temp!=NULL)
	 	{
	 		temp->show();
	 		 personenliste.remove(temp);
	 	}

 }
 Person* Oberflaeche::benutzer_suchen()
  {
	 char vbuf[128];
	 int zahl=0;
	 clearscreen();
	 personenliste.show();
	 cout<<"Bitte eine der Zahlen eingeben"<<endl;
	 cin.getline(vbuf,127);
	 if(strlen(vbuf)==0)
	{
		cout<<"Sie haben nichts eingegeben"<<endl;
		return NULL;
	}
	 zahl=atoi(vbuf);
	Person* temp= personenliste.search(zahl);
	if(temp!=NULL)
	{
		temp->show();
	}
	return temp;
  }
 void Oberflaeche::medien_hinzufuegen()
 {
	 char selection[128];
	 char buf1[128];
	 char buf2[128];
	 clearscreen();
	 cout<<"Medien hinzufuegen"<<endl;
	 cout<<"(1) Buch"<<endl;
	 cout<<"(2) Video"<<endl;
	 cout<<"(0) zurueck"<<endl;
	 cin.getline(selection,127);
	 if(strlen(selection)==0)
	{
		cout<<"Sie haben nichts eingegeben"<<endl;
		return;
	}
	 cout<<"Titel"<<endl;
	 cin.getline(buf1,127);
	 if(strlen(buf1)==0)
	{
		cout<<"Sie haben nichts eingegeben"<<endl;
		return;
	}
	 cout<<"Autor"<<endl;
	 cin.getline(buf2,127);
	 if(strlen(buf2)==0)
	{
		cout<<"Sie haben nichts eingegeben"<<endl;
		return;
	}
	 if(selection[0]=='1')
	 {
		 this->akt_buchnr++;
		 Buch* b=new Buch(this->akt_buchnr,buf1,buf2);
		 b->show();
		 buchliste.add(b);
	 }
	 else if(selection[0]=='2')
	 {
		 this->akt_videonr++;
		 Video* v=new Video(this->akt_videonr,buf1,buf2);
		 v->show();
		 videoliste.add(v);
	 }

 }
 void Oberflaeche::medien_loeschen()
 {
	 char vbuf[128];
	 int nummer=0,auswahl=0;
	 medien_anzeigen();

	 cout<<endl<<"Was wollen Sie löschen?"<<endl<<"Geben Sie eine der Nummern ein"<<endl<<"(1) Buch"<<endl<<"(2) Video"<<endl<<"(0) zurueck"<<endl;
	 cin.getline(vbuf,128);
	 auswahl=atoi(vbuf);
	 if(strlen(vbuf)==0)
	{
		cout<<"Sie haben nichts eingegeben"<<endl;
		return ;
	}
	if(auswahl==2)
	{
		cout<<"Videonummer? "<<endl;
		cin.getline(vbuf,128);
		if(strlen(vbuf)==0)
		{
			cout<<"Sie haben nichts eingegeben"<<endl;
			return;
		}
		 nummer=atol(vbuf);
		 Video * temp=videoliste.search(nummer);
		 if(temp!=NULL)
		{
			//gefunden
			 cout<<"gefunden: "<<endl;
			 temp->show();
			 videoliste.remove(temp);
		}
	}
	else if(auswahl==1)
	{
		cout<<"Buchnummer? "<<endl;
		cin.getline(vbuf,128);
		 nummer=atol(vbuf);
		 if(strlen(vbuf)==0)
		 {
			cout<<"Sie haben nichts eingegeben"<<endl;
			return;
		}
		 Buch * temp=buchliste.search(nummer);
		if(temp!=NULL)
		{
			//gefunden
			cout<<"gefunden: "<<endl;
			temp->show();
			buchliste.remove(temp);
		}
	}
	else if(auswahl==0)
	{
		return;
	}
	else
	{
		cout<<"Inkorrekte Eingabe"<<endl;
	}



 }
 void Oberflaeche::medien_ausleihen()
 {
//	 liste aller personen
//	 person auswählen
//	 liste aller ausleihbaren medien anzeigen (auf exemplare achten !!)
//	 medium auswählen
//	 bei person ausgeliehenes medium einsetzen
//	 medium_asuleihen()
	 char vbuf[128];
	 int auswahl=0,nummer=0;
	 Person* ausleiher=benutzer_suchen();
	 cout<<"Was möchten Sie leihen?"<<endl<<"(1) Buch"<<endl<<"(2) Video"<<endl;
	 cin.getline(vbuf,127);
	 if(strlen(vbuf)==0)
	{
		cout<<"Sie haben nichts eingegeben"<<endl;
		return;
	}
	auswahl=atoi(vbuf);
	if(auswahl==1)
	{
		if(buchliste.show(true)==-1)
		{
			cout<<"Es kann leider kein Buch ausgeliehen werden"<<endl;
		}
	}
	if(auswahl==2)
	{
		if(videoliste.show(true)==-1)
		{
			cout<<"Es kann leider kein Video ausgeliehen werden"<<endl;
		}
	}
	cout<<"bitte Mediumnummer eingeben"<<endl;
	cin.getline(vbuf,127);
	if(strlen(vbuf)==0)
	{
		cout<<"Sie haben nichts eingegeben"<<endl;
		return;
	}
	nummer=atoi(vbuf);
	cout<<"Auswahl getroffen: "<<nummer<<endl;
	if(auswahl==1)
	{
		Buch* auszuleihen=buchliste.search(nummer);

		if(auszuleihen!=NULL)
		{
			auszuleihen->show();
			ausleiher->leihenBuch(auszuleihen);
			auszuleihen->Exemplar_ausleihen();
		}
	}
	if(auswahl==2)
	{
		Video* auszuleihen=videoliste.search(nummer);
		if(auszuleihen!=NULL)
		{
			auszuleihen->show();
			ausleiher->leihenVideo(auszuleihen);
			auszuleihen->Exemplar_ausleihen();
		}
	}
 }
 void Oberflaeche::medien_anzeigen()
  {
	 cout<<"Bücher"<<endl;
//	 buchliste.getCurrent()->getData()->show();
	 if(buchliste.show()==-1)
	 {
		 cout<<"Keine Bücher mehr vorhanden"<<endl;
	 }
	 cout<<endl;
	 cout<<"Video"<<endl;
	 if(videoliste.show()==-1)
	 {
		 cout<<"Keine Videos mehr vorhanden"<<endl;
	 }

  }
 void Oberflaeche::medien_zurueckgeben()
 {
//	 liste aller personen
//	 	 person auswählen
//	 	liste ausgelihener medien von person anzeigen
//	 	 medium auswählen
//	 	 bei person ausgeliehenes medium austragen
//	 	 medium_zurückgeben()
	char vbuf[128];

	int auswahl=0,zur_med_nr=0;
	Person* ausleiher=benutzer_suchen();
	cout<<"Was möchten Sie zurueckgeben?"<<endl<<"(1) Buch"<<endl<<"(2) Video"<<endl;
	cin.getline(vbuf,127);
	auswahl=atoi(vbuf);
	if(strlen(vbuf)==0)
			{
				cout<<"Sie haben nichts eingegeben"<<endl;
				return ;
			}
	if(auswahl==1)
	{
		Buch* zur_buch;
		zur_med_nr=ausleiher->zurueckgebenBuch();
		if(zur_med_nr==-1)
		{
			return;
		}
		zur_buch=buchliste.search(zur_med_nr);
		zur_buch->Exemplar_zurueckgeben();
	}
	if(auswahl==2)
	{

		Video* zur_video;
		zur_med_nr=ausleiher->zurueckgebenVideo();
		if(zur_med_nr==-1)
		{
			return;
		}
		zur_video=videoliste.search(zur_med_nr);
		zur_video->Exemplar_zurueckgeben();
}

 }
signed int Oberflaeche::getzahl(short whnr)
 {
	 /*Parameter
	  *  1 Buchnummer
	  *  2 Videonummer
	  *  3 Benutzernummer
	  *
	  */
	 FILE* pFile=NULL;
	 short is_nr=0;
	char vbuf[128];

	 pFile=fopen("../listen/zahlen.ini","r+b");
	 	if(pFile==NULL)
	 	{
	 		cout<<"Zahlen.ini existiert nicht"<<endl;
	 		return 0;
	 	}

	 	while(fgets(vbuf, 128, pFile)!=NULL)
	 	{
	 			is_nr++;
	 			if(is_nr==whnr)
	 			{
					fclose(pFile);
	 				return atoi(vbuf);
	 			}

	 	}
	 	fclose(pFile);
	 	return 0;
 }
  void Oberflaeche::setzahl(int buchnr,int vidnr,int kundnr)
  {

	  FILE* pFile=fopen("../listen/zahlen.ini","wt");
	  if(pFile==NULL)
	  {
		  cout<<"zahlen.ini konnte nicht geöffnet werden"<<endl;
	  }
	  fprintf(pFile,"%i\n%i\n%i",buchnr,vidnr,kundnr);
	  fclose(pFile);

  }
Oberflaeche::~Oberflaeche()
{
	setzahl(this->akt_buchnr,this->akt_videonr,this->akt_kundnr);
	speichern();
}
