#ifndef __SYNTAX_NODE_INC_H__
#define __SYNTAX_NODE_INC_H__

#include "SyntaxNodeCompute.h"

class SyntaxNodeInc : public SyntaxNodeCompute {
public:
	explicit SyntaxNodeInc(SyntaxNodeScope &outer, bool isBack);
	virtual ~SyntaxNodeInc();
	
	void OutputInstructions(std::unique_ptr<Output>& output) override;
	
private:
	
	const bool m_is_back = true;
	
};


#endif