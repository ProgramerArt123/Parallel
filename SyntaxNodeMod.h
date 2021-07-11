#ifndef __SYNTAX_NODE_MOD_H__
#define __SYNTAX_NODE_MOD_H__

#include "SyntaxNode.h"

class SyntaxNodeMod : public SyntaxNode {
public:
	explicit SyntaxNodeMod();
	virtual ~SyntaxNodeMod();

	void generate(std::stringstream& output) override;
};


#endif