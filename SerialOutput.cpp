#include <string.h>
#include "SyntaxNodeAdd.h"
#include "SyntaxNodeSub.h"
#include "SyntaxNodeNumber.h"
#include "SyntaxNodeVariable.h"
#include "SyntaxNodeAssignment.h"
#include "SyntaxNodeScope.h"
#include "SyntaxNodeProcCall.h"

#include "SerialOutput.h"


SerialOutput::SerialOutput(const char *filePath) :
	Output(filePath){

}

void SerialOutput::ComputeOne(const SyntaxNodeCompute &one, const char *instructions, std::unique_ptr<Output>& output) {
	one.m_children.front()->OutputInstructions(output);
	one.m_children.back()->OutputInstructions(output);
	output->GetStream() << '\t' << "movq	-" << 
		one.m_children.front()->GetResultPos() << "(%rbp), %rax" << std::endl;
	one.GetOuter()->PopCache();
	output->GetStream() << '\t' << "movq	-" << 
		one.m_children.back()->GetResultPos() << "(%rbp), %rdx" << std::endl;
	one.GetOuter()->PopCache();
	m_output << '\t' << instructions << "	%rdx, %rax" << std::endl;
}

void SerialOutput::Assignment(const SyntaxNodeAssignment &assign, std::unique_ptr<Output>& output) {
	SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>(assign.m_children.front().get());
	assign.m_children.back()->OutputInstructions(output);
	output->GetStream() << '\t' << "movq	-" << 
		assign.m_children.back()->GetResultPos() << "(%rbp), %rax" << std::endl;
	m_output << '\t' << "movq	%rax, -" << variable->GetScopeStackTopOffset() << "(%rbp)" << std::endl;
}

void SerialOutput::ProcessScope(SyntaxNodeScope &scope, std::unique_ptr<Output>& output) {
	for (std::shared_ptr<SyntaxNode> &child : scope.m_children) {
		child->OutputInstructions(output);
	}
}