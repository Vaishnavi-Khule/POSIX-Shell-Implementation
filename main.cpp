#include "headers.h"
void storehistory1(string History);
//vector<string>History;
//bool shouldExit = false;

/* void handleCtrlD(int signal) {
    if (signal == EOF) {
        // Handle Ctrl-D (EOF)
        cout << "Logging out of your shell..." << endl;
        shouldExit = true;
    }
} */
void executepipecommand(vector<string>& args) {
    pid_t pid = fork();
    if (pid == 0) {
        vector<char*> c_args;
        for (const auto& arg : args) {
            c_args.push_back(const_cast<char*>(arg.c_str()));
        }
        c_args.push_back(nullptr);

        execvp(c_args[0], c_args.data());
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
    } else {
        waitpid(pid, nullptr, 0);
    }
}

void runpipeline(vector<vector<string>>& commands) {
    int num = commands.size() - 1;
    int pipefds[2];
    int prevread = -1;

    for (int i = 0; i < commands.size(); ++i) {
        if (i < num) {
            pipe(pipefds); 
        }
pid_t pid = fork();
        if (pid == 0) { 
            if (i > 0) {
                dup2(prevread, STDIN_FILENO); 
                close(prevread);
            }
 if (i < num) {
                dup2(pipefds[1], STDOUT_FILENO);
                close(pipefds[0]);
            }
executepipecommand(commands[i]);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
        } else { 
            if (i > 0) {
                close(prevread);
            }
            if (i < num) {
                close(pipefds[1]);
                prevread = pipefds[0];
            }
        }
    } for (int i = 0; i < num; ++i) {
        close(pipefds[0]);
        close(pipefds[1]);
    }for (int i = 0; i < commands.size(); ++i) {
        wait(nullptr);
    }
}




string  curretwd=Currentdirectory();
string  prevwd= Currentdirectory();
void runbackcommand(vector<string> args, bool back) {
    pid_t pid = fork();
    if (pid == 0) {
        vector<char*> c_args;
        for (const auto &arg : args) {
            c_args.push_back(const_cast<char*>(arg.c_str()));
        }
        c_args.push_back(nullptr);

        execvp(c_args[0], c_args.data());
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
    } 
    
    
    else {
        if (back) {
            cout << pid << endl;
        } else {
            waitpid(pid, nullptr, 0);
        }
    }
}
void runcommand(vector<string>&args) {
   
    if (args.empty()) {
        return;
    }
    if (args[0] == "cd") {
    
        if (args.size() > 1) {
            cd(args[1]);
        }
    } else if (args[0].compare("exit") == 0) {
 
    exit(0);
}else if(args[0]=="history")
    {   if(args.size()==1)
        loadHistory();
        if(args.size()==2)
        {
            int num=stoi(args[1]);
        loadHistory(num);
        }
    } else if(args[0]=="echo")
    {
        echo(args);
    }
    else if(args[0]=="pwd")
    {
        char* pwd1=new char[100];
        pwd1=pwd();
        if(pwd1!=nullptr)
        cout<<pwd1<<endl;
    }
    else if(args[0]=="ls")
    {
          bool h = false;
                bool D = false;
                char *path = nullptr;

                for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "-a") {
            h = true;
        } else if (args[i] == "-l") {
            D = true;
        } else if (args[i]=="-la" || args[i]=="-al"){
            h=true;
            D=true;
            
        }
        else {
            path = const_cast<char*>(args[i].c_str());
        }
    }
                if (path) {
                    ls(path, h, D);
                } else {
                    ls(pwd(), h, D);
                }
  } else if (args[0] == "pinfo") {
    if (args.size() == 1) {
        int pid = getpid();
        pInfo(pid);
    } else if (args.size() == 2) {
        int pid;
        istringstream argStream(args[1]);
        if (!(argStream >> pid)) {
            cerr << "Invalid PID" << endl;
        } else {
           
            pInfo(pid);
        }    
    } else {
     
        cerr << "pinfo is giving error" << endl;
    }
}
else if(args[0]=="search")
{
    char * present=pwd();
    bool ans=search(present,args[1]);
    if(ans==0)
    cout<<"FALSE";
    else
    cout<<"TRUE";
}
 else {
        bool background = false;
        if (!args.empty() && args.back() == "&") {
            background = true;
            args.pop_back();
        }
        runbackcommand(args, background);
    }
    
}
int main() {
    while (true) {
        prompt();
        signal(SIGTSTP, handleCtrlZ);
        signal(SIGINT, handleCtrlC);

        string userCommand;
        getline(cin, userCommand);

        if (userCommand == "exit") {
            exit(0); 
        }

        vector<vector<string>> commands;
        istringstream iss(userCommand);
        string token;
        vector<string> currentCommand;
        int flag = 0;

        while (iss >> token) {
            if (token == "|") {
                commands.push_back(currentCommand);
                flag = 1;
                currentCommand.clear();
            } else {
                currentCommand.push_back(token);
            }
        }

        if (!currentCommand.empty()) {
             //storehistory1(commands);
            commands.push_back(currentCommand);
        }

        if (!commands.empty() && flag==1) {
           
            runpipeline(commands);
        } else { 
            vector<string> tokenization;
            istringstream multicommand(userCommand);
            string command;

            while (getline(multicommand, command, ';')) {
                tokenization.push_back(command);
                storehistory1(command);
            }

            if (flag == 0) { 
                for (const string& command : tokenization) {
                    vector<string> tokens;
                    istringstream singlecommand(command);
                    string token;

                    while (singlecommand >> token) {
                        tokens.push_back(token);
                    }

                    bool ioRedirectionOnly = true;

                    for (const string& token : tokens) {
                        if (token != "<" && token != ">" && token != ">>") {
                            ioRedirectionOnly = false;
                            break;
                        }
                    }

                    if (ioRedirectionOnly) {
                        pid_t pid = fork();

                        if (pid == -1) {
                            perror("Fork failed");
                            exit(1);
                        } else if (pid == 0) {
                            size_t index = 0;

                            while (index < tokens.size()) {
                                if (tokens[index] == "<") {
                                    inputredirection(tokens, index);
                                } else if (tokens[index] == ">") {
                                    outputredirection(tokens, index);
                                } else if (tokens[index] == ">>") {
                                    appendredirection(tokens, index);
                                } else {
                                    index++;
                                }
                            }

                            if (!tokens.empty()) {
                                runcommand(tokens);
                            }

                            exit(0);
                        } else {
                            int status;
                            waitpid(pid, &status, 0);
                        }
                    } else {
                        runcommand(tokens);
                    }
                }
            }
        }
    }

    return 0;
}


