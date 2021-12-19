#include "SyntaxNodeMod.h"
#include "common.h"

SyntaxNodeMod::SyntaxNodeMod():
	SyntaxNodeCompute("%"){
	m_type = SYNTAX_NODE_TYPE_MOD;
}

SyntaxNodeMod::~SyntaxNodeMod() {
	
}

void SyntaxNodeMod::OutputInstructions(std::unique_ptr<Output>& output) {
	output->Mod(*this);
}

const char *SyntaxNodeMod::GetResultRegName() {
	return "rdx";
}