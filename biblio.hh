#ifndef BIBLIO_HH
#define BIBLIO_HH

#include <iostream>
#include <string>
#include <vector>

enum class support {
    DVD,
    BluRay,
    BluRay3D
};

class document {
public:
    virtual ~document() = default;
    document(const std::string &titre, const std::string &nomauteur);
    const std::string &getTitre() const {
        return _titre;
    }
    const std::string &getNomauteur() const {
        return _nomauteur;
    }
    virtual bool emprunt() const = 0;
    virtual double cout() const = 0;
    virtual void sortie(std::ostream &os) const;
    virtual const std::string &typedoc() const = 0;
    virtual document * clone() const = 0 ;

private:
    std::string _titre;
    std::string _nomauteur;
};
                    //docecrit
class docecrit : public document {
public:
    docecrit(const std::string &titre, const std::string &nomauteur, unsigned int nb);
    unsigned int getNbPages() const {
        return _nbPages;
    }
    double cout() const override {
        return 0.50 * _nbPages;
    }
    void sortie(std::ostream &os) const override {
        document::sortie(os);
        os << "avec " << _nbPages << " pages\n";
        os << "Il coûte " << cout() << "€\n";
    }

private:
    unsigned int _nbPages;
};
                        //video
class video : public document {
public:
    video(const std::string &titre, const std::string &nomauteur, support supp);
    double cout() const override {
        return 0.70;
    }
    bool emprunt() const override {
        return true;
    }
    void affichage(std::ostream &os) const {
        switch (_support) {
            case support::BluRay:
                os << "c'est un support Blu-ray\n";
                break;
            case support::DVD:
                os << "c'est un support DVD\n";
                break;
            case support::BluRay3D:
                os << "c'est un support Blu-ray 3D\n";
                break;
            default:
                os << "support non reconnu\n";
                break;
        }
    }
    support getsup() const {
        return _support;
    }
    void sortie(std::ostream &os) const override;
    const std::string &typedoc() const override {
        static const std::string type = "Vidéo";
        return type;
    }
    document * clone() const override {
        return new video(*this);
    }

private:
    support _support;
};
                            //periodique
class periodique : public docecrit {
public:
    periodique(const std::string &titre, const std::string &nomauteur, unsigned int nb, unsigned int num);
    bool emprunt() const override {
        return false;
    }
    void sortie(std::ostream &os) const override;
    const std::string &typedoc() const override {
        static const std::string type = "périodique";
        return type;
    }
    document * clone() const override {
        return new periodique(*this);
    }

private:
    unsigned int _numPeriode;
};

                        //livre

class livre : public docecrit {
public:
    livre(const std::string &titre, const std::string &nomauteur, unsigned int nb, bool emp);
    bool emprunt() const override {
        return _capemprunt;
    }
    void sortie(std::ostream &os) const override;
    const std::string &typedoc() const override {
        static const std::string type = "livre";
        return type;
    }
    document * clone() const override {
        return new livre(*this);
    }
private:
    bool _capemprunt;
};

std::ostream & operator<<(std::ostream & os , document const & doc);

// classe bibliotheque

class bibliotheque {
public:
    ~bibliotheque();
    void ajouter (document const & doc){
        _biblio.push_back(doc.clone());
    }
    bibliotheque(bibliotheque const & biblio) ;
    document const & acces (std::size_t i ) const {
        return *(_biblio.at(i));
    }
    std::size_t taille () const {
        return _biblio.size();
    }
    std::size_t nombrevideos(support ts) const ;
    void affichage(std::ostream & os) const ;
private:
    std::vector<document * > _biblio;
};
std::ostream & operator<<(std::ostream & os , bibliotheque const & biblio);
#endif // BIBLIO_HH
