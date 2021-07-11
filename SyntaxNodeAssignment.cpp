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
	if (m_is_paralleled) {
		return GENERATE_PARALLEL_RESULT_COMPLETED;
	}
	std::shared_ptr<SyntaxNode> &right = self->m_children.back();
	GENERATE_PARALLEL_RESULT result = right->GenerateParallel(right, parallel);
	if (GENERATE_PARALLEL_RESULT_NO_FIND == result) {
		return GENERATE_PARALLEL_RESULT_NO_FIND;
	}
	if (parallel.CheckLastType(GetType())) {
		parallel.AddNode(self);
		m_is_paralleled = true;
		return GENERATE_PARALLEL_RESULT_FINDED;
	}
	else {
		return GENERATE_PARALLEL_RESULT_NO_FIND;
	}
}

void SyntaxNodeAssignment::generate(std::stringstream& output) {
	SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>(m_children.front().get());
	SyntaxNode *value = m_children.back().get();
	if (SYNTAX_NODE_TYPE_NUMBER == value->GetType()) {
		output << '\t' << "movq	$" << std::to_string(static_cast<SyntaxNodeNumber *>(value)->GetValue())
			<< ", -" << (variable->GetScopePos() + 1)*8 << "(%rbp)" << std::endl;
	}
	else {
		value->generate(output);
		output << '\t' << "movq	%rax, -" << (variable->GetScopePos() + 1)*8 << "(%rbp)" << std::endl;
	}
	m_scope.UpdateRuntimePos(variable->GetScopePos() + 1);
}