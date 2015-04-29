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
	string nomfic = "./FichiersTests/cubes10_4.txt";

	cout << "CONSTRUCTION" << endl;
	cout << "------------" << endl;
	START;
	arbrecubes AC(nomfic);
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;
	
	cout << "LISTAGE DES premier cube posé sur la table" << endl;
	cout << "------------" << endl;
	START;
	vector<cube> liste = AC.dessus(AC.table());
	vector<cube>::iterator it = liste.begin();
	for ( int i = 0; i < 100; i++ ){
		AC.dessus(AC.table());
	}
	for(it;it != liste.end(); it++)
		cout<<" coordonnée :"<<(*it).centre().x<<","<<(*it).centre().y <<"||"<<(*it).cote()<<endl;
		 
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;
	
	cout << "SOUTIEN" << endl;
	cout << "------------" << endl;
	START;
	cube soutien = AC.soutien(liste[1]);
	cout<<" le cube soutenant ["<<liste[1].centre().x<<","<<liste[1].centre().y <<"||"<<liste[1].cote()<<"]"<< "est :"<<endl;
	cout<<"["<<soutien.centre().x<<","<<soutien.centre().y <<"||"<<soutien.cote()<<"]"<<endl;	
	STOP;
	cout << ">>> Temps : " << TEMPS << "s" << endl << endl;

	cout << "SUPPRIMER" << endl;
	cout << "------------" << endl;
	double temps2 = 0;
	int cpt = 0;
	ifstream fic(nomfic.c_str());
   	assert(fic.is_open());
    	string ligne;
    	getline(fic,ligne);
	while(!fic.eof() && cpt < 1)
    	{
		stringstream ss(ligne);
		int x,y,largeur;
		ss >> x >> y >> largeur;
		point P(x,y);
		cube CC(P,largeur);
		START;
		AC.supprimer(CC);
		STOP;
		temps2 = temps2 + TEMPS;
		cpt = cpt + 1;
	}
	cout << ">>> Temps : " << temps2<< "s" << endl << endl;         
		getline(fic,ligne);	

	return 0;
}
