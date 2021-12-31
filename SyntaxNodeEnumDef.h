#ifndef _SYNTAX_NODE_ENUM_DEF_H_
#define _SYNTAX_NODE_ENUM_DEF_H_

#include <string>
#include <map>
#include <stdint.h>
#include "SyntaxNode.h"

class SyntaxNodeEnumDef : public SyntaxNode {
public:
	explicit SyntaxNodeEnumDef(SyntaxNodeScope &scope,
		int line,
		const char *name,
		size_t pos);
	virtual ~SyntaxNodeEnumDef();

	void SetEnumValue(const char *name, int64_t value);
private:
	std::map<std::string, int64_t> m_enums;

};

#endif