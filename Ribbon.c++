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
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;
using std::vector;
using std::priority_queue;
using std::unordered_map;
using std::min_element;


// ------------
// ribbon_eval
// ------------

int ribbon_eval ( int n, int a, int b, int c  ) {

	int pieces = 0;

	// Xa + Yb + Zc = n
	// 	all positive integers 1<= n,a,b,c <= 4000
	// 	so Xa can be at most n (if Y and Z == 0) ==> max X == n/a
	// 	 Yb can be at most n (if X and Z == 0) ==> max Y == n/b
	// 	 Zc can be at most n (if X and Z == 0) ==> max Y == n/c
	//

	vector<int> abc = {a,b,c};

	// pre-filter
	//   bypass worst-case calculations
	//   //   worst case = big n, small a,b, or c
	if (*min_element(abc.begin(), abc.end()) == 1) { return n; }
	if (*min_element(abc.begin(), abc.end()) == 2)  {
			if (n % 2 ==0) { return n/2; }
			else if (a==3 || b ==3 || c == 3)  { return (n-1)/2 ; } // all 2's except one 3

	}
	



	// check unique  
	//int limits[3] = {0,0,0};


	std::sort ( abc.begin(), abc.end());

	std::vector<int>::iterator new_end;
	new_end = std::unique ( abc.begin(), abc.end());

	abc.resize(std::distance(abc.begin(), new_end));


	// if n is divisible by a, b, or c, return n div the smallest of those (ordered smallest to largest here, break early)
	for (unsigned int i = 0; i < abc.size(); ++i) {
		if (n % abc[i] == 0) { return n / abc[i]; }
	}




	int x_lim = n / a;
	int y_lim = n / b;
	int z_lim = n / c;


	// if a==b==c, early exit with mod prior to this point
	//
	// brute force & ugly TODO permute over abc vector
	
	if (a == b) { y_lim = 0; }
	if (b == c) { z_lim = 0; }
	if (a == c) { z_lim = 0; }


/*	
	if( ((a!=c) && (c % a == 0)) || ( (c !=b) && (c % b == 0))  { z_lim = 0;}
	if( (b % a == 0) || (b % c == 0))  { y_lim = 0;}
	if( (a % b == 0) || (a % c == 0))  { x_lim = 0;}

*/



	//priority_queue<int> pieces_pq;
	vector<int> pieces_v;
	int sum;



	// < lim here because = case has early exit above
	for ( int x = 0 ; x < x_lim; x++ ) {
		for ( int y = 0 ; y < y_lim; y++ ) {
			if (((x*a) + (y*b)) > n) {break;}

			for ( int z = 0 ; z < z_lim; z++ ) {

				sum = (x*a) + (y*b) + (z*c);

				if (sum == n) {
					pieces = x + y + z;
					//pieces_pq.push(pieces);
					pieces_v.push_back(pieces);
				}
				else if (sum > n) { break;} // 
			} // z
		} // y
	} // x
	

	//return pieces_pq.top();
	return *max_element(pieces_v.begin(), pieces_v.end());

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
