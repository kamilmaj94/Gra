#include "PCH.hpp"
#include "Utils.hpp"


namespace Utils {

namespace FS {

std::string GetExecutableDir()
{
    return GetParentDir(GetExecutablePath());
}

std::string GetExecutablePath()
{
    HMODULE exe = GetModuleHandle(0);

    char path[512];
    GetModuleFileNameA(exe, path, 512);

    return UnifySlashes(path);
}

std::string GetParentDir(const std::string& path)
{
    std::string temp = UnifySlashes(path);
    return path.substr(0, temp.rfind("/"));
}

bool SetCWD(const std::string& path)
{
    if (!SetCurrentDirectoryA(path.c_str()))
    {
        printf("Failed to set current directory");
        return false;
    }

    // TODO replace with logger
    std::cout << "Set current working directory to " << path << std::endl;
    return true;
}

std::string UnifySlashes(const std::string& path)
{
    std::string result = path;

    for (char& c : result)
    {
        if (c == '\\')
            c = '/';
    }

    return result;
}

} // namespace FS

} // namespace Utils