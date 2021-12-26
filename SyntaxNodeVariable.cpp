#include "SyntaxNodeVariable.h"
#include "common.h"

SyntaxNodeVariable::SyntaxNodeVariable(SyntaxNodeScope &scope, const char *name, std::shared_ptr<DataType> &dataType, size_t pos):
	SyntaxNode(scope, name), m_name(name), m_data_type(dataType),
	m_scope_pos(pos){
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
	output->GetStream() << '\t' << "movq	-" << GetScopeStackTopOffset() <<
		"(%rbp), %rax" << std::endl;
	output->GetStream() << '\t' << "movq	%rax, -" <<
		SetResultPos(GetOuter()->PushCache()) << "(%rbp)" << std::endl;
}

const size_t SyntaxNodeVariable::GetScopePos()const {
	return m_scope_pos;
}

const size_t SyntaxNodeVariable::GetScopeStackTopOffset()const {
	return (GetScopePos() + 1) * 8;
}

std::shared_ptr<SyntaxNodeAssignment> SyntaxNodeVariable::GetLastAssign() {
	return m_outer->GetLastAssign(m_content.c_str(), m_generate_line);
}