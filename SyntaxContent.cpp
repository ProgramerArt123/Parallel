
#include "common.h"
#include "SyntaxContent.h"

SyntaxContent::SyntaxContent(const std::string fileName, const Config &config)
	: Content(fileName, config) {
	m_scopes.push(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(0)));
}

SyntaxContent::~SyntaxContent() {
	m_scopes.pop();
}

std::shared_ptr<SyntaxNodeScope> &SyntaxContent::GetCurrentScope()  {
	if (m_scopes.empty()) {
		throw std::string("scopes is empty!");
	}
	return m_scopes.top();
}
void SyntaxContent::PushScope(const std::shared_ptr<SyntaxNodeScope> scope) {
	m_scopes.push(scope);
}
std::shared_ptr<SyntaxNodeScope> SyntaxContent::PopScope() {
	const std::shared_ptr<SyntaxNodeScope> top = GetCurrentScope();
	m_scopes.pop();
	return top;
}
