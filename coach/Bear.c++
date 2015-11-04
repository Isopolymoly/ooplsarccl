// ----------------------------
// Coach.c++
// Copyright (C) 2015
// based on Collatz.c++ by Glenn P. Downing
// ----------------------------

// 000

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

	int mod2=0;
	int mod3=0;

	while (lowest >=3) {
		mod2 = 0;
		mod3 = 0;

		if (lowest % 2 == 0)  { mod2 = lowest / 2; }
		if (lowest % 3 == 0)  { mod3 = lowest / 3; }

		//cout << "lowest: " << lowest ;
		//cout << " mod2: " << mod2 ;
		//cout << " mod3: " << mod3 << endl;

		if ((lowest % 2 ==0) || (lowest % 3 ==0)) {
			lowest = max(mod2, mod3);

		} else { break; }

	} // while loop

	return lowest;
}



// ------------
// bear_eval
// ------------

bool bear_eval (  queue< int>  &players ) {
	int  lcm;
	int  this_lcm;
	int  this_bid;
	//int this_bid2;
	//int this_bid3;

	bool success=1;


	this_bid = players.front();
	players.pop();

	//cout << "this_bid:" << this_bid ;


	lcm = bear_mod23(this_bid);
	//cout << "  lcm: " << lcm << endl;

	while (players.size() > 0) {

		this_bid = players.front();
		players.pop();


		this_lcm = bear_mod23(this_bid);
		//cout << "this_bid: " << this_bid <<  "  this_lcm: " << this_lcm << endl;

		if (this_lcm != lcm) {
			success = 0;
			break;
		}
	  
	//cout << "players.size: " << players.size() << endl;
	} // while


	return success;

} // bear eval



// -------------
// bear_solve
// -------------

void bear_solve (istream& r, ostream& w) {
	std::string input_line;
	bool success;


	getline(r, input_line); // first line
	istringstream sin1(input_line);

	int n;
	sin1 >> n;

	queue<int>  players;
	getline(r, input_line); // second line
	istringstream sin2(input_line);

	int p;
	for (int i = 0; i < n; ++i) {
		sin2 >> p;
		players.push(p);

	}

	success = bear_eval( players);

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

