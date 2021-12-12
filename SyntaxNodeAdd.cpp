#include "common.h"

#include "SyntaxNodeAdd.h"

SyntaxNodeAdd::SyntaxNodeAdd():
	SyntaxNodeCompute("+"){
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

void SyntaxNodeAdd::OutputInstructions(std::unique_ptr<Output>& output) {
	output->Add(*this);
}

