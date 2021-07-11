#include "SyntaxNodeString.h"
#include "common.h"

SyntaxNodeString::SyntaxNodeString(const char *litera):
	SyntaxNode(litera){
	m_type = SYNTAX_NODE_TYPE_STRING;
}

SyntaxNodeString::~SyntaxNodeString() {
	
}

int SyntaxNodeString::GetNO() {
	return m_NO;
}

void SyntaxNodeString::generate(std::stringstream& output) {
	static unsigned int NO = 0;
	m_NO = NO ++;
	consts << ".LC" << std::to_string(m_NO)<< ":" << std::endl;
	PLATFORM.StringGenerate(m_content.c_str(), output);
}