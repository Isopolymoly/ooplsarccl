// ----------------------------
// projects/dijkstra/Dijkstra.c++
// Copyright (C) 2015
// based on Collatz.c++ by Glenn P. Downing
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

#include <limits>


using namespace std;


// ------------
// dijkstra_eval
// ------------

int dijkstra_eval ( int n, int graph[][6]  ) {
    
  //cout << "hello, world" << endl;

int int_max = std::numeric_limits<int>::max();


//cout << "int_max = " << int_max << endl;


/*
cout << "graph: " << endl;
for (int i=0; i < n; ++i) {
	for (int j=0; j < n; ++j) {

		cout << graph[i][j] ;
	}
	cout << endl;
}
*/


// www.cs.cornell.edu/~wdtseng/icpc/notes/graph_part2.pdf	

// FIXME need up to 10^5 elements in arrays
int dist[128];
int path[128];
bool done[128];



//void dijkstra( ) {
	for (int i = 0; i < n; i++ ) {
		dist[i] = int_max; // 2<=n<=10^5; 1 <= wi <= 10^6
		done[i] = false;
	} // for i

	dist[0]=0; // vertex 1 is starting point, stored in arrays [0]
	


	int this_step = 0;
	while (true) {

	int u = -1, bestDist= int_max;

	//cout << "while loop first round n=" << n << ", u=" << u << endl;
	//cout << "  done[0] = " << done[0] << " dist=" << dist[0] << endl;

	for(int i=0; i<n; i++) {

	//cout << ", i=" << i << " done = " << done[i] << " dist=" << dist[i] << endl;
		 if (!done[i] && dist[i] < bestDist) {


		u=i; // found a vertex with a shorter distance
		bestDist = dist[i];
	cout << "while loop new u=" << u << endl;
	cout << " new bestDist == " << bestDist << endl;

		} // not done, and distance is less than best so far
	} // for i

	// once everything is done, an iteration of the while loop will skip the int i loop and break here
	if(bestDist==int_max) break;


	for (int v = 0; v < n; v++) if (!done[v] && graph[u][v] != -1) {
		// update distance between not-done connections and u
		if (dist [v] > dist[u] + graph[u][v] ) {
			dist[v] = dist[u] + graph[u][v];
			}
	cout << "for v loop, dist["<<v<<"] = " <<  dist[v] << endl;


	} // for v
	done[u] = true;

/* not here, this catches every vertex
	path[this_step] = u+1;
	cout << "next on path:" << path[this_step] << endl;
	++this_step;
*/

	} // while true


	cout << "distance:" << dist[n-1] << endl;
	cout << "done:" << done[n-1] << endl;
	cout << "path:" ;

	for (int i=0; i<this_step; ++i){
	cout << path[i] << endl;

		}


//} // dijkstra loop




// end cornell.edu notes






	return dist[n-1];



} // dijkstra eval

// -------------
// dijkstra_print
// -------------

void dijkstra_print (ostream& w,  int shortest_distance) {
    w << shortest_distance  << endl;
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
	const int  n = nm.first;
	const int  m = nm.second;


	int graph[6][6];

	for (int i=0; i < n; ++i) {
		for (int j=0; j < n; ++j) {
		graph[i][j] = -1; 
	}
	}



	for (int i = 0; i < m; ++i) {
     		getline(r, input_line);
	cout << "next line: " << input_line << endl;

    	std::vector<int> edge = dijkstra_read_a_b_w(input_line);
	int a = edge[0] -1;
	int b = edge[1] -1;
	int w = edge[2];
	graph[a][b] = w;
	graph[b][a] = w;

	cout << "added to graph["<<a<<"][" << b << "]: " << w << endl;
	
	}

	cout << "fresh graph: " << endl;
	for (int i=0; i < n; ++i) {
		for (int j=0; j < n; ++j) {
	
			cout << graph[i][j] << " "  ;
		}
		cout << endl;
	}
        

        int  shortest_distance = dijkstra_eval(n, graph);

        dijkstra_print(w, shortest_distance);}



// ----
// main
// ----

int main () {
    using namespace std;
    dijkstra_solve(cin, cout);
    return 0;
}

