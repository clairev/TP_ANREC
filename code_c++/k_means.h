
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

	int number_data; 
	int dim_data; 
	int K; 
	int seed; // choix du hasard
	
	vector <vector <double > > datas;
	
	vector <vector <double > > means;
	vector <vector <double > > new_means;
	
	vector <list <int> > groups; 
	
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
