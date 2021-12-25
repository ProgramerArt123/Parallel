#include "common.h"

#include "SyntaxNodeAdd.h"

SyntaxNodeAdd::SyntaxNodeAdd(SyntaxNodeScope &outer):
	SyntaxNodeCompute(outer, "+"){
	m_type = SYNTAX_NODE_TYPE_ADD;
}

SyntaxNodeAdd::~SyntaxNodeAdd() {

}



void SyntaxNodeAdd::OutputInstructions(std::unique_ptr<Output>& output) {
	output->Add(*this, output);
}

