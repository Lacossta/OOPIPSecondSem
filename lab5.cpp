#include "lab5.h"

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

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
            : name(name), version(version), releaseDate(releaseDate),
              status(status), developer(developer), platform(platform) {}

    void display() const {
        cout << "Name: " << name << ", Version: " << version
             << ", Release Date: " << releaseDate << ", Status: " << status
             << ", Developer: " << developer << ", Platform: " << platform << endl;
    }

    bool operator<(const MobileApp& other) const {
        return name > other.name;
    }
};

class Laba5 {
private:
    queue<MobileApp> appQueue;
    stack<MobileApp> appStack;
    priority_queue<MobileApp> appPriorityQueue;

public:
    void addAppToQueue(const MobileApp& app) {
        appQueue.push(app);
    }

    void addAppToStack(const MobileApp& app) {
        appStack.push(app);
    }

    void addAppToPriorityQueue(const MobileApp& app) {
        appPriorityQueue.push(app);
    }

    void deleteFromQueue() {
        if (!appQueue.empty()) {
            appQueue.pop();
            cout << "Application removed from queue.\n";
        } else {
            cout << "Queue is empty.\n";
        }
    }

    void deleteFromStack() {
        if (!appStack.empty()) {
            appStack.pop();
            cout << "Application removed from stack.\n";
        } else {
            cout << "Stack is empty.\n";
        }
    }

    void deleteFromPriorityQueue() {
        if (!appPriorityQueue.empty()) {
            appPriorityQueue.pop();
            cout << "Application removed from priority queue.\n";
        } else {
            cout << "Priority queue is empty.\n";
        }
    }

    template <typename Container>
    void displayContainer(Container& container) {
        cout << "--- Displaying Container ---\n";

        if constexpr (is_same_v<Container, queue<MobileApp>>) {
            queue<MobileApp> temp = container;
            while (!temp.empty()) {
                temp.front().display();
                temp.pop();
            }
        } else if constexpr (is_same_v<Container, stack<MobileApp>>) {
            stack<MobileApp> temp = container;
            while (!temp.empty()) {
                temp.top().display();
                temp.pop();
            }
        } else if constexpr (is_same_v<Container, priority_queue<MobileApp>>) {
            priority_queue<MobileApp> temp = container;
            while (!temp.empty()) {
                temp.top().display();
                temp.pop();
            }
        }
    }

    template <typename Container>
    void saveToFile(Container& container, const string& filename) {
        ofstream file(filename);

        if constexpr (is_same_v<Container, queue<MobileApp>>) {
            queue<MobileApp> temp = container;
            while (!temp.empty()) {
                const MobileApp& app = temp.front();
                file << app.name << "," << app.version << "," << app.releaseDate << ","
                     << app.status << "," << app.developer << "," << app.platform << "\n";
                temp.pop();
            }
        } else if constexpr (is_same_v<Container, stack<MobileApp>>) {
            stack<MobileApp> temp = container;
            while (!temp.empty()) {
                const MobileApp& app = temp.top();
                file << app.name << "," << app.version << "," << app.releaseDate << ","
                     << app.status << "," << app.developer << "," << app.platform << "\n";
                temp.pop();
            }
        } else if constexpr (is_same_v<Container, priority_queue<MobileApp>>) {
            priority_queue<MobileApp> temp = container;
            while (!temp.empty()) {
                const MobileApp& app = temp.top();
                file << app.name << "," << app.version << "," << app.releaseDate << ","
                     << app.status << "," << app.developer << "," << app.platform << "\n";
                temp.pop();
            }
        }

        file.close();
        cout << "Container saved to file: " << filename << endl;
    }

    void containerMenu() {
        while (true) {
            cout << "\n--- Container Management Menu ---" << endl;
            cout << "1. Display Queue" << endl;
            cout << "2. Display Stack" << endl;
            cout << "3. Display Priority Queue" << endl;
            cout << "4. Delete from Queue" << endl;
            cout << "5. Delete from Stack" << endl;
            cout << "6. Delete from Priority Queue" << endl;
            cout << "7. Save Queue to File" << endl;
            cout << "8. Save Stack to File" << endl;
            cout << "9. Save Priority Queue to File" << endl;
            cout << "0. Return to main menu" << endl;
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    displayContainer(appQueue);
                    break;
                case 2:
                    displayContainer(appStack);
                    break;
                case 3:
                    displayContainer(appPriorityQueue);
                    break;
                case 4:
                    deleteFromQueue();
                    break;
                case 5:
                    deleteFromStack();
                    break;
                case 6:
                    deleteFromPriorityQueue();
                    break;
                case 7:
                    saveToFile(appQueue, "queue.txt");
                    break;
                case 8:
                    saveToFile(appStack, "stack.txt");
                    break;
                case 9:
                    saveToFile(appPriorityQueue, "priority_queue.txt");
                    break;
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
            cout << "1. Add application to Queue" << endl;
            cout << "2. Add application to Stack" << endl;
            cout << "3. Add application to Priority Queue" << endl;
            cout << "4. Container Management Menu" << endl;
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

                    addAppToQueue(MobileApp(name, version, releaseDate, status, developer, platform));
                    break;
                }
                case 2: {
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

                    addAppToStack(MobileApp(name, version, releaseDate, status, developer, platform));
                    break;
                }
                case 3: {
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

                    addAppToPriorityQueue(MobileApp(name, version, releaseDate, status, developer, platform));
                    break;
                }
                case 4:
                    containerMenu();
                    break;
                case 0:
                    return;
                default:
                    cout << "Invalid choice.\n";
            }
        }
    }
};

void lab5() {
    Laba5 laba;
    laba.menu();
}
