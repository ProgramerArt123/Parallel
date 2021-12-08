#include "SyntaxNodeAssignment.h"
#include "SyntaxNodeVariable.h"
#include "common.h"

SyntaxNodeAssignment::SyntaxNodeAssignment(Scope &scope):
	SyntaxNode("="), m_scope(scope){
	m_type = SYNTAX_NODE_TYPE_ASSIGNMENT;
}

SyntaxNodeAssignment::~SyntaxNodeAssignment() {

}

GENERATE_PARALLEL_RESULT SyntaxNodeAssignment::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) {
	if (UINT64_MAX != m_parallel_index) {
		return GENERATE_PARALLEL_RESULT_COMPLETED;
	}
	std::shared_ptr<SyntaxNode> &right = self->m_children.back();
	GENERATE_PARALLEL_RESULT result = right->GenerateParallel(right, parallel);
	if (GENERATE_PARALLEL_RESULT_NO_FIND == result) {
		return GENERATE_PARALLEL_RESULT_NO_FIND;
	}
	return GenerateParallelSelf(self, parallel);
}

void SyntaxNodeAssignment::OutputSerial(std::stringstream& output) {
	SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>(m_children.front().get());
	SyntaxNode *value = m_children.back().get();
	if (SYNTAX_NODE_TYPE_NUMBER == value->GetType()) {
		output << '\t' << "movq	$" << std::to_string(static_cast<SyntaxNodeNumber *>(value)->GetValue())
			<< ", -" << (variable->GetScopePos() + 1)*8 << "(%rbp)" << std::endl;
	}
	else {
		value->OutputSerial(output);
		output << '\t' << "movq	%rax, -" << (variable->GetScopePos() + 1)*8 << "(%rbp)" << std::endl;
	}
	m_scope.UpdateRuntimePos(variable->GetScopePos() + 1);
}

void SyntaxNodeAssignment::OutputParallel(std::stringstream& output) {
	SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>(m_children.front().get());
	SyntaxNode *value = m_children.back().get();
	if (SYNTAX_NODE_TYPE_NUMBER == value->GetType()) {
		output << '\t' << "movq	$" << std::to_string(static_cast<SyntaxNodeNumber *>(value)->GetValue())
			<< ", -" << (variable->GetScopePos() + 1) * 8 << "(%rbp)" << std::endl;
	}
	else {
		if (SYNTAX_NODE_TYPE_ADD == value->GetType()) {
			SyntaxNodeAdd *add = static_cast<SyntaxNodeAdd *>(value);
			if (add->GetRightChildStackTop() + 32 != (variable->GetScopePos() + 1) * 8) {
				output << '\t' << "movq	-" << add->GetRightChildStackTop() + 32 << "(%rbp), %rax" << std::endl;
				output << '\t' << "movq	%rax, -" << (variable->GetScopePos() + 1) * 8 << "(%rbp)" << std::endl;
			}
		}
	}
	m_scope.UpdateRuntimePos(variable->GetScopePos() + 1);
}