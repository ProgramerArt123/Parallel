#include "SyntaxNodeDiv.h"
#include "common.h"

SyntaxNodeDiv::SyntaxNodeDiv(SyntaxNodeScope &outer, int line)
	:
	SyntaxNodeCompute(outer, line, "/"){
	m_type = SYNTAX_NODE_TYPE_DIV;
}

SyntaxNodeDiv::~SyntaxNodeDiv() {

}

void SyntaxNodeDiv::OutputInstructions(std::unique_ptr<Output>& output) {
	output->Div(*this, output);
}