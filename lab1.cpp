#include "lab1.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <map>
#include <fstream>

using namespace std;

class Toy {
protected:
    int amount;
    float price;
public:
    Toy(int amount, float price) : amount(amount), price(price) {}

    virtual void display() const {
        cout.setf(ios::left);
        cout << setw(10) << amount << setw(10) << fixed << setprecision(2) << price;
        cout.unsetf(ios::left);
    }
    float getPrice() const { return price; }
    int getAmount() const { return amount; }
    void setAmount(int amount) { this->amount = amount; }
    virtual string getType() const = 0;
    virtual string getName() const = 0;
};

class Bear : public Toy {
    string name;
    string collection;
    bool isAvailableToSpeak;
public:
    Bear(int amount, float price, string collection, bool isAvailableToSpeak, string name)
            : Toy(amount, price), collection(collection), isAvailableToSpeak(isAvailableToSpeak), name(name) {}

    void display() const override {
        cout.setf(ios::left);
        cout << setw(15) << "Bear" << setw(15) << name << setw(20) << collection
             << setw(10) << (isAvailableToSpeak ? "Yes" : "No");
        Toy::display();
        cout << endl;
        cout.unsetf(ios::left);
    }

    string getType() const override { return "Bear"; }
    string getName() const override { return name; }
};

class Doll : public Toy {
    string name;
    string collection;
    bool isAvailableToSpeak;
public:
    Doll(int amount, float price, string collection, bool isAvailableToSpeak, string name)
            : Toy(amount, price), collection(collection), isAvailableToSpeak(isAvailableToSpeak), name(name) {}

    void display() const override {
        cout.setf(ios::left);
        cout << setw(15) << "Doll" << setw(15) << name << setw(20) << collection
             << setw(10) << (isAvailableToSpeak ? "Yes" : "No");
        Toy::display();
        cout << endl;
        cout.unsetf(ios::left);
    }

    string getType() const override { return "Doll"; }
    string getName() const override { return name; }
};

class Order {
    map<string, pair<int, float>> purchasedToys;
public:
    void addToy(Toy* toy, int quantity) {
        string toyName = toy->getName();
        float totalPrice = quantity * toy->getPrice();
        if (purchasedToys.find(toyName) != purchasedToys.end()) {
            purchasedToys[toyName].first += quantity;
            purchasedToys[toyName].second += totalPrice;
        } else {
            purchasedToys[toyName] = make_pair(quantity, totalPrice);
        }
    }

    void displayOrder() const {
        cout << "\nOrder contains:" << endl;
        cout.setf(ios::left);
        cout << setw(15) << "Name" << setw(10) << "Quantity" << setw(10) << "Total" << endl;
        for (const auto& entry : purchasedToys) {
            cout << setw(15) << entry.first
                 << setw(10) << entry.second.first
                 << setw(10) << fixed << setprecision(2) << entry.second.second << endl;
        }
        cout.unsetf(ios::left);
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& entry : purchasedToys) {
            total += entry.second.second;
        }
        return total;
    }
};

class Customer {
private:
    string name;
    Order order;
public:
    Customer(const string& name) : name(name) {}
    void addToyToOrder(Toy* toy, int quantity) {
        order.addToy(toy, quantity);
    }
    void displayOrder() const {
        cout << "Customer: " << name << endl;
        order.displayOrder();
        cout << "Total Price: $" << fixed << setprecision(2) << order.calculateTotal() << endl;
    }
    string getName() const { return name; }
};

class Lab1 {
private:
    vector<Toy*> toys;
    vector<Customer> customers;

    int CheckToInt() {
        int number;
        while (true) {
            cin >> number;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "You didn't enter a number! Retry: ";
            } else {
                return number;
            }
        }
    }

