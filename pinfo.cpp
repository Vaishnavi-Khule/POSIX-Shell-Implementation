#include "headers.h"

  
bool isPidValid(int pid) {
  
    return (kill(pid, 0) == 0);
}

void pInfo(int pid) {
     if (!isPidValid(pid)) {
        cerr << " Process with given pid does not exist." << endl;
        return;
    }
    string processStatus;
    long processmemoryUsage;
    string processexecutablePath;
    char processstate;
    stringstream statusFilePath;
    statusFilePath << "/proc/" << pid << "/status";

    ifstream statusFile(statusFilePath.str());
    if (statusFile) {
        string line;
        while (getline(statusFile, line)) {
            istringstream lineStream(line);
            string key;
            lineStream >> key;
            if (key == "State:") {
                 
                lineStream >> processstate;
              
            } else if (key == "VmSize:") {
                lineStream >> processmemoryUsage;
            }
        }
    }

    
    stringstream LinkPath;
    LinkPath << "/proc/" << pid << "/exe";

    char PathBuffer[1024];
    ssize_t len = readlink(LinkPath.str().c_str(), PathBuffer, sizeof(PathBuffer) - 1);
    if (len != -1) {
        PathBuffer[len] = '\0';
        processexecutablePath = PathBuffer;
    }

    cout<< "pid -- " << pid << endl;
    cout << "Process Status -- {" << processstate << "}" << endl;
    cout << "memory -- " << processmemoryUsage << " {Virtual Memory}" << endl;
    cout << "Executable Path -- " << processexecutablePath << endl;
}