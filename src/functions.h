//
// Created by zygisau on 27/05/2019.
//

#ifndef OBJ_5_FUNCTIONS_H
#define OBJ_5_FUNCTIONS_H

int stringLength(const string& word) {
    return std::count_if(word.begin(), word.end(),
                  [](char c) { return (static_cast<unsigned char>(c) & 0xC0) != 0x80; } );
}

void findRemovePunctuation(string& word, const int pos) {
    // firstly erase all punctuation marks that are known by a built-in function
    if (ispunct(word[pos]))
        // erase that symbol
        word.erase(pos, 1);

    // search for non char type symbols — “ ”    ex. „SEB“
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
        // erase symbols
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

    // try to match the string with the regular expressions
    return (std::regex_match(link, httpsPattern) || std::regex_match(link, wwwPattern));
}

bool isPunctMark(const string& word) {
    // punctuation mark by its own could be [1;3] characters long (spaces included)
    if (word.length() <= 3) {
        std::size_t found = word.find("—");
        if (found == std::string::npos) found = word.find("–"); // looks like the same but aren't
        if (found == std::string::npos) found = word.find('-');
        if (found == std::string::npos) found = word.find(' '); // if it's just a space
        // if it's only a punctuation mark (found equals something, not npos), return true
        return found != std::string::npos;
    }
    return false;
}

u32string toUtf (string &word) {
    // define converter
    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>,char32_t> converter;
    // convert the word
    return converter.from_bytes(word);
}

string fromUtf (u32string & string32) {
    // define converter
    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>,char32_t> converter;
    // convert the word
    return converter.to_bytes(string32);
}

void toLowerCase (string& word) {
    // try to make symbols to lower case by a built-in function
    std::transform(word.begin(), word.end(), word.begin(), ::towlower);

    // convert the word to utf-8
    u32string string32 = toUtf(word);

    // checking utf table for letters that are listed this way (Ė-278 ė-279 Ę-280 ę-281)
    for(char32_t& character : string32) {
        if((character >= 255 && character <= 311) || // [ Ā ; ķ ]
           (character >= 313 && character <= 328) || // [ Ĺ ; ň ]
           (character >= 330 && character <= 375))   // [ Ŋ ; ŷ ]
            if (character % 2 == 0) character++; // checking for capital letters

        if(character >= 377 && character <= 382)     // [ Ź ; ž ]
            if (character % 2 != 0) character++; // checking for capital letters, previous pattern changes
    }

    // transform new word back to a normal string
    word = fromUtf(string32);
}

bool processIdentifyWord(string& word) {
    // check if its email
    bool email = isEmail(word);

    // check if the word is only punctuation mark
    if (isPunctMark(word) && !email) return false;

    // delete punctuation
    findRemovePunctuation(word, 0); // first letter
    findRemovePunctuation(word, word.length()-1); // last letter

    // check if the word is a link
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
    // try to insert a new word
    if ( !words.insert( std::make_pair( word, WordModel(ref) ) ).second ) {
        // if it's already in the container
        auto it = words.find(word);
        // add +1
        it->second.addOne();
        // and its reference
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

    // checking if file was successfully opened
    checkFileStream(file);

    string line, word;      // defining variable for word, line
    int ref = 0, maxWord=0; // line number (ref) and the longest word (maxWord)
    // while reading new line from the file is true
    while (std::getline(file,line)) {
        istringstream lineStream(line);
        ref++; // iterating new line
        // while line has words
        while (lineStream >> word) {
            // first string from the file always has (or potentially could have nbsp character)
            removeNotBreakSpaceChar(word);

            // if the word matches requirements
            if (processIdentifyWord(word)) {
                // insert it to the container
                insertWord(words, word, ref);
                // check if it's longer than others
                maxWord = compareSizes(maxWord, word);
            }
        }
    }
    file.close();
    // return the longest word
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
    string refs; // var for the string of references

    // iterate through all words in the map
    for(auto& elem : words) {
        // if the word was used more than one time
        if (elem.second.getCounter() > 1) {
            // print it
            resultFile << std::left << setfill(' ') << elem.first << setw(maxWord - stringLength(elem.first) + 10)
                       << std::right << elem.second.getCounter()
                       << "     " << makeRefsString(elem.second.getReference()) << endl;
        }
    }
    resultFile.close();
}

#endif //OBJ_5_FUNCTIONS_H
