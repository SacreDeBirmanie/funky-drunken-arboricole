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
		
	/**
	 * @brief redéfinition de l'operator inferieur en fonction de la valeur de x, ou de la valeur de y si les x des deux points sont égaux
	 * @param point p2, le point qui sera comparé à this
	 * @return un booléen vraie si les coordonnées du point this est inférieur aux coordonnées du point entré en paramètre
	*/
	bool operator<(const point & p2) const{
            if(x == p2.x)
                  return y<p2.y;
            else
                  return x<p2.x;
	}

	/**
	 * @brief redéfinition de l'operator superieur en fonction de la valeur de x, ou de la valeur de y si les x des deux points sont égaux
	 * @param point p2, le point qui sera comparé à this
	 * @return un booléen vraie si les coordonnées du point this est inférieur aux coordonnées du point entré en paramètre
	*/
	bool operator>( const point & p2) const{
		if(x == p2.x)
                	return y>p2.y;
            	else
                	return x>p2.x;
	}

	/**
	 * @brief redéfinition de l'operator égalité en fonction de la valeur de x et de y
	 * @param point p2, le point qui sera comparé à this
	 * @return un booléen à vraie si les coordonnées x et y des deux points sont égaux, faux sinon
	*/
	bool operator==( const point & p2) const {
		return (x == p2.x && y == p2.y);
	}
};

#endif // __point_HPP__
