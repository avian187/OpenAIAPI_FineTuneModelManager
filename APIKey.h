#ifndef GPTMANAGER_APIKEY_H
#define GPTMANAGER_APIKEY_H

#include <string>
#include "Directory.h"
#include <iostream>
#include <vector>

class APIKey : public Directory {
public:
    // API keys, in OpenAI, have a name, as well as the actual value of the key.
    APIKey(std::string name, std::string key);
    APIKey();
    void setName(std::string name) { mName = std::move(name); };
    void setKey(std::string key) { mKey = std::move(key); };
    std::string getName() const { return mName; };
    std::string getKey() const { return mKey; };
    string print(const Directory &dir) const override;
    static void deleteKey(const APIKey& apiKey);
    static void printKeys();
    static string apiKeysDirectory;
    static vector<APIKey> apiKeys;

    friend std::ostream const &operator<<(std::ostream &os, const APIKey& apiKey);
    friend bool operator==(const APIKey& apiKey1, const APIKey& apiKey2);
private:
    std::string mKey;
    std::string mName;
};

#endif //GPTMANAGER_APIKEY_H
