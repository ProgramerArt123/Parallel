#include "SyntaxNodeVariable.h"
#include "SyntaxNodeCompute.h"

SyntaxNodeCompute::SyntaxNodeCompute(const char *content, int priority):
	SyntaxNode(content, priority){

}
SyntaxNodeCompute:: ~SyntaxNodeCompute() {

}

GENERATE_PARALLEL_RESULT SyntaxNodeCompute::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) {
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

int SyntaxNodeCompute::GetRightChildStackTop()const {
	SYNTAX_NODE_TYPE rightType = m_children.back()->GetType();
	if (SYNTAX_NODE_TYPE_VARIABLE == rightType) {
		const int rightPos = static_cast<SyntaxNodeVariable *>(m_children.back().get())->GetScopePos();
		return (rightPos + 1) * 8;
	}
	else {
		return 0;
	}
}
