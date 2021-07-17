#ifndef __SYNTAX_NODE_SUB_H__
#define __SYNTAX_NODE_SUB_H__

#include "SyntaxNode.h"

class SyntaxNodeSub : public SyntaxNode {
public:
	explicit SyntaxNodeSub();
	virtual ~SyntaxNodeSub();

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	void OutputSerial(std::stringstream& output) override;
};


#endif