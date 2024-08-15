#include "Model.h"
#include "Directory.h"
#include <utility>

Model::Model(string name) {
    this->mName = std::move(name);
}

Model::Model() = default;

string Model::getName() const {
    // Return the model's name without its parent directory.
    // Also truncate the .JSONL from the mName.
    return mName.substr(mName.find_last_of("/\\") + 1, mName.find_last_of(".") - mName.find_last_of("/\\") - 1);
}

string Model::getFullName(const Model& model) {
    return Directory::getModelDirectory() + "\\" + model.getName() + ".JSONL";
}

string Model::getResponse() {
    return mResponse;
}

void Model::setPath(string path2) {
    this->mName = std::move(path2);
}

ostream &operator<<(ostream &os, const Model& model) {
    // Return the model's name without its parent directory.
    os << model.getName();
    return os;
}

bool operator==(const Model& model1, const Model& model2) {
    // Models are considered equal if they have the same name.
    return model1.getName() == model2.getName();
}