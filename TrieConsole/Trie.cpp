#include "Tree.h"
#include "TrieNodeQueue.h"

using namespace Tree;

Trie::Trie() {
	root = new TrieNode();
}

Trie::~Trie() {
	delete root;
	root = NULL;
}

bool Trie::IsValidChar(const char alphabet) {
	return root->IsValidChar(alphabet);
}

TrieNode* Trie::FindNode(const string word) {
	int length = static_cast<int>(word.length());
	TrieNode* currentNode = root;
	for (int c = 0; c < length && currentNode; c++) {
		currentNode = currentNode->GetChild(word[c]);
	}
	return currentNode;
}

int Trie::GetWords(const string prefix, string*& words) { // return length and words
	//initialize
	words = NULL;
	//
	int returnLength = 0;
	int prefixLength = static_cast<int>(prefix.length());

	TrieNode* currentPrefixNode = FindNode(prefix);
	if (!currentPrefixNode)
		return returnLength;
	//BFS
	TrieNodeQueue queue;
	queue.Push(currentPrefixNode);
	TrieNode* currentNode;
	while (!queue.IsEmpty()) {
		currentNode = queue.Pop();
		if (currentNode->IsLeaf()) {
			string* oldWords = words;
			words = new string[returnLength + 1];
			if (oldWords) {
				for (int i = 0; i < returnLength; i++)
					words[i] = oldWords[i];
				delete[] oldWords;
			}
			words[returnLength] = currentNode->GetWord();
			returnLength++;
		}
		if (currentNode->HasChild()) {
			TrieChildNode* childNode = currentNode->GetFirstChildNode();
			while (childNode) {
				queue.Push(childNode->node);
				childNode = childNode->next;
			}
		}
	}
	return returnLength;
}

bool Trie::AddWord(const string word) { // return success
	int length = static_cast<int>(word.length());
	TrieNode* currentNode = root;
	TrieNode* lastNode = NULL;
	for (int c = 0; c < length; c++) {
		int mapIndex;
		currentNode->AddChildAndGetMapIndex(word[c], mapIndex);
		if (mapIndex > -1)
			lastNode = currentNode = currentNode->GetChildByMapIndex(mapIndex);
		else
			return false;
	}
	if (lastNode)
		lastNode->ChangeToLeaf();
	return true;
}

bool Trie::RemoveWord(const string word) { // return success
	TrieNode* currentNode = FindNode(word);
	TrieChildNode* currentChildNode = currentNode->GetThisChild();
	if (!currentNode->IsLeaf())
		return false;
	if (currentNode->HasChild()) {
		currentNode->ChangeToNoLeaf();
		return true;
	}
	//is leaf but no child
	if (currentNode = currentNode->GetParent()) {
		currentNode->DeleteChild(currentChildNode);
		currentChildNode = currentNode->GetThisChild();
		while (currentNode != root
			&& (!currentNode->IsLeaf() && !currentNode->HasChild())
			) {
			currentNode = currentNode->GetParent();
			currentNode->DeleteChild(currentChildNode);
			currentChildNode = currentNode->GetThisChild();
		}
		return true;
	}
	return false;
}

void Trie::Clear() {
	delete root;
	root = new TrieNode();
}
