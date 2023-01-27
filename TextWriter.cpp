// Copyright 2021 Peter Nguyen
/*
TextWriter.cpp: A driver file to test RandWriter
                and display its outputs
*/
#include "RandWriter.h"

int main(int argc, char** argv) {
    string text = "", line;

    // Get file redirect into a string
    // Count new line as space
    while (getline(std::cin, line)) {
        text = text + line + '\n';
    }

    // Create RandWriter
    RandWriter write(text, std::stoi(argv[1]));
    // Display markov state
    std::cout << write << std::endl;
    // Generate text from the first kgram of length from the command line
    std::cout << write.generate
        (text.substr(0, write.order_k()), std::stoi(argv[2]));
    std::cout << std::endl;
}
