Ex1

Acest proiect este rezolvarea execitiului 1 din GD1.
Se utilizeaza ca header stiva prezentata la laborator.

Functionalitati implementate:
- INSERT – insereaza un text la o pozitie specifica.
- DELETE – sterge un numar de caractere incepand de la o anumita pozitie.
- UNDO – anuleaza ultima operatie efectuata (INSERT sau DELETE).
- REDO – reface ultima operatie anulata cu UNDO.

Structura de operatii:

	struct Operatii{ 
		char tip[101];  // Tipul operatiei: INSERT sau DELETE
   	 	int poz;        // Pozitia în text unde are loc operatia
    		char s[101];    // Textul implicat în operatie
		};

Funcții principale:

1. void preluarefrumoasa(char *s)
   - Transforma comanda in majuscule, eliminand spatiile.

2. void inserare(char *text, int poz, char *s)
   - Insereaza textul s în șirul principal text la pozitia poz.
   - Verifica validitatea pozitiei si reconstruieste textul.

3. void stergere(char *text, int poz, int nr)
   - sterge nr caractere de la pozita poz.
   - Se face suprascriere si adaugare de '\0'.

Fluxul de control principal (main):
- Initializeaza textul si stivele undo si redo
- Ruleaza o bucla infinita pentru a primi comenzi:
    * INSERT – insereaza si salveaza in undo
    * DELETE – sterge si salveaza in undo
    * UNDO – inverseaza ultima operatie, salveaza în redo
    * REDO – reaplica operatia si salveaza in undo

!!!Atentie: 
	**Introducerea comenzilor se face de la tastatura.
 		Dupa fiecare parte introdusa a comenzii se apasa ENTER.
		Ex: Insert Enter 0 Enter Delete Enter 1 Enter 2 Enter, etc.
	**In fisierul ce contine cod, s-au utilizat atat mesaje de afisare, cat si comentarii specifice care explica codul.
	**Rezultatele se afiseaza in consola.