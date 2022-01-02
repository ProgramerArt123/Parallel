#ifndef __SYNTAX_CONTENT_H__
#define __SYNTAX_CONTENT_H__

#include <stack>
#include "Scanner.h"
class SyntaxNodeScope;

class SyntaxContent : public Content {
public:
	explicit SyntaxContent(const std::string fileName, const Config &config);
	virtual ~SyntaxContent();
	const std::shared_ptr<SyntaxNodeScope> &GetCurrentScope() const;
	void PushScope(const std::shared_ptr<SyntaxNodeScope> &scope);
	std::shared_ptr<SyntaxNodeScope> PopScope();
private:
	std::shared_ptr<DataType> ProduceDataType(const char *type, bool isConst, bool isStatic, bool isVolatile);
	std::stack<std::shared_ptr<SyntaxNodeScope>> m_scopes;
};

#endif