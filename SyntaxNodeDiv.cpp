#include "SyntaxNodeDiv.h"
#include "common.h"

SyntaxNodeDiv::SyntaxNodeDiv():
	SyntaxNode("/"){
	m_type = SYNTAX_NODE_TYPE_DIV;
}

SyntaxNodeDiv::~SyntaxNodeDiv() {

}

void SyntaxNodeDiv::OutputSerial(std::stringstream& output) {
	SYNTAX_NODE_TYPE leftType = m_children.front()->GetType();
	SYNTAX_NODE_TYPE rightType = m_children.back()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == leftType &&
		SYNTAX_NODE_TYPE_NUMBER == rightType) {
		const int left = static_cast<SyntaxNodeNumber *>(m_children.front().get())->GetValue();
		const int right = static_cast<SyntaxNodeNumber *>(m_children.back().get())->GetValue();
		output << '\t' << "movq	$" << std::to_string(left / right) << ", %rax" << std::endl;
	}
	else {
		if (SYNTAX_NODE_TYPE_NUMBER == leftType) {
			const int left = static_cast<SyntaxNodeNumber *>(m_children.front().get())->GetValue();
			output << '\t' << "movq	$" << std::to_string(left) << ", %rax" << std::endl;
		}
		else {
			const int pos = static_cast<SyntaxNodeVariable *>(m_children.front().get())->GetScopePos();
			output << '\t' << "movq	-" << (pos + 1) * 8 << "(%rbp), %rax" << std::endl;
		}
		output << '\t' << "sarl	$31, %rdx" << std::endl;
		if (SYNTAX_NODE_TYPE_NUMBER == rightType) {
			const int right = static_cast<SyntaxNodeNumber *>(m_children.back().get())->GetValue();
			output << '\t' << "idivq	$" << std::to_string(right) << std::endl;
		}
		else {
			const int pos = static_cast<SyntaxNodeVariable *>(m_children.back().get())->GetScopePos();
			output << '\t' << "idivq	-" << (pos+1)*8 << "(%rbp)" << std::endl;
		}
		
	}
}