#include "../../../includes/NodeType.h"
#include "../../../includes/lexer.h"
#include "./Nodes.cpp"
#include "../lexer.cpp"
#include <vector>
#include <iostream>

class Parser {
	private:
		std::vector<Token> tokens;

		bool not_eof(){
			return this->tokens[0].type != _EOF;
		}

		Token at() {
			return this->tokens[0];
		}

		Statement* parse_stmt() {
			return new StatementExpr(this->parse_expr());
		}

		Expr parse_expr(){
			return this->parse_additive_expr();
		}

		Expr parse_additive_expr() {
			Expr left = this->parse_multiplicative_expr();
			while (this->at().type == PLUS || this->at().type == MINUS) {
				Token op = this->consome();
				Expr right= this->parse_multiplicative_expr();

				BinaryExpr binop(left, op.value.c_str(), right);
				left = binop;
			}
			return left;
		}

		Expr parse_multiplicative_expr() {
			Expr left = this->parse_primary_expr();
			while (this->at().type == SLASH || this->at().type == STAR || MODULUS) { 
				Token op = this->consome();
				Expr right = this->parse_primary_expr();
				BinaryExpr binop(left, op.value.c_str(), right);
				left = binop;
			}
			return left;
		}

		Expr parse_primary_expr(){
			Token tk = this->at();

			switch (tk.type) {
				case IDENTIFIER:
					return Identifier(tk.value);
				case NUMBER:
					if (tk.value.find(".") != std::string::npos) {
						return FloatLiteral(std::stod(tk.value));
					} else {
						return IntLiteral(std::stoi(tk.value));

					}
					//me perdoa, mas n achei tratamento de erros melhor kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
				case LPAREN: {
					this->consome();
					Expr exp = this->parse_expr();
					if (!(this->at().type == RPAREN)) {
						this->error("Malformed expression");
						return Expr();
					} else {
						this->consome();
					}

					return exp;
				}
				case RPAREN:
					     this->error("Malformed expression.");
					     return Expr();
				default:
					     return Expr();
			


			}
		}


		Token consome() {
			Token t = this->at();
			this->tokens.erase(this->tokens.begin());
			return t;
		}

		void error(std::string message) {
			std::cerr << "error: " << message;
		}

	public:
		Program produceAST(std::string sourceCode){
			this->tokens = tokenize(sourceCode);
			Program program({});

			while (this->not_eof()) {
				program.body->push_back(this->parse_stmt());
			}

			return program;
		}
};

int main(){
	Parser parser;
	parser.produceAST("main = () => {};");


	return 0;
}
