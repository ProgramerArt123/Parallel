#ifndef __SYNTAX_CONTENT_H__
#define __SYNTAX_CONTENT_H__

#include <stack>
#include "Scanner.h"
class SyntaxNodeScope;

class SyntaxContent : public Content {
public:
	explicit SyntaxContent(const std::string fileName, const Config &config);
	virtual ~SyntaxContent();
private:
	std::stack<std::shared_ptr<SyntaxNodeScope>> m_scopes;
};

#endif