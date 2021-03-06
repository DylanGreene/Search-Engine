/*
 Accepts input with a list of urls and the included text, as:
 url1 word1 word2...
 url2 word1 word2...
 url3 ...
 ...

 And organizes them into a map of strings and heaps, the heap containing the
 all the urls in which that word occurs and their frequencies.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include "Indexer.h"

using namespace std;

Indexer::Indexer(){}

void Indexer::initializeIndex(){
    string url_line;
    string url;
    string word;
    istringstream ss;
    ifstream fs;
    fs.open(".urlText.txt");
    unordered_map<string, unsigned int> frequency;

    while (!fs.eof()) {

        // get url followed by all the words
        getline(fs, url_line);
        ss.str(url_line);
        ss >> url;

        while (ss >> word) {
            // count the frequency of each word
            if (frequency.find(word) == frequency.end()) {
		/*
                if (indexer.find(word) == indexer.end()) {
                    URLheap heap;
                    indexer[word] = heap;
                    // make a new heap since the word is not in our indexer
                }
		*/
                frequency[word] = 1;
            } else {
                frequency[word] += 1;
            }
        }

        // add those frequency pairs to the wolrd indexer
        for (auto it = frequency.begin(); it != frequency.end(); it++) {
            indexer[it->first].push_back(pair<string, unsigned int>(url, it->second));
            push_heap(indexer[it->first].begin(), indexer[it->first].end(), index_sort());
        }

        url_line.clear();
        url.clear();
        ss.clear();
        frequency.clear();

    }
}

unordered_map<string, URLheap > Indexer::getIndexer(){
    return indexer;
}

void Indexer::toFile() {
	ofstream mapFileStream;
	mapFileStream.open(".mapFile.txt");
	for(auto it = indexer.begin(); it != indexer.end(); it++)
	{
		mapFileStream << it->first << " ";
		for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			mapFileStream << it2->first << " " << it2->second << " ";
		}
		mapFileStream << endl;
	}
	mapFileStream.close();
}
