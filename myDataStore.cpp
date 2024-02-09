#include "mydatastore.h"
#include "util.h"  

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
    // Iterate through the map of products and delete Product pointers
    // std::cout << "products size: " << products_.size() << std::endl;
    for (std::map<std::string, Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        //std::cout << "deleting " << it->second->getName() << "," << it->second->getPrice() << "," << it->second->getQty() << std::endl; 
        delete it->second;  // Free the dynamically allocated Product
    }
    // std::cout << "users size: " << users_.size() << std::endl;
    // Iterate through the map of users and delete User pointers
    for (std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        // std::cout << "deleting " << it->second->getName()  << std::endl; 
        delete it->second;  // Free the dynamically allocated User
    }
}

void MyDataStore::addProduct(Product* p) {
    products_.insert(make_pair(p->getName(), p));
    // std::cout << "product added to ds. new size: " << products_.size() << std::endl; 
}

void MyDataStore::addUser(User* u) {

    users_.insert(make_pair(u->getName(), u)); 
}
<<<<<<< HEAD
=======

void MyDataStore::addProductToCart(const std::string& username, Product* p) {
    std::map<std::string, std::vector<Product*>>::iterator it = carts_.find(username);
    if (it == carts_.end()) {
        carts_[username] = std::vector<Product*>();  // Initialize an empty cart for new user
    }
    carts_[username].push_back(p); }
>>>>>>> 4e4fe8c9d6258fbdf7dca7a936037170278e50a9

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> results;

    // Convert search terms vector to a set for more efficient searching (done only once before the loop)
    std::set<std::string> searchTerms(terms.begin(), terms.end());

    // Iterate over all products
    for (std::map<std::string, Product*>::iterator productIt = products_.begin(); productIt != products_.end(); ++productIt) {
        Product* currentProduct = productIt->second;
        std::set<std::string> productKeywords = currentProduct->keywords();

        if (type == 0) {  // AND search
            std::set<std::string> matchedKeywords;
            // Perform intersection between product keywords and search terms
            std::set_intersection(productKeywords.begin(), productKeywords.end(), searchTerms.begin(), searchTerms.end(), std::inserter(matchedKeywords, matchedKeywords.begin()));

            // If all search terms are matched, add to results
            if (matchedKeywords.size() == searchTerms.size()) {
                
                results.insert(currentProduct);
            }
        } else {  // OR search
            for (std::set<std::string>::iterator termIt = searchTerms.begin(); termIt != searchTerms.end(); ++termIt) {
                if (productKeywords.find(*termIt) != productKeywords.end()) {
                    results.insert(currentProduct);
                    break;  // Found a matching keyword, no need to check the rest
                }
            }
        }
    }

    // Convert the set of results to a vector and return
    std::vector<Product*> resultVector(results.begin(), results.end());
    return resultVector;
}

<<<<<<< HEAD
=======
void MyDataStore::viewCart(const std::string& username) {
    std::map<std::string, std::vector<Product*>>::iterator it = carts_.find(username);
    if (it == carts_.end() || it->second.empty()) {
        std::cout << "Cart is empty or user does not exist." << std::endl;
        return;
    }

    // Display each product in the cart
    const std::vector<Product*>& cartItems = it->second;
    for (size_t i = 0; i < cartItems.size(); ++i) {
        std::cout << i + 1 << ": " << cartItems[i]->displayString() << std::endl;
    }
}

void MyDataStore::buyCart(const std::string& username) {
    // Check if user exists
    std::map<std::string, User*>::iterator userIt = users_.find(username);
    if (userIt == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    User* user = userIt->second;  // Get user pointer

    // Check if the user has a cart
    std::map<std::string, std::vector<Product*>>::iterator cartIt = carts_.find(username);
    if (cartIt == carts_.end() || cartIt->second.empty()) {
        std::cout << "Cart is empty or user does not exist." << std::endl;
        return;
    }

    // Process each item in the cart
    std::vector<Product*>& cartItems = cartIt->second;
    std::vector<Product*>::iterator it = cartItems.begin();
    while (it != cartItems.end()) {
        Product* product = *it;
        // Check if product is in stock and user has enough credit
        if (product->getQty() > 0 && user->getBalance() >= product->getPrice()) {
            product->subtractQty(1);  // Reduce product quantity
            user->deductAmount(product->getPrice());  // Deduct amount from user's credit
            it = cartItems.erase(it);  // Remove product from cart
        } else {
            ++it;  // Move to the next item if not purchasable
        }
    }
}

>>>>>>> 4e4fe8c9d6258fbdf7dca7a936037170278e50a9
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
