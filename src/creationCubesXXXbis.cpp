#include <iostream>
#include <fstream>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include <time.h>
#include <assert.h>
#include <string>
#include <math.h> 
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cctype>
#include <cstring>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////****DELCARATION DES VARIABLES GLOBALES****///////////////////
//////////////////////////////////////////////////////////////////////////////////////
///
ofstream sortieEcriture;//fichier de sortieEcriture ouvert en écriture

int TAILLE = 9;// nombre d'étage de l'empilement des cubes
int MAXFILS = 2; //nombre total de cube posé sur chacun des blocs
int TAILLEDEPART = 6;//taille des plus petits cubes (ceux empiler au dernier etage)
int ECART = 3;//valeur de tous les ecarts entre les cubes sauf 1

int BLOCPARLIGNE;//nombre de bloc par ligne
int DERNIERECART; // valeur du dernier ECART pour avoir une taille paire et ainsi diviser facilement la taille par deux

struct base{
	int x;
	int y;
	int cote;
};

char usage[] = "creationCubesXXX [-t taille] [] [-o output] [-h help] [...]" ;
char help[]  = "Parametres :\n"
  "-t TAILLE: indique la taille du fichier à générer (le fichier fera la somme de h=0 à TAILLE de 9 puissance h, par default) \n"
  "-f MAXFILS: indique le nombre de fils de chaque cube ( 9 par default)\n"
  "-d TAILLEDEPART: indique la taille de départ des plus petits blocs\n"
  "-e ECART: indique l'ecart entre chaque bloc (3 par default)\n"
  "-o output: la sortieEcriture du fichier \n"
  "-h help  : cette aide." ;

  //////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////FIN DES VARIABLES GLOBALES/////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////
  


//////////////////////////////////////////////////////////////////////////////////////
//**********************DELCARATION DES FONCTIONS GLOBALES**************************//
//////////////////////////////////////////////////////////////////////////////////////


/**
    * @brief ecrit sur la sortie fdout les paramètres séparé d'un espace
    * @param x, un entier x (correspondant à une position x d'un cube)
    * @param y, un entier y (correspondant à une position y d'un cube)
    * @param taille, un entier x (correspondant à la taille d'un cube)
*/
void ecrire(int x, int y, int taille){
	string bloc = to_string(x)+" "+ to_string(y)+" "+to_string(taille);
	
	sortieEcriture<<bloc<<endl;
}


/**
    * @brief permet de vérifier qu'une chaine de caractère est bien un nombre entier
    * @param chaine, la chaine de caractère à vérifier
    * @return un booleen à vrai si la chaine peut être transformer en nombre entier, faux sinon
*/
bool verification(char* chaine){
	bool valeur = true;
	int i = 0;
	while (chaine[i] != '\0'){
		if(!isdigit(chaine[i]))
			valeur = false;
		i++;
	}

	return valeur;

}


/**
    * @brief permet de calculer la taille du cube à une certaine hauteur
    * @param entier numeroEtage, la hauteur du cube dont la base doit être calculé, en fonction du nombre de fils, des ecarts et de la taille de depart
    * @return entier resultat, la taille du cube à l'étage passé en paramètre
*/
int calculDeLaBase(int numeroEtage){
	int resultat = TAILLEDEPART;
	for(int i = TAILLE; i>numeroEtage ; --i){
		resultat = ECART*(BLOCPARLIGNE) + (resultat * BLOCPARLIGNE) + DERNIERECART;
	}
	return resultat;

}


