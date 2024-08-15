#include <fstream>
#include "ModelManager.h"
#include "Model.h"
#include <iostream>
#include <filesystem>
#include "Directory.h"

std::vector<Model> ModelManager::models;
string ModelManager::directory;

ModelManager::ModelManager() {
    /*
     * This essentially opens the Models directory and reads the files from it.
     */

    // Open the directory. Extract all the models from it.
    // The directory tells you where to find the models, which are just .JSONL files.
    for (const auto &entry: std::filesystem::directory_iterator(Directory::getModelDirectory())) {
        // Create a model from the mName.
        Model model(entry.path().string());
        // Add the model to the vector.
        models.push_back(model);
    }
}

void ModelManager::addModel(const Model& model) {
    models.push_back(model);
}

void ModelManager::removeModel(const Model& model) {
    string path = Model::getFullName(model);
    cout << "Removing model with path: " << path << "\n";
    // First, delete the model from the vector.
    models.erase(models.begin());
    // Then, delete the model from the file system.
    std::filesystem::remove(path);
}

Model ModelManager::getModel(Model model) {
    // iterate over the vector and return the model that matches the model passed in.
    for (const Model& model1 : models) {
        if (model1 == model) {
            return model;
        }
    }
    // If the model is not found, return an error model.
    return Model("ERROR_MODEL_NOT_FOUND");
}

vector<Model> ModelManager::getAllModels() {
    return models;
}

void ModelManager::deleteAllModels() {
    // For each model in the vector, delete the model from the file system and the vector.
    for (const Model& model : models) {
        ModelManager::removeModel(model);
    }
}

ostream &operator<<(ostream &os, ModelManager modelManager) {
    // Iterate over the vector and print out each model.
    for (const Model& model : ModelManager::models) {
        os << model << "\n";
    }
    return os;
}