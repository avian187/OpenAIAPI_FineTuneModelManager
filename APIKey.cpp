#include <sstream>
#include <filesystem>
#include <fstream>
#include "APIKey.h"
#include "Directory.h"

string APIKey::apiKeysDirectory = {};
vector<APIKey> APIKey::apiKeys = {};

bool operator==(const APIKey &apiKey1, const APIKey &apiKey2) {
    return ((apiKey1.getName() == apiKey2.getName())
    && (apiKey1.getKey() == apiKey2.getKey()));
}

std::ostream const &operator<<(std::ostream &os, const APIKey &apiKey) {
    os << apiKey.print(apiKey);
    return os;
}

string APIKey::print(const Directory &dir) const {
    stringstream ss;
    ss << "API Key with name: [" << this->getName() << "], Key value: [" << this->getKey() << "]\n";
    return ss.str();
}

APIKey::APIKey(std::string name, std::string key) {
    this->mName = std::move(name);
    this->mKey = std::move(key);

    // Save the API key to a file, with format: name.key, in a new directory under Workspace, named APIKeys.
    // First, create the APIKeys directory.
    if (!std::filesystem::exists(apiKeysDirectory)) {
        std::filesystem::create_directory(apiKeysDirectory);
    }

    // Create the file.
    string fileName = apiKeysDirectory + "\\" + getName() + ".key";
    std::ofstream file(fileName);
    file << getKey();
    file.close();

    // update the status of the APIKeys vector.
    apiKeys.push_back(*this);
}

void APIKey::deleteKey(const APIKey& apiKey) {
    // Delete the key from the APIKeys directory.
    string fileName = apiKeysDirectory + "\\" + apiKey.getName() + ".key";
    std::filesystem::remove(fileName);
    // Make sure that the file was deleted
    // Delete the key from the vector.
    for (int i = 0; i < apiKeys.size(); i++) {
        if (apiKeys[i] == apiKey) {
            apiKeys.erase(apiKeys.begin() + i);
        }
    }
}

void APIKey::printKeys() {
    // Iterate over the vector and print out each key.
    for (const APIKey& apiKey : APIKey::apiKeys) {
        cout << apiKey;
    }
}

APIKey::APIKey() {
    // Instantiates. Loads the API keys from the APIKeys directory, and adds them to the vector.
    // First, check if the directory exists.
    apiKeysDirectory = Directory::getDirectory() + "\\APIKeys";
    if (!std::filesystem::exists(apiKeysDirectory)) {
        std::filesystem::create_directory(apiKeysDirectory);
        // print the newly created directory
    }
    // Iterate over the directory and add the keys to the vector.
    // The keys are stored in files, with the name of the file being the name of the key.
    for (const auto &entry: std::filesystem::directory_iterator(apiKeysDirectory)) {
        // Create a key from the file.
        std::ifstream file(entry.path().string());
        string key;
        file >> key;
        // Truncate the file name to get the name of the key.
        string fileName = entry.path().filename().string();
        string name = fileName.substr(0, fileName.find('.'));
        APIKey apiKey(name, key);
        // Add the key to the vector.
        apiKeys.push_back(apiKey);
    }
}