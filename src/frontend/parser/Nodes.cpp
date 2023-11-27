#include "../../../includes/NodeType.h"

class Expr : public NodeType {
	private:
		Expr& left;
		char* op;
		Expr& right;

	public:
		Expr( const Expr& left_, char* op_, const Expr& right) : left(left_),op(op_), right(right_) { };


};
