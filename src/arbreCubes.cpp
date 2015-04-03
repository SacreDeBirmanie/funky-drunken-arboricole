
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
        vector<cube> cubes; 
        _noeud * courant = CC.fils ;
        
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
        return CC.pere->bloc;
        
    }

      /**
       * @brief ajoute un cube dans l'arbre, à sa place
       * @param CC un cube à ajouter
       * 
       * ajoute CC dans la liste des fils du plus petit cube qui peut le supporter
       *    ( dans l'ordre ) 
       * et prend comme fils tous les cubes qu'il peut supporter
       */	
void arbrecubes::ajouter(const cube & CC)
    { 
        // à compléter
        if(_racine == NULL){
			_noeud * newneuneu;
			
			newneuneu->bloc = CC;
			newneuneu->fils = NULL;
			newneuneu->pere = NULL;
			
			_racine =  newneuneu;
		}
		else{
			//regarder si le cube n'est pas déjà present
			//parcourir les fils tant que CC.x < filsCourant.x
			//puis parcourir tant que CC.y < filsCourant.y
			
			//vérifier que CC a la place de s'insérer
				/------->si oui, l'inserer !
				/------->si non
		
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
