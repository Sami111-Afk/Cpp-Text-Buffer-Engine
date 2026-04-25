#include <iostream>
#include <string>
#include "myqueue2.h"

using namespace std;

struct Pacient//struct pentru pacient
{
    string nume;
    string conditiemedicala;
};


class HospitalManagementSystem
{

public:

    QueueCirc<Pacient> td[31];//cozi pentru fiecare set de 4 pacienti, variabila pentru ocupat/vacant nu este necesara
                            //(cand am inceput sa rezolv am uitat sa o folosesc si am facut rezolvarea testand in functie continut, daca exista sau nu )
                            //merg doar pana la 31 , nu cred ca un spital mic are mai mult de 124 de pacienti odata:)
    HospitalManagementSystem()//clasa
    {

    }

    void admitPatient(string patientName, string condition)//fucntia de admitere
    {
        if(patientName=="NULL" || condition=="NULL")//daca nu se introduc numele sau conditia, practic nu se respecta fucntia si trebuie sa dea eroare
        {
            cout<<"Eroare , nu exista nume sau conditie pentru pacient"<<' '<<endl;
            return ;
        }

        for(int i=0; i<31; i++)//parcurg toate cozile
        {
            if(td[i].getSize()<4)//verific sa nu fie pline si adaug
            {
                Pacient np;
                np.nume=patientName;
                np.conditiemedicala=condition;
                td[i].enqueue(np);
                return;
            }
        }
        cout<<"Eroare niciun departament deschis(nu mai sunt serii de cate 4 paturi)"<<' '<<endl;
    }

    void dischargePatient(int bedIndex)//functia de iesire
    {
        if(bedIndex<0||bedIndex>=124)//verific sa u fie index gresit
        {
            cout<<"Eroare, index de pat invalid"<<' '<<endl;
        }

        Pacient totipacientii[124];//fac un vector pentru toti pacientii posibili
        int tp=0;//totalul pacientilor
        int indexpacient=0;
        for(int i=0; i<31; i++)
        {

            while(td[i].isEmpty()==0)//scot toti pacientii si ii pun in vector, mai putin cel pe care trebuie sa il elimin
            {
                Pacient p=td[i].dequeue();
                if(indexpacient!=bedIndex)
                {
                    totipacientii[tp++]=p;
                }
                indexpacient++;
            }
        }
        if(tp==indexpacient)
        {
            cout<<"Eroare , nu exista pacientul in sistem"<<' '<<endl;
        }

        for(int i=0; i<31; i++)//ma asigur ca toate cozile sunt goale
        {
            while(td[i].isEmpty()==0)
            {
                td[i].dequeue();
            }
        }
        for(int i=0; i<tp; i++)//pun inapoi in cozi pe seturi de cate 4 toti pacientii in oridine fara spatii
        {
            td[i/4].enqueue(totipacientii[i]);

        }


        cout<<"Pacientul a fugit cu succes"<<' '<<endl;
    }

