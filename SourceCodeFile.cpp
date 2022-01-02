
#include "common.h"
#include "SyntaxNodeScope.h"
#include "Content.h"
#include "Generate.h"
#include "SourceCodeFile.h"
std::shared_ptr<Config> GetConfig0();

SourceCodeFile::SourceCodeFile(const char *fileName):
	m_file_name(fileName){
	m_scopes.push(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(0)));
		m_config = GetConfig0();
}

SourceCodeFile::~SourceCodeFile() {
	m_scopes.pop();
}

void SourceCodeFile::Parse() throw (std::string) {
	Content content(m_file_name, *m_config);
	content.Load();
	content.Parse();
	content.ForeachLexical();
}

void SourceCodeFile::OutputFile(std::unique_ptr<Output>& output) throw (std::exception) {
	m_scopes.top()->OutputFile(output);
}