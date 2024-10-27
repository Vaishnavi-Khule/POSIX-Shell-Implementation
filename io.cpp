#include "headers.h"
void inputredirection(vector<string>& tokens, size_t& index) {
    if (index < tokens.size() - 2 && tokens[index] == "<") {
        const char* file = tokens[index + 1].c_str();
        int fd = open(file, O_RDONLY);
        if (fd == -1) {
            perror("Input file open failed");
            exit(1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        tokens.erase(tokens.begin() + index, tokens.begin() + index + 2);
    } else {
        cerr << "Missing input file" << endl;
        exit(1);
    }
}



void outputredirection(vector<string>& tokens, size_t& index) {
    if (index + 1 < tokens.size()) {
        const char* file = tokens[index + 1].c_str();
        int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Output file open failed");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        tokens.erase(tokens.begin() + index, tokens.begin() + index + 2); 
    } else {
        cerr << "missing output file " << endl;
        exit(1);
    }
}


void appendredirection(vector<string>& tokens, size_t& index) {
    if (index + 1 < tokens.size()) {
        const char* file = tokens[index + 1].c_str();
        int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            perror("output file open failed");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        tokens.erase(tokens.begin() + index, tokens.begin() + index + 2); 
    } else {
        cerr << "Missing output file " << endl;
        exit(1);
    }
}