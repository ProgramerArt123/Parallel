#include "SyntaxNodeNumber.h"
#include "SyntaxNodeAdd.h"
#include "SyntaxNodeSub.h"
#include "SyntaxNodeMul.h"
#include "SyntaxNodeDiv.h"
#include "SyntaxNodeVariable.h"
#include "SyntaxNodeAssignment.h"
#include "Parallel.h"
#include "SyntaxNodeScope.h"

#include "common.h"
#include "ParallelOutput.h"

ParallelOutput::ParallelOutput(const char *filePath) :
	Output(filePath) {
	//source->m_scopes.top()->FindEffectives();
	//source->m_scopes.top()->GenerateParallel();
}

void ParallelOutput::ComputeOne(const SyntaxNodeCompute &one, const char *instructions, std::unique_ptr<Output>& output) {
	SYNTAX_NODE_TYPE leftType = one.m_children.front()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == leftType) {
		const int left = static_cast<SyntaxNodeNumber *>(one.m_children.front().get())->GetValue();
		m_output << '\t' << "vmovq $" << left << ", %xmm" << one.m_parallel_index % 4 << std::endl;
	}
	else {
		const int leftOffset = static_cast<SyntaxNodeVariable *>(one.m_children.front().get())->GetScopeStackTopOffset();
		m_output << '\t' << "vmovq -" << leftOffset << "(%rbp), %xmm" << one.m_parallel_index % 4 << std::endl;
	}

	SYNTAX_NODE_TYPE rightType = one.m_children.back()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == rightType) {
		const int right = static_cast<SyntaxNodeNumber *>(one.m_children.back().get())->GetValue();
		m_output << '\t' << "vmovq $" << right << ", %xmm" << one.m_parallel_index % 4 + 4 << std::endl;
	}
	else {
		m_output << '\t' << "vmovq -" << one.GetRightChildStackTopOffset() << "(%rbp), %xmm" << one.m_parallel_index % 4 + 4 << std::endl;
	}
}

void ParallelOutput::Assignment(SyntaxNodeAssignment &assign, std::unique_ptr<Output>& output) {
	SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>(assign.m_children.front().get());
	SyntaxNode *value = assign.m_children.back().get();
	if (SYNTAX_NODE_TYPE_NUMBER == value->GetType()) {
		m_output << '\t' << "movq	$" << std::to_string(static_cast<SyntaxNodeNumber *>(value)->GetValue())
			<< ", -" << variable->GetScopeStackTopOffset() << "(%rbp)" << std::endl;
	}
	else {
		if (SYNTAX_NODE_TYPE_ADD <= value->GetType() && value->GetType() <= SYNTAX_NODE_TYPE_OR) {
			SyntaxNodeCompute *compute = static_cast<SyntaxNodeCompute *>(value);
			if (compute->CacheResultStackTopOffset() != variable->GetScopeStackTopOffset()) {
				m_output << '\t' << "movq	-" << compute->CacheResultStackTopOffset() << "(%rbp), %rax" << std::endl;
				m_output << '\t' << "movq	%rax, -" << variable->GetScopeStackTopOffset() << "(%rbp)" << std::endl;
			}
		}
	}
}

void ParallelOutput::ProcessScope(SyntaxNodeScope &scope, std::unique_ptr<Output>& output) {	//for (std::shared_ptr<SyntaxNode> &child : m_children) {
	for (std::shared_ptr<SyntaxNode> &child : scope.m_children) {
		SYNTAX_NODE_TYPE type = child->GetType();
		if (SYNTAX_NODE_TYPE_PROC_DEF == type || SYNTAX_NODE_TYPE_FOR == type) {
			child->OutputInstructions(output);
		}
	}
	scope.m_parallel.OutputInstructions(output);
}

void ParallelOutput::ElementAdd(ParallelElement &element, std::unique_ptr<Output>& output) {
	size_t count = element.m_nodes.size();
	for (size_t index = 0; index < count; index += 4) {
		for (size_t j = 0; j < 4; j++) {
			if (index + j >= count) {
				break;
			}
			std::shared_ptr<SyntaxNode> &add = element.m_nodes[index + j];
			add->OutputInstructions(output);
		}
		GetStream() << '\t' << "vpunpcklqdq     %xmm0, %xmm1, %xmm0" << std::endl;
		GetStream() << '\t' << "vinserti128     $1, %xmm0, %ymm0, %ymm0" << std::endl;
		GetStream() << '\t' << "vpunpcklqdq     %xmm2, %xmm3, %xmm2" << std::endl;
		GetStream() << '\t' << "vinserti128     $0, %xmm2, %ymm0, %ymm0" << std::endl;
		GetStream() << '\t' << "vpunpcklqdq     %xmm4, %xmm5, %xmm4" << std::endl;
		GetStream() << '\t' << "vinserti128     $1, %xmm4, %ymm1, %ymm1" << std::endl;
		GetStream() << '\t' << "vpunpcklqdq     %xmm6, %xmm7, %xmm6" << std::endl;
		GetStream() << '\t' << "vinserti128     $0, %xmm6, %ymm1, %ymm1" << std::endl;
		GetStream() << '\t' << "vpaddq  %ymm1, %ymm0, %ymm0" << std::endl;
		//cache result
		SyntaxNodeAdd *add = static_cast<SyntaxNodeAdd *>(element.m_nodes[index].get());
		GetStream() << '\t' << "vmovdqu  %ymm0, -" << 
			add->CacheResultStackTopOffset(element.m_scope.GetCurrentPos()) << "(%rbp)" << std::endl;
	}
}

