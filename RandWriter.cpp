// Copyright 2021 Peter Nguyen
/*
Last Updated: 11/29/21
RandWriter.cpp: Implementation file for a class that creates
              a markov model from a string and predicts
              the next character(s) from a starting text.
*/
#include <cfloat>
#include <algorithm>
#include <stdexcept>
#include <random>
#include <iomanip>
#include <vector>
#include "RandWriter.h"

// Constructor takes in a string and int for order
RandWriter:: RandWriter(std::string text, int x) {
    k = x;
    map<string, map<char, int>>::iterator it;
    string kgram;
    char c;
    // Find all kgrams of order x
    for (int i = 0; i < text.size(); i++) {
        // Wrap around text
        if ((i+k) > text.size()) {
            kgram = text.substr(i, text.size()-i);
            kgram += text.substr(0, (k-(text.size()-i)));
            c = text[(k-(text.size()-i))+1];
        } else {
            kgram = text.substr(i, k);
            if ((i+k) == text.size()) c = text[0];
            else
                c = text[i+k];
        }

        it = markov.find(kgram);
        // If k-gram already exists
        if (it != markov.end()) {
            // if char exists in inner map
            if (it->second.find(c) != it->second.end())
                it->second.find(c)->second++;
            // If it doesn't exist, add to inner map
            else
                it->second[c] = 1;
        } else {  // If kgram does exist
            markov[kgram] = map<char, int> {{c, 1}};
        }
    }
}

// Return order k
int RandWriter::order_k() const {
    return k;
}

// Return frequency of a kgram
int RandWriter:: freq(string kgr) const {
    if (kgr.size() != k)
        throw std::runtime_error("freq(string): string is not size of k");
    // If kgram doesn't exist in map return 0
    if (markov.find(kgr) == markov.end()) return 0;
    map<char, int> m = markov.find(kgr)->second;
    int total = 0;
    // Sum up all values in inner map to get total occurance of kgram
    for (auto it : m) {
        total = total + it.second;
    }

    return total;
}

// Return frequency of a given character after given kgram
int RandWriter:: freq(string s, char c) {
    if (s.size() != k)
        throw std::runtime_error("freq(string,char): string is not size of k");
    // If it doesn't exist in map, return 0
    if (markov.find(s) == markov.end()) return 0;
    map<char, int> m = markov.find(s)->second;
    if (m.find(c) == m.end()) return 0;
    // Return value in map
    return m.find(c)->second;
}

// Generate random character based on probability from given string
char RandWriter:: k_rand(string s) {
    if (markov.find(s) == markov.end())
        throw std::runtime_error("k_rand(string): kgram not found");

    // Find map with argument key
    map<char, int> b = markov.find(s)->second;

    // Create a vector and fill it with each occurence of each k+1 gram
    std::vector<char> v;
    map<char, int>:: iterator itr = b.begin();
    for (itr; itr != b.end(); ++itr) {
        for (int i = 0; i < itr->second; ++i) {
            v.push_back(itr->first);
        }
    }

    // Generate random number in range 0 to v.size()-1
    std::random_device  rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dis(0, v.size()-1);
    double rNum = dis(mt);

    // Return random index of vector
    return v[rNum];
}

// Generate a string of length l
string RandWriter::generate(string s, int l) {
    if (s.size() != k)
        throw std::runtime_error("generate(): the string is not of k order");
    string r = s;
    char c;
    // Loop until l iterations, using k_rand
    // Remove first character from string and add next char to end
    for (int i = 0; i < (l+s.size()); ++i) {
        c = k_rand(s);
        s.erase(0, 1);
        s = s+c;
        r = r + c;
    }
    return r;
}

// Overload insertion operator
ostream& operator<<(ostream& out, const RandWriter& r) {
    auto pad = [](RandWriter t) {
        if (t.order_k() > 6) return t.order_k()+1;
        else return 7;
    };
    out << "Order: " << r.order_k() << std::endl;
    // Pad with spaces if the order_k is > 6
    out << std::left << std::setw(pad(r));
    out << "kgram" << " freq ";

    // Print out active alphabet except last character (space)
    for (int i = 0; i < r.alpha.size()-1; ++i) {
        out << std::setw(3) << r.alpha[i];
    }

    // Print unicode for space and print newline as string
    out << std::setw(3) << "␣" << "  \\n" << std::endl;

    // Loop through each kgram
    for (auto m =r.markov.begin(); m != r.markov.end(); ++m) {
        string kg = m->first;
        // Look for new line character and replace literal with string
        // So the kgrams with \n don't get printed on 2 lines
        if (kg.find('\n') != string::npos) {
            int pos = kg.find('\n');
            kg.erase(pos, 1);
            kg.insert(pos, "\\n");
        }
        out << std::left << std::setw(pad(r));
        out << kg << " ";
        out << std::left << std::setw(5) << r.freq(m->first);
        // Print out each kgram+1 on alphabet string
        for (int i = 0; i < r.alpha.size(); ++i) {
            if (m->second.find(r.alpha[i]) == m->second.end())
                out << std::setw(3) << 0;
            else
                out << std::setw(3) << m->second.find(r.alpha[i])->second;
        }
        // Find newline kgram+1
        out << std::setw(3) << m->second.find('\n')->second;
        out << std::endl;
    }
    return out;
}
