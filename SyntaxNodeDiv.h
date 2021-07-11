#ifndef __SYNTAX_NODE_DIV_H__
#define __SYNTAX_NODE_DIV_H__

#include "SyntaxNode.h"

class SyntaxNodeDiv : public SyntaxNode {
public:
	explicit SyntaxNodeDiv();
	virtual ~SyntaxNodeDiv();

	void generate(std::stringstream& output) override;
};


#endif