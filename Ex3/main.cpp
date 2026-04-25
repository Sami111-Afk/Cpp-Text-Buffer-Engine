#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "F2.h"

using namespace std;

int main() {
    MiniSpotify Copie;

    ifstream fin("input.txt");
    ofstream fout("Output.txt");
 //erori in caz de nu merg fisierele
    if (!fin) {
        cout << "nu se deschide fisierul,probabil nu e introdus bine\n";
        return 1;
    }

    if (!fout) {
        cout << "nu se poaate deschide fisierul de scriere, cel mai probabil e introdus prost mai incearca\n";
        return 1;
    }

    string linie, comanda;

    while (getline(fin, linie)) {
        stringstream linestream(linie);
        linestream >> comanda;

        if (comanda == "ADD") {
            int pref;
        int timp;
            string titlu;
            linestream >> pref >> timp;

            //citim lucrurile din fisier altfel nu avem cum sa apelam fucntile
            linestream.ignore();

            getline(linestream, titlu);


            Song s(pref, timp, titlu);

            Copie.addSong(s);
        }

         if (comanda == "PLAY") {
            Copie.play(fout);
        }
         if (comanda == "SKIP") {
            int secunde;
            //citim secundele <<e nevoie pentru functie altfel nu putem aplica>>
            linestream >> secunde;

            Copie.skip(secunde, fout);
        }
        if (comanda == "REPLAY") {
            Copie.replay(fout);
        }
         if (comanda == "REMOVE") {
            string nume;
            linestream.ignore();
            getline(linestream, nume);
            Copie.remove(nume, fout);
        }
        if (comanda == "SHOW") {
            Copie.show(fout);
        }
        if (comanda == "HISTORY") {
            Copie.historyPrint(fout);
        }
    }

    fin.close();
    fout.close();

    return 0;
}
