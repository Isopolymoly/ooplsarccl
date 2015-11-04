// ----------------------------
// Bear.c++
// Copyright (C) 2015
// based on Collatz.c++ by Glenn P. Downing
// ----------------------------

// 003

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <cstring>   // std::strcpy
#include <utility>  // make_pair, pair
#include <algorithm>  // so 198199
#include <limits>
#include <queue>

using namespace std;
using std::queue;

/* References:
 * cplusplus.com
 */

// ------------
// bear_mod2
// ------------
//

int bear_mod (int m, int bid){
	int lowest = bid;

	while (lowest >= m ) {
		if (lowest %m ==0) {
			lowest = lowest/m;
		}
		else break;
	}

	return lowest;

}



int bear_mod23 (int bid){
	int lowest = bid;
	//cout << "bid: " << bid;

		while ((lowest % 2 ==0) || (lowest % 3 ==0)) {

		if (lowest % 2 == 0)  { lowest = lowest / 2;  }
		if (lowest % 3 == 0)  { lowest = lowest / 3; }


		//cout << "lowest: " << lowest << endl; ;


	} // while loop

	return lowest;
}



// -------------
// bear_solve
// -------------

void bear_solve (istream& r, ostream& w) {
	std::string input_line;

	int  lcm;
	int  this_lcm;
	int  this_bid;

	bool success=1;
	int n;


// read in first line
	getline(r, input_line); // first line
	istringstream sin1(input_line);
	sin1 >> n;


	getline(r, input_line); // second line
	istringstream sin2(input_line);
	sin2 >> this_bid;


	lcm = bear_mod23(this_bid);


	// i=0 already handled above
	for (int i = 1 ; i < n; ++i) {

		sin2 >> this_bid;
		this_lcm = bear_mod23(this_bid);

		if (this_lcm != lcm) {
			success = 0;
			break;
		}
	  
	} // for 1:n


	if (success) { cout << "Yes" << endl;}
	else { cout << "No" << endl;}


} // solve

// ----
// main
// ----

int main () {
	using namespace std;
	bear_solve(cin, cout);
	return 0;
}

