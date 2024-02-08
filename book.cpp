#include "book.h"
#include "util.h"
#include <sstream>
#include <iostream>

using namespace std;

Book::Book(const std::string ISBN, const std::string author) : Product(category_, name_, price_, qty_){
    ISBN_ = ISBN;
    author_ = author;
}

Book::~Book(){

}

set<std::string> Book::keywords() const{
    std::set<std::string> keywords_ = parseStringToWords(name_);
    std::set<std::string> authorWords = parseStringToWords(author_);
    keywords_.insert(authorWords.begin(), authorWords.end());
    keywords_.insert(ISBN_);

    return keywords_;
}

std::string Book::displayString() const{
    std::stringstream ss;
    ss << name_ << "\n" << "Author: " << author_ << " ISBN: " << ISBN_ << "\n" << price_ << " " << qty_ << " left.";
    return ss.str();
}

void::Book::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << std::endl;

}

