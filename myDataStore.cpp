#include "mydatastore.h"
#include "util.h"  

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {

}

void MyDataStore::addProduct(Product* p) {
    products_.insert(make_pair(p->getName(), p));

}

void MyDataStore::addUser(User* u) {

    users_.insert(make_pair(u->getName(), u)); 
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
      std::set<Product*> results;

    // Iterate over the map of products
    for (std::map<std::string, Product*>::iterator productIt = products_.begin(); productIt != products_.end(); ++productIt) {
        // Access the Product* using productIt->second
        Product* currentProduct = productIt->second;

        // Get the keywords for the current product
        std::set<std::string> productKeywords = currentProduct->keywords();

        // Convert search terms vector to a set for intersection/union operations
        std::set<std::string> searchTerms(terms.begin(), terms.end());

        std::set<std::string> matchedKeywords;
        if (type == 0) {  // AND search
            matchedKeywords = setIntersection<std::string>(productKeywords, searchTerms);
            if (!matchedKeywords.empty()) {
                results.insert(currentProduct);
            }
        } else {  // OR search
            matchedKeywords = setUnion<std::string>(productKeywords, searchTerms);
            if (!matchedKeywords.empty()) {
                results.insert(currentProduct);
            }
        }
    }

    // Convert the set of results to a vector and return
    return std::vector<Product*>(results.begin(), results.end());
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    // Iterate over the map of products
    for (std::map<std::string, Product*>::iterator productIt = products_.begin(); productIt != products_.end(); ++productIt) {
        // Access the Product* using productIt->second
        Product* currentProduct = productIt->second;
        currentProduct->dump(ofile);  // Dump the product details to the output stream
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    // Iterate over the map of users
    for (std::map<std::string, User*>::iterator userIt = users_.begin(); userIt != users_.end(); ++userIt) {
        // Access the User* using userIt->second
        User* currentUser = userIt->second;
        currentUser->dump(ofile);  // Dump the user details to the output stream
    }
    ofile << "</users>" << std::endl;
}
