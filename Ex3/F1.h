#ifndef F1_H_INCLUDED
#define F1_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>





using namespace std;

//liste doublement chainee

template <typename T>
struct Node
{ //structure pour le noeud de la liste; contient l'info de la liste et 2 pointeurs
    T info;
    Node <T> *next; //pointeur au noeud suivant
    Node <T> *prev; //pointeur au noeud anterieur
};

template <typename T>
class LinkedList
{
    public:
        Node <T> *pfirst; //pointeur au premier noeud
        Node <T> *plast; //pointeur au dernier noeud

    void addFirst(T x)
    {
        //ajoute info x sur la premiere position

        Node <T> *paux = new Node<T>;

        paux->info = x; // ou (*paux).info = x;
        paux->prev = NULL;
        paux->next = pfirst;

        if (pfirst != NULL)
            pfirst->prev = paux;

        pfirst = paux; //on relie "first" avec l'element nouveau

        //si on vient d'ajouter le premier element
        if (plast==NULL)
            plast=pfirst;
    }

    void addLast(T x)
    {
        //ajoute info x sur la derniere position

        Node<T> *paux = new Node <T>;

        paux->info = x;
        paux->prev = plast;
        paux->next = NULL;

        if (plast != NULL)
            plast->next = paux;

        plast = paux;

        if (pfirst == NULL)
            pfirst = plast;
    }

    T getInfo (Node<T>* p)
    {
		//retourne l'info d'un certain neoud
        return p->info;
    }

    void removeFirst()
    {
        // efface l'element de la premiere position
        Node<T>* paux;

        if (pfirst != NULL)
        {
            paux = pfirst->next;

            //cas special
            if (pfirst == plast)
                plast = NULL;

            delete pfirst; //efface avec delete

            pfirst = paux;  //l'element suivant devient le nouveau first

            if (pfirst != NULL)
                pfirst->prev = NULL;
        }
        else
            cout<<"The list is empty"<<endl;
    }

    void removeLast()
    {
        //efface l'element de la derniere position
        Node <T> *paux;

        if (plast != NULL)
        {
            paux = plast->prev;

            if (pfirst == plast)
                pfirst = NULL;

            delete plast; //efface avec delete

            plast = paux; //le noeud anterieur devient le nouveau "last"
            if (plast != NULL)
                plast->next = NULL;
        }
        else
            cout<<"The list is empty"<<endl;
    }

    Node <T>* findFirstOccurrence(T x)
    {
        //cherche le premier noeud qui contient info x
        Node <T> *paux;

        paux = pfirst;

        while (paux != NULL)
        {
            if (paux->info == x)
                return paux;
            paux = paux->next;
        }
        return NULL;
    }

    Node <T>* findLastOccurrence(T x)
    { //cherche le dernier noeud qui contient info x
        Node <T> *paux;

        paux = plast;
        while (paux != NULL) {
            if (paux->info == x)
                return paux;
            paux = paux->prev;
        }

        return NULL;
    }

    void removeFirstOccurrence(T x)
    {
        //efface le premier noeud qui contient info x
        Node <T> *px;

        px = findFirstOccurrence(x); //px va etre efface

        if (px != NULL)
        {//on doit les relier
            if (px->prev != NULL)
                px->prev->next = px->next;

            if (px->next != NULL)
                px->next->prev = px->prev;

            if (px->prev == NULL) // if px == pfirst
                pfirst = px->next;

            if (px->next == NULL) // if px == plast
                plast = px->prev;

            delete px; //maintenant on peux l'effacer
        }
    }

    void removeLastOccurrence(T x)
    {
       // efface le dernier noeud qui contient info x
        Node <T> *px;

        px = findLastOccurrence(x);

        if (px != NULL)
        {
            if (px->prev != NULL)
                px->prev->next = px->next;

            if (px->next != NULL)
                px->next->prev = px->prev;

            if (px->prev == NULL) // if px == pfirst
                pfirst = px->next;

            if (px->next == NULL) // if px == plast
                plast = px->prev;

            delete px;
        }
    }

    int isEmpty()
    { //verifie si la liste est vide
        return (pfirst == NULL);
    }

    LinkedList()
    { //constructeur
        pfirst = plast = NULL;
    }

void printListInverse()
{
    Node<T>* paux = plast;
    while (paux != NULL)
    {
        cout << paux->info << " ";
        paux = paux->prev;
    }
    cout << endl;
}

};

#endif
