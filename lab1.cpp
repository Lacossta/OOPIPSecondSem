#include "lab1.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <map>
#include <fstream>

using namespace std;

//class
class Toy {
protected:
    int amount;
    float price;
public:
    Toy(int amount, float price) : amount(amount), price(price) {}

    virtual void display() const {
        cout.setf(ios::left); // set flag
        cout << setw(10) << amount << setw(10) << fixed << setprecision(2) << price;
        cout.unsetf(ios::left); // remove flags
    }
    float getPrice() const {
        return price;
    }
    int getAmount() const {
        return amount;
    }
    void setAmount(int amount) {
        this->amount = amount;
    }
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
    string getType() const override {
        return "Bear";
    }
    string getName() const override {
        return name;
    }
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

    string getType() const override {
        return "Doll";
    }

    string getName() const override {
        return name;
    }
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
    string getName() const {
        return name;
    }
};
//class

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

ostream& operator<<(ostream& os, const Toy& toy) {
    os << toy.getName() << " " << toy.getAmount() << " " << toy.getPrice() << endl;
    return os;
} // simple

ostream& operator<<(ostream& os, const Toy* toy) {
    if (toy) {
        os << toy->getType() << " " <<  toy->getName()
           << " " << toy->getAmount() << " " << toy->getPrice();

    }
    return os;
} // vector

istream& operator>>(istream& is, Toy& toy) {
    string type, name;
    int amount;
    float price;
    is >> type >> name >> amount >> price;
    toy.setAmount(amount);
    return is;
}


//file
void addToyToFile(const Toy& toy) {
    ofstream outfile("../F.txt", ios::app);
    if (outfile.is_open()) {
        cout << toy;
        outfile << toy;
        outfile.close();
        cout  << endl << "Товар добавлен." << endl;
    } else {
        cerr << "Error opening file for writing.\n";
    }
}

void viewToysFromFile() {
    ifstream infile("../F.txt");
    if (infile.is_open()) {
        string line;
        if (infile.peek() == ifstream::traits_type::eof()) {
            cout << endl << "Файл пуст" << endl << endl;
        }
        else {
            string line;
            cout << endl;
            while (getline(infile, line)) {
                cout << line << endl;
            }
            cout << endl;
        }
        infile.close();
    }
    else {
        cerr << "Error opening file for reading.\n";
    }
}

void searchToyInFile(const string& searchName) {
    ifstream infile("../F.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            if (line.find(searchName) != string::npos) {
                cout << "Found: " << line << endl;
                return;
            }
        }
        infile.close();
        cout << "Товар не найден" << endl;
    } else {
        cerr << "Error opening file for searching.\n";
    }
}

bool checkIsInFile(const string& searchName) {
    ifstream infile("../F.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            if (line.find(searchName) != string::npos) {
                return true;
            }
        }
        infile.close();
    } else {
        cerr << "Error opening file for searching.\n";
    }
}

void deleteToyFromFile(const string& toyName) {
    string filename = "../F.txt";
    ifstream infile(filename);
    ofstream outfile("../temp.txt");

    if (infile.is_open() && outfile.is_open()) {
        string line;
        while (getline(infile, line)) {
            if (line.find(toyName) == string::npos) {
                outfile << line << endl;
            }
        }
        infile.close();
        outfile.close();
        remove(filename.c_str());
        rename("../temp.txt", filename.c_str());
    }
    else {
        cerr << "Error opening files for deletion.\n";
    }
}
//file

//logic
void shop(Customer &customer, Doll &doll, Bear &bear, float &totalPrice) {
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
                cout << "\nТовары в наличии:" << endl;
                cout.setf(ios::left);
                cout << setw(15) << "Type" << setw(15) << "Name" << setw(20) << "Collection"
                     << setw(10) << "Speak" << setw(10) << "Amount" << setw(10) << "Price" << endl;
                doll.display();
                bear.display();
                cout.unsetf(ios::left);
                break;
            case 3:
                customer.displayOrder();
                return;
            case 2:
                cout << "1 ";
                doll.display();
                cout << "2 ";
                bear.display();
                cout << "Выберите товар: " << endl;
                int variant = CheckToInt();
                cout << "Введите кол-во товара: ";
                int amount = CheckToInt();
                switch (variant) {
                    case 1:
                        if (amount <= doll.getAmount()) {
                            customer.addToyToOrder(&doll, amount);
                            doll.setAmount(doll.getAmount() - amount);
                            totalPrice += amount * doll.getPrice();
                            cout << "К оплате: $" << fixed << setprecision(2) << totalPrice << endl;
                        } else {
                            cout << "Товара не хватает на складе" << endl;
                        }
                        break;
                    case 2:
                        if (amount <= bear.getAmount()) {
                            customer.addToyToOrder(&bear, amount);
                            bear.setAmount(bear.getAmount() - amount);
                            totalPrice += amount * bear.getPrice();
                            cout << "К оплате: $" << fixed << setprecision(2) << totalPrice << endl;
                        } else {
                            cout << "Товара не хватает на складе" << endl;
                        }
                        break;
                    default:
                        cout << "Тут нет такого варианта ответа" << endl;
                        break;
                }
                break;
        }
    }
}

