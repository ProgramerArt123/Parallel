#ifndef __SYNTAX_NODE_LOOP_H__
#define __SYNTAX_NODE_LOOP_H__

#include "SyntaxNode.h"
#include "Scope.h"

class SyntaxNodeLoop : public SyntaxNode {
public:
	explicit SyntaxNodeLoop(Scope &outter);
	virtual ~SyntaxNodeLoop();
	std::shared_ptr<Scope> &GetBody();
	void SetTimes(uint64_t times);
	void generate(std::stringstream& output) override;
private:
	std::shared_ptr<Scope> m_body;
};


#endif