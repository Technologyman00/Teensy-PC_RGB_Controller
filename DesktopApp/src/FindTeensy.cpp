#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

using namespace std;

int main(){

    const regex regexp("16C0"); 
    smatch m;
    const string idResults = exec("wmic path Win32_SerialPort get PNPDeviceID");
    regex_search(idResults, m, regexp);

    int countOfNewLine = 0;
    for(int i=0; i < m.position(0); i++){
        if(idResults.c_str()[i] == '\n'){
            countOfNewLine++;
        }
    }

    const string portResults = exec("wmic path Win32_SerialPort get DeviceID");
    string port;
    int countOfNewLine2 = 0;
    for(int i=0; i < portResults.length(); i++){ 
        if(countOfNewLine2 != countOfNewLine){
            if(portResults.c_str()[i] == '\n'){
                countOfNewLine2++;
            }
        }
        else{
            for(int c=i; c < portResults.length(); c++){
                if(portResults.c_str()[c] == ' '){
                    port = portResults.substr(i, c-i);
                    break;
                }
            }
            break;
        }
    }

    cout << port <<endl;
    wcout << port.length() <<endl;
    

    //LPCSTR port = "\\\\.\\COM4";
    //HANDLE serialCommand = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    //wcout << GetFileAttributesA(port) <<endl;

    //CloseHandle(serialCommand);

    system("pause");
    return 0;
}