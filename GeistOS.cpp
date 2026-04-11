#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <unordered_map>
#include <windows.h>

#include <dxgi.h>

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

#include <algorithm>
#include <richedit.h>
#include <regex>
#include <map>

#include <stdio.h>

#include "lib.cpp"
#include "rotatingGhost.cpp"
#include "UIElements/Window.h"
#include "UIElements/Window.cpp"

#include <thread>
#include <chrono>
#include <cstdlib>
#include <regex>
#include <random>

#include <unknwn.h> // IUnknown
#include <dxgi.h>
#include <iomanip>

#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <string>
#include <chrono>
#include <thread>

#include <cstdio>
#include <memory>
#include <atomic>
#include <array>

#include <cstring>
#include <unistd.h>

#include "VariadicTable.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>   // für rmdir
    #include <limits.h>   // PATH_MAX
    #include <unistd.h>   // readlink
#endif

#include <filesystem>
#include <sstream>
#include <fstream>

#include <cstdio>
#include <memory>

#if defined(_WIN32)
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// ==========================
// User-Struktur
// ==========================
struct User {
    int userId;
    std::string preName;
    std::string lastName;
    std::string name;
    std::string password;
    std::string created;
    std::string rank;
    std::string userRights;
};

// ==========================
// Passwort-Eingabe unsichtbar
// ==========================
std::string getHiddenInput() {
    std::string input;

#if defined(_WIN32)
    char ch;
    while ((ch = _getch()) != '\r') { // Enter
        if (ch == '\b') { // Backspace
            if (!input.empty()) {
                input.pop_back();
                std::cout << "\b \b";
            }
        } else {
            input.push_back(ch);
            std::cout << '*'; // optional: Sternchen anzeigen
        }
    }
    std::cout << std::endl;
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::getline(std::cin, input);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    return input;
}

// ==========================
// Hilfsfunktion: String splitten
// ==========================
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    for (char c : s) {
        if (c == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token.push_back(c);
        }
    }
    if (!token.empty()) tokens.push_back(token);
    return tokens;
}

std::string currentDictonary = "/";

// ==========================
// Globale aktuelle Farbe (Standard: Weiß)
// ==========================
std::string currentColor = "\033[0;37m"; 
std::string secColor = "\033[1;32m";


void printScreenOld(std::string type) {
    //font: Kban

    if (type == "Welcome") {
        std::cout << "\n";
        std::cout << currentColor + "\033[1;34m  ..|'''.|           ||           .       ..|''||    .|'''.|   \033[0m \n";
        std::cout << currentColor + "\033[1;34m .|'     '    ....  ...   ....  .||.     .|'    ||   ||..  '   \033[0m \n";
        std::cout << currentColor + "\033[1;34m ||    .... .|...||  ||  ||. '   ||      ||      ||   ''|||.   \033[0m \n";
        std::cout << currentColor + "\033[1;34m '|.    ||  ||       ||  . '|..  ||      '|.     || .     '||  \033[0m \n";
        std::cout << currentColor + "\033[1;34m  ''|...'|   '|...' .||. |'..|'  '|.'     ''|...|'  |'....|'   \033[0m \n\n"; 
        std::cout << "\n";
    } else if (type == "Login") {
        std::cout << "\n";
        std::cout << currentColor + "\033[1;34m '||'                       ||            \033[0m\n";
        std::cout << currentColor + "\033[1;34m  ||         ...     ... . ...  .. ...    \033[0m\n";
        std::cout << currentColor + "\033[1;34m  ||       .|  '|.  || ||   ||   ||  ||   \033[0m\n";
        std::cout << currentColor + "\033[1;34m  ||       ||   ||   |''    ||   ||  ||   \033[0m\n";
        std::cout << currentColor + "\033[1;34m .||.....|  '|..|'  '||||. .||. .||. ||.  \033[0m\n";
        std::cout << currentColor + "\033[1;34m                   .|....'                \033[0m\n\n";
        std::cout << "\n";                         
    } else if (type == "Help") {
        std::cout << "\n";
        std::cout << currentColor + "\033[1;34m '||'  '||'         '||           \033[1;34m\n";
        std::cout << currentColor + "\033[1;34m  ||    ||    ....   ||  ... ...  \033[1;34m\n";
        std::cout << currentColor + "\033[1;34m  ||''''||  .|...||  ||   ||'  || \033[1;34m\n";
        std::cout << currentColor + "\033[1;34m  ||    ||  ||       ||   ||    | \033[1;34m\n";
        std::cout << currentColor + "\033[1;34m .||.  .||.  '|...' .||.  ||...'  \033[1;34m\n";
        std::cout << currentColor + "\033[1;34m                          ||      \033[1;34m\n";
        std::cout << currentColor + "\033[1;34m                          ''''    \033[1;34m\n";
        std::cout << "\n";
    }
}

void printScreen(const std::string& text) {
    if (text.empty()) return;

    std::string upper;
    for (char c : text)
        upper += std::toupper(static_cast<unsigned char>(c));

    std::cout << "\n";

    constexpr int FONT_HEIGHT = 5;

    for (int row = 0; row < FONT_HEIGHT; ++row) {
        for (char c : upper)
        {
            auto it = FONT.find(c);
            if (it != FONT.end())
                std::cout << currentColor << "\033[1;34m"
                          << it->second[row] << " \033[0m";
            else
                std::cout << "      "; // unbekanntes Zeichen → leer
        }

        std::cout << "\n";
    }

    std::cout << std::endl; // EINMAL newline → fertig
}


// Hilfsfunktion: Mapping von CMD-Farbcode zu ANSI
std::string getAnsiColor(char code) {
    switch (toupper(code)) {
        case '0': return "\033[0;30m"; // Schwarz
        case '1': return "\033[0;34m"; // Dunkelblau
        case '2': return "\033[0;32m"; // Dunkelgrün
        case '3': return "\033[0;36m"; // Dunkelcyan
        case '4': return "\033[0;31m"; // Dunkelrot
        case '5': return "\033[0;35m"; // Dunkellila
        case '6': return "\033[0;33m"; // Dunkelgelb
        case '7': return "\033[0;37m"; // Hellgrau
        case '8': return "\033[1;30m"; // Dunkelgrau
        case '9': return "\033[1;34m"; // Hellblau
        case 'A': return "\033[1;32m"; // Hellgrün
        case 'B': return "\033[1;36m"; // Hellcyan
        case 'C': return "\033[1;31m"; // Hellrot
        case 'D': return "\033[1;35m"; // Helllila
        case 'E': return "\033[1;33m"; // Hellgelb
        case 'F': return "\033[1;37m"; // Weiß
        default:  return "\033[0;37m"; // Fallback Weiß
    }
}

std::atomic<bool> animationRunning(false);
std::atomic<bool> stopAnimation(false);
std::atomic<std::chrono::steady_clock::time_point> lastInput;

// -------------------------------------------------
// GHOST ASCII FRAMES
// -------------------------------------------------
std::vector<std::string> frames = {
    R"(
       .-.
     .'   `.
     :      :
     |      |
     :      :
     `.    .'
       `--'
    )",
    R"(
       .-.
     .'o  `.
     :   o  :
     |  o   |
     :   o  :
     `.  o .'
       `--'
    )",
    R"(
       .-.
     .' *  `.
     :   *  :
     |  *   |
     :   *  :
     `.  * .'
       `--'
    )"
};

// -------------------------------------------------
// Helper: Clear screen using ANSI escape codes
// -------------------------------------------------
void clearScreen() {
    //std::cout << "\033[2J\033[H"; // clear screen + move cursor home
    system("cls");
}

bool anyKeyPressed()
{
    for (int key = 0x08; key <= 0xFE; ++key) {
        // LOW-ORDER BIT = Taste wurde gedrückt (nicht gehalten!)
        if (GetAsyncKeyState(key) & 0x0001)
        {
            return true;
        }
    }
    return false;
}



// -------------------------------------------------
// GHOST ANIMATION THREAD (läuft unabhängig)
// -------------------------------------------------
void animationThread()
{
    size_t idx = 0;
    (void)idx;
    stopAnimation = false;

    while (!stopAnimation) {
        animateGhost();
    }

    animationRunning = false;
}