/* int main() {
    while (true) {
        prompt();
        signal(SIGTSTP, handleCtrlZ);
        signal(SIGINT, handleCtrlC);

        string userCommand;
        getline(cin, userCommand);

        if (userCommand == "exit") {
            exit(0); // Terminate the shell
        }

        vector<vector<string>> commands;
        istringstream iss(userCommand);
        string token;
        vector<string> currentCommand;
        int flag = 0;

        while (iss >> token) {
            if (token == "|") {
                commands.push_back(currentCommand);
                flag = 1;
                currentCommand.clear();
            } else {
                currentCommand.push_back(token);
            }
        }

        if (!currentCommand.empty()) {
            commands.push_back(currentCommand);
        }

        if (!commands.empty()) {
            runpipeline(commands);
        } else {
            vector<string> tokenization;
            istringstream multicommand(userCommand);
            string command;

            while (getline(multicommand, command, ';')) {
                tokenization.push_back(command);
                storehistory1(command);
            }

            for (const string& command : tokenization) {
                vector<string> tokens;
                istringstream singlecommand(command);
                string token;

                while (singlecommand >> token) {
                    tokens.push_back(token);
                }

                bool ioRedirectionOnly = true;

                for (const string& token : tokens) {
                    if (token != "<" && token != ">" && token != ">>") {
                        ioRedirectionOnly = false;
                        break;
                    }
                }

                if (ioRedirectionOnly) {
                    pid_t pid = fork();

                    if (pid == -1) {
                        perror("Fork failed");
                        exit(1);
                    } else if (pid == 0) {
                        size_t index = 0;

                        while (index < tokens.size()) {
                            if (tokens[index] == "<") {
                                inputredirection(tokens, index);
                            } else if (tokens[index] == ">") {
                                outputredirection(tokens, index);
                            } else if (tokens[index] == ">>") {
                                appendredirection(tokens, index);
                            } else {
                                index++;
                            }
                        }

                        if (!tokens.empty()) {
                            runcommand(tokens);
                        }

                        exit(0);
                    } else {
                        int status;
                        waitpid(pid, &status, 0);
                    }
                } else {
                    runcommand(tokens);
                }
            }
        }
    }

    return 0;
}
 */




