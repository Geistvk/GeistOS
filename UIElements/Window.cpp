#include "Window.h"
#include <windowsx.h>
#include <string>
#include <cmath>
#include <thread>
#include <sstream>

static Window* g_win = nullptr;

// Definition der globalen Variable
std::string m_activeLeftPanelId;

/* ---------------- PANEL WINDOW PROC ---------------- */
LRESULT CALLBACK PanelProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_COMMAND) {
        SendMessage(GetParent(h), WM_COMMAND, w, l);
        return 0;
    }
    return DefWindowProc(h, m, w, l);
}

/* ---------------- MAIN WINDOW PROC ---------------- */
LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_COMMAND && g_win) {
        g_win->HandleCommand(w);
        return 0;
    }
    if (m == WM_CLOSE) DestroyWindow(h);
    if (m == WM_DESTROY) PostQuitMessage(0);
    return DefWindowProc(h, m, w, l);
}

/* ---------------- WINDOW ---------------- */
Window::Window(const char* t, int w, int h, const char* cls) {
    g_win = this;
    m_inst = GetModuleHandle(nullptr);

    WNDCLASS wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = m_inst;
    wc.lpszClassName = cls;
    RegisterClass(&wc);

    WNDCLASS pc{};
    pc.lpfnWndProc = PanelProc;
    pc.hInstance = m_inst;
    pc.lpszClassName = "UIPanel";
    RegisterClass(&pc);

    RECT r{0,0,w,h};
    AdjustWindowRect(&r, WS_CAPTION | WS_SYSMENU, FALSE);

    m_hWnd = CreateWindow(cls, t,
        WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        r.right - r.left, r.bottom - r.top,
        nullptr, nullptr, m_inst, nullptr);

    GetClientRect(m_hWnd, &m_freeArea);
}

Window::~Window() { for (auto e : m_elements) delete e; }

bool Window::ProcessMessages() {
    MSG msg{};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

/* ---------------- COMMAND ---------------- */
int Window::GenerateId() { return m_nextId++; }
void Window::RegisterButton(int id, std::function<void()> cb) { m_callbacks[id] = cb; }
void Window::HandleCommand(WPARAM wParam) {
    if (HIWORD(wParam) != BN_CLICKED) return;
    int id = LOWORD(wParam);
    auto it = m_callbacks.find(id);
    if (it != m_callbacks.end()) it->second();
}

/* ---------------- LAYOUT ---------------- */
RECT Window::GetFreeArea() const { return m_freeArea; }
void Window::SetFreeArea(const RECT& r) { m_freeArea = r; }

Text::Text(HWND p, const char* t, int x, int y, int w, int h) {
    hWnd = CreateWindow("STATIC", t, WS_CHILD | WS_VISIBLE, x, y, w, h, p, nullptr, GetModuleHandle(0), nullptr);
}

Button::Button(Window& win, HWND p, int x, int y, int w, int h, const char* t, std::function<void()> cb) {
    int id = win.GenerateId();
    win.RegisterButton(id, cb);
    hWnd = CreateWindow("BUTTON", t, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y, w, h, p, (HMENU)(intptr_t)id, GetModuleHandle(0), nullptr);
}

Panel::Panel(Window& win, Dock d, int size, Orientation o, const RECT* fixedRect) {
    orientation = o;
    RECT r = fixedRect ? *fixedRect : win.GetFreeArea();
    rect = r;

    if (!fixedRect && d != Dock::None) {
        if (d == Dock::Left) { rect.right = rect.left + size; r.left += size; }
        else if (d == Dock::Top) { rect.bottom = rect.top + size; r.top += size; }
        win.SetFreeArea(r);
    }

    hWnd = CreateWindow("UIPanel", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
        win.GetHWND(), nullptr, GetModuleHandle(0), nullptr);
}

/* ---------------- VISIBILITY ---------------- */
void Window::ShowLeftPanel(const std::string& id) {
    if (!m_activeLeftPanelId.empty()) {
        auto oldIt = m_leftPanels.find(m_activeLeftPanelId);
        if (oldIt != m_leftPanels.end()) { ShowWindow(oldIt->second, SW_HIDE); UpdateWindow(oldIt->second); }
    }
    auto newIt = m_leftPanels.find(id);
    if (newIt == m_leftPanels.end()) return;
    ShowWindow(newIt->second, SW_SHOW); UpdateWindow(newIt->second);
    m_activeLeftPanelId = id;
    auto defIt = m_leftToDefaultMain.find(id);
    if (defIt != m_leftToDefaultMain.end()) ShowMainPanel(defIt->second);
}

void Window::ShowMainPanel(const std::string& id) {
    for (auto& p : m_mainPanels) ShowWindow(p.second, SW_HIDE);
    auto it = m_mainPanels.find(id);
    if (it != m_mainPanels.end()) ShowWindow(it->second, SW_SHOW);
}

/* ---------------- LOAD CONFIG ---------------- */
void Window::LoadFromConfig(const WindowConfig& cfg) {
    const int spacing = 8;
    for (auto& p : cfg.panels) {
        const RECT* fixed = nullptr;
        if (p.dock == Dock::Left && m_leftDockUsed) fixed = &m_leftRect;

        Panel* panel = new Panel(*this, p.dock, p.size, p.orientation, fixed);
        m_elements.push_back(panel);
        ShowWindow(panel->hWnd, (p.dock == Dock::Top) ? SW_SHOW : SW_HIDE);

        if (p.dock == Dock::Left) {
            if (!m_leftDockUsed) { m_leftDockUsed = true; m_leftRect = panel->rect; }
            m_leftPanels[p.id] = panel->hWnd;
            if (!p.defaultMainPanelId.empty()) m_leftToDefaultMain[p.id] = p.defaultMainPanelId;
        } else if (p.dock == Dock::None) { m_mainPanels[p.id] = panel->hWnd; }

        int x = 10, y = 10;
        for (auto item : p.items) {
            if (auto t = dynamic_cast<TextConfig*>(item)) { m_elements.push_back(new Text(panel->hWnd, t->text.c_str(), x, y, t->w, t->h));
                (p.orientation == Orientation::Vertical) ? y += t->h + spacing : x += t->w + spacing; }
            else if (auto b = dynamic_cast<ButtonConfig*>(item)) { m_elements.push_back(new Button(*this, panel->hWnd, x, y, b->w, b->h, b->text.c_str(), b->onClick));
                (p.orientation == Orientation::Vertical) ? y += b->h + spacing : x += b->w + spacing; }
            else if (auto tbl = dynamic_cast<TableConfig*>(item)) { m_elements.push_back(new Table(panel->hWnd, x, y, tbl->w, tbl->h, tbl->columns));
                y += tbl->h + spacing; }
            else if (auto g = dynamic_cast<GraphConfig*>(item)) { m_elements.push_back(new Graph(panel->hWnd, x, y, g->w, g->h, g->labels));
                y += g->h + spacing; }
        }
    }
}

/* ---------------- TABLE ---------------- */
Table::Table(HWND parent, int x, int y, int w, int h, const std::vector<std::string>& columns) {
    hListView = CreateWindow(WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS,
        x, y, w, h, parent, nullptr, GetModuleHandle(0), nullptr);
    hWnd = hListView;

    LVCOLUMN col{};
    col.mask = LVCF_TEXT | LVCF_WIDTH;
    for (size_t i = 0; i < columns.size(); i++) {
        col.cx = 100;
        col.pszText = (LPSTR)columns[i].c_str();
        ListView_InsertColumn(hListView, (int)i, &col);
    }
    ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void Table::AddRow(const std::vector<std::string>& row) {
    LVITEM item{};
    item.mask = LVIF_TEXT;
    item.iItem = ListView_GetItemCount(hListView);
    for (size_t i = 0; i < row.size(); i++) {
        item.iSubItem = (int)i;
        item.pszText = (LPSTR)row[i].c_str();
        if (i == 0) ListView_InsertItem(hListView, &item);
        else ListView_SetItem(hListView, &item);
    }
}

void Table::Clear() { ListView_DeleteAllItems(hListView); }

/* ---------------- GRAPH ---------------- */
Graph::Graph(HWND parent, int x, int y, int w, int h, const std::vector<std::string>& lbls) {
    hStatic = CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT, x, y, w, h, parent, nullptr, GetModuleHandle(0), nullptr);
    hWnd = hStatic;
    labels = lbls;
}

void Graph::AddValue(float v) {
    values.push_back(v);
    if (values.size() > labels.size()) values.erase(values.begin());

    std::ostringstream ss;
    for (size_t i = 0; i < values.size(); i++) {
        std::string lbl = (i < labels.size()) ? labels[i] : "";
        ss << lbl << " ";
        int len = (int)(values[i] / 100.0f * 20);
        ss << std::string(len, '|') << "\n";
    }
    SetWindowText(hStatic, ss.str().c_str());
}

void Graph::Clear() { values.clear(); SetWindowText(hStatic, ""); }
