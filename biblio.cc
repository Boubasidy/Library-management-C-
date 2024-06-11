#include "biblio.hh"

document::document(const std::string &titre, const std::string &nomauteur)
    : _titre(titre), _nomauteur(nomauteur) {}

void document::sortie(std::ostream &os) const {
    os << "document de type " << typedoc() << "\n";
    os << "Titre : " << _titre << "\n";
    os << "Nom de l'auteur du document : " << _nomauteur << "\n";
    if (emprunt()) {
        os << "document empruntable" << "\n";
    } else {
        os << "non empruntable" << "\n";
    }
}

docecrit::docecrit(const std::string &titre, const std::string &nomauteur, unsigned int nb)
    : document(titre, nomauteur), _nbPages(nb) {}

video::video(const std::string &titre, const std::string &nomauteur, support supp)
    : document(titre, nomauteur), _support(supp) {}

void video::sortie(std::ostream &os) const {
    document::sortie(os);
    affichage(os);
}

periodique::periodique(const std::string &titre, const std::string &nomauteur, unsigned int nb, unsigned int num)
    : docecrit(titre, nomauteur, nb), _numPeriode(num) {}

void periodique::sortie(std::ostream &os) const {
    docecrit::sortie(os);
    os << "Il s'agit du périodique numéro " << _numPeriode << "\n";
    if (emprunt()) {
        os << "document empruntable" << "\n";
    } else {
        os << "non empruntable" << "\n";
    }
}

livre::livre(const std::string &titre, const std::string &nomauteur, unsigned int nb, bool emp)
    : docecrit(titre, nomauteur, nb), _capemprunt(emp) {}

void livre::sortie(std::ostream &os) const {
    docecrit::sortie(os);
    if (emprunt()) {
        os << "document empruntable" << "\n";
    } else {
        os << "non empruntable" << "\n";
    }
}

std::ostream &operator<<(std::ostream &os, const document &doc){
    doc.sortie(os);
    return os;
}

bibliotheque::~bibliotheque(){
    for (auto p : _biblio){
    delete p;
    }
}

bibliotheque::bibliotheque(const bibliotheque &biblio){
    for(auto p : biblio._biblio){
    _biblio.push_back(p->clone());
    }
}

std::size_t bibliotheque::nombrevideos(support ts) const{
    std::size_t nombrevid (0);
    for (auto p : _biblio){
        auto vid = dynamic_cast<video const *>(p);
        if (vid && (vid->getsup() == ts)){
            nombrevid ++;
        }
    }
    return nombrevid;

}

void bibliotheque::affichage(std::ostream &os) const{
for (std::size_t i(0) ; i<taille() ; i++){
    acces(i).sortie(os);
    }
}
