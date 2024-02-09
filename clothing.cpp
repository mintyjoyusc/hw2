#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iostream>


using namespace std;

Clothing::Clothing(const std::string size, const std::string brand, const std::string category_, const std::string name_, double price_, int qty_) : Product(category_, name_, price_, qty_){
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing(){

}

set<std::string> Clothing::keywords() const{

    std::set<std::string> keywords_ = parseStringToWords(name_);
    std::set<std::string> brandWords = parseStringToWords(brand_);
    keywords_.insert(brandWords.begin(), brandWords.end());
    return keywords_;
}

std::string Clothing::displayString() const{

    std::stringstream ss;
    ss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left.";
    return ss.str();
}

void::Clothing::dump(std::ostream& os) const{
    
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;

}