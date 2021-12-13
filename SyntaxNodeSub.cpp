#include "SyntaxNodeSub.h"
#include "common.h"

SyntaxNodeSub::SyntaxNodeSub():
	SyntaxNodeCompute("-"){
	m_type = SYNTAX_NODE_TYPE_SUB;
}

SyntaxNodeSub::~SyntaxNodeSub() {

}

void SyntaxNodeSub::OutputInstructions(std::unique_ptr<Output>& output) {
	output->Sub(*this);
}
