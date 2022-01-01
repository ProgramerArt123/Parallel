#include <string.h>
#include "common.h"
#include "SyntaxNodeProcCall.h"

SyntaxNodeProcCall::SyntaxNodeProcCall(SyntaxNodeScope &scope, int line, const char *name)
	: SyntaxNode(scope, line, name) {
	m_type = SYNTAX_NODE_TYPE_PROC_CALL;
}

SyntaxNodeProcCall::~SyntaxNodeProcCall() {

}

//std::shared_ptr<SyntaxNodeScope> &SyntaxNodeProcCall::GetArgments() {
//	return m_arguments;
//}

void SyntaxNodeProcCall::FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	effectives.insert(self);
}

GENERATE_PARALLEL_RESULT SyntaxNodeProcCall::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) {
	if (UINT64_MAX != m_parallel_index) {
		return GENERATE_PARALLEL_RESULT_COMPLETED;
	}
	bool isHaveNoFind = false;
	for (std::shared_ptr<SyntaxNode> argment : m_arguments) {
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
	BeginCallGenerate(output);
	PLATFORM.ProcCallGenerate(m_content.c_str(), output->GetStream());
	EndCallGenerate(output->GetStream());
	output->GetStream() << '\t' << "movq	%rax, -" << SetResultPos(GetOuter()->PushCache()) << "(%rbp)" << std::endl;
}


void SyntaxNodeProcCall::BeginCallGenerate(std::unique_ptr<Output>& output) {
	
	for (std::shared_ptr<SyntaxNode> argment : m_arguments) {	
		argment->OutputInstructions(output);
	}
	
	uint32_t index = 0;
	for (std::shared_ptr<SyntaxNode> argment : m_arguments) {
		argment->ArgmentCache(index++, output);
	}

	if (GetOuter()->GetSubProcOffset()) {
		output->GetStream() << '\t' << "subq    $" << GetOuter()->GetSubProcOffset() << ", %rsp" << std::endl;
	}
}

void SyntaxNodeProcCall::EndCallGenerate(std::stringstream& output) {
	if (GetOuter()->GetSubProcOffset()) {
		output << '\t' << "addq    $" << GetOuter()->GetSubProcOffset() << ", %rsp" << std::endl;
	}
	uint32_t index = m_arguments.size() - 1;
	for (std::shared_ptr<SyntaxNode> argment : m_arguments) {
		if (index < PLATFORM.registersCount) {
			if (0 == strcmp(PLATFORM.registers[index], "rcx")) {
				std::string dst;
				size_t offset = GetOuter()->PopRegister(dst);
				output << '\t' << "movq	" << "-" << std::to_string(offset) << "(%rbp)," << dst << std::endl;
			}
		}
		else {
			GetOuter()->PopArgument();
		}
		index--;
	}
}