// -------------------------------------------------
// IDLE MONITOR THREAD (überwacht Inaktivität)
// -------------------------------------------------
void idleMonitor()
{
    while (true) {
        auto now = std::chrono::steady_clock::now();
        long diff = std::chrono::duration_cast<std::chrono::seconds>(now - lastInput.load()).count();

        if (diff >= 30 && !animationRunning.load()) {
            animationRunning = true;
            std::thread(animationThread).detach();
            std::cout << currentColor + "\n\033[1;36mYou are now AFK! Press enter to resume\033[0m\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

std::string cmdLog = "";
int cmdLogId = 1;

// ==========================
// Terminal-Klasse 
// ==========================
class Terminal {
public:
    Terminal() {
        users["root"] = {0, "Root", "Root", "root", "root123", "2024", "Owner", "1111"};
        users["user"] = {1, "User", "User", "user", "user123", "2024", "Member", "1010"};
        users["Bot"] = {2, "Bot", "Bot", "Bot", "bot123", "2024", "Bot", "0010"};
        users["Amy"] = {3, "Admin", "Admin", "Admin", "admin123", "2024", "Admin", "1111"};
        users["Jonas"] = {4, "Jonas", "Broschinski", "Jonas", "12345", "2024", "Admin", "1111"};
    }

    void registerCommand(const std::string& name,
                         std::function<void(const std::vector<std::string>&)> func,
                         bool requiresRead = false,
                         bool requiresWrite = false,
                         bool requiresExecute = false,
                         bool requiresSudo = false) {
        commands[name] = {func, requiresRead, requiresWrite, requiresExecute, requiresSudo};
    }

    boolean handleRights(std::string userRights, int pos) {
        if (userRights[pos] == '1') {
            return true;
        } else {
            return false;
        }
    }

    bool loginPrompt(std::string error = "none") {
        SetConsoleTitleA("Geist OS");
        
        std::string username, password;

        system("cls");
        printScreen("Login");

        if (error != "none") {
            std::cout << currentColor + error;
        }

        std::cout << currentColor + "\033[0;36m======\033[0m GeistOS Login \033[0;36m======\033[0m\n";
        std::cout << currentColor + "Admin Username:       root\n";
        std::cout << currentColor + "Admin User Password:  root123\n\n";
        std::cout << currentColor + "\033[1;32m" << "Username\033[0m: ";
        std::getline(std::cin, username);

        if (users.find(username) == users.end()) {
            std::string wrongPwd = "\033[0;31mUsername incorrect.\033[0m\n";
            loginPrompt(wrongPwd);
            return false;
        }

        std::cout << currentColor + "\033[1;32m" << "Password\033[0m: ";
        password = getHiddenInput();

        if (users[username].password == password) {
            #if defined(_WIN32)
                        system("cls");
            #else
                        system("clear");
            #endif
            currentUser = &users[username];
            printScreen("Geist OS");
            std::cout << currentColor + "Welcome, \033[1;32m" << username << "\033[0m!\n\n";
            return true;
        } else {
            std::string wrongPwd = "\033[0;31mPassword incorrect.\033[0m\n";
            loginPrompt(wrongPwd);
            return false;
        }
    }

    void run() {
        std::string input;

        std::cout << currentColor + "Type '\033[1;34mhelp\033[0m' for some Commands.\n\n";

        lastInput = std::chrono::steady_clock::now();

        //this line enables the Screen Saver
        //std::thread(idleMonitor).detach();


        while (running) {
            if (anyKeyPressed())
            {
                lastInput = std::chrono::steady_clock::now();

                // Animation abbrechen
                if (animationRunning.load()) {
                    stopAnimation = true;
                    clearScreen();
                    std::string prompt = "\033[1;32m" + currentUser->name + "@GeistOS\033[0m:\033[0;34m" + currentDictonary + "\033[0m$";
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            
            if (currentColor != "\033[0;37m") {
                std::string prompt = secColor + currentUser->name + "@GeistOS:" + currentDictonary + "$";
                std::cout << currentColor + prompt;
            } else {
                std::string prompt = "\033[1;32m" + currentUser->name + "@GeistOS\033[0m:\033[0;34m" + currentDictonary + "\033[0m$";
                std::cout << currentColor + prompt;
            }
            if (!std::getline(std::cin, input)) break;

            auto tokens = split(input, ' ');
            if (tokens.empty()) continue;

            bool sudoMode = false;
            if (tokens[0] == "sudo") {
                sudoMode = true;
                if (tokens.size() < 2) {
                    std::cout << currentColor + "\033[1;36msudo\033[0m: no command specified\n";
                    continue;
                }
                tokens.erase(tokens.begin());
            }

            auto it = commands.find(tokens[0]);
            if (it != commands.end()) {
                auto &cmd = it->second;
 
                if (cmd.requiresRead && !handleRights(currentUser -> userRights, 0)) {
                    std::cout << currentColor + "Command \033[1;34m'" << tokens[0] << "'\033[0m requires \033[1;36mRead rights\033[0m\n";
                    continue;
                }
                if (cmd.requiresWrite && !handleRights(currentUser -> userRights, 1)) {
                    std::cout << currentColor + "Command \033[1;34m'" << tokens[0] << "'\033[0m requires \033[1;36mWrite rights\033[0m\n";
                    continue;
                }
                if (cmd.requiresWrite && !handleRights(currentUser -> userRights, 2)) {
                    std::cout << currentColor + "Command \033[1;34m'" << tokens[0] << "'\033[0m requires \033[1;36mExecute rights\033[0m\n";
                    continue;
                }
                if (cmd.requiresSudo && !sudoMode) {
                    std::cout << currentColor + "Command \033[1;34m'" << tokens[0] << "'\033[0m requires \033[1;36msudo\033[0m\n";
                    continue;
                }

                if (sudoMode || cmd.requiresSudo) {
                    if (!handleRights(currentUser -> userRights, 3)) {
                        std::cout << currentColor + "User \033[1;32m'" << currentUser->name << "'\033[0m is not in the sudoers file\n";
                        continue;
                    }
                    std::string pass;
                    std::cout << currentColor + "[\033[1;36msudo\033[0m] Password for \033[1;32m" << currentUser->name << "\033[0m: ";
                    pass = getHiddenInput();
                    if (pass == currentUser->password) {
                        cmdLog += "\033[1;33m" + std::to_string(cmdLogId) + "\033[1;0m. " + input + "\n";
                        cmdLogId++;
                        cmd.func(tokens);
                    } else {
                        std::cout << currentColor + "Sorry, try again.\n";
                    }
                } else {
                    cmdLog += "\033[1;33m" + std::to_string(cmdLogId) + "\033[1;0m. " + input + "\n";
                    cmdLogId++;
                    cmd.func(tokens);
                }

            } else {
                std::cout << currentColor + "Unknown Command: \033[1;34m" << tokens[0] << "\033[0m\n";
            }
        }
    }

    void getCmdLog() {
        std::cout << currentColor << cmdLog;
    }

    void clearCmdLog() {
        cmdLog = "";
        cmdLogId = 1;
    }

    void stop() { running = false; }

    User* getCurrentUser() { return currentUser; }
    std::unordered_map<std::string, User>& getUsers() { return users; }
    void switchUser(const std::string& name) {
        if (users.find(name) != users.end()) {
            currentUser = &users[name];
        }
    }

private:
    struct Command {
        std::function<void(const std::vector<std::string>&)> func;
        bool requiresRead;
        bool requiresWrite;
        bool requiresExecute;
        bool requiresSudo;
    };

    bool running = true;
    std::map<std::string, Command> commands;

    std::unordered_map<std::string, User> users;
    User* currentUser = nullptr;
};

// ==========================
// Befehle
// ==========================
void cmd_help(const std::vector<std::string>& args) {
    (void)args;
    printScreen("Help");
    std::cout << currentColor + "Available Commands:\n";
    std::cout << currentColor + "  \033[1;34mhelp\033[0m, \033[1;34mclear\033[0m, \033[1;34mecho\033[0m, \033[1;34mls\033[0m, \033[1;34mexit\033[0m\n";
    std::cout << currentColor + "  \033[1;34mping <ip>\033[0m\n";
    std::cout << currentColor + "  \033[1;34mdir /s\033[0m\n";
    std::cout << currentColor + "  \033[1;34mapt update/install <Package>\033[0m (\033[1;36msudo\033[0m required)\n";
    std::cout << currentColor + "  \033[1;34mcd <Folder Path or Folder Name>\033[0m\n";
    std::cout << currentColor + "  \033[1;34mmkdir <Folder Name>\033[0m\n";
    std::cout << currentColor + "  \033[1;34mrm <filename|foldername>\033[0m (\033[1;36msudo\033[0m required)\n";
    std::cout << currentColor + "  \033[1;34mtouch <File Name>\033[0m\n";
    std::cout << currentColor + "  \033[1;34mvim <File Name>\033[0m\n";
    std::cout << currentColor + "  \033[1;34mcolor <hex-code>\033[0m (0-F) {7 = default}\n";
    std::cout << currentColor + "  \033[1;34mpasswd\033[0m (\033[1;36msudo\033[0m required)\n";
    std::cout << currentColor + "  \033[1;34muser <list/add/edit/del/help>\033[0m (\033[1;36msudo\033[0m required)\n";
    std::cout << currentColor + "  \033[1;34mperm <list/edit/info/help>\033[0m (\033[1;36msudo\033[0m required)\n";
    std::cout << currentColor + "  \033[1;34mprint <word to print>\033[0m\n";
}

void cmd_clear(const std::vector<std::string>& args) {
    (void)args;
    #if defined(_WIN32)
        system("cls");
    #else
        system("clear");
    #endif
}

void cmd_echo(const std::vector<std::string>& args) {
    for (size_t i = 1; i < args.size(); i++) {
        std::cout << currentColor + args[i] << " ";
    }
    std::cout << currentColor + "\n";
}

void cmd_color(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << currentColor + "Usage: \033[1;34mcolor <hex-code>\033[0m (0-F)\n";
        return;
    }

    char code = args[1][0]; // nur 1. Zeichen
    currentColor = getAnsiColor(code);
    secColor = getAnsiColor(code);

    std::cout << currentColor + currentColor << "Color changed to code " << code << "\n";
}

void cmd_ping(const std::vector<std::string>& args) {
    std::string command;

    #ifdef _WIN32
        // Windows-Befehl
        command = "ping " + args[1];
    #else
        // Linux / Mac-Befehl
        command = "ping -c 4 " + args[0];
    #endif

    std::cout << currentColor + "Running Ping...\n\n";
    int result = system(command.c_str());

    if(result == 0) {
        std::cout << currentColor + "\nPing successful!\n";
    } else {
        std::cout << currentColor + "\nPing Error!\n";
    }
}

void cmd_dir(const std::vector<std::string>& args) {
    // Beispiel: dir mit mehreren Argumenten
    std::string path = ".";       // aktuelles Verzeichnis
    std::string attributes = "/a"; // Alle Dateien anzeigen (inkl. versteckte)
    std::string recursive = "/s";  // rekursiv
    std::string bare = "/b";       // nur Pfade ohne Header/Footer
    std::string order = "/o:n";    // sortieren nach Name
    std::string pause = "";        // optional /p für Pause, leer = keine Pause

    std::string command = "dir " + args[1];

    std::cout << currentColor + "Running Command: " << command << "\n\n";

    // popen startet den Befehl und liefert die Ausgabe
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
    if (!pipe) {
        std::cerr << currentColor + "Error while running Command!\n";
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        std::cout << currentColor + buffer; // Ausgabe zeilenweise
    }
}


void wait(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

std::string fakeIP(const std::string& pkg) {
    return "https://" + pkg + ".com/" 
           + std::to_string(rand() % 256) + "." 
           + std::to_string(rand() % 256) + "." 
           + std::to_string(rand() % 256) + "." 
           + std::to_string(rand() % 256);
}

// Zufallszahlen einsetzen anstelle von Zahlen & %d
std::string replaceWithRandom(const std::string& input, std::mt19937& gen) {
    std::string result = input;

    // 1. %d durch kleine Zufallszahlen ersetzen (1-20)
    std::uniform_int_distribution<> smallDist(1, 20);
    std::regex percentRegex("%d");
    result = std::regex_replace(result, percentRegex, std::to_string(smallDist(gen)));

    // 2. vorhandene Zahlen durch größere Zufallszahlen ersetzen (500-9999)
    std::uniform_int_distribution<> largeDist(500, 9999);
    std::regex numberRegex("\\d+");
    auto words_begin = std::sregex_iterator(result.begin(), result.end(), numberRegex);
    auto words_end = std::sregex_iterator();

    std::string finalResult;
    size_t lastPos = 0;
    for (auto it = words_begin; it != words_end; ++it) {
        finalResult += result.substr(lastPos, it->position() - lastPos);
        finalResult += std::to_string(largeDist(gen));
        lastPos = it->position() + it->length();
    }
    finalResult += result.substr(lastPos);

    return finalResult;
}

int randomNum(int min, int max) {
    // Zufallsgenerator initialisieren
    static std::random_device rd;   // Zufallssamen
    static std::mt19937 gen(rd());  // Mersenne-Twister-Generator

    // Gleichverteilte Ganzzahl im Bereich [min, max]
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}


void cmd_apt_install(const std::vector<std::string>& args) {
    if (args.size() < 2 || args.size() > 4) {
        std::cout << currentColor + "Usage: sudo apt install <package>" << std::endl;
    }

    std::string pkg = args[2];
    srand(time(0));

    if (args[1] == "install") {
        std::cout << currentColor + "Reading package lists... Done" << std::endl;
        wait(700);
        std::cout << currentColor + "Building dependency tree" << std::endl;
        wait(700);
        std::cout << currentColor + "Reading state information... Done" << std::endl;
        wait(700);
        std::cout << currentColor + "The following NEW packages will be installed:" << std::endl;
        std::cout << currentColor + "  " << pkg << std::endl;
        wait(700);
        std::cout << currentColor + "0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded." << std::endl;
        std::cout << currentColor + "Need to get " + std::to_string(rand() % 20) + " MB of archives." << std::endl;
        std::cout << currentColor + "After this operation, " + std::to_string(rand() % 20) + " MB of additional disk space will be used." << std::endl;
        wait(1000);

        std::cout << currentColor + "Get:1 " << fakeIP(pkg) << " " << pkg << " [" + std::to_string(rand() % 20) + " MB]" << std::endl;
        wait(1500);

        std::cout << currentColor + "Pulling packages (" << fakeIP(pkg) << ")" << std::endl;
        wait(1000);

        // Fortschrittsbalken
        for (int i = 0; i <= 100; i+=10) {
            std::cout << currentColor + "\rProgress: " << i << "%";
            std::cout.flush();
            wait(randomNum(500, 3000));
        }
        std::cout << std::endl;

        int fetch = rand() % 15000;
        int download = rand() % 15000;
        int sec = fetch / download;

        std::cout << currentColor + "Fetched " + std::to_string(fetch) + " kB in " + std::to_string(sec) + "s (" + std::to_string(download) + " kB/s)" << std::endl;
        wait(500);
        std::cout << currentColor + "Selecting previously unselected package " << pkg << "." << std::endl;
        wait(500);

        for (int i = 0; i <= 100; i+=5) {
            std::cout << currentColor + "\r(Reading database ... " << i << "% complete)";
            std::cout.flush();
            wait(randomNum(250, 3000));
        }
        std::cout << std::endl;

        wait(500);
        std::cout << currentColor + "Preparing to unpack ..." << std::endl;
        wait(500);
        std::cout << currentColor + "Unpacking " << pkg << " (" + std::to_string(rand() % 5) + "." + std::to_string(rand() % 6) + "-" + std::to_string(rand() % 9) + ") ..." << std::endl;
        wait(1000);
        std::cout << currentColor + "Setting up " << pkg << " (" + std::to_string(rand() % 5) + "." + std::to_string(rand() % 6) + "-" + std::to_string(rand() % 9) + ") ..." << std::endl;
        wait(800);
        std::cout << currentColor + "Processing triggers for man-db (" + std::to_string(rand() % 5) + "." + std::to_string(rand() % 6) + "-" + std::to_string(rand() % 9) + ") ..." << std::endl;

        std::cout << currentColor + "\nInstallation finished." << std::endl;
    } else if (args[1] == "update") {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> sleepDist(1000, 6000); // Pause zwischen 1s und 6s

        std::vector<std::string> fakeMessages = {
            "Get:1 http://archive.ubuntu.com/ubuntu focal InRelease [265 kB]",
            "Get:2 http://archive.ubuntu.com/ubuntu focal-updates InRelease [123 kB]",
            "Get:3 http://archive.ubuntu.com/ubuntu focal-backports InRelease [48 kB]",
            "Get:4 http://security.ubuntu.com/ubuntu focal-security InRelease [110 kB]",
            "Get:5 http://security.ubuntu.com/ubuntu focal-workspace InRelease [170 kB]",
            "Get:6 http://security.ubuntu.com/ubuntu focal-frontend InRelease [210 kB]",
            "Get:7 http://security.ubuntu.com/ubuntu focal-backend InRelease [180 kB]",
            "Get:8 http://security.ubuntu.com/ubuntu focal-database InRelease [180 kB]",
            "Get:9 http://security.ubuntu.com/ubuntu focal-image InRelease [180 kB]",
            "Get:10 http://security.ubuntu.com/ubuntu focal-version InRelease [180 kB]",
            "Get:11 http://security.ubuntu.com/ubuntu focal-programm InRelease [180 kB]",
            "Get:12 http://security.ubuntu.com/ubuntu focal-snapshot InRelease [180 kB]",
            "Your System got %d kB in %d s (%d kB/s).",
            "Packages are being read... Finished"
        };

        for (auto& msg : fakeMessages) {
            std::string modified = replaceWithRandom(msg, gen);
            std::cout << currentColor + modified << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepDist(gen)));
        }
    } else {
        std::cout << currentColor + "Usage: sudo apt update/install <package>" << std::endl;
    }
}

void cmd_cd(const std::vector<std::string>& args) {
    if (args[1] != "/") {
        currentDictonary = args[1] + "/";
    } else {
        currentDictonary = args[1];
    }
}

std::string getExecutablePath() {
    #ifdef _WIN32
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        return std::string(buffer);
    #else
        char buffer[PATH_MAX];
        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (len != -1) {
            buffer[len] = '\0';
            return std::string(buffer);
        }
        return "";
    #endif
}

std::string getExecutableDir(const std::string &exePath) {
    #ifdef _WIN32
        size_t pos = exePath.find_last_of("\\/");
    #else
        size_t pos = exePath.find_last_of('/');
    #endif
        if (pos == std::string::npos) {
            return "."; // falls kein Trennzeichen gefunden wurde
        }
        return exePath.substr(0, pos);
}


void cmd_mkdir(const std::vector<std::string>& args) {
    // Pfad der .exe und Verzeichnis bestimmen
    std::string exePath = getExecutablePath();
    std::string exeDir  = getExecutableDir(exePath);

    // Zielordner zusammensetzen
    #ifdef _WIN32
        std::string ordnerName = exeDir + "\\" + currentDictonary + args[1];
    #else
        std::string ordnerName = exeDir + "/" + args[1];
    #endif

    #ifdef _WIN32
        if (CreateDirectoryA(ordnerName.c_str(), NULL) ||
            GetLastError() == ERROR_ALREADY_EXISTS) {
            std::cout << currentColor + "Created Folder or replaced existing one: " << ordnerName << std::endl;
        } else {
            std::cerr << currentColor + "Can't create the Folder!" << std::endl;
        }
    #else
        if (mkdir(ordnerName.c_str(), 0777) == 0) {
            std::cout << currentColor + "Created Folder: " << ordnerName << std::endl;
        } else if (errno == EEXIST) {
            std::cout << currentColor + "Folder already exists: " << ordnerName << std::endl;
        } else {
            perror("Can't create the Folder");
        }
    #endif
}

// Ordnerinhalt auflisten
void listDirectory(const std::string &path) {
    #ifdef _WIN32
        WIN32_FIND_DATAA findFileData;
        HANDLE hFind = FindFirstFileA((path + "\\*").c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE) {
            std::cerr << currentColor + "Error while opening Folder: " << path << std::endl;
            return;
        }

        do {
            std::string name = findFileData.cFileName;
            if (name != "." && name != "..") {
                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    std::cout << currentColor + "[Folder] " << name << std::endl;
                } else {
                    std::cout << currentColor + "[File]  " << name << std::endl;
                }
            }
        } while (FindNextFileA(hFind, &findFileData) != 0);

        FindClose(hFind);

    #else
        DIR *dir = opendir(path.c_str());
        if (!dir) {
            std::cerr << currentColor + "Error while opening Folder: " << path << std::endl;
            return;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string name = entry->d_name;
            if (name != "." && name != "..") {
                if (entry->d_type == DT_DIR) {
                    std::cout << currentColor + "[Folder] " << name << std::endl;
                } else {
                    std::cout << currentColor + "[File]  " << name << std::endl;
                }
            }
        }
        closedir(dir);
    #endif
}

void cmd_ls(const std::vector<std::string>& args) {
    (void)args;
    // aktuellen Arbeitsordner herausfinden (wo .exe liegt)
    char buffer[1024];

    GetModuleFileName(NULL, buffer, sizeof(buffer));
    std::string exePfad(buffer);
    exePfad = exePfad.substr(0, exePfad.find_last_of("\\/")); // nur Verzeichnis

    std::string ordnerPfad = exePfad + "\\" + currentDictonary;

    std::cout << currentColor + "Content of the Folder: " << ordnerPfad << std::endl;
    listDirectory(ordnerPfad);
}

void cmd_rm(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "Usage: rm <filename|foldername>" << std::endl;
        return;
    }

    std::string targetName = args[1];
    char buffer[1024];

    #ifdef _WIN32
        // Pfad der exe herausfinden
        GetModuleFileNameA(NULL, buffer, sizeof(buffer));
        std::string exePfad(buffer);
        exePfad = exePfad.substr(0, exePfad.find_last_of("\\/"));

        std::string targetPath = exePfad + "\\" + currentDictonary + targetName;

        DWORD attr = GetFileAttributesA(targetPath.c_str());
        if (attr == INVALID_FILE_ATTRIBUTES) {
            std::cerr << currentColor + "Error: File or directory not found!" << std::endl;
            return;
        }

        if (attr & FILE_ATTRIBUTE_DIRECTORY) {
            // Ordner löschen
            if (RemoveDirectoryA(targetPath.c_str())) {
                std::cout << currentColor + "Deleted Folder: " << targetName << std::endl;
            } else {
                std::cerr << currentColor + "Error while deleting folder (is it empty?)" << std::endl;
            }
        } else {
            // Datei löschen
            if (DeleteFileA(targetPath.c_str())) {
                std::cout << currentColor + "Deleted File: " << targetName << std::endl;
            } else {
                std::cerr << currentColor + "Error while deleting file!" << std::endl;
            }
        }

    #else
        // Pfad der exe herausfinden
        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer)-1);
        if (len == -1) {
            perror("Can't find the path");
            return;
        }
        buffer[len] = '\0';
        std::string exePfad(buffer);
        exePfad = exePfad.substr(0, exePfad.find_last_of("\\/"));

        std::string targetPath = exePfad + "/" + targetName;

        struct stat pathStat;
        if (stat(targetPath.c_str(), &pathStat) != 0) {
            perror("Error: File or directory not found");
            return;
        }

        if (S_ISDIR(pathStat.st_mode)) {
            // Ordner löschen
            if (rmdir(targetPath.c_str()) == 0) {
                std::cout << currentColor + "Deleted Folder: " << targetPath << std::endl;
            } else {
                perror("Error while deleting folder (is it empty?)");
            }
        } else if (S_ISREG(pathStat.st_mode)) {
            // Datei löschen
            if (unlink(targetPath.c_str()) == 0) {
                std::cout << currentColor + "Deleted File: " << targetPath << std::endl;
            } else {
                perror("Error while deleting file");
            }
        } else {
            std::cerr << currentColor + "Error: Not a regular file or directory!" << std::endl;
        }
    #endif
}

