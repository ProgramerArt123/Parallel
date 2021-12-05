#include "SyntaxNodeProcCall.h"
#include "common.h"

SyntaxNodeProcCall::SyntaxNodeProcCall(const char *name, Scope &scope):
	SyntaxNode(name), m_scope(scope){
	m_type = SYNTAX_NODE_TYPE_PROC_CALL;
}

SyntaxNodeProcCall::~SyntaxNodeProcCall() {

}

void SyntaxNodeProcCall::FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	effectives.insert(self);
}

GENERATE_PARALLEL_RESULT SyntaxNodeProcCall::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) {
	if (UINT64_MAX != m_parallel_index) {
		return GENERATE_PARALLEL_RESULT_COMPLETED;
	}
	bool isHaveNoFind = false;
	for (std::shared_ptr<SyntaxNode> &argment : m_children) {
		argment->m_generate_line = m_line;
		GENERATE_PARALLEL_RESULT result = argment->GenerateParallel(argment, parallel);
		if (GENERATE_PARALLEL_RESULT_FINDED == result) {
			return GENERATE_PARALLEL_RESULT_FINDED;
		}
		else if (GENERATE_PARALLEL_RESULT_NO_FIND == result) {
			isHaveNoFind = true;
		}
	}
	if (isHaveNoFind) {
		return GENERATE_PARALLEL_RESULT_NO_FIND;
	}
	else {
		return GenerateParallelSelf(self, parallel);
	}
}

void SyntaxNodeProcCall::OutputSerial(std::stringstream& output) {
	uint32_t top = m_scope.BeginCallGenerate(output, m_children);
	if (top) {
		output << '\t' << "subq    $" << top << ", %rsp" << std::endl;
	}
	PLATFORM.ProcCallGenerateSerial(m_content.c_str(), output);
	if (top) {
		output << '\t' << "addq   $" << top << ", %rsp" << std::endl;
	}
	m_scope.EndCallGenerate(output, m_children);
}
