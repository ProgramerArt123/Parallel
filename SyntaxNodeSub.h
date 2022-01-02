#ifndef __SYNTAX_NODE_SUB_H__
#define __SYNTAX_NODE_SUB_H__

#include "SyntaxNodeCompute.h"

class SyntaxNodeSub : public SyntaxNodeCompute {
public:
	explicit SyntaxNodeSub(SyntaxNodeScope &outer, int line);
	virtual ~SyntaxNodeSub();

	void OutputInstructions(std::unique_ptr<Output>& output) override;
};


#endif