void ParallelOutput::ElementSub(ParallelElement &element, std::unique_ptr<Output>& output) {
	size_t count = element.m_nodes.size();
	for (size_t index = 0; index < count; index += 4) {
		for (size_t j = 0; j < 4; j++) {
			if (index + j >= count) {
				break;
			}
			std::shared_ptr<SyntaxNode> &sub = element.m_nodes[index + j];
			sub->OutputInstructions(output);
		}
		GetStream() << '\t' << "vpunpcklqdq     %xmm0, %xmm1, %xmm0" << std::endl;
		GetStream() << '\t' << "vinserti128     $1, %xmm0, %ymm0, %ymm0" << std::endl;
		GetStream() << '\t' << "vpunpcklqdq     %xmm2, %xmm3, %xmm2" << std::endl;
		GetStream() << '\t' << "vinserti128     $0, %xmm2, %ymm0, %ymm0" << std::endl;
		GetStream() << '\t' << "vpunpcklqdq     %xmm4, %xmm5, %xmm4" << std::endl;
		GetStream() << '\t' << "vinserti128     $1, %xmm4, %ymm1, %ymm1" << std::endl;
		GetStream() << '\t' << "vpunpcklqdq     %xmm6, %xmm7, %xmm6" << std::endl;
		GetStream() << '\t' << "vinserti128     $0, %xmm6, %ymm1, %ymm1" << std::endl;
		GetStream() << '\t' << "vpsubq  %ymm1, %ymm0, %ymm0" << std::endl;
		//cache result
		SyntaxNodeSub *sub = static_cast<SyntaxNodeSub *>(element.m_nodes[index].get());
		GetStream() << '\t' << "vmovdqu  %ymm0, -" << 
			sub->CacheResultStackTopOffset(element.m_scope.GetCurrentPos()) << "(%rbp)" << std::endl;
	}
}

void ParallelOutput::ElementMul(ParallelElement &element, std::unique_ptr<Output>& output) {
	size_t count = element.m_nodes.size();
	for (size_t index = 0; index < count; index += 4) {
		for (size_t j = 0; j < 4; j++) {
			if (index + j >= count) {
				break;
			}
			std::shared_ptr<SyntaxNode> &add = element.m_nodes[index + j];
			add->OutputInstructions(output);
		}
		GetStream() << '\t' << "vpunpcklqdq     %xmm0, %xmm1, %xmm0" << std::endl;
		GetStream() << '\t' << "vinserti128     $1, %xmm0, %ymm0, %ymm0" << std::endl;
		GetStream() << '\t' << "vpunpcklqdq     %xmm2, %xmm3, %xmm2" << std::endl;
		GetStream() << '\t' << "vinserti128     $0, %xmm2, %ymm0, %ymm0" << std::endl;
		GetStream() << '\t' << "vpunpcklqdq     %xmm4, %xmm5, %xmm4" << std::endl;
		GetStream() << '\t' << "vinserti128     $1, %xmm4, %ymm1, %ymm1" << std::endl;
		GetStream() << '\t' << "vpunpcklqdq     %xmm6, %xmm7, %xmm6" << std::endl;
		GetStream() << '\t' << "vinserti128     $0, %xmm6, %ymm1, %ymm1" << std::endl;
		GetStream() << '\t' << "vpmuldq  %ymm1, %ymm0, %ymm0" << std::endl;
		//cache result
		SyntaxNodeMul *mul = static_cast<SyntaxNodeMul *>(element.m_nodes[index].get());
		GetStream() << '\t' << "vmovdqu  %ymm0, -" <<
			mul->CacheResultStackTopOffset(element.m_scope.GetCurrentPos()) << "(%rbp)" << std::endl;
	}
}

void ParallelOutput::ElementDiv(ParallelElement &element, std::unique_ptr<Output>& output) {
	size_t count = element.m_nodes.size();
	for (size_t index = 0; index < count; index ++) {
		std::shared_ptr<SyntaxNode> &node = element.m_nodes[index];
		node->OutputInstructions(output);
		SyntaxNodeCompute *compute = static_cast<SyntaxNodeCompute *>(node.get());
		GetStream() << '\t' << "movq  %"<< compute->GetResultRegName() <<", -" << 
			compute->CacheResultStackTopOffset(element.m_scope.GetCurrentPos()) << "(%rbp)" << std::endl;
	}
}

void ParallelOutput::ElementMod(ParallelElement &element, std::unique_ptr<Output>& output) {
	size_t count = element.m_nodes.size();
	for (size_t index = 0; index < count; index++) {
		std::shared_ptr<SyntaxNode> &node = element.m_nodes[index];
		node->OutputInstructions(output);
		SyntaxNodeCompute *compute = static_cast<SyntaxNodeCompute *>(node.get());
		GetStream() << '\t' << "movq  %" << compute->GetResultRegName() << ", -" << 
			compute->CacheResultStackTopOffset(element.m_scope.GetCurrentPos()) << "(%rbp)" << std::endl;
	}
}