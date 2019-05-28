//
// Created by zygisau on 27/05/2019.
//

#ifndef OBJ_5_FUNCTIONS_H
#define OBJ_5_FUNCTIONS_H

void findRemovePunctuation(string& word, const int pos) {
    if (ispunct(word[pos]))
        word.erase(pos, 1);

    // search for non char type symbols — “ ”    „SEB“
    std::size_t found = word.find("“");
    string mark = "“";
    if (found == std::string::npos) {
        found = word.find("”");
        mark = "”";
    }
    if (found == std::string::npos) {
        found = word.find("„");
        mark = "„";
    }
    if (found != std::string::npos) {
        word.erase(found, mark.length());
    }
}

bool isEmail(const std::string& email)
{
    // define a regular expression
    const std::regex pattern
            ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    // try to match the string with the regular expression
    return std::regex_match(email, pattern);
}

bool isPunctMark(const string& word) {
    std::size_t found = word.find("—");
    if (found == std::string::npos) found = word.find("–"); // looks like the same but aren't
    if (found == std::string::npos) found = word.find('-');
    if (found == std::string::npos) found = word.find(' '); // if it's just a space
    return found != std::string::npos;
}

void toLowerCase (string& word) {
    std::transform(word.begin(), word.end(), word.begin(), ::towlower);
}

bool processIdentifyWord(string& word) {
    if (isEmail(word))
        return true;

    // check if the word is only punctuation mark
    if (isPunctMark(word)) return false;

    // delete punctuation
    findRemovePunctuation(word, 0); // first letter
    findRemovePunctuation(word, word.length()-1); // last letter

    // make lowercase
    toLowerCase(word);

    // if everything is alright
    return true;
}

void checkFileStream(const ifstream& file) {
    if(!file.is_open()) {
        printf ("Error while opening the file");
        exit (EXIT_FAILURE);
    }
}

void readFromFile(mapType& words) {
    ifstream file("../textFiles/source_1.txt");

    checkFileStream(file);

    string line, word;
    while (std::getline(file,line)) {
        istringstream lineStream(line);

        while (lineStream >> word) {
            if (processIdentifyWord(word))
                ++words[word];
        }
    }
    file.close();
}

void printElements (const mapType& words) {
    ofstream resultFile("result.txt");

    for(auto& elem : words) {
        resultFile << elem.first << " " << elem.second << "\n";
    }
    resultFile.close();
}

#endif //OBJ_5_FUNCTIONS_H
