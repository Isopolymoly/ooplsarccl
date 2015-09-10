// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    // <your code>
    /// return max cycle length between integers i and j

	int max_cycle_length = 0;
	int l = 0;
    	int c = 1;
	int n = 0;


	// switch as needed for increasing order i->j in for loop
	if (j < i) {

	// borrow n for a sec here as a temporary variable
		n = i; // TEMP
		i = j; // i is smaller of 2 input values 
		j = n; // j takes larger of 2 input values

	}


	/// loop through from i to j, update max cycle length
	//	go through loop once for i==j
	for (l = i; l <= j; ++l) {

	cout << "next loop l=" << l << endl;


	c = 1; // when input is [1,*], while loop is not executed, cycle length=1
	n = l;
    	while (n > 1) {
        	if ((n % 2) == 0)
            		n = (n / 2);
        	else
            		n = (3 * n) + 1;

        	++c;
		//cout << "updated n=" << n << endl;
 	}

		cout << "c =" << c << " for n=" << n << endl;
	if (c > max_cycle_length) {
		max_cycle_length = c;
		}


	}
		//cout << "returning max cycle length =" << max_cycle_length << endl;
	return max_cycle_length;


// nested function -- or move out? TODO

/*
// from examples/Collatz1.h
int cycle_length (int n) {
    assert(n > 0);
    int c = 0;
    while (n > 1) {
        if ((n % 2) == 0)
            n = (n / 2);
        else
            n = (3 * n) + 1;
        ++c;}
    assert(c > 0);
    return c;}
*/


	

}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
