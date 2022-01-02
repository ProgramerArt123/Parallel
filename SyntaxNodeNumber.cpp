#include "SyntaxNodeScope.h"
#include "SyntaxNodeNumber.h"

SyntaxNodeNumber::SyntaxNodeNumber(SyntaxNodeScope &outer, int line, int value)
	:
	SyntaxNode(outer, line, std::to_string(value).c_str()),
	m_value(value){
	m_type = SYNTAX_NODE_TYPE_NUMBER;
}

SyntaxNodeNumber::~SyntaxNodeNumber() {

}


void SyntaxNodeNumber::OutputInstructions(std::unique_ptr<Output>& output) {
	output->GetStream() << '\t' << "movq	$" << GetValue() << ", -" <<
		SetResultPos(GetOuter()->PushCache()) << "(%rbp)" << std::endl;
}

GENERATE_PARALLEL_RESULT SyntaxNodeNumber::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception)  {
	return GENERATE_PARALLEL_RESULT_COMPLETED;
}

const int SyntaxNodeNumber::GetValue() {
	return m_value;
}

bool SyntaxNodeNumber::IsSameDataType(DATA_TYPE_TYPE type) {
	return DATA_TYPE_TYPE_INT == type;
}