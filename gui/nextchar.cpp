#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

string loadSeed(string);
map<char, char> next_char(string);

int main(){

	string _text = loadSeed("obama.txt");
	map <char,char> next_letter = next_char(_text);


	cin >> _text; //pause
}

string loadSeed(string infile)
{
	string _text = "";
	ifstream fin(infile);
	if (!fin) {
		cerr << "Error opening input file \"" << infile << "\"!" << endl;
		return false;
	}
	string _text_file = infile;

	// get all strings; extra whitespace will be ignored
	ostringstream text;
	while (!fin.eof()) {
		string s;
		fin >> s;
		text << s << ' ';
	}
	fin.close();

	_text = text.str();


	return _text;
}

map<char,char> next_char(string _text)
{

	map<char, int> next_count;
	map<char, char> next_letter;


	for (char current_char = 'a'; current_char <= 'z'; current_char++)
	{
		next_count.clear();
		for (int i = 0; i < _text.size(); i++)
		{
			_text[i] = tolower(_text[i]);
			if (_text[i] == current_char)
			{
				//if the key doesn't exist
				if (!next_count.count(_text[i + 1]))
				{
					//cout << "added " << _text[i + 1] << endl;
					next_count.insert(pair<char, int>(_text[i + 1], 1));
				}
				else //if the key does exist
				{
					//cout << "incremented " << _text[i + 1] << endl;
					next_count[_text[i + 1]]++;
				}
			}
		}

		int max = 0;
		char charmax = 'a';
		for (char i = 'a'; i <= 'z'; i++)
		{
			if (next_count[i] > max)
			{
				max = next_count[i];
				charmax = i;
			}
		}

		next_letter.insert(pair<char, char>(current_char, charmax));

	}
	return next_letter;
}
