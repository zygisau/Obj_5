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

bool isLink(const std::string& link)
{
    // define a regular expression
    const std::regex httpsPattern
            ("https?:\\/\\/(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");
    const std::regex wwwPattern
            ("[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");

    // try to match the string with the regular expression
    return (std::regex_match(link, httpsPattern) || std::regex_match(link, wwwPattern));
}

bool isPunctMark(const string& word) {
    if (word.length() <= 3) {
        std::size_t found = word.find("—");
        if (found == std::string::npos) found = word.find("–"); // looks like the same but aren't
        if (found == std::string::npos) found = word.find('-');
        if (found == std::string::npos) found = word.find(' '); // if it's just a space
        return found != std::string::npos;
    }
    return false;
}

u32string toUtf (string &word) {
    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>,char32_t> converter;
    return converter.from_bytes(word);
}

string fromUtf (u32string & string32) {
    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>,char32_t> converter;
    return converter.to_bytes(string32);
}

void toLowerCase (string& word) {
    std::transform(word.begin(), word.end(), word.begin(), ::towlower);

    u32string string32 = toUtf(word);

    // checking utf table for letters that are listed this way (Ė-278 ė-279 Ę-280 ę-281)
    for(char32_t& character : string32) {
        if((character >= 255 && character <= 311) || // [ Ā ; ķ ]
           (character >= 313 && character <= 328) || // [ Ĺ ; ň ]
           (character >= 330 && character <= 375))   // [ Ŋ ; ŷ ]
            if (character % 2 == 0) character++; // checking for capital letters

        if(character >= 377 && character <= 382)     // [ Ź ; ž ]
            if (character % 2 != 0) character++; // checking for capital letters, previous pattern changes
//        std::cout << character << std::endl;
//        std::cout << converter.to_bytes(character) << std::endl;
    }
//    for(char32_t character : string32) {
//        std::cout << "Žodis " << converter.to_bytes(character) << std::endl;
//    }
    word = fromUtf(string32);

//    std::cout << word;
}

bool processIdentifyWord(string& word) {
    bool email = isEmail(word);

    // check if the word is only punctuation mark
    if (isPunctMark(word) && !email) return false;

    // delete punctuation
    findRemovePunctuation(word, 0); // first letter
    findRemovePunctuation(word, word.length()-1); // last letter

    bool link = isLink(word);
    // make lowercase
    if(!email && !link) toLowerCase(word);

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

void removeNotBreakSpaceChar(string & word) {
    u32string string32 = toUtf(word);
    u32string nbsp; nbsp = (char32_t)65279;
    size_t pos = string32.find(nbsp);
    if (pos != std::string::npos) {
        string32.replace(pos, nbsp.length(), U"");
        word = fromUtf(string32);
    }
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
            removeNotBreakSpaceChar(word);

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
//    int wordLength;

    for(auto& elem : words) {
        refs = makeRefsString(elem.second.getReference());
//        wordLength = elem.first.length();
//        resultFile << std::left << elem.first << setw(maxWord - wordLength) << std::right << "|" << endl;
        resultFile  << std::left << setw(maxWord + 10) << setfill(' ') << elem.first << " "
                    << elem.second.getCounter() << " "
                    << fixed << setfill('.') << std::right << setw(40) << refs << "\n";
    }
    resultFile.close();
}

#endif //OBJ_5_FUNCTIONS_H
