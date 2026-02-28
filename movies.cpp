#include "movies.h"
#include <set>
#include <string>
#include <iostream>
#include <vector>

bool MovieList::Movie::operator<(const Movie& right) const{
    return title < right.title;
}

void MovieList::addMovie(std::string t, double r){
    mList.insert(Movie(t,r));
}
void MovieList::printList(){
    for (auto& movie : mList){
        std::cout << movie.title << ", " << movie.rating << std::endl;
    }
}

std::set<MovieList::Movie>& MovieList::getList(){
    return mList;
}
bool PrefixList::Movie::operator<(const Movie& right) const{
    if(rating == right.rating)
        return title < right.title;
    return rating > right.rating;
}

void PrefixList::filterMList(MovieList& movies, std::string prefix){
    std::set<Movie> result;
    for(auto it: movies.getList()){
        if(prefix == it.title.substr(0,prefix.length())){
            result.insert(Movie(it.title,it.rating));
        } else if (!result.empty()){
            break;
        }
    }
    pfList.push_back(result);
    pf.push_back(prefix);
}
void PrefixList::printPFList(){
    for(int i = 0; i < pfList.size(); i++){
        if(pfList[i].empty()){
            std::cout << "No Movies found with prefix " << pf[i] << std::endl;
        } else {
            for(auto it: pfList[i]){
                std::cout << it.title << ", " << it.rating << std::endl;
            }
            std::cout << std::endl;
        }
    }
    for(int i = 0; i < pfList.size(); i++){
        if(!pfList[i].empty()){
            std::cout << "Best movie with prefix " << pf[i] << " is: " << pfList[i].begin()->title << " with rating " << pfList[i].begin()->rating << std::endl;
        }
    }
}