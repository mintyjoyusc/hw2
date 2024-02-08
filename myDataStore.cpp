#include "myDataStore.h"
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
void MyDataStore::addProductToCart(const std::string& username, Product* p) {
    carts_[username].push_back(p);
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

void MyDataStore::viewCart(const std::string& username) {
    if (carts_.find(username) != carts_.end()) {
        std::vector<Product*>& cartItems = carts_[username];
        for (std::vector<Product*>::iterator it = cartItems.begin(); it != cartItems.end(); ++it) {
            std::cout << (*it)->displayString() << std::endl;
        }
    } else {
        std::cout << "Cart is empty or user does not exist." << std::endl;
    }
}

void MyDataStore::buyCart(const std::string& username) {
    if (carts_.find(username) != carts_.end()) {
        std::vector<Product*>& cartItems = carts_[username];
        for (std::vector<Product*>::iterator it = cartItems.begin(); it != cartItems.end();) {
            Product* product = *it;
            if (product->getQty() > 0) {
                product->subtractQty(1);
                it = cartItems.erase(it);  // Safely erase and advance the iterator
            } else {
                ++it;  // Move to the next item if this one cannot be purchased
            }
        }
    }
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
