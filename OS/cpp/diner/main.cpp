//
// Created by infini on 12/05/22.
//

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#define TAB_MAX 5
#define TIME_MIN 5
#define TIME_MAX 25

using namespace std;

// La class fourchette
class Fourchette {
private:
    bool isFree; // La variable d'etat
public:
    Fourchette(){
        this->isFree = true; // Initialisation à libre
    }

    bool getFree(){return this->isFree;}
    void setFree(bool free){
        this->isFree = free;
    }

    bool switchFree(){
        return this->isFree = !this->isFree;
    }
};

// La class Pholosophe
class Philosophe: public QThread{
private:
    QMutex *mutex; // Adresse du mutex

    string name; // Nom
    Fourchette *g; // Adresse de la fourchette Gauche
    Fourchette *d; // Adresse de la fourchette Droite

    void run(){ // Redéfinition de la fonction run de Qthread
        while (1){
            if(g->getFree() && d->getFree()) // Si la fourchette Gauche et Droite sont libre on Mange
                manger();
            else // Sinon on Pense
                penser();
        }
    }

public:
    // Constructeur par défaut et surchargé
    Philosophe(): QThread() {mutex = new QMutex();}
    Philosophe(string name) : QThread(),name(name){mutex = new QMutex();}
    Philosophe(Fourchette *gauche, Fourchette *droite) : QThread(), g(gauche), d(droite){mutex = new QMutex();}
    Philosophe(string name, Fourchette *gauche, Fourchette *droite) : QThread(), name(name),  g(gauche), d(droite){mutex = new QMutex();}

    // la méthode penser
    void penser(){
        if(mutex->tryLock()) { // Exclusion d'acces sur les fourchettes
            if(rand() % 2 == 1){ // Obtenir les fourchettes l'ordre par hasard
                g->setFree(true);
                d->setFree(true);
                cout<< name << "  Laiser la Fourchette : G - D" <<endl;
            }else{
                d->setFree(true);
                g->setFree(true);
                cout<< name << "  Laiser la Fourchette : D - G" <<endl;
            }
            mutex->unlock(); // Libération d'acces sur la fourchette
        }
        // Je pense
        int t = rand() % TIME_MAX + TIME_MIN;
        cout<< name << "\t=>\t PENSE (" << t << "s)" <<endl;
        sleep(t);
    }

    void manger(){
        if(mutex->tryLock()) { // Exclusion d'acces sur les fourchettes
            if(rand() % 2 == 1){ // Obtenir les fourchettes l'ordre par hasard
                g->setFree(false);
                d->setFree(false);
                cout<< name << "  Prendre la Fourchette : G - D" <<endl;
            }else{
                d->setFree(false);
                g->setFree(false);
                cout<< name << "  Prendre la Fourchette : G - D" <<endl;
            }
            mutex->unlock();
        }
        // Je mange
        int t = rand() % TIME_MAX + TIME_MIN;
        cout<< name << "\t=>\t MANGE (" << t << "s)" <<endl;
        sleep(t);
    //      sleep(2);
    }

    void setGauche(Fourchette *item){
        g = item;
    }

    void setDroite(Fourchette *item){
        d = item;
    }

    void setName(string n){
        name = n;
    }

    string getName(){return name;}
    Fourchette* getGauche(){return g;}
    Fourchette* getDroite(){return d;}
};

int main(){
    Fourchette tab[TAB_MAX]; // Tableau de Fourchette
    Philosophe * phils[TAB_MAX]; // Tableau d'adresse de Philosophe

    phils[0] = new Philosophe("A", &tab[4], &tab[0]);
    phils[1] = new Philosophe("B", &tab[0], &tab[1]);
    phils[2] = new Philosophe("C", &tab[1], &tab[2]);
    phils[3] = new Philosophe("D", &tab[2], &tab[3]);
    phils[4] = new Philosophe("E", &tab[3], &tab[4]);

    for(int i = 0; i < TAB_MAX; i++)
    {
        phils[i]->start(); // Démarrage des Threads
    }

    for(int i = 0; i < TAB_MAX; i++)
    {
        phils[i]->wait(); // Attent des Threads
    }

    return EXIT_SUCCESS;
}