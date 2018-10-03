# WordAutoComplete

A word auto complete program.

When run, the user is prompted to either
1. Enter their own words to build their own dictionary, or
2. Use a pre-assembled dictionary of words.

Once the input is recived, the program will create a trie of letters. Traversing this trie can give you any word from the dictionary (no more, no less.)

The user then enters some text. The program will then recursivly traverse the trie, and output every word that could potentially match the user's given text (i.e. the rest of the trie after you traversed the trie until you matched the user's input.)
