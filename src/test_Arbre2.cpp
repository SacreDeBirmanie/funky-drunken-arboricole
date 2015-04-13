#include <iostream>
#include "arbresCubes.cpp"

using namespace std;

//------------------------------------------------------------------------------
// Fonctionnalités de chronométrage
/**
 * @var chrono
 * @brief chronomètre du programme
**/
clock_t chrono;

/**
 * @def START
 * @brief démarre le chronomètre
**/
#define START chrono=clock()

/**
 * @def STOP
 * @brief arrête le chronomètre
**/
#define STOP chrono=clock()-chrono

/**
 * @def TEMPS
 * @brief donne le temps du chronomètre (après arrêt)
**/
#define TEMPS double(chrono)/CLOCKS_PER_SEC


//------------------------------------------------------------------------------
// Programme principal
int main()
{

	cout << "CONSTRUCTION" << endl;
	cout << "------------" << endl;
	START;
	ArbreCube AC("cubes.txt");
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;
	
	cout << "LISTAGE DES CUBES" << endl;
	cout << "------------" << endl;
	START;
		Vector<cube> liste = AC.dessus(AC.table());
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;
	
	cout << "AFFICHAGE DE LA LISTE DES CUBES" << endl;
	cout << "------------" << endl;
	START;
	for (auto c : liste )
	{
		cout << "centre : " << c.centre() << endl;
		cout << "cote : " << c.cote() << endl;
	}
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;
	
	cout << "SOUTIEN" << endl;
	cout << "------------" << endl;
	START;
	AC.soutien(liste[1]);
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;
	
	cout << "AJOUTER" << endl;
	cout << "------------" << endl;
	START;
	AC.ajouter(liste[1]);
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;
	
	cout << "SUPPRIMER" << endl;
	cout << "------------" << endl;
	START;
	AC.ajouter(liste[1]);
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;

	return 0;
}
