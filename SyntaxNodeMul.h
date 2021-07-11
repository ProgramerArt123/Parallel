#ifndef __SYNTAX_NODE_MUL_H__
#define __SYNTAX_NODE_MUL_H__

#include "SyntaxNode.h"

class SyntaxNodeMul : public SyntaxNode {
public:
	explicit SyntaxNodeMul();
	virtual ~SyntaxNodeMul();

	void generate(std::stringstream& output) override;
};


#endif