#ifndef __SYNTAX_NODE_DIV_H__
#define __SYNTAX_NODE_DIV_H__

#include "SyntaxNodeCompute.h"

class SyntaxNodeDiv : public SyntaxNodeCompute {
public:
	explicit SyntaxNodeDiv(SyntaxNodeScope &outer);
	virtual ~SyntaxNodeDiv();

	void OutputInstructions(std::unique_ptr<Output>& output) override;

};


#endif