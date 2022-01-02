#ifndef __SYNTAX_NODE_ADD_H__
#define __SYNTAX_NODE_ADD_H__

#include "SyntaxNodeCompute.h"

class SyntaxNodeAdd : public SyntaxNodeCompute {
public:
	explicit SyntaxNodeAdd(SyntaxNodeScope &outer, int line);
	virtual ~SyntaxNodeAdd();
	
	void OutputInstructions(std::unique_ptr<Output>& output) override;
	
};


#endif