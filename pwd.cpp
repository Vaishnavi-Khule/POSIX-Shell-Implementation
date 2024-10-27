#include "headers.h"
char* pwd()
{
    char* pwd1 = new char[100]; 
    if (getcwd(pwd1, 100) == nullptr) {
        perror("getcwd");
        delete[] pwd1; 
        return nullptr;
    }
return pwd1;
}