void cmd_touch(const std::vector<std::string>& args) {
    (void)args;
    std::string filename = args[1];

    // aktuellen Arbeitsordner herausfinden (wo .exe liegt)
    char buffer[1024];

    GetModuleFileName(NULL, buffer, sizeof(buffer));
    std::string exePath(buffer);
    exePath = exePath.substr(0, exePath.find_last_of("\\/")); // nur Verzeichnis

    std::string ordnerPfad = exePath + "\\" + currentDictonary;

    // Endgültiger Pfad zur neuen Datei
    std::string filePath = ordnerPfad + filename;

    // Datei erstellen
    std::ofstream newFile(filePath);
    if (newFile.is_open()) {
        std::cout << currentColor + "Created File sucessfully: " << filePath << std::endl;
        newFile.close();
    } else {
        std::cerr << currentColor + "Error: Can't create File!" << std::endl;
    }
}

void cmd_vim(const std::vector<std::string>& args) {
    std::string filename = args[1];
    char buffer[MAX_PATH];

    // Pfad zur exe
    GetModuleFileNameA(NULL, buffer, sizeof(buffer));
    std::string exePath(buffer);
    exePath = exePath.substr(0, exePath.find_last_of("\\/"));

    std::string filePath = exePath + "\\" + currentDictonary + filename;

    std::vector<std::string> lines;

    auto loadFile = [&]() {
        lines.clear();
        std::ifstream in(filePath);
        if (in.is_open()) {
            std::string line;
            while (std::getline(in, line)) {
                lines.push_back(line);
            }
            in.close();
        }
    };

    auto saveFile = [&]() {
        std::ofstream out(filePath, std::ios::trunc);
        for (auto& l : lines) out << l << "\n";
        out.close();
    };

    loadFile(); // Datei initial laden

    std::string command;
    while (true) {
        // Bildschirm „clearen“
        system("cls"); 
        std::cout << currentColor + "===== Editor: " << filename << " =====\n";
        for (size_t i = 0; i < lines.size(); ++i) {
            std::cout << i + 1 << ": " << lines[i] << "\n";
        }
        std::cout << currentColor + "\nCommands: :q (Quit), :w (Save), :e <Number> (Edit), :a (Add Line), :d <Number> (Delete Line)\n";
        std::cout << currentColor + "Command: ";
        std::getline(std::cin, command);

        if (command == ":q") break;
        else if (command == ":w") saveFile();
        else if (command.rfind(":e ", 0) == 0) {
            int lineNum = std::stoi(command.substr(3)) - 1;
            if (lineNum >= 0 && lineNum < (int)lines.size()) {
                std::cout << currentColor + "New Line " << lineNum + 1 << ": ";
                std::string newLine;
                std::getline(std::cin, newLine);
                lines[lineNum] = newLine;
            }
        }
        else if (command == ":a") {
            std::cout << currentColor + "Add new Line: ";
            std::string newLine;
            std::getline(std::cin, newLine);
            lines.push_back(newLine);
        }
        else if (command.rfind(":d ", 0) == 0) {
            int lineNum = std::stoi(command.substr(3)) - 1;
            if (lineNum >= 0 && lineNum < (int)lines.size()) {
                lines.erase(lines.begin() + lineNum);
            }
        }
        else {
            std::cout << currentColor + "Unknown Command!\n";
            system("pause");
        }
    }

    saveFile();
    std::cout << currentColor + "Saved File: " << filePath << std::endl;
}


