// NOM    : LOTFI
// PRENOM : Ayoub

#ifndef __gangster_hpp__
#define __gangster_hpp__
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
using namespace std;

class InconnuException
{
private:
    /* data */
public:
    InconnuException(/* args */);
    virtual const char * what() const throw();
    ~InconnuException();
};


class Personne
{
private:
    /* data */
    string nom;
public:
    Personne(/* args */);
    Personne(const string & _nom);

    bool operator<(const Personne & perso) const;
    string getNom() const;
    ;
    bool equals(const Personne & perso) const ;
    void setNom(const string & nom);
    ~Personne();
};
extern Personne INCONNU;


/* CLASS GANGSTER */
class Gangster
{
protected:
    /* data */
    int id;
    int influence;
    static int compteur;
    Personne personne;
public:
    Gangster(/* args */);
    int getId() const;
    int getInfluence() const;
    bool estInconnu() const ;
    Personne getPersonne() const;
    bool operator<(const Gangster & gang) const;
    void setPersonne(const Personne & perso);
    ~Gangster();
};

/* Class Chef */
class Chef : public Gangster
{
private:
    /* data */
    vector<Gangster> gangsters;
public:
    Chef(/* args */);
    void commande(Gangster* gangster );
    ~Chef();
};

/* CLASS FAmille */
class Famille
{
private:
    /* data */
    vector<Gangster *> familles;
public:
    Famille(/* args */);
    void ajouter(Gangster * gang);
    void listePersonnes(ostream & o = cout);
    ~Famille();
};


//CLASS COMPARATOR
class Comparator
{
private:
    /* data */
public:
    Comparator(/* args */);
    bool operator() (const Gangster* perso1, const Gangster* perso2) const;

};








#endif
