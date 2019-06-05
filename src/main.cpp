//
// Created by zygisau on 27/05/2019.
//
#include "classes/WordModel/WordModel.h"
#include "main.h"
#include "functions.h"

int main() {
    mapType words;

    int maxWord = readFromFile(words);

    printElements(words, maxWord);
}

/*
 * TODO: one letter word
 * */