// sudo required: Passwort ändern
void cmd_passwd(const std::vector<std::string>& args, Terminal& term) {
    (void)args;
    User* user = term.getCurrentUser();
    std::string oldPass;
    std::cout << currentColor + "Current \033[0;33mPassword\033[0m: ";
    oldPass = getHiddenInput();

    if (oldPass != user->password) {
        std::cout << currentColor + "Authentication failed.\n";
        return;
    }

    std::string newPass1, newPass2;
    std::cout << currentColor + "Enter new \033[0;33mPassword\033[0m: ";
    newPass1 = getHiddenInput();
    std::cout << currentColor + "Retype new \033[0;33mPassword\033[0m: ";
    newPass2 = getHiddenInput();

    if (newPass1 != newPass2) {
        std::cout << currentColor + "\033[0;33mPasswords\033[0m do not match.\n";
        return;
    }

    user->password = newPass1;
    std::cout << currentColor + "\033[0;33mPassword\033[0m updated successfully.\n";
}

// Funktion zum Ändern eines einzelnen Feldes
bool updateUserData(std::unordered_map<std::string, User>& users,
                     const std::string& username,
                     const std::string& field,
                     const std::string& newValue)
{
    auto it = users.find(username);
    if (it == users.end()) {
        return false; // Benutzer nicht gefunden
    }

    User& user = it->second;

    if (field == "userid") user.userId = stoi(newValue);
    else if (field == "preName") user.preName = newValue;
    else if (field == "lastName") user.lastName = newValue;
    else if (field == "name") user.name = newValue;
    else if (field == "password") user.password = newValue;
    else if (field == "created") user.created = newValue;
    else if (field == "rank") user.rank = newValue;
    else if (field == "userRights") user.userRights = newValue;
    else return false; // Feld existiert nicht

    return true;
}

