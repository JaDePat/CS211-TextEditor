Milestone 6 Design Diary

In this milestone I didn't run into that many issues. I would say the hardest part of this milestone was recording the frequency at which a word appears on the screen. But once I had that number it was pretty simple to put the words and frequencies into a priority queue and then assign each word a binary value. I wrote a function for converting decimal to binary using integer division and remainders. 

To improve on this project, I would not use an incrementing binary representation for each word. Using an incrementing binary representation increases in size quickly and once you get past one "bit" then half of the possible binary representations are ignored. For example I would want 0 1 00 01 10 as a representation instead of 0 1 10 11 100. In order to do this I would need a function to read the binary string and if the string is all 1's, then it would add a character and start back at 0.

My advice for other students working on this milestone would be to make yourself real familiar with unordered_maps since they're an integral part of this milestone. While I was working on this milestone I always had the cplusplus.com unordered_map page open. It was a tremendous help in my working with unordered_maps.

For milestone 6 gif:

docs/Text Editor Milestone 6.gif

https://github.com/JaDePat/CS211-TextEditor/blob/master/docs/Text%20Editor%20Milestone%206.gif
