/* 
 * File:   Trie.h
 * Author: Nick Soetaert
 *
 * Created on November 19, 2017, 12:04 PM
 * 
 * Bug/feature: If no matches for that word are found in dictionary,
 * the program will return all nodes that shared the final node found
*/

#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>
#include <cctype>
using namespace std;

class Trie
{
private:
    TrieNode *_root = nullptr;

    vector<char> buildAlphabet()
    {
        char letter = 'A';
        vector<char> alphabet;
        while(letter < 'Z' + 1){
            alphabet.push_back(letter);
            letter++;
        }
        alphabet.push_back('$');
        return alphabet;
    }
    
    vector<char> alphabet = buildAlphabet(); //contains [A-Z] and $

public:
    Trie()
    {
        _root = new TrieNode{}; //why the {}s? Google aggregate initialization
    }

    //TODO: Implement
    virtual ~Trie()
    {
        //destroyTree(_root);
    }
    
    //Expects a word, and puts it on its current node using addWordHelper
    void addWord(const string &word)
    {
        //addWordHelper returns a TrieNode* that we never use.
        addWordHelper(word, _root);
    }
    

    //Expects a word and a node, and adds that SINGLE WORD.
    //RECURSIVELY does so by creating a new node and giving it a value 
    //(or simply going to said node if one already exists for that letter)
    //at word[i], then incrementing i.
    //then recursively goes to the node it just created and does the same
    //thing until i == word.length()

    //Then returns the ORIGIONAL root node it was given
private:
    int counter = 0;  //KEEP OUTSIDE addWordHelper, else it will be reset itself
public:
    TrieNode* addWordHelper(const string &word, TrieNode* node)
    {
        if(node->isSentinel()){ //base case: no more letters.
            //cout << "end of word!" << endl;
            counter = 0; //reset for next word
            return node; //simply return our original root (why though?) once there are no more nodes to create
        }
        else if(node->getChild(word[counter]) == nullptr){
            TrieNode* newNode = new TrieNode();//create new node
            newNode->setValue(word[counter]); //give this new node a letter
            node->setChild(word[counter], newNode); //make this new node the child of the current node
            //cout<< "Added [" << word[counter] << "] as child to [" 
            //    << node->getValue() << "] (child is nullptr)" << endl;
            counter++;
            addWordHelper(word, newNode); //recursively call
        }
        else{
            //do NOT create a new node
            //do NOT set any nodes as the child of this node
            //cout<< "Did NOT define [" << word[counter] 
            //    << "] as a new child to [" << node->getValue() 
            //    << "], as it was already equal to that." << endl;
            counter++;
            addWordHelper(word, node->getChild(word[counter-1])); //i-1 to offset i++
        }        
    }


    vector<string> search(const string &word)
    {
        //word: word we check for to see if it has any autocompletes
        //_root: the root of the tree
        vector<string> matches; //once a match is found, put it in here. Adam made this val.
        string stringThatIsConcatinated; //string that gets put into matches.
        searchHelper(word, _root, matches, stringThatIsConcatinated);
        return matches;
    }
    
    //Uses an in-order traversal (left center right) for alphabetical order
    //Expects:
    //  a word to look for
    //  a node to search from 
    //  a vector of strings that it can update with pass by ref,
    //  another string to use to concat to, which will then be put into the vector.
private:
    int wordIndex = 0;
public:
    void searchHelper(const string &index, TrieNode* node, vector<string> &matches, string run)
    {
        if(node->getChild(index[wordIndex]) == nullptr){ //base case: we've found the end
            matches = printEntireTree(node, run);
            wordIndex = 0;
        }
        else if(node->getChild(index[wordIndex]) != nullptr){ //node if definitely NOT nullptr
            //node is NOT sentinel, so access the node's index[wordIndex] 
            run += node->getValue(); 
            wordIndex++;
            searchHelper(index, node->getChild(index[wordIndex-1]), matches, run); //-1 to account for wordIndex++, which can't go after recursive call. 
            //^This was the bug that I spent literally 8+ hours on. An off by 1 error. lol.
        } 
        else{ //should never get here
            cout << "Only alphabetical input please." << endl;
            exit(0);
        }
    } //end searchHelper
    
    vector<string> printEntireTree(TrieNode* node, const string toAppend){
        vector<string> dictionary; //once a match is found, put it in here
        string temp;
        printEntireTreeHelper(node, dictionary, temp, toAppend);
        cout << "Number of matches: " << dictionary.size() << endl;
        return dictionary;
    }
    
    void printEntireTreeHelper(TrieNode* node, vector<string> &matches, string run, string toAppend){
        //only do first loop through.
        run+= node->getValue(); //Gee, only took 2 hours to figure this line out (correctly)
        
        for(char letter : alphabet){
            if(node->getChild(letter) != nullptr){
                //a sentinel comes directly before a nullptr
                if((node->getChild(letter))->isSentinel()){
                    string aMatch = toAppend + run;
                    matches.push_back(aMatch);
                } 
                else {
                    printEntireTreeHelper(node->getChild(letter), matches, run, toAppend);
                }
            }
        }
    } //end printEntireTree
    
}; //end class

#endif // !TRIE_H