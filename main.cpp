#include <bits/stdc++.h>
using namespace std;

set<string> stopWords = {
    "the","is","in","at","of","a","and","to","on","for","with","as",
    "by","an","be","this","that","it","from","or"
};

string toLower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

vector<string> splitSentences(const string &text) {
    vector<string> sentences;
    string temp;
    for (char c : text) {
        temp += c;
        if (c == '.') {
            sentences.push_back(temp);
            temp.clear();
        }
    }
    return sentences;
}

vector<string> splitWords(string s) {
    vector<string> words;
    string word;
    s = toLower(s);
    for (char c : s) {
        if (isalpha(c)) word += c;
        else {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) words.push_back(word);
    return words;
}

int main() {
    ifstream file("input.txt");
    if (!file) {
        cout << "Error: input.txt not found\n";
        return 0;
    }

    string text, line;
    while (getline(file, line))
        text += line + " ";

    vector<string> sentences = splitSentences(text);
    unordered_map<string, int> freq;

    for (string s : sentences) {
        vector<string> words = splitWords(s);
        for (string w : words) {
            if (stopWords.find(w) == stopWords.end())
                freq[w]++;
        }
    }

    vector<pair<int, string>> scored;
    for (string s : sentences) {
        int score = 0;
        vector<string> words = splitWords(s);
        for (string w : words)
            score += freq[w];
        scored.push_back({score, s});
    }

    sort(scored.begin(), scored.end(), greater<>());

    cout << "---- Summary ----\n";
    for (int i = 0; i < min(3, (int)scored.size()); i++)
        cout << scored[i].second << "\n";

    return 0;
}
