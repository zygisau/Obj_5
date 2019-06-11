//
// Created by zygisau on 27/05/2019.
//
#include "classes/WordModel/WordModel.h"
#include "main.h"
#include "functions.h"

int main() {
    // creating a container where words will be stored
    mapType words;

    // reading words from file and gathering the longest word from this function
    int maxWord = readFromFile(words);

    int longestRef = 0;
    for (auto& elem : words) {
        if (longestRef < elem.second.getCounter()) {
            longestRef = elem.second.getCounter();
        }
    }

    // printing elements to the file
    printElements(words, maxWord, longestRef);
}