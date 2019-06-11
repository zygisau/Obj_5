//
// Created by zygisau on 29/05/2019.
//

#ifndef OBJ_5_WORDMODEL_H
#define OBJ_5_WORDMODEL_H

#include <vector>
#include <string>
#include <set>
using std::vector; using std::string; using std::set;

class WordModel {
private:
    int counter = 0;
    set<int> reference;
public:
    WordModel() : counter(0) {}
    explicit WordModel(int ref) { counter++; reference.insert(ref); }
    void addOne() { counter++; }
    void addReference(const int& ref) { reference.insert(ref); }
    int getCounter() const { return counter; }
    set<int> getReference() const { return reference; }
};


#endif //OBJ_5_WORDMODEL_H
