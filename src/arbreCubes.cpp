
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

/**
 * @file arbreCubes.cpp
 * @author Sebastien VALLEE && Kevin GONNORD
 * @since 01/05/2015
 * @brief implémentation des méthodes de la classe arbrecubes
 *
**/

#include "arbreCubes.hpp"
 using namespace std;

/**
	*brief Constructeur, crée un arbre avec les cubes donnés dans un fichier
  	* @param nomfic Le nom du fichier texte
*/
arbrecubes::arbrecubes(std::string nomfic){
    _racine=NULL;
    ifstream fic(nomfic.c_str());
    assert(fic.is_open());
    string ligne;
    getline(fic,ligne);
    while(!fic.eof())
    {
	//cout <<"   "<< "j'ai lu " << ligne << endl;
        stringstream ss(ligne);
        int x,y,largeur;
        ss >> x >> y >> largeur;
        point P(x,y);
        cube CC(P,largeur);
		ajouter(CC);         // suppose que l'on peut ajouter même si _racine==NULL
		getline(fic,ligne);
	}
}

/**
    * @brief Donne la liste des cubes directement supportés par le paramètre
    * @param CC un cube supposé présent dans l'arbre
    * @return un vecteur de cubes ayant tous CC comme père
*/
std::vector<cube> arbrecubes::dessus(const cube & CC) const {
    _noeud * courant = recherche(CC);
<<<<<<< HEAD
=======
>>>>>>> d41b1ed36d9912e1033bceec29f38aedfaac19dc

    //etape 2 : créer le vecteur
    std::vector<cube> cubes;
    courant = courant->fils ;

    while(courant !=NULL){
        cubes.push_back(courant->bloc);
        courant = courant->frere;
    }
    return cubes;
}

/**
    * @brief Donne le cube sur lequel est empilé le paramètre
    * @param CC un cube supposé présent dans l'arbre
    * @return le cube père de CC
*/
const cube arbrecubes::soutien(const cube & CC) const {
    _noeud * soutien = recherche(CC,true);
    return soutien->bloc;

}

/**
    * @brief ajoute un cube dans l'arbre, à sa place
    * @param CC un cube à ajouter
    * ajoute CC dans la liste des fils du plus petit cube qui peut le supporter
    *    ( dans l'ordre )
    * et prend comme fils tous les cubes qu'il peut supporter
*/
void arbrecubes::ajouter(const cube & CC){ //probleme ?
    _noeud * newneuneu = new _noeud();
    if(_racine == NULL){
        newneuneu->bloc = CC;
        newneuneu->frere = NULL;
        newneuneu->fils = NULL;

        _racine =  newneuneu;
	}
    else{
        std::vector<_noeud*> tmp;

        _noeud * pereTempo = _racine;
        _noeud * courant = _racine->fils;
        while(courant != NULL){
            if(peutSupp(CC , courant->bloc)){
                tmp.push_back(courant);
                courant = courant->frere;
            }
            else if(peutSupp(courant->bloc, CC)){
                pereTempo = courant;
                courant = courant->fils;
                std::vector<_noeud*> tmp;//permet d'écraser l'ancien tmp pour repartir de zéro
            }
            else 
                courant = courant->frere;

        }
        newneuneu->bloc = CC;
        newneuneu->frere = NULL;
        newneuneu->fils = NULL;

<<<<<<< HEAD
=======

        vector<_noeud*>::iterator it =tmp.begin();

>>>>>>> d41b1ed36d9912e1033bceec29f38aedfaac19dc
        insertionMultiple(pereTempo, newneuneu, tmp);
        insertion(pereTempo,newneuneu);

    }
}


/**
    * @brief supprime un cube de l'arbre
    * @param CC un cube supposé présent dans l'arbre (sauf la table)
    *
    * supprime CC de la liste des fils de son père
    * et transmet ses fils à son père
*/
void arbrecubes::supprimer(const cube & CC){
    _noeud * pere = recherche(CC,true);
    _noeud * frereGauche = NULL;
    _noeud * courant = pere->fils;

    while(!(courant->bloc == CC)){//pas de condition null vu que le cube est présent
        frereGauche = courant;
        courant = courant->frere;
    }

    if(frereGauche == NULL)
        pere->fils = courant->frere;
    else
        frereGauche->frere = courant->frere;

    courant->frere = NULL; // opération non obligatoire
    _noeud * filsCourant = courant->fils;
    courant->fils = NULL;//opération non obligatoire

    _noeud * tmp;
    while(filsCourant !=NULL){
        tmp = filsCourant->frere;
        filsCourant->frere = NULL;
        insertion(pere, filsCourant);
        filsCourant = tmp;
    }


    delete(courant);
}


/**
    * @brief Donne le cube empilé le plus haut dont la projection au sol contient M
    * @param M un point (du plan)
    * @return un cube tel que M ne soit pas plus loin de centre() que cote()/2
    * @pre l'arbre de doit pas être vide et posséder au moins la "table"
*/
const cube arbrecubes::cubede(const point & M) const {
    //arbre supposé non vide
    _noeud * pereTempo;//sera toujours egale à racine à la premiere itération de la boucle
    _noeud * courant = _racine;
    while(courant != NULL){
        if(peutSupp(courant->bloc , M)){
            pereTempo = courant;
            courant = courant->fils;
        }
        else
            courant = courant->frere;
    }
    return pereTempo->bloc;
}

