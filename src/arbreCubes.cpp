
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


std::vector<cube> arbrecubes::dessus(const cube & CC) const {
    _noeud * courant = recherche(CC);

    //etape 2 : créer le vecteur
    std::vector<cube> cubes;
    courant = courant->fils ;

    while(courant !=NULL){
        cubes.push_back(courant->bloc);
        courant = courant->frere;
    }
    return cubes;
}


const cube arbrecubes::soutien(const cube & CC) const {
    _noeud * cubeSoutien = recherche(CC,true);
    return cubeSoutien->bloc;

}


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
                tmp.clear();//permet d'écraser l'ancien tmp pour repartir de zéro
            }
            else 
                courant = courant->frere;

        }
        newneuneu->bloc = CC;
        newneuneu->frere = NULL;
        newneuneu->fils = NULL;

        vector<_noeud*>::iterator it =tmp.begin();

        insertionMultiple(pereTempo, newneuneu, tmp);
        insertion(pereTempo,newneuneu);

    }
}



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
    assert(pereTempo !=NULL);
    return pereTempo->bloc;
}


int arbrecubes::hauteur(const point & M) const {
    //arbre supposé non vide
    _noeud * courant = _racine;
    int sommeHauteur = 0;
    while(courant != NULL){
        if(peutSupp(courant->bloc , M)){
            sommeHauteur += courant->bloc.cote();
            courant = courant->fils;
        }
        else
            courant = courant->frere;
    }
    return sommeHauteur;

}


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
