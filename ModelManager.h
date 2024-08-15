//
// Created by protr on 11/25/2023.
//

#ifndef GPTMANAGER_MODELMANAGER_H
#define GPTMANAGER_MODELMANAGER_H
#include <string>
#include <vector>
#include "Model.h"

class ModelManager {
public:
    ModelManager();
    static void addModel(const Model& model);
    static void removeModel(const Model& model);
    static Model getModel(Model model);
    static std::vector<Model> getAllModels();
    static void deleteAllModels();

    friend std::ostream &operator<<(std::ostream &os, ModelManager modelManager);
private:
    static std::vector<Model> models;
    static std::string directory;
};


#endif //GPTMANAGER_MODELMANAGER_H
