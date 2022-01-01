#ifndef __SYNTAX_NODE_FOR_H__
#define __SYNTAX_NODE_FOR_H__

#include "SyntaxNode.h"
#include "SyntaxNodeScope.h"

class SyntaxNodeFor : public SyntaxNode {
public:
	explicit SyntaxNodeFor(SyntaxNodeScope &outter, int line);
	virtual ~SyntaxNodeFor();
	void FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) override;
	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;
	std::shared_ptr<SyntaxNodeScope> &GetWhole();
	void SetTimes(uint64_t times);
	void OutputInstructions(std::unique_ptr<Output>& output) override;
private:
	std::shared_ptr<SyntaxNodeScope> m_whole;
};


#endif