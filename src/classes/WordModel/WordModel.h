//
// Created by zygisau on 29/05/2019.
//

#ifndef OBJ_5_WORDMODEL_H
#define OBJ_5_WORDMODEL_H

#include <vector>
#include <string>
using std::vector; using std::string;

class WordModel {
private:
    int counter = 0;
    vector<int> reference;
public:
    WordModel() : counter(0), reference(0) {}
    explicit WordModel(int ref) { counter++; reference.push_back(ref); }
    void addOne() { counter++; }
    void addReference(const int& ref) { reference.push_back(ref); }
    int getCounter() const { return counter; }
    vector<int> getReference() const { return reference; }
};


#endif //OBJ_5_WORDMODEL_H
