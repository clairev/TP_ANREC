
#include "k_means.h"



K_means::K_means (int Dim_data, int k, int Seed) {
	dim_data = Dim_data;
	K=k;
	seed=Seed;
	srand(seed); // initialise les nombres aléatoires
	number_data=1000;	// sera mis à jour lors de la lecture des données
	datas = vector < vector <double > > (number_data, vector <double> (dim_data, 0));
	means = vector < vector <double> > (K, vector <double> (dim_data, 0));
	new_means = vector < vector <double> > (K, vector <double> (dim_data, 0));
	groups = vector < list < int > > (K, list <int> () );
}


void K_means::read_datas(int n_skipped) {
	
	// sauter n_skipped lignes
	
	char buffer[100];
	for (int i =0; i < n_skipped; i++)
	fgets(buffer, 100, stdin);
	
	
	double dum;
	number_data = 0;
	bool end_reached=false;
	
	while (!end_reached) {
		for (int j = 0; j < dim_data; j++) {
			if (fscanf(stdin,"%lf",&dum)!=EOF) {
				datas[number_data][j] = dum;
	//			cout << "i just read " << dum << "\n";
			}
			else end_reached= true;
		}
		number_data++;
	//	cout << "#" << number_data << endl;
		if (number_data == datas.size()) {
	//		cout << "resizing \n";
			datas.resize(2*number_data, vector < double > (dim_data,0));
	}
	}
	number_data--;
	datas.resize(number_data);
	
	
	for (int i = 0; i < number_data; i++) {
		for (int j = 0; j < dim_data; j++) {
	//	cout << datas[i][j] << " ";
		}
	//	cout << endl;
	}
}

void K_means::get_means(double (* get_dist) (vector<double>,vector<double>)) {
	init_means();
	double dist = 100;
	int n_try = 0;
	while (dist > 1e-8 && n_try <= 10000) {
		update_groups(get_dist);
		dist = update_means(get_dist);
		n_try++;
	}
	if (n_try==10000) { cerr << "warning, not converged \n";}
}

void K_means::print_means() {
	for (int i = 0; i < K; i++) {
		std::list<int>:: const_iterator iterator;
		for (iterator = groups[i].begin(); iterator != groups[i].end(); ++iterator) {
			for (int j = 0; j < dim_data; j++) {
				cout << datas[(* iterator)][j] << " ";
			}
			cout << endl;
		}
		if (i < K-1) cout << endl;
	}
}
	

	
void K_means::init_means() {
	if (K> number_data) {
		cerr << "too few datas \n";
		return;
	}
	else {
		vector < int > choosen_data (number_data, 0);
		int n_found = 0;
		while (n_found < K) {
			int i = rand()%number_data;
			if (choosen_data[i]==0) { // si pas encore choisi
				choosen_data[i] = 1;
				means[n_found] = datas[i];
				n_found ++;
			}
			else; // sinon on ne fait rien
		}
	}
}

void K_means::update_groups( double (* get_dist) (vector<double>,vector<double>) ) {
	
	for (int j = 0; j<K; j++) {
		groups[j].clear();
	}
	
	for (int i = 0; i < number_data; i++) {
		double dist = get_dist(datas[i],means[0]);
		int nearest = 0;
		double val_nearest = dist;
		for (int j = 1; j < K; j++) {
			dist = get_dist(datas[i],means[j]);
			if (dist < val_nearest) {
				nearest =j;
				val_nearest=dist;
			}
		}
		groups[nearest].push_back(i);
	}
}



double K_means::update_means( double (* get_dist) (vector<double>,vector<double>) ) {
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < dim_data; j++) {
			new_means[i][j]=0;
		}
		// on parcourt chaque groupe (liste de numéros de datas) pour déterminer sa moyenne
		std::list<int>:: const_iterator iterator;
		for (iterator = groups[i].begin(); iterator != groups[i].end(); ++iterator) {
			for (int j = 0; j < dim_data; j++) {
				new_means[i][j] += datas[(* iterator)][j];
			}
		}
		for (int j = 0; j < dim_data; j++) {
			new_means[i][j] /= groups[i].size();
		}
	}
	double dist = 0;
	for (int i = 0; i < K; i++) {
		dist += get_dist(means[i], new_means[i]);
	}
	
	for (int i = 0; i < K; i++) {
		means[i] = new_means[i];
	}
	
	return dist;
	
}
