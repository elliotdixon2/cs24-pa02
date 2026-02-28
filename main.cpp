// Winter'24
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    MovieList inputMovies;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            //   insert elements into your data structure

        //cout << movieName << " has rating " << movieRating << endl;
        inputMovies.addMovie(movieName,movieRating);
            
    }

    movieFile.close();

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
            inputMovies.printList();
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    //cout << "No movies found with prefix "<<"<replace with prefix>" << endl;

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    //cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;

    PrefixList createdPrefixList;
    for(int i = 0; i < prefixes.size(); i++){
        createdPrefixList.filterMList(inputMovies,prefixes[i]);
    }
    createdPrefixList.printPFList();
    return 0;
}

/*
Time complexity analysis of filtering (worst case):
    -Iterates through all n in the dataset, with O(n) runtime
    -If all movies titles match the prefix, insertion into the set is O(k*log(k)) 
        as implementation uses std::set insertion
    -For each prefix, total runtime is then O(n + k*log(k))
    -For m prefixes, runtime is repeated m times and results in O(m * (n + klogk) )
    -Total runtime for worst case filtering: O(m * (n + klogk) )

Time complexity analysis of printing prefix info:
    -For each prefix, prints out all movies beginning with each prefix
    -Total runtime for printing prefix info: O(m*k)


Runtimes on input files: 



Space complexity for Prefix List implementation:
    -pfList uses memory equal to m prefixes * k movies for each prefix, resulting in O(m*k)
    -pf uses memory equal to k movies, resulting in O(k)
    -dominant space complexity of O(m*k)


Question based on designing an algorithm focused on low time complexity:
    I designed an algorithm for a low time complexity. Because of this, I did not focus on the resulting
    space complexity. I would say my algorithm ended up having a somewhat optimized space complexity, but 
    I still took an expensive approach. In order to optimize for time, I commonly used vectors and sets, 
    which can be quite expensive for space complexity especially when used together. I mainly wanted to 
    avoid anything worse than O(nlogn) for run time, so I ended up using multiple imbedded dynamic
    stuctures to help me out. I would say this tradeoff is worth it though, as the space complexity is 
    not an extremity.
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}