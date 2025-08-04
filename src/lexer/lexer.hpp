#ifndef LEXER_H
#define LEXER_H

#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

enum type 
{
	TOKEN_ID,
	TOKEN_INT,
	TOKEN_EQUALS,
	TOKEN_SEMICOLON,
	TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_PAREN
};

struct Token
{
	enum type TYPE;
	string VALUE;
};

string typeToString(enum type TYPE) {
	switch(TYPE) {
	case TOKEN_ID : return "TOKEN_ID";
	case TOKEN_INT : return "TOKEN_INT";
	case TOKEN_EQUALS : return "TOKEN_EQUALS";
	case TOKEN_LEFT_PAREN : return "TOKEN_LEFT_PAREN";
	case TOKEN_RIGHT_PAREN : return "TOKEN_RIGHT_PAREN";
	case TOKEN_SEMICOLON : return "TOKEN_SEMICOLON";
	}
}

class Lexer 
{
	
	public:
	Lexer(string codigo_fuente) {
		fuente = codigo_fuente;
		cursor = 0;
		tamano = codigo_fuente.length();
		actual = codigo_fuente.at(cursor);
		linea_numero = 1;
		characterNumber = 1;
	}

	char advance() {
		if(cursor < tamano) {
			char temp = actual;
			cursor++;
			actual = (cursor < tamano) ? fuente[cursor] : '\0';
			return temp;

		} else {
			return '\0';
		}
	}

	void checkAndSkip() {
		while(actual == ' ' || actual == '\n' || actual == '\t' || actual == '\r') {
			if(actual == '\n') {
				linea_numero++;
				characterNumber = 1;

			} else {
				characterNumber++;
			}
			advance();
		}
	}

	Token * tokenizeID() {
		stringstream buffer;
		buffer << advance();

		while(isalnum(actual) || actual == '_') {
			buffer << advance();
		}

		Token * newToken = new Token();

		newToken->TYPE = TOKEN_ID;
		newToken->VALUE = buffer.str();

		return newToken;

	}

	Token * tokenizeSPECIAL(enum type TYPE) {
		Token * newToken = new Token();
		newToken->TYPE = TYPE;
		newToken->VALUE = string(1, advance());

		return newToken;

	}

	Token * tokenizeINT() {
		string buffer;
		while(isdigit(actual)) {
			buffer += advance();
		}

		Token * newToken = new Token();
		newToken->TYPE = TOKEN_INT;
		newToken->VALUE = buffer.c_str();

		return newToken;

	}

	vector<Token *> tokenize() {
		vector<Token *> tokens;
		bool notEOF = true;
		while(cursor < tamano && notEOF) {
			checkAndSkip();
			if(isalpha(actual) || actual == '_') {
				tokens.push_back(tokenizeID());
				continue;
			}

			if(isdigit (actual)) {
				tokens.push_back(tokenizeINT());
				continue;
			}

			switch(actual) {
				case ';': {
					tokens.push_back(tokenizeSPECIAL(TOKEN_SEMICOLON));
					break;
				}

				case '=': {
					tokens.push_back(tokenizeSPECIAL(TOKEN_EQUALS));
					break;
				}

				case '(': {
					tokens.push_back(tokenizeSPECIAL(TOKEN_LEFT_PAREN));

					break;
				}
				

				case ')': {
					tokens.push_back(tokenizeSPECIAL(TOKEN_RIGHT_PAREN));
					break;
				}

			default:{
				cerr << "ERROR EN LA LÍNEA NÚMERO " << linea_numero << " " << endl;
				cerr << "ERROR, SÍMBOLO INDEFINIDO: " << actual;
				exit(1);
			}
				
				
			}

		}
		return tokens;
	}

	char peak (int offset = 0) {
		if(cursor + offset < tamano) {
			return fuente[cursor + offset];
		
		} else {
			return '\0';
		}
	}

	private:
	string fuente;
	int cursor;
	int tamano;
	char actual;
	int linea_numero;
	int characterNumber;

};

#endif