/**
    * @brief Donne l'altitude de la face supérieure du cubede(M)
    * @param M un point (du plan)
    * @return une altitude entière (somme des cote() des cubes empilés sous M)
    * @pre l'arbre de doit pas être vide et posséder au moins la "table"
*/
int arbrecubes::hauteur(const point & M) const {
    //arbre supposé non vide
    _noeud * pereTempo;//sera toujours egale à racine à la premiere itération de la boucle
    _noeud * courant = _racine;
    int hauteur = 0;
    while(courant != NULL){
        if(peutSupp(courant->bloc , M)){
            hauteur += courant->bloc.cote();
            pereTempo = courant;
            courant = courant->fils;
        }
        else
            courant = courant->frere;
    }
    return hauteur;

}

/**
    * @brief recherche d'un pointeur sur _noeud contenant le cube supposé present dans l'arbre, la methode retourne soit son pere, soit directement le _noeud
    * @param CC un cube supposé présent dans l'arbre
    * @param booleen retourPere, un booleen indiquand à la fonction si elle doit retourner le pere du _noeud* contenant le cube (true) ou directement le _noeud contenant CC (faux par defaut)
    * @return un pointeur sur un noeud correspondant au cube passé en paramètre
    * @pre CC doit se trouver dans l'arbre à la position qui lui correspond
*/
arbrecubes::_noeud* arbrecubes::recherche(const cube & CC, bool retourPere) const{
    _noeud * pere = NULL;
    _noeud * courant = _racine;

    bool trouve = false;
    while(!trouve){
        assert(courant !=NULL);
        if(courant->bloc == CC)
			trouve = true;

        else if(peutSupp(courant->bloc, CC)){
            pere = courant;
            courant = courant->fils;
        }
        else
            courant = courant->frere;
    }

    if(retourPere)
        return pere;
    else
        return courant;

}

/**
    * @brief permet de savoir si un cube peut supporter un autre cube, en fonction de leur taille et de leur position
    * @param C1, un cube quelconque
    * @param C2, un deuxieme cube quelconque
    * @return un booleen à vrai si C1 peut supporter C2, faux sinon
*/
bool arbrecubes::peutSupp(const cube & C1, const cube & C2 ) const{
	if(C1.cote()>C2.cote()){
		int limiteSupY(C1.centre().y + (C1.cote()-1)/2);
		int limiteInfY(C1.centre().y - (C1.cote()-1)/2);
		int limiteSupX(C1.centre().x + (C1.cote()-1)/2);
		int limiteInfX(C1.centre().x - (C1.cote()-1)/2);

		if(C2.centre().y<limiteSupY && C2.centre().y>limiteInfY && C2.centre().x<limiteSupX && C2.centre().x>limiteInfX)
			return true;
		else
			return false;
	}
	else
		return false;
}

/**
    * @brief permet de savoir si un cube peut supporter un point, en fonction de leur position
    * @param C1, un cube quelconque
    * @param M, un point quelconque
    * @return un booleen à vrai si C1 peut supporter le point, faux sinon
*/
bool arbrecubes::peutSupp(const cube & C1, const point & M ) const{
    int limiteSupY(C1.centre().y + (C1.cote()-1)/2);
    int limiteInfY(C1.centre().y - (C1.cote()-1)/2);
    int limiteSupX(C1.centre().x + (C1.cote()-1)/2);
    int limiteInfX(C1.centre().x - (C1.cote()-1)/2);

    if(M.y<limiteSupY && M.y>limiteInfY && M.x<limiteSupX && M.x>limiteInfX)
      return true;
	else
      return false;
}


/**
    * @brief insere une liste de vector de _noeud (supposé preent dans l'arbre), les supprime de leur ancien pere, et les ajoutes fils du nouveau pere
    * @param ancienPere, un pointeur sur un noeud
    * @param nouveauPere, un pointeur sur un noeud
    * @param vecteur contenant une liste de noeud *
    * @pre le vecteur doit être trié dans l'ordre des x, y,tout comme ceux de l'ancien pere
    * @pre tous les noeuds du vecteur doivent être un fils de l'ancien Pere
*/
void arbrecubes::insertionMultiple(_noeud * ancienPere, _noeud * nouveauPere, std::vector<_noeud*> fils){
    vector<_noeud*>::iterator it = fils.begin();
    _noeud * prec = NULL;
    _noeud * courant = ancienPere->fils;

    while(courant !=NULL && it != fils.end()){
        if(courant == (*it)){
            if(prec == NULL){
                ancienPere->fils = (*it)->frere;
                (*it)->frere = NULL;
                courant = ancienPere->fils;
            }
            else{
                prec->frere = (*it)->frere;
                (*it)->frere = NULL; // assure que le noeud ne soit plus présent
                courant = prec->frere;//prec ne correspond à aucun it
            }

            insertion(nouveauPere,(*it));
            it++;
        }
        else{
            prec = courant;
            courant = courant->frere;
        }
    }

}

/**
    * @brief insere un noeud comme fils d'un autre noeud (ne supprime pas l'ancien Pere si jamais le noeud était déjà present)
    * @param pere, un pointeur sur un noeud
    * @param fils, un pointeur sur un noeud
    * @pre le noeud à ajouter comme fils ne doit pas être déjà le frere ou le fils d'un autre noeud dans l'arbre
*/
void arbrecubes::insertion(_noeud * pere, _noeud * fils){

    _noeud * courant = pere->fils;

    if(courant == NULL)
        pere->fils = fils;
    else if(fils->bloc.centre() < courant->bloc.centre()){
        fils->frere = courant;
        pere->fils = fils;
    }
    else{
        _noeud * prec = courant;
        courant = courant->frere;

        while(courant != NULL && courant->bloc.centre()<fils->bloc.centre() ){
            prec = courant;
            courant = courant->frere;
        }

        fils->frere = courant;
        prec->frere = fils;

    }
}
