
# ifndef k_means
# define k_means 


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <list>


//for the file handler
#include <string>
#include <fstream>
#include <sstream>

//for the file name out put system
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

class K_means {
	public :

	int number_data; //nb de lignes du fichier de données
	int dim_data; // nb de colonnes dans le fichier de données
	int K; // nb de clusters (représentants)
	int seed; // pour les nombres aléatoires 
	
	vector <vector <double > > datas;
	
	vector <vector <double > > means;
	vector <vector <double > > new_means;
	
	vector <list <int> > groups; // vecteur de k-listes où les entiers sont les numéros de ligne des valeur
	
	K_means(int Dim_data, int k, int Seed);
	void read_datas(int n_skipped); // read from standard input
	
	void get_means(double (* get_dist) (vector<double>,vector<double>));
	void print_means();
	
	void init_means();	// initialise les représentants de chaque classe, au hasard
	void update_groups( double (* get_dist) (vector<double>,vector<double>) );	// affecte chaque donnée au groupe le plus proche;
	// prend la fonction get_dist en paramètre
	double update_means(  double (* get_dist) (vector<double>,vector<double>) );	// calcule les moyennes de chaque groupe
	
	
};

#endif
