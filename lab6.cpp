#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <string>

using namespace std;

class MobileApp {
public:
    virtual void display() const = 0;
    virtual void edit(const string& newName) = 0;
    virtual void saveToFile(ofstream& file) const = 0;
    virtual unique_ptr<MobileApp> clone() const = 0;
    virtual ~MobileApp() {}

protected:
    string name;
};

class GameApp : public MobileApp {
public:
    GameApp(const string& name) { this->name = name; }

    void display() const override {
        cout << "Game App: " << name << endl;
    }

    void edit(const string& newName) override {
        name = newName;
    }

    void saveToFile(ofstream& file) const override {
        file << "GameApp: " << name << endl;
    }

    unique_ptr<MobileApp> clone() const override {
        return make_unique<GameApp>(*this);
    }
};

class SocialMediaApp : public MobileApp {
public:
    SocialMediaApp(const string& name) { this->name = name; }

    void display() const override {
        cout << "Social Media App: " << name << endl;
    }

    void edit(const string& newName) override {
        name = newName;
    }

    void saveToFile(ofstream& file) const override {
        file << "SocialMediaApp: " << name << endl;
    }

    unique_ptr<MobileApp> clone() const override {
        return make_unique<SocialMediaApp>(*this);
    }
};

class ProductivityApp : public MobileApp {
public:
    ProductivityApp(const string& name) { this->name = name; }

    void display() const override {
        cout << "Productivity App: " << name << endl;
    }

    void edit(const string& newName) override {
        name = newName;
    }

    void saveToFile(ofstream& file) const override {
        file << "ProductivityApp: " << name << endl;
    }

    unique_ptr<MobileApp> clone() const override {
        return make_unique<ProductivityApp>(*this);
    }
};

class UtilityApp : public MobileApp {
public:
    UtilityApp(const string& name) { this->name = name; }

    void display() const override {
        cout << "Utility App: " << name << endl;
    }

    void edit(const string& newName) override {
        name = newName;
    }

    void saveToFile(ofstream& file) const override {
        file << "UtilityApp: " << name << endl;
    }

    unique_ptr<MobileApp> clone() const override {
        return make_unique<UtilityApp>(*this);
    }
};

class EducationApp : public MobileApp {
public:
    EducationApp(const string& name) { this->name = name; }

    void display() const override {
        cout << "Education App: " << name << endl;
    }

    void edit(const string& newName) override {
        name = newName;
    }

    void saveToFile(ofstream& file) const override {
        file << "EducationApp: " << name << endl;
    }

    unique_ptr<MobileApp> clone() const override {
        return make_unique<EducationApp>(*this);
    }
};

class MobileAppFactory {
public:
    virtual unique_ptr<MobileApp> createApp(const string& name) const = 0;
    virtual ~MobileAppFactory() {}
};

class GameAppFactory : public MobileAppFactory {
public:
    unique_ptr<MobileApp> createApp(const string& name) const override {
        return make_unique<GameApp>(name);
    }
};

class SocialMediaAppFactory : public MobileAppFactory {
public:
    unique_ptr<MobileApp> createApp(const string& name) const override {
        return make_unique<SocialMediaApp>(name);
    }
};

class ProductivityAppFactory : public MobileAppFactory {
public:
    unique_ptr<MobileApp> createApp(const string& name) const override {
        return make_unique<ProductivityApp>(name);
    }
};

class UtilityAppFactory : public MobileAppFactory {
public:
    unique_ptr<MobileApp> createApp(const string& name) const override {
        return make_unique<UtilityApp>(name);
    }
};

class EducationAppFactory : public MobileAppFactory {
public:
    unique_ptr<MobileApp> createApp(const string& name) const override {
        return make_unique<EducationApp>(name);
    }
};

class Laba6 {
private:
    class AppManager {
    private:
        vector<unique_ptr<MobileApp>> apps;

    public:
        void addApp(unique_ptr<MobileApp> app) {
            apps.push_back(move(app));
        }

        void deleteApp(size_t index) {
            if (index < apps.size()) {
                apps.erase(apps.begin() + index);
            }
        }

        void editApp(size_t index, const string& newName) {
            if (index < apps.size()) {
                apps[index]->edit(newName);
            }
        }

        void displayApps() const {
            for (const auto& app : apps) {
                app->display();
            }
        }

        void saveAppsToFile(const string& filename) const {
            ofstream file(filename);
            if (file.is_open()) {
                for (const auto& app : apps) {
                    app->saveToFile(file);
                }
            }
        }
    };

    AppManager manager;
    GameAppFactory gameFactory;
    SocialMediaAppFactory socialFactory;
    ProductivityAppFactory productivityFactory;
    UtilityAppFactory utilityFactory;
    EducationAppFactory educationFactory;

    void displayMenu() const {
        cout << "\nMenu:" << endl;
        cout << "1. Add App" << endl;
        cout << "2. Delete App" << endl;
        cout << "3. Edit App" << endl;
        cout << "4. Display Apps" << endl;
        cout << "5. Save Apps to File" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
    }

public:
    void run() {
        int choice;
        do {
            displayMenu();
            cin >> choice;

            switch (choice) {
                case 1: {
                    cout << "Choose App Type: \n1. Game \n2. Social Media \n3. Productivity \n"
                            "4. Utility \n5. Education" << endl;
                    int type;
                    cin >> type;
                    cout << "Enter App Name: ";
                    string name;
                    cin.ignore();
                    getline(cin, name);

                    switch (type) {
                        case 1:
                            manager.addApp(gameFactory.createApp(name));
                            break;
                        case 2:
                            manager.addApp(socialFactory.createApp(name));
                            break;
                        case 3:
                            manager.addApp(productivityFactory.createApp(name));
                            break;
                        case 4:
                            manager.addApp(utilityFactory.createApp(name));
                            break;
                        case 5:
                            manager.addApp(educationFactory.createApp(name));
                            break;
                        default:
                            cout << "Invalid type!" << endl;
                    }
                    break;
                }
                case 2: {
                    cout << "Enter App Index to Delete: ";
                    size_t index;
                    cin >> index;
                    manager.deleteApp(index);
                    break;
                }
                case 3: {
                    cout << "Enter App Index to Edit: ";
                    size_t index;
                    cin >> index;
                    cout << "Enter New Name: ";
                    string newName;
                    cin.ignore();
                    getline(cin, newName);
                    manager.editApp(index, newName);
                    break;
                }
                case 4:
                    manager.displayApps();
                    break;
                case 5: {
                    cout << "Enter Filename: ";
                    string filename;
                    cin >> filename;
                    manager.saveAppsToFile(filename);
                    break;
                }
                case 6:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
        } while (choice != 6);
    }
};

int main() {
    Laba6 laba;
    laba.run();
    return 0;
}
