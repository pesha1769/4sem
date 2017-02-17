#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>

#define AMOUNT 5
#define MAX_WORDS 10000

char punctiation_symbol [] = { '.', ',', '!', ':', ';', '?' };

bool is_punctuation(char last_symbol) 
{
	for (int j = 0; j < sizeof(punctiation_symbol) / sizeof(char); j++)
	{
		if (last_symbol == punctiation_symbol[j])
			return true;
	}
	return false;
}

std::string prepare(const std::string& str)
{
	std::string result = str;
	int last_symbol = str.size() - 1;
	std::transform(str.begin(), str.end(), result.begin(), ::tolower);
	if (is_punctuation(result[last_symbol])) 
	{
		result.pop_back();
	}
	return result;
}


struct Statistic 
{
	int count;
	std::string word;
};

bool compare(const Statistic & a, const Statistic & b) {
	if (a.count != b.count) {
		return a.count > b.count;
	}
	return a.word < b.word;
}

int main()
{
	std::map<std::string, int> m;

	std::ifstream file("file.txt");

	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string word;
			file >> word;
			std::cout << word << "\n";
			word = prepare(word);
			m[word] += 1;
		}
	}

	file.close();

	std::vector<Statistic > str;

	str.resize(MAX_WORDS);

	int i = 0;

	for (auto it : m)
	{
		str[i].word = it.first;
		str[i].count = it.second;
		i++;
	}

	std::sort(str.begin(), str.end(), compare);

	for (i = 0; i < AMOUNT; i++) 
	{
		std::cout << i + 1 << ") " << str[i].word << "  " << str[i].count << "\n";
	}

	return 0;
}