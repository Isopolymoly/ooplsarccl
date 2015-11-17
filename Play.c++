// ----------------------------
// Play.c++
// Copyright (C) 2015
// based on Collatz.c++ by Glenn P. Downing
// ----------------------------

// 131C
//
// How many ways are there to choose a group of t actors,
// such that 

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


long long combinations (int group, int subset){
	// c(group, subset) = group! / (subset! * (group - subset)! )
	//                  = [group * group-1 * group-2...group-subset+1] * (group - subset)! / subset! * (group - subset)!
	//                  = [group ...] / subset!


	long long C = 1;

	vector<int>  numeratorV;
	vector<int>  denominatorV;


	for (int i=group; i > (group - subset); --i){
		numeratorV.push_back(i);
	}


	for (int i=subset; i > 0; --i){
		denominatorV.push_back(i);
	}



// contorted math to use integer divides without overflowing
	for (size_t i=0; i < denominatorV.size(); ++i ){
		for (size_t j=0; j < numeratorV.size(); ++j ){
			if ( numeratorV[j] % denominatorV[i] == 0) {
				numeratorV[j] = numeratorV[j] / denominatorV[i];
				denominatorV[i] = 1;
				break;
			}

		}
	}


C = 1;
for (auto n : numeratorV){
	C = C * n;
	////cout << "n: " << n << endl;
}
for (auto d : denominatorV){
	C = C / d;
	//cout << "d: " << d << endl;
}





	//cout << "group: " << group << " subset: " << subset << " C: " << C << endl;

	return(C);


}

// ------------
// play_eval
// ------------

void play_eval ( int n, int m, int t) {

	//cout << "n: " << n << " m: " << m << " t: " << t << endl;

	// 5 <= t <= (n + m)
	// 4 <= n <= 30 # boys in club
	// 1 <= m <= 30 # girls in club


	// 4 <= b <= n // at least 4 boys in play
	// 1 <= g <= m // at least 1 girl in play
	// b + g = t;    b = t-g


	long long running_total = 0;

	for (int g=1; ((g<=m) && ((t-g) >=4 )); ++g){

		//cout << "g: " << g  << endl;

		long long gc = combinations(m, g);
		//cout << "gc: " << gc  << endl;
		long long bc = combinations(n, t-g);
		//cout << "bc: " << bc  << endl;

		running_total +=  (gc * bc);

	}

	cout << running_total << endl;

} // play eval



// -------------
// play_solve
// -------------

void play_solve (istream& r, ostream& w) {
	std::string input_line;

	int n;
	int m;
	int t;

	getline(r, input_line);

	istringstream sin(input_line);

	sin >> n >> m >> t;


	play_eval(n, m, t);


} // solve

// ----
// main
// ----

int main () {
	using namespace std;
	play_solve(cin, cout);
	return 0;
}

