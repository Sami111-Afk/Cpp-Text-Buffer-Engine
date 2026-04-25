#include <iostream>
#include <cstring>
#include <cstdlib>
#include "mystack.h"//stiva prezentata si utilizata la curs si laborator

using namespace std;

struct Operatii//struct specific folosit pentru stocarea comenzilor introduse
{
    char tip[101];
    int poz;
    char s[101];

};

void preluarefrumoasa(char *s)//prelucrarea comenzii introduse
{
    int j = 0;
    for (int i = 0; s[i]!='\0'; ++i)//parcurgerea comenzii introduse pana la final
    {
        if (s[i]!=' ')//cat timp e diferit de spatiu
        {
            s[j++] = toupper(s[i]);//conversie in litera mare
        }
    }
    s[j] = '\0';//adaugarea la finalul comenzii prelucrate a caracterului specific de incheiere/delimitare
}


void inserare(char *text, int poz, char *s)//comanda de INSERT
{
    if(poz<0 || poz>strlen(text))//verificarea validitatii pozitiei introduse
    {
        cout<<"Eroare cauzata de pozitie invalida"<<' ';
        cout<<endl;
        return;
    }
    else
    {
        //inserarea propriu-zisa
        char aux1[101];
        strncpy(aux1, text, poz);
        aux1[poz]='\0';
        char aux2[101];
        strcpy(aux2, text+poz);
        strcpy(text,aux1);
        strcat(text, s);
        strcat(text,aux2);
    }//executarea  operatiunilor necesare pentru insert,
    //adica  copiam intr-un auxiliar1 prima parte a textului pana la pozitie,
    //intr-un auxiliar 2 copiam restul textului,
    // iar  ulterior copiam in text auxiliarul 1,
    //concatenam cu sirul pe care vrem sa il introducem si la final concatenam si auxiliar2.

}

void stergere(char *s, int poz, int nr)//comanda de DELETE
{
    if(poz<0 || poz+nr>strlen(s))//verificarea pozitiilor introduse
    {
        cout<<"Eroare cauzata de pozitie invalida"<<' ';
        cout<<endl;
    }

    else
    {
        int i;
        for( i=poz; i+nr<strlen(s); i++)//parcurgem textul de la prima pozitie la a doua si permutam toate caracterele la stanga cu a numarul=a doua pozitie
        {
            s[i]=s[i+nr];//stergerea propriu-zisa
        }
        s[i]='\0';//punem finalul
    }

}

int main()
{
    char text[1001]="";
    Operatii com;
    Stack<Operatii> undo;//stiva undo
    Stack<Operatii> redo;//stiva redo

    while (true)
    {
        cin.getline(com.tip, 100);
        cout<<"Comanda testata "<<com.tip<<endl;//comenzi de debug, ca sa avem un minim feedback, dupa fiecare comanda propriu-zisa(INSERT, etc.) se apasa ENTER
        preluarefrumoasa(com.tip);
        cout<<"Comanda dupa preluarefrumoasa "<<com.tip<<endl;
        if(strcmp(com.tip,"INSERT")==0)
        {
            cin>>com.poz;
            cin.ignore();//ignoram endl
            cin.getline(com.s, 100);
            inserare(text, com.poz, com.s);
            undo.push(com);//stocam in stiva de undo
            cout<<"Textul la acest moment "<<text<<endl;
        }
        else if(strcmp(com.tip,"DELETE")==0)
        {
            cin>>com.poz;
            cin.ignore();
            cin.getline(com.s, 100);
            int nr=atoi(com.s);//folosim atoi pentru a obtine int ul speicific echivalent char ului de la comanda delete , care in fapt este numar.
            if(nr>=0 && nr<=strlen(text))//vaerificam validitatea index-ilor
            {

                char aux[101];
                strncpy(aux, text + com.poz, nr);
                aux[nr] = '\0';
                strcpy(com.s, aux);
                stergere(text, com.poz, nr);
                undo.push(com);
                cout<<"Textul la acest moment "<<text<<endl;
            }
            else
            {
                cout<<"Eroare"<<' '<<endl;
            }
        }
        else if(strcmp(com.tip,"UNDO")==0)

        {
            if(!undo.isEmpty())
            {
                Operatii op=undo.pop();
                int nr=strlen(op.s);
                if(strcmp(op.tip,"INSERT")==0)
                {
                    stergere(text, op.poz, nr);//daca comanda este de tip insert noi la undo trebuie sa facem defapt delete, si tot asa
                    Operatii re;
                    strcpy(re.tip,"INSERT");
                    re.poz=op.poz;
                    strcpy(re.s, op.s);
                    redo.push(re);//practic inseram comanda utilizata(stocata prin struct) in stiva de redo
                    cout<<"Textul dupa UNDO "<<text<<endl;
                }
                else if(strcmp(op.tip,"DELETE")==0)
                {
                    inserare(text, op.poz, op.s);
                    Operatii re;
                    strcpy(re.tip,"DELETE");
                    re.poz=op.poz;
                    strcpy(re.s, op.s);
                    redo.push(re);
                    cout<<"Textul dupa UNDO "<<text<<endl;
                }
            }
            else
            {
                cout<<"UNDO este gol"<<' '<<endl;
            }
        }
        else if(strcmp(com.tip,"REDO")==0)

        {
            if(!redo.isEmpty())
            {
                Operatii op=redo.pop();//scaotem comanda din stiva redo
                if(strcmp(op.tip,"INSERT")==0)
                {
                    inserare(text, op.poz, op.s);
                    undo.push(op);//restocam comanda in stiva undo
                }
                else if(strcmp(op.tip,"DELETE")==0)
                {
                    int nr=strlen(op.s);
                    stergere(text, op.poz, nr);
                    undo.push(op);
                }
                cout<<"Textul dupa REDO "<<text<<endl;
            }
            else
            {
                cout<<"REDO este gol"<<' '<<endl;
            }
        }
        else
        {
            cout<<"Comanda necunoscuta"<<' '<<endl;
            return 0;
        }

    }

}


//:D
