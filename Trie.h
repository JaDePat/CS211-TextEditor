#pragma once
#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>
#include <cctype>
#include <iostream>

using namespace std;

class Trie
{
private:
	TrieNode* _root = nullptr;

protected:

public:
	Trie()
	{
		_root = new TrieNode{};
	}

	virtual ~Trie()
	{
		//TODO: clean up memory
	}

	//TODO: implement
	void addWord(const string& word)
	{
		TrieNode* _mover = _root;

		for (int i = 0; i < word.length(); i++)
		{
			if (!_mover->hasChild(word[i]))
			{
				_mover->setChild(word[i], new TrieNode(word[i]));
			}
			_mover = _mover->getChild(word[i]);
		}
		_mover->setChild('$', new TrieNode('$'));
	}

	//TODO: implement
	vector<string> search(const string& word)
	{
		TrieNode* _mover = _root;
		vector<string> matches{};
		string _matched_word = word;

		for (int i = 0; i < word.length(); i++)
		{
			if (_mover->hasChild(word[i]))
			{
				_mover = _mover->getChild(word[i]);
			}
			else
				return matches;
		}

		for (auto child : _mover->getChildren())
		{
			if (child.first != '$')
			{
				_matched_word += child.first;
				traversal(word + child.first, matches);
			}
			else
			{
				matches.push_back(_matched_word);
			}
		}

		return matches;
	}

	void traversal(const string& match, vector<string>& matches)
	{
		TrieNode* _mover = _root;
		string temp = match;

		for (int i = 0; i < match.length(); i++)
		{
			if (_mover->hasChild(match[i]))
			{
				_mover = _mover->getChild(match[i]);
			}
		}

		for (auto child : _mover->getChildren())
		{
			if (child.first != '$')
			{
				temp += child.first;
				traversal(match + child.first, matches);
			}
			else
			{
				matches.push_back(match);
			}
		}
	}
};

#endif // !TRIE_H
