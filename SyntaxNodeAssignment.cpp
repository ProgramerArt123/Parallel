#include "SyntaxNodeAssignment.h"
#include "SyntaxNodeVariable.h"
#include "common.h"

SyntaxNodeAssignment::SyntaxNodeAssignment(SyntaxNodeScope &scope, int line):
	SyntaxNode(scope, line, "="){
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

void SyntaxNodeAssignment::OutputInstructions(std::unique_ptr<Output>& output) {
	output->Assignment(*this, output);
}
