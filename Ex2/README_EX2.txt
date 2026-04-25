Ex2


Acest proiect este rezolvarea exercitiului 2 din GD1.
Se utilizeaza ca header , coada circulara prezentata la laborator.

Functionalitati implementate si functii principale:

-admitPatient(string patientName, string condition)-adauga un pacient pe prima pozitite libera din fiecare coada.
-dischargePatient(int bedIndex)-scoate unu pacient de pe pozitia data.
-transferPatient(int sourceBedIndex, int targetBedIndex)-transfera un pacient de pe o pozitie pe o alta.
-getPatientInfo(int bedIndex)-afiseaza informatiile despre pacientul de pe o pozitie data.
-displaySystem()-afiseaza toti pacientii.

Structura folosita:
	struct Pacient{
    		 string nume;
   		 string conditiemedicala;
		};

Clasa folosita: class HospitalManagementSystem

Fluxul de control principal (main):
-initializeaza clasa HospitalManagementSystem
-realizeaza o serie de operatii pe baza functiilor implementate in clasa.

!!!Atentie:
	**Introducerea comenzilor de face inainte de rularea programului.
	**In fisierul ce contine cod, s-au utilizat atat mesaje de afisare, cat si comentarii specifice care explica codul.
 	**Rezultatele sunt afisate in consola.
