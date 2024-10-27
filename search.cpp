#include "headers.h"
#include <filesystem>
namespace fs = filesystem;

bool search(const fs::path& curr, const string& target) {
    try {
        for (const auto& entry : fs::directory_iterator(curr)) {
            if (entry.is_directory()) {
                if (entry.path().filename() == target) {
                    return true;
                }
                if (search(entry.path(), target)) {
                    return true;
                }
            } else if (entry.is_regular_file() && entry.path().filename() == target) {
                return true;
            }
        }
    } catch (const exception& ex) {
      cerr << "Error: " << ex.what() << endl;
        return false;
    }
    return false;
}


