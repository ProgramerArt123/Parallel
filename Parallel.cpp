#include <iostream>
#include "Parallel.h"
#include "SyntaxNode.h"

void Parallel::AddNode(const std::shared_ptr<SyntaxNode> &node) {
	if (m_nodes.empty()) {
		AddElement();
	}
	if (SYNTAX_NODE_TYPE_NONE == m_nodes.back().m_type) {
		m_nodes.back().m_type = node->GetType();
	}
	m_nodes.back().m_nodes.push_back(node);
}

void Parallel::AddElement() {
	ParallelElement element;
	m_nodes.push_back(element);
}

void Parallel::Truncation() {
	if (!m_nodes.empty() && SYNTAX_NODE_TYPE_NONE == m_nodes.back().m_type) {
		m_nodes.pop_back();
	}
}

bool Parallel::CheckLastType(SYNTAX_NODE_TYPE type) {
	if (m_nodes.empty()) {
		return true;
	}
	else if(SYNTAX_NODE_TYPE_NONE == m_nodes.back().m_type){
		return true;
	}
	else {
		return m_nodes.back().m_type == type;
	}
}

void Parallel::generate(std::stringstream& output) {
	//for (std::map<SYNTAX_NODE_TYPE, std::set<std::shared_ptr<SyntaxNode>>> &level : m_nodes) {
	//	generate(level, output);
	//}
}

void Parallel::generate(std::map<SYNTAX_NODE_TYPE, std::set<std::shared_ptr<SyntaxNode>>> &level,
	std::stringstream& output) {
	for (std::map<SYNTAX_NODE_TYPE, std::set<std::shared_ptr<SyntaxNode>>>::iterator itor =
		level.begin(); itor != level.end(); itor++) {
		switch (itor->first)
		{
		case SYNTAX_NODE_TYPE_ADD:
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
		default:
			break;
		}
	}
}

std::ostream &operator<<(std::ostream &out, Parallel &parallel) {
	for (ParallelElement &element : parallel.m_nodes) {
		out << "----------------------------------------------------------------------------" << std::endl;
		for (std::shared_ptr<SyntaxNode> &node : element.m_nodes) {
			out << node->GetContent() << '|';
		}
		out <<  std::endl;
	}
	return out;
}