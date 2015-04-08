
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
vector<cube> arbrecubes::dessus(const cube & CC) const
    { 
        // à compléter
        // 
        // etape 1 : retrouver le cube
        
        _noeud * courant = _racine;
        bool trouve = false;
        while(!trouve){

          if(courant->cube == CC)
            trouve = true;

          else{
            point limiteSupG(courant->cube.centre().x - (courant->cube.cote()-1)/2 , courant->cube.centre().y + (courant->cube.cote()-1)/2);
            point limiteInfG(courant->cube.centre().x - (courant->cube.cote()-1)/2 , courant->cube.centre().y - (courant->cube.cote()-1)/2);
            point limiteSupD(courant->cube.centre().x + (courant->cube.cote()-1)/2 , courant->cube.centre().y + (courant->cube.cote()-1)/2);
            point limiteInfD(courant->cube.centre().x + (courant->cube.cote()-1)/2 , courant->cube.centre().y - (courant->cube.cote()-1)/2);
              if(CC.centre()>limiteSupG && CC.centre()>limiteInfG && CC.centre()>limiteSupD && CC.centre()>limiteInfD)
                courant = courant->fils;
              else
                courant = courant->frere;
            }

        }


        //etape 2 : créer le vecteur
        vector<cube> cubes; 
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
        if(_racine->cube == CC)
          return CC;
        else{

          _noeud * pere = _racine;
          _noeud * courant = _racine->fils;
          bool trouve = false;
          while(!trouve){

            if(courant->cube == CC)
              trouve = true;

            else{
              int limiteSupY(courant->cube.centre().y + (courant->cube.cote()-1)/2);
              int limiteInfY(courant->cube.centre().y - (courant->cube.cote()-1)/2);
              int limiteSupX(courant->cube.centre().x + (courant->cube.cote()-1)/2);
              int limiteInfX(courant->cube.centre().x + (courant->cube.cote()-1)/2);
                if(CC.centre().y<limiteSupY && CC.centre().y>limiteInfY && CC.centre().x<limiteSupX && CC.centre().x>limiteInfX){
                  pere = courant
                  courant = courant->fils;
                }
                else
                  courant = courant->frere;
              }

          }
          return pere->cube;
      }
        
    }

      /**
       * @brief ajoute un cube dans l'arbre, à sa place
       * @param CC un cube à ajouter
       * 
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
      bool trouve = false;
      bool sortir = false;

      _noeud * courant = _racine->fils;
      while(courant != NULL && trouve == false && sortir == false){
        if(courant->cube.cote()<CC.cote()){
          courant = courant->frere;
        }
        else{
          point limiteSupG(courant->cube.centre().x - (courant->cube.cote()-1)/2 , courant->cube.centre().y + (courant->cube.cote()-1)/2);
          point limiteInfG(courant->cube.centre().x - (courant->cube.cote()-1)/2 , courant->cube.centre().y - (courant->cube.cote()-1)/2);
          point limiteSupD(courant->cube.centre().x + (courant->cube.cote()-1)/2 , courant->cube.centre().y + (courant->cube.cote()-1)/2);
          point limiteInfD(courant->cube.centre().x + (courant->cube.cote()-1)/2 , courant->cube.centre().y - (courant->cube.cote()-1)/2);

          //fonctionne puisque les cubes sont censé pouvoir supporter la contrainte
          if(CC.centre()>limiteSupG && CC.centre()>limiteInfG && CC.centre()>limiteSupD && CC.centre()>limiteInfD){
              courant->ajouter(CC);
              trouve = true;
          }
          else if(CC.centre()<courant->cube.centre())//REVOIR cette sortie !!!!!!!
            sortir = true;
          else
            courant = courant->frere;

        }
      }

      if(trouve == false){
        newneuneu->bloc = CC;
        newneuneu->fils = _racine->fils; // TOUS les fils ????????????????
        newneuneu->pere = _racine;
      }

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
        // à compléter
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
