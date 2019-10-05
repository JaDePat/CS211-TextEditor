#ifdef _WIN32
//Windows includes
#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#else
//Linux / MacOS includes
#include <curses.h>
#endif
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

#define ctrl(x)			((x) & 0x1f)

//initialized variables
int num_rows = 0;      
int num_cols = 0;      
int top = 0;                         
int sub_rows = 0;      
int sub_cols = 0;      
int y = 0;
int x = 0;
WINDOW* sub = nullptr; 

//array of character for catching input string
char input[80];
vector<vector<char>> saver(0);
vector<char> char_saver(0);

//initialization of files
ifstream myfile;
ofstream output_file;

//function for typing to the window
void typing();

//function for scrolling down
void scrollDown();

//function for scrolling up
void scrollUp();

//displays file contents
void fileContents();

int main(int argc, char* argv[])
{

	//2 args means 2nd arg is file name
	//allows user to open file from the command line
	/*ifstream commandFile;
	if (argc == 2)
	{
		commandFile.open(argv[1]);
		char contents;
		while (commandFile.good() == true)
		{
			commandFile.get(contents);
			addch(contents);
		}

		if (commandFile.is_open() == false)
		{
			//create that file for later
		}
	}*/

	WINDOW* main_window = nullptr;

	//initialize screen, begin curses mode
	main_window = initscr();

	//take up most of the screen
	getmaxyx(main_window, num_rows, num_cols);

	//creates border 
	wborder(main_window, 0, 0, 1161, 0, 0, 0, 0, 0);

	//creates new windwo to be typed in
	sub_rows = num_rows - 3;
	sub_cols = num_cols - 2;
	sub = newwin(sub_rows, sub_cols, 2, 1);
	keypad(sub, TRUE);

	cbreak();

	//displays cursor
	curs_set(2);

	//adds message and refreshes screen
	mvwaddstr(main_window, 1, 1, "Press ESC to quit");
	mvwaddstr(main_window, 1, num_cols - 31, "Press CTRL + s to save changes");
	wrefresh(main_window);

	mvwaddstr(sub, 0, 0, "Type name of file and press enter: ");
	wrefresh(sub);

	//gets the string for the file name
	wgetstr(sub, input);

	//allows user to open and display a file
	myfile.open(input);
	char file_chars;
	if (myfile.is_open())
	{
		while (myfile.good() == true)
		{

			//collects the characters from the file
			myfile.get(file_chars);
			char_saver.push_back(file_chars);

			//pushes back the vector of characters into the vector of vectors
			if (file_chars == '\n')
			{
				saver.push_back(char_saver);
				char_saver.clear();
			}

			if (char_saver.size() == sub_cols)
			{
				saver.push_back(char_saver);
				char_saver.clear();
			}
		}

		//adds the final line into the 2d vector
		saver.push_back(char_saver);
		char_saver.clear();

		//closes the file
		myfile.close();
	}
	else
	{
		string failOpen = "The file did not open or does not exist.";
		strcpy_s(input, failOpen.c_str());
		wprintw(sub, input);
	}

	//adds contents of the file to the screen
	fileContents();

	//lets user type
	typing();

	//saves changes to the text file
	output_file.open(input);
	for (int i = 0; i < saver.size(); i++)
	{
		for (int j = 0; j < saver[i].size(); j++)
		{
			output_file << saver[i][j];
		}
	}
	output_file.close();

	endwin();

}

