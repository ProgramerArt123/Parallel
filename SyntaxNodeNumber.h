#ifndef __SYNTAX_NODE_NUMBER_H__
#define __SYNTAX_NODE_NUMBER_H__

#include "SyntaxNode.h"

class SyntaxNodeNumber : public SyntaxNode {
public:
	explicit SyntaxNodeNumber(SyntaxNodeScope &outer, int value);
	virtual ~SyntaxNodeNumber();
	
	void OutputInstructions(std::unique_ptr<Output>& output) override;
	
	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;
	bool IsSameDataType(DATA_TYPE_TYPE type) override;	
	const int GetValue();
private:
	int m_value;
};


#endif