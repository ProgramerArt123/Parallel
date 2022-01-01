#ifndef __SYNTAX_NODE_PROC_CALL_H__
#define __SYNTAX_NODE_PROC_CALL_H__

#include "SyntaxNode.h"

class SyntaxNodeProcCall : public SyntaxNode {
public:
	explicit SyntaxNodeProcCall(SyntaxNodeScope &scope, int line, const char *name);
	virtual ~SyntaxNodeProcCall();
	
	//std::shared_ptr<SyntaxNodeScope> &GetArgments();

	void FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) override;

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override ;

	void OutputInstructions(std::unique_ptr<Output>& output) override;
	
private:
	
	void BeginCallGenerate(std::unique_ptr<Output>& output);
	void EndCallGenerate(std::stringstream& output);
	
private:
	std::vector<std::shared_ptr<SyntaxNodeScope>> m_arguments;
};


#endif