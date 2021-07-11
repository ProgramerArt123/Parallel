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

typedef struct _ParallelElement {
	SYNTAX_NODE_TYPE m_type = SYNTAX_NODE_TYPE_NONE;
	std::vector<std::shared_ptr<SyntaxNode>> m_nodes;
}ParallelElement;

class Parallel {
public:
	void AddNode(const std::shared_ptr<SyntaxNode> &node);
	void AddElement();
	void Truncation();
	bool CheckLastType(SYNTAX_NODE_TYPE type);
	void generate(std::stringstream& output);
	friend std::ostream &operator<<(std::ostream &out, Parallel &parallel);

private:
	void generate(std::map<SYNTAX_NODE_TYPE, std::set<std::shared_ptr<SyntaxNode>>> &level, std::stringstream& output);
private:
	std::vector<ParallelElement> m_nodes;
};


#endif