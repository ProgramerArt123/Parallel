#ifndef __SYNTAX_TREE_H__
#define __SYNTAX_TREE_H__

#include <list>
#include <vector>
#include <set>
#include <memory>
#include <exception>

#include "Parallel.h"
#include "SyntaxNode.h"

class SyntaxTree : public SyntaxNode {
public:
	explicit SyntaxTree();
	explicit SyntaxTree(SyntaxNode &parent);
	virtual ~SyntaxTree();

	void FindEffectives(std::set<std::shared_ptr<SyntaxNode>> &effectives);

	void GenerateParallel(std::set<std::shared_ptr<SyntaxNode>> &effectives) throw (std::exception);
	
	friend std::ostream &operator<<(std::ostream &out, SyntaxTree &tree);
protected:
	Parallel m_nodes;
};


#endif