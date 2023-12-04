#include "../../../includes/NodeType.h"
#include <memory>
#include <vector>

class Expr : public NodeType { };

class BinaryExpr : public Expr {
	public:

		std::unique_ptr<Expr> left;
		const char* op;
		std::unique_ptr<Expr> right;

		BinaryExpr(Expr& left, const char* op, Expr& right) : left(std::make_unique<Expr>(left)), op(op), right(std::make_unique<Expr>(right)) { }
};

class UnaryExpr : public Expr {
	public:
		std::unique_ptr<Expr> operand;
		const char* op;

		UnaryExpr(const char* op, Expr& oper) : operand(std::make_unique<Expr>(oper)), op(op) { }

};

class Identifier : public Expr {
	public:
		std::string symbol;

		Identifier(std::string ident) : symbol(ident) { }
};

class Literal : public Expr { 

};

class IntLiteral : public Literal {
	public:
		int value;

		IntLiteral(int val) : value(val) { }
};

class FloatLiteral : public Literal {
	public:
		double value;

		FloatLiteral(double val) : value(val) { }
};

class Statement : public NodeType {

};

class Program : public NodeType {
	public:
		std::vector<Statement*>* body = nullptr;

		Program(std::initializer_list<Statement*> body) {
			this->body = new std::vector<Statement*>(body);
		}

		~Program() {
			for (Statement* i : *(this->body)) {
				delete i;
			}
			delete this->body;
		}
};

class StatementExpr : public Statement {
	public:
		std::unique_ptr<Expr> expr;

		StatementExpr(Expr exp) : expr(std::make_unique<Expr>(exp)) { }
};
