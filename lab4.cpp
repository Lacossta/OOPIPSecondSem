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
        return name < other.name;
    }

    bool operator==(const MobileApp& other) const {
        return name == other.name && version == other.version;
    }
};

struct MobileAppHash {
    size_t operator()(const MobileApp& app) const {
        return hash<string>()(app.name) ^ hash<string>()(app.version);
    }
};

class Laba4 {
private:
    map<string, MobileApp> appMap;
    set<MobileApp> appSet;
    unordered_map<string, MobileApp> appUnorderedMap;
    multimap<string, MobileApp> appMultimap;
    unordered_multiset<MobileApp, MobileAppHash> appUnorderedMultiset;

public:
    void addApp(const MobileApp& app) {
        appMap[app.name] = app;
        appSet.insert(app);
        appUnorderedMap[app.name] = app;
        appMultimap.insert({app.name, app});
        appUnorderedMultiset.insert(app);
    }

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

    void editApp(const string& appName, const MobileApp& updatedApp) {
        deleteAppFromAll(appName);
        addApp(updatedApp);
    }

    void displayApps() const {
        for (const auto& [key, app] : appMap) {
            app.display();
        }
    }

    void saveToFile() const {
        ofstream file("../apps.txt");
        for (const auto& [key, app] : appMap) {
            file << app.name << "," << app.version << "," << app.releaseDate << ","
                 << app.status << "," << app.developer << "," << app.platform << "\n";
        }
        file.close();
    }

    void searchApp(const string& appName) const {
        auto it = appMap.find(appName);
        if (it != appMap.end()) {
            it->second.display();
        } else {
            cout << "Application not found.\n";
        }
    }

    void displayMap() const {
        cout << "--- Map ---" << endl;
        for (const auto& [key, app] : appMap) {
            app.display();
        }
    }

    void displaySet() const {
        cout << "--- Set ---" << endl;
        for (const auto& app : appSet) {
            app.display();
        }
    }

    void displayUnorderedMap() const {
        cout << "--- Unordered Map ---" << endl;
        for (const auto& [key, app] : appUnorderedMap) {
            app.display();
        }
    }

    void displayMultimap() const {
        cout << "--- Multimap ---" << endl;
        for (const auto& [key, app] : appMultimap) {
            app.display();
        }
    }

    void displayUnorderedMultiset() const {
        cout << "--- Unordered Multiset ---" << endl;
        for (const auto& app : appUnorderedMultiset) {
            app.display();
        }
    }

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
                    displayMap();
                    break;
                case 2:
                    displaySet();
                    break;
                case 3:
                    displayUnorderedMap();
                    break;
                case 4:
                    displayMultimap();
                    break;
                case 5:
                    displayUnorderedMultiset();
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
                    cin >> platform;
                    addApp(MobileApp(name, version, releaseDate, status, developer, platform));
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
                    displayApps();
                    break;
                case 4:
                    containerMenu();
                    break;
                case 5:
                    saveToFile();
                    cout << "Applications saved to file.\n";
                    break;
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

                    editApp(name, MobileApp(newName, version, releaseDate, status, developer, platform));
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Invalid choice.\n";
            }
        }
    }
};

void lab4() {
    Laba4 laba;
    laba.menu();
}
