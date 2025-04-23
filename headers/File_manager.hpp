#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>

#include "../headers/Hero.hpp"

class FileManager {
public:
    FileManager();

    static void saveHero(const Hero& hero);
    static Hero loadHero(const std::string& name);
    static void deleteHero(const std::string& name);

private:
    static int nameToLineIndex(const std::string& name);

};

#endif