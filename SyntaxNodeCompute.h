#ifndef __SYNTAX_NODE_COMPUTE_H__
#define __SYNTAX_NODE_COMPUTE_H__

#include "SyntaxNode.h"

class SyntaxNodeCompute : public SyntaxNode {
public:
	explicit SyntaxNodeCompute(SyntaxNodeScope &outer, int line, const char *content = "", int priority = 0);
	virtual ~SyntaxNodeCompute();

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	int GetRightChildStackTopOffset()const;

	virtual const char *GetResultRegName();

	size_t CacheResultStackTopOffset(size_t pos);
	size_t CacheResultStackTopOffset();
protected:
	size_t m_cache_result_pos = 0;
};

#endif