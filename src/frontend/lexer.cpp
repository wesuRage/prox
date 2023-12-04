#include <iostream>
#include <vector>
#include "../../includes/lexer.h"

std::string shift(std::string &src) { // remove primeiro caracter de uma string e retorna a mesma
	std::string firstElement(1, src[0]);
	src.erase(src.begin());
	return firstElement;
}

bool isAlpha(char src) { // verifica se é uma letra do alfabeto ou um underscore
	return std::toupper(src) != std::tolower(src) || src == '_';
}

bool isInt(char src){ // verifica se é um numero
	return src >= '0' && src <= '9';
}

bool isSkippable(char src){ // verifica se é um espaço em branco
	return src == ' ';
}

Token token(TokenType type, std::string value) { // gera o objeto de token
	Token tk;
	tk.type = type;
	tk.value = value;
	return tk;
}

std::vector<Token> tokenize(std::string sourceCode) { // classifica os tokens
	std::vector<Token> tokens;
    
	while (sourceCode.length() > 0) {

		switch (sourceCode[0]){
			case '(': tokens.push_back(token(RPAREN, shift(sourceCode))); break;
			case ')': tokens.push_back(token(LPAREN, shift(sourceCode))); break;
			case '{': tokens.push_back(token(RBRACE, shift(sourceCode))); break;
			case '}': tokens.push_back(token(LBRACE, shift(sourceCode))); break;
			case '[': tokens.push_back(token(RBRACKET, shift(sourceCode))); break;
			case ']': tokens.push_back(token(LBRACKET, shift(sourceCode))); break;
			case '<': tokens.push_back(token(LT, shift(sourceCode))); break;
			case '>': tokens.push_back(token(GT, shift(sourceCode))); break;
			case ':': tokens.push_back(token(COLON, shift(sourceCode))); break;
			case ';': tokens.push_back(token(SEMICOLON, shift(sourceCode))); break;
			case ',': tokens.push_back(token(COMMA, shift(sourceCode))); break;
			case '.': tokens.push_back(token(DOT, shift(sourceCode))); break;
			case '+': tokens.push_back(token(PLUS, shift(sourceCode))); break; 
			case '-': tokens.push_back(token(MINUS, shift(sourceCode))); break;
			case '*': tokens.push_back(token(STAR, shift(sourceCode))); break;
			case '/': tokens.push_back(token(SLASH, shift(sourceCode))); break;
			case '%': tokens.push_back(token(MODULUS, shift(sourceCode))); break;
			case '=':
				if (sourceCode[1] == '>'){
					shift(sourceCode);
					shift(sourceCode);
					tokens.push_back(token(ARROW, "=>"));
				} else {
					tokens.push_back(token(EQUALS, shift(sourceCode)));
				}
				break;

			default:
				if (isSkippable(sourceCode[0])) {
					shift(sourceCode);
				} else if (isAlpha(sourceCode[0])){
					std::string ident = "";
					while (sourceCode.length() > 0 && (isAlpha(sourceCode[0]) || isInt(sourceCode[0]))){
						ident += shift(sourceCode);
					}

					tokens.push_back(token(IDENTIFIER, ident));

				} else if (isInt(sourceCode[0])){
					std::string num = "";
					while (sourceCode.length() > 0 && isInt(sourceCode[0]) || sourceCode[0] == '.'){	
						num += shift(sourceCode);
					}

					tokens.push_back(token(NUMBER, num));
				} else {
					std::cout << "Unexpected token: " << sourceCode[0] << std::endl;
					shift(sourceCode);
				}
        			break;
		}
	}
	
	tokens.push_back(token(_EOF, "EOF"));
	return tokens;
}

