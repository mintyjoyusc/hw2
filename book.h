#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Book : public Product{
    public: 
        Book(const std::string ISBN, const std::string author);
        virtual ~Book();
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;

    protected:
        std::string ISBN_;
        std::string author_;

};

#endif