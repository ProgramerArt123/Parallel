#ifndef __SYNTAX_NODE_ASSIGNMENT_H__
#define __SYNTAX_NODE_ASSIGNMENT_H__

#include "SyntaxNode.h"

class Scope;

class SyntaxNodeAssignment : public SyntaxNode {
public:
	explicit SyntaxNodeAssignment(Scope &scope);
	virtual ~SyntaxNodeAssignment();

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	void OutputInstructions(std::unique_ptr<Output>& output) override;
	
private:
	Scope &m_scope;
};


#endif