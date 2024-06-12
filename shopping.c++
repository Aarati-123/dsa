#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void login(std::string& username) {
    std::cout << "Enter your username: ";
    std::cin >> username;
    // Check if the username exists in the file
    std::ifstream file("users.txt");
    std::string line;
    bool found = false;
    while (std::getline(file, line)) {
        if (line == username) {
            found = true;
            break;
        }
    }
    file.close();
    if (!found) {
        std::cout << "Username not found. Please sign up.\n";
        username = "";
    }
}

void signup(std::string& username) {
    std::cout << "Enter a new username: ";
    std::cin >> username;
    // Check if the username already exists in the file
    std::ifstream file("users.txt");
    std::string line;
    bool found = false;
    while (std::getline(file, line)) {
        if (line == username) {
            found = true;
            break;
        }
    }
    file.close();
    if (found) {
        std::cout << "Username already exists. Please login.\n";
        username = "";
    } else {
        // Add the new username to the file
        std::ofstream outfile("users.txt", std::ios_base::app);
        outfile << username << "\n";
        outfile.close();
    }
}

void shopping(const std::string& username) {
    std::vector<std::string> inventory = {"apple", "banana", "bread", "milk", "eggs", "cheese", "juice"};
    std::vector<std::string> shoppingList;

    std::cout << "Enter items for your shopping list (type 'done' to finish):\n";
    std::string item;
    while (true) {
        std::cin >> item;
        if (item == "done") break;
        shoppingList.push_back(item);
    }

    std::cout << "\nChecking availability:\n";
    for (const auto& item : shoppingList) {
        bool available = std::find(inventory.begin(), inventory.end(), item) != inventory.end();
        std::cout << item << ": " << (available ? "Available" : "Not available") << "\n";
    }

    // Store the shopping list in a file
    std::ofstream file(username + "_history.txt", std::ios_base::app);
    if (file.is_open()) {
        file << "Shopping list:\n";
        for (const auto& item : shoppingList) {
            file << "- " << item << "\n";
        }
        file << "\n";
        file.close();
        std::cout << "Shopping list saved successfully.\n";
    } else {
        std::cout << "Failed to save shopping list.\n";
    }
}

int main() {
    std::string username;
    int choice;
    do {
        std::cout << "Enter 1 to login or 2 to sign up: ";
        std::cin >> choice;
        if (choice == 1) {
            login(username);
        } else if (choice == 2) {
            signup(username);
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (username.empty());

    std::cout << "Welcome, " << username << "!\n";

    shopping(username);

    return 0;
}
