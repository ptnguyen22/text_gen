// Copyright 2021 Peter Nguyen
/*
Last Updated: 11/29/21
RandWriter.h: Header file for a class that creates
              a markov model from a string and predicts
              the next character(s) from a starting text.
*/
#ifndef RANDWRITER_H // NOLINT
#define RANDWRITER_H // NOLINT
#include <string>
#include <map>
#include <iostream>

using std::string;
using std::map;
using std::ostream;

class RandWriter {
 public:
    RandWriter(string, int);
    int order_k() const;
    int freq(string) const;
    int freq(string, char);
    char k_rand(string);
    string generate(string, int);
    friend ostream& operator<<(ostream& out, const RandWriter& r);

 private:
    map<string, map<char, int>> markov;
    int k;
    string alpha = "abcdefghijklmnopqrstuvwxyz,./?:;\"'- ";
};
#endif // NOLINT
