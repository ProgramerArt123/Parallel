#ifndef __SYNTAX_NODE_MUL_H__
#define __SYNTAX_NODE_MUL_H__

#include "SyntaxNodeCompute.h"

class SyntaxNodeMul : public SyntaxNodeCompute {
public:
	explicit SyntaxNodeMul(SyntaxNodeScope &outer);
	virtual ~SyntaxNodeMul();

	void OutputInstructions(std::unique_ptr<Output>& output) override;
};


#endif