void cmd_perm(const std::vector<std::string>& args, Terminal& term, std::string error = "none") {
    if (error != "none") {
        User* currentUser = term.getCurrentUser();
        std::string prompt = "\033[1;32m" + currentUser->name + "@GeistOS\033[0m:\033[0;34m" + currentDictonary + "\033[0m$";
        std::cout << currentColor + prompt << "sudo perm (list/edit/info/help)\n";
        std::cout << currentColor + error << "\n";
    }

    if (args[1] == "list") {
        auto& users = term.getUsers();
        std::cout << currentColor + "All Users Permissions:\n";

        VariadicTable<int, std::string, std::string, std::string> userTable({"UserId", "Username", "Rights", "Permissions"});

        // 1) Kopiere Paare in einen Vektor (Erhält die aktuelle Iterations-Reihenfolge)
        std::vector<std::pair<const std::string, User>> vec;
        vec.reserve(users.size());
        for (const auto& p : users) {
            vec.push_back(p);
        }

        // 2) Iteriere den Vektor rückwärts
        for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
            const User& u = it->second;
            std::string userPermissions = "";

            std::string allRights = "rwxs";
            for (int i = 0; i < 4; i++) {
                if (u.userRights[i] == '1') {
                    userPermissions += allRights[i];
                } else {
                    userPermissions += '-';
                }
            }

            userTable.addRow({u.userId, u.name, u.userRights, userPermissions});
        }

        userTable.print(std::cout << currentColor);



    } else if (args[1] == "edit") {
        std::cout << currentColor + "All Available Rights: \n\n";
        VariadicTable<std::string, std::string, std::string, std::string> permTable({"Octal", "Decimal", "Permission", "Representation"});

        permTable.addRow({"0000", "0  (0 + 0 + 0 + 0)", "No Permission", "----"});
        permTable.addRow({"0001", "1  (0 + 0 + 0 + 1)", "Sudo", "---s"});
        permTable.addRow({"0010", "2  (0 + 0 + 2 + 0)", "Execute", "--x-"});
        permTable.addRow({"0011", "3  (0 + 0 + 2 + 1)", "Execute + Sudo", "--xs"});

        permTable.addRow({"0100", "4  (0 + 4 + 0 + 0)", "Write", "-w--"});
        permTable.addRow({"0101", "5  (0 + 4 + 0 + 1)", "Write + Sudo", "-w-s"});
        permTable.addRow({"0110", "6  (0 + 4 + 2 + 0)", "Write + Execute", "-wx-"});
        permTable.addRow({"0111", "7  (0 + 4 + 2 + 1)", "Write + Execute + Sudo", "-wxs"});

        permTable.addRow({"1000", "8  (8 + 0 + 0 + 0)", "Read", "r---"});
        permTable.addRow({"1001", "9  (8 + 0 + 0 + 1)", "Read + Sudo", "r--s"});
        permTable.addRow({"1010", "10 (8 + 0 + 2 + 0)", "Read + Execute", "r-x-"});
        permTable.addRow({"1011", "11 (8 + 0 + 2 + 1)", "Read + Execute + Sudo", "r-xs"});

        permTable.addRow({"1100", "12 (8 + 4 + 0 + 0)", "Read + Write", "rw--"});
        permTable.addRow({"1101", "13 (8 + 4 + 0 + 1)", "Read + Write + Sudo", "rw-s"});
        permTable.addRow({"1110", "14 (8 + 4 + 2 + 0)", "Read + Write + Execute", "rwx-"});
        permTable.addRow({"1111", "15 (8 + 4 + 2 + 1)", "Read + Write + Execute + Sudo", "rwxs"});

        permTable.print(std::cout << currentColor);

        std::cout << currentColor + "\n\n";

        auto& users = term.getUsers();
        std::cout << currentColor + "All Users Permissions:\n";

        VariadicTable<int, std::string, std::string, std::string> userTable({"UserId", "Username", "Rights", "Permissions"});

        // 1) Kopiere Paare in einen Vektor (Erhält die aktuelle Iterations-Reihenfolge)
        std::vector<std::pair<const std::string, User>> vec;
        vec.reserve(users.size());
        for (const auto& p : users) {
            vec.push_back(p);
        }

        // 2) Iteriere den Vektor rückwärts
        for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
            const User& u = it->second;
            std::string userPermissions = "";

            std::string allRights = "rwxs";
            for (int i = 0; i < 4; i++) {
                if (u.userRights[i] == '1') {
                    userPermissions += allRights[i];
                } else {
                    userPermissions += '-';
                }
            }

            userTable.addRow({u.userId, u.name, u.userRights, userPermissions});
        }

        userTable.print(std::cout << currentColor);
        std::string userName;
        std::cout << currentColor + "\n" << "What \033[1;32mUsers\033[0m \033[0;33mPermission\033[0m do you want to change?: ";
        std::getline(std::cin, userName);

        if (users.find(userName) == users.end()) {
            std::cout << currentColor + "\033[1;32mUser\033[0m not found.\n";
            return;
        }

        std::string userRightsNew;
        std::cout << currentColor + "\n" << "What should be the \033[1;32mUsers\033[0m new \033[0;33mRights\033[0m?: ";
        std::getline(std::cin, userRightsNew);

        std::string userPermissions = "";
        std::string allRights = "rwxs";
        for (int i = 0; i < 4; i++) {
            if (userRightsNew[i] == '1') {
                userPermissions += allRights[i];
            } else {
                userPermissions += '-';
            }
        }

        // Feld ändern
        if (updateUserData(users, userName, "userRights", userRightsNew)) {
            std::cout << "Rights changed successfully!\n" << "New Rights of \033[1;32m" + userName + "\033[0m: \033[0;33m" + userRightsNew + "\033[0m\nSo the \033[1;32mUser\033[0m can: \033[0;33m" + userPermissions + "\033[0m\n";
        } else {
            std::cout << "Error while changing the \033[1;32mUsers\033[0m Rights.\n";
        }



    } else if (args[1] == "info") {
        VariadicTable<std::string, std::string, std::string, std::string> permTable({"Octal", "Decimal", "Permission", "Representation"});

        permTable.addRow({"0000", "0  (0 + 0 + 0 + 0)", "No Permission", "----"});
        permTable.addRow({"0001", "1  (0 + 0 + 0 + 1)", "Sudo", "---s"});
        permTable.addRow({"0010", "2  (0 + 0 + 2 + 0)", "Execute", "--x-"});
        permTable.addRow({"0011", "3  (0 + 0 + 2 + 1)", "Execute + Sudo", "--xs"});

        permTable.addRow({"0100", "4  (0 + 4 + 0 + 0)", "Write", "-w--"});
        permTable.addRow({"0101", "5  (0 + 4 + 0 + 1)", "Write + Sudo", "-w-s"});
        permTable.addRow({"0110", "6  (0 + 4 + 2 + 0)", "Write + Execute", "-wx-"});
        permTable.addRow({"0111", "7  (0 + 4 + 2 + 1)", "Write + Execute + Sudo", "-wxs"});

        permTable.addRow({"1000", "8  (8 + 0 + 0 + 0)", "Read", "r---"});
        permTable.addRow({"1001", "9  (8 + 0 + 0 + 1)", "Read + Sudo", "r--s"});
        permTable.addRow({"1010", "10 (8 + 0 + 2 + 0)", "Read + Execute", "r-x-"});
        permTable.addRow({"1011", "11 (8 + 0 + 2 + 1)", "Read + Execute + Sudo", "r-xs"});

        permTable.addRow({"1100", "12 (8 + 4 + 0 + 0)", "Read + Write", "rw--"});
        permTable.addRow({"1101", "13 (8 + 4 + 0 + 1)", "Read + Write + Sudo", "rw-s"});
        permTable.addRow({"1110", "14 (8 + 4 + 2 + 0)", "Read + Write + Execute", "rwx-"});
        permTable.addRow({"1111", "15 (8 + 4 + 2 + 1)", "Read + Write + Execute + Sudo", "rwxs"});

        permTable.print(std::cout << currentColor);



    } else if (args[1] == "help") {
        std::cout << currentColor + "The Permission command: \n";
        std::cout << currentColor + "   - \033[1;36msudo\033[0m \033[1;34mperm list\033[0m \033[0;33m(Show the Currents Permissions of the Users)\033[0m \n";
        std::cout << currentColor + "   - \033[1;36msudo\033[0m \033[1;34mperm edit\033[0m \033[0;33m()\033[0m \n";
        std::cout << currentColor + "   - \033[1;36msudo\033[0m \033[1;34mperm info\033[0m \033[0;33m(Show the Permission Table)\033[0m \n";
        std::cout << currentColor + "   - \033[1;36msudo\033[0m \033[1;34mperm help\033[0m \033[0;33m(Show this Help)\033[0m \n";
        


    } else {
        std::cout << currentColor + "Usage: \033[1;36msudo\033[0m \033[1;34mperm (list/edit/info/help)\033[0m\n";
    }
}

