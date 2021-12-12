#ifndef __SYNTAX_NODE_PROC_DEF_H__
#define __SYNTAX_NODE_PROC_DEF_H__

#include "SyntaxNode.h"
#include "Scope.h"

class SyntaxNodeVariable;

class SyntaxNodeProcDef : public SyntaxNode {
public:
	explicit SyntaxNodeProcDef(const char *name, Scope &outter);
	virtual ~SyntaxNodeProcDef();

	std::shared_ptr<Scope> &GetBody();
	
	void FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) override;
	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	void OutputInstructions(std::unique_ptr<Output>& output) override;
	friend std::ostream &operator<<(std::ostream &out, SyntaxNodeProcDef &def);

private:
	void OutputHead(std::stringstream& output);
	void OutputTail(std::stringstream& output);

	unsigned int m_NO = 0;
private:
	std::shared_ptr<Scope> m_body;
	
};


#endif