/* int main() {
    while (true) {
        prompt();
        signal(SIGTSTP, handleCtrlZ);
        signal(SIGINT, handleCtrlC);

        string userCommand;
        getline(cin, userCommand);
        vector<string> tokenization;
        istringstream multicommand(userCommand);
        string command;
        while (getline(multicommand, command, ';')) {
            tokenization.push_back(command);
            storehistory1(command);
        }

        for (const string& command : tokenization) {
            vector<string> tokens;
            istringstream singlecommand(command);
            string token;
            bool inQuotes = false;
            string currentToken = "";

            while (singlecommand >> token) {
                if (token.find('"') != string::npos) {
                    if (!inQuotes) {
                        inQuotes = true;
                        currentToken = token;
                    } else {
                        inQuotes = false;
                        currentToken += " " + token;
                        tokens.push_back(currentToken);
                        currentToken = "";
                    }
                } else if (inQuotes) {
                    currentToken += " " + token;
                } else {
                    tokens.push_back(token);
                }
            }

            bool ioRedirectionOnly = true;
            for (const string& token : tokens) {
                if (token != "<" && token != ">" && token != ">>") {
                    ioRedirectionOnly = false;
                    break;
                }
            }

            if (ioRedirectionOnly) {
                pid_t pid = fork();

                if (pid == -1) {
                    perror("Fork failed");
                    exit(1);
                } else if (pid == 0) {
                    size_t index = 0;
                    while (index < tokens.size()) {
                        if (tokens[index] == "<") {
                            inputredirection(tokens, index);
                        } else if (tokens[index] == ">") {
                            outputredirection(tokens, index);
                        } else if (tokens[index] == ">>") {
                            appendredirection(tokens, index);
                        } else {
                            index++;
                        }
                    }

                    if (!tokens.empty()) {
                        runcommand(tokens);
                    }
                    exit(0);
                } else {
                    int status;
                    waitpid(pid, &status, 0);
                }
            } else {
                runcommand(tokens);
            }
        }

        if (userCommand == "exit") {
            exit(0);
        }
    }

    return 0;
} */






 /* int main() {
    
        while(true)
        {
        prompt();
        signal(SIGTSTP, handleCtrlZ);
        signal(SIGINT, handleCtrlC);
         // signal(EOF, handleCtrlD); 
        string userCommand;
        getline(cin, userCommand);
           if (userCommand == "exit") {
            exit(0); // Terminate the shell
        }
////////here pipe
  vector<vector<string>> commands;
        istringstream iss(userCommand);
        string token;
        vector<string> currentCommand;
        int flag=0;
        while (iss >> token) {
            if (token == "|") {
                commands.push_back(currentCommand);
                flag=1;
                currentCommand.clear();
            } else {
                currentCommand.push_back(token);
            }
        }

        if (!currentCommand.empty()) {
            commands.push_back(currentCommand);
        }
if (!commands.empty()) {
            runpipeline(commands);
        }
    









//////////to here pipe
        vector<string> tokenization;
        istringstream multicommand(userCommand);
        string command;
        while (getline(multicommand, command, ';')) {
            tokenization.push_back(command);
            storehistory1(command);
        }
        if(flag=0)
        {
        for (const string& command : tokenization) {
            vector<string> tokens;
            istringstream singlecommand(command);
            string token;
            while (singlecommand >> token) {
                tokens.push_back(token);
            }
            bool ioRedirectionOnly = true;
            for (const string& token : tokens) {
                if (token != "<" && token != ">" && token != ">>") {
                    ioRedirectionOnly = false;
                    break;
                }
            }

            if (ioRedirectionOnly) {
                pid_t pid = fork();

                if (pid == -1) {
                    perror("Fork failed");
                    exit(1);
                } else if (pid == 0) {
                    size_t index = 0;
                    while (index < tokens.size()) {
                        if (tokens[index] == "<") {
                            inputredirection(tokens, index);
                        } else if (tokens[index] == ">") {
                            outputredirection(tokens, index);
                        } else if (tokens[index] == ">>") {
                            appendredirection(tokens, index);
                        } else {
                            index++;
                        }
                    }

                    
                   
                } else {
                    int status;
                    waitpid(pid, &status, 0);
                }
            } else {
               
            runcommand(tokens);
            }
        }
       /*  if (userCommand == "exit") {
            exit(0);
        } 
        }

    } 
  return 0;
 } */
   
 


/* int main() {
    while (true) {
        prompt();
        signal(SIGTSTP, handleCtrlZ);
        signal(SIGINT, handleCtrlC);

        string userCommand;
        getline(cin, userCommand);
        vector<string> tokenization;
        istringstream multicommand(userCommand);
        string command;
        while (getline(multicommand, command, ';')) {
            tokenization.push_back(command);
            storehistory1(command);
        }

        for (const string& command : tokenization) {
            pid_t pid = fork();

            if (pid == -1) {
                perror("Fork failed");
                exit(1);
            } else if (pid == 0) {
              vector<string> tokens;
                istringstream singlecommand(command);
                string token;

                while (singlecommand >> token) {
                    tokens.push_back(token);
                }

                size_t index = 0;
                while (index < tokens.size()) {
                    if (tokens[index] == "<") {
                        inputredirection(tokens, index);
                    } else if (tokens[index] == ">") {
                        outputredirection(tokens, index);
                    } else if (tokens[index] == ">>") {
                        appendredirection(tokens, index);
                    } else {
                        index++;
                    }
                }

                if (!tokens.empty()) {
                    runcommand(tokens);
                }
                 exit(0);
            } else {
                int status;
                waitpid(pid, &status, 0);
            }
        }
         if (userCommand == "exit") {
            exit(0);
        }
    } */

    




























