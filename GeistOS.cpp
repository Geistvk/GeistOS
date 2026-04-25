#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <unordered_map>
#include <windows.h>

#include <algorithm>
#include <cctype>
#include <memory>

#include <dxgi.h>
#include <cstdlib>

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

#include <functional>

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

#include <ctime>

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

static inline std::string ltrim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start])))
        start++;
    return s.substr(start);
}

static inline std::string rtrim(const std::string& s) {
    if (s.empty()) return s;

    size_t end = s.size() - 1;
    while (end > 0 && std::isspace(static_cast<unsigned char>(s[end])))
        end--;

    return s.substr(0, end + 1);
}

static inline std::string trim(const std::string& s) {
    return rtrim(ltrim(s));
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

auto systemStart = std::chrono::steady_clock::now();
std::string cmdLog = "";
int cmdLogId = 1;

// ==========================
// Terminal-Klasse 
// ==========================
class Terminal {
private:
    struct Command {
        std::function<std::string(const std::vector<std::string>&, const std::string&)> func;
        bool requiresRead;
        bool requiresWrite;
        bool requiresExecute;
        bool requiresSudo;
    };

    bool running = true;
    std::map<std::string, Command> commands;

    std::string error = "none";
    std::unordered_map<std::string, User> users;
    User* currentUser = nullptr;
public:
    Terminal() {
        users["root"] = {0, "Root", "Root", "root", "root123", "2024", "Owner", "1111"};
        users["user"] = {1, "User", "User", "user", "user123", "2024", "Member", "1010"};
        users["Bot"] = {2, "Bot", "Bot", "Bot", "bot123", "2024", "Bot", "0010"};
        users["Amy"] = {3, "Admin", "Admin", "Admin", "admin123", "2024", "Admin", "1111"};
        users["Jonas"] = {4, "Jonas", "Broschinski", "Jonas", "12345", "2024", "Admin", "1111"};
    }

    void registerCommand(const std::string& name,
                         std::function<std::string(const std::vector<std::string>&, const std::string&)> func,
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

    bool loginPrompt() {
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

        std::cout << currentColor + "\033[1;32mUsername\033[0m: ";
        std::getline(std::cin, username);

        if (users.find(username) == users.end()) {
            error = "\033[0;31mUsername incorrect.\033[0m\n";
            return false;
        }

        std::cout << currentColor + "\033[1;32mPassword\033[0m: ";
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
            error = "\033[0;31mPassword incorrect.\033[0m\n";
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
            try
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));

                std::string prompt;
                if (currentColor != "\033[0;37m") {
                    prompt = secColor + currentUser->name + "@GeistOS:" + currentDictonary + "$";
                } else {
                    prompt = "\033[1;32m" + currentUser->name +
                            "@GeistOS\033[0m:\033[0;34m" +
                            currentDictonary + "\033[0m$";
                }

                std::cout << currentColor + prompt;

                if (!std::getline(std::cin, input)) {
                    std::cout << "\nInput stream closed\n";
                    std::cin.clear();
                    continue;
                }

                if (input.empty())
                    continue;

                if (input.size() > 50000) {
                    std::cout << "Input too large\n";
                    continue;
                }

                std::vector<std::string> pipeline;
                if (input.find('|') != std::string::npos)
                    pipeline = split(input, '|');
                else
                    pipeline.push_back(input);

                std::string pipeInput;
                bool error = false;

                for (const auto& raw : pipeline)
                {
                    if (error)
                        break;

                    std::string segment = trim(raw);
                    if (segment.empty())
                        continue;

                    auto tokens = split(segment, ' ');
                    if (tokens.empty())
                        continue;

                    bool sudoMode = false;

                    if (tokens[0] == "sudo") {
                        if (tokens.size() < 2) {
                            std::cout << "sudo: no command specified\n";
                            error = true;
                            break;
                        }

                        sudoMode = true;
                        tokens.erase(tokens.begin());
                    }

                    auto it = commands.find(tokens[0]);
                    if (it == commands.end()) {
                        std::cout << "Unknown command: " << tokens[0] << "\n";
                        error = true;
                        break;
                    }

                    auto& cmd = it->second;

                    if ((cmd.requiresRead && !handleRights(currentUser->userRights, 0)) ||
                        (cmd.requiresWrite && !handleRights(currentUser->userRights, 1)) ||
                        (cmd.requiresExecute && !handleRights(currentUser->userRights, 2)))
                    {
                        std::cout << "Permission denied\n";
                        error = true;
                        break;
                    }

                    std::string safeInput = pipeInput.substr(0, 10000);

                    if (sudoMode || cmd.requiresSudo)
                    {
                        if (!handleRights(currentUser->userRights, 3)) {
                            std::cout << "not in sudoers file\n";
                            error = true;
                            break;
                        }

                        std::cout << "[sudo] password: ";
                        std::string pass = getHiddenInput();

                        if (pass != currentUser->password) {
                            std::cout << "Sorry, try again.\n";
                            error = true;
                            break;
                        }
                    }

                    std::string output;

                    try {
                        cmdLog += std::to_string(cmdLogId++) + ". " + segment + "\n";

                        output = cmd.func(tokens, safeInput);
                    } catch (const std::bad_alloc&) {
                        std::cout << "Memory overflow in command: " << tokens[0] << "\n";
                        error = true;
                        break;
                    } catch (const std::exception& e) {
                        std::cout << "Error in command: " << e.what() << "\n";
                        error = true;
                        break;
                    } catch (...) {
                        std::cout << "Command crashed: " << tokens[0] << "\n";
                        error = true;
                        break;
                    }

                    pipeInput = output;

                    if (pipeInput.size() > 200000) {
                        std::cout << "Pipe overflow protection triggered\n";
                        error = true;
                        break;
                    }
                }

                /*if (!error && !pipeInput.empty()) {
                    std::cout << pipeInput << std::endl;
                }*/
            } catch (const std::exception& e) {
                std::cout << "Fatal loop error: " << e.what() << "\n";
            } catch (...) {
                std::cout << "Unknown fatal error in main loop\n";
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
};



class ConsoleWindow {
public: 
    struct Row {
        std::string label;
        std::string value;
    };

    struct Section {
        std::string title;
        std::vector<Row> rows;
    };

    ConsoleWindow(int w, const std::string& t) : minWidth(w), title(t) {}

    void addSection(const std::string& sectionTitle = "") {
        sections.push_back({sectionTitle, {}});
    }

    void addRow(const std::string& label, const std::string& value) {
        if (sections.empty()) addSection();
        sections.back().rows.push_back({label, value});
    }

private:
    int minWidth;
    std::string title;
    std::vector<Section> sections;

    const std::string RESET   = "\033[0m";
    const std::string TITLE   = "\033[1;37m";
    const std::string BORDER  = "\033[1;36m";
    const std::string LABEL   = "\033[1;34m";
    const std::string VALUE   = "\033[1;32m";
    const std::string SECTION = "\033[1;33m";

    int calculateWidth() const {
        int w = minWidth;

        w = std::max(w, (int)title.size() + 4);

        for (const auto& sec : sections) {
            w = std::max(w, (int)sec.title.size() + 6);

            for (const auto& r : sec.rows) {
                int len = 2 + r.label.size() + 1 + r.value.size() + 2;
                w = std::max(w, len);
            }
        }

        return w;
    }

public:
    void draw() const {
        int width = calculateWidth();

        auto line = [&](char left, char fill, char right) {
            std::cout << BORDER << left
                      << std::string(width - 2, fill)
                      << right << RESET << "\n";
        };

        auto centered = [&](const std::string& text, const std::string& color) {
            int pad = (width - 2 - (int)text.size()) / 2;
            std::cout << BORDER << "|"
                      << std::string(pad, ' ')
                      << color << text << RESET
                      << std::string(width - 2 - pad - text.size(), ' ')
                      << BORDER << "|" << RESET << "\n";
        };

        auto sectionLine = [&](const std::string& text) {
            std::string t = " " + text + " ";
            int total = width - 2;

            int left = (total - t.size()) / 2;
            int right = total - t.size() - left;

            std::cout << BORDER << "+"
                      << std::string(left, '-')
                      << SECTION << t << RESET
                      << BORDER
                      << std::string(right, '-')
                      << "+"
                      << RESET << "\n";
        };

        auto row = [&](const Row& r) {
            std::ostringstream out;
            out << " " << LABEL << std::left << std::setw(18) << r.label << RESET
                << " " << VALUE << std::left << std::setw(width - 23) << r.value << RESET << " ";

            std::string s = out.str();
            if ((int)s.size() < width - 2)
                s += std::string(width - 2 - s.size(), ' ');

            std::cout << BORDER << "|" << RESET
                      << s
                      << BORDER << "|" << RESET << "\n";
        };

        line('=','=', '=');
        centered(" " + title + " ", TITLE);
        line('=','=', '=');

        for (const auto& sec : sections) {

            if (!sec.title.empty()) {
                sectionLine(sec.title);
            } else {
                line('-','-','-');
            }

            for (const auto& r : sec.rows) {
                row(r);
            }
        }

        line('=','=', '=');
    }
};

class Config {
protected: 
    struct cmdHelp {
        std::string cmd;
        std::vector<std::string> args = {};
        boolean sudo = false;
        std::string suffix = ""; 
    };

    struct Category {
        std::string title;
        std::vector<cmdHelp> lines;
        size_t width = 0;
    };





    struct changes {
        std::string type;
        std::string color;
        std::string description;
    };

    struct SubVersions {
        std::string title;
        std::vector<changes> changes;
    };

    struct versionHistory {
        std::string title;
        std::vector<SubVersions> subVersions;
    };
    
private: 
    std::vector<Category> categories;
    std::vector<versionHistory> allVersions;

    void initHelpCategories() {
        categories.clear();

        categories.push_back({
            "General",
            {
                {"help"}, {"clear"}, {"echo"}, {"ls"}, {"exit"}, {"logout"}, {"date"}
            }
        });

        categories.push_back({
            "Network & System",
            {
                {"ping", {"ip"}},
                {"sys", {"info", "help", "uptime", "time", "tasks", "run", "kill", "mem", "cpu", "host", "config", "update", "clearcache", "bench"}}
            }
        });

        categories.push_back({
            "File System",
            {
                {"dir /s"},
                {"cd", {"Folder Path", "Folder Name"}},
                {"mkdir", {"Folder Name"}},
                {"rm", {"File Name", "Folder Name"}, true},
                {"touch", {"File Name"}},
                {"vim", {"File Name"}}
            }
        });

        categories.push_back({
            "Users & Permissions",
            {
                {"user", {"list", "add", "edit", "del", "help"}, true},
                {"perm", {"list", "edit", "info", "help"}, true},
                {"passwd", {}, true}
            }
        });

        categories.push_back({
            "System Tools",
            {
                {"apt update/install", {"Package"}, true}
            }
        });

        categories.push_back({
            "Entertaining",
            {
                {"games", {"casino"}}, 
                {"bank", {}}
            }
        });

        categories.push_back({
            "UI & Output",
            {
                {"print", {"text"}},
                {"color", {"hex-codes"}, false, "(0-F, 7 default)"}
            }
        });
    }





    void initVersions() {
        allVersions.clear();

        allVersions.push_back({
            "0.0.0.1",
            {
                {
                    "0.0.0.1.1",
                    {
                        {"Added", "\033[1;30m", "Dynamic C++ Code for an Linux like OS"}
                    }
                },
                {
                    "0.0.0.1.2",
                    {
                        {"Added", "\033[1;34m", "help\033[0m, \033[1;34mclear\033[0m, \033[1;34mecho\033[0m, \033[1;34mls\033[0m, \033[1;34mexit"},
                        {"Added", "\033[1;34m", "ping <ip>"}
                    }
                }
            }
        });

        allVersions.push_back({
            "0.0.0.2",
            {
                {
                    "0.0.0.2.1",
                    {
                        {"Added", "\033[1;34m", "dir /s"},
                        {"Added", "\033[1;34m", "apt update/install <Package>\033[0m (\033[1;36msudo\033[0m required)"}
                    }
                },
                {
                    "0.0.0.2.2",
                    {
                        {"Added", "\033[1;34m", "cd <Folder Path or Folder Name>"},
                        {"Added", "\033[1;34m", "mkdir <Folder Name>"}, 
                        {"Added", "\033[1;34m", "rm <filename|foldername>\033[0m (\033[1;36msudo\033[0m required)"}
                    }
                },
                {
                    "0.0.0.2.3",
                    {
                        {"Added", "\033[1;34m", "touch <File Name>"},
                        {"Added", "\033[1;34m", "vim <File Name>"}
                    }
                }
            }
        });

        allVersions.push_back({
            "0.0.0.3",
            {
                {
                    "0.0.0.3.1", 
                    {
                        {"Added", "\033[1;34m", "color <hex-code>\033[0m (0-F) {7 = default}"}
                    }
                },
                {
                    "0.0.0.3.2",
                    {
                        {"Added", "\033[1;34m", "addUser <Username>"},
                        {"Added", "\033[1;34m", "listUser <Username>"},
                        {"Added", "\033[1;34m", "delUser <Username>"},
                        {"Added", "\033[1;34m", "passwd\033[0m (\033[1;36msudo\033[0m required)"}
                    }
                }
            }
        });

        allVersions.push_back({
            "0.0.0.4",
            {
                {
                    "0.0.0.4.1", 
                    {
                        {"Updated", "\033[1;34m", "user <list/add/edit/del/help>\033[0m (\033[1;36msudo\033[0m required)"},
                        {"Reworked", "\033[1;34m", "perm <list/edit/info/help>\033[0m (\033[1;36msudo\033[0m required)"}
                    }
                },
                {
                    "0.0.0.4.2",
                    {
                        {"Added", "\033[1;30m", "Spinning Ghost Idle Animation"},
                        {"Added", "\033[1;30m", "Early Versions of GeistOS GUI"},
                        {"Added", "\033[1;34m", "win"}
                    }
                },
                {
                    "0.0.0.4.3",
                    {
                        {"Added", "\033[1;34m", "Letter Library for print Cmd"},
                        {"Added", "\033[1;34m", "print <word to print>"}
                    }
                }
            }
        });

        allVersions.push_back({
            "0.0.0.5",
            {
                {
                    "0.0.0.5.1",
                    {
                        {"Reworked", "\033[1;30m", "Spinning Ghost Idle Animation"}, 
                        {"Disabled", "\033[1;30m", "Spinning 3D Ghost Idle Animation"}
                    }
                },
                {
                    "0.0.0.5.2",
                    {
                        {"Added", "\033[1;34m", "sys version <history/cur>"},
                        {"Added", "\033[1;34m", "sys log <show/clear>"}
                    }
                }
            }
        });

        allVersions.push_back({
            "0.0.0.6",
            {
                {
                    "0.0.0.6.1",
                    {
                        {"Reworked", "\033[1;30m", "User Rank System"},
                        {"Reworked", "\033[1;30m", "User Settings Menu"},
                        {"Added", "\033[1;34m", "A lot of Features to the sys Command"},
                        {"Info", "\033[1;30m", "Type 'sys help' to see all features"},
                        {"Added", "\033[1;34m", "Pipes that run multiple commands at once"}
                    }
                },
                {
                    "0.0.0.6.2",
                    {
                        {"Reworked", "\033[1;30m", "The Help Screen with fresh colors and new Backend"},
                        {"Added", "\033[1;34m", "The Date Command with a beautiful Table View"},
                        {"Reworked", "\033[1;30m", "The Date Command with a modular Design"}
                    }
                },
                {
                    "0.0.0.6.3",
                    {
                        {"Reworked", "\033[1;30m", "The Logic of the 'help' and the 'sys versions' command to be more modular"},
                        {"Added", "\033[1;34m", "A central Config class that the 'help' and 'sys version' command get the data from"}
                    }
                },
                {
                    "0.0.0.6.4",
                    {
                        {"Added", "\033[1;34m", "A new 'games' command that has different groups of games"},
                        {"Added", "\033[1;34m", "The section 'casino' to the 'games' command"},
                        {"Added", "\033[1;34m", "The Games 'roulette', 'Dice Rolling Game' and 'Slots' to the 'games casino' command"},
                        {"Added", "\033[1;34m", "A new 'bank' command"}
                    }
                },
                {
                    "0.0.0.6.5",
                    {
                        {"Reworked", "\033[1;30m", "The 'sys version history' command with fresh visuals and clear versions and subVersions"},
                        {"Reworked", "\033[1;30m", "The Logic of the main function to be more modular and easy to modify"}
                    }
                },
                {
                    "0.0.0.6.6",
                    {
                        {"Added", "\033[1;34m", "The AsciiGraph Class to manage and render Graphes in pure Text"},
                        {"Added", "\033[1;34m", "A new 'graph' command to test the AsciiGraph Class"}
                    }
                }
            }
        });
    }

public: 
    Config() {
        initHelpCategories();
        initVersions();
    }

    std::vector<Category> getHelpCategories() {
        return categories;
    }

    std::vector<versionHistory> getAllVersions() {
        return allVersions;
    }
};

Config config;

class Help: public Config {
private:
    int maxPerLine = 4;
    int maxListPerLine = 9;

    std::string standard   = getAnsiColor('8');
    std::string textColor1 = getAnsiColor('1');
    std::string textColor2 = getAnsiColor('3');
    std::string catTitle   = getAnsiColor('D');
    std::string sudoColor  = getAnsiColor('B');

    std::vector<Category> categories;

    void printCategory(const std::string& title) {
        std::cout << "\n" << standard << "==== " << catTitle << title << standard << " ====\n";
    }

    void printStandardCmds(const std::vector<cmdHelp>& cmds) {
        std::cout << textColor1 << "  ";

        for (size_t i = 0; i < cmds.size(); i++) {
            if (i != 0 && i % maxPerLine == 0) {
                std::cout << "\n  ";
            }

            std::cout << textColor1 << cmds[i].cmd;

            if (i < cmds.size() - 1 && ((i + 1) % maxPerLine) != 0) {
                std::cout << standard << ", ";
            }
        }

        std::cout << standard << "\n";
    }

    void printHelp(
        const std::string& cmd,
        const std::vector<std::string>& list,
        bool sudo = false,
        const std::string& suffix = ""
    ) {
        std::cout << textColor1 << "  " << cmd;

        if (!list.empty()) {
            std::cout << standard << " <";

            int totalListIndex = 0;
            int listIndex = 0;
            int totalCharLength = 0;

            auto handleOverflow = [&]() {
                std::cout << standard << "\n   ";
                for (size_t u = 0; u <= cmd.size(); u++) {
                    std::cout << standard << " ";
                }
                listIndex = 0;
                totalCharLength = 0;
            };

            for (size_t i = 0; i < list.size(); i++) {
                boolean isNotEndItem = (totalListIndex + 1) < ((int) list.size());
                totalCharLength += (int) list[i].size();

                std::cout << textColor2 << list[i];

                if (i < list.size() - 1) {
                    std::cout << standard << "/";
                }

                if (isNotEndItem &&
                    ((listIndex >= maxListPerLine) ||
                    //(totalCharLength >= (maxListPerLine) * 2) ||
                    (totalCharLength >= ((maxListPerLine - 1) * 2)))
                ) {
                    handleOverflow();
                }

                totalListIndex++;
                listIndex++;
            }

            std::cout << standard << ">";
        }

        if (!suffix.empty()) {
            std::cout << standard << " " << suffix;
        }

        if (sudo) {
            std::cout << standard << " (" << sudoColor << "sudo" << standard << " required)";
        }

        std::cout << standard << "\n";
    }

    void printCmds() {
        int catIndex = 0;
        for (const auto& category : categories) {
            printCategory(category.title);

            if (catIndex > 0) {
                for (const auto& cmd : category.lines) {
                    printHelp(cmd.cmd, cmd.args, cmd.sudo, cmd.suffix);
                }
            } else {
                printStandardCmds(category.lines);
            }

            catIndex++;
        }
    }

    void initCategories() {
        categories = config.getHelpCategories();
    }

public:
    void render() {
        initCategories();
        printCmds();
    }
};

// ==========================
// Befehle
// ==========================
void cmd_help(const std::vector<std::string>& args) {
    (void)args;

    Help help;

    printScreen("Help");
    std::cout << currentColor + "Available Commands:\n";
    help.render();
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

        std::vector<std::pair<const std::string, User>> vec;
        vec.reserve(users.size());
        for (const auto& p : users) {
            vec.push_back(p);
        }

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

void cmd_date(const std::vector<std::string>& args, Terminal& term) {
    (void) args; (void) term;
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *ltm = std::localtime(&currentTime);

    const char* weekdays[] = {
        "Sunday","Monday","Tuesday",
        "Wednesday","Thursday","Friday","Saturday"
    };

    std::ostringstream date, time;

    date << (1900 + ltm->tm_year) << "-"
         << std::setw(2) << std::setfill('0') << (1 + ltm->tm_mon) << "-"
         << std::setw(2) << ltm->tm_mday;

    time << std::setw(2) << std::setfill('0') << ltm->tm_hour << ":"
         << std::setw(2) << ltm->tm_min << ":"
         << std::setw(2) << ltm->tm_sec;

    ConsoleWindow win(50, "Current Date");

    win.addSection("General");
    win.addRow("Date", date.str());
    win.addRow("Time", time.str());
    win.addRow("Day", weekdays[ltm->tm_wday]);

    win.addSection("Date Details");
    win.addRow("Year", std::to_string(1900 + ltm->tm_year));
    win.addRow("Month", std::to_string(1 + ltm->tm_mon));
    win.addRow("Day", std::to_string(ltm->tm_mday));
    win.addRow("Day of Year", std::to_string(ltm->tm_yday));

    win.addSection("Time Details");
    win.addRow("Hour", std::to_string(ltm->tm_hour));
    win.addRow("Minute", std::to_string(ltm->tm_min));
    win.addRow("Second", std::to_string(ltm->tm_sec));

    win.addSection("Other");
    win.addRow("Summertime", ltm->tm_isdst ? "Yes" : "No");

    win.draw();
}

void cmd_dateOld(const std::vector<std::string>& args, Terminal& term) {
    (void) args; (void) term;
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *ltm = std::localtime(&currentTime);

    const std::string RESET  = "\033[0m";
    const std::string TITLE  = "\033[1;37m";
    const std::string BORDER = "\033[1;36m";
    const std::string LABEL  = "\033[1;34m";
    const std::string VALUE  = "\033[1;32m";
    const std::string DIM    = "\033[2m";

    const char* weekdays[] = {
        "Sunday","Monday","Tuesday",
        "Wednesday","Thursday","Friday","Saturday"
    };

    std::ostringstream date, time;
    date << (1900 + ltm->tm_year) << "-"
         << std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon) << "-"
         << std::setw(2) << ltm->tm_mday;

    time << std::setfill('0')
         << std::setw(2) << ltm->tm_hour << ":"
         << std::setw(2) << ltm->tm_min  << ":"
         << std::setw(2) << ltm->tm_sec;

    const int W = 50;

    auto line = [&](char left, char fill, char right) {
        std::cout << BORDER << left << std::string(W - 2, fill) << right << RESET << "\n";
    };

    auto row = [&](const std::string& l, const std::string& v) {
        std::ostringstream out;
        out << " " << LABEL << std::left << std::setw(18) << l << RESET
            << " " << VALUE << std::left << std::setw(27) << v << RESET << " ";
        std::string s = out.str();
        if ((int)s.size() < W - 2) s += std::string(W - 2 - s.size(), ' ');
        std::cout << BORDER << "|" << RESET << s << BORDER << "|" << RESET << "\n";
    };

    line('+','-','+');

    std::string title = " Current Date ";
    int pad = (W - 2 - (int)title.size()) / 2;
    std::cout << BORDER << "|"
              << std::string(pad, ' ')
              << TITLE << title << RESET
              << std::string(W - 2 - pad - title.size(), ' ')
              << BORDER << "|" << RESET << "\n";

    line('+','-','+');

    row("Date", date.str());
    row("Time", time.str());
    row("Day", weekdays[ltm->tm_wday]/* + std::string(" (") + std::to_string(ltm->tm_wday) + ")"*/);

    line('+','-','+');

    row("Year", std::to_string(1900 + ltm->tm_year));
    row("Month", std::to_string(1 + ltm->tm_mon));
    row("Day", std::to_string(ltm->tm_mday));
    row("Day of the Year", std::to_string(ltm->tm_yday));

    line('+','-','+');
    
    row("Hour", std::to_string(ltm->tm_hour));
    row("Minute", std::to_string(ltm->tm_min));
    row("Second", std::to_string(ltm->tm_sec));
    
    line('+','-','+');
    
    row("Summertime", ltm->tm_isdst ? "Yes" : "No");

    line('+','-','+');
    //std::cout << DIM << "Wochentag: 0=Sonntag, 6=Samstag" << RESET << "\n";
}

std::string curVersion;

class Versions: public Config {
private: 
    std::vector<versionHistory> allVersions;

    void initVersions() {
        allVersions = config.getAllVersions();
    }

    void printVersion(const std::string& version) {
        curVersion = version;

        std::cout << currentColor
                << "\n   === \033[1;37mGeistOS\033[0m "
                << "\033[1;35mV" << version << "\033[0m "
                << "===\n";
    }

    void printSubVersion(const std::string& version) {
        curVersion = version;

        std::cout << currentColor
                << "   |-- \033[1;36mV" << version << "\033[0m\n";
    }

    void printUpdate(const std::string& prefix, const std::string& color, const std::string& change) {
        std::cout << currentColor
                << "   |   |-- \033[1;30m[" << prefix << "]\033[0m "
                << color << change
                << "\033[0m\n";
    }

    void printVersionHistory() {
        for (const auto& version : allVersions) {
            printVersion(version.title);

            for (const auto& subVersion : version.subVersions) {
                printSubVersion(subVersion.title);

                for (const auto& change : subVersion.changes) {
                    printUpdate(change.type, change.color, change.description);
                }
            }
        }
    }

public:
    void render() {
        initVersions();
        printVersionHistory();
    }
};

// =========================
// Fake System States
// =========================
std::map<std::string, std::string> sysConfig = {
    {"hostname", "GeistOS-PC"},
    {"theme", "dark"},
    {"version_channel", "stable"}
};

struct Task {
    int pid;
    std::string name;
};

std::vector<Task> tasks = {
    {1, "init"},
    {2, "terminal"},
    {3, "ghost_anim"}
};

int nextPID = 4;

#define C_RESET "\033[0m"
#define C_CMD "\033[1;34m"
#define C_ERR "\033[1;31m"
#define C_OK "\033[1;32m"
#define C_WARN "\033[1;33m"
#define C_TITLE "\033[1;35m"
#define C_VAL "\033[0;36m"


void cmd_sys(const std::vector<std::string>& args, Terminal& term) {

    if (args.size() < 2) {
        std::cout << currentColor
        << C_WARN << "Usage: " << C_CMD
        << "sys [info/uptime/time/tasks/run/kill/mem/cpu/config/host/update/clearcache/bench]"
        << C_RESET << "\n";
        return;
    } else if (args[1] == "version") {
        if (args[2] == "history") {
            Versions versions;

            printScreen("Versions");

            std::cout << currentColor + "All \033[0;35mVersions\033[0;0m:\n";
            versions.render();
            
        } else if (args[2] == "cur") {
            std::cout << currentColor + "\033[1;30mCurrent Version\033[1;0m: \033[0;37mGeistOS v\033[1;0m\033[0;35m" + curVersion + "\033[0;0m:\n";
        } else {
            std::cout << C_ERR << "Usage: " << C_CMD << "sys version <history/cur>" << C_RESET << "\n";
        }
    } else if (args[1] == "log") {

        if (args.size() < 3) {
            std::cout << C_ERR << "Usage: " << C_CMD << "sys log <show/clear>" << C_RESET << "\n";
            return;
        }

        if (args[2] == "show") {
            printScreen("CMD History");
            term.getCmdLog();
        }

        else if (args[2] == "clear") {
            term.clearCmdLog();
            std::cout << C_OK << "Log cleared." << C_RESET << "\n";
        }
    } else if (args[1] == "info") {
        curVersion = "0.0.0.6";
        auto user = term.getCurrentUser();
        printScreen("System Info");

        std::cout << C_WARN << "OS: " << C_VAL << "GeistOS\n";
        std::cout << C_WARN << "Version: " << C_VAL << curVersion << "\n";
        std::cout << C_WARN << "Username: " << C_VAL << user->name << "\n";
        std::cout << C_WARN << "User: " << C_VAL << user->preName << " " << user->lastName << "\n";
        std::cout << C_WARN << "Hostname: " << C_VAL << sysConfig["hostname"] << C_RESET << "\n";
    } else if (args[1] == "uptime") {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - systemStart);

        std::cout << C_WARN << "Uptime: "
                << C_VAL
                << duration.count() / 3600 << "h "
                << (duration.count() % 3600) / 60 << "m "
                << duration.count() % 60 << "s"
                << C_RESET << "\n";
    } else if (args[1] == "time") {
        std::time_t t = std::time(nullptr);
        std::cout << C_WARN << "Current Time: " << C_VAL
                << std::ctime(&t) << C_RESET;
    } else if (args[1] == "tasks") {
        printScreen("Running Tasks");

        for (auto& t : tasks) {
            std::cout << C_WARN << "PID: " << C_VAL << t.pid
                    << C_WARN << " | " << C_VAL << t.name << "\n";
        }
    } else if (args[1] == "kill") {
        if (args.size() < 3) {
            std::cout << C_ERR << "Usage: " << C_CMD << "sys kill <pid>" << C_RESET << "\n";
            return;
        }

        int pid = std::stoi(args[2]);

        tasks.erase(
            std::remove_if(tasks.begin(), tasks.end(),
                [&](Task& t){ return t.pid == pid; }),
            tasks.end()
        );

        std::cout << C_OK << "Process " << pid << " killed." << C_RESET << "\n";
    } else if (args[1] == "run") {
        if (args.size() < 3) {
            std::cout << C_ERR << "Usage: " << C_CMD << "sys run <name>" << C_RESET << "\n";
            return;
        }

        tasks.push_back({nextPID++, args[2]});
        std::cout << C_OK << "Started task: " << C_VAL << args[2] << C_RESET << "\n";
    } else if (args[1] == "mem") {
        //Simulated Data (Not real)
        int used = 512 + (rand() % 1024);
        std::cout << C_WARN << "Memory: " << C_VAL << used << "MB / 2048MB" << C_RESET << "\n";
    } else if (args[1] == "cpu") {
        //Simulated Data (Not real)
        std::cout << C_WARN << "CPU Usage: " << C_VAL << (rand() % 100) << "%" << C_RESET << "\n";
    } else if (args[1] == "config") {
        if (args.size() == 2) {
            printScreen("System Config");

            for (auto& c : sysConfig) {
                std::cout 
                    << C_WARN << std::setw(15) << std::left << c.first
                    << C_RESET << " : "
                    << C_VAL << c.second 
                    << C_RESET << "\n";
            }
        } else if (args.size() >= 5 && args[2] == "set") {

            std::string key = args[3];
            std::string value = args[4];

            if (sysConfig.find(key) == sysConfig.end()) {
                std::cout 
                    << C_ERR << "Unknown config key: "
                    << C_CMD << key 
                    << C_RESET << "\n";
                return;
            }

            std::string oldValue = sysConfig[key];
            sysConfig[key] = value;

            std::cout 
                << C_OK << "Updated "
                << C_CMD << key 
                << C_RESET << " ("
                << C_VAL << oldValue 
                << C_RESET << " -> "
                << C_VAL << value 
                << C_RESET << ")\n";
        } else if (args.size() == 4 && args[2] == "get") {
            std::string key = args[3];

            if (sysConfig.find(key) != sysConfig.end()) {
                std::cout 
                    << C_WARN << key << " = "
                    << C_VAL << sysConfig[key]
                    << C_RESET << "\n";
            } else {
                std::cout << C_ERR << "Key not found" << C_RESET << "\n";
            }
        } else {
            std::cout 
                << C_ERR << "Invalid usage.\n"
                << C_WARN << "Usage: " 
                << C_CMD << "sys config [set <key> <value> | get <key>]\n"
                << C_RESET;

            std::cout 
                << C_TITLE << "\nAvailable keys:\n" 
                << C_RESET;

            for (auto& c : sysConfig) {
                std::cout << "  " << C_CMD << c.first << C_RESET << "\n";
            }
        }
    } else if (args[1] == "host") {
        if (args.size() < 3) {
            std::cout << C_WARN << "Hostname"<< C_RESET << ": " << C_VAL << sysConfig["hostname"] << C_RESET << "\n";
        } else {
            sysConfig["hostname"] = args[2];
            std::cout << C_WARN << "Hostname" << C_RESET << " changed to " << C_VAL << args[2] << C_RESET << "\n";
        }
    } else if (args[1] == "update") {
        std::cout << C_WARN << "Checking for updates...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << C_WARN << "Fetching Packages ...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << C_WARN << "Installing Packages ...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << C_OK << "System is up to date ✔" << C_RESET << "\n";
    } else if (args[1] == "clearcache") {
        std::cout << C_WARN << "Clearing cache..." << C_RESET << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << C_OK << "Done." << C_RESET << "\n";
    } else if (args[1] == "bench") {
        printScreen("Benchmark");

        int limit = 100000000;

        if (args.size() >= 3) {
            try {
                limit = std::stoi(args[2]);
            } catch (...) {
                std::cout << C_ERR << "Invalid Number" << C_RESET << ": "
                        << C_CMD << args[2]
                        << C_RESET << "\n";
                std::cout << C_ERR << "Only enter Numbers (" << C_VAL << "1 - " << INT_MAX << C_ERR << ")" << C_RESET "\n";
                return;
            }
        }

        std::cout << C_WARN << "Running Benchmark\n" << "Iterations" << C_RESET << ": " << C_VAL << limit << C_RESET << "\n";

        auto start = std::chrono::high_resolution_clock::now();

        volatile int x = 0;
        for (int i = 0; i < limit; i++) x++;

        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << C_WARN << "Benchmark Time: "
                << C_VAL << dur.count() << " ms"
                << C_RESET << "\n";
        
        std::cout << C_WARN << "Benchmark Time: "
                << C_VAL << (((double) dur.count()) / 1000) << " s"
                << C_RESET << "\n";
    } else if (args[1] == "loading") {
        printScreen("Loader");

        std::string loading = "\u2588"; //█
        std::string progressBar = "";

        SetConsoleOutputCP(CP_UTF8);

        for (int i = 0; i <= 100; i+=10) {
            //std::cout << currentColor + "\rProgress: " << i << "%";
            progressBar += loading;
            std::cout << currentColor + "\rProgress: " << progressBar << " ";

            std::cout.flush();
            wait(randomNum(1000, 3000));
        }
        std::cout << std::endl;

    } else if (args[1] == "help") {
        printScreen("sys Commands");

        std::cout
        << C_CMD  << "info        " << C_RESET << "- " << C_VAL << "system info\n"
        << C_CMD  << "uptime      " << C_RESET << "- " << C_VAL << "show uptime\n"
        << C_CMD  << "time        " << C_RESET << "- " << C_VAL << "current time\n"
        << C_CMD  << "tasks       " << C_RESET << "- " << C_VAL << "list processes\n"
        << C_CMD  << "run <name>  " << C_RESET << "- " << C_VAL << "start task\n"
        << C_CMD  << "kill <pid>  " << C_RESET << "- " << C_VAL << "kill task\n"
        << C_CMD  << "cpu         " << C_RESET << "- " << C_VAL << "cpu usage\n"
        << C_CMD  << "mem         " << C_RESET << "- " << C_VAL << "memory usage\n"
        << C_CMD  << "config      " << C_RESET << "- " << C_VAL << "show config\n"
        << C_CMD  << "host        " << C_RESET << "- " << C_VAL << "show/set hostname\n"
        << C_CMD  << "update      " << C_RESET << "- " << C_VAL << "system update\n"
        << C_CMD  << "clearcache  " << C_RESET << "- " << C_VAL << "clear cache\n"
        << C_CMD  << "bench       " << C_RESET << "- " << C_VAL << "performance test\n";
    } else {
        std::cout << C_ERR << "Unknown command.\n" 
                << C_WARN << "Usage: " 
                << C_CMD << "sys [info/uptime/time/tasks/run/kill/mem/cpu/config/host/update/clearcache/bench]" 
                << C_RESET << "\n";
    }
}





