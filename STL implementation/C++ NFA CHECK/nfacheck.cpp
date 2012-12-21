#include <iostream>
#include <vector>

using namespace std;

void initTable();
void buildNFA(string regex);
void addState();
bool isMatch(string s);

void initNFA();
void addDummyData();

vector<vector<int> > T;
int finalState = -1;
int nrInput = 10;
int nrState = 0;
string literals = "()+*|[]";

// DEBUG vals
bool testNFA = false;
bool showNFA = false;

int main(int argc, char *argv[])
{
	initTable();
	buildNFA("010111");

	vector<string> inputs;
	inputs.push_back("010111");
	inputs.push_back("0101010101");

	for (int i = 0; i < inputs.size(); i++)
	{
		string input = inputs[i];
		if (isMatch(input))
		{
			cout << input + " Matches!\n";
		}
		else
		{
			cout << input + " Doesn't match!\n";
		}
	}
	
	// hardcoded testing
	if (testNFA)
	{
		initNFA();
		addDummyData();
		
		if (showNFA)
		{
			for(int i = 0; i < T.size(); i++)
			{
				for(int j = 0; j < T[i].size(); j++)
				{
					cout << T[i][j] << " ";
				}
				cout << "\n";
			}
		}

		finalState = 2;

		vector<string> inputs;
		inputs.push_back("011101101");
		inputs.push_back("0101010101");
		inputs.push_back("010101010");
		inputs.push_back("0000000101");

		for (int i = 0; i < inputs.size(); i++)
		{
			string input = inputs[i];
			if (isMatch(input))
			{
				cout << input + " Matches!\n";
			}
			else
			{
				cout << input + " Doesn't match!\n";
			}
		}
	}

	return 0;
}

void initTable()
{
	nrState = 1;
	T.push_back(vector<int>());
	for (int j = 0; j < nrInput; j++)
	{
		T[0].push_back(-1);
	}
}

void buildNFA(string regex)
{
	size_t found;

	for(int i = 0; i < regex.size(); i++)
	{
		string input = "";
		input += regex[i];
		found=literals.find(input);

  		if (found!=string::npos)
  		{
  			switch (regex[i])
  			{
  				case '(':
  					cout << "Found ( at " << i << "\n";
  					break;
  				case ')':
					cout << "Found ) at " << i << "\n";
					break;
				default:
					break;
				//	cout << "Invalid\n";
  			}
  		}
  		else
  		{
			addState();
			int c = regex[i] - '0';
			T[nrState-2][c] = nrState-1;

			if (i == regex.size()-1)
			{
				finalState = nrState - 1;
			}
  		}
	}
}

void addState()
{
	nrState++;
	T.push_back(vector<int>());
	for(int j = 0; j < nrInput; j++)
	{
		T[nrState-1].push_back(-1);
	}
}

void initNFA()
{
	for (int i = 0; i < 3; i++)
	{
		T.push_back(vector<int>());
		for (int j = 0; j < 2; j++)
		{
			T[i].push_back(-1);
		}
	}
}

void addDummyData()
{
	T[0][0] = 1;
	T[0][1] = 2;
	T[1][0] = 1;
	T[1][1] = 2;
	T[2][0] = 1;
	T[2][1] = 2;
}

bool isMatch(string s)
{
	int i = 0;
	int state = 0;

	while (i < s.size())
	{
		int c = s[i] - '0';
		state = T[state][c];
		if (state == -1)
		{
			return false;
		}
		i++;
	}

	if (state == finalState)
		return true;
	return false;
}