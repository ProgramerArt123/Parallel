#include "SyntaxNodeVariable.h"
#include "SyntaxNodeCompute.h"

SyntaxNodeCompute::SyntaxNodeCompute(const char *content, int priority):
	SyntaxNode(content, priority){

}
SyntaxNodeCompute:: ~SyntaxNodeCompute() {

}

int SyntaxNodeCompute::GetRightChildStackTop()const {
	SYNTAX_NODE_TYPE rightType = m_children.back()->GetType();
	if (SYNTAX_NODE_TYPE_VARIABLE == rightType) {
		const int rightPos = static_cast<SyntaxNodeVariable *>(m_children.back().get())->GetScopePos();
		return (rightPos + 1) * 8;
	}
	else {
		return 0;
	}
}