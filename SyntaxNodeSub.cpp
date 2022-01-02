#include "SyntaxNodeSub.h"
#include "common.h"

SyntaxNodeSub::SyntaxNodeSub(SyntaxNodeScope &outer, int line)
	:
	SyntaxNodeCompute(outer, line, "-"){
	m_type = SYNTAX_NODE_TYPE_SUB;
}

SyntaxNodeSub::~SyntaxNodeSub() {

}

void SyntaxNodeSub::OutputInstructions(std::unique_ptr<Output>& output) {
	output->Sub(*this, output);
}
