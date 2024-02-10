#include "MyDataStore.h"
#include "util.h"  

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
    // Iterate through the map of products and delete Product pointers

    for (std::map<std::string, Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {

        delete it->second;  // Free the dynamically allocated Product
    }
    // Iterate through the map of users and delete User pointers
    for (std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {

        delete it->second;  // Free the dynamically allocated User
    }
}

void MyDataStore::addProduct(Product* p) {
    // Insert the product into the products map
    products_.insert(std::make_pair(p->getName(), p));

    // Get the keywords for the product
    std::set<std::string> keywords = p->keywords();

    // Insert the product into the keyword index for each keyword
    for (const std::string& keyword : keywords) {

        keywordIndex_[keyword].insert(p);
    }
}

void MyDataStore::addUser(User* u) {

    users_.insert(make_pair(u->getName(), u)); 
}

void MyDataStore::addProductToCart(const std::string& username, Product* p) {
    std::map<std::string, std::vector<Product*>>::iterator it = carts_.find(username);
    if (it == carts_.end()) {
        carts_[username] = std::vector<Product*>();  // Initialize an empty cart for new user
    }
    carts_[username].push_back(p); }

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
        std::set<Product*> results;

    if (type == 0) { // AND search

        bool isFirstTerm = true;
        for (const std::string& term : terms) {

            if (keywordIndex_.find(term) == keywordIndex_.end()) {

                return std::vector<Product*>(); // Term not found, return empty result
            }

            if (isFirstTerm) {

                results = keywordIndex_[term];
                isFirstTerm = false;
            } 
            else {

                std::set<Product*> termResults = keywordIndex_[term];
                std::set<Product*> intersection;
                std::set_intersection(results.begin(), results.end(), termResults.begin(), termResults.end(),
                                        std::inserter(intersection, intersection.begin()));
                results = intersection;
            }

            if (results.empty()) {

                break; // No need to continue if no products match
            }
        }
    } 
    else { // OR search

        for (const std::string& term : terms) {

            if (keywordIndex_.find(term) != keywordIndex_.end()) {

                std::set<Product*>& termProducts = keywordIndex_[term];
                results.insert(termProducts.begin(), termProducts.end());
            }
        }
    }

    return std::vector<Product*>(results.begin(), results.end());
}

void MyDataStore::viewCart(const std::string& username) {
    std::map<std::string, std::vector<Product*>>::iterator it = carts_.find(username);
    if (it == carts_.end() || it->second.empty()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    // Display each product in the cart
    const std::vector<Product*>& cartItems = it->second;
    for (size_t i = 0; i < cartItems.size(); ++i) {
        std::cout << "Item " << i + 1 << "\n" << cartItems[i]->displayString() << std::endl;
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
        } 

        else {
            ++it;  // Move to the next item if not purchasable
        }
    }
}

bool MyDataStore::userExists(const std::string& username) const {

    return users_.find(username) != users_.end();
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
