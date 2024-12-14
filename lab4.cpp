#include "lab4.h"
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

class MobileApp {
public:
    string name;
    string version;
    string releaseDate;
    string status;
    string developer;
    string platform;

    MobileApp() = default;

    MobileApp(const string& name, const string& version, const string& releaseDate,
              const string& status, const string& developer, const string& platform)
            : name(name), version(version), releaseDate(releaseDate), status(status), developer(developer), platform(platform) {}

    void display() const {
        cout << "Name: " << name << ", Version: " << version
             << ", Release Date: " << releaseDate << ", Status: " << status
             << ", Developer: " << developer << ", Platform: " << platform << endl;
    }

    bool operator<(const MobileApp& other) const {
        return name < other.name; // Используется для контейнеров, где нужно сравнение
    }

    bool operator==(const MobileApp& other) const {
        return name == other.name && version == other.version;
    }
};

// Хэш-функция для MobileApp для работы с unordered-контейнерами
struct MobileAppHash {
    size_t operator()(const MobileApp& app) const {
        return hash<string>()(app.name) ^ hash<string>()(app.version);
    }
};

// --- Containers ---
map<string, MobileApp> appMap;                                     // уникальные сортированные
set<MobileApp> appSet;                                             // уникальные сортированные
unordered_map<string, MobileApp> appUnorderedMap;                  // уникальные без порядка
multimap<string, MobileApp> appMultimap;                           // ключ копирование сорт
unordered_multiset<MobileApp, MobileAppHash> appUnorderedMultiset; // без ключ копирование не сорт

// add
void addApp(map<string, MobileApp>& container, const MobileApp& app) {
    container[app.name] = app;
    appSet.insert(app);
    appUnorderedMap[app.name] = app;
    appMultimap.insert({app.name, app});
    appUnorderedMultiset.insert(app);
}

// remove
void deleteAppFromAll(const string& appName) {
    appMap.erase(appName);

    auto itSet = find_if(appSet.begin(), appSet.end(), [&appName](const MobileApp& app) {
        return app.name == appName;
    });
    if (itSet != appSet.end()) appSet.erase(itSet);

    appUnorderedMap.erase(appName);

    auto range = appMultimap.equal_range(appName);
    appMultimap.erase(range.first, range.second);

    for (auto it = appUnorderedMultiset.begin(); it != appUnorderedMultiset.end();) {
        if (it->name == appName) {
            it = appUnorderedMultiset.erase(it);
        } else {
            ++it;
        }
    }
}

// rewrite
void editApp(map<string, MobileApp>& container, const string& appName, const MobileApp& updatedApp) {
    deleteAppFromAll(appName);
    addApp(container, updatedApp);// перезаписываем
}

void displayApps(const map<string, MobileApp>& container) {
    for (const auto& [key, app] : container) {
        app.display();
    }
}

// to file
void saveToFile(const map<string, MobileApp>& container) {
    ofstream file("../apps.txt");
    for (const auto& [key, app] : container) {
        file << app.name << "," << app.version << "," << app.releaseDate << ","
             << app.status << "," << app.developer << "," << app.platform << "\n";
    }
    file.close();
}

// search
void searchApp(const map<string, MobileApp>& container, const string& appName) {
    auto it = container.find(appName);
    if (it != container.end()) {
        it->second.display();
    } else {
        cout << "Application not found.\n";
    }
}

// sort
void sortAppsByName(map<string, MobileApp>& container) {
    cout << "Applications are already sorted by name.\n";
}

//displays
void displayMap(const map<string, MobileApp>& container) {
    cout << "--- Map ---" << endl;
    for (const auto& [key, app] : container) {
        app.display();
    }
}

void displaySet(const set<MobileApp>& container) {
    cout << "--- Set ---" << endl;
    for (const auto& app : container) {
        app.display();
    }
}

void displayUnorderedMap(const unordered_map<string, MobileApp>& container) {
    cout << "--- Unordered Map ---" << endl;
    for (const auto& [key, app] : container) {
        app.display();
    }
}

void displayMultimap(const multimap<string, MobileApp>& container) {
    cout << "--- Multimap ---" << endl;
    for (const auto& [key, app] : container) {
        app.display();
    }
}

void displayUnorderedMultiset(const unordered_multiset<MobileApp, MobileAppHash>& container) {
    cout << "--- Unordered Multiset ---" << endl;
    for (const auto& app : container) {
        app.display();
    }
}

// container menu
void containerMenu() {
    while (true) {
        cout << "\n--- Container Management Menu ---" << endl;
        cout << "1. Display Map" << endl;
        cout << "2. Display Set" << endl;
        cout << "3. Display Unordered Map" << endl;
        cout << "4. Display Multimap" << endl;
        cout << "5. Display Unordered Multiset" << endl;
        cout << "6. Delete from all containers" << endl;
        cout << "0. Return to main menu" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                displayMap(appMap);
                break;
            case 2:
                displaySet(appSet);
                break;
            case 3:
                displayUnorderedMap(appUnorderedMap);
                break;
            case 4:
                displayMultimap(appMultimap);
                break;
            case 5:
                displayUnorderedMultiset(appUnorderedMultiset);
                break;
            case 6: {
                string name;
                cout << "Enter name of application to delete from all containers: ";
                cin >> name;
                deleteAppFromAll(name);
                cout << "Application deleted from all containers.\n";
                break;
            }

            case 0:
                return;
            default:
                cout << "Invalid choice.\n";
        }
    }
}

// main menuuuu
void menu() {
    while (true) {
        cout << "\n--- Mobile App Management ---" << endl;
        cout << "1. Add application" << endl;
        cout << "2. Delete application from all containers" << endl;
        cout << "3. Display all applications (from Map)" << endl;
        cout << "4. Container Management Menu" << endl;
        cout << "5. Save to file" << endl;
        cout << "6. Edit application" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, version, releaseDate, status, developer, platform;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter version: ";
                cin >> version;
                cout << "Enter release date: ";
                cin >> releaseDate;
                cout << "Enter status: ";
                cin >> status;
                cout << "Enter developer: ";
                cin >> developer;
                cout << "Enter platform: ";
                cin >> platform;addApp(appMap, MobileApp(name, version, releaseDate, status, developer, platform));
                break;
            }
            case 2: {
                string name;
                cout << "Enter name of application to delete from all containers: ";
                cin >> name;
                deleteAppFromAll(name);
                cout << "Application deleted from all containers.\n";
                break;
            }
            case 3:
                displayMap(appMap);
                break;
            case 4:
                containerMenu();
                break;
            case 5: {
                saveToFile(appMap);
                cout << "Applications saved to file.\n";
                break;
            }
            case 6: {
                string name;
                cout << "Enter name of application to edit: ";
                cin >> name;

                string newName, version, releaseDate, status, developer, platform;
                cout << "Enter new name: ";
                cin >> newName;
                cout << "Enter new version: ";
                cin >> version;
                cout << "Enter new release date: ";
                cin >> releaseDate;
                cout << "Enter new status: ";
                cin >> status;
                cout << "Enter new developer: ";
                cin >> developer;
                cout << "Enter new platform: ";
                cin >> platform;

                editApp(appMap, name, MobileApp(newName, version, releaseDate, status, developer, platform));
                break;
            }
            case 0:
                return;
            default:
                cout << "Invalid choice.\n";
        }
    }
}

void lab4() {
    menu();
}