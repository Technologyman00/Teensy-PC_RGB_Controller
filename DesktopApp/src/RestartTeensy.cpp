#include <iostream>
#include <windows.h>

using namespace std;
int main(){
    LPCSTR port = "\\\\.\\COM4";
    HANDLE serialCommand = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    wcout << "Starting Sending..." <<endl;
    WriteFile(serialCommand, "r", 1, 0, 0);
    wcout << "Finished Sending..." <<endl;
    CloseHandle(serialCommand);
}