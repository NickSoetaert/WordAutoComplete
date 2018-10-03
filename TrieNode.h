/* 
 * File:   TrieNode.h
 * Author: Nick Soetaert
 *
 * Created on November 19, 2017, 11:37 AM
 */

#ifndef TRIENODE_H
#define TRIENODE_H

#include <vector>
#include <cctype>
using namespace std;

class TrieNode
{
private:
    char _data;
    vector<TrieNode*> _children;

    //For our Trie, we are using the character '$' as a sentinel
    //value to mark the end of a word. It exists at index 26,
    //which is immediately after the character 'Z'.
    static const int sentinel_index = 26; //index 25 == Z

    //Nice helper function to convert a char (upper or lower)
    //into a valid index for our Trie.
    
    //This takes a char, and returns an int that can be used to access _children
    //Note that this is PRIVATE
    int charToIndex(const int &ch) const
    {
        //account for sentinel
        if (ch == '$')
        {
            return sentinel_index;
        }

        //start char 'A' at index 0.
        int index = toupper(ch) - 65; //65 to account for A=65 in Unicode
        return index;
    }

public:
    //initialize an empty node w/ 27 nullptr children
    TrieNode(const char &data = '\0')
    {
        setValue(data);
        _children.resize(27);
        for (int i = 0; i < 27; i++)
        {
            _children[i] = nullptr;
        }
    }
    
    //used in ~Trie
//    void destroyTree(TrieNode*& root){
//        char alphabet = 'A';
//        destroyTree(root->getChild(alphabet)); //to acount for alphabet++
//        while (alphabet <= 'Z') {
//            alphabet++;
//            destroyTree(root->getChild(alphabet));
//            delete root;
//        }
//    }

    void setValue(const char &data)
    {
        _data = toupper(data);
    }

    const char& getValue() const
    {
        return _data;
    }

    char& getValue()
    {
        return _data;
    }

    //Returns true if the current node represents the end of a word.
    bool isWord() const
    {
        return _children[sentinel_index] != nullptr;
    }

    //Returns true when the current node contains the sentinel value $
    bool isSentinel() const
    {
        return _data == '$';
    }

    //returns true when the node has at least one child that's not a nullptr
    bool hasChild(const char &index) const
    {
        return _children[charToIndex(index)] != nullptr;
    }

    //makes the node given as an arg the child of the node you're passing it on
    //Also automatically converts given char to an int for you.
    void setChild(const char &index, TrieNode *node)
    {
        int i = charToIndex(index);
        _children[i] = node;
    }

    TrieNode* getChild(const char &index)
    {
        return _children[charToIndex(index)];
    }

    //returns a list of children.  Null nodes are not included in the list.
    vector<TrieNode*> getChildren()
    {
        vector<TrieNode*> children{};
        for (auto node : _children)
        {
                if (node != nullptr)
                {
                        children.push_back(node);
                }
        }
        return children;
    }

};

#endif /* TRIENODE_H */

