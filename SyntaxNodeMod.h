#ifndef __SYNTAX_NODE_MOD_H__
#define __SYNTAX_NODE_MOD_H__

#include "SyntaxNodeCompute.h"

class SyntaxNodeMod : public SyntaxNodeCompute {
public:
	explicit SyntaxNodeMod(SyntaxNodeScope &outer);
	virtual ~SyntaxNodeMod();

	void OutputInstructions(std::unique_ptr<Output>& output) override;

	const char *GetResultRegName() override;
};


#endif