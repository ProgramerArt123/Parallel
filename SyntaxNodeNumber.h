#ifndef __SYNTAX_NODE_NUMBER_H__
#define __SYNTAX_NODE_NUMBER_H__

#include "SyntaxNode.h"

class SyntaxNodeNumber : public SyntaxNode {
public:
	explicit SyntaxNodeNumber(int value);
	virtual ~SyntaxNodeNumber();
	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override {
		return GENERATE_PARALLEL_RESULT_COMPLETED;
	}
	const int GetValue();
private:
	int m_value;
};


#endif