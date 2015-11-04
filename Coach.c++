// ----------------------------
// Coach.c++
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

using namespace std;
using std::vector;

/* References:
 * cplusplus.com
 */


// ------------
// coach_eval
// ------------

 void coach_eval ( int n, vector< pair<int,int> > &buddies ) {

	int teams [16][3] = {0}; // print 
	int next_team = 0;
	bool success = 1;
	vector<bool> used;


	// force init -- getting different answers locally and with online judge's compile
	for (int i=1; i <= n; ++i){
		used.push_back(0);
	}
	

	//cout << "inside eval" << endl;

	// for each element in buddies vector, add ab pair to teams array
	//    find a, if it's already in the table
	//     or add it if it's not
	//     then add b to same row, if it fits
	//     early exit -1 if it doesn't fit
	//

	bool done;

	// removing c11-ish code to see what's causing compile errs, diff answers in online judge
	//for (auto const &entry : buddies) {
	for (size_t l=0; l < buddies.size(); l++ ) {
		pair<int,int> entry = buddies[l];
		//cout << "buddy list: " << entry.first << ", " << entry.second << endl;

		
		done=0;

		for (int i =0; i < 16; ++i){
			for (int j =0; j <= 2; ++j){
				//cout << "checking for " << entry.first << " in teams[" << i << "][" << j << "]" << endl;

				if (entry.first == teams[i][j]) {
					// found team; now look for empty spot

					//cout << "found team at " << teams[i][j] << endl;

					for (int k = j+1; k <=2; k++) {

						if (teams[i][k] == 0) { 
							//cout << "found empty spot at [" << i << "][" << j << "]" << endl; 
							teams[i][k] = entry.second; 
							used[entry.second] = 1;
							//cout << "updating used[" << entry.second << "]";
							done = 1;
							break;
						} // 
					}
					if (!done) {
					//  team is full with extra pair; exit with -1
					success = 0;
 					break; 
					}


				} // matching team
			} // for j
		} // for i

		// start new team
		if (success && !done) {
		teams[next_team][0] = entry.first;
		used[entry.first] = 1;
		teams[next_team][1] = entry.second;
		used[entry.second] = 1;
		++next_team;
		done  = 1;
		}

} // for each buddies element  (pair a,b)
// TODO fill in un-paired c's cout << "c's left to fill in: " << endl; 
 //for (int i =0; i<=n; i++) {
 //cout << used [i] << " ";
	//}
//cout << endl;


// used[0] is initialized to zero and doesn't change;
// using 1<=n for indices to match team member numbers
for (int c=1; c <=n ; c++){
  if (!used[c]){
	done = 0;
	//cout << "looking for spot for " << c << endl;
	// find an open spot for this c
		for (int i =0; i < 16; ++i){
			for (int j =0; j <= 2; ++j){

			  if (teams[i][j] == 0){
				//cout << "found spot at teams[" << i << "][" << j << "]" << endl;
				teams[i][j] = c;
				used[c] = 1;
				done = 1;
				break;
				}
			}
			if (done) {break;}
}


  }

}


/////////////////////////////
if (success) {

	for(int i=0; i < n/3; ++i){
		//cout << "team" << i << ": " ;
		for(int j=0; j < 3; ++j){
			cout <<  teams[i][j]  << " ";
		}
		cout << endl;
	}
} else {
	cout << "-1" << endl;
}



//return success;

} // coach eval

// -------------
// coach_print
// -------------

/*
   void coach_print (ostream& w, const int n, int[] teams) {

   for(int i=0; i < n/3; ++i){
   w <<  teams[i][0]  << " ";
   }
   w << endl;
   }

*/

pair<int, int> coach_read_pair (const string& s){

	istringstream sin(s);
	int n;
	int m;
	sin >> n >> m;
	return make_pair(n,m);
}



// -------------
// coach_solve
// -------------

void coach_solve (istream& r, ostream& w) {
	std::string input_line;

	getline(r, input_line);
	const pair<int,int> nm = coach_read_pair(input_line);
	const int  n = nm.first;
	const int  m = nm.second;


	vector<pair<int, int>>  buddies;

	for (int i = 1; i <= m; ++i) {
		getline(r, input_line);
		pair<int,int> ab = coach_read_pair(input_line);

		buddies.push_back(ab);

	}

	coach_eval(n, buddies);

	//coach_print(cout, n, teams);

} // solve

// ----
// main
// ----

int main () {
	using namespace std;
	coach_solve(cin, cout);
	return 0;
}