void typing()
{

	//gets initial character before loop
	int result = ' ';

	//lets user type in the window
	while (result != 27)
	{
		noecho();
		result = wgetch(sub);
		getyx(sub, y, x);

		//cases for the caught character
		switch (result)
		{

			//Lets the user backspace and delete characters
		case 8:
			wprintw(sub, "\b");
			wprintw(sub, " ");
			mvwaddch(sub, y, x, result);
			break;

			//custom enter key
		case 10:
			y++;
			x = 0;
			wmove(sub, y, x);
			break;

			//arrow keys
		case KEY_UP:
			
			//Moves the cursor up and scrolls through text
			scrollUp();

			break;
		case KEY_DOWN:
			
			//Moves the cursor down and scrolls through text
			scrollDown();

			break;
		case KEY_RIGHT:
			x++;
			wmove(sub, y, x);
			break;
		case KEY_LEFT:
			x--;
			wmove(sub, y, x);
			break;
		case ctrl('s'):

			//more robust form of saving
			/*for (int i = 0; i < num_rows; i++)
			{
				for (int j = 0; j < sub_cols && char(mvwinch(sub, i, j)) != '\n'; j++)
				{
					char_saver.push_back(char(mvwinch(sub, i, j)));
				}
				char_saver.push_back('\n');
				saver.push_back(char_saver);
				char_saver.clear();
			}
			for (int i = 0; i < saver.size(); i++)
			{
				for (int j = 0; j < saver[i].size(); j++)
				{
					cout << saver[i][j];
				}
			}*/

			//saves changes to the text file
			/*output_file.open(input);
			for (int i = 0; i < saver.size(); i++)
			{
				for (int j = 0; j < saver[i].size(); j++)
				{
					output_file << saver[i][j];
				}
			}
			output_file.close();
			mvwaddstr(sub, sub_rows - 1, sub_cols - 12, "File saved.");
			wmove(sub, y, x);*/
			break;

		default:

			//moves the cursor down when user gets to the side of the screen
			if (x == sub_cols)
			{
				y++;
				x = 0;
				wmove(sub, y, x);
			}

			mvwaddch(sub, y, x, result);

		}

		//allows editing of text
		if (result != KEY_UP && result != KEY_DOWN && result != KEY_LEFT && result != KEY_RIGHT
			&& result != 10 && result != 27)
		{
			getyx(sub, y, x);
			int edit_y = y + top;
			int edit_x = x - 8;
			if (edit_x < 0)
				edit_x = 7 + edit_x;
			saver[edit_y][edit_x] = result;
		}

		wrefresh(sub);
	}
}

void scrollDown()
{
	if (saver.size() > sub_rows)
	{
		y++;
		wmove(sub, y, x);

		//allows user to scroll down
		if (y == sub_rows)
		{
			wclear(sub);
			wmove(sub, 0, 0);
			int newTop = top + 1;
			int bottom = sub_rows + newTop;
			for (int i = newTop; i < bottom && i < saver.size(); i++)
			{
				for (int j = 0; j < saver[i].size(); j++)
				{
					waddch(sub, saver[i][j]);
				}
			}
			wmove(sub, sub_rows - 1, x);
			top++;

			//keeps top from increasing past size of vector
			if (top == saver.size())
			{
				top--;
			}

		}
	}
	else
	{
		y++;
		wmove(sub, y, x);
	}
	
	wrefresh(sub);
}

void scrollUp()
{
	if (saver.size() > sub_rows)
	{
		y--;
		wmove(sub, y, x);

		//allows user to scroll up
		if (y < 0)
		{
			wclear(sub);
			wmove(sub, 0, 0);
			int newTop = top - 1;
			if (top == 0)
			{
				newTop = 0;
			}
			for (int i = newTop; i < (sub_rows + newTop) && i < saver.size(); i++)
			{
				for (int j = 0; j < saver[i].size(); j++)
				{
					waddch(sub, saver[i][j]);
				}
			}
			wmove(sub, 0, x);
			top--;
			if (top <= 1)
			{
				top = 0;
			}
		}
	}
	else
	{
		y--;
		wmove(sub, y, x);
	}

	wrefresh(sub);
}

void fileContents()
{
	//adds contents of the file to the screen
	if (saver.size() > sub_rows)
	{
		wmove(sub, 0, 0);
		int difference = saver.size() - sub_rows - 2;
		top = difference;
		for (int i = difference; i < saver.size(); i++)
		{
			for (int j = 0; j < saver[i].size(); j++)
			{
				waddch(sub, saver[i][j]);
			}
		}


	}
	else          //Adds contents of file to screen for an input that is less than the
	{                  //the number of rows within the window 
		for (int i = 0; i < saver.size(); i++)
		{
			for (int j = 0; j < saver[i].size(); j++)
			{
				waddch(sub, saver[i][j]);
			}
		}
	}

	wrefresh(sub);
}