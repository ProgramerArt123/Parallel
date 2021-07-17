#include <iostream>
#include "Parallel.h"
#include "SyntaxNode.h"
#include "common.h"

void ParallelElement::OutPut(std::stringstream &output) {
	switch (m_type)
	{
	case SYNTAX_NODE_TYPE_ADD:
	{
		size_t count = m_nodes.size();
		for (size_t index = 0; index < count; index += 4) {
			for (size_t j = 0; j < 4; j ++) {
				if (index + j >= count) {
					break;
				}
				std::shared_ptr<SyntaxNode> &add = m_nodes[index + j];
				add->OutputParallel(output);
			}
			output << '\t' << "vpunpcklqdq     %xmm0, %xmm1, %xmm0" << std::endl;
			output << '\t' << "vinserti128     $0, %xmm0, %ymm0, %ymm0" << std::endl;
			output << '\t' << "vpunpcklqdq     %xmm2, %xmm3, %xmm2" << std::endl;
			output << '\t' << "vinserti128     $1, %xmm2, %ymm0, %ymm0" << std::endl;
			output << '\t' << "vpunpcklqdq     %xmm4, %xmm5, %xmm4" << std::endl;
			output << '\t' << "vinserti128     $0, %xmm4, %ymm1, %ymm1" << std::endl;
			output << '\t' << "vpunpcklqdq     %xmm6, %xmm7, %xmm6" << std::endl;
			output << '\t' << "vinserti128     $1, %xmm6, %ymm1, %ymm1" << std::endl;
			output << '\t' << "vpaddq  %ymm0, %ymm1, %ymm0" << std::endl;
		}
	}
		break;
	case SYNTAX_NODE_TYPE_SUB:
		break;
	case SYNTAX_NODE_TYPE_MUL:
		break;
	case SYNTAX_NODE_TYPE_DIV:
		break;
	case SYNTAX_NODE_TYPE_AND:
		break;
	case SYNTAX_NODE_TYPE_OR:
		break;
	case SYNTAX_NODE_TYPE_NOT:
		break;
	case SYNTAX_NODE_TYPE_ASSIGNMENT:
	{
		for (std::shared_ptr<SyntaxNode> &node : m_nodes) {
			node->OutputParallel(output);
		}
	}
		break;
	default:
	{
		for (std::shared_ptr<SyntaxNode> &node : m_nodes) {
			node->OutputSerial(output);
		}
	}
		break;
	}
}

uint64_t Parallel::AddNode(const std::shared_ptr<SyntaxNode> &node) {
	if (m_elements.empty()) {
		AddElement();
	}
	if (SYNTAX_NODE_TYPE_NONE == m_elements.back().m_type) {
		m_elements.back().m_type = node->GetType();
	}
	m_elements.back().m_nodes.push_back(node);
	return m_elements.back().m_nodes.size() - 1;
}

void Parallel::AddElement() {
	ParallelElement element;
	m_elements.push_back(element);
}

void Parallel::Truncation() {
	if (!m_elements.empty() && SYNTAX_NODE_TYPE_NONE == m_elements.back().m_type) {
		m_elements.pop_back();
	}
}

bool Parallel::CheckLastType(SYNTAX_NODE_TYPE type) {
	if (m_elements.empty()) {
		return true;
	}
	else if(SYNTAX_NODE_TYPE_NONE == m_elements.back().m_type){
		return true;
	}
	else {
		return m_elements.back().m_type == type;
	}
}

bool Parallel::CheckLastElement(const SyntaxNode &node) {
	if (m_elements.empty()) {
		return true;
	}
	ParallelElement &last = m_elements.back();
	for (std::shared_ptr<SyntaxNode> &other : last.m_nodes) {
		if (&node == other.get()) {
			return false;
		}
	}
	return true;
}

void Parallel::Output(std::stringstream& output) {
	for (ParallelElement &element : m_elements) {
		element.OutPut(output);
	}
}

std::ostream &operator<<(std::ostream &out, Parallel &parallel) {
	out << "==============================================================================" << std::endl;
	for (ParallelElement &element : parallel.m_elements) {
		for (std::shared_ptr<SyntaxNode> &node : element.m_nodes) {
			out << node->GetContent() << '|';
		}
		out <<  std::endl;
		out << "----------------------------------------------------------------------------" << std::endl;
	}
	out << "==============================================================================" << std::endl;
	return out;
}