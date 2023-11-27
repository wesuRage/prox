#include "./frontend/lexer.cpp"
#include <iostream>
#include <vector>


int main(){
	std::vector<Token> tok = tokenize("ola mundo");

	for (int i = 0; i < tok.size(); i++){
		std::cout << tok[i] << std::endl;
	}

	return 0;
}
