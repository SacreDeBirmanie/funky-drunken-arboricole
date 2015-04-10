/**
 * @file arbreCubes.hpp
 * @author D.Robbes
 * @since 01/05/2015
 * @brief Définition d'une classe de cube à poser (pas en 3D !)
 *
**/
#ifndef __arbrecubes_HPP__
#define __arbrecubes_HPP__

#include <string>
#include <vector>
#include "point.hpp"
#include "cube.hpp"

/**
 * @class arbrecubes 
 * 
 * @brief Classe implémentant un arbre de cubes empilés
 *
 */
class arbrecubes
{  private:
				// type pour les noeuds de l'arbre :
	     struct _noeud 
	        { 
	           cube bloc;        // le cube stocké dans ce noeud
	           _noeud * fils;    // la tête de la liste des cubes posés dessus
	           _noeud * frere;   // la suite de la liste des cubes posés sur le même père
	        };
	            // attribut : pointeur vers le sommet de l'arbre (la table)
	     _noeud * _racine;
	     	     
   public:
            // méthodes
      /**
       * @brief Constructeur, crée un arbre avec les cubes donnés dans un fichier
       * @param nomfic Le nom du fichier texte
       */
	arbrecubes(std::string nomfic);

      /**
       * @brief Accès au cube à la racine de l'arbre
       * @return le cube qui soutient tous les autres
       */
	const cube table() const {return _racine->bloc;}
	
      /**
       * @brief Donne la liste des cubes directement supportés par le paramètre
       * @param CC un cube supposé présent dans l'arbre
       * @return un vecteur de cubes ayant tous CC comme père
       */	
	std::vector<cube> dessus(const cube & CC) const;
	
      /**
       * @brief Donne le cube sur lequel est empilé le paramètre
       * @param CC un cube supposé présent dans l'arbre
       * @return le cube père de CC
       */	
	const cube soutien(const cube & CC) const;

      /**
       * @brief ajoute un cube dans l'arbre, à sa place
       * @param CC un cube à ajouter
       * 
       * ajoute CC dans la liste des fils du plus petit cube qui peut le supporter
       *    ( dans l'ordre ) 
       * et prend comme fils tous les cubes qu'il peut supporter
       */	
	void ajouter(const cube & CC);
	
      /**
       * @brief supprime un cube de l'arbre
       * @param CC un cube supposé présent dans l'arbre (sauf la table)
       * 
       * supprime CC de la liste des fils de son père
       * et transmet ses fils à son père
       */		
	void supprimer(const cube & CC);
	
      /**
       * @brief Donne le cube empilé le plus haut dont la projection au sol contient M 
       * @param M un point (du plan)
       * @return un cube tel que M ne soit pas plus loin de centre() que cote()/2
       */	
	const cube cubede(const point & M) const;

      /**
       * @brief Donne l'altitude de la face supérieure du cubede(M) 
       * @param M un point (du plan)
       * @return une altitude entière (somme des cote() des cubes empilés sous M) 
       */	
	int hauteur(const point & M) const;
	
	_noeud * recherche(const cube & CC) const;
	
	bool peutSupp(const cube & C1, const cube & C2 );
};

#endif // __arbrecubes_HPP__
