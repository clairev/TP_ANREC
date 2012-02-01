#include <iostream>
#include "k_means.h";



// distances possibles à utiliser dans le main

double norm_l1 (vector <double > a, vector <double >b) {
	if (a.size() != b.size() ) {
		cerr << "incompatible sizes \n";
		return 0;
	}
	double dist = 0;
	for (int i = 0; i < a.size(); i++) {
		dist += fabs(a[i]-b[i]);
	}
	return dist;
}

double norm_l2 (vector <double > a, vector <double >b) {
	if (a.size() != b.size() ) {
		cerr << "incompatible sizes \n";
		return 0;
	}
	double dist = 0;
	for (int i = 0; i < a.size(); i++) {
		dist += pow(a[i]-b[i],2);
	}
	return sqrt(dist);
}

double norm_linf (vector <double > a, vector <double >b) {
	if (a.size() != b.size() ) {
		cerr << "incompatible sizes \n";
		return 0;
	}
	double dist = 0;
	for (int i = 0; i < a.size(); i++) {
		if (fabs(a[i]-b[i])>dist)
			dist = fabs(a[i]-b[i]);
	}
	return dist;
}




int main (int argc, char * const argv[]) {
	int k, dim_data, seed, n_skipped, type;
	
	if (argc>5)
    {
		k=atoi(argv[1]);
		dim_data=atoi(argv[2]);
		seed=atoi(argv[3]);
		n_skipped= atoi(argv[4]);
		type = atoi(argv[5]);
	}
	
	else {
		cerr << "Usage : k dim_data seed n_skipped type_similarité < in_file > out_file \n";
		return 0;
	}
	
	
	K_means test = K_means(dim_data,k,seed);
	
	test.read_datas(0);
	
	
	if (type==2) {
	test.get_means(norm_l2);
	}
	else if (type==1) {
		test.get_means(norm_l1);
	}
	
	else if (type==0) {
		test.get_means(norm_linf);
	}
	
	else {
		cerr << "please enter a type \n";
		return 0;
	}
	
	test.print_means();
	
	return 0;
	
}