    void transferPatient(int sourceBedIndex, int targetBedIndex)//functia de transfer
    {

        if(sourceBedIndex<0 || sourceBedIndex>=124 || targetBedIndex<0 || targetBedIndex>=124)//verific sa fie valide indexurile
        {
            cout<<"Eroare , indexuri invalide pentru transfer"<<' '<<endl;
        }

        if(sourceBedIndex==targetBedIndex)
        {
            cout<<"Atentie, indexul este identic, transferul nu este necesar"<<' '<<endl;
        }

        int tp=0;//total pacienti
        Pacient pacienti[124];//tin minte toti pacientii in vector


        for(int i=0; i<31; i++)//ii scot pe toti
        {
            while(td[i].isEmpty()==0)
            {
                pacienti[tp++]=td[i].dequeue();
            }
        }
        if(sourceBedIndex<0 || targetBedIndex>=tp || targetBedIndex<0 || targetBedIndex>=tp)
        //Daca cumva incerc sa tranfer un pacient pe o pozitie goala inseamna ca voi lasa un spatiu liber,
        //ceea ce incalca o conditie a functiei.
        //Daca ar fi sa fac acest transfer intrebarea devine, ce fac cu restul pacientilor,
        //ii mut cu o pozitie , ca sa nu am spatii libere intre pacienti, ci doar la inceput sau la final,
        //caz in care defapt tot sunt spatii goale si incalc cerinta, sau mut si pacientul deja mutat ,
        //in fapt facand doar mutarea la capetele cozii. In lipsa de claritate a cerintei si in lipsa de timp,
        //consider eroare acest caz. Cazul, care defapt functioneaza,
        //este cel in care incerc sa mut pacientul pe o pozitie pe care deja am un alt pacient,
        //iar atunci functia mea devine doar o functie de swap. Defapt functia foar asta este o functie de swap,
        //in rest nu face altceva decat sa fiseze eroare.
        {
            cout<<"Eroare index invalid, mutarea paacientului din patul"<<' '<<sourceBedIndex<<' '<<"la patul"<<' '<<targetBedIndex<<' '<<"ar lasa un spatiu liber , iar atunci se incalca una din conditiile functiei, deci eroare."<<endl;

            for(int i=0; i<tp; i++)//reintroduc pacientii
            {
                td[i/4].enqueue(pacienti[i]);
            }
            return;
        }

        //efectuez swap-ul
        Pacient aux=pacienti[sourceBedIndex];
        pacienti[sourceBedIndex]=pacienti[targetBedIndex];
        pacienti[targetBedIndex]=aux;

        for(int i=0; i<tp; i++)//reintroduc pacientii
        {
            td[i/4].enqueue(pacienti[i]);
        }


        cout<<"Pacientul a fost mutat de la patul"<<' '<<sourceBedIndex<<' '<<"la patul"<<' '<<targetBedIndex<<' '<<"si invers"<<' '<<endl;
    }




    string getPatientInfo(int bedIndex)//functia de obtinere a informatiilor
    {
        if(bedIndex<0 || bedIndex>=124)//verific validitatea indexului
        {
            cout<<"Eroare , index invalid"<<' '<<endl;
        }
        int index=0;
        for (int i=0; i<31; i++)//parcurg toate set-urilre de pacienti
        {
            int s=td[i].getSize();
            Pacient aux[4];
            for(int j=0; j<s; j++)//parcurg pacientii
            {
                aux[j] =td[i].dequeue();//ii scot si ii tin minte
            }
            for(int j=0; j<s; j++)//parcurg fiecare set
            {
                if(index==bedIndex)//verific sa afisez informatiile doar despre pacientul corect
                {
                    string afisare=aux[j].nume+'-'+aux[j].conditiemedicala;//pregatesc setul de date de afisare.
                    for(int k=0; k<s; k++)//readaug pacientul scos
                    {
                        td[i].enqueue(aux[k]);
                    }
                    return afisare;//fac afisarea cu return pentru ca in cerinta functia este de tip string, si nu am avut alta idee
                }
                index++;
            }
            for(int j=0; j<s; j++)//readaug pacientii
            {
                td[i].enqueue(aux[j]);
            }
        }
        return "Eroare nu sunt pacienti";

    }

    void displaySystem()//functia de afisare a sistumului intreg
    {
        int gol=1;
        for(int i=0; i<31; i++)//parcurg set-urile de pacienti
        {
            int s=td[i].getSize();
            int index=0;
            Pacient pacienti[4];
            for(int j=0; j<s; j++)//parcurg pacientii din set
            {
                Pacient p =td[i].peek();
                cout<<p.nume<<"-"<<p.conditiemedicala<<' '<<endl;//afisez informatiile
                pacienti[index]=td[i].dequeue();//scot pacientul ca sa pot sa il vad pe urmatorul
                index++;
            }
            for(int j=0; j<s; j++)//readaug pacientii
            {
                td[i].enqueue(pacienti[j]);
            }
            if(s>0)
                gol=0;
        }
        if(gol==1)
        {
            cout<<"Sistemul este gol"<<' '<<endl;
        }
    }



};

int main()
{
    HospitalManagementSystem sms;

    sms.admitPatient("Sergiu", "Pneumonia");
    sms.admitPatient("Rares", "Broken Arm");
    sms.displaySystem();
    cout<<sms.getPatientInfo(0)<<endl;
    sms.dischargePatient(0);
    sms.displaySystem();
    sms.transferPatient(1,3);
    sms.displaySystem();
    sms.admitPatient("1", "Pneumonia");
    sms.admitPatient("2", "Pneumonia");
    sms.admitPatient("3", "Pneumonia");
    sms.transferPatient(1,3);
    sms.displaySystem();


    return 0;

}
//:D
