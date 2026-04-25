#ifndef F2_H_INCLUDED
#define F2_H_INCLUDED
#include <fstream>
#include <string>
#include <iostream>

#endif

#include "F1.h"
 using namespace std;

class Song {
private:                      //asta este clasa specifcata in enunt am preferat lucratul cu clase nu cu STRUCT pentru folosirea setarilor si getarilor
    int preference;
    int duration;
    string name;
public:
     Song() : preference(0), duration(0), name("") {}
                                                         //iniatilizare prin lista de initializare
    Song(int p, int d, string n) {                      //(este necesar in acest caz deoarece initalizizeaza direct si evita erori de suprascriere)
        preference = p;                                 //(prezente in cazul absentei ei)
        duration = d;
        name = n;
    }


    int getPreference()  {
        return preference;
    }

    int getDuration()  {
        return duration;
    }

    string getName()  {
        return name;
    }


    void setPreference(int p) {
        preference = p;
    }

    void setDuration(int d) {
        duration = d;
    }

    void setName(string n) {
        name = n;
    }

    bool operator==( Song& other)  {    //acest operator practic creeaza un alt tip de egal
        return (this->name == other.name);        // compilatorul nu stie altfel sa compare doua melodii
                                                  // necesara pentru a nu avea eroare in program ,,nu exista operatorul =="
    }
};

  class MiniSpotify{
    private:
    LinkedList<Song> Vip;
    LinkedList<Song> Casual;
    LinkedList<Song> Ultimul;

     LinkedList<Song> Istoric;
     Song piesaCurenta;
     int duratieRamasa=0;            //sunt simple lucruri declarate pentru a putea jongla in program mai comod
     Song piesaDinIstoric;           //acealasi lucru ca mai sus



     public:   //e necesar ca metodeel sa fie publice pentru a putea fi utilizate in main

           void addSong(Song piesa)  {                //functia de adaugare folosim get arul din constructor plus o fucntrie din headearul de la clasa
        if(piesa.getPreference()==1){
            Vip.addFirst(piesa);}
            else if (piesa.getPreference()==2){


            Casual.addLast(piesa);}
            else Ultimul.addLast(piesa);

           }


      //de specificat folosinta la ofstream aici e necesara pentru scrierea in fisier va fi prezenta in toate functile unde trebuie scris in fisier

      void play(ofstream& out){
      if (!Vip.isEmpty()){
         piesaCurenta=Vip.pfirst->info;                                                                          //verificam listele declarate la inceput cu prioritati
        out<<"Now playing:" << piesaCurenta.getName() <<"("   << piesaCurenta.getDuration()<< "s) \n";           //pentru vederea modului in care dam play la muzica
        Istoric.addFirst(piesaCurenta);
      }
      else if(!Casual.isEmpty()){
        piesaCurenta=Casual.pfirst->info;
        out<<"Now playing:" << piesaCurenta.getName() <<"("   << piesaCurenta.getDuration()<< "s) \n";
         Istoric.addFirst(piesaCurenta);
      }
      else if(!Ultimul.isEmpty()){
         piesaCurenta=Ultimul.pfirst->info;
        out<<"Now playing:" << piesaCurenta.getName() <<"("   << piesaCurenta.getDuration()<< "s) \n";
         Istoric.addFirst(piesaCurenta);

      }
      duratieRamasa=piesaCurenta.getDuration();
      }




  void skip(int n, ofstream& out) {
      if(duratieRamasa!=0  && n>=duratieRamasa){
            out << "Skipped" << n << "s. Song Finished\n";
            duratieRamasa = 0;}

      if(duratieRamasa!=0 && n<duratieRamasa){
        duratieRamasa-=n;
        out << "Skipped" << n << "s.  " << duratieRamasa << "s. remaining\n";
      }
        }









void replay(ofstream& out) {
        if (Istoric.isEmpty()) {
            out << "No song was played\n";
            return;
        }

Song lastPlayed = Istoric.plast->info; //necesar pentru nu a  obtine de 2 ori acelasi lucru adica o dublura


  Vip.removeFirstOccurrence(lastPlayed);
         Casual.removeFirstOccurrence(lastPlayed);   //aici doar verificam si dam remove cu functia din headerul de la clasa
        Ultimul.removeFirstOccurrence(lastPlayed);

        if (lastPlayed.getPreference() == 1) {
            Vip.addLast(lastPlayed);
        } else if (lastPlayed.getPreference() == 2) {     //readaugam in lista a carei preferinta face parte
            Casual.addLast(lastPlayed);
        } else {
            Ultimul.addLast(lastPlayed);
        }

        out << "Replaying: " << lastPlayed.getName() << "\n";
    }








       void remove(string songName, ofstream& out){
       Song Comparatie(0, 0, songName);                // e nevoie de ceva de comparat ca creem un obiect

        Vip.removeFirstOccurrence(Comparatie);         //acum putem da remove folosind functia din calsa din cauza antetului de mai sus

        Casual.removeFirstOccurrence(Comparatie);      //doar dam remove folosind functia de la clasa

        Ultimul.removeFirstOccurrence(Comparatie);

        out << "Removed: " << songName << "\n";

       }





   void show(ofstream& out) {
     out << "Playlist:\n";

      out << "Preference 1:\n";                            //ne folosim de while uri si cateva functii din headerul de la calsa
      Node<Song>* p1 = Vip.pfirst;
     while (p1 != NULL) {                                // scopul fiind sa afisam mai intai dupa preferinta apoi dupa mna lucrurile de afisat
        out << p1->info.getName();
         if (p1->next != NULL)
            out << ", ";
        else
            out << "\n";
        p1 = p1->next;
    }

     out << "Preference 2:\n";
     Node<Song>* p2 = Casual.pfirst;
      while (p2 != NULL) {
        out << p2->info.getName();
         if (p2->next != NULL)
             out << ", ";
        else
            out << "\n";
         p2 = p2->next;
    }

     out << "Preference 3:\n";
      Node<Song>* p3 = Ultimul.pfirst;
    while (p3 != NULL) {
           out << p3->info.getName();
         if (p3->next != NULL)
              out << ", ";
        else
            out << "\n";
        p3 = p3->next;
    }
}






void historyPrint(ofstream& out) {
    out << "History:\n";

    int idx = 1;



    Node<Song>* p = Istoric.pfirst;
                                                                 //afisarea la istoric fucntioneaza la fel cu exceptia lui idx care este un index
    while (p != NULL) {
         out << idx << ". " << p->info.getName() << "\n";         //ar fi putut fi devinit ind dar pentru orice motiv programul da eroare cu ind
           idx++;
         p = p->next;
    }                                                            // tot asa ne folosim de functiile din header sa obtinem rezulattul de afisaz (ma refer la ehaderul de la clasa)
}

  };

