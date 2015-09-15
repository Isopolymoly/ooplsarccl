// ----------------------------
// projects/kita/Kita.c++
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
#include <cstring>   // std::strcpy
#include <utility>  // make_pair, pair

#include <algorithm>  // so 198199


//#include "Kita.h"

using namespace std;

// ------------
// kita_read
// ------------


/*
std::string kita_read (const string& skita) {
    istringstream sin(skita);
    std::string s;

    sin >> s;

    return s;
}

*/

// ------------
// kita_eval
// ------------

//const char* kita_eval ( const char*  s) { \\}
std::string kita_eval ( std::string  s) {
    
	std::string palindrome = "NA";

	int slength = s.length();

// adding same character to single-character string -> palindrome
if (slength == 1) {
	palindrome.assign(s);
	palindrome.append(s);
    return palindrome;

}

// adding first character to end of two-character string -> palindrome
if (slength == 2) {
	palindrome.assign(s);
	std::string s0 = s.substr(0,1);	
	palindrome.append(s0);
    return palindrome;
}


std::string s_reversed = s;
std::reverse(s_reversed.begin(), s_reversed.end());

   cout << s_reversed << endl;


// compare first half of s with first half of reversed



// brute force: loop through
//
//for (std::string::iterator it=s.begin(); it!=s.end(); ++it) {
	//s.compare(
//
//
//}
  

int half = slength  >> 1; //  check for 0 here


std::string piece = s.substr(0,half);
cout << "piece: " << piece << endl;
cout << "s_reversed: " << s_reversed << endl;


std::size_t s_found = s_reversed.find(piece,0);

cout << "found: " << s_found << endl;






	//int same = s.compare(0,1, s.at(1));// compare 0th character to 1st character
		//palindrome.insert(1,"x");


//std::cout << palindrome.length() << endl;
std::cout << s.length() << endl;




    return palindrome;
}

// -------------
// kita_print
// -------------

void kita_print (ostream& w,  std::string p) {
    w << p  << endl;
}

// -------------
// kita_solve
// -------------

void kita_solve (istream& r, ostream& w) {
    std::string skita;
    while (getline(r, skita)) {
        //std::string s = kita_read(skita);
         std::string    p = kita_eval(skita);
        kita_print(w, p);}}



//for (std::string::reverse_iterator rit=palindrome.rbegin(); rit!=palindrome.rend(); ++rit) {
	//std::cout << *rit << std::endl;
	//s_reversed.append(*rit);
	//s_reversed.append(*rit);
//
//}
//
