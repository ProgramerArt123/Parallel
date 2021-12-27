#include <string.h>
#include "common.h"
#include "SyntaxNodeString.h"


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

void SyntaxNodeString::ArgmentCache(uint32_t index, std::unique_ptr<Output>& output) {
	std::string dst;
	if (index < PLATFORM.registersCount) {
		dst = std::string("%") + PLATFORM.registers[index];
	}
	else {
		dst = "-" + std::to_string(GetOuter()->PushArgument()) + "(%rbp)";
	}
	if (index < PLATFORM.registersCount && 0 == strcmp(PLATFORM.registers[index], "rcx")) {
		output->GetStream() << '\t' << "movq	" << dst << ", -" << 
			GetOuter()->PushRegister(dst.c_str()) << "(%rbp)" << std::endl;
	}
	PLATFORM.ProcStringArgmentGenerateSerial(GetNO(), dst.c_str(), output->GetStream());
}