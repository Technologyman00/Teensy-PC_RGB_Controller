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

string TeensyPort(){
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
    return port;
}

char fileName[255];
char lengthBytes[4];
char ReadBack[40];
char DataPos[1];
char SendData[1];

int pos = 0;

void getFileName(char* filePath){
    int length = strlen(filePath);
    int slashPos = length;
    for(int i=length; i > 0; i--){
        if(filePath[i] == '\\'){
            slashPos = i;
            break;
        }
    }

    for(int i=0; i < (length-(slashPos+1)); i++){
        fileName[i] = filePath[i+slashPos+1];
    }
}

int main(int argc, char** argv){
    if(argc > 1){
        string portString = "\\\\.\\" + TeensyPort();
        LPCSTR port = portString.c_str();
        HANDLE serialCommand = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        wcout << "Starting Sending..." <<endl;
        wcout << argv[1] <<endl;

        //open file
        ifstream infile;

        infile.open(argv[1], ios::in|ios::binary|ios::ate );

        int length = infile.tellg();
        infile.seekg(0, ios::beg);

        // Convert Length int to Bytes to be sent
        lengthBytes[0] = (length >> 24) & 0xFF;
        lengthBytes[1] = (length >> 16) & 0xFF;
        lengthBytes[2] = (length >> 8) & 0xFF;
        lengthBytes[3] = length & 0xFF;

        getFileName((char*) argv[1]);
        string Command = "W " + (string) fileName;

        WriteFile(serialCommand, Command.c_str(), Command.length(), NULL, NULL);

        Sleep(2000);

        WriteFile(serialCommand, (char*) lengthBytes, 4, NULL, NULL);

        Sleep(1000);

        wcout<< length <<endl;

        for(int i=0; i < length; i++){
            infile.read(SendData, 1);
            WriteFile(serialCommand, SendData, 1, NULL, NULL);
            Sleep(0.5);
            wcout << i <<endl;
        }
        
        // Send File Crap in Bytes
        CloseHandle(serialCommand);
    }
    else{
       wcout << "No File to Send." <<endl; 
    }
    system("pause");
    return 0;
}