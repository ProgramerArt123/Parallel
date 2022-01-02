#include <string.h>
#include "common.h"
#include "SyntaxContent.h"

SyntaxContent::SyntaxContent(const std::string fileName, const Config &config)
	: Content(fileName, config) {
	m_scopes.push(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(0)));
}

SyntaxContent::~SyntaxContent() {
	m_scopes.pop();
}

const std::shared_ptr<SyntaxNodeScope> &SyntaxContent::GetCurrentScope() const {
	if (m_scopes.empty()) {
		throw std::string("scopes is empty!");
	}
	return m_scopes.top();
}
void SyntaxContent::PushScope(const std::shared_ptr<SyntaxNodeScope> &scope) {
	m_scopes.push(scope);
}
std::shared_ptr<SyntaxNodeScope> SyntaxContent::PopScope() {
	const std::shared_ptr<SyntaxNodeScope> top = GetCurrentScope();
	m_scopes.pop();
	return top;
}
std::shared_ptr<DataType> SyntaxContent::ProduceDataType(const char *type, bool isConst, bool isStatic, bool isVolatile) {
	if (0 == strcmp(type, "int")) {		
		return std::shared_ptr<DataType>(new DataTypeInt(isConst, isStatic, isVolatile));
	}
	else if (0 == strcmp(type, "void")) {		
		return std::shared_ptr<DataType>(new DataTypeVoid(isConst, isStatic, isVolatile));
	}
	else {
		throw error_info(std::string(type) + " undefined");
	}
}