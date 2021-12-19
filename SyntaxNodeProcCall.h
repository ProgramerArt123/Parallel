#ifndef __SYNTAX_NODE_PROC_CALL_H__
#define __SYNTAX_NODE_PROC_CALL_H__

#include "SyntaxNode.h"
#include "SyntaxNodeScope.h"

class SyntaxNodeProcCall : public SyntaxNode {
public:
	explicit SyntaxNodeProcCall(const char *name, SyntaxNodeScope &scope);
	virtual ~SyntaxNodeProcCall();

	void FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) override;

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override ;

	void OutputInstructions(std::unique_ptr<Output>& output) override;
private:
	SyntaxNodeScope &m_scope;
};


#endif