#include <iostream>
#include <fstream>

using namespace std;

// Part 1 (Connect the cities)
/* Read an input file of a graph represented in a adjacency
matrix with the weights (distance in km)

Find the optimal way to wire all the cities using the less
optical fiber 

Create a MST 
*/


/* Part 2 (Traveling Salesman Problem) 
Find the shortest possible route that visits each neighborhood 
exactly once and returns to the neighborhood of origin.

Display the route with cities labeled as A, B, C, etc.
The first city will be called A, the second B, and so on.

This is a classic TSP (Traveling Salesman Problem).
*/

/* Part 3 (Maximum Flow Problem)
Read another square matrix of N x N data representing the maximum 
capacity of data transmission between neighborhood i and neighborhood j.

The cities have electromagnetic fields that can generate interference,
which is already reflected in this capacity matrix.

Find the maximum information flow from the initial node to the final node.
Display this maximum flow in the standard output.

This is a classic Maximum Flow problem.
*/

/* Part 4 (Closest Exchange/Central)
Given the geographic location of several "exchanges" (centrals) to which 
new homes can be connected, determine which exchange is geographically 
closest to a new service contract.

Note: There is not necessarily one exchange for each neighborhood.
- Some neighborhoods may have no central
- Some neighborhoods may have more than one central

Find the closest exchange for any new contract location.
*/

int main() {

    ifstream file("inputs/input.txt");

    if (!file.is_open()){
        cout << "Error opening file" << endl;
    }

    string line;

    while (getline(file, line)){
        cout << line << endl;
    }
    
    cout << "Hello, world!" << endl;
    return 0;
}

