#include <iostream>
#include "Customer.h"
#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

extern "C" {
#include "foo.h" //a C header, so wrap it in extern "C"
}

BOOL CALLBACK enumWindowsProc(
        HWND hWnd,
        LPARAM lParam
) {
//    if( !::IsIconic( hWnd ) ) {
//        return TRUE;
//    }

    int length = ::GetWindowTextLength(hWnd);
    if (0 == length) return TRUE;
    LPTSTR lptstr = (LPTSTR) lParam;
    char cWindow[length];
//    HWND wnd = GetForegroundWindow();
    GetWindowTextA(hWnd, cWindow, length);
//    printf("lparam %s\r\n", lptstr);
//    printf("cWindows %s\r\n", cWindow);
    const basic_string<char> &sout = string(cWindow);
    if (sout.find(lptstr) != string::npos) {
        cout << sout << std::endl;
        return FALSE;
    }
    return TRUE;
}

int main() {
    BOOL enumeratingWindowsSucceeded = ::EnumWindows(enumWindowsProc, (LPARAM) (LPTSTR) "CLion");
    foo();
    return 0;
}
