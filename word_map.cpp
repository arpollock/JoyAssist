#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;


void gen_word_occ(string infile);
map<string, int> load_word_occ();
string finish_word(string, map<string, int> this_word);

void gen_word_occ(string infile)
{
	ofstream outfile("word_map.txt");
	string _text = loadSeed(infile);
	//convert everything to a vector
	vector<string> text;
	string temp = "";
	for (int i = 0; i < _text.size(); i++)
	{
		_text[i] = tolower(_text[i]);

		if (isalpha(unsigned char(_text[i]))) //randomly breaks at some point
			temp += _text[i];

		if (_text[i] == ' ')
		{
			text.push_back(temp);
			temp = "";
		}
		cout << double(i) / double(_text.size()) << endl;
	}

	map<string, int> this_word;
	//cout << next_letter << endl;

	for (int i = 0; i < text.size(); i++)
	{
		if (!this_word.count(text[i]))
			this_word.insert(pair<string, int>(text[i], 1));
		else
			this_word[text[i]] ++;
	}

	int j = 0;
	for (pair<string, int> i : this_word)
	{
		outfile << get<0>(i) << " " << get<1>(i);
		if (j < this_word.size() - 1)
			outfile << endl;
		j++;
	}

	outfile.close();
}

map<string,int> load_word_occ()
{

	string infile = "word_map.txt";
	ifstream fin(infile);
	if (!fin) {
		cerr << "Error opening input file \"" << endl;
		//return false;
	}

	map<string, int> this_word;


	// get all strings; extra whitespace will be ignored 
	//int i = 0;
	while (!fin.eof()) {
		string s;
		string ss;
		int t = 0;
		getline(fin,s);

		int s_index = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == ' ') {
				s_index = i;
				break;
			}
		}
		ss = s.substr(s_index, s.length());
		s = s.substr(0, s_index);

		t = stoi(ss);
		//fin >> t;
		this_word.insert(pair<string, int>(s, t));
	//	cout << s << "   " << t << endl;
	}
	fin.close();
	return this_word;
}

string finish_word(string current_word, map<string, int> this_word)
{
	int max = 0;
	string finalword = "";
	vector<string> remaining;


	for (pair<string, int> i : this_word)
	{
		if (get<1>(i) > max && get<0>(i).substr(0, current_word.size()) == current_word)
		{
			max = get<1>(i);
			finalword = get<0>(i);
		}
	}

	return finalword;
}
