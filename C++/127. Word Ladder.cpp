// Word Ladder
/**
Problem - 
Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list.
**/

/**
Approach:
This is a search problem, the key idea is to make the graph and use bredth first search to find the shortest distance from starting word to required word.
**/

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<queue>

using namespace std;

int ladderLength_bfs(string beginWord, string endWord, vector<string>& wordList) 
{
	unordered_set<string> wordSet(wordList.begin(), wordList.end());
	unordered_map<string, int> pathCnt{{{beginWord, 1}}};
	queue<string> q{{beginWord}};
	
	while (!q.empty()) 
	{
		string word = q.front(); q.pop();
		for (int i = 0; i < word.size(); ++i) 
		{
			string newWord = word;
			for (char ch = 'a'; ch <= 'z'; ++ch) 
			{
				newWord[i] = ch;
				if (wordSet.count(newWord) && newWord == endWord) 
					return pathCnt[word] + 1;
				if (wordSet.count(newWord) && !pathCnt.count(newWord)) 
				{
					q.push(newWord);
					pathCnt[newWord] = pathCnt[word] + 1;
				}   
			}
		}
	}
	return 0;
}

int ladderLength_two_end_bfs(string beginWord, string endWord, vector<string>& wordList) 
{
	unordered_set<string> dict(wordList.begin(), wordList.end());
	if (dict.count(endWord) == 0) return 0;

	unordered_set<string> string1 = {beginWord};
	unordered_set<string> string2 = {endWord};
	dict.erase(endWord);
	int step = 0;

	while (!string1.empty() && !string2.empty()) 
	{
	    step++;
	    if (string1.size() > string2.size()) swap(string1, string2);
	    unordered_set<string> temp;

	    for (auto word : string1) 
	    {
	        for (int i=0; i<word.size(); i++) 
	        {
	            char oldChar = word[i];
	            for (char c='a'; c<='z'; c++) 
	            {
	                if (c == oldChar) continue;
	                string newWord = word;
	                newWord[i] = c;
	                if (string2.count(newWord)) 
	                	return step+1;

	                if (dict.count(newWord)) 
	                {
	                    temp.insert(newWord);
	                    dict.erase(newWord);
	                }
	            }
	        }
	    }
	    swap(string1, temp);
	}
	return 0;
}


int main() 
{ 
    vector<string> wordList; 
    wordList.push_back("hot");
    wordList.push_back("dot");
    wordList.push_back("dog");
    wordList.push_back("lot");
    wordList.push_back("log");
    wordList.push_back("cog");
    string beginWord  = "hit"; 
    string endWord  = "cog"; 

    cout << "Length of shortest chain using one end BFS is: "<< ladderLength_bfs(beginWord, endWord, wordList)<<endl;  
   	cout << "Length of shortest chain using two end BFS is: "<< ladderLength_two_end_bfs(beginWord, endWord, wordList)<<endl;  

    return 0;  
}
