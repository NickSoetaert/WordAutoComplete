#include <string>
#include <iostream>
#include <fstream>
#include "Trie.h"

using namespace std;

int main(void)
{
    Trie dictionary{}; //this dictionary is a trie
    
    string line = "";
    
    string choice;
    cout << "Would you like to:" << endl 
            << "[1] enter your own input, " << endl
            << "[2] use a pre-written 5000 word dictionary, or" << endl
            << "[3] use a pre-written 20000 word dictionary?" << endl;
    cin >> choice;

    //First loop: learn all words    
    if(choice == "1"){
        cout << "Type a word, then press enter. Enter -1 to end data entry" << endl;
        getline(cin, line);
        while (line != "-1")
        {
            //add word to tree
            line = line + "$";
            dictionary.addWord(line);
            getline(cin, line);
        }
    }
    else if(choice == "2"){
    cout << "Your dictionary: " << endl;
        ifstream largeDict;
        largeDict.open("Words.txt");
        while(largeDict >> line){
            line = line + "$";
            dictionary.addWord(line);
        }
        largeDict.close();
    }
    else if(choice == "3"){
        cout << "Your dictionary: " << endl;
        ifstream largeDict;
        largeDict.open("20k.txt");
        while(largeDict >> line){
            line = line + "$";
            dictionary.addWord(line);
        }
        largeDict.close();
    }
    else{
        cout << "[1], [2] or [3] only please. Goodbye." << endl;
        exit(0);
    }
   
    //Second loop: perform lookups
    
    cout << "Please enter words to search for:" << endl;
    
    getline(cin, line);
    while (line != "-1") //keep as a string
    {
        //search tree
        vector<string> words = dictionary.search(line);
//        cout << "potential matches: [-1 to exit]" << endl;
        for (string word : words)
        {
            cout << word << endl;
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        getline(cin, line);
    }

}
