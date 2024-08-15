/*
 * The working directory. This will control where the program saves its models.
 */

#ifndef GPTMANAGER_DIRECTORY_H
#define GPTMANAGER_DIRECTORY_H


#include <string>
using namespace std;
// Declare a Directory class.

class Directory {
    public:
        static string getDirectory();
        static void setDirectory(const string& directory);
        static string getModelDirectory();
        virtual string print(const Directory &dir) const;

        friend ostream const &operator<<(ostream &os, const Directory& directory);
    private:
        static string directory;
        static string modelDirectory;
};


#endif //GPTMANAGER_DIRECTORY_H
