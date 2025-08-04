#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>

#include "lexer/lexer.hpp"

using namespace std;

int main(int argc, char ** argv) {
	if(argc < 2) {
		cout << "Por favor, pasa el archivo .acew de código fuente." << endl;
		exit(1);
	}
	
	ifstream archivo_codigo (argv[1]);

	string buffer;

	char temp;

	while(archivo_codigo.get(temp)) {
		buffer += temp;
	}

	string codigo_fuente = buffer.c_str();

	Lexer lexer(codigo_fuente);

	vector<Token *> tokens = lexer.tokenize();

	int contador = 0;

	for(Token * temp : tokens) {
		contador++;
		cout << contador << ") " << temp->VALUE << " " << typeToString(temp->TYPE) << endl;
	}

	return 0;


}