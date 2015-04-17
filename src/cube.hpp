/**
 * @file cube.hpp
 * @author D.Robbes
 * @since 01/05/2015
 * @brief Définition d'une classe de cube à poser (pas en 3D !)
 *
 * pas de fichier .cpp associé, tout est inclus ici
**/
#ifndef __cube_HPP__
#define __cube_HPP__

/**
 * @class cube 
 * 
 * @brief Classe implémentant un cube à coordonnées entières des sommets
 * 
 * 
 */
class cube
{   private:             // attributs : centre et distance du centre aux faces
              point milieu; int demiCote;		
	public:
	        // méthodes
		/**
		 @brief Constructeur par défaut
		*/
	    cube(){ 
	        point dede(0,0);
	        milieu = dede;
	         demiCote = 1; 
	    };
	    
		/**
		* @brief Constructeur 
		* @param c le centre du cube
		* @param cote la longueur d'une arête (supposée impaire)
		*/        
		cube(point c,int cote){milieu=c;demiCote=cote/2;}
		
		/**
		* @brief Accès au centre du cube
		* @return le point au centre du cube 
		*/
		const point centre() const {return milieu;}
		
		/**
		* @brief Accès à la dimension du cube
		* @return la longueur d'une arête 
		*/
		int cote() const {return 2*demiCote+1;}
		
		/**
		 * @brief redéfintion de l'opérateur égalité comparant les coordonnées et la longueur des deux cubes
		 * @param cube c2, le cube qui sera comparé avec this
		 * @return un booléen à vraie si les points deux deux cubes sont égaux ainsi que leur demi-cote, faux sinon
		*/
        bool operator==(const cube & c2){
            return ((milieu == c2.milieu) && (demiCote == c2.demiCote));
		}
};

#endif // __cube_HPP__
