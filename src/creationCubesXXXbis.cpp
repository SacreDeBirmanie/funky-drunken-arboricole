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
ofstream sortie;//fichier de sortie

int TAILLE = 3;// nombre d'étage de l'empilement des cubes
int MAXFILS = 9; //nombre total de cube posé sur chacun des blocs
int TAILLEDEPART = 6;//taille des plus petits cubes
int ECART = 3;//valeur de tous les ecarts entre les cubes sauf 1
int DERNIERECART = ECART + ((int)((sqrt(MAXFILS) *5 + (sqrt(MAXFILS)+1)*ECART))%2); // valeur du dernier ECART pour avoir une taille paire 

struct base{
	int x;
	int y;
	int cote;
};

char usage[] = "creationCubesXXX [-t taille] [-o output] [-h help] [...]" ;
char help[]  = "Parametres :\n"
  "-t TAILLE: indique la taille du fichier à générer (le fichier fera la taille indiqué puissance 9 par default) \n"
  "-f MAXFILS: indique le nombre de fils de chaque cube (doit avoir une racine carrée entière, 9 par default)\n"
  "-d TAILLEDEPART: indique la taille de départ des plus petits blocs (doit être divisible par deux)\n"
  "-e ECART: indique l'ecart entre chaque bloc (3 par default)\n"
  "-o output: la sortie du fichier \n"
  "-h help  : cette aide." ;

  //////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////FIN DES VARIABLES GLOBALES/////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////
  


//////////////////////////////////////////////////////////////////////////////////////
//**********************DELCARATION DES FONCTIONS GLOBALES**************************//
//////////////////////////////////////////////////////////////////////////////////////
void ecrire(int x, int y, int taille){
	string bloc = to_string(x)+" "+ to_string(y)+" "+to_string(taille);
	
	sortie<<bloc<<endl;
}

int valeurAbs(int nb){
	if(nb>=0)
		return nb;
	else
		return -nb;
}

bool verification(char* chaine){
	bool valeur = true;
	int i = 0;
	while (chaine[i] != '/0'){
		if(!isdigit(chaine[i]))
			valeur = false;
		i++;
	}

	return valeur;

}

int calculDeLaBase(int numeroEtage){
	int resultat = TAILLEDEPART;
	for(int i = TAILLE; i>numeroEtage ; ++i){
		resultat = ECART*(sqrt(MAXFILS)) + (resultat * sqrt(MAXFILS)+1) + DERNIERECART;
	}
	return resultat;

}
 
int creationFILS(int etage, base laBase){
		int bornex = laBase.x - laBase.cote;
		int borney = laBase.y - laBase.cote;

		int ecartx = 3;
		int ecarty = 3;

	assert(etage<=TAILLE);

	for(int i =0 ; i<MAXFILS ; ++i){
		base cube = {bornex + ecartx, borney + ecarty, calculDeLaBase(etage)};

		ecrire(cube.x,cube.y , cube.cote);

		ecartx = ecartx + cube.cote + ECART;

		if(i%(int)sqrt(MAXFILS) == 0)
			ecarty = ecarty + ECART;

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
	string fdout = "cubes"+to_string(MAXFILS)+"_"+to_string(TAILLE)+".txt";

	char ch;
	int nb = 1;
	ifstream fichier("cubes.txt", ios::out);
	
	while (nb < argc) {
		ch = (argv[nb])[0];
		if(nb+1 != argc)
			switch(ch) {
				case 't' :
					if(verification(argv[nb+1]))
						TAILLE = atoi(argv[nb+1]);
					else
						exit(EXIT_FAILURE);
				case 'o' :
					fdout = argv[nb+1];
				case 'f' :
					if(verification(argv[nb+1]))
						MAXFILS = atoi(argv[nb+1]);
					else
						exit(EXIT_FAILURE);
				case 'd' :
					if(verification(argv[nb+1]))
						TAILLEDEPART = atoi(argv[nb+1]);
					else
						exit(EXIT_FAILURE);
				case 'e' :
					if(verification(argv[nb+1]))
						ECART = atoi(argv[nb+1]);
					else
						exit(EXIT_FAILURE);
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
	}

	sortie.open(fdout.c_str());
	
	if(sortie){
		int BASETABLE = calculDeLaBase(0);
		base table = {0,0,BASETABLE};
		for(int numero = 1; numero<=(MAXFILS) ; ++numero){
			creationFILS(1,table);
		}
		//melanger les lignes
		ecrire(table.x,table.y,table.cote);
		
		sortie.close();
	}
	else
		cerr<<"Impossible d'ouvrir et de modifier le fichier !" << endl;
	
	return 0;
	
}
