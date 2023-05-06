#pragma once

#include <string>
#include "TrieNodeQueue.h"

using namespace std;

namespace Tree {
	class Trie {
	protected:
		TrieNode* root;

		TrieNode* FindNode(string word);
	public:
		Trie();
		~Trie();

		bool IsValidChar(char alphabet);

		int GetWords(string prefix, string*& words); // return length and words
		bool AddWord(string word); // return success
		bool RemoveWord(string word); // return success
		void Clear();
	};
}
