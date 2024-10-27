#include "headers.h"
void cd(string &path) {
    if (path == ".") {
      return;
    } else if (path == "..") {
      char curr_path[PATH_MAX];
        if (getcwd(curr_path, sizeof(curr_path)) != nullptr) {
            char *slash = strrchr(curr_path, '/');
            if (slash != nullptr) {
                *slash = '\0'; 
                if (chdir(curr_path) != 0 ) {
                    perror("chdir");
                }
            } else {
                perror("getcwd");
            }
        } else {
            perror("getcwd");
        }
    } 
      else if (path == "~") {
        const char *homeDir = getenv("HOME");
        if (homeDir != nullptr) {
            if (chdir(homeDir) != 0) {
                perror("chdir");
            }
        } else {
            perror("getenv");
        }
    } 
   else if(chdir(path.c_str()) != 0) {
            perror("chdir");
        }
    } 

   