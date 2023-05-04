#include <iostream>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <directory>\n";
        return 1;
    }
    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        std::cout << "Error opening directory " << argv[1] << "\n";
        return 1;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char path[1024];
            sprintf(path, "%s/%s", argv[1], entry->d_name);
            struct stat st;
            if (stat(path, &st) == 0) {
                std::cout << entry->d_name << ": " << (long long) st.st_size << " bytes\n";
            } else {
                std::cout << "Error getting file size for " << path << "\n";
            }
        }
    }
    closedir(dir);
    return 0;
}