public:
    Lab1() {
        toys = {
                new Doll(12, 3.3, "Doll Collection", true, "Dolly"),
                new Bear(12, 4.5, "Bear Collection", true, "BearBuddy")
        };
        customers = { Customer("Customer1"), Customer("Customer2") };
    }

    ~Lab1() {
        for (auto toy : toys) {
            delete toy;
        }
    }

    void shop(Customer& customer) {
        float totalPrice = 0;
        while (true) {
            cout << "\nВыберите пункт меню:" << endl
                 << "1. Просмотреть товар" << endl
                 << "2. Купить товар" << endl
                 << "3. Выход" << endl;
            switch (CheckToInt()) {
                default:
                    cout << "Тут нет такого варианта ответа" << endl;
                    break;
                case 1:
                    viewToys();
                    break;
                case 3:
                    customer.displayOrder();
                    return;
                case 2:
                    handlePurchase(customer, totalPrice);
                    break;
            }
        }
    }

    void viewToys() {
        cout << "\nAvailable Toys:\n";
        cout.setf(ios::left);
        cout << setw(15) << "Type" << setw(15) << "Name" << setw(20) << "Collection"
             << setw(10) << "Speak" << setw(10) << "Amount" << setw(10) << "Price" << endl;
        for (const auto& toy : toys) {
            toy->display();
        }
        cout.unsetf(ios::left);
    }

    void handlePurchase(Customer& customer, float& totalPrice) {
        viewToys();
        cout << "\nВыберите товар: ";
        int variant = CheckToInt();
        if (variant < 0 || variant >= toys.size()) {
            cout << "Invalid selection." << endl;
            return;
        }
        Toy* selectedToy = toys[variant];

        cout << "Введите кол-во товара: ";
        int amount = CheckToInt();
        if (amount <= selectedToy->getAmount()) {
            customer.addToyToOrder(selectedToy, amount);
            selectedToy->setAmount(selectedToy->getAmount() - amount);
            totalPrice += amount * selectedToy->getPrice();
            cout << "К оплате: $" << fixed << setprecision(2) << totalPrice << endl;
        } else {
            cout << "Товара не хватает на складе" << endl;
        }
    }

    void addToy() {
        cout << "Add a new toy (1 for Doll, 2 for Bear): ";
        int choice = CheckToInt();

        cout << "Enter amount: ";
        int amount = CheckToInt();

        cout << "Enter price: ";
        float price;
        cin >> price;

        cout << "Enter collection: ";
        string collection;
        cin >> collection;
        cout << "Is it available to speak (1 for Yes, 0 for No): ";

        bool canSpeak;
        cin >> canSpeak;
        cout << "Enter name: ";

        string name;
        cin >> name;

        if (choice == 1) {
            toys.push_back(new Doll(amount, price, collection, canSpeak, name));
        } else if (choice == 2) {
            toys.push_back(new Bear(amount, price, collection, canSpeak, name));
        }
    }

    void run() {
        while (true) {
            cout << endl << "Выберите действие:" << endl
                 << "1. Выбрать покупателя" << endl
                 << "2. Посмотреть товары" << endl
                 << "3. Добавить товар" << endl
                 << "4. Выйти" << endl;

            switch (CheckToInt()) {
                case 1: {
                    cout << "Выберите покупателя:" << endl;
                    for (size_t i = 0; i < customers.size(); ++i) {
                        cout << i + 1 << ". " << customers[i].getName() << endl;
                    }
                    int customerIndex = CheckToInt() - 1;
                    if (customerIndex < 0 || customerIndex >= customers.size()) {
                        cout << "Неверный выбор, завершение программы." << endl;
                        return;
                    }
                    shop(customers[customerIndex]);
                    break;
                }
                case 2:
                    viewToys();
                    break;
                case 3:
                    addToy();
                    break;
                case 4:
                    return;
                default:
                    cout << "Неверный выбор, попробуйте снова." << endl;
                    break;
            }
        }
    }
};

int main() {
    Lab1 lab;
    lab.run();
    return 0;
}

//это 1-2 лаба т.к я просто доработал первую