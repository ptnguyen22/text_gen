/**********************************************************************
 *  readme.txt template                                                   
 *  Random Writer 
 **********************************************************************/

Peter Nguyen
Developed in Ubuntu using the G++ GNU compiler.
Dependencies: SFML --to install: sudo apt-get install libsfml-dev
 
This program implements a markov model that can redirect input from a file and builds a data structure that stores kgrams and kgram+1 and their frequencies. It takes command line arguments for the order k of the markov model and also the length of text to be generated. It uses all this information to guess the next characters from an input string. Uses Google's lint style guide.
Included are sample text files to build the markov model.

 
to run:
./TextWriter < (text file) (k-gram) (# of letters to produce)
example:
./TextWriter < dream.txt 4 1000


