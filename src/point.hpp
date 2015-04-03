/**
 * @file point.hpp
 * @author D.Robbes
 * @since 01/05/2015
 * @brief Définition d'une classe points
 *
 * pas de fichier .cpp associé, tout est inclus ici
**/
#ifndef __point_HPP__
#define __point_HPP__

/**
 * @class point 
 * 
 * @brief Classe implémentant un point du plan à coordonnées entières
 *
 */
class point
{  public:
      					// attributs : abscisse et ordonnée
      	// ces attributs sont publics pour simplifier l'utilisation de la classe
	    int x,y;
     					 // méthodes
      /**
       * @brief Constructeur par défaut : l'origine du repère
       * @param n Le nom du produit
       * @param p Son poids
       * @param e Son étiquette
       */
	    point(){x=0;y=0;}
      /**
       * @brief Constructeur 
       * @param x l'abscisse
       * @param y l'ordonnée
       */
		point(int x,int y)
		     {this->x=x;this->y=y;}
};

#endif // __point_HPP__
