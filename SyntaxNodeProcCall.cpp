#include "common.h"
#include "SyntaxNodeProcCall.h"

SyntaxNodeProcCall::SyntaxNodeProcCall(SyntaxNodeScope &scope, const char *name):
	SyntaxNode(scope, name){
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

void SyntaxNodeProcCall::OutputInstructions(std::unique_ptr<Output>& output) {
	GetOuter()->BeginCallGenerate(output, m_children);
	PLATFORM.ProcCallGenerate(m_content.c_str(), output->GetStream());
	GetOuter()->EndCallGenerate(output->GetStream(), m_children);
	output->GetStream() << '\t' << "movq	%rax, -" << SetResultPos(GetOuter()->PushCache()) << "(%rbp)" << std::endl;
}
