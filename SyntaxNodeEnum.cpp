#include "SyntaxNodeEnum.h"
#include "common.h"

SyntaxNodeEnum::SyntaxNodeEnum(SyntaxNodeScope &scope,
	int line,
	const char *name, 
	size_t pos):
	SyntaxNode(scope,line, name){
		m_type = SYNTAX_NODE_TYPE_ENUM;
}

SyntaxNodeEnum::~SyntaxNodeEnum() {

}

void SyntaxNodeEnum::SetEnumValue(const char *name, int64_t value) {
	if(m_enums.find(name) != m_enums.end()) {
		Error(std::string(name) + " redefined!");
	}
	m_enums.insert(std::make_pair(name, value));
}
