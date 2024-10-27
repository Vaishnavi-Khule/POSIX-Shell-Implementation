#include "headers.h"

string Username() {
    struct passwd *pwd = getpwuid(getuid());
    if (pwd) {
        return pwd->pw_name;
    }
    return "user";
}
string SystemName() {
    struct utsname unameData;
    if (uname(&unameData) == 0) {
        return unameData.nodename;
    }
    return "system";
}

string Currentdirectory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        return cwd;
    }
    return "~";
} 

void prompt() {
    string prompt;
    string username = Username();
    string systemName = SystemName();
    string curr_dir=Currentdirectory();
  /*   prevwd=Currentdirectory();
    curretwd=Currentdirectory(); */
    string homeDirectory = getenv("HOME");
    if (curr_dir == homeDirectory) {
        curr_dir= "~";
    } else if (curr_dir.find(homeDirectory) == 0) {
        curr_dir.replace(0, homeDirectory.length(), "~");
    }

    cout << prompt << username << "@" << systemName << ":"<<Currentdirectory();
}






        
 