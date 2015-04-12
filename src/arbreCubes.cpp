
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include "arbrecubes.hpp"

/**
 * @file arbreCubes.cpp
 * @author D.Robbes
 * @since 01/05/2015
 * @brief implémentation des méthodes de la classe arbrecubes
 *
**/
#include "arbrecubes.hpp"

 using namespace std;

      /**
       * @brief Constructeur, crée un arbre avec les cubes donnés dans un fichier
       * @param nomfic Le nom du fichier texte
       */
       arbrecubes::arbrecubes(std::string nomfic)
       {   _racine=NULL;
           ifstream fic(nomfic);
           assert(fic.is_open());
           string ligne;
           getline(fic,ligne);
           while(!fic.eof())
             {         cout <<"   "<< "j'ai lu " << ligne << endl;
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
       std::vector<cube> arbrecubes::dessus(const cube & CC) const
       { 
        // à compléter
        // 
        // etape 1 : retrouver le cube


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

      /**
       * @brief Donne le cube sur lequel est empilé le paramètre
       * @param CC un cube supposé présent dans l'arbre
       * @return le cube père de CC
       */	
       const cube soutien(const cube & CC) const
       { 
        // à compléter
          return recherche(CC,true);


       /* if(_racine->cube == CC)
          return CC;
      else{

          _noeud * pere = _racine;
          _noeud * courant = _racine->fils;
          bool trouve = false;
          while(!trouve){

            if(courant->cube == CC)
              trouve = true;

          else{
              if(peutSupp(courant->cube, CC)){
                pere = courant
                courant = courant->fils;
            }
            else
                courant = courant->frere;
        }

       }
        return pere->cube;
      }*/

}

/**
    * @brief ajoute un cube dans l'arbre, à sa place
    * @param CC un cube à ajouter 
    * ajoute CC dans la liste des fils du plus petit cube qui peut le supporter
    *    ( dans l'ordre ) 
    * et prend comme fils tous les cubes qu'il peut supporter
*/	
    void arbrecubes::ajouter(const cube & CC){ 
        // à compléter
        _noeud * newneuneu;
        if(_racine == NULL){

            newneuneu->bloc = CC;
            newneuneu->fils = NULL;
            newneuneu->pere = NULL;

            _racine =  newneuneu;
        }
        else{
            std::vector<_noeud *> tmp;

            _noeud * pereTempo = _racine;
            _noeud * courant = _racine->fils;
            while(courant != NULL){
                if(courant->cube.cote()<CC.cote()){//a regrouper dans la fonction peutSupp
                    if(peutSupp(CC , courant->cube))
                        tmp.push_back(courant);

                    courant = courant->frere;
                }
                else if(peutSupp(courant->cube, CC)){
                    pereTempo = courant;
                    courant = courant->fils;
                    std::vector<_noeud *> tmp;//permet d'écraser l'ancien tmp pour repartir de zéro
                }
                    //SORTIE ??
                }
                else
                    courant = courant->frere;

            }

            newneuneu->bloc = CC;
            inserer(pereTempo, newneuneu, tmp);
            inserer(pereTempo,newneuneu);
            newneuneu->pere = courant;

        }
    }


      /**
       * @brief supprime un cube de l'arbre
       * @param CC un cube supposé présent dans l'arbre (sauf la table)
       * 
       * supprime CC de la liste des fils de son père
       * et transmet ses fils à son père
       */		
       void arbrecubes::supprimer(const cube & CC)
       { 
        noeud * pere = recherche(CC,true);
        _noeud * frereGauche = NULL;
        courant = pere->fils;

        _noeud * tmp;

        while(courant->cube != CC){//pas de condition null vu que le cube est présent
          frereGauche = courant;
          courant = courant->frere;
        }

        if(frereGauche == NULL)
          pere->fils = courant->fere;
        else
          frereGauche->frere = courant->frere;

        courant->frere = NULL; // opération non obligatoire
        _noeud * filsCourant = courant->fils;
        courant->fils = NULL;//opération non obligatoire

        while(filsCourant !=NULL)
          inserer(pere, filsCourant);

        delete(courant);
       }


      /**
       * @brief Donne le cube empilé le plus haut dont la projection au sol contient M 
       * @param M un point (du plan)
       * @return un cube tel que M ne soit pas plus loin de centre() que cote()/2
       */	
       const cube arbrecubes::cubede(const point & M) const 
       { 
        // à compléter
       }

      /**
       * @brief Donne l'altitude de la face supérieure du cubede(M) 
       * @param M un point (du plan)
       * @return une altitude entière (somme des cote() des cubes empilés sous M) 
       */	    
       int arbrecubes::hauteur(const point & M) const 
       { 
        // à compléter
       }

       _noeud * arbrecubes::recherche(const cube & CC, bool retourPere=false) const{
        _noeud * pere = NULL;
        _noeud * courant = _racine;
        bool trouve = false;
        while(!trouve){

          if(courant->cube == CC)
            trouve = true;

        else{
         if(peutSupp(courant->cube, CC){
            pere = courant;
            courant = courant->fils;
            else
              courant = courant->frere;
      }

      if(retourPere)
        return pere;
      else
        return courant;
  }
}

bool arbrecubes::peutSupp(const cube & C1, const cube & C2 ){
    int limiteSupY(C1.centre().y + (C1.cote()-1)/2);
    int limiteInfY(C1.centre().y - (C1.cote()-1)/2);
    int limiteSupX(C1.centre().x + (C1.cote()-1)/2);
    int limiteInfX(C1.centre().x - (C1.cote()-1)/2);

    if(C2.centre().y<limiteSupY && C2.centre().y>limiteInfY && C2.centre().x<limiteSupX && C2.centre().x>limiteInfX)
      return true;
  else
      return false;
}

//le vecteur doit être trié dans l'ordre 
void inserer(_noeud * ancienPere, _noeud * nouveauPere, std::vector<_noeud> fils){
    vector<int>::iterator it = fils.begin();
    _noeud * prec = NULL;
    noeud * courant = ancienPere->fils;

    while(courant !=NULL && it != fils.end()){
        if(courant == *it){
            if(prec == NULL){
                ancienPere->fils = *it->frere;
                courant = ancienPere->fils;
            }
            else{
                prec->frere = courant->frere;
                courant->frere = NULL; // assure que le noeud ne soit plus présent
                courant = prec->frere;//prec ne correspond à aucun it
            }

            inserer(*it);
            it++;
        }
        else{
            prec = courant;
            courant = courant->frere;
        }
    }

}

void inserer(_noeud * pere, _noeud * fils){

    _noeud * courant = pere->fils;

    if(courant == NULL)
        pere->fils = fils;
    else if(courant->cube.centre() >fils->cube.centre()){
        fils->frere = courant;
        pere->fils = fils;
    }
    else{
        while(courant->frere != NULL && courant->frere->cube.centre()<fils->cube.centre() ){
            courant = courant->frere;
        }

    fils->frere = courant->frere;
    courant->frere = fils;

    }
}