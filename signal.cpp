   #include "headers.h"
   struct Job {
    pid_t pid;      
    string cmd; 
    bool foreground;
};
vector<Job> jobs;
void changetoback() {
    for (Job &job : jobs) {
        if (job.foreground) {
            job.foreground = false;
            cout << job.pid << endl;
            return;
        }
    }
cout << "no foreground job is there" << endl;
}
void handleCtrlZ(int signal) {
    changetoback();
}

bool inForegroundProcess = false; 

void handleCtrlC(int signal) {
    if (inForegroundProcess) {
        
        for (const Job &job : jobs) {
            if (job.foreground) {
                if (kill(-job.pid, SIGINT) == -1) {
                    perror("kill");
                }
            }
        }
    } else {
      cout << endl;
             prompt();
       cout.flush();
    }
}




/* 
void handleCtrlC(int signal) {
    for (const Job &job : jobs) {
        if (job.foreground) {
          if (kill(-job.pid, SIGINT) == -1) {
                perror("kill");
            }
              cout.flush();
            return;
        }
    }
   
} */





