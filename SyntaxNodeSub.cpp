#include "SyntaxNodeSub.h"
#include "common.h"

SyntaxNodeSub::SyntaxNodeSub():
	SyntaxNodeCompute("-"){
	m_type = SYNTAX_NODE_TYPE_SUB;
}

SyntaxNodeSub::~SyntaxNodeSub() {

}

GENERATE_PARALLEL_RESULT SyntaxNodeSub::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) {
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

void SyntaxNodeSub::OutputInstructions(std::unique_ptr<Output>& output) {
	output->Sub(*this);
}
