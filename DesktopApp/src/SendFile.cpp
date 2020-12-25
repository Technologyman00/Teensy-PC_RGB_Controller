#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>

using namespace std;
int main(int argc, char** argv){
    if(argc > 1){
        LPCSTR port = "\\\\.\\COM4";
        HANDLE serialCommand = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        wcout << "Starting Sending..." <<endl;
        wcout << argv[1] <<endl;

        //open file
        std::ifstream infile(argv[1]);

        //get length of file
        infile.seekg(0, std::ios::end);
        size_t length = infile.tellg();

        infile.seekg(0, std::ios::beg);

        // don't overflow the buffer!
        //if (length > sizeof (buffer))
        //{
        //    length = sizeof (buffer);
        //}

        //read file
        //infile.read(buffer, length);
        
        //WriteFile(serialCommand, "w Frames4.txt", 13, 0, 0);
        //Sleep(2000);
        //Write File Byte Length in Bytes
        //Sleep(1000);
        // Send File Crap in Bytes
        CloseHandle(serialCommand);
        

    }
    else{
       wcout << "No File to Send." <<endl; 
    }
    system("pause");
    return 0;
}