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

    // printing elements to the file
    printElements(words, maxWord);
}