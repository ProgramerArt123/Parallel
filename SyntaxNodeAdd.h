#ifndef __SYNTAX_NODE_ADD_H__
#define __SYNTAX_NODE_ADD_H__

#include "SyntaxNode.h"

class SyntaxNodeAdd : public SyntaxNode {
public:
	explicit SyntaxNodeAdd();
	virtual ~SyntaxNodeAdd();

	void generate(std::stringstream& output) override;
};


#endif