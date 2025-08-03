#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int ALPHABET_SIZE = 26;


struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

    
    void findAllWords(TrieNode* node, string currentWord, vector<string>& suggestions) {
        if (node->isEndOfWord) {
            suggestions.push_back(currentWord);
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != nullptr) {
                char c = 'a' + i;
                findAllWords(node->children[i], currentWord + c, suggestions);
            }
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

   
    void insert(string word) {
        TrieNode* current = root;

        for (char c : word) {
            int index = c - 'a';
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }

        current->isEndOfWord = true;
    }

   
    vector<string> getSuggestions(string prefix) {
        vector<string> suggestions;
        TrieNode* current = root;

       
        for (char c : prefix) {
            int index = c - 'a';
            if (current->children[index] == nullptr) {
                return suggestions; 
            }
            current = current->children[index];
        }

        
        findAllWords(current, prefix, suggestions);
        return suggestions;
    }
};

int main() {
    Trie trie;

    
    vector<string> dictionary = {
        "apple", "application", "banana", "banquet", "band",
        "cat", "category", "dog", "document", "domain"
    };

    
    for (string word : dictionary) {
        trie.insert(word);
    }

    cout << "Программа автодополнения слов. Введите начало слова (или 'exit' для выхода):\n";

    string input;
    while (true) {
        cout << "\nВведите часть слова: ";
        cin >> input;

        
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "exit") {
            break;
        }

        vector<string> suggestions = trie.getSuggestions(input);

        if (suggestions.empty()) {
            cout << "Вариантов для автодополнения не найдено.\n";
        }
        else {
            cout << "Возможные варианты:\n";
            for (string word : suggestions) {
                cout << "- " << word << "\n";
            }
        }
    }

    cout << "Программа завершена.\n";
    return 0;
}