// Farben
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

#define REDR     "\033[31m"
#define GREENR   "\033[32m"
#define YELLOWR  "\033[33m"
#define WHITER   "\033[37m"
#define RESETR   "\033[0m"

class IGame {
public:
    virtual ~IGame() = default;
    virtual std::string getName() const = 0;
    virtual void play() = 0;
};

// ---------------- BANK ----------------
class Bank {
private:
    int balance;
    std::string depositString = "Deposit";
    std::string widthdrawString = "Withdraw";

    struct Transaction {
        int id;
        std::string type;
        std::string operation;
        int amount;
        std::string timestamp;
        int balanceBefore;
        int balanceAfter;
    };

    std::vector<Transaction> history;
    int nextId = 1;

    static std::string getTimeStamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        std::tm tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%d.%m.%Y %H:%M:%S");
        return oss.str();
    }

    static std::string formatBalance(long long value) {
        std::string s = std::to_string(value);
        std::string result;

        int count = 0;

        for (int i = (int)s.size() - 1; i >= 0; i--) {
            result.insert(result.begin(), s[i]);
            count++;

            if (count % 3 == 0 && i != 0) {
                result.insert(result.begin(), '.');
            }
        }

        return result;
    }

    void addTransaction(const std::string& type, int amount) {
        std::string operation;
        
        int balanceBefore = balance;

        if (type == widthdrawString) {
            operation = REDR + std::string("-");
            balanceBefore += amount;
        }
        else if (type == depositString) {
            operation = GREENR + std::string("+");
            balanceBefore -= amount;
        }

        Transaction t;
        t.id = nextId++;
        t.type = type;
        t.operation = operation;
        t.amount = amount;
        t.timestamp = getTimeStamp();
        t.balanceBefore = balanceBefore;
        t.balanceAfter = balance;

        history.push_back(t);
    }

