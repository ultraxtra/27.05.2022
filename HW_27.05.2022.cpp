
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

using std::map;
using std::cout;
using std::string;
using std::endl;

class FrequencyDictionary
{
	map <string, int> countWords;
	void addWord(string word);

public:
	FrequencyDictionary() = default;
	void readFromFile(const char* fname);
	map<string, int>::iterator getMostCom();
	void print();
	void writeToFile(const char* fname);
};

void FrequencyDictionary::addWord(string word)
{
	map<string, int>::iterator it = countWords.find(word);
	if (it != countWords.end())
		it->second++;
	else
		countWords[word] = 1;
}

void  FrequencyDictionary::readFromFile(const char* fname)
{
	std::ifstream file(fname);
	string str;
	if (!file.is_open())
		throw "could not open file";
	while (!file.eof())
	{
		std::getline(file, str);
		char* str_ch = &str[0];
		char* pch = strtok(str_ch, " ,.-:\"!?;");
		while (pch)
		{
			string word(pch);
			char capitalLet = toupper(word[0]);
			word = capitalLet + word.substr(1);
			addWord(word);
			pch = strtok(0, " ,.-:\"!?;");
		}
	}
	file.close();
}

map<string, int>::iterator  FrequencyDictionary::getMostCom()
{
	return std::max_element(countWords.begin(), countWords.end(),
		[](const std::pair<string, int>& p1, const std::pair<string, int>& p2) {
			return p1.second < p2.second; });
}

void FrequencyDictionary::print()
{
	map<string, int>::iterator it = countWords.begin();
	cout << "---------------------------------------------" << endl;
	for (int i = 0; it != countWords.end(); it++, i++)
		cout << it->first << " - " << it->second << endl;
	cout << "---------------------------------------------" << endl;
	map<string, int>::iterator comW = getMostCom();
	cout << "The most common word: " << comW->first << " - " << comW->second << endl;
}

void FrequencyDictionary::writeToFile(const char* fname)
{
	std::ofstream file(fname);
	if (!file.is_open())
		throw "could not open file";
	map<string, int>::iterator it = countWords.begin();
	file << "---------------------------------------------" << endl;
	for (int i = 0; it != countWords.end(); it++, i++)
		file << it->first << " - " << it->second << endl;
	file << "---------------------------------------------" << endl;
	map<string, int>::iterator comW = getMostCom();
	file << "The most common word: " << comW->first << " - " << comW->second << endl;
	file.close();
}

int main()
{
	FrequencyDictionary d;
	try
	{
		d.readFromFile("test_r.txt");
		d.print();
		d.writeToFile("test_w.txt");
	}
	catch (const char* error)
	{
		cout << "Error: " << error;
	}
	return 0;
}
