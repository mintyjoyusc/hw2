#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <map>

class MyDataStore : public DataStore{
    public: 
        MyDataStore();
        virtual ~MyDataStore();
        void addProduct(Product* p);
        void addUser(User* u);
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        void dump(std::ostream& ofile);

    private:
        std::map<std::string, Product*> products_;
        std::map<std::string, User*> users_;
        //username= key, user=value

};

#endif 