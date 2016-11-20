#include "charmap.h"

using namespace std;

string loadSeed(string);
void gen_char_occ(string);
map<char, char> load_char_occ();

string loadSeed(string infile)
{
	string _text = "";
	ifstream fin(infile);
	if (!fin) {
		cerr << "Error opening input file \"" << infile << "\"!" << endl;
        return "";
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

void gen_char_occ(string infile)
{
	string _text = loadSeed(infile);
	map<char, int> next_count;
	ofstream outfile("occ_map.txt");
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
					next_count.insert(pair<char, int>(_text[i + 1], 1));
				}
				else //if the key does exist
				{
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

	for (pair<char, char> i : next_letter)
		outfile << get<0>(i) << " " << get<1>(i) << endl;

	outfile.close();
}

map<char,char> load_char_occ()
{
	string infile = "occ_map.txt";
	ifstream fin(infile);
	if (!fin) {
		cerr << "Error opening input file \"" << endl;
	}

	map<char, char> char_map;
	// get all strings; extra whitespace will be ignored
	while (!fin.eof()) {
		char s;
		char t;
		fin >> s >> t;
		char_map.insert(pair<char, char>(s, t));
	}

	fin.close();
	return char_map;
}

