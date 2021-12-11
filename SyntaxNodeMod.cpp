#include "SyntaxNodeMod.h"
#include "common.h"

SyntaxNodeMod::SyntaxNodeMod():
	SyntaxNode("%"){
	m_type = SYNTAX_NODE_TYPE_MOD;
}

SyntaxNodeMod::~SyntaxNodeMod() {
	
}
