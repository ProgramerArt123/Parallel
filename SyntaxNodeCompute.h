#ifndef __SYNTAX_NODE_COMPUTE_H__
#define __SYNTAX_NODE_COMPUTE_H__

#include "SyntaxNode.h"

class SyntaxNodeCompute : public SyntaxNode {
public:
	explicit SyntaxNodeCompute(const char *content = "", int priority = 0);
	virtual ~SyntaxNodeCompute();

	int GetRightChildStackTop()const;
};

#endif