void viewToys(const vector<Toy*>& toys) {
    cout << "\nAvailable Toys:\n";
    cout.setf(ios::left);
    cout << setw(17) << "  Type" << setw(15) << "Name" << setw(20) << "Collection"
         << setw(10) << "Speak" << setw(10) << "Amount" << setw(10) << "Price" << endl
         << "==============================================================================" << endl;
    int counter = 0;
    for (const auto& toy : toys) {
        cout << counter << " ";
        toy->display();
        counter++;
    }
    cout.unsetf(ios::left);
}

void addToy(vector<Toy*>& toys) {
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

void editToy(vector<Toy*>& toys) {
    cout << "Enter the name of the toy to edit: ";
    string name;
    cin >> name;
    for (auto& toy : toys) {
        if (toy->getName() == name) {
            cout << "Enter new amount: ";
            int amount = CheckToInt();
            cout << "Enter new price: ";
            float price;
            cin >> price;
            toy->setAmount(amount);
            cout << "Toy updated.\n";
            return;
        }
    }
    cout << "Toy not found.\n";
}

void sortToys(vector<Toy*>& toys) {
    cout << "Sorting toys by name...\n";
    sort(toys.begin(), toys.end(), [](Toy* a, Toy* b) {
        return a->getName() < b->getName();
    });
    cout << "Toys sorted.\n";
}

bool searchToy(const vector<Toy*>& toys, const string name) {
    for (const auto& toy : toys) {
        if (toy->getName() == name) {
            cout << "Toy found:\n";
            toy->display();
            return true;
        }
    }
    return false;
}
//logic


//menus
void fileWork(vector<Toy*> &toys){
    while(true){
        cout << "Работа с файлами:" << endl
             << "1. Посмотреть игрушки в файле" << endl
             << "2. Добавить игрушку в файл" << endl
             << "3. Найти игрушку в файле" << endl
             << "4. Удалить игрушку из файла" << endl;
        int fileOption = CheckToInt();
        switch (fileOption) {
            case 1:
                viewToysFromFile();
                break;
            case 2: {
                viewToys(toys);
                cout << endl << "Выберите товар для добавления: ";
                int number = CheckToInt();
                if(number >= 0 && number < toys.size()) {
                    if (checkIsInFile(toys[number]->getName()) == false) {
                        addToyToFile(*toys[number]);
                    }
                    else {
                        cout << "Товар уже есть в файле" << endl;
                    }
                }
                else{
                    cout << "Invalid index))))" << endl;
                }
                break;
            }
            case 3: {
                cout << "Введите имя игрушки для поиска в файле: ";
                string searchName;
                cin >> searchName;
                searchToyInFile(searchName);
                break;
            }
            case 4: {
                viewToysFromFile();
                cout << "Введите имя игрушки для удаления из файла: ";
                string deleteName;
                cin >> deleteName;
                deleteToyFromFile(deleteName);
                break;
            }
            case -1:
                return;
            default:
                cout << "Неверный выбор." << endl;
                break;
        }
    }
    }

void lab1() {
    vector<Toy*> toys = {
            new Doll(12, 3.3, "Doll Collection", true, "Dolly"),
            new Doll(13, 2.3, "dfojsdif", true, "Dolly2"),
            new Doll(14, 3.39, "f", true, "Dolly3"),
            new Bear(12, 4.5, "Bear Collection", true, "BearBuddy")
    };
    vector<Customer> customers = { Customer("Customer1"), Customer("Customer2") };


    while (true) {
        cout << endl << "Выберите действие:" << endl
             << "1. Выбрать покупателя" << endl
             << "2. Посмотреть товары" << endl
             << "3. Добавить товар" << endl
             << "4. Редактировать товар" << endl
             << "5. Сортировать товары" << endl
             << "6. Найти товар" << endl
             << "7. Работа с файлами" << endl
             << "8. Выйти" << endl;

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
                Customer &currentCustomer = customers[customerIndex];
                float totalPrice = 0;
                shop(currentCustomer, *dynamic_cast<Doll*>(toys[0]), *dynamic_cast<Bear*>(toys[1]), totalPrice);
                break;
            }
            case 2:
                viewToys(toys);
                break;
            case 3:
                addToy(toys);
                break;
            case 4:
                editToy(toys);
                break;
            case 5:
                sortToys(toys);
                break;
            case 6: {
                string name;
                cin >> name;
                if (searchToy(toys, name)) {
                    cout << "Товар найден" << endl;
                } else {
                    cout << "Товар не найден" << endl;
                };
                break;
            }
            case 7:
                fileWork(toys);
                break;
            case 8:
                for (auto toy : toys) {
                    delete toy;
                }
                return;
            default:
                cout << "Неверный выбор, попробуйте снова." << endl;
                break;
        }
    }
}
//menus