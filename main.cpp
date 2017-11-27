#include <iostream>
#include "Customer.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <regex>
#include <list>

using namespace std;

extern "C" {
#include "foo.h" //a C header, so wrap it in extern "C"
}
std::list<HWND> list;
HWND current;
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
        if (hWnd != current) {
            cout << "match!" << std::endl;
            current=hWnd;
            return FALSE;
        }
        return TRUE;
    }
    return TRUE;
}

int main() {
    current = GetForegroundWindow();
    std::regex txt_regex(".*(CLion|IntelliJ|cmd|Total).*");
    EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM >(&txt_regex));
    EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM >(&txt_regex));
    foo();
    return 0;
}
