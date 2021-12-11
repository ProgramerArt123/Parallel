#ifndef __SYNTAX_NODE_PROC_CALL_H__
#define __SYNTAX_NODE_PROC_CALL_H__

#include "SyntaxNode.h"
#include "Scope.h"

class SyntaxNodeProcCall : public SyntaxNode {
public:
	explicit SyntaxNodeProcCall(const char *name, Scope &scope);
	virtual ~SyntaxNodeProcCall();

	void FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) override;

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override ;

	void OutputInstructions(std::unique_ptr<Output>& output) override;
private:
	Scope &m_scope;
};


#endif