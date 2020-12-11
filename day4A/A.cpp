#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

enum class TokenType
{
	character,
	identifier,
	keyword,
	str
};

struct Token
{
    string value;
    TokenType type;
	int mapping;

	Token(const string& value, TokenType type) : value(value), type(type), mapping(0) {}
};

vector<Token> parse_program()
{
	string program;
	vector<Token> program_parsat;

	string s;
	while (getline(cin, s))
	{
		if (s.find('#') != string::npos)
			break;
		program += " ";
		program += s;
	}

	int i = 0;
	while (i < program.size())
	{
		//whitespace
		while (i < program.size() && program[i] <= 32)
			i++;

		if (i == program.size())
			break;
		
		if (i < program.size()-1 && program[i] == '/' && program[i+1] == '*') //comment
		{
			while (i < program.size())
			{
				i++;
				if (program[i] == '/' && program[i - 1] == '*')
				{
					i++;
					break;
				}
			}
		}
		else if (program[i] == '\"') //string
		{
			while (i < program.size())
			{
				i++;
				if (program[i] == '\"' && program[i - 1] != '\\')
				{
					program_parsat.emplace_back(R"("")", TokenType::str);
					i++;
					break;
				}
			}
		}
		else if (program[i] == '_' || isalpha(program[i])) //identifier
		{
			int j = i+1;
			while (j < program.size() && (program[j] == '_' || isalnum(program[j])))
				j++;
			program_parsat.emplace_back(program.substr(i, j - i), TokenType::identifier);
			i = j;
		}
		else //caracter random
		{
			string aux = { program[i] };
			program_parsat.emplace_back(aux, TokenType::character);
			i++;
		}
	}
	return program_parsat;
}

map<string, int> mapare1;
map<string, int> mapare2;
int num1, num2;

void mark_keywords(vector<Token>& v)
{
	for (auto& token : v)
		if (token.type == TokenType::identifier && mapare1.count(token.value))
			token.type = TokenType::keyword;
}

void map_identifiers(vector<Token>& v, map<string,int>& mapare, int& num)
{
	for (auto& token : v)
		if (token.type == TokenType::identifier || token.type == TokenType::keyword)
		{
			auto it = mapare.find(token.value);
			if (it == mapare.end())
				it = mapare.insert({ token.value, ++num }).first;
			token.mapping = it->second;
		}
}

int main()
{
	ios::sync_with_stdio(false);

	auto keywords = parse_program();
	for (auto keyword : keywords)
		if (!mapare1[keyword.value])
		{
			mapare1[keyword.value] = ++num1;
			mapare2[keyword.value] = ++num2;
		}
	auto program1 = parse_program();
	auto program2 = parse_program();
	if (program1.size() != program2.size())
	{
		cout << "NO\n";
		return 0;
	}
	mark_keywords(program1);
	mark_keywords(program2);
	map_identifiers(program1, mapare1, num1);
	map_identifiers(program2, mapare2, num2);
	for (int i=0;i<program1.size();i++)
	{
		if (program1[i].type != program2[i].type)
		{
			cout << "NO\n";
			return 0;
		}
		if (program1[i].type == TokenType::identifier || program1[i].type == TokenType::keyword)
		{
			if (program1[i].mapping != program2[i].mapping)
			{
				cout << "NO\n";
				return 0;
			}
		}
		else if (program1[i].value != program2[i].value)
		{
			cout << "NO\n";
			return 0;
		}
	}
	cout << "YES\n";
    return 0;
}
