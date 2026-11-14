
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

// Structure to store word and document ID
struct Word {
    string word;
    int docID;
};

// Hash Table Size
const int TABLE_SIZE = 37;

// Hash Table using Separate Chaining
class ChainingHashTable {

    vector<list<Word>> table;

    // Custom Hash Function
    int hashFunction(string word) {
        unsigned long long hash = 0;

        for (char ch : word) {
            hash = (hash * 31 + ch) % TABLE_SIZE;
        }

        return hash;
    }

public:

    ChainingHashTable() {
        table.resize(TABLE_SIZE);
    }

    // Insert word into hash table
    void insert(string word, int docID) {

        int index = hashFunction(word);

        table[index].push_back({word, docID});
    }

    // Search word using separate chaining
    bool search(string key, int &comparisons, int &docID) {

        int index = hashFunction(key);

        comparisons = 0;

        for (auto item : table[index]) {

            comparisons++;

            if (item.word == key) {
                docID = item.docID;
                return true;
            }
        }

        return false;
    }
};

// Hash Table using Linear Probing
class ProbingHashTable {

    vector<Word> table;
    vector<bool> occupied;

    // Custom Hash Function
    int hashFunction(string word) {
        unsigned long long hash = 0;

        for (char ch : word) {
            hash = (hash * 31 + ch) % TABLE_SIZE;
        }

        return hash;
    }

public:

    ProbingHashTable() {
        table.resize(TABLE_SIZE);
        occupied.resize(TABLE_SIZE, false);
    }

    // Insert using linear probing
    void insert(string word, int docID) {

        int index = hashFunction(word);

        for (int i = 0; i < TABLE_SIZE; i++) {

            int position = (index + i) % TABLE_SIZE;

            if (!occupied[position]) {

                table[position] = {word, docID};
                occupied[position] = true;

                return;
            }

            // Avoid duplicate entries
            if (table[position].word == word)
                return;
        }

        cout << "Hash table is full!\n";
    }

    // Search using linear probing
    bool search(string key, int &probes, int &docID) {

        int index = hashFunction(key);

        probes = 0;

        for (int i = 0; i < TABLE_SIZE; i++) {

            int position = (index + i) % TABLE_SIZE;

            probes++;

            if (!occupied[position]) {
                return false;
            }

            if (table[position].word == key) {

                docID = table[position].docID;
                return true;
            }
        }

        return false;
    }
};

// Binary Search on sorted word list
bool binarySearch(vector<Word>& words, string key,
                  int &comparisons, int &docID) {

    int low = 0;
    int high = words.size() - 1;

    comparisons = 0;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        comparisons++;

        if (words[mid].word == key) {

            docID = words[mid].docID;
            return true;
        }

        else if (words[mid].word < key) {

            low = mid + 1;
        }

        else {

            high = mid - 1;
        }
    }

    return false;
}

// Display search result
void displayResult(string method, bool found,
                   int docID, int count, string unit) {

    cout << "\n" << method << ":\n";

    if (found) {
        cout << "Word Found!\n";
        cout << "Document ID: " << docID << endl;
    }
    else {
        cout << "Word Not Found!\n";
    }

    cout << unit << ": " << count << endl;
}

// Main Function
int main() {

    // Dictionary containing 30 words
    vector<Word> dictionary = {
        {"algorithm", 101},
        {"array", 102},
        {"artificial", 103},
        {"binary", 104},
        {"computer", 105},
        {"database", 106},
        {"data", 107},
        {"development", 108},
        {"digital", 109},
        {"education", 110},
        {"function", 111},
        {"graph", 112},
        {"hashing", 113},
        {"internet", 114},
        {"java", 115},
        {"machine", 116},
        {"network", 117},
        {"operating", 118},
        {"program", 119},
        {"python", 120},
        {"query", 121},
        {"recursion", 122},
        {"search", 123},
        {"sorting", 124},
        {"software", 125},
        {"structure", 126},
        {"technology", 127},
        {"tree", 128},
        {"variable", 129},
        {"website", 130}
    };

    // Sort dictionary alphabetically for binary search
    sort(dictionary.begin(), dictionary.end(),
         [](Word a, Word b) {
             return a.word < b.word;
         });

    // Create both hash tables
    ChainingHashTable chaining;
    ProbingHashTable probing;

    // Insert all words into both hash tables
    for (auto item : dictionary) {

        chaining.insert(item.word, item.docID);

        probing.insert(item.word, item.docID);
    }

    cout << "====================================\n";
    cout << "       SEARCH ENGINE SIMULATOR\n";
    cout << "====================================\n";

    cout << "\nDictionary contains "
         << dictionary.size() << " words.\n";

    string key;

    cout << "\nEnter word to search: ";
    cin >> key;

    // Search using Binary Search
    int binaryComparisons = 0;
    int binaryDocID = -1;

    bool binaryFound = binarySearch(
        dictionary,
        key,
        binaryComparisons,
        binaryDocID
    );

    // Search using Separate Chaining
    int chainComparisons = 0;
    int chainDocID = -1;

    bool chainFound = chaining.search(
        key,
        chainComparisons,
        chainDocID
    );

    // Search using Linear Probing
    int probes = 0;
    int probeDocID = -1;

    bool probeFound = probing.search(
        key,
        probes,
        probeDocID
    );

    // Display all results
    cout << "\n========== SEARCH RESULTS ==========\n";

    displayResult(
        "Binary Search",
        binaryFound,
        binaryDocID,
        binaryComparisons,
        "Comparisons"
    );

    displayResult(
        "Hash Table - Separate Chaining",
        chainFound,
        chainDocID,
        chainComparisons,
        "Comparisons"
    );

    displayResult(
        "Hash Table - Linear Probing",
        probeFound,
        probeDocID,
        probes,
        "Probes"
    );

    cout << "\n====================================\n";

    return 0;
}
