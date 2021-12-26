#include "SyntaxNodeString.h"
#include "common.h"

SyntaxNodeString::SyntaxNodeString(SyntaxNodeScope &outer, const char *litera):
	SyntaxNode(outer, litera){
	m_type = SYNTAX_NODE_TYPE_STRING;
}

SyntaxNodeString::~SyntaxNodeString() {
	
}

int SyntaxNodeString::GetNO() {
	return m_NO;
}



void SyntaxNodeString::OutputInstructions(std::unique_ptr<Output>& output) {
	m_NO = output->GetConstNO();
	output->GetConstStream() << ".LC" << std::to_string(m_NO)<< ":" << std::endl;
	PLATFORM.StringGenerate(m_content.c_str(), output);
}