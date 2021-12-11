#include "SyntaxNodeNumber.h"
#include "SyntaxNodeAdd.h"
#include "SyntaxNodeVariable.h"
#include "SyntaxNodeAssignment.h"

#include "ParallelOutput.h"

ParallelOutput::ParallelOutput(const char *filePath) :
	Output(filePath) {

}

void ParallelOutput::Add(const SyntaxNodeAdd *add) {
	SYNTAX_NODE_TYPE leftType = add->m_children.front()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == leftType) {
		const int left = static_cast<SyntaxNodeNumber *>(add->m_children.front().get())->GetValue();
		m_output << '\t' << "vmovq $" << left << ", %xmm" << add->m_parallel_index % 4 << std::endl;
	}
	else {
		const int leftPos = static_cast<SyntaxNodeVariable *>(add->m_children.front().get())->GetScopePos();
		m_output << '\t' << "vmovq -" << (leftPos + 1) * 8 << "(%rbp), %xmm" << add->m_parallel_index % 4 << std::endl;
	}

	SYNTAX_NODE_TYPE rightType = add->m_children.back()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == rightType) {
		const int right = static_cast<SyntaxNodeNumber *>(add->m_children.back().get())->GetValue();
		m_output << '\t' << "vmovq $" << right << ", %xmm" << add->m_parallel_index % 4 + 4 << std::endl;
	}
	else {
		m_output << '\t' << "vmovq -" << add->GetRightChildStackTop() << "(%rbp), %xmm" << add->m_parallel_index % 4 + 4 << std::endl;
	}
}

size_t ParallelOutput::Assignment(const SyntaxNodeAssignment *assign, std::unique_ptr<Output>& output) {
	SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>(assign->m_children.front().get());
	SyntaxNode *value = assign->m_children.back().get();
	if (SYNTAX_NODE_TYPE_NUMBER == value->GetType()) {
		m_output << '\t' << "movq	$" << std::to_string(static_cast<SyntaxNodeNumber *>(value)->GetValue())
			<< ", -" << (variable->GetScopePos() + 1) * 8 << "(%rbp)" << std::endl;
	}
	else {
		if (SYNTAX_NODE_TYPE_ADD == value->GetType()) {
			SyntaxNodeAdd *add = static_cast<SyntaxNodeAdd *>(value);
			if (add->GetRightChildStackTop() + 32 != (variable->GetScopePos() + 1) * 8) {
				m_output << '\t' << "movq	-" << add->GetRightChildStackTop() + 32 << "(%rbp), %rax" << std::endl;
				m_output << '\t' << "movq	%rax, -" << (variable->GetScopePos() + 1) * 8 << "(%rbp)" << std::endl;
			}
		}
	}
	return variable->GetScopePos() + 1;
}