struct EditOption {
    std::string displayName;
    std::string dbName;
};

std::vector<EditOption> editOptions = {
    {"UserId", "userid"},
    {"UserName", "name"},
    {"PreName", "preName"},
    {"LastName", "lastName"},
    {"Password", "password"},
    {"Created", "created"},
    {"Rank", "rank"},
    {"Rights", "userRights"}
};

std::vector<EditOption> rankOptions = {
    {"Member", "1"},
    {"Admin", "2"},
    {"Owner", "3"},
    {"Bot", "4"},
    {"Tester", "5"}
};

// sudo required: User Befehler
void cmd_user(const std::vector<std::string>& args, Terminal& term, std::string error = "none") {
    if (args[1] == "list") {
        auto& users = term.getUsers();
        std::cout << currentColor + "All users:\n";

        VariadicTable<int, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string> userTable({"UserId", "Username", "Prename", "Lastname", "Password", "Created", "Rank", "Rights", "Permissions"});

        // 1) Kopiere Paare in einen Vektor (Erhält die aktuelle Iterations-Reihenfolge)
        std::vector<std::pair<const std::string, User>> vec;
        vec.reserve(users.size());
        for (const auto& p : users) {
            vec.push_back(p);
        }

        // 2) Iteriere den Vektor rückwärts
        std::string allRights = "rwxs";
        for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
            const User& u = it->second;
            std::string userPermissions = "";

            for (int i = 0; i < 4; i++) {
                if (u.userRights[i] == '1') {
                    userPermissions += allRights[i];
                } else {
                    userPermissions += '-';
                }
            }

            userTable.addRow({u.userId, u.name, u.preName, u.lastName, u.password, u.created, u.rank, u.userRights, userPermissions});
        }

        userTable.print(std::cout << currentColor);



    } else if (args[1] == "add") {
        if (error != "none") {
            User* currentUser = term.getCurrentUser();
            std::string prompt = "\033[1;32m" + currentUser->name + "@GeistOS\033[0m:\033[0;34m" + currentDictonary + "\033[0m$";
            std::cout << currentColor + prompt << "sudo user add\n";
            std::cout << currentColor + error << "\n";
        }

        std::string userName;
        std::cout << currentColor + "What is the \033[0;33mUsername\033[0m?: ";
        std::getline(std::cin, userName);

        auto& users = term.getUsers();
        if (users.find(userName) != users.end()) {
            std::cout << currentColor + userName << " already exists.\n";
            return;
        }

        std::string preName;
        std::cout << currentColor + "What is \033[1;32m" << userName << "s\033[0m \033[0;33mPrename\033[0m?: ";
        std::getline(std::cin, preName);

        std::string lastName;
        std::cout << currentColor + "What is \033[1;32m" << userName << "s\033[0m \033[0;33mLastname\033[0m?: ";
        std::getline(std::cin, lastName);

        std::string pass;
        std::cout << currentColor + "Enter \033[0;33mPassword\033[0m for \033[1;32m" << userName << "\033[0m: ";
        pass = getHiddenInput();

        std::string created;
        std::cout << currentColor + "When should \033[1;32m" << userName << "\033[0m be \033[0;33mCreated\033[0m?: ";
        std::getline(std::cin, created);

        std::string userRank;
        std::string userRankIndex;

        std::cout << currentColor + "Available \033[0;33mRanks\033[0m: \n";

        // Menü dynamisch generieren
        for (size_t i = 0; i < rankOptions.size(); ++i) {
            std::cout << currentColor << "   " << (i + 1)
                    << ". \033[1;36m" << rankOptions[i].displayName << "\033[0m\n";
        }

        std::cout << currentColor + "What should \033[1;32m" << userName << "s\033[0m \033[0;33mRank\033[0m be? (1 - " << std::to_string(rankOptions.size()) << "): ";
        std::getline(std::cin, userRankIndex);

        // Eingabe prüfen
        int choice = std::stoi(userRankIndex);
        if (choice < 1 || choice > std::stoi(std::to_string(rankOptions.size()))) {
            std::string errorMsg = "\033[0;31mPlease only enter the Numbers 1 - " + std::to_string(rankOptions.size()) + "!\033[0m";
            cmd_user(args, term, errorMsg);
            return;
        }
        userRank = rankOptions[choice - 1].displayName;

        std::string userRights;
        std::cout << currentColor + "What \033[0;33mRights\033[0m should \033[1;32m" << userName << "\033[0m have?: ";
        std::getline(std::cin, userRights);

        std::cout << currentColor + "\n" << "User \033[1;32m" << userName << "\033[0m added successfully!" << "\n";

        VariadicTable<int, std::string, std::string, std::string, std::string, std::string, std::string, std::string> userTable({"UserId", "Prename", "Lastname", "Username", "Password", "Created", "Rank", "Rights"});

        userTable.addRow({(int) users.size(), preName, lastName, userName, pass, created, userRank, userRights});
        //users[userName] = {(int) users.size(), preName, lastName, userName, pass, created, userRank, userRights};
        users.emplace(userName, User{
            static_cast<int>(users.size()),
            preName,
            lastName,
            userName,
            pass,
            created,
            userRank,
            userRights
        });
        userTable.print(std::cout << currentColor);



    } else if (args[1] == "edit") {
        if (error != "none") {
            User* currentUser = term.getCurrentUser();
            std::string prompt = "\033[1;32m" + currentUser->name + "@GeistOS\033[0m:\033[0;34m" + currentDictonary + "\033[0m$";
            std::cout << currentColor + prompt << "sudo user edit\n";
            std::cout << currentColor + error << "\n";
        }

        auto& users = term.getUsers();
        std::cout << currentColor + "All users:\n";

        VariadicTable<int, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string> userTable({"UserId", "Username", "Prename", "Lastname", "Password", "Created", "Rank", "Rights", "Permissions"});

        // 1) Kopiere Paare in einen Vektor (Erhält die aktuelle Iterations-Reihenfolge)
        std::vector<std::pair<const std::string, User>> vec;
        vec.reserve(users.size());
        for (const auto& p : users) {
            vec.push_back(p);
        }

        // 2) Iteriere den Vektor rückwärts
        std::string allRights = "rwxs";
        for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
            const User& u = it->second;
            std::string userPermissions = "";

            for (int i = 0; i < 4; i++) {
                if (u.userRights[i] == '1') {
                    userPermissions += allRights[i];
                } else {
                    userPermissions += '-';
                }
            }

            userTable.addRow({u.userId, u.name, u.preName, u.lastName, u.password, u.created, u.rank, u.userRights, userPermissions});
        }

        userTable.print(std::cout << currentColor);

        std::string userName;
        std::cout << currentColor + "What \033[1;32mUser\033[0m do you want to \033[0;33medit\033[0m? (Enter \033[1;32mUsername\033[0m): ";
        std::getline(std::cin, userName);

        if (users.find(userName) == users.end()) {
            std::string errorMsg = "\033[1;32mUser\033[0m not found.\n";
            cmd_user(args, term, errorMsg);
            return;
        }

        std::string editNum;
        std::string editTitle;

        std::cout << currentColor + "What Data do you want to \033[0;33medit\033[0m?: \n";

        // Menü dynamisch generieren
        for (size_t i = 0; i < editOptions.size(); ++i) {
            std::cout << currentColor << "   " << (i + 1)
                    << ". \033[1;36m" << editOptions[i].displayName << "\033[0m\n";
        }

        std::cout << currentColor << "Choose one Number (1 - " << editOptions.size() << "): ";
        std::getline(std::cin, editNum);

        // Eingabe prüfen
        int choice = std::stoi(editNum);
        editTitle = editOptions[choice - 1].displayName;
        editNum = editOptions[choice - 1].dbName;

        std::string userDataNew;
        std::cout << currentColor + "What should be the \033[0;33mNew\033[0m \033[1;32m" + editTitle + "\033[0m?: ";
        std::getline(std::cin, userDataNew);

        // Feld ändern
        if (updateUserData(users, userName, editNum, userDataNew)) {
            std::cout << editTitle + " changed successfully!\n" << "New " + editTitle + " of \033[1;32m" + userName + "\033[0m: \033[0;33m" + userDataNew + "\n";
        } else {
            std::cout << "Error while changing the \033[1;32mUsers\033[0m \033[1;32m" + editTitle + "\033[0m.\n";
        }



    } else if (args[1] == "del") {
        std::string userName;
        std::cout << currentColor + "What \033[1;32mUser\033[0m should be \033[0;31mdeleted\033[0m?: ";
        std::getline(std::cin, userName);

        auto& users = term.getUsers();
        if (users.find(userName) == users.end()) {
            std::cout << currentColor + "\033[1;32mUser\033[0m not found.\n";
            return;
        }

        users.erase(userName);
        std::cout << currentColor + "User \033[1;32m" << userName << "\033[0m \033[0;31mdeleted\033[0m.\n";



    } else if (args[1] == "help") {
        std::cout << currentColor + "The user command: \n";
        std::cout << currentColor + "   - \033[1;36msudo\033[0m \033[1;34muser list\033[0m \033[0;33m(Lists all \033[1;32mUsers\033[0;33m)\033[0m \n";
        std::cout << currentColor + "   - \033[1;36msudo\033[0m \033[1;34muser add\033[0m \033[0;33m(Add a new \033[1;32mUser\033[0;33m)\033[0m \n";
        std::cout << currentColor + "   - \033[1;36msudo\033[0m \033[1;34muser del\033[0m \033[0;33m(delete a certain \033[1;32mUser\033[0;33m)\033[0m \n";
        std::cout << currentColor + "   - \033[1;36msudo\033[0m \033[1;34muser edit\033[0m \033[0;33m(Change certain Data of a certain \033[1;32mUser\033[0;33m)\033[0m \n";
        std::cout << currentColor + "   - \033[1;36msudo\033[0m \033[1;34muser help\033[0m \033[0;33m(Show this Help)\033[0m \n";
        
    } else {
        std::cout << currentColor + "Usage: \033[1;36msudo\033[0m \033[1;34muser (list/add/edit/del/help)\033[0m\n";
    }
}

void cmd_print(const std::vector<std::string>& args, Terminal& term) {
    (void)term;
    printScreen(args[1]);
}

// ---------------- TIMER CALLBACK ----------------
void UpdateGraph(Graph* g) {
    static float t = 0;
    t += 0.1f;
    g->AddValue(50 + 50 * sin(t));
}

void cmd_win(const std::vector<std::string>& args, Terminal& term) {
    (void)args; (void)term;

    Window win("Main Window", 900, 600, "MainWin");
    WindowConfig cfg;

    // -------- TOP PANEL --------
    PanelConfig top;
    top.dock = Dock::Top; 
    top.size = 50; 
    top.orientation = Orientation::Horizontal;
    top.items.push_back(new ButtonConfig("System", [&win]{ win.ShowLeftPanel("left_system"); }));
    top.items.push_back(new ButtonConfig("Apps", [&win]{ win.ShowLeftPanel("left_apps"); }));

    // -------- LEFT PANEL SYSTEM --------
    PanelConfig leftSys;
    leftSys.dock = Dock::Left; 
    leftSys.size = 200; 
    leftSys.id = "left_system"; 
    leftSys.orientation = Orientation::Vertical;
    leftSys.defaultMainPanelId = "main_sys_gen";
    leftSys.items.push_back(new ButtonConfig("General", [&win]{ win.ShowMainPanel("main_sys_gen"); }));
    leftSys.items.push_back(new ButtonConfig("Test", [&win]{ win.ShowMainPanel("main_sys_table"); }));

    // -------- LEFT PANEL APPS --------
    PanelConfig leftApps;
    leftApps.dock = Dock::Left; 
    leftApps.size = 200; 
    leftApps.id = "left_apps"; 
    leftApps.orientation = Orientation::Vertical;
    leftApps.defaultMainPanelId = "main_apps";
    leftApps.items.push_back(new ButtonConfig("Installed", [&win]{ win.ShowMainPanel("main_apps"); }));
    leftApps.items.push_back(new ButtonConfig("Available", [&win]{ win.ShowMainPanel("available_apps"); }));

    // -------- MAIN PANELS --------
    PanelConfig GenPan; 
    GenPan.id = "main_sys_gen"; 
    GenPan.orientation = Orientation::Vertical;
    GenPan.items.push_back(new TextConfig("System > General"));

    GenPan.items.push_back(new TextConfig("Graph Example"));
    GenPan.items.push_back(new GraphConfig(300,150, {"A","B","C","D","E"})); // Balken-Titel

    PanelConfig GenTable; 
    GenTable.id = "main_sys_table";
    GenTable.orientation = Orientation::Vertical;
    GenTable.items.push_back(new TextConfig("System > Table"));

    GenTable.items.push_back(new TextConfig("Table Example"));
    GenTable.items.push_back(new TableConfig({ "Octal","Decimal","Permission", "Representation" }));

    for (auto e : win.m_elements) {
        if (auto t = dynamic_cast<Table*>(e)) {
            std::vector<std::vector<std::string>> rows = {
                {"0000", "0 (0 + 0 + 0 + 0)", "No Permission", "----"},
                {"0001", "1 (0 + 0 + 0 + 1)", "Sudo", "---s"},
                {"0010", "2 (0 + 0 + 2 + 0)", "Execute", "--x-"},
                {"0011", "3 (0 + 0 + 2 + 1)", "Execute + Sudo", "--xs"},
                {"0100", "4 (0 + 4 + 0 + 0)", "Write", "-w--"},
                {"0101", "5 (0 + 4 + 0 + 1)", "Write + Sudo", "-w-s"},
                {"0110", "6 (0 + 4 + 2 + 0)", "Write + Execute", "-wx-"},
                {"0111", "7 (0 + 4 + 2 + 1)", "Write + Execute + Sudo", "-wxs"},
                {"1000", "8 (8 + 0 + 0 + 0)", "Read", "r---"},
                {"1001", "9 (8 + 0 + 0 + 1)", "Read + Sudo", "r--s"},
                {"1010", "10 (8 + 0 + 2 + 0)", "Read + Execute", "r-x-"},
                {"1011", "11 (8 + 0 + 2 + 1)", "Read + Execute + Sudo", "r-xs"},
                {"1100", "12 (8 + 4 + 0 + 0)", "Read + Write", "rw--"},
                {"1101", "13 (8 + 4 + 0 + 1)", "Read + Write + Sudo", "rw-s"},
                {"1110", "14 (8 + 4 + 2 + 0)", "Read + Write + Execute", "rwx-"},
                {"1111", "15 (8 + 4 + 2 + 1)", "Read + Write + Execute + Sudo", "rwxs"}
            };

            for (const auto& row : rows) {
                LVITEM item{};
                item.mask = LVIF_TEXT;
                item.iItem = ListView_GetItemCount(t->hListView);
                item.iSubItem = 0;
                item.pszText = (LPSTR)row[0].c_str(); // ANSI
                ListView_InsertItem(t->hListView, &item);

                for (size_t col = 1; col < row.size(); col++) {
                    LVITEM subitem{};
                    subitem.mask = LVIF_TEXT;
                    subitem.iItem = item.iItem;
                    subitem.iSubItem = (int)col;
                    subitem.pszText = (LPSTR)row[col].c_str(); // ANSI
                    ListView_SetItem(t->hListView, &subitem);
                }
            }
        }
    }

    PanelConfig m3; 
    m3.id = "main_apps";
    m3.items.push_back(new TextConfig("Apps > Installed"));
    
    PanelConfig m4; 
    m4.id = "available_apps"; 
    m4.items.push_back(new TextConfig("Apps > Available"));

    cfg.panels = { top, leftSys, leftApps, GenPan, GenTable, m3, m4 };
    win.LoadFromConfig(cfg);

    win.ShowLeftPanel("left_system");
    win.ShowMainPanel("main_sys_gen");

    // Finde Graph-Element
    Graph* graph = nullptr;
    for (auto e : win.m_elements) if (auto g = dynamic_cast<Graph*>(e)) { graph = g; break; }

    // Hauptloop
    while (win.ProcessMessages()) {
        if (graph) UpdateGraph(graph);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (auto& p : cfg.panels)
        for (auto item : p.items) delete item;
}


void addVersion(std::string version) {
    std::cout << currentColor + "   \033[0;37mGeistOS v\033[1;0m\033[0;35m" + version + "\033[0;0m:\n";
}

void addUpdate(std::string prefix, std::string color, std::string change) {
    std::cout << currentColor + "       \033[1;30m" + prefix + "\033[1;0m " + color + change + "\033[0m\n";
}


void cmd_sys(const std::vector<std::string>& args, Terminal& term) {

    if (args.size() < 2) {
        std::cout << currentColor + "Usage: \033[1;34msys [(version <history/cur>)]\033[0m\n";
    } else if (args[1] == "version") {
        if (args[2] == "history") {
            printScreen("Versions");

            //addVersion("Version");
            //addUpdate("Prefix", "Color", "Change");
            
            std::cout << currentColor + "All \033[0;35mVersions\033[0;0m:\n";
            addVersion("0.0.0.1");
            addUpdate("Added", "\033[1;30m", "Dynamic C++ Code for an Linux like OS");
            addUpdate("Added", "\033[1;34m", "help\033[0m, \033[1;34mclear\033[0m, \033[1;34mecho\033[0m, \033[1;34mls\033[0m, \033[1;34mexit");
            addUpdate("Added", "\033[1;34m", "ping <ip>");

            addVersion("0.0.0.2");
            addUpdate("Added", "\033[1;34m", "dir /s");
            addUpdate("Added", "\033[1;34m", "apt update/install <Package>\033[0m (\033[1;36msudo\033[0m required)");
            addUpdate("Added", "\033[1;34m", "cd <Folder Path or Folder Name>");
            addUpdate("Added", "\033[1;34m", "mkdir <Folder Name>");
            addUpdate("Added", "\033[1;34m", "rm <filename|foldername>\033[0m (\033[1;36msudo\033[0m required)");
            addUpdate("Added", "\033[1;34m", "touch <File Name>");
            addUpdate("Added", "\033[1;34m", "vim <File Name>");
            
            addVersion("0.0.0.3");
            addUpdate("Added", "\033[1;34m", "color <hex-code>\033[0m (0-F) {7 = default}");
            addUpdate("Added", "\033[1;34m", "addUser <Username>");
            addUpdate("Added", "\033[1;34m", "listUser <Username>");
            addUpdate("Added", "\033[1;34m", "delUser <Username");
            addUpdate("Added", "\033[1;34m", "passwd\033[0m (\033[1;36msudo\033[0m required)");
            
            addVersion("0.0.0.4");
            addUpdate("Updated", "\033[1;34m", "user <list/add/edit/del/help>\033[0m (\033[1;36msudo\033[0m required)");
            addUpdate("Reworked", "\033[1;34m", "perm <list/edit/info/help>\033[0m (\033[1;36msudo\033[0m required)");
            addUpdate("Added", "\033[1;30m", "Spinning Ghost Idle Animation");
            addUpdate("Added", "\033[1;30m", "Early Versions of GeistOS GUI");
            addUpdate("Added", "\033[1;34m", "win");
            addUpdate("Added", "\033[1;30m", "Letter Library for print Cmd");
            addUpdate("Added", "\033[1;34m", "print <word to print>");
            
            addVersion("0.0.0.5");
            addUpdate("Reworked", "\033[1;30m", "Spinning Ghost Idle Animation");
            addUpdate("Disabled", "\033[1;30m", "Spinning 3D Ghost Idle Animation");
            addUpdate("Added", "\033[1;34m", "sys version <history/cur>");
            addUpdate("Added", "\033[1;34m", "sys log <show/clear>");

            addVersion("0.0.0.6");
        } else if (args[2] == "cur") {
            std::string curVersion = "0.0.0.6";
            std::cout << currentColor + "\033[1;30mCurrent Version\033[1;0m: \033[0;37mGeistOS v\033[1;0m\033[0;35m" + curVersion + "\033[0;0m:\n";
        } else {
            std::cout << currentColor + "Usage: \033[1;34msys version <history/cur>\033[0m\n";
        }
    } else if (args[1] == "log") {
        if (args[2] == "show") {
            printScreen("CMD History");
            term.getCmdLog();
        } else if (args[2] == "clear") {
            term.clearCmdLog();
        } else {
            std::cout << currentColor + "Usage: \033[1;34msys log <show/clear>\033[0m\n";
        }
    } else {
        std::cout << currentColor + "Usage: \033[1;34msys [(version <history/cur>)/(log <show/clear>)]\033[0m\n";
    }
}


























// ==========================
// main
// ==========================
int main() {
    Terminal terminal;

    // normale Befehle
    terminal.registerCommand("help", cmd_help);
    terminal.registerCommand("clear", cmd_clear);
    terminal.registerCommand("echo", cmd_echo);
    terminal.registerCommand("ls", cmd_ls);
    terminal.registerCommand("exit", [&](const std::vector<std::string>& args) {
        (void)args;
        std::cout << currentColor + "Stopping Terminal...\n";
        terminal.stop();
    });

    terminal.registerCommand("ping", [&](const std::vector<std::string>& args) {
        cmd_ping(args);
    }, false, false, true);

    terminal.registerCommand("dir", [&](const std::vector<std::string>& args) {
        cmd_dir(args);
    }, true);

    terminal.registerCommand("cd", [&](const std::vector<std::string>& args) {
        cmd_cd(args);
    }, true, false, false);

    terminal.registerCommand("mkdir", [&](const std::vector<std::string>& args) {
        cmd_mkdir(args);
    }, false, true);

    terminal.registerCommand("rm", [&](const std::vector<std::string>& args) {
        cmd_rm(args);
    }, true);

    terminal.registerCommand("touch", [&](const std::vector<std::string>& args) {
        cmd_touch(args);
    }, true, true);

    terminal.registerCommand("vim", [&](const std::vector<std::string>& args) {
        cmd_vim(args);
    }, true, true);

    terminal.registerCommand("apt", [&](const std::vector<std::string>& args) {
        cmd_apt_install(args);
    }, true, true, false, true);

    //color changer
    terminal.registerCommand("color", [&](const std::vector<std::string>& args) {
        cmd_color(args);
    });

    terminal.registerCommand("passwd", [&](const std::vector<std::string>& args) {
        cmd_passwd(args, terminal);
    }, true, true, true, true);

    // permission management commands (sudo required)
    terminal.registerCommand("perm", [&](const std::vector<std::string>& args) {
        cmd_perm(args, terminal);
    }, true, true, true, true);

    // user management commands (sudo required)
    terminal.registerCommand("user", [&](const std::vector<std::string>& args) {
        cmd_user(args, terminal);
    }, true, true, true, true);
    // Read Write Execute Sudo

    terminal.registerCommand("print", [&](const std::vector<std::string>& args) {
        cmd_print(args, terminal);
    }, true, true);

    terminal.registerCommand("win", [&](const std::vector<std::string>& args) {
        cmd_win(args, terminal);
    });

    terminal.registerCommand("sys", [&](const std::vector<std::string>& args) {
        cmd_sys(args, terminal);
    });

    // === Login beim Start ===
    while (!terminal.loginPrompt()) {}

    // Terminal starten
    terminal.run();

    return 0;
}
