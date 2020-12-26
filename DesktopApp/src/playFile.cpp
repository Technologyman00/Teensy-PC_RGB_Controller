#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>

using namespace std;

char fileName[255];
char commandToSend[255];

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
        LPCSTR port = "\\\\.\\COM4";
        HANDLE serialCommand = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        wcout << "Starting Sending..." <<endl;

        //wcout << argv[1] <<endl;

        getFileName((char*) argv[1]);

        //wcout << fileName <<endl;

        string Command = "p " + (string) fileName;

        WriteFile(serialCommand, Command.c_str(), Command.length(), 0, 0);

        wcout << "Finished Sending..." <<endl;

        CloseHandle(serialCommand);
    }
    else{
       wcout << "No File to Send." <<endl; 
    }
    system("pause");
    return 0;
}