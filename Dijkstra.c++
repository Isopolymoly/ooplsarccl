// ----------------------------
// projects/dijkstra/Dijkstra.c++
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
using std::map;
using std::unordered_map;

/* References:
 * cplusplus.com
 expecially	 cplusplus.com/forum/articles/7459
 www.cs.cornell.edu/~wdtseng/icpc/notes/connections_part2.pdf	
 */


// ------------
// dijkstra_eval
// ------------

std::deque<int> dijkstra_eval ( int n, map<int, map<int,int> > &connections ) {
	// n has been decremented to match indices bfeore it's passed to this function

	int huge_number = std::numeric_limits<int>::max() -1;

	// www.cs.cornell.edu/~wdtseng/icpc/notes/connections_part2.pdf	

	// *scaling* need up to 10^5 elements in arrays
	//std::vector<int> distance_to_v0;
	std::unordered_map<int, int> distance_to_v0;
	std::unordered_map<int, int> via;
	std::deque<int> path = {n+1}; // converting back to 1:n notation (from 0:n-1 indices)

	for (int i = 1; i <= n; i++ ) {
		distance_to_v0[i] = huge_number; // 2<=n<=10^5; 1 <= wi <= 10^6
		//cout << "distance_to_v0[" << i << "]: " << distance_to_v0[i] << endl;
	} // for i

	distance_to_v0[0]= 0; // starting point

	while (true) {
		int u = -1;
		int bestDist= huge_number;

		for(auto const &d0 : distance_to_v0) {
			//cout <<  "dista[ " << d0.first << "] => " << d0.second << endl;

			if ( d0.second < bestDist) {
				u=d0.first; // found a vertex with a shorter distance_to_v0
				bestDist = d0.second;
				//cout << " update: d0.first "<< " ==> " << d0.second << endl;
			} // not done, and distance_to_v0ance is less than best so far
		} // for every not-done vertex

		// once all vertices are makred as  done, an iteration of the while loop will skip the int i loop and break here
		if(bestDist==huge_number) break;


		//cout << "check row " << u << endl ; // << " map: " << connections[u] << " ";
		for (auto const &columns : connections[u]){
			//cout << "     check v:" << columns.first <<  " ";
			//cout <<  "    check w:" <<columns.second << endl;
		 //cout << (distance_to_v0.count(columns.first))  << endl;

			if (distance_to_v0.count(columns.first)) {
				//cout << "count v" << endl;
				//cout <<  distance_to_v0[columns.first] << endl;
				//cout <<  distance_to_v0[u] << endl;
				//cout <<  columns.second << endl;
				// update distance_to_v0ance between not-done connections and u
				if (distance_to_v0[columns.first] > distance_to_v0[u] + columns.second ) {
					distance_to_v0[columns.first] = distance_to_v0[u] + columns.second;
					via[columns.first] = u;
					//cout << "distance to v0" << distance_to_v0[columns.first] << endl;
				}
			} // if not done
		} // for each v in sparse matrix (auto iterator)


		//done[u] = true;
		//distance_to_v0[u] = -1; // marked as done
		distance_to_v0.erase(u);

		//cout << "done for u:" << u << endl;

		// keep track of path from vertex 0 to this vertex u, when it's done

	} // while true


	// end cornell.edu notes


	int step = n;

	while ( step != 0 ){
		if (!via.count(step)) {
			path[0] = -1;
			break;
		}
		path.push_front(via[step] + 1); // convert back to [1 to n] style from [0 to n-1]
		step = via[step];
	}


	std::deque<int>::size_type  dq_size = path.size();

	if  ((dq_size > 1) &&  (path[0] == 1) )  {

		for(unsigned i=0; i < dq_size; ++i){
			cout <<  path[i]  << " ";
		}
		cout << endl;
	}
	else {
		path[0]=-1; // in case of no path to connect vertex 1 to vertex n, return -1
		cout <<  path[0]  << endl;

	}

	return path;


} // dijkstra eval

// -------------
// dijkstra_print
// -------------

void dijkstra_print (ostream& w,  std::deque<int> path) {

	std::deque<int>::size_type  dq_size = path.size();

	for(unsigned i=0; i < dq_size; ++i){
		w <<  path[i]  << " ";
	}
	w << endl;
}


pair<int, int> dijkstra_read_n_m (const string& s){

	istringstream sin(s);
	int n;
	int m;
	sin >> n >> m;
	return make_pair(n,m);
}


std::vector<int> dijkstra_read_a_b_w (const string& s){

	istringstream sin(s);
	int a;
	int b;
	int w;
	sin >> a >> b >> w;

	std::vector<int> edge = { a,b,w};

	return edge;
}



// -------------
// dijkstra_solve
// -------------

void dijkstra_solve (istream& r, ostream& w) {
	std::string input_line;

	getline(r, input_line);
	const pair<int,int> nm = dijkstra_read_n_m(input_line);
	const int  n = nm.first -1;
	const int  m = nm.second;


	// replacing 2-D array from vector of vectors with a sparse matrix, map of maps
	map<int, map<int, int> > connections;

	for (int i = 0; i < m; ++i) {
		getline(r, input_line);
		std::vector<int> edge = dijkstra_read_a_b_w(input_line);
		int a = edge[0] -1; // rename vectors to match indices in connections
		int b = edge[1] -1;
		int w = edge[2];
		connections[a][b] = w;
		connections[b][a] = w;
	}

	std::deque<int>  path = dijkstra_eval(n, connections);

} // solve

// ----
// main
// ----

int main () {
	using namespace std;
	dijkstra_solve(cin, cout);
	return 0;
}

