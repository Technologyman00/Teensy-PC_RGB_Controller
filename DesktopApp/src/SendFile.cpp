#include <iostream>
#include <windows.h>

using namespace std;
int main(){
    LPCSTR wide_string = "\\\\.\\COM4";
    HANDLE serialCommand = CreateFile(wide_string, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    wcout << "Starting Sending..." <<endl;
    WriteFile(serialCommand, "p Frames4.txt", 13, 0, 0);
    CloseHandle(serialCommand);
}