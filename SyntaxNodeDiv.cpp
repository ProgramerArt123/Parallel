#include "SyntaxNodeDiv.h"
#include "common.h"

SyntaxNodeDiv::SyntaxNodeDiv():
	SyntaxNode("/"){
	m_type = SYNTAX_NODE_TYPE_DIV;
}

SyntaxNodeDiv::~SyntaxNodeDiv() {

}
