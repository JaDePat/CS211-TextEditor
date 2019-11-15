#pragma once
#ifndef BINARY_FILE_H
#define BINARY_FILE_H
#include <queue>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

unordered_map<string, string> _binary_mapping{};

string binaryConverter(int n)
{
	int _binary_value = 0;
	string _binary = "";
	stack<int> _bin_holder{};
	if (n == 0)
	{
		return "0";
	}
	while (n != 0)
	{
		_binary_value = n % 2;
		_bin_holder.push(_binary_value);
		n = n / 2;
	}
	while (_bin_holder.empty() == false)
	{
		_binary = _binary + to_string(_bin_holder.top());
		_bin_holder.pop();
	}
	return _binary;
}

unordered_map<string, int> countWords(string words)
{
	//initializations
	unordered_map<string, int> test{};
	string holder{};
	vector<string> _word_holder{};

	//pushes the individual words from the inputted string into a vector of strings
	for (auto character : words)
	{
		if (character == ' ')
		{
			if (holder != "")
			{
				_word_holder.push_back(holder);
			}
			holder = "";
		}
		else
		{
			// creates the word
			holder = holder + character;
		}
	}

	_word_holder.push_back(holder);			//pushes the final word

	//insert the word into an unordered map and count its frequency
	for (int i = 0; i < _word_holder.size(); i++)
	{
		unordered_map<string, int>::iterator got = test.find(_word_holder[i]);
		if (got == test.end())
		{
			//if the word is not found, then it is inserted
			test.insert({ _word_holder[i], 1 });
		}
		else
		{
			//increments the count for a word if found
			test[_word_holder[i]]++;
		}
	}

	//clears the vector of strings
	_word_holder.clear();

	return test;
}

void Compress(string input, string _out_file)
{
	unordered_map<string, int> _the_one;
	string tester = input;
	string catcher;
	string holder = "";
	vector<string> _word_holder{};
	ofstream _file1(_out_file + ".compressed.txt"), _file2(_out_file + ".codes.txt");

	_the_one = countWords(tester);

	priority_queue<pair<int, string>> max_pq{};

	for (pair<string, int> element : _the_one)
	{
		pair<int, string> element2;
		element2 = make_pair(element.second, element.first);
		max_pq.push(element2);
	}

	//put the words and their binary mapping into another unordered map
	int counter = 0;
	while (max_pq.empty() == false)
	{
		catcher = binaryConverter(counter);
		_binary_mapping.insert({ max_pq.top().second, catcher });
		_file2 << max_pq.top().second << "," << catcher << endl;
		max_pq.pop();
		counter++;
	}

	for (auto character : tester)
	{
		if (character == ' ')
		{
			if (holder != "")
			{
				_word_holder.push_back(holder);
			}
			holder = "";
		}
		else
		{
			holder = holder + character;
		}
	}

	_word_holder.push_back(holder);

	// Saves the compressed text
	for (int i = 0; i < _word_holder.size(); i++)
	{
		_file1 << _binary_mapping[_word_holder[i]] << " ";
	}
}

#endif // !BINARY_FILE_H