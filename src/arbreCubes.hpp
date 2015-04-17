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
 
	private :
	/**
       * @brief recherche d'un pointeur sur _noeud contenant le cube supposé present dans l'arbre, la methode retourne soit son pere, soit directement le _noeud
       * @param CC un cube supposé présent dans l'arbre 
       * @param booleen retourPere, un booleen indiquand à la fonction si elle doit retourner le pere du _noeud* contenant le cube (true) ou directement le _noeud contenant CC (faux par defaut)
       * @return un pointeur sur un noeud
    */	
	_noeud* recherche(const cube & CC, bool retourPere=false) const;
	
	/**
       * @brief permet de savoir si un cube peut supporter un autre cube, en fonction de leur taille et de leur position
       * @param C1, un cube quelconque
       * @param C2, un deuxieme cube quelconque
       * @return un booleen à vrai si C1 peut supporter C2, faux sinon 
       */	
	bool peutSupp(const cube & C1, const cube & C2 ) const;
	
	/**
       * @brief permet de savoir si un cube peut supporter un point, en fonction de leur position
       * @param C1, un cube quelconque
       * @param M, un point quelconque
       * @return un booleen à vrai si C1 peut supporter le point, faux sinon 
       */		
    bool peutSupp(const cube & C1, const point & M ) const;
	
	/**
       * @brief insere une liste de vector de _noeud (supposé preent dans l'arbre), les supprime de leur ancien pere, et les ajoutes fils du nouveau pere 
       * @param ancienPere, un pointeur sur un noeud
       * @param nouveauPere, un pointeur sur un noeud
       * @param vecteur contenant une liste de noeud *
       * @pre le vecteur doit être trié dans l'ordre des x, y
       * @pre tous les noeuds du vecteur doivent être un fils de l'ancien Pere
       */	
    void insertionMultiple(_noeud * ancienPere, _noeud * nouveauPere, std::vector<_noeud*> fils);
	
	/**
       * @brief insere un noeud comme fils d'un autre noeud (ne supprime pas l'ancien Pere si jamais le noeud était déjà present) 
       * @param pere, un pointeur sur un noeud
       * @param fils, un pointeur sur un noeud
       * @pre le noeud à ajouter comme fils ne doit pas être déjà le frere ou le fils d'un autre noeud dans l'arbre
       */	
    void insertion(_noeud * pere, _noeud * fils);
};

#endif // __arbrecubes_HPP__
