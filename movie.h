#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Movie : public Product{
    public: 
        Movie(const std::string genre, const std::string rating);
        virtual ~Movie();
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;

    private:
        std::string genre_;
        std::string rating_;

};


#endif