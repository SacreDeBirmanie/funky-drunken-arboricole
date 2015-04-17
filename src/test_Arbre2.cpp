#include <iostream>
#include <ctime>
#include "arbreCubes.cpp"

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
	//String fichier = new String();
	arbrecubes AC("cubes.txt");
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;
	
	cout << "LISTAGE DES premier cube posé sur la table" << endl;
	cout << "------------" << endl;
	START;
		vector<cube> liste = AC.dessus(AC.table());
		vector<cube>::iterator it = liste.begin();
		
		for(it;it != liste.end(); it++)
			cout<<" coordonnée :"<<(*it).centre().x<<","<<(*it).centre().y
								<<"||"<<(*it).cote()<<endl;
		 
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;
	
	cout << "AFFICHAGE DE TOUS LES CUBES" << endl;
	cout << "------------" << endl;
	START;
		//afficherTousLesCubes();
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;
	
	cout << "SOUTIEN" << endl;
	cout << "------------" << endl;
	START;
		cube soutien = AC.soutien(liste[1]);
		cout<<" le cube soutenant ["<<liste[1].centre().x<<","<<liste[1].centre().y
								<<"||"<<liste[1].cote()<<"]"<< "est :"<<endl;
		cout<<"["<<soutien.centre().x<<","<<soutien.centre().y
								<<"||"<<soutien.cote()<<"]"<<endl;
		
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
