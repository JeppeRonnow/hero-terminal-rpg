#include "../headers/File_manager.hpp"
#include <fstream>

// find line with matching name
int FileManager::nameToLineIndex(const std::string& name) {

    std::ifstream file("../data/heros.txt");
    std::string line;
    int index = 0;

    // read all lines
    while (std::getline(file, line)) {
        size_t pos = line.find(',');

        // check if name matches
        if (pos != std::string::npos && line.substr(0, pos) == name) {
            file.close();
            return index;
        }

        // next line
        index++;
    }
    file.close();

    return -1; // not found
}


// save hero to file
void FileManager::saveHero(const Hero& hero) {
    // Check if the hero already exists in the file
    int lineIndex = nameToLineIndex(hero.getName());
    std::ifstream inputFile("../data/heros.txt");
    std::string line;
    std::vector<std::string> lines;
    int currentIndex = 0;

    // Read all lines from the file
    while (std::getline(inputFile, line)) {
        if (currentIndex == lineIndex) {
            // Update the existing hero's data
            line = hero.getName() + "," + std::to_string(hero.getXP()) + "," +
                   std::to_string(hero.getLevel()) + "," + std::to_string(hero.getHP()) + "," +
                   std::to_string(hero.getStrength()) + "," +
                   std::to_string(hero.getGold());
        }
        lines.push_back(line);
        currentIndex++;
    }
    inputFile.close();

    // If the hero does not exist, add it to the end of the file
    if (lineIndex == -1) {
        lines.push_back(hero.getName() + "," + std::to_string(hero.getXP()) + "," +
                        std::to_string(hero.getLevel()) + "," + std::to_string(hero.getHP()) + "," +
                        std::to_string(hero.getStrength()) + "," + std::to_string(hero.getGold()));
    }

    // Write all lines back to the file
    std::ofstream outputFile("../data/heros.txt", std::ios::trunc);
    for (const auto& l : lines) {
        outputFile << l << "\n";
    }
    outputFile.close();
}

// load hero from file using index line
Hero FileManager::loadHero(const std::string& name) {
    
    // Get the line index of the hero name
    int lineIndex = nameToLineIndex(name);
    if (lineIndex == -1) {
        throw std::runtime_error("Hero not found"); // Throw an error if the hero is not found
    }

    std::ifstream file("../data/heros.txt");
    std::string line;
    int currentIndex = 0;

    // Read the file line by line
    while (std::getline(file, line)) {
        if (currentIndex == lineIndex) {
            file.close();

            // get the hero data from the line
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            size_t pos4 = line.find(',', pos3 + 1);
            size_t pos5 = line.find(',', pos4 + 1);

            // make and return the hero
            return Hero(
                line.substr(0, pos1),
                std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1)),
                std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1)),
                std::stoi(line.substr(pos3 + 1, pos4 - pos3 - 1)),
                std::stoi(line.substr(pos4 + 1, pos5 - pos4 - 1)),
                std::stoi(line.substr(pos5 + 1))                   
            );
        }
        currentIndex++; // next line
    }
    file.close();

    // If the hero is not found in the file
    throw std::runtime_error("Hero not found in file");

}

// delete hero from file using index line
void FileManager::deleteHero(const std::string& name) {
    // Get the line index of the hero name
    int lineIndex = nameToLineIndex(name);

    std::ifstream inputFile("../data/heros.txt");
    std::string line;
    std::vector<std::string> lines;
    int currentIndex = 0;

    // Read all lines from the file
    while (std::getline(inputFile, line)) {
        if (currentIndex != lineIndex) {
            lines.push_back(line); // Add all lines except the one to be deleted
        }
        currentIndex++;
    }
    inputFile.close();

    // Write all lines back to the file
    std::ofstream outputFile("../data/heros.txt", std::ios::trunc);
    for (const auto& l : lines) {
        outputFile << l << "\n";
    }
    outputFile.close();
}