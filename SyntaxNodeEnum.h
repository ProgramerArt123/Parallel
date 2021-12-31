#ifndef _SYNTAX_NODE_ENUM_H_
#define _SYNTAX_NODE_ENUM_H_

#include <string>
#include <map>
#include <stdint.h>
#include "SyntaxNode.h"

class SyntaxNodeEnum : public SyntaxNode {
public:
	explicit SyntaxNodeEnum(SyntaxNodeScope &scope,
		int line,
		const char *name,
		size_t pos);
	virtual ~SyntaxNodeEnum();

	void SetEnumValue(const char *name, int64_t value);
private:
	std::map<std::string, int64_t> m_enums;

};

#endif