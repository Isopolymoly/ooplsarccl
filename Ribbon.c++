// ----------------------------
// projects/ribbon/Ribbon.c++
// Copyright (C) 2015
// based on Collatz.c++ by Glenn P. Downing
// ----------------------------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <cstring>   // std::strcpy
#include <utility>  // make_pair, pair
#include <algorithm>  // so 198199
#include <limits>
#include <deque>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;
using std::vector;
//using std::map;
//using std::unordered_map;
//
//

// mod_chunk
int mod_chunk(int chunk, vector<int> factors) {
	int pieces = 0;
	int remainder;

	for (unsigned int i=0; i<factors.size(); ++i){

		cout << "mod_chunk factors[" << i << "]: " << factors[i] << endl;

		remainder = chunk % factors[i];

		if (remainder == 0) { 
			pieces = chunk / factors[i];
			break;
		}
	}	
	return pieces; // return 0 if not perfect fit yet

}


// ------------
// ribbon_eval
// ------------

int ribbon_eval ( int n, int a, int b, int c  ) {
	//int huge_number = std::numeric_limits<int>::max() -1;

	int pieces = 0;

	int ab = a + b;
	int ac = a + c;
	int bc = b + c;
	int abc = a + b + c;

	vector<int>  factors {a,b,c,ab,ac,bc,abc};
	
	//cout << "factors0" << factors[0] << endl;
	cout << "before sorting, factors size=" << factors.size() << endl;
	//for (auto i : factors){
	for (unsigned int i=0; i<factors.size(); ++i){
		cout << "factors[" << i << "]: " << factors[i] << endl;
	}

	std::sort ( factors.begin(), factors.end());

	std::vector<int>::iterator new_end;
	new_end = std::unique ( factors.begin(), factors.end());
	factors.resize(std::distance(factors.begin(), new_end));

	cout << "after sorting and uniquify" << endl;
	for (unsigned int i=0; i<factors.size(); ++i){
		cout << "factors[" << i << "]: " << factors[i] << endl;
	}

	cout << " remove factors > n" << endl;
	for (unsigned int i=0; i<factors.size(); ++i){
		if (factors[i] > n) { factors.erase(factors.begin()+i); }
	}	
	for (unsigned int i=0; i<factors.size(); ++i){
		cout << "factors[" << i << "]: " << factors[i] << endl;
	}
	cout << "next, screening" << endl;

	// screen for trivial cases first

	int chunk = n;

	pieces = mod_chunk(chunk, factors);


	while ( (pieces > 0) && factors.size() > 0) {

		chunk = factors.back();
		factors.pop_back();

		pieces = mod_chunk(chunk, factors);
		if (pieces > 0) break;

	}

	// else, done and return
	return pieces;

} // ribbon eval




// -------------
// ribbon_print
// -------------

void ribbon_print (ostream& pieces) {
	pieces << endl;
}


std::vector<int> ribbon_read_input (const string& s){

	istringstream sin(s);
	int n;
	int a;
	int b;
	int c;
	sin >> n >> a >> b >> c;

	std::vector<int> nabc = { n,a,b,c};

	return nabc;
}



// -------------
// ribbon_solve
// -------------

void ribbon_solve (istream& r, ostream& w) {
	std::string input_line;


		getline(r, input_line);
		std::vector<int> nabc = ribbon_read_input(input_line);
		int n = nabc[0] ; 
		int a = nabc[1] ; 
		int b = nabc[2] ;
		int c = nabc[3];

	cout << "input:" << n << a << b << c << endl;

	int pieces = ribbon_eval(n, a, b, c);


	cout << pieces << endl;

} // solve

// ----
// main
// ----

int main () {
	using namespace std;
	ribbon_solve(cin, cout);
	return 0;
}
