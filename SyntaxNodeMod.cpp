#include "SyntaxNodeMod.h"
#include "common.h"

SyntaxNodeMod::SyntaxNodeMod(SyntaxNodeScope &outer, int line) :
	SyntaxNodeCompute(outer, line, "%"){
	m_type = SYNTAX_NODE_TYPE_MOD;
}

SyntaxNodeMod::~SyntaxNodeMod() {
	
}

void SyntaxNodeMod::OutputInstructions(std::unique_ptr<Output>& output) {
	output->Mod(*this, output);
}

const char *SyntaxNodeMod::GetResultRegName() {
	return "rdx";
}