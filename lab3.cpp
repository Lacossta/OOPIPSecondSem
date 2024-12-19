#include "lab3.h"
#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <algorithm>
#include <fstream>
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

    // constructor
    MobileApp(const string& name, const string& version, const string& releaseDate,
              const string& status, const string& developer, const string& platform)
            : name(name), version(version), releaseDate(releaseDate), status(status), developer(developer), platform(platform) {}

    // display
    void display() const {
        cout << "Name: " << name << ", Version: " << version
             << ", Release Date: " << releaseDate << ", Status: " << status
             << ", Developer: " << developer << ", Platform: " << platform << endl;
    }
};

class Laba3 {
private:
    vector<MobileApp> apps;               // main
    list<MobileApp> recentApps;           // last add
    array<MobileApp, 5> topApps;          // top 5 last

public:
    void addApp(const MobileApp& app) {
        apps.push_back(app);
        recentApps.push_back(app);
        if (recentApps.size() > 5) {
            recentApps.pop_front(); // keep last 5
        }
    }

    void updateTopApps() {
        vector<MobileApp> sortedApps = apps;
        sort(sortedApps.begin(), sortedApps.end(), [](const MobileApp& a, const MobileApp& b) {
            return a.name < b.name;
        });
        for (size_t i = 0; i < topApps.size() && i < sortedApps.size(); ++i) {
            topApps[i] = sortedApps[i];
        }
    }

    void deleteApp(const string& appName) {
        apps.erase(remove_if(apps.begin(), apps.end(),
                             [&appName](const MobileApp& app) { return app.name == appName; }),
                   apps.end());
    }

    void editApp(const string& appName, const MobileApp& updatedApp) {
        for (auto& app : apps) {
            if (app.name == appName) {
                app = updatedApp;
                break;
            }
        }
    }

    void displayApps() const {
        for (const auto& app : apps) {
            app.display();
        }
    }

    void displayRecentApps() const {
        cout << "Recently Added Apps:\n";
        for (const auto& app : recentApps) {
            app.display();
        }
    }

    void displayTopApps() const {
        cout << "Top 5 Apps:\n";
        for (const auto& app : topApps) {
            if (!app.name.empty()) {
                app.display();
            }
        }
    }

    void saveToFile() const {
        string filename = "../file.txt";
        ofstream file(filename);
        for (const auto& app : apps) {
            file << app.name << "," << app.version << "," << app.releaseDate << ","
                 << app.status << "," << app.developer << "," << app.platform << "\n";
        }
    }

    void sortAppsByName() {
        sort(apps.begin(), apps.end(), [](const MobileApp& a, const MobileApp& b) {
            return a.name < b.name;
        });
    }

    void searchApp(const string& appName) const {
        auto it = find_if(apps.begin(), apps.end(), [&appName](const MobileApp& app) {
            return app.name == appName;
        });
        if (it != apps.end()) {
            it->display();
        } else {
            cout << "Application not found.\n";
        }
    }

    int static CheckToInt() {
        int number;
        while (true) {
            cin >> number;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "You didn't enter a number! Retry " << endl;
            } else {
                break;
            }
        }
        return number;
    }

    void menu() {
        while (true) {
            cout << "\n--- Mobile App Management ---" << endl;
            cout << "1. Add application" << endl;
            cout << "2. Delete application" << endl;
            cout << "3. Edit application" << endl;
            cout << "4. Display all applications" << endl;
            cout << "5. Display recent applications" << endl;
            cout << "6. Display top applications" << endl;
            cout << "7. Save to file " << endl;
            cout << "8. Sort applications by name" << endl;
            cout << "9. Search application by name" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            int choice = CheckToInt();
            cout << endl;

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
                    updateTopApps();
                    break;
                }

                case 2: {
                    string name;

                    cout << "Enter name of application to delete: ";
                    cin >> name;

                    deleteApp(name);
                    updateTopApps();
                    break;
                }

                case 3: {
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
                    updateTopApps();
                    break;
                }

                case 4: {
                    displayApps();
                    break;
                }

                case 5: {
                    displayRecentApps();
                    break;
                }

                case 6: {
                    displayTopApps();
                    break;
                }

                case 7: {
                    cout << "Saving....";
                    saveToFile();
                    break;
                }

                case 8: {
                    sortAppsByName();
                    cout << "Applications sorted by name.\n";
                    break;
                }

                case 9: {
                    string name;

                    cout << "Enter name of application to search: ";
                    cin >> name;

                    searchApp(name);
                    break;
                }

                case 0: {
                    return;
                }

                default: {
                    cout << "Invalid choice: " << choice << endl;
                }
            }
        }
    }

    void run() {
        menu();
    }
};

int main() {
    Laba3 appManager;
    appManager.run();
    return 0;
}