public:
    Bank(int start) : balance(start) {}

    int getBalance() const {
        return balance;
    }

    bool withdraw(int amount) {
        if (amount > balance) return false;

        balance -= amount;
        addTransaction(widthdrawString, amount);
        return true;
    }

    void deposit(int amount) {
        balance += amount;
        addTransaction(depositString, amount);
    }

    void print() const {
        std::cout << YELLOWR
                  << "Balance: "
                  << formatBalance(balance)
                  << " Chips\n"
                  << RESETR;
    }

    void printHistory() const {
        for (const auto& t : history) {
            std::cout << std::left
                    << RESETR << std::setw(4)  << ("#" + std::to_string(t.id))
                    << RESETR << std::setw(22) << ("[" + t.timestamp + "]")
                    << RESETR << std::setw(9) << t.type
                    << RESETR << " | "
                    << RESETR << std::setw(20) << (t.operation + formatBalance(t.amount))
                    << RESETR << " | "
                    << RESETR << std::setw(20) << ("Old Balance: " + formatBalance(t.balanceBefore))
                    << RESETR << " | "
                    << RESETR << std::setw(20) << ("New Balance: " + formatBalance(t.balanceAfter))
                    << RESETR << "\n";
        }
    }
};






// ---------------- ROULETTE ----------------
class Roulette : public IGame {
private:
    Bank& bank;

