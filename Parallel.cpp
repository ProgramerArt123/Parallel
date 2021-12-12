#include <iostream>
#include "ParallelOutput.h"
#include "SyntaxNode.h"
#include "common.h"

#include "Parallel.h"

void ParallelElement::OutputInstructions(std::unique_ptr<Output>& output) {
	ParallelOutput *parallel = static_cast<ParallelOutput *>(output.get());
	switch (m_type)
	{
	case SYNTAX_NODE_TYPE_ADD:
		parallel->ElementAdd(*this, output);
		break;
	case SYNTAX_NODE_TYPE_SUB:
		parallel->ElementSub(*this, output);
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
			node->OutputInstructions(output);
		}
	}
		break;
	default:
	{
		for (std::shared_ptr<SyntaxNode> &node : m_nodes) {
			node->OutputInstructions(output);
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

void Parallel::OutputInstructions(std::unique_ptr<Output>& output) {
	for (ParallelElement &element : m_elements) {
		element.OutputInstructions(output);
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