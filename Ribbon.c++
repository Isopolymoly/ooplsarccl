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
//#include <deque>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;
using std::vector;
using std::priority_queue;
using std::unordered_map;

// mod_chunk
// negative return values:  index of smallest factor with mod 0
// // positive return values: 
int mod_chunk(int chunk, vector<int> factors) {
	int remainder;

	for (unsigned int i=0; i<factors.size(); ++i){

		//cout << "mod_chunk factors[" << i << "]: " << factors[i] << endl;

		remainder = chunk % factors[i];
		//cout << chunk << " % " << factors[i] << " = " << remainder << endl;

		if (remainder == 0) { 
			remainder = -1 + (-1*i); // override with index
			//cout << "remainder negative index: " << remainder << endl;
			break;
		}
	}	
	//cout << "returning: " << remainder << endl;
	return remainder; // return > 0 if not perfect fit yet

}


// ------------
// ribbon_eval
// ------------

int ribbon_eval ( int n, int a, int b, int c  ) {

	int pieces = 0;

	int ab = a + b;
	int ac = a + c;
	int bc = b + c;
	int abc = a + b + c;

	vector<int>  candidates {a,b,c,ab,ac,bc,abc};
	unordered_map<int, int>  factors_pieces { {a,1}, {b,1}, {c,1}, {ab,2}, {bc,2}, {ac,2}, {abc,3}};

	// number of pieces for each factor
	
	//cout << "before sorting, candidates size=" << candidates.size() << endl;
	//for (unsigned int i=0; i<candidates.size(); ++i){
		//cout << "candidates[" << i << "]: " << candidates[i] << endl;
	//}

	std::sort ( candidates.begin(), candidates.end());

	std::vector<int>::iterator new_end;
	new_end = std::unique ( candidates.begin(), candidates.end());

	candidates.resize(std::distance(candidates.begin(), new_end));

	//cout << "after sorting and uniquify" << endl;
	//for (unsigned int i=0; i<candidates.size(); ++i){
		//cout << "candidates[" << i << "]: " << candidates[i] << endl;
	//}

	//cout << " remove candidates > n" << endl;
	for (unsigned int i=0; i<candidates.size(); ++i){
		if (candidates[i] > n) { 
			candidates.erase(candidates.begin()+i); 
		}
	}	
	//for (unsigned int i=0; i<candidates.size(); ++i){
		//cout << "candidates[" << i << "]: " << candidates[i] << endl;
	//}


	vector<int>  factors = candidates;
	priority_queue<int> pieces_pq;

	//cout << "next, modding" << endl;


	int chunk = n;
	int remainder;

	remainder = 5000;  // integer > max input

	for ( int i= candidates.size(); i > 0; i-- ) {

		while ( (remainder > 0) && (factors.size() > 0))  {

		remainder = mod_chunk(chunk, factors);

		// negative return values indicate index for smallest factor element with mod 0
		if (remainder < 0) {
			int i = (-1*remainder) -1;
			pieces += factors_pieces[factors[i]] * ( chunk / factors[i]);
			pieces_pq.push(pieces);
			break;
		} else {
			// account for these pieces, then pop off the end of factors and keep going
			pieces +=  factors_pieces[factors.back()] * (chunk / factors.back() ); // integer division
			chunk = factors.back();
			factors.pop_back();
		}


	} // while remainder > 0

	// either check for break condition here, or don't touch pieces (and allow others to be corrupt here)

	
	// remove biggest element of factor and start over again
	candidates.pop_back();
	factors = candidates;
	chunk = n;

	} // for i= factors.size()  --> 0

	

	return pieces_pq.top();

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

	//cout << "input:" << n << a << b << c << endl;

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
