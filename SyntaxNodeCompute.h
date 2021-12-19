#ifndef __SYNTAX_NODE_COMPUTE_H__
#define __SYNTAX_NODE_COMPUTE_H__

#include "SyntaxNode.h"

class SyntaxNodeCompute : public SyntaxNode {
public:
	explicit SyntaxNodeCompute(const char *content = "", int priority = 0);
	virtual ~SyntaxNodeCompute();

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	int GetRightChildStackTop()const;

	virtual const char *GetResultRegName();
};

#endif