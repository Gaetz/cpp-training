#ifndef UTILITIES_H
#define UTILITIES_H

#define RUNNING_WINDOWS
#include <iostream>
#include <string>
#include <algorithm>

namespace Utils {
#ifdef RUNNING_WINDOWS
    #include <windows.h>
    #include <Shlwapi.h>

inline std::string getWorkingDirectory() {
    HMODULE hModule = GetModuleHandle(nullptr);
    if(hModule) {
        char path[256];
        GetModuleFileName(hModule, path, sizeof(path));
        PathRemoveFileSpec(path);
        strcat_s(path, "\\");
        return std::string(path);
    }
    return "";
}
#elif defined RUNNING_LINUX
#include <unistd.h>
inline std::string getWorkingDirectory() {
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != nullptr) {
        return std::string(cwd) + std::string("/");
    }
    return "";
}
#endif
}

#endif // UTILITIES_H
