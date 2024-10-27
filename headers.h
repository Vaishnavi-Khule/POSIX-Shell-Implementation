#include <iostream>
#include <string>
#include <pwd.h>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <stdio.h>
#include <cstdio>
#include <sys/wait.h>
#include <sys/utsname.h>
#include<vector>
#include <cstring>
#include <iomanip>
#include <dirent.h>
#include<grp.h>
#include <csignal>
#include<filesystem>
#include<algorithm>
#include <sys/types.h>
#include <sstream>
#include <cstdlib>

#include <fcntl.h>
namespace fs = std::filesystem;
using namespace std;
string Currentdirectory();
void prompt();
void echo(vector<string> &args);
void ls( char *path, bool h, bool D);
char* pwd();
void cd(string &path);
void storehistory1(string History);
void pInfo(int pid);
bool search(const fs::path& currentDir, const string& targetFile) ;
void loadHistory();
void loadHistory(int n);
  void handleCtrlZ(int signal);
  void handleCtrlC(int signal) ;
  void inputredirection(vector<string>& tokens, size_t& index); 
  void outputredirection(vector<string>& tokens, size_t& index);
  void appendredirection(vector<string>& tokens, size_t& index);
 