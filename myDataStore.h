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
        void addProductToCart(const std::string& username, Product* p);
        void viewCart(const std::string& username);
        void buyCart(const std::string& username);
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        void dump(std::ostream& ofile);


    private:
        std::map<std::string, Product*> products_;
        std::map<std::string, User*> users_;
        //username= key, user=value
        std::map<std::string, std::vector<Product*>> carts_;  // Maps username to their shopping cart (list of Product pointers)


};

#endif 