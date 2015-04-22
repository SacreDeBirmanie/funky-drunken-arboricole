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

int TAILLE = 1;// nombre d'étage de l'empilement des cubes
int MAXFILS = 9; //nombre total de cube posé sur chacun des blocs
int TAILLEDEPART = 6;//taille des plus petits cubes
int ECART = 3;//valeur de tous les ecarts entre les cubes sauf 1

int BLOCPARLIGNE;//nombrede bloc par ligne
int DERNIERECART; // valeur du dernier ECART pour avoir une taille paire 

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

int puissanceSuperieur(int nombre){
	return 0;
}

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

int calculDeLaBase(int numeroEtage){
	int resultat = TAILLEDEPART;
	for(int i = TAILLE; i>numeroEtage ; --i){
		resultat = ECART*(BLOCPARLIGNE) + (resultat * BLOCPARLIGNE) + DERNIERECART;
	}
	cout<<resultat<<"::"<<numeroEtage<<endl;
	return resultat;

}
 
int creationFILS(int etage, base laBase){
		int bornex = laBase.x - laBase.cote/2;
		int borney = laBase.y - laBase.cote/2;

		int ecartx = ECART;
		int ecarty = ECART;

	assert(etage<=TAILLE);
	int tailleCubeCourant = calculDeLaBase(etage);
	for(int i =1 ; i<=MAXFILS ; ++i){
		base cube = {bornex + ecartx + tailleCubeCourant/2 , borney + ecarty + tailleCubeCourant/2, tailleCubeCourant};

		ecrire(cube.x,cube.y , cube.cote);

		if((i%BLOCPARLIGNE) == 0){
			cout<<"x re"<<endl;
			ecarty = ecarty + ECART;
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
	string fdout;
	while (nb < argc) {
		cout<<(argv[nb])<<endl;
		ch = (argv[nb])[1]; // ne prend que la lettre aprèsle tiret
		cout<<"nb arg = "<<argc <<endl;
		if(nb+1 != argc)
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
					fdout = argv[nb+1];
					nouvelleSortie = true;
					break;
				case 'f' :
					if(verification(argv[nb+1])){
						MAXFILS = atoi(argv[nb+1]);
						break;
					}
					/*else
						exit(EXIT_FAILURE);*/
				case 'd' :
					if(verification(argv[nb+1])){
						TAILLEDEPART = atoi(argv[nb+1]);
						break;
					}
					/*else
						exit(EXIT_FAILURE);*/
				case 'e' :
					if(verification(argv[nb+1])){
						ECART = atoi(argv[nb+1]);
						break;
					}
					/*else
						exit(EXIT_FAILURE);*/
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

	if(!nouvelleSortie)
		fdout = "cubes"+to_string(MAXFILS)+"_"+to_string(TAILLE)+".txt";
	BLOCPARLIGNE = (int)ceil(sqrt(MAXFILS));
	DERNIERECART = 4 - (ECART*BLOCPARLIGNE)%2;

	sortie.open(fdout.c_str());
	cout<<"creation du fichier"<<endl;
	
	if(sortie){
		int BASETABLE = calculDeLaBase(0);
		base table = {0,0,BASETABLE};
			creationFILS(1,table);
		//melanger les lignes
		sortie.seekp(0, ios::beg);
		sortie<<to_string(table.x)+" "+ to_string(table.y)+" "+to_string(table.cote);
		cout<<"fichier crée"<<endl;
		sortie.close();
	}
	else
		cerr<<"Impossible d'ouvrir et de modifier le fichier !" << endl;
	
	return 0;
	
}