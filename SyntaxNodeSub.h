#ifndef __SYNTAX_NODE_SUB_H__
#define __SYNTAX_NODE_SUB_H__

#include "SyntaxNodeCompute.h"

class SyntaxNodeSub : public SyntaxNodeCompute {
public:
	explicit SyntaxNodeSub();
	virtual ~SyntaxNodeSub();

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	void OutputInstructions(std::unique_ptr<Output>& output) override;
};


#endif