#include "headers.h"
void ls( char *path, bool h, bool D) {
    DIR *dir = opendir(path);

    if (!dir) {
        perror("ls");
        return;
    }
    struct dirent *file1;
    while ((file1 = readdir(dir))) {
        char *name = file1->d_name;

        if (D) {
            struct stat file;
            string fullPath = string(path) + "/" + name;

            if (stat(fullPath.c_str(), &file) == 0) {
                std::cout << ((S_ISDIR(file.st_mode)) ? "d" : "-")
                          << ((file.st_mode & S_IRUSR) ? "r" : "-")
                          << ((file.st_mode & S_IWUSR) ? "w" : "-")
                          << ((file.st_mode & S_IXUSR) ? "x" : "-")
                          << ((file.st_mode & S_IRGRP) ? "r" : "-")
                          << ((file.st_mode & S_IWGRP) ? "w" : "-")
                          << ((file.st_mode & S_IXGRP) ? "x" : "-")
                          << ((file.st_mode & S_IROTH) ? "r" : "-")
                          << ((file.st_mode & S_IWOTH) ? "w" : "-")
                          << ((file.st_mode & S_IXOTH) ? "x" : "-")
                          << " ";

                struct passwd *user = getpwuid(file.st_uid);
                struct group *gr = getgrgid(file.st_gid);

                if (user) {
                    cout << user->pw_name << " ";
                } else {
                    cout << file.st_uid << " ";
                }

                if (gr) {
                    cout << gr->gr_name << " ";
                } else {
                    cout << file.st_gid << " ";
                }
                            time_t modTime = file.st_mtime;
                char dateStr[20];
                strftime(dateStr, sizeof(dateStr), "%b %d %H:%M", localtime(&modTime));
                cout << dateStr << " ";
                cout << setw(10) << file.st_size << " "<< file1->d_name<<endl ;
                 
            }
        } else {
            cout << file1->d_name << " ";
        }
    }

    closedir(dir);
}