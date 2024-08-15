//
// Created by protr on 11/25/2023.
//

#ifndef GPTMANAGER_MODEL_H
#define GPTMANAGER_MODEL_H
#include <string>

class Model {
public:
    explicit Model(std::string name);
    Model();
    std::string getName() const;
    std::string getResponse();
    void setPath(std::string path2);
    static std::string getFullName(const Model& model);
private:
    std::string mName;
    std::string mResponse;

    friend std::ostream &operator<<(std::ostream &os, const Model& model);
    friend bool operator==(const Model& model1, const Model& model2);

};


#endif //GPTMANAGER_MODEL_H