    bool isRed(int n) {
        int red[] = {
            1,3,5,7,9,12,14,16,18,19,
            21,23,25,27,30,32,34,36
        };
        for (int r : red) if (r == n) return true;
        return false;
    }

    void printNumber(int n) {
        if (n == 0) {
            std::cout << GREENR << n << RESETR;
        } else if (isRed(n)) {
            std::cout << REDR << n << RESETR;
        } else {
            std::cout << WHITER << n << RESETR;
        }
    }

    void drawTable() {
        std::cout << "\n";
        std::cout << GREENR << "========== ROULETTE ==========\n" << RESETR;
        std::cout << "Numbers:\n";

        for (int i = 0; i <= 36; i++) {
            printNumber(i);
            std::cout << " ";

            if (i % 12 == 0 && i != 0) std::cout << "\n";
        }

        std::cout << "\n==============================\n";
    }

    void spinWheel(int finalNumber) {
        std::vector<int> wheel = {
            0,32,15,19,4,21,2,25,17,34,
            6,27,13,36,11,30,8,23,10,5,
            24,16,33,1,20,14,31,9,22,18,
            29,7,28,12,35,3,26
        };

        auto printNum = [&](int n) {
            if (n == 0) std::cout << "\033[32m" << n << "\033[0m";
            else if (isRed(n)) std::cout << "\033[31m" << n << "\033[0m";
            else std::cout << "\033[37m" << n << "\033[0m";
        };

        int index = 0;
        (void) index;

        for (int i = 0; i < (int)wheel.size(); i++) {
            if (wheel[i] == finalNumber) {
                index = i;
                break;
            }
        }

        int current = 0;
        int steps = 80 + (std::rand() % 40);

        for (int i = 0; i < steps; i++) {
            current = (current + 1) % wheel.size();

            std::cout << "\r";

            std::cout << "        ";
            for (int j = -3; j <= 3; j++) {
                int idx = (current + j + wheel.size()) % wheel.size();

                if (j == 0) {
                    std::cout << "[";
                    printNum(wheel[idx]);
                    std::cout << "]";
                } else {
                    std::cout << " ";
                    printNum(wheel[idx]);
                    std::cout << " ";
                }
            }

            std::cout << "   " << std::flush;

            std::this_thread::sleep_for(
                std::chrono::milliseconds(40 + i * 4)
            );
        }

        while (wheel[current] != finalNumber) {
            current = (current + 1) % wheel.size();

            std::cout << "\r        ";
            for (int j = -3; j <= 3; j++) {
                int idx = (current + j + wheel.size()) % wheel.size();

                if (j == 0) {
                    std::cout << "[";
                    printNum(wheel[idx]);
                    std::cout << "]";
                } else {
                    std::cout << " ";
                    printNum(wheel[idx]);
                    std::cout << " ";
                }
            }

            std::cout << "   " << std::flush;

            std::this_thread::sleep_for(
                std::chrono::milliseconds(120)
            );
        }

        std::cout << "\n";
    }

public:
    Roulette(Bank& b) : bank(b) {}

