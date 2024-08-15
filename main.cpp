/*
 * Project for creating fine-tuned GPT models.
 * Author: Ian Utnehmer, MiraCosta College
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <dirent.h>
#include "Model.h"
#include "ModelManager.h"
#include "Directory.h"
#include "APIKey.h"

int main() {
    // Check for previous models from file
    string apiKey;
    ofstream keystream;
    Directory::setDirectory("Workspace");
    APIKey instantiator = APIKey();
    // If the API Key vector is empty, then the user needs to add an API key.
    if (APIKey::apiKeys.empty()) {
        cout << "No API keys found. Please add an API key." << endl;
        string name, key;
        cout << "Enter the name of the API key: ";
        getline(cin, name);
        cout << "Enter the key value: ";
        getline(cin, key);
        APIKey apiKey1 = APIKey(name, key);
        cout << "\nAPI key added." << endl;
    }


    string modelName;
    cout << "Enter the name of your new model (press enter if not applicable): ";
    getline(cin, modelName);
    ModelManager modelManager = ModelManager();
    // close files
    keystream.close();
    int dataEntryMode;
    do {
        cout << "1.  Enter data manually" << endl;
        cout << "2.  Add data to model from existing data (Directory of .JSONL files)" << endl;
        cout << "3.  Add data to existing model" << endl;
        cout << "4.  Show existing models" << endl;
        cout << "5.  Delete existing model" << endl;
        cout << "6.  Delete all models" << endl;
        cout << "7.  Manage API Keys" << endl;
        cout << "8.  Exit program (saves work on current model)" << endl;
        cout << "Enter a number: ";
        cin >> dataEntryMode;

        string prompt1, completion1;
        int count = 1;

        string fileName, extractedLine, extractedPrompt, extractedCompletion;
        string existingModelName;
        Model preexistingModel, extractModel;
        ofstream outFile;

        string directory, path;
        vector<string> fileNames;

        string deleteModel;
        string addOrDelete;

        getline(cin, prompt1);
        ifstream inFile;

        switch (dataEntryMode) {
            case 1:
                outFile.open(Directory::getModelDirectory() + "\\" + modelName + ".JSONL", ios::app);
                // Enter data manually
                cout << "\nEnter -1 at any time to quit.\n" << endl;
                while (prompt1 != "-1" && completion1 != "-1") {
                    cout << "Enter prompt " << count << ": ";;
                    getline(cin, prompt1);
                    if (prompt1 == "-1") {
                        break;
                    }
                    cout << "Enter completion " << count << ": ";
                    getline(cin, completion1);
                    if (completion1 == "-1") {
                        break;
                    }
                    // Add to file
                    outFile << R"({"prompt": ")" << prompt1 << R"(", "completion": ")" << completion1 << "\"}\n";
                    cout << "Prompt and completion added to file." << endl;
                    count++;
                }
                // Close file
                outFile.close();
                break;
            case 2:
                outFile.open(Directory::getModelDirectory() + "\\" + modelName + ".JSONL", ios::app);
                cout << "\nMake sure your files are in the cmake-build-debug folder.\n"
                        "All .JSONL files in the directory will be extracted to"
                        " a new .JSONL file, which will be used to "
                        " train the new model.\n"
                        "Enter the name of the directory: ";
                getline(cin, directory);
                // Extract pairs from directory. The directory will contain
                // .JSONL files that contain prompt-completion pairs.
                // Write the pairs to the file
                // Close the file when done
                // Create and add a model to model manager.

                // First, get the names of all the files in the directory
                DIR *dir;
                struct dirent *ent;
                // Skip the first two entries in the directory, which are . and .., representing location within the dir.
                if ((dir = opendir(directory.c_str())) != nullptr) {
                    while ((ent = readdir(dir)) != nullptr) {
                        if (ent->d_name[0] != '.') {
                            fileNames.emplace_back(ent->d_name);
                            // Print out the saved name
                            cout << ent->d_name << endl;
                        }
                    }
                } else {
                    cerr << "Unable to open directory.\n";
                }

                // Next, iterate over the files and extract the prompt-completion pairs
                for (const string& file_name : fileNames) {
                    path = directory + "\\" + file_name;
                    inFile.open(path);
                    // Check if the file is opened successfully
                    if (!inFile.is_open()) {
                        cerr << "Error opening file: " << file_name << endl;
                        return 1; // Return an error code
                    }
                    // Parse each line, write them to the file
                    while (getline(inFile, extractedLine)) {
                        outFile << extractedLine << "\n";
                        cout << "Pair: " << extractedLine << " added to model." << endl;
                    }
                    // Close the file when done
                    inFile.close();
                }
                outFile.close();
                break;
            case 3:
                // Add data to existing model
                cout << "\nEnter the name of the model you would like to add data to: ";
                getline(cin, existingModelName);
                // Load model object from ModelManager
                // Add data to current model
                preexistingModel = ModelManager::getModel(Model(existingModelName));
                cout << "\nAdding data to model: " << preexistingModel.getName() << endl;
                outFile.open(Directory::getModelDirectory() + "\\" + preexistingModel.getName() + ".JSONL", ios::app);
                // Enter data manually
                cout << "Data can only be added from a pre-existing file.\n"
                        "Enter the name of the model you would like to add data from (Workspace\\Models): ";
                getline(cin, modelName);
                extractModel = ModelManager::getModel(Model(modelName));
                cout << "\nExtracting data from model: " << extractModel.getName() << endl;
                inFile.open(Directory::getModelDirectory() + "\\" + extractModel.getName() + ".JSONL");
                // Check if the file is opened successfully
                if (!inFile.is_open()) {
                    cerr << "Error opening file: " << extractModel.getName() << endl;
                    return 1; // Return an error code
                }
                // Parse each line, write them to the file
                while (getline(inFile, extractedLine)) {
                    outFile << extractedLine << "\n";
                    cout << "Pair: " << extractedLine << " added to model." << endl;
                }
                // Close the file when done
                inFile.close();
                break;
            case 4:
                // Show existing models
                cout << "\nExisting models:" << endl;
                cout << modelManager << endl;
                break;
            case 5:
                // Delete existing model
                cout << "\nEnter the name of the model you would like to delete: ";
                getline(cin, existingModelName);
                // Find the model in the ModelManager
                preexistingModel = ModelManager::getModel(Model(existingModelName));
                cout << "\nAre you sure you want to delete model: " << preexistingModel.getName() << "? (y/n): ";
                getline(cin, deleteModel);
                if (deleteModel == "y") {
                    ModelManager::removeModel(preexistingModel);
                } else {
                    cout << "\nModel not deleted." << endl;
                }
                break;
            case 6:
                // Delete all models
                cout << "\nAre you sure you want to delete all models? (y/n): ";
                char deleteAllModels;
                cin >> deleteAllModels;
                if (deleteAllModels == 'y') {
                    cout << "\nDeleting all models..." << endl;
                    ModelManager::deleteAllModels();
                } else {
                    cout << "\nModels not deleted." << endl;
                }
                break;
            case 7:
                // Print the keys
                cout << "Would you like to print the API keys? (y/n): ";
                char printKeys;
                cin >> printKeys;
                if (printKeys == 'y') {
                    APIKey::printKeys();
                }
                cout << "Would you like to add a new API key or delete an existing one? (add/delete): ";
                getline(cin, addOrDelete);
                getline(cin, addOrDelete); // get the getline to work properly.
                // Use the APIKey class to add or delete an API key.
                if (addOrDelete == "add") {
                    string name, key;
                    cout << "\nEnter the name of the API key: ";
                    getline(cin, name);
                    cout << "Enter the key value: ";
                    getline(cin, key);
                    APIKey apiKey1 = APIKey(name, key);
                    cout << "\nAPI key added." << endl;
                } else if (addOrDelete == "delete") {
                    string name;
                    cout << "\nEnter the name of the API key you would like to delete: ";
                    getline(cin, name);
                    APIKey apiKey1 = APIKey(name, "");
                    APIKey::deleteKey(apiKey1);
                    cout << "\nAPI key deleted." << endl;
                } else {
                    cout << "\nInvalid entry." << endl;
                }
                break;
            case 8:
                cout << "Exiting...";
                return 0;
            default:
                cout << "Invalid entry. Please enter a number between 1 and 8." << endl;
        }
    } while (dataEntryMode != 8 );
    // Cleanup, close files, streams, etc
    keystream.close();
    return 0;
}