#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include <commctrl.h>

enum class Dock { None, Left, Top };
enum class Orientation { Vertical, Horizontal };

// globale Variable für aktives Left Panel
extern std::string m_activeLeftPanelId;

struct UIItem { virtual ~UIItem() = default; };

struct TextConfig : UIItem {
    std::string text;
    int w = 150, h = 25;
    TextConfig(const std::string& t) : text(t) {}
};

struct ButtonConfig : UIItem {
    std::string text;
    int w = 120, h = 30;
    std::function<void()> onClick;
    ButtonConfig(const std::string& t, std::function<void()> cb) : text(t), onClick(cb) {}
};

struct TableConfig : UIItem {
    std::vector<std::string> columns;
    int w = 300, h = 150;
    TableConfig(const std::vector<std::string>& cols, int width = 300, int height = 150)
        : columns(cols), w(width), h(height) {}
};

struct GraphConfig : UIItem {
    std::vector<std::string> labels; // jeder Balken hat einen Titel
    int w = 300, h = 150;
    GraphConfig(int width = 300, int height = 150, const std::vector<std::string>& lbls = {})
        : labels(lbls), w(width), h(height) {}
};

struct PanelConfig {
    Dock dock = Dock::None;
    int size = 0;
    Orientation orientation;
    std::string id;
    std::vector<UIItem*> items;
    std::string defaultMainPanelId;
};

struct WindowConfig { std::vector<PanelConfig> panels; };

struct GUIElement { HWND hWnd{}; virtual ~GUIElement() = default; };

class Window {
public:
    Window(const char*, int, int, const char*);
    ~Window();

    bool ProcessMessages();
    HWND GetHWND() const { return m_hWnd; }

    int GenerateId();
    void RegisterButton(int, std::function<void()>);
    void HandleCommand(WPARAM);

    RECT GetFreeArea() const;
    void SetFreeArea(const RECT&);

    void ShowLeftPanel(const std::string&);
    void ShowMainPanel(const std::string&);

    void LoadFromConfig(const WindowConfig&);
    std::vector<GUIElement*> m_elements;

private:
    HWND m_hWnd{};
    HINSTANCE m_inst{};
    int m_nextId = 1;

    RECT m_freeArea{};
    RECT m_leftRect{};
    bool m_leftDockUsed = false;

    std::unordered_map<int, std::function<void()>> m_callbacks;
    std::unordered_map<std::string, HWND> m_leftPanels;
    std::unordered_map<std::string, HWND> m_mainPanels;
    std::unordered_map<std::string, std::string> m_leftToDefaultMain;
};

struct Text : GUIElement { Text(HWND, const char*, int, int, int, int); };
struct Button : GUIElement { Button(Window&, HWND, int, int, int, int, const char*, std::function<void()>); };
struct Panel : GUIElement { RECT rect{}; Orientation orientation; Panel(Window&, Dock, int, Orientation, const RECT*); };

struct Table : GUIElement {
    HWND hListView{};
    Table(HWND parent, int x, int y, int w, int h, const std::vector<std::string>& columns);
    void AddRow(const std::vector<std::string>& row);
    void Clear();
};

struct Graph : GUIElement {
    std::vector<float> values;
    std::vector<std::string> labels; // Titel für jeden Balken
    HWND hStatic{};
    Graph(HWND parent, int x, int y, int w, int h, const std::vector<std::string>& lbls = {});
    void AddValue(float v); // fügt neuen Wert hinzu und zeigt Balken
    void Clear();
};
