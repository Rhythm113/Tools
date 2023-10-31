/* 
No Backup Hook For external CPP
Writen by : @Rhythm113 
Channel : @InfinityCreators1

git : gitHub.com/Rhythm113
*/


#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <thread>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <cstdlib>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

using namespace std;

int getPID(const char *PackageName) {
    DIR *dir = opendir("/proc");
    if (dir == nullptr) {
        perror("opendir");
        return 0;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type != DT_DIR)
            continue;
        
        int pid = atoi(entry->d_name);
        if (pid == 0)
            continue;
        
        char cmdline_path[256];
        snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%d/cmdline", pid);

        ifstream cmdline_file(cmdline_path);
        string process_name;
        getline(cmdline_file, process_name, '\0');

        if (strcmp(process_name.c_str(), PackageName) == 0) {
            closedir(dir);
            return pid;
        }
    }

    closedir(dir);
    return 0;
}

uintptr_t get_module_base(const char *module_name, int target_pid) {
    uintptr_t addr = 0;
    char filename[32], buffer[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", target_pid);
    ifstream file(filename);
    if (file.is_open()) {
        while (file.getline(buffer, sizeof(buffer))) {
            if (strstr(buffer, module_name)) {
                sscanf(buffer, "%lx-", &addr);
                break;
            }
        }
        file.close();
    }
    return addr;
}

uintptr_t get_module_end(const char *module_name, int target_pid) {
    uintptr_t temp = 0, addr = 0;
    char filename[32], buffer[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", target_pid);
    ifstream file(filename);
    if (file.is_open()) {
        while (file.getline(buffer, sizeof(buffer))) {
            if (strstr(buffer, module_name)) {
                sscanf(buffer, "%*x-%lx", &addr);
                break;
            }
        }
        file.close();
    }
    return addr;
}


uintptr_t String2Offset(const char *c) {
    int base = 16;
	static_assert(sizeof(uintptr_t) == sizeof(unsigned long) || sizeof(uintptr_t) == sizeof(unsigned long long), "Please add string to handle conversion for this architecture.");
	
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }
    return strtoull(c, nullptr, base);
}


int hook_lib_no_backup(const char *pkg , const char *module_name , const char *offset, void *target){

    char memFile[1024];
    int pid = getPID(pkg);
    sprintf(memFile, "/proc/%d/mem", pid);
    FILE* fp = fopen(memFile, "r+");
    void* hookc = mmap(NULL, sizeof(target), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memcpy(hookc, target, sizeof(target));
    uintptr_t addr = get_module_base(module_name,pid) + String2Offset(offset);
    fseek(fp, addr, SEEK_SET);
    fwrite(hookc, sizeof(target), 1, fp);
    fclose(fp);
    munmap(hookc, sizeof(target));

    printf("Hooking successful!\n");

    return 0;
  }
    