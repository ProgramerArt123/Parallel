#include "SyntaxNode.h"
#include "Parallel.h"
#include "SyntaxNodeProcDef.h"


SyntaxNode::SyntaxNode(const char *content, int priority) :
	m_content(content), m_parent(*this) {
	m_line = lineno;
}
SyntaxNode::SyntaxNode(SyntaxNode &parent, const char *content, int priority) :
	m_content(content), m_parent(parent) {
	m_line = lineno;
}
SyntaxNode::~SyntaxNode() {
}


void SyntaxNode::FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	for (std::shared_ptr<SyntaxNode> &child : self->m_children) {
		child->FindEffectives(child, effectives);
	}
}

std::shared_ptr<SyntaxNode> SyntaxNode::AddChild(SyntaxNode *child) {
	std::shared_ptr<SyntaxNode> childPtr(child);
	AddChildBack(childPtr);
	return childPtr;
}

void SyntaxNode::AddChild(std::shared_ptr<SyntaxNode> &child) {
	AddChildBack(child);
}

GENERATE_PARALLEL_RESULT SyntaxNode::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel)  throw (std::exception) {
	if (UINT64_MAX == m_parallel_index) {
		return GenerateParallelSelf(self, parallel);
	}
	else {
		return GENERATE_PARALLEL_RESULT_COMPLETED;
	}
}

GENERATE_PARALLEL_RESULT SyntaxNode::GenerateParallelSelf(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) {
	if (parallel.CheckLastElement(m_parent) && parallel.CheckLastType(GetType())) {
		m_parallel_index = parallel.AddNode(self);
		return GENERATE_PARALLEL_RESULT_FINDED;
	}
	else {
		return GENERATE_PARALLEL_RESULT_NO_FIND;
	}
}

std::ostream &operator<<(std::ostream &out, SyntaxNode &node) {
	for (int i = 0; i < node.m_deep; i++) {
		out << '\t';
	}
	out << node.GetContent() << std::endl;
	for (std::shared_ptr<SyntaxNode> &child : node.m_children) {
		if (child->m_type == SYNTAX_NODE_TYPE_PROC_DEF) {
			out << *(SyntaxNodeProcDef*)child.get();
		}
		else {
			out << *child;
		}
	}
	return out;
}


void SyntaxNode::InsertChild(std::shared_ptr<SyntaxNode> &child,
	std::list<std::shared_ptr<SyntaxNode>>::iterator childItor) {
	m_children.insert(childItor, child);
}

void SyntaxNode::AddChildFront(std::shared_ptr<SyntaxNode> &child) {
	m_children.push_front(child);
}

void SyntaxNode::AddChildBack(std::shared_ptr<SyntaxNode> &child) {
	m_children.push_back(child);
}

std::list<std::shared_ptr<SyntaxNode>>::iterator SyntaxNode::RemoveChild(
	std::list<std::shared_ptr<SyntaxNode>>::iterator childItor) {
	std::list<std::shared_ptr<SyntaxNode>>::iterator nextItor
		= m_children.erase(childItor);
	return nextItor;
}

std::list<std::shared_ptr<SyntaxNode>>::iterator SyntaxNode::MoveChild(
	std::list<std::shared_ptr<SyntaxNode>>::iterator childItor) {
	std::shared_ptr<SyntaxNode> child = *childItor;
	std::list<std::shared_ptr<SyntaxNode>>::iterator
		next = RemoveChild(childItor);
	return next;
}

void SyntaxNode::SetDeep(int deep) {
	m_deep = deep;
	for (std::shared_ptr<SyntaxNode> &child : m_children) {
		child->SetDeep(m_deep + 1);
	}
}

const char* SyntaxNode::GetContent() {
	return m_content.c_str();
}

size_t SyntaxNode::GetChildrenCount() {
	return m_children.size();
}

SYNTAX_NODE_TYPE SyntaxNode::GetType() {
	return m_type;
}

int SyntaxNode::GetLine() {
	return m_line;
}

bool SyntaxNode::IsRoot() {
	return this == &m_parent;
}

void SyntaxNode::OutputSerial(std::stringstream& output) {
	for (std::shared_ptr<SyntaxNode> &child : m_children) {
		child->OutputSerial(output);
	}
}

void SyntaxNode::OutputParallel(std::stringstream& output) {
	for (std::shared_ptr<SyntaxNode> &child : m_children) {
		child->OutputParallel(output);
	}
}

