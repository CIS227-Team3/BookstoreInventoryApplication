#include <iostream>
#include <string>
#include <deque>

#ifndef list_h //guard
#define list_h

    using namespace std;

    class cart {
        
    public:
        deque<string> shoppingCart;
        string titleCart;
        string ISBNCart;
        int priceCart = 0;
};

#endif