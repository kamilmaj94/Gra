#pragma once

#include <string>

namespace Utils {

namespace FS {

std::string GetExecutableDir();
std::string GetExecutablePath();
std::string GetParentDir(const std::string& path);
bool SetCWD(const std::string& path);
std::string UnifySlashes(const std::string& path);

} // namespace FS

} // namespace Utils
