#include <sstream>
#include "SyntaxTree.h"
#include "SyntaxNode.h"

SyntaxTree::SyntaxTree(){
	m_type = SYNTAX_NODE_TYPE_TREE;
	m_content = "SyntaxTree";
}

SyntaxTree::SyntaxTree(SyntaxNode &parent):
	SyntaxNode(parent) {
	m_type = SYNTAX_NODE_TYPE_TREE;
	m_content = "SyntaxTree";
}

SyntaxTree::~SyntaxTree() {

}

void SyntaxTree::FindEffectives(std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	for (std::shared_ptr<SyntaxNode> &child : m_children) {
		child->FindEffectives(child, effectives);
	}
}

void SyntaxTree::GenerateParallel(std::set<std::shared_ptr<SyntaxNode>> &effectives) throw (std::exception) {
	for (const std::shared_ptr<SyntaxNode> &effective : effectives) {
		while (true){
			GENERATE_PARALLEL_RESULT result = effective->GenerateParallel(effective, m_nodes);
			if (GENERATE_PARALLEL_RESULT_COMPLETED == result) {
				break;
			}
			else if (GENERATE_PARALLEL_RESULT_NO_FIND == result) {
				m_nodes.AddElement();
			}
		}
	}
	m_nodes.Truncation();
}


std::ostream &operator<<(std::ostream &out, SyntaxTree &tree) {
	out << *static_cast<SyntaxNode*>(&tree);
	out << tree.m_nodes;
	return out;
}