#ifndef __SYNTAX_NODE_LOOP_H__
#define __SYNTAX_NODE_LOOP_H__

#include "SyntaxNode.h"
#include "SyntaxNodeScope.h"

class SyntaxNodeLoop : public SyntaxNode {
public:
	explicit SyntaxNodeLoop(SyntaxNodeScope &outter, int line);
	virtual ~SyntaxNodeLoop();
	void FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) override;
	
	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	std::shared_ptr<SyntaxNodeScope> &GetBody();
	void SetTimes(uint64_t times);
	void OutputInstructions(std::unique_ptr<Output>& output) override;
private:
	std::shared_ptr<SyntaxNodeScope> m_body;
};


#endif