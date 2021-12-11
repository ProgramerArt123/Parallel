#include "SyntaxNodeVariable.h"
#include "common.h"

SyntaxNodeVariable::SyntaxNodeVariable(SyntaxNode &scope, const char *name, size_t pos):
	SyntaxNode(scope, name), m_name(name), m_scope_pos(pos){
	m_type = SYNTAX_NODE_TYPE_VARIABLE;
}

SyntaxNodeVariable::~SyntaxNodeVariable() {

}


GENERATE_PARALLEL_RESULT SyntaxNodeVariable::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) {
	if (UINT64_MAX != m_parallel_index) {
		return GENERATE_PARALLEL_RESULT_COMPLETED;
	}
	std::shared_ptr<SyntaxNodeAssignment> lastAssign = GetLastAssign();
	if (lastAssign) {
		GENERATE_PARALLEL_RESULT result = lastAssign->GenerateParallel(lastAssign, parallel);
		if (GENERATE_PARALLEL_RESULT_NO_FIND == result) {
			return GENERATE_PARALLEL_RESULT_NO_FIND;
		}
	}
	m_parallel_index = 0;
	return GENERATE_PARALLEL_RESULT_FINDED;
}

void SyntaxNodeVariable::OutputInstructions(std::unique_ptr<Output>& output) {
	output->GetStream() << '\t' << "movq	" << GetScopePos() << "(%rbp), %rax" << std::endl;
}

size_t SyntaxNodeVariable::GetScopePos() {
	return m_scope_pos;
}

std::shared_ptr<SyntaxNodeAssignment> SyntaxNodeVariable::GetLastAssign() {
	Scope &scope = *static_cast<Scope *>(&m_parent);
	return scope.GetLastAssign(m_content.c_str(), m_generate_line);
}