#include "SyntaxNodeMul.h"
#include "common.h"

SyntaxNodeMul::SyntaxNodeMul():
	SyntaxNodeCompute("*"){
	m_type = SYNTAX_NODE_TYPE_MUL;
}

SyntaxNodeMul::~SyntaxNodeMul() {

}

void SyntaxNodeMul::OutputInstructions(std::unique_ptr<Output>& output) {
	output->Mul(*this);
}
