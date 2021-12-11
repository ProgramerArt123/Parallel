#include "SyntaxNodeMul.h"
#include "common.h"

SyntaxNodeMul::SyntaxNodeMul():
	SyntaxNode("*"){
	m_type = SYNTAX_NODE_TYPE_MUL;
}

SyntaxNodeMul::~SyntaxNodeMul() {

}

