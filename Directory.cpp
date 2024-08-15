//
// Created by protr on 12/5/2023.
//
#include <filesystem>
#include <iostream>
#include "Directory.h"
string Directory::directory;
string Directory::modelDirectory;

string Directory::getDirectory() {
    return directory;
}

void Directory::setDirectory(const string& directory1) {
    directory = directory1;
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directory(directory);
    }

    // Create a model directory as a child of the directory.
    modelDirectory = directory + "\\Models";
    if (!std::filesystem::exists(modelDirectory)) {
        std::filesystem::create_directory(modelDirectory);
    }
}

string Directory::getModelDirectory() {
    return modelDirectory;
}

string Directory::print(const Directory &dir) const {
    stringstream ss;
    ss << "Directory: " << dir.getDirectory() << "\n";
    ss << "Model Directory: " << dir.getModelDirectory() << "\n";
    return ss.str();
}

ostream const &operator<<(ostream &os, const Directory& directory) {
    // Use the print function
    os << directory.print(directory);
    return os;
}

