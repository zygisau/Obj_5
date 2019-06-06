//
// Created by zygisau on 27/05/2019.
//

#ifndef OBJ_5_FUNCTIONS_H
#define OBJ_5_FUNCTIONS_H

int stringLength(const string& word);

void findRemovePunctuation(string& word, const int pos);

bool isEmail(const std::string& email);

bool isLink(const std::string& link);

bool isPunctMark(const string& word);

u32string toUtf (string &word);

string fromUtf (u32string & string32);

void toLowerCase (string& word);

bool processIdentifyWord(string& word);

void checkFileStream(const ifstream& file);

void insertWord(mapType& words, const string& word, int& ref);

int compareSizes(int& oldLength, const string& newStr);

void removeNotBreakSpaceChar(string & word);

int readFromFile(mapType& words);

string makeRefsString (const vector<int>& references);

void printElements (const mapType& words, const int& maxWord);

#endif //OBJ_5_FUNCTIONS_H
