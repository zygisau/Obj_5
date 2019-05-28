//
// Created by zygisau on 27/05/2019.
//
#include "main.h"
#include "functions.h"

int main() {
    mapType words;

    readFromFile(words);

    printElements(words);
}

/*
 * TODO: utf letters to lowercase
 * TODO: searching for link if(islink()) with regex;
 * */