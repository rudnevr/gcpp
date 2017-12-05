#include <iostream>
#include "Customer.h"
#include "PState.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <regex>
#include <list>

using namespace std;


extern "C" {
#include "foo.h" //a C header, so wrap it in extern "C"
}


HWND current;

HHOOK KeyboardHook;

BOOL shift = FALSE;
BOOL ctrl = FALSE;
BOOL alt = FALSE;
BOOL tab = FALSE;
BOOL caps = FALSE;

string mapCodeToText(int code) {
    if (code == VK_F12) { return "IntelliJ"; }
    if (code == VK_F13) { return "Firefox"; }
    if (code == VK_F14) { return "Chrome"; }
    if (code == VK_F4) { return "cmd"; }
    if (code == VK_F7) { return "MINGW"; }
    if (code == VK_F6) { return "Sky"; }
    if (code == VK_F5) { return "PyCharm"; }
    printf("ret null");
    return string("");
}

BOOL CALLBACK enumWindowsProc(
        HWND hWnd,
        LPARAM lParam
) {
    int length = ::GetWindowTextLength(hWnd);
    if (0 == length) return TRUE;
    regex *regex1 = reinterpret_cast<std::regex *>(lParam);
    char cWindow[length];
    GetWindowTextA(hWnd, cWindow, length);
//    printf("lparam %s\r\n", regex1);
//    printf("cWindows %s\r\n", cWindow);
    const basic_string<char> &sout = string(cWindow);
    if (std::regex_match(sout, *regex1)) {
        cout << sout << std::endl;

//        if (hWnd != current) {
            cout << "match!" << std::endl;
//            current = hWnd;
            SetForegroundWindow(hWnd);
//            return FALSE;
//        }
        return TRUE;
    }
    return TRUE;
}

void press(int code, BOOL up) {
    INPUT input;
    WORD vkey = code;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = vkey;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
    if (up)
        input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void pressCtrlCode(int code) {
    press(VK_LCONTROL, FALSE);
    press(code, TRUE);
    press(VK_LCONTROL, TRUE);
}

LRESULT CALLBACK HookProcedure2(int nCode, WPARAM wParam, LPARAM lParam) {
    KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *) lParam;
    if (nCode == HC_ACTION) {
        printf("code %lu\n", p->vkCode);
        string te = mapCodeToText(p->vkCode);
        if (!te.empty() && GetAsyncKeyState(VK_LSHIFT)) {
            press(VK_LSHIFT, TRUE);
            printf("%s mapped to %lu\n", te, p->vkCode);
            std::regex txt_regex(te);
            EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM >(&txt_regex));
            return -1;
        } else {
            if (p->vkCode == VK_F11) {
                press(VK_LSHIFT, TRUE);
                press(VK_LWIN, TRUE);
                return -1;
            }
            if (p->vkCode == VK_F8) {
                press(VK_LSHIFT, TRUE);
                press(VK_LMENU, FALSE);
                press(VK_TAB, TRUE);
                pressCtrlCode('T');
                return -1;
            }
            if (p->vkCode == VK_F2) {
                press(VK_LSHIFT, TRUE);
                UnhookWindowsHookEx(KeyboardHook);
                return -1;
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

//
//void createState() {
//    keys = Keys(GetAsyncKeyState(VK_CAPITAL), GetAsyncKeyState(VK_SHIFT), GetAsyncKeyState(VK_MENU),
//                GetAsyncKeyState(VK_SHIFT), GetAsyncKeyState(VK_CONTROL), GetAsyncKeyState(VK_LWIN));
//}


int main() {
    cout << "start" << endl;
    current = GetForegroundWindow();
    KeyboardHook = SetWindowsHookEx(
            WH_KEYBOARD_LL,
            HookProcedure2,
            GetModuleHandle(NULL),
            0
    );
    MSG Msg;
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        printf("in mess\n");
        DispatchMessage(&Msg);
    }
    printf("unhook\n");
    UnhookWindowsHookEx(KeyboardHook);
//    EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM >(&txt_regex));
//    EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM >(&txt_regex));
    return 0;
}
