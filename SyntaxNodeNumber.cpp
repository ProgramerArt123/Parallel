#include "SyntaxNodeNumber.h"

SyntaxNodeNumber::SyntaxNodeNumber(int value):
	SyntaxNode(std::to_string(value).c_str()),
	m_value(value){
	m_type = SYNTAX_NODE_TYPE_NUMBER;
}

SyntaxNodeNumber::~SyntaxNodeNumber() {

}

const int SyntaxNodeNumber::GetValue() {
	return m_value;
}