// I used PrefixAlgo that you sent on group

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int CHAR_BITS = 8; // Number of bits in a char

vector<string> NDB;

// Function to convert a character to its ASCII binary representation
string charToBinary(char c) {
    return bitset<CHAR_BITS>(c).to_string();
}

// Function to generate prefixes for the given word length
set<string> PrefixAlgo(int length) {
    set<string> prefixes;

    for (int i = 0; i < (1 << length); ++i) {
        string prefix;
        for (int j = length - 1; j >= 0; --j) {
            prefix += ((i >> j) & 1) ? '1' : '0';
        }
        prefixes.insert(prefix);
    }

    return prefixes;
}

// Function to initialize the database with all possible binary strings for a given word length
void initNDB(int length) {
    PrefixAlgo(length);
    for (long long int i = 0; i < (1LL << (length * CHAR_BITS)); ++i) {
        string binaryString;
        for (int j = 0; j < length; ++j) {
            char c = static_cast<char>((i >> (CHAR_BITS * (length - j - 1))) & 0xFF);
            binaryString += charToBinary(c);
        }
        NDB.push_back(binaryString);
    }
}

// Function to complete a word with wildcard characters ('*') to match the specified length
set<string> completeWord(const string& word, int length) {
    set<string> completions;
    string completedWord = word;

    while (completedWord.length() < length) {
        completedWord += '*';
    }
    set<string> prefixes = PrefixAlgo(completedWord.length());
    
    for (const string& prefix : prefixes) {
        completions.insert(completedWord.substr(0, prefix.length()));
    }

    return completions;
}

// Function to delete a word from the DB and insert it into the NDB
void insertIntoDB(const string& word, int length) {
    set<string> completions = completeWord(word, length);

    for (const string& completedWord : completions) {
        string binaryWord;
        for (char c : completedWord) {
            binaryWord += charToBinary(c);
        }
        // Find the word in the Negative database
        auto it = find(NDB.begin(), NDB.end(), binaryWord);
        if (it != NDB.end()) {
            NDB.erase(it);
            cout << "Word '" << completedWord << "' inserted into DB.\n";
        } else {
            cout << "Word '" << completedWord << "' already exists in DB.\n";
        }
    }
}

// Function to delete a word from the DB and insert it into the NDB
void deleteFromDB(const string& word, int length) {
    set<string> completions = completeWord(word, length);

    for (const string& completedWord : completions) {
        string binaryWord;
        for (char c : completedWord) {
            binaryWord += charToBinary(c);
        }
        // Check if the binary representation already exists in NDB
    auto it = find(NDB.begin(), NDB.end(), binaryWord);
    if (it != NDB.end()) {
        cout << "Word '" << word << "' not founded in DB.\n";
    } else {
        NDB.push_back(binaryWord);
        cout << "Word '" << word << "' Deleted from DB.\n";
    }
}
}

int main() {
    int length;
    cout << "Enter the length of the word: ";
    cin >> length;

    // Call initNDB 
    initNDB(length);

    int choice;
    do {
        cout << "\nOptions:\n";
        cout << "1. Insert a word into DB\n";
        cout << "2. Delete a word from DB \n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string word;
                cout << "Enter word to insert into DB: ";
                cin >> word;
                if(word.length() <= length)
                {
                // Convert each character to lowercase
                 for (char& c : word) {
                    if (isupper(c)) {
                        c = tolower(c);
                    }
                 }
                 insertIntoDB(word, length);
                 break;
                }
                else 
                  {
                      cout << "the word is greater than length  ";
                      break;
                  }
                  
            }
            case 2: {
                string word;
                cout << "Enter word to delete from DB : ";
                cin >> word;
                if(word.length() <= length)
                {
                // Convert each character to lowercase
                 for (char& c : word) {
                    if (isupper(c)) {
                        c = tolower(c);
                    }
                 }
                 deleteFromDB(word, length);
                 break;
                }
                else 
                  {
                      cout << "the word is greater than length  ";
                      break;
                  }
            }
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
