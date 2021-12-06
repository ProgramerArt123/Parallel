#include "SyntaxNodeAdd.h"
#include "common.h"

SyntaxNodeAdd::SyntaxNodeAdd():
	SyntaxNode("+"){
	m_type = SYNTAX_NODE_TYPE_ADD;
}

SyntaxNodeAdd::~SyntaxNodeAdd() {

}

GENERATE_PARALLEL_RESULT SyntaxNodeAdd::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception)  {
	if (UINT64_MAX != m_parallel_index) {
		return GENERATE_PARALLEL_RESULT_COMPLETED;
	}
	std::shared_ptr<SyntaxNode> &left = self->m_children.front();
	left->m_generate_line = m_line;
	{
		GENERATE_PARALLEL_RESULT result = left->GenerateParallel(left, parallel);
		if (GENERATE_PARALLEL_RESULT_NO_FIND == result) {
			return GENERATE_PARALLEL_RESULT_NO_FIND;
		}
	}
	std::shared_ptr<SyntaxNode> &right = self->m_children.back();
	right->m_generate_line = m_line;
	{
		GENERATE_PARALLEL_RESULT result = right->GenerateParallel(right, parallel);
		if (GENERATE_PARALLEL_RESULT_NO_FIND == result) {
			return GENERATE_PARALLEL_RESULT_NO_FIND;
		}
	}
	return GenerateParallelSelf(self, parallel);
}

void SyntaxNodeAdd::OutputSerial(std::stringstream& output) {
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

void SyntaxNodeAdd::OutputParallel(std::stringstream& output) {
	SYNTAX_NODE_TYPE leftType = m_children.front()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == leftType) {
		const int left = static_cast<SyntaxNodeNumber *>(m_children.front().get())->GetValue();
		output << '\t' << "vmovq $" << left << ", %xmm" << m_parallel_index % 4 << std::endl;
	}
	else {
		const int leftPos = static_cast<SyntaxNodeVariable *>(m_children.front().get())->GetScopePos();
		output << '\t' << "vmovq -" << (leftPos + 1) * 8 << "(%rbp), %xmm" << m_parallel_index % 4 << std::endl;
	}

	SYNTAX_NODE_TYPE rightType = m_children.back()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == rightType) {
		const int right = static_cast<SyntaxNodeNumber *>(m_children.back().get())->GetValue();
		output << '\t' << "vmovq $" << right << ", %xmm" << m_parallel_index % 4 + 4 << std::endl;
	}
	else {
		output << '\t' << "vmovq -" << GetRightChildStackTop() << "(%rbp), %xmm" << m_parallel_index % 4 + 4 << std::endl;
	}
}

int SyntaxNodeAdd::GetRightChildStackTop() {
	SYNTAX_NODE_TYPE rightType = m_children.back()->GetType();
	if (SYNTAX_NODE_TYPE_VARIABLE == rightType) {
		const int rightPos = static_cast<SyntaxNodeVariable *>(m_children.back().get())->GetScopePos();
		return (rightPos + 1) * 8;
	}
	else {
		return 0;
	}
}