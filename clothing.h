#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Clothing : public Product{
    public: 
        Clothing(const std::string size, const std::string brand, const std::string category_, const std::string name_, double price_, int qty_);
        virtual ~Clothing();
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;

    private:
        std::string size_;
        std::string brand_;
};

#endif