#include "gangster.hpp"
//CLASS PERSONNE
Personne INCONNU("INCONNU");
Personne::Personne(/* args */) : Personne("inconnu")
{
}
Personne::Personne(const string & _nom): nom(_nom){

}

bool Personne::operator<(const Personne & perso) const{
    return nom < perso.getNom();
}
string Personne::getNom() const {
    return nom;
}

void Personne::setNom(const string & _nom) {
    nom = _nom;
}
bool Personne::equals(const Personne & perso) const{
    return this->nom == perso.getNom();
}
Personne::~Personne()
{
}


/* CLASS GANGSTER */
int Gangster::compteur = 0;
Gangster::Gangster(/* args */)
{
    compteur++;
    id = compteur;
    influence = 1;
}

int Gangster::getId() const {
    return id;
}
bool Gangster::estInconnu() const {
    return personne.getNom() == "inconnu";
}
bool Gangster::operator<(const Gangster & gang) const{
    if (this->getInfluence() == gang.getInfluence())
    {
        return this->getId() > gang.getId();
    }else
    {
        return this->getInfluence() < gang.getInfluence();
    }
}
int Gangster::getInfluence() const {
    return influence;
}
Personne  Gangster::getPersonne() const{
    if (personne.getNom() == "inconnu")
        throw InconnuException();
    return personne;
}
void Gangster::setPersonne(const Personne & perso){
    personne = perso;
}
Gangster::~Gangster()
{
}


/* Class Chef */
Chef::Chef(/* args */)
{
}

void Chef::commande(Gangster * gangster){
    gangsters.push_back(*gangster);
    if (gangsters.size() == 1)
    {
        influence = 10 + gangster->getInfluence(); 
    }else
    {
        influence += gangster->getInfluence();
    }
}

Chef::~Chef()
{
}


/* CLASS EXCEPTION */

InconnuException::InconnuException(/* args */)
{
} 
const char * InconnuException::what() const throw(){
    return "personnalite inconnue";
}
InconnuException::~InconnuException()
{
}



//CLASS COMPARATOR
Comparator::Comparator(/* args */)
{
}
bool Comparator::operator() (const Gangster* perso1, const Gangster* perso2) const{
    if (!perso1->estInconnu() && !perso2->estInconnu() )
    {
        return perso1->getPersonne() < perso2->getPersonne();
    }else if(!perso1->estInconnu()) return true;
    else if(!perso2->estInconnu()) return false;
    else return true;
    
    
    // return resultat;
    // return *perso1 < *perso2;
}

FoncteurInf::FoncteurInf(/* args */)
{
}
bool FoncteurInf::operator()(const Gangster* g1, const Gangster * g2) const{
    return *g1 < *g2;
}


FoncteurSup::FoncteurSup(/* args */)
{
}
bool FoncteurSup::operator() (const Gangster * gg1, const Gangster * gg2) const{
    return *gg2 < *gg1;
}

//CLASS FAMILLE

Famille::Famille(/* args */)
{
}
void Famille::ajouter(Gangster* gang){
    
    familles.push_back(gang);
}
void Famille::listeMembres(ostream & o ){
    string resultat {};
    sort(familles.begin(),familles.end(),FoncteurSup());
   
    std::for_each(familles.begin(), familles.end(), [&](const auto& item) {
        o << resultat << item->getId();
        resultat = " ";
    });
    
}


void Famille::listePersonnes(ostream & o){
    // Comparator temp;
    vector<string> toto;
    sort(familles.begin(),familles.end(),Comparator());
    string resultat = "";
    auto it = familles.begin();
    for (it = familles.begin(); it != familles.end()-1; it++)
    {
        if (!(*it)->estInconnu())
        {
            if (!(*(it+1))->estInconnu())
            {
                /* code */
                resultat += (*it)->getPersonne().getNom() + ", ";
            }else
            {
                /* code */
                resultat+= (*(it))->getPersonne().getNom();
            }
            
            // toto.push_back((*it)->getPersonne().getNom());
        }
    }


    // auto it = toto.begin();
    // for (it = toto.begin(); it != toto.end()-1; it++)
    // {
    //     resultat+= *it + ", ";
    // }
    // resultat += *it;
    
    
    
    // resultat += (*it)->getPersonne().getNom();
    o << resultat;
    

}
ostream & operator<<(ostream & o, Famille famille){
    famille.listePersonnes(o);
    return o;
}
Famille::~Famille()
{
}


