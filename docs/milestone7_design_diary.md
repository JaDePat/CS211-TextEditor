With this milestone I got myself familiar with the debugger in visual studios. Before the quicksort function was fixed in class I tried 
to implement it and found out that it was broken. I used the debugger to go through the function step-by-step and was able to find where
the program was getting stuck. After the function was fixed, it was simple to implement it in the text editor. So, the biggest benefit of
this milestone was using the debugger.

However, the sorting in my text editor is not robust. It will only work correctly the first time that it is used and I believe that is
because of the way I am saving text into the vector that I pass through the function.

Unfortunately, my 2d vector that is used to open files is not generalized, so for several of the milestones I had to create more vectors. 
If I were able to restart this project fresh I would try to make a more generalized 2d vector for typing and opening files. Currently, 
sorting would not work on a file that has been opened, I would have to change the function to pass in a 2d vector.

Another thing that I would add to my text editor is the ability to close/exit out of a file. Currently, if a user opens a file, that file
will be displayed on the screen until the program is closed.

For milestone 7 gif:

docs/Text Editor Milestone 7.gif

https://github.com/JaDePat/CS211-TextEditor/blob/master/docs/Text%20Editor%20Milestone%207.gif
