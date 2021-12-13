#include <string.h>
#include "SyntaxNodeAdd.h"
#include "SyntaxNodeSub.h"
#include "SyntaxNodeNumber.h"
#include "SyntaxNodeVariable.h"
#include "SyntaxNodeAssignment.h"
#include "Scope.h"

#include "SerialOutput.h"


SerialOutput::SerialOutput(const char *filePath) :
	Output(filePath){

}

void SerialOutput::ComputeOne(const SyntaxNodeCompute &one, const char *instructions) {
	if (0==strcmp(instructions, "mulq")) {
		return;
	}
	SYNTAX_NODE_TYPE leftType = one.m_children.front()->GetType();
	SYNTAX_NODE_TYPE rightType = one.m_children.back()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == leftType &&
		SYNTAX_NODE_TYPE_NUMBER == rightType) {
		const int left = static_cast<SyntaxNodeNumber *>(one.m_children.front().get())->GetValue();
		const int right = static_cast<SyntaxNodeNumber *>(one.m_children.back().get())->GetValue();
		m_output << '\t' << "movq	$" << std::to_string(left + right) << ", %rax" << std::endl;
	}
	else {
		if (SYNTAX_NODE_TYPE_NUMBER == leftType) {
			const int rightPos = static_cast<SyntaxNodeVariable *>(one.m_children.back().get())->GetScopePos();
			m_output << '\t' << "movq	-" << (rightPos + 1) * 8 << "(%rbp), %rax" << std::endl;
			const int left = static_cast<SyntaxNodeNumber *>(one.m_children.front().get())->GetValue();
			m_output << '\t' << "addq	$" << std::to_string(left) << ", %rax" << std::endl;
		}
		else if (SYNTAX_NODE_TYPE_NUMBER == rightType) {
			const int leftPos = static_cast<SyntaxNodeVariable *>(one.m_children.front().get())->GetScopePos();
			m_output << '\t' << "movq	-" << (leftPos + 1) * 8 << "(%rbp), %rax" << std::endl;
			const int right = static_cast<SyntaxNodeNumber *>(one.m_children.back().get())->GetValue();
			m_output << '\t' << "addq	$" << std::to_string(right) << ", %rax" << std::endl;
		}
		else {
			const int leftPos = static_cast<SyntaxNodeVariable *>(one.m_children.front().get())->GetScopePos();
			m_output << '\t' << "movq	-" << (leftPos + 1) * 8 << "(%rbp), %rax" << std::endl;
			const int rightPos = static_cast<SyntaxNodeVariable *>(one.m_children.back().get())->GetScopePos();
			m_output << '\t' << "movq	-" << (rightPos + 1) * 8 << "(%rbp), %rdx" << std::endl;
			m_output << '\t' << instructions << "	%rdx, %rax" << std::endl;
		}
	}
}

size_t SerialOutput::Assignment(const SyntaxNodeAssignment &assign, std::unique_ptr<Output>& output) {
	SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>(assign.m_children.front().get());
	SyntaxNode *value = assign.m_children.back().get();
	if (SYNTAX_NODE_TYPE_NUMBER == value->GetType()) {
		m_output << '\t' << "movq	$" << std::to_string(static_cast<SyntaxNodeNumber *>(value)->GetValue())
			<< ", -" << (variable->GetScopePos() + 1) * 8 << "(%rbp)" << std::endl;
	}
	else {
		value->OutputInstructions(output);
		m_output << '\t' << "movq	%rax, -" << (variable->GetScopePos() + 1) * 8 << "(%rbp)" << std::endl;
	}
	return variable->GetScopePos() + 1;
}

void SerialOutput::ProcessScope(Scope &scope, std::unique_ptr<Output>& output) {
	for (std::shared_ptr<SyntaxNode> &child : scope.m_children) {
		child->OutputInstructions(output);
	}
}