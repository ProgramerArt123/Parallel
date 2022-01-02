#ifndef __SYNTAX_NODE_ASSIGNMENT_H__
#define __SYNTAX_NODE_ASSIGNMENT_H__

#include "SyntaxNode.h"

class SyntaxNodeScope;

class SyntaxNodeAssignment : public SyntaxNode {
public:
	explicit SyntaxNodeAssignment(SyntaxNodeScope &scope, int line);
	virtual ~SyntaxNodeAssignment();

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	void OutputInstructions(std::unique_ptr<Output>& output) override;
	
};


#endif