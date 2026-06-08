#include <iostream>
#include <fstream>

#include "menu.h"

#include "../models/Product.h"

#include "../structures/LinkedList.h"

#include "../algorithms/Search.h"

#include "../algorithms/Sort.h"

#include "../json/json.hpp"

using namespace std;

using json = nlohmann::json;

void saveProductJSON(
    int id,
    string name,
    int price
) {

    json product;

    product["id"] = id;

    product["name"] = name;

    product["price"] = price;

    json data;

    ifstream inputFile(
        "products.json"
    );

    if(inputFile.is_open()) {

        inputFile >> data;

        inputFile.close();
    }

    if(!data.is_array()) {

        data = json::array();
    }

    data.push_back(product);

    ofstream outputFile(
        "products.json"
    );

    outputFile
        << data.dump(4);

    outputFile.close();
}

int main() {

    LinkedList productList;

    string loginName;
    string loginNPM;

    cout << "===== LOGIN ====="
         << endl;

    cout << "Input Name : ";

    getline(cin, loginName);

    cout << "Input NPM : ";

    getline(cin, loginNPM);

    cout << "Login Success!"
         << endl;

    int choice;

    do {

        Menu::showMenu();

        cin >> choice;

        cin.ignore();

        switch(choice) {

        case 1: {

            int id;
            string name;
            int price;

            cout << "===== ADD PRODUCT ====="
                 << endl;

            cout << "Input Product ID : ";

            cin >> id;

            cin.ignore();

            cout << "Input Product Name : ";

            getline(cin, name);

            cout << "Input Product Price : ";

            cin >> price;

            Product p(
                id,
                name,
                price
            );

            productList.insert(p);

            saveProductJSON(
                id,
                name,
                price
            );

            cout << "Product Added!"
                 << endl;

            break;
        }

        case 2: {

            cout << "===== PRODUCT LIST ====="
                 << endl;

            productList.display();

            break;
        }

        case 3: {

            string keyword;

            cout << "===== SEARCH PRODUCT ====="
                 << endl;

            cout << "Input Product Name : ";

            getline(cin, keyword);

            linearSearch(
                productList,
                keyword
            );

            break;
        }

        case 4: {

            Node* temp =
                productList.getHead();

            Product arr[100];

            int n = 0;

            while(temp != NULL) {

                arr[n] = temp->data;

                temp = temp->next;

                n++;
            }

            bubbleSort(arr, n);

            cout << "===== SORTED PRODUCT ====="
                 << endl;

            for(int i = 0; i < n; i++) {

                arr[i].display();
            }

            break;
        }

        case 5: {

            string message;

            cout << "===== CHAT SELLER ====="
                 << endl;

            cout << "Input Message : ";

            getline(cin, message);

            cout << "Message Sent : "
                 << message
                 << endl;

            break;
        }

        case 6:

            cout << "Logout Success!"
                 << endl;

            break;

        default:

            cout << "Invalid Menu!"
                 << endl;
        }

        cout << endl;

    } while(choice != 6);

    return 0;
}