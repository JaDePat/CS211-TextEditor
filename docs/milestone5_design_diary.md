Design Diary 

For me, this has been the toughest milestone to complete. Now that we're well into this semester, we are obviously using data structures that I have never worked with before. A trie tree is a data structure that had me very confused when trying to implement it. I could understand a trie tree conceptually but I couldn't figure out how to actually code it into our text editor. So, I created another project where I copied over the TrieNode.h and Trie.h header files and created a main. It was easier and for the best to create another project to practice and struggle with the trie tree. I managed to get the addWord function working but I could not manage the same for the search function. After struggling with the search function for a few days, I began looking at others' code and how they did it. After looking at the other code I was able to understand how to search the tree and that I needed a helper function. I finally got the functions needed for this milestone to work and then it was on to actually implementing them in the text editor. 

The first step in implementing auto-complete was to descide how I would keep track of the current word. To do that I used a vector of chars that would clear itself when the user pressed enter, space, or used the auto-complete function. I was stuck on converting my vector of chars into a string because I originally had ctrl('o') as the buttons for popping up the auto-complete box and the symbol for ctrl was pushed back into the vector. So, when converting it to a string, the string always had '^' at the end, which would screw up my search function. I changed the opening of the auto-complete box to be alt + o, and that fixed that problem.

My advice for future students working on this milestone is to work with others. I was stuck on defining the addWord and search functions for a very long time and looking at someone else's code instantly made it easier to understand. So, teamwork makes the dreamwork.

For milestone gif:

docs/Text Editor Milestone 5.gif
https://github.com/JaDePat/CS211-TextEditor/blob/master/docs/Text%20Editor%20Milestone%205.gif
