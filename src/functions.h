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

//    for (int i=0; i<word.length(); i++) {
//        if ((int)word[i]
//    }
}

bool processIdentifyWord(string& word) {
    bool email = isEmail(word);

    // check if the word is only punctuation mark
    if (isPunctMark(word) && !email) return false;

    // delete punctuation
    findRemovePunctuation(word, 0); // first letter
    findRemovePunctuation(word, word.length()-1); // last letter

    // make lowercase
    if(!email) toLowerCase(word);

    // if everything is alright
    return true;
}

void checkFileStream(const ifstream& file) {
    if(!file.is_open()) {
        printf ("Error while opening the file");
        exit (EXIT_FAILURE);
    }
}

void insertWord(mapType& words, const string& word, int& ref) {
    if ( !words.insert( std::make_pair( word, WordModel(ref) ) ).second ) {
        auto it = words.find(word);
        it->second.addOne();
        it->second.addReference(ref);
    }
}

int compareSizes(int& oldLength, const string& newStr) {
    if (oldLength < newStr.length())
        return newStr.length();
    return oldLength;
}

int readFromFile(mapType& words) {
    ifstream file("../textFiles/source_1.txt");

    checkFileStream(file);

    string line, word;
    int ref = 0, maxWord=0;
    while (std::getline(file,line)) {
        istringstream lineStream(line);
        ref++;
        while (lineStream >> word) {
            if (processIdentifyWord(word)) {
                insertWord(words, word, ref);
                maxWord = compareSizes(maxWord, word);
            }
        }
    }
    file.close();
    return maxWord;
}

string makeRefsString (const vector<int>& references) {
    string refs;
    for (int ref : references) {
        refs += " ";
        refs += std::to_string(ref);
    }

    return refs;
}

void printElements (const mapType& words, const int& maxWord) {
    ofstream resultFile("result.txt");
    string refs;

    for(auto& elem : words) {
        refs = makeRefsString(elem.second.getReference());
        resultFile << fixed << setw(maxWord) << setfill(' ') << std::left << elem.first << " "
                    << elem.second.getCounter() << " "
                    << fixed << setfill('.') << std::right << setw(40) << refs << "\n";
    }
    resultFile.close();
}

#endif //OBJ_5_FUNCTIONS_H
