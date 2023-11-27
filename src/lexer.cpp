#include <iostream>
#include <vector>
#include <cctype>
#include <regex>

enum TokenType { // lista de tokens
    NUMBER,
    IDENTIFIER,
    RPAREN,
    LPAREN,
    RBRACE,
    LBRACE,
    RBRACKET,
    LBRACKET,
    EQUALS,
    ARROW,
    COLON,
    SEMICOLON,
    COMMA,
    GT,
    LT,
    BINARYOP,
};

struct Token { // tipo de token
	TokenType type;
	std::string value;

	friend std::ostream& operator<<(std::ostream& os, const Token& obj) {
		os << " type: " << obj.type << ", value: \"" << obj.value << "\" " ;	
		return os;
    }
};

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
	return { type, value };
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
      case '+' || '-' || '*' || '/' || '%': 
        tokens.push_back(token(BINARYOP, shift(sourceCode)));
        break;
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
          while (sourceCode.length() > 0 && isInt(sourceCode[0])){	
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

	return tokens;
}

void printTokens(std::vector<Token> tokens) { // mostra os tokens no terminal
	auto tok = tokens[0];
	std::cout << "{\n" << tok;
	for (int i = 1; i < tokens.size(); i++) {
		tok = tokens[i];
		std::cout << "\t\n" << tok;
	}

	std::cout << "\n}" << std::endl;
}


int main() {
	std::string src;

	std::cout << "Enter the source code: ";
	std::getline(std::cin, src);
	printTokens(tokenize(src));

	return 0;
}
