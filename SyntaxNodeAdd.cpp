#include "SyntaxNodeAdd.h"
#include "common.h"

SyntaxNodeAdd::SyntaxNodeAdd():
	SyntaxNode("+"){
	m_type = SYNTAX_NODE_TYPE_ADD;
}

SyntaxNodeAdd::~SyntaxNodeAdd() {

}

void SyntaxNodeAdd::generate(std::stringstream& output) {
	SYNTAX_NODE_TYPE leftType = m_children.front()->GetType();
	SYNTAX_NODE_TYPE rightType = m_children.back()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == leftType &&
		SYNTAX_NODE_TYPE_NUMBER == rightType) {
		const int left = static_cast<SyntaxNodeNumber *>(m_children.front().get())->GetValue();
		const int right = static_cast<SyntaxNodeNumber *>(m_children.back().get())->GetValue();
		output << '\t' << "movq	$" << std::to_string(left + right) << ", %rax" << std::endl;
	}
	else {
		if (SYNTAX_NODE_TYPE_NUMBER == leftType) {
			const int rightPos = static_cast<SyntaxNodeVariable *>(m_children.back().get())->GetScopePos();
			output << '\t' << "movq	-" << (rightPos + 1) * 8 << "(%rbp), %rax" << std::endl;
			const int left = static_cast<SyntaxNodeNumber *>(m_children.front().get())->GetValue();
			output << '\t' << "addq	$" << std::to_string(left) << ", %rax" << std::endl;
		}
		else if (SYNTAX_NODE_TYPE_NUMBER == rightType) {
			const int leftPos = static_cast<SyntaxNodeVariable *>(m_children.front().get())->GetScopePos();
			output << '\t' << "movq	-" << (leftPos + 1) * 8 << "(%rbp), %rax" << std::endl;
			const int right = static_cast<SyntaxNodeNumber *>(m_children.back().get())->GetValue();
			output << '\t' << "addq	$" << std::to_string(right) << ", %rax" << std::endl;
		}
		else {
			const int leftPos = static_cast<SyntaxNodeVariable *>(m_children.front().get())->GetScopePos();
			output << '\t' << "movq	-" << (leftPos + 1) * 8 << "(%rbp), %rax" << std::endl;
			const int rightPos = static_cast<SyntaxNodeVariable *>(m_children.back().get())->GetScopePos();
			output << '\t' << "movq	-" << (rightPos + 1) * 8 << "(%rbp), %rdx" << std::endl;
			output << '\t' << "addq	%rdx, %rax" << std::endl;
		}
	}
}