#include "movie.h"
#include "util.h"
#include <sstream>
#include <iostream>


using namespace std;

Movie::Movie(const std::string genre, const std::string rating, const std::string category_, const std::string name_, double price_, int qty_) : Product(category_, name_, price_, qty_){
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie(){

}

set<std::string> Movie::keywords() const{

    std::set<std::string> keywords_ = parseStringToWords(name_);
    std::set<std::string> genreWords = parseStringToWords(genre_);

    keywords_.insert(genreWords.begin(), genreWords.end());
    
    return keywords_;
}

std::string Movie::displayString() const{

    std::stringstream ss;
    ss << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left.";
    return ss.str();
}

void::Movie::dump(std::ostream& os) const{
    
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;

}