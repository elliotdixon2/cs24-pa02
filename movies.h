#include <set>
#include <string>
#include <vector>

class MovieList{
private:
    struct Movie{
        std::string title;
        double rating;
        Movie(std::string t, double r): title(t), rating(r){};
        bool operator<(const Movie& right) const;
    };
    std::set<Movie> mList;
public:
    void addMovie(std::string t, double r);
    void printList();
    std::set<Movie>& getList();
};

class PrefixList{
private:
    struct Movie{
        std::string title;
        double rating;
        Movie(std::string t, double r): title(t), rating(r){};
        bool operator<(const Movie& right) const;
    };
    std::vector<std::set<Movie>> pfList;
    std::vector<std::string> pf;
public:
    void filterMList(MovieList& movies, std::string prefix);
    void printPFList();
};