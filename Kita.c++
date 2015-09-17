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

   //cout << s_reversed << endl;


// compare first half of s with first half of reversed



// brute force: loop through
//
//for (std::string::iterator it=s.begin(); it!=s.end(); ++it) {
	//s.compare(
//
//
//}
  

// evens 
//if (slength % 2 == 0) {
//
//
//}



// should not be zero as long as length >= 3
unsigned int half = slength  >> 1; //  check for 0 here
//int diff = 0;





// if set difference is more than one character, FAIL with NA
//
// if set difference is one character, find the matching character from other half  and insert it
// if set difference is zero, insert any character into middle
//





std::string piece = s.substr(0,half);
////cout << "piece: " << piece << endl;
//cout << "s_reversed: " << s_reversed << endl;


//std::size_t s_found = s_reversed.find(piece,0);
//
  



std::string left2 = s.substr(0,2);
std::string right2 = s_reversed.substr(0,2);

//cout << "left2: " << left2 << " right2: " << right2 << endl;

std::sort(left2.begin(), left2.end());
std::sort(right2.begin(), right2.end());

//cout << " sorted left2: " << left2 << " right2: " << right2 << endl;



// quick screening step to auto-fail non-palindromes
// check end two characters from both sides of fold
// if there is no intersection, it can't be a palindrome; FAIL with NA

std::string intersect_check, check;

std::set_intersection(left2.begin(),left2.end(), right2.begin(), right2.end(),  std::back_inserter(intersect_check) );

//cout << "set intersection: " <<  intersect_check << endl;

// stack overflow 7936654
//std::set_union(left2.begin(),left2.end(), right2.begin(), right2.end(), std::back_inserter(check));
//
//cout << "set union: " <<  check << endl;


if (intersect_check.length() <1) {

	return palindrome;  // NA
}


// at this point in the flow, s.length >= 3, and it's not an auto-fail
//  now get serious about finding palindromes
//
std::string lefthalf = s.substr(0,half);
std::string righthalf = s_reversed.substr(0,half);

//cout << "lefthalf: " << lefthalf << " righthalf: " << righthalf << endl;

std::sort(lefthalf.begin(), lefthalf.end());
std::sort(righthalf.begin(), righthalf.end());

//cout << " sorted lefthalf: " << lefthalf << " righthalf: " << righthalf << endl;



std::string check_half;

std::set_intersection(lefthalf.begin(),lefthalf.end(), righthalf.begin(), righthalf.end(),  std::back_inserter(check_half) );

//cout << "half intersection echeck:" << check_half << endl;

if (check_half.length() < half-1) {

	return palindrome; // NA

}

///////
///   set buckets have right contents, not necesarily in order for palindrome


	palindrome.assign("possible");


if ( s.compare(0,half, s_reversed, 0, half) == 0) {

	//cout << "found match: " << s << ", " << s_reversed <<"." << endl;
	palindrome.assign(s);

	// must insert a letter;
	//    if s is even # characters, insert any character into new middle 
	//    if s is odd # characters, insert repeated middle character into new middle 
	// -->  insert repeated middle character into new middle


	palindrome.insert( half+1, s,half,1 );

    return palindrome;
}

// else check character by character
//   ... at this point, there are the right characters, maybe not in order

else {
//cout << "s=" << s << "; srev= " << s_reversed << endl;
//


// compare endpoints.  If they're not equal, compare left end to right end -2
//    if that's a match, replicate and check for palindrome
//    otherwise, it can't be made a palindrome, FAIL with NA
//
bool bubble_taken = FALSE;
for (unsigned int i=0; i< half; ++i) {
	cout << "i:" << i << endl;
	cout << s.at(i) << endl;
	if ( s.compare(i,1, s_reversed, i, 1) != 0) {
	// these 2 didn't match...try ith one on left with next one in on right side
		if (s.compare(i,1, s_reversed, i+1,1) !=0) {
		// these didn't match either.  it could be a fail, or could need an insertion here.

	// FIXME here under construction
		palindrome.assign(s);
		palindrome.insert(i,s_reversed, i,1);


		// more than one letter off, game over
		palindrome.assign("NA");
		return palindrome;
	}
	palindrome.assign(s);
	palindrome.insert(i,s_reversed, i,1);
	cout << "inserted, now: " << palindrome << endl;
    return palindrome;
	
}
// if they match, go on to the next i

}

} //else check each

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
