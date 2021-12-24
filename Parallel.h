#ifndef __PARALLEL_H__
#define __PARALLEL_H__

#include <list>
#include <vector>
#include <set>
#include <memory>
#include <exception>
#include <map>
#include "SyntaxNodeType.h"

class SyntaxNode;
class Output;

class ParallelElement {
public:
	explicit ParallelElement(SyntaxNodeScope &scope);
	SYNTAX_NODE_TYPE m_type = SYNTAX_NODE_TYPE_NONE;
	std::vector<std::shared_ptr<SyntaxNode>> m_nodes;
	void OutputInstructions(std::unique_ptr<Output>& output);
	SyntaxNodeScope &m_scope;
};

class Parallel {
public:
	explicit Parallel(SyntaxNodeScope &scope);
	uint64_t AddNode(const std::shared_ptr<SyntaxNode> &node);
	void AddElement();
	void Truncation();
	bool CheckLastType(SYNTAX_NODE_TYPE type);
	bool CheckLastElement(const SyntaxNode &node);
	void OutputInstructions(std::unique_ptr<Output>& output);
	friend std::ostream &operator<<(std::ostream &out, Parallel &parallel);

private:
	std::vector<ParallelElement> m_elements;

	SyntaxNodeScope &m_scope;
};


#endif