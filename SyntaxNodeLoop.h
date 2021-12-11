#ifndef __SYNTAX_NODE_LOOP_H__
#define __SYNTAX_NODE_LOOP_H__

#include "SyntaxNode.h"
#include "Scope.h"

class SyntaxNodeLoop : public SyntaxNode {
public:
	explicit SyntaxNodeLoop(Scope &outter);
	virtual ~SyntaxNodeLoop();

	void FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) override;

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	std::shared_ptr<Scope> &GetBody();
	void SetTimes(uint64_t times);
	void OutputInstructions(std::unique_ptr<Output>& output) override;
private:
	std::shared_ptr<Scope> m_body;
};


#endif