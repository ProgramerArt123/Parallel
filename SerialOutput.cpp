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

void SerialOutput::ComputeOne(const SyntaxNodeCompute &one, const char *instructions) {
	SYNTAX_NODE_TYPE leftType = one.m_children.front()->GetType();
	SYNTAX_NODE_TYPE rightType = one.m_children.back()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == leftType &&
		SYNTAX_NODE_TYPE_NUMBER == rightType) {
		const int left = static_cast<SyntaxNodeNumber *>(one.m_children.front().get())->GetValue();
		const int right = static_cast<SyntaxNodeNumber *>(one.m_children.back().get())->GetValue();
		m_output << '\t' << "movq	$" << std::to_string(left + right) << ", %rax" << std::endl;
	}
	else {
		if (SYNTAX_NODE_TYPE_NUMBER == leftType) {
			const int rightOffset = static_cast<SyntaxNodeVariable *>(one.m_children.back().get())->GetScopeStackTopOffset();
			m_output << '\t' << "movq	-" << rightOffset << "(%rbp), %rax" << std::endl;
			const int left = static_cast<SyntaxNodeNumber *>(one.m_children.front().get())->GetValue();
			m_output << '\t' << "addq	$" << std::to_string(left) << ", %rax" << std::endl;
		}
		else if (SYNTAX_NODE_TYPE_NUMBER == rightType) {
			const int leftOffset = static_cast<SyntaxNodeVariable *>(one.m_children.front().get())->GetScopeStackTopOffset();
			m_output << '\t' << "movq	-" << leftOffset << "(%rbp), %rax" << std::endl;
			const int right = static_cast<SyntaxNodeNumber *>(one.m_children.back().get())->GetValue();
			m_output << '\t' << "addq	$" << std::to_string(right) << ", %rax" << std::endl;
		}
		else {
			const int leftOffset = static_cast<SyntaxNodeVariable *>(one.m_children.front().get())->GetScopeStackTopOffset();
			m_output << '\t' << "movq	-" << leftOffset << "(%rbp), %rax" << std::endl;
			const int rightOffset = static_cast<SyntaxNodeVariable *>(one.m_children.back().get())->GetScopeStackTopOffset();
			m_output << '\t' << "movq	-" << rightOffset << "(%rbp), %rdx" << std::endl;
			m_output << '\t' << instructions << "	%rdx, %rax" << std::endl;
		}
	}
}

void SerialOutput::Assignment(const SyntaxNodeAssignment &assign, std::unique_ptr<Output>& output) {
	SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>(assign.m_children.front().get());
	SyntaxNode *value = assign.m_children.back().get();
	if (SYNTAX_NODE_TYPE_NUMBER == value->GetType()) {
		m_output << '\t' << "movq	$" << std::to_string(static_cast<SyntaxNodeNumber *>(value)->GetValue())
			<< ", -" << variable->GetScopeStackTopOffset() << "(%rbp)" << std::endl;
	}
	else if (SYNTAX_NODE_TYPE_ADD <= value->GetType() && value->GetType() <= SYNTAX_NODE_TYPE_OR) {
		SyntaxNodeCompute *compute = static_cast<SyntaxNodeCompute *>(value);
		compute->OutputInstructions(output);
		m_output << '\t' << "movq	%" << compute->GetResultRegName() << ", -" << variable->GetScopeStackTopOffset() << "(%rbp)" << std::endl;
	}
	else if (SYNTAX_NODE_TYPE_PROC_CALL == value->GetType()) {
		SyntaxNodeProcCall *call = static_cast<SyntaxNodeProcCall *>(value);
		call->OutputInstructions(output);
	}
}

void SerialOutput::ProcessScope(SyntaxNodeScope &scope, std::unique_ptr<Output>& output) {
	for (std::shared_ptr<SyntaxNode> &child : scope.m_children) {
		child->OutputInstructions(output);
	}
}