    std::string getName() const override {
        return "Roulette";
    }

    void play() override {
        int betNumber, betAmount;

        drawTable();
        bank.print();

        std::cout << "Bet on Number (0-36): ";
        std::cin >> betNumber;

        if (betNumber < 0 || betNumber > 36) {
            std::cout << REDR << "Invalid Number\n" << RESETR;
            return;
        }

        std::cout << "Bet: ";
        std::cin >> betAmount;

        if (!bank.withdraw(betAmount)) {
            std::cout << REDR << "Balance is too low\n" << RESETR;
            return;
        }

        int result = std::rand() % 37;

        std::cout << "\nWheel spins...\n";
        spinWheel(result);

        std::cout << "\nResult: ";
        printNumber(result);
        std::cout << "\n";

        if (result == betNumber) {
            int win = betAmount * 35;
            bank.deposit(win);

            std::cout << GREENR << "You Won +" << win << "\n" << RESETR;
        } else {
            std::cout << REDR << "You Lost -" << betAmount << "\n" << RESETR;
        }

        bank.print();
    }
};




class DiceGame : public IGame {
private:
    Bank& bank;

public:
    DiceGame(Bank& b) : bank(b) {}

    std::string getName() const override {
        return "Dice Game";
    }

    void play() override {
        int bet;

        std::cout << CYAN << "\n=== DICE GAME ===\n" << RESET;
        bank.print();

        std::cout << "Bet: ";
        std::cin >> bet;

        if (!bank.withdraw(bet)) {
            std::cout << RED << "Not enough Balance\n" << RESET;
            return;
        }

        int player = (std::rand() % 6) + 1;
        int cpu    = (std::rand() % 6) + 1;

        std::cout << "You:  " << player << "\n";
        std::cout << "CPU: " << cpu << "\n";

        if (player > cpu) {
            int win = bet * 2;
            bank.deposit(win);
            std::cout << GREEN << "You Won +" << win << "\n" << RESET;
        } else if (player == cpu) {
            bank.deposit(bet);
            std::cout << YELLOW << "Tie\n" << RESET;
        } else {
            std::cout << RED << "You Lost -" << bet << "\n" << RESET;
        }
    }
};


class SlotGame : public IGame {
private:
    Bank& bank;

    const int WIDTH = 5;

    std::vector<std::string> symbols = {
        "7", "BAR", "CHR", "LEM", "DIA"
    };

    std::string pad(const std::string& s) {
        std::string out = s;
        while ((int)out.size() < WIDTH) out += " ";
        return out;
    }

    std::string color(const std::string& s) {
        if (s == "7")   return "\033[31m" + pad(s) + "\033[0m";
        if (s == "BAR") return "\033[37m" + pad(s) + "\033[0m";
        if (s == "CHR") return "\033[32m" + pad(s) + "\033[0m";
        if (s == "LEM") return "\033[33m" + pad(s) + "\033[0m";
        if (s == "DIA") return "\033[36m" + pad(s) + "\033[0m";
        return pad(s);
    }

    void drawReels(int r1, int r2, int r3, bool highlight = false) {
        std::cout << "\033[H";

        std::cout << "==============================\n";
        std::cout << "         SLOT MACHINE         \n";
        std::cout << "==============================\n\n";

        bank.print();
        std::cout << "\n";

        for (int row = -1; row <= 1; row++) {
            std::string offset = "     ";
            if (row == 0) offset = "";

            int i1 = (r1 + row + symbols.size()) % symbols.size();
            int i2 = (r2 + row + symbols.size()) % symbols.size();
            int i3 = (r3 + row + symbols.size()) % symbols.size();

            if (row == 0) std::cout << "  -->";

            std::cout << offset + "  | ";

            auto cell = [&](int idx) {
                bool hl = (highlight && row == 0);

                if (hl) std::cout << "\033[42m";
                std::cout << color(symbols[idx]);
                if (hl) std::cout << "\033[0m";
            };

            cell(i1);
            std::cout << " | ";
            cell(i2);
            std::cout << " | ";
            cell(i3);

            std::cout << " |";

            if (row == 0) std::cout << "  <--";

            std::cout << "\n";
        }

        std::cout << "\n" << std::flush;
    }

    bool almostWin(const std::string& a,
                   const std::string& b,
                   const std::string& c) {
        return (a == b && b != c) ||
               (a == c && a != b) ||
               (b == c && a != b);
    }

public:
    SlotGame(Bank& b) : bank(b) {}

    std::string getName() const override {
        return "Slot Machine";
    }

    void play() override {
        std::cout << "\033[2J\033[H";
        int bet;

        std::cout << "\n=== SLOT MACHINE ===\n";
        bank.print();

        std::cout << "Bet: ";
        std::cin >> bet;

        if (!bank.withdraw(bet)) {
            std::cout << "Not enough Balance\n";
            return;
        }

        system("cls");

        int r1 = 0, r2 = 0, r3 = 0;

        bool stop1 = false;
        bool stop2 = false;
        bool stop3 = false;

        int spins1 = 50 + std::rand() % 10;
        int spins2 = 70 + std::rand() % 10;
        int spins3 = 90 + std::rand() % 10;

        int target1 = (r1 + spins1) % symbols.size();
        int target2 = (r2 + spins2) % symbols.size();
        int target3 = (r3 + spins3) % symbols.size();

        int i = 0;

        while (!stop1 || !stop2 || !stop3) {

            if (!stop1) {
                r1 = (r1 + 1) % symbols.size();
                if (i >= spins1 && r1 == target1) {
                    stop1 = true;
                }
            }

            if (!stop2) {
                r2 = (r2 + 1) % symbols.size();
                if (i >= spins2 && r2 == target2) {
                    stop2 = true;
                }
            }

            if (!stop3) {
                r3 = (r3 + 1) % symbols.size();
                if (i >= spins3 && r3 == target3) {
                    stop3 = true;
                }
            }

            drawReels(r1, r2, r3);

            std::this_thread::sleep_for(
                std::chrono::milliseconds(20 + i * 2)
            );

            i++;
        }

        drawReels(r1, r2, r3);

        std::string a = symbols[r1];
        std::string b = symbols[r2];
        std::string c = symbols[r3];

        bool win3 = (a == b && b == c);
        bool win2 = almostWin(a, b, c);

        if (win3 || win2) {
            for (int i = 0; i < 8; i++) {
                bool on = (i % 2 == 0);

                drawReels(r1, r2, r3, on);

                std::cout << (win3 ? "\033[32mJACKPOT LINE\033[0m"
                                : "\033[33mWIN LINE\033[0m")
                        << std::flush;

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }

        std::cout << "\n";

        if (a == b && b == c) {
            int win = bet * 10;
            bank.deposit(win);
            std::cout << "\033[32mJACKPOT +" << win << "\033[0m\n";
        }
        else if (almostWin(a, b, c)) {
            int win = bet * 3;
            bank.deposit(win);
            std::cout << "\033[32mWin +" << win << "\033[0m\n";
        }
        else {
            std::cout << "\033[31mLose -" << bet << "\033[0m\n";
        }

        bank.print();
    }
};










static Bank bank(100000000);

class Casino {
private:
    std::vector<std::unique_ptr<IGame>> games;

public:
    Casino() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        games.push_back(std::make_unique<Roulette>(bank));
        games.push_back(std::make_unique<DiceGame>(bank));
        games.push_back(std::make_unique<SlotGame>(bank));
    }

    void showMenu() {
        std::cout << "\033[2J\033[H";

        printScreen("Casino");

        bank.print();
        std::cout << "\n";

        std::cout << "0. Exit\n";

        for (size_t i = 0; i < games.size(); i++) {
            std::cout << (i + 1) << ". " << games[i]->getName() << "\n";
        }

        std::cout << "\nChoice: ";
    }

    void run() {
        while (true) {

            if (bank.getBalance() <= 0) {
                std::cout << "\033[31mNot enough Balance\n\033[0m";
                return;
            }

            showMenu();

            int choice;
            std::cin >> choice;

            if (choice == 0) {
                std::cout << "Bye\n";
                return;
            }

            if (choice < 1 || choice > (int)games.size()) {
                std::cout << "\033[31mInvalid Choice\n\033[0m";
                continue;
            }

            int currentGame = choice - 1;

            while (true) {

                games[currentGame]->play();

                if (bank.getBalance() <= 0) {
                    std::cout << "\033[31mNot enough Balance\n\033[0m";
                    return;
                }

                std::cout << "\n";
                std::cout << "\033[36m==============================\n";
                std::cout << "         NEXT STEP            \n";
                std::cout << "==============================\033[0m\n";

                std::cout << "1. Play again\n";
                std::cout << "2. Choose another game\n";
                std::cout << "3. Exit Casino\n";
                std::cout << "\nChoice: ";

                int next;
                std::cin >> next;

                if (next == 1) {
                    continue;
                }
                else if (next == 2) {
                    break;
                }
                else if (next == 3) {
                    std::cout << "Bye\n";
                    return;
                }
                else {
                    std::cout << "\033[31mInvalid Choice\033[0m\n";
                }
            }
        }
    }
};




// Startguthaben
static Casino casino;


void cmd_games(const std::vector<std::string>& args, Terminal& term) {
    (void)term;

    if (args[1] == "casino") {
        casino.run();
    }
}

struct MenuItem {
    std::string label;
    std::function<void()> action;
};

void cmd_bank(const std::vector<std::string>& args, Terminal& term) {
    (void)args;
    (void)term;

    auto clearScreen = []() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    };

    auto getNext = [&]() {
        std::cout << "\n";
        std::cout << currentColor << "Press Enter to Continue ...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

        clearScreen();
    };

    while (true) {
        std::vector<MenuItem> menu = {
            {
                "Show Balance",
                [&]() {
                    bank.print();
                    getNext();
                }
            },
            {
                "Show Transactions",
                [&]() {
                    bank.printHistory();
                    getNext();
                }
            },
            {
                "Deposit",
                [&]() {
                    int amount;
                    std::cout << "Amount: ";
                    std::cin >> amount;

                    bank.deposit(amount);
                    std::cout << "OK\n";

                    getNext();
                }
            },
            {
                "Withdraw",
                [&]() {
                    int amount;
                    std::cout << "Amount: ";
                    std::cin >> amount;

                    if (bank.withdraw(amount)) {
                        std::cout << "OK\n";
                    } else {
                        std::cout << "Not enough Balance\n";
                    }

                    getNext();
                }
            }
        };

        clearScreen();

        printScreen("Bank");

        std::cout << "0. Exit\n";

        for (size_t i = 0; i < menu.size(); i++) {
            std::cout << i + 1 << ". " << menu[i].label << "\n";
        }

        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            clearScreen();
            break;
        }

        if (choice < 0 || choice > (int)menu.size()) {
            std::cout << "Invalid Number\n";
            getNext();
            continue;
        }

        std::cout << "\n";

        menu[choice - 1].action();
    }
}
















class AsciiGraph {
private:
    struct point {
        std::string label;
        double y;
    };

    struct Point {
        double x;
        double y;
    };

    std::vector<Point> points;
    std::vector<std::string> xLabels;

    int width;
    int plotWidth;
    int height;

    int cellWidth = 3;

    std::vector<std::string> grid;

    double minX, maxX;
    double minY, maxY;

    void computeBounds() {
        minX = maxX = points[0].x;
        minY = maxY = points[0].y;

        for (const auto& p : points) {
            minX = std::min(minX, p.x);
            maxX = std::max(maxX, p.x);
            minY = std::min(minY, p.y);
            maxY = std::max(maxY, p.y);
        }

        if (minY == maxY) {
            minY -= 1;
            maxY += 1;
        }

        if (minX == maxX) {
            minX -= 1;
            maxX += 1;
        }
    }

    std::vector<double> computeTicks() const {
        std::vector<double> ticks;

        double range = maxY - minY;
        if (range <= 0) return {minY};

        double rawStep = range / 5.0;

        double mag = std::pow(10, std::floor(std::log10(rawStep)));
        double norm = rawStep / mag;

        double step;

        if (norm < 1.5) step = 1 * mag;
        else if (norm < 3) step = 2 * mag;
        else if (norm < 7) step = 3 * mag;
        else step = 10 * mag;

        double start = std::floor(minY / step) * step;

        for (double v = start; v <= maxY; v += step) {
            ticks.push_back(v);
        }

        return ticks;
    }

    static double computeStep(double minY, double maxY) {
        double range = maxY - minY;
        double rawStep = range / 6.0;

        double mag = std::pow(10, std::floor(std::log10(rawStep)));
        double norm = rawStep / mag;

        if (norm < 1.5) return 1 * mag;
        if (norm < 3)   return 2 * mag;
        if (norm < 7)   return 5 * mag;
        return 10 * mag;
    }

    int mapX(double x) const {
        double t = (x - minX) / (maxX - minX);
        return (int)(t * (width * cellWidth - 1));
    }

    int mapY(double y) const {
        return (int)((1.0 - (y - minY) / (maxY - minY)) * (height - 1));
    }

    int mapTickToRow(double tick) const {
        return (int)((maxY - tick) / (maxY - minY) * (height - 1));
    }

    void initGrid() {
        grid.assign(height, std::string(width * cellWidth, ' '));
    }

    void setPoint(int x, int y, char c) {
        if (x < 0 || x >= width * cellWidth || y < 0 || y >= height) return;

        grid[y][x] = c;
    }

    void drawLine(int x0, int y0, int x1, int y1) {
        int dx = std::abs(x1 - x0);
        int dy = std::abs(y1 - y0);

        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;

        int err = dx - dy;

        while (true) {
            if (x0 == x1 && y0 == y1) break;
            
            setPoint(x0, y0, '*');

            int err2 = err;

            if (err2 > -dy) {
                err -= dy;
                x0 += sx;
            } else if (err2 < dx) {
                err += dx;
                y0 += sy;
            }
        }
    }

public:
    AsciiGraph(int h = 20)
        : height(h) {}

    void addPoints(std::vector<point> allPoints) {
        for (size_t i = 0; i < allPoints.size(); i++) {
            points.push_back({(double)i, allPoints[i].y});
            xLabels.push_back(allPoints[i].label);
        }
    }

    void setXLabels(const std::vector<std::string>& labels) {
        xLabels = labels;
    }

    void prepare() {
        computeBounds();

        width = (int)points.size();
        plotWidth = width * cellWidth;
        if (width < 2) width = 2;

        initGrid();
    }

    void drawAxes() {
        int zeroY = mapY(0);
        int zeroX = mapX(0);

        for (int x = 0; x < width * cellWidth; x++) {
            if (zeroY >= 0 && zeroY < height) {
                grid[zeroY][x] = '-';
            }
        }

        if (zeroX >= 0 && zeroX < width &&
            zeroY >= 0 && zeroY < height) {
            grid[zeroY][zeroX * cellWidth + 1] = '+';
        }
    }

    void plot() {
        grid.assign(height, std::string(plotWidth, ' '));

        for (size_t i = 0; i + 1 < points.size(); i++) {
            int x0 = mapX(points[i].x);
            int y0 = mapY(points[i].y);

            int x1 = mapX(points[i + 1].x);
            int y1 = mapY(points[i + 1].y);

            drawLine(x0, y0, x1, y1);
        }
    }

    void print() const {
        std::string spacing = "       ";
        double step = computeStep(minY, maxY);

        int tickSpacing = height / 6;
        if (tickSpacing < 1) tickSpacing = 1;

        for (int y = 0; y < height; y++) {

            bool isTick = (y % tickSpacing == 0);

            if (isTick) {
                double value = maxY - (double)y / (height - 1) * (maxY - minY);

                double rounded = std::round(value / step) * step;

                std::cout << std::setw(6)
                        << std::fixed << std::setprecision(2)
                        << rounded << " |";
            } else {
                std::cout << spacing << "|";
            }

            std::cout << grid[y] << "\n";
        }

        std::cout << spacing << "+";

        for (int i = 0; i < width * cellWidth; i++) {
            std::cout << "-";
        }

        std::cout << "\n" << spacing << " ";

        for (int i = 0; i < width; i++) {
            std::string label;

            if (i < (int)xLabels.size()) {
                label = xLabels[i];
            } else {
                label = std::to_string(i);
            }

            int padding = cellWidth - (int)label.size();
            int left = padding / 2;

            for (int j = 0; j < left; j++) std::cout << " ";
            std::cout << label;
            for (int j = 0; j < padding - left; j++) std::cout << " ";
        }

        std::cout << "\n";
    }
};




void cmd_graph(const std::vector<std::string>& args, Terminal& term) {
    (void) args; (void) term;
    
    AsciiGraph g(16);

    g.addPoints( 
        {
            {"A", 1},
            {"B", 3},
            {"C", 2},
            {"D", 5},
            {"E", 4},
            {"F", 6},
            {"G", 3},
            {"H", 2},
            {"I", 4},
            {"J", 5},
            {"K", 6}
        }
    );

    g.prepare();
    g.drawAxes();
    g.plot();
    g.print();
}








struct Permissions {
    bool read = false;
    bool write = false;
    bool exec = false;
    bool sudo = false;
};

struct Command {
    std::string name;
    std::function<std::string(const std::vector<std::string>&, const std::string&)> func;
    Permissions perms;
};

class CommandManager {
public:
    CommandManager(Terminal& term) : terminal(term) {
        initCommands();
    }

    void registerAll() {
        for (const auto& cmd : commands) {
            terminal.registerCommand(
                cmd.name,
                cmd.func,
                cmd.perms.read,
                cmd.perms.write,
                cmd.perms.exec,
                cmd.perms.sudo
            );
        }
    }

private:
    Terminal& terminal;
    std::vector<Command> commands;

    void initCommands() {

        commands = {

            {"help", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_help(args);
                return "";
            }, 
            {}},

            {"clear", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_clear(args);
                return "";
            },
            {}},

            {"echo", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_echo(args);
                return "";
            }, 
            {}},

            {"ls", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_ls(args);
                return "";
            }, 
            {}},

            {"exit", [this](const auto& args, const std::string& input){
                (void)args; (void)input;
                std::cout << currentColor << "Stopping Terminal...\n";
                terminal.stop();
                return "";
            }, 
            {}},

            {"logout", [this](const auto& args, const std::string& input){
                (void)args; (void)input;
                while (!terminal.loginPrompt()) {}
                terminal.run();
                return "";
            }, 
            {}},

            {"ping", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_ping(args);
                return "";
            }, 
            {false, false, true, false}},

            {"dir", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_dir(args);
                return "";
            }, 
            {true}},

            {"cd", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_cd(args);
                return "";
            }, 
            {true}},

            {"mkdir", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_mkdir(args);
                return "";
            }, 
            {false, true}},

            {"rm", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_rm(args);
                return "";
            }, 
            {true}},

            {"touch", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_touch(args);
                return "";
            }, 
            {true, true}},

            {"vim", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_vim(args);
                return "";
            }, 
            {true, true}},

            {"apt", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_apt_install(args);
                return "";
            }, 
            {true, true, false, true}},

            {"color", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_color(args);
                return "";
            }, 
            {}},

            {"passwd", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_passwd(args, terminal);
                return "";
            }, 
            {true, true, true, true}},

            {"perm", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_perm(args, terminal);
                return "";
            }, 
            {true, true, true, true}},

            {"user", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_user(args, terminal);
                return "";
            }, 
            {true, true, true, true}},

            {"print", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_print(args, terminal);
                return "";
            }, 
            {true, true}},

            {"win", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_win(args, terminal);
                return "";
            }, 
            {}},

            {"date", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_date(args, terminal);
                return "";
            }, 
            {}},

            {"sys", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_sys(args, terminal);
                return "";
            }, 
            {}},

            {"games", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_games(args, terminal);
                return "";
            }, 
            {}},

            {"bank", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_bank(args, terminal);
                return "";
            }, 
            {}},

            {"graph", [this](const auto& args, const std::string& input){
                (void)input;
                cmd_graph(args, terminal);
                return "";
            }, 
            {}}
        };
    }
};


// ==========================
// main
// ==========================
int main() {
    Terminal terminal;

    CommandManager manager(terminal);
    manager.registerAll();

    // normale Befehle
    /*terminal.registerCommand("help", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_help(args);
            return "";
        }, false, false, false
    );

    terminal.registerCommand("clear", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_clear(args);
            return "";
        }, false, false, false
    );

    terminal.registerCommand("echo", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_echo(args);
            return "";
        }, false, false, false
    );

    terminal.registerCommand("ls", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_ls(args);
            return "";
        }, false, false, false
    );

    terminal.registerCommand("exit",
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input; (void)args; (void)input;
            std::cout << currentColor + "Stopping Terminal...\n";
            terminal.stop();
            return "";
        }
    );

    terminal.registerCommand("logout", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input; (void)args;
            while (!terminal.loginPrompt()) {}
            terminal.run();
            return "";
        }
    );

    terminal.registerCommand("ping", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_ping(args);
            return "";
        }, false, false, true
    );

    terminal.registerCommand("dir", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_dir(args);
            return "";
        }, true
    );

    terminal.registerCommand("cd", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_cd(args);
            return "";
        }, true, false, false
    );

    terminal.registerCommand("mkdir", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_mkdir(args);
            return "";
        }, false, true
    );

    terminal.registerCommand("rm", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_rm(args);
            return "";
        }, true
    );

    terminal.registerCommand("touch", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_touch(args);
            return "";
        }, true, true
    );

    terminal.registerCommand("vim", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_vim(args);
            return "";
        }, true, true
    );

    terminal.registerCommand("apt", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_apt_install(args);
            return "";
        }, true, true, false, true
    );

    //color changer
    terminal.registerCommand("color", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_color(args);
            return "";
        }
    );

    terminal.registerCommand("passwd", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_passwd(args, terminal);
            return "";
        }, true, true, true, true
    );

    // permission management commands (sudo required)
    terminal.registerCommand("perm", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_perm(args, terminal);
            return "";
        }, true, true, true, true
    );

    // user management commands (sudo required)
    terminal.registerCommand("user", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_user(args, terminal);
            return "";
        }, 
        true, true, true, true
    );
    // Read Write Execute Sudo

    terminal.registerCommand("print", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_print(args, terminal);
            return "";
        }, 
        true, true
    );

    terminal.registerCommand("win", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_win(args, terminal);
            return "";
        }
    );

    terminal.registerCommand("date", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_date(args, terminal);
            return "";
        }
    );

    terminal.registerCommand("sys", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_sys(args, terminal);
            return "";
        }
    );

    terminal.registerCommand("games", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_games(args, terminal);
            return "";
        }
    );

    terminal.registerCommand("bank", 
        [&](const std::vector<std::string>& args, const std::string& input) -> std::string {
            (void)input;
            cmd_bank(args, terminal);
            return "";
        }
    );*/

    // === Login beim Start ===
    while (!terminal.loginPrompt()) {}

    // Terminal starten
    terminal.run();

    return 0;
}