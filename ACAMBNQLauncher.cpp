// ACAMBNQLauncher.cpp
// mbnq.pl

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

int main() {
    system("title CA Starter ^(mbnq.pl^)");

    string gamePath;
    bool runUpdate = false;
    int runIT = 0;

    ifstream configFile("config.txt");
    if (configFile.is_open()) {
        string line;
        while (getline(configFile, line)) {
            size_t equalsPos = line.find('=');
            if (equalsPos != string::npos) {
                string key = line.substr(0, equalsPos);
                string value = line.substr(equalsPos + 1);

                if (key == "gamePath") {
                    gamePath = value;
                }
                else if (key == "runUpdate") {
                    runUpdate = (value == "TRUE" || value == "true");
                }
                else if (key == "runIT") {
                    runIT = stoi(value);
                }
            }
        }
        configFile.close();
    }
    else {
        cout << "Error: Cannot open or find config.txt file!" << endl;
        return 1;
    }

    int counter = 0;
    int pauseTime = 5;  // hardcoded

    if (!gamePath.empty()) {
        if (runIT >= 1 && runIT <= 16) {
            cout << "Config loaded!" << endl;
            cout << "You may need to start this as administrator." << endl;

            if (runUpdate) {
                cout << "Updating..." << endl;
                cout << "Wait 15s or press any key to stop updating..." << endl;
                system("start AlefLauncher.exe");
                Sleep(15000);
                system("taskkill /F /IM javaw.exe > nul");
            }

            while (counter < runIT) {
                counter++;
                cout << "Starting instance: " << counter << endl;

                string cmd = (counter == 1) ? "start AlefClient.exe" : "start /LOW /MIN /AFFINITY 4 AlefClient.exe";
                system(cmd.c_str());

                if (counter >= runIT) {
                    break;
                }

                Sleep(pauseTime * 1000);
            }
        }
        else {
            cout << "Cannot run " << runIT << " instances!" << endl;
            cout << "Make sure config is set up correctly!" << endl;
        }
    }
    else {
        cout << "Game files not found!" << endl;
        cout << "Make sure game path config is set up correctly!" << endl;
    }

    cout << "Press any key to quit..." << endl;
    cin.get();

    return 0;
}
