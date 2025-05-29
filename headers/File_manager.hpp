#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>

#include "../headers/Hero.hpp"

/*

    FileManger not used after 3. interration, but kept for future reference.

*/


class FileManager {
public:
    FileManager();

    static void saveHero(const Hero& hero);
    static Hero loadHero(const std::string& name);
    static void deleteHero(const std::string& name);

private:
    static int nameToLineIndex(const std::string& name); // Convert hero name to line index in the file

};

#endif