/**
    * @brief permet de crée recursivement des empilement de bloc
    * @param entier etage, l'étage du cube
    * @param base labase, le cube sur lequel seront empilé les blocs de l'étage courant
*/
int creationFILS(int etage, base laBase){
		int bornex = laBase.x - laBase.cote/2;
		int borney = laBase.y + laBase.cote/2;

		int ecartx = ECART;
		int ecarty = ECART;

	assert(etage<=TAILLE);
	int tailleCubeCourant = calculDeLaBase(etage);
	for(int i =1 ; i<=MAXFILS ; ++i){
		base cube = {bornex + ecartx + tailleCubeCourant/2 , borney - ecarty - tailleCubeCourant/2, tailleCubeCourant};

		ecrire(cube.x,cube.y , cube.cote+1);

		if((i%BLOCPARLIGNE) == 0){
			ecarty = ecarty + cube.cote + ECART;
			ecartx = ECART;
		}
		else
			ecartx = ecartx + cube.cote + ECART;

		if(etage!=TAILLE)
			creationFILS(etage+1,cube);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////FIN DES FONCTIONS GLOBALES/////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////
//*********************************PROGRAMME PRINCIPAL*********************************//
/////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

	char ch;
	int nb = 1;
	bool nouvelleSortie = false;
	string fdout,fdout2;
//////////////////recuperation des arguments passés à la fonction////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (nb < argc) {
		ch = (argv[nb])[1]; // ne prend que la lettre après le tiret
		if(nb+1 != argc || ch =='h')
			switch(ch) {
				case 't' :
					if(verification(argv[nb+1])){
						cout<<"taille enregistre"<<endl;
						TAILLE = atoi(argv[nb+1]);
						break;
					}
					/*else
						exit(EXIT_FAILURE);*/
				case 'o' :
					fdout2 = argv[nb+1];
					fdout2 = "./FichiersTests/"+fdout2;
					nouvelleSortie = true;
					break;
				case 'f' :
					if(verification(argv[nb+1])){
						MAXFILS = atoi(argv[nb+1]);
						break;
					}
				case 'd' :
					if(verification(argv[nb+1])){
						int tmp = atoi(argv[nb+1]);
						if(tmp%2 ==0)
							TAILLEDEPART =tmp ;
						else{
							TAILLEDEPART = tmp+1;
							cout<<"la taille de départ à été augmenté de 1 pour avoir une taille paire "<<tmp<<"=>"<<TAILLEDEPART<<endl;
						}
						break;
					}
				case 'e' :
					if(verification(argv[nb+1])){
						ECART = atoi(argv[nb+1]);
						break;
					}
				case 'h' :
		      		cout<<usage<<endl<<help<<endl;
		      		exit(EXIT_SUCCESS);
		      		break ;
					
				default :
					perror("ARGUMENTS INVALIDES, SORTIE DU PROGRAMME \n");
					cout<<usage<<endl;
					exit(EXIT_FAILURE);
				
			}
		else{
			perror("NOMBRE D'ARGUMENTS INVALIDES \n");
			exit(EXIT_FAILURE);
		}
		nb = nb +2;
	}
//////////////////fin de la recuperation des arguments passés à la fonction////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

	if(!nouvelleSortie)//si aucune nouvelle sortie n'a été donnée en argument
		fdout2 = "./FichiersTests/cubes"+to_string(MAXFILS)+"_"+to_string(TAILLE)+".txt";

	fdout = "cubes"+to_string(MAXFILS)+"_"+to_string(TAILLE)+".tmp.txt";

	BLOCPARLIGNE = (int)ceil(sqrt(MAXFILS));//donne le nombre de bloc max par ligne
	DERNIERECART = 4 - (ECART*BLOCPARLIGNE)%2;//calcul le dernier ecart

	sortieEcriture.open(fdout.c_str());
	cout<<"creation du fichier"<<endl;

//////////////////creation de l'arbre////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(sortieEcriture){//le fichier a bien été ouvert
		int BASETABLE = calculDeLaBase(0);
		base table = {0,0,BASETABLE};
		ecrire(table.x,table.y,table.cote+1);//on ecrit sur la premiere ligne la table
		creationFILS(1,table);//on crée récursivement les cubes
		sortieEcriture.close();//on ferme le fichier puisque tous les bloc ont été ecrits
		cout<<"l'Arbre a été crée"<<endl;

		cout<<"debut du mélange du fichier"<<endl;

		system(("bash melange.sh "+fdout+" "+fdout2).c_str());//execute le script bash pour melanger les lignes aléatoirement (en gardant la table en premiere ligne)

		cout<<"melange termine"<<endl;
	}
	else
		cerr<<"Impossible d'ouvrir et de modifier le fichier !" << endl;
	
	return 0;
	
}
