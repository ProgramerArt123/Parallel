#include "SyntaxNodeMul.h"
#include "common.h"

SyntaxNodeMul::SyntaxNodeMul(SyntaxNodeScope &outer):
	SyntaxNodeCompute(outer, "*"){
	m_type = SYNTAX_NODE_TYPE_MUL;
}

SyntaxNodeMul::~SyntaxNodeMul() {

}

void SyntaxNodeMul::OutputInstructions(std::unique_ptr<Output>& output) {
	output->Mul(*this, output);
}
