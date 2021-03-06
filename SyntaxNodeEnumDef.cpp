#include "SyntaxNodeEnumDef.h"
#include "common.h"

SyntaxNodeEnumDef::SyntaxNodeEnumDef(SyntaxNodeScope &scope,
	int line,
	const char *name, 
	size_t pos):
	SyntaxNode(scope,line, name){
		m_type = SYNTAX_NODE_TYPE_ENUM_DEF;
}

SyntaxNodeEnumDef::~SyntaxNodeEnumDef() {

}

void SyntaxNodeEnumDef::SetEnumValue(const char *name, int64_t value) {
	if(m_enums.find(name) != m_enums.end()) {
		Error(GetLine(), std::string(name) + " redefined!");
	}
	m_enums.insert(std::make_pair(name, value));
}
