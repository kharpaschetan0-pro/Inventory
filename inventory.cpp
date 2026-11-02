// Product Inventory Management System
// Data structure: Binary Search Tree (BST) keyed by product ID.
// Insertion, search and in-order display are O(log n) on average.

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

struct Product {
    int id;
    string name;
    int quantity;
    double price;
    Product *left, *right;

    Product(int i, const string& n, int q, double p)
        : id(i), name(n), quantity(q), price(p), left(nullptr), right(nullptr) {}
};

class Inventory {
    Product* root = nullptr;
    int count = 0;

    // Recursive insert. Returns false if the ID already exists.
    bool insert(Product*& node, int id, const string& name, int qty, double price) {
        if (!node) {
            node = new Product(id, name, qty, price);
            return true;
        }
        if (id < node->id) return insert(node->left, id, name, qty, price);
        if (id > node->id) return insert(node->right, id, name, qty, price);
        return false; // duplicate ID
    }

    Product* find(Product* node, int id) const {
        if (!node || node->id == id) return node;
        return id < node->id ? find(node->left, id) : find(node->right, id);
    }

    void inorder(Product* node) const {
        if (!node) return;
        inorder(node->left);
        cout << left << setw(8) << node->id
             << setw(22) << node->name
             << setw(10) << node->quantity
             << "$" << fixed << setprecision(2) << node->price << "\n";
        inorder(node->right);
    }

    void destroy(Product* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    ~Inventory() { destroy(root); }

    bool addProduct(int id, const string& name, int qty, double price) {
        if (insert(root, id, name, qty, price)) { ++count; return true; }
        return false;
    }

    void search(int id) const {
        Product* p = find(root, id);
        if (!p) { cout << "Product not found.\n"; return; }
        cout << "ID: " << p->id << " | Name: " << p->name
             << " | Qty: " << p->quantity
             << " | Price: $" << fixed << setprecision(2) << p->price << "\n";
    }

    void display() const {
        if (!root) { cout << "Inventory is empty.\n"; return; }
        cout << left << setw(8) << "ID" << setw(22) << "Name"
             << setw(10) << "Qty" << "Price\n"
             << string(48, '-') << "\n";
        inorder(root);
        cout << "Total products: " << count << "\n";
    }
};

// Safe numeric input helpers
int readInt(const string& prompt, int minVal = 0) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v && v >= minVal) break;
        cout << "Invalid input. Enter a whole number >= " << minVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return v;
}

double readPrice(const string& prompt) {
    double v;
    while (true) {
        cout << prompt;
        if (cin >> v && v >= 0) break;
        cout << "Invalid price.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return v;
}

int main() {
    Inventory inv;
    int choice;

    do {
        cout << "\n=== Inventory Menu ===\n"
             << "1. Add product\n2. Search product\n3. Display all\n0. Exit\n";
        choice = readInt("Choice: ");

        if (choice == 1) {
            int id = readInt("Product ID: ", 1);
            string name;
            cout << "Product name: ";
            getline(cin, name);
            int qty = readInt("Quantity: ");
            double price = readPrice("Price: ");

            if (inv.addProduct(id, name, qty, price))
                cout << "Product added.\n";
            else
                cout << "Error: ID " << id << " already exists.\n";
        } else if (choice == 2) {
            inv.search(readInt("Product ID to search: ", 1));
        } else if (choice == 3) {
            inv.display();
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}
