
#include "common.h"
#include "SyntaxNodeScope.h"
#include "Scanner.h"
#include "SyntaxContent.h"
#include "SourceCodeFile.h"

void ProcDef(const Lexical &lexical, const Content &content);

SourceCodeFile::SourceCodeFile(const char *fileName):
	m_file_name(fileName), m_implicit(0){
	m_scopes.push(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(0)));
	m_config = GenerateConfig0();
		m_config->BindActionFunction("ProcDef", &ProcDef);
}

SourceCodeFile::~SourceCodeFile() {
	m_scopes.pop();
}

void SourceCodeFile::Parse() throw (std::string) {
	SyntaxContent content(m_file_name, *m_config);
	content.Load();
	content.Parse();
	content.ForeachLexical();
}

void SourceCodeFile::OutputFile(std::unique_ptr<Output>& output) throw (std::exception) {
	m_scopes.top()->OutputFile(output);
}


void ProcDef(const Lexical &lexical, const Content &content) {
	const SyntaxContent &syntax = static_cast<const SyntaxContent &>(content);
	std::cout << "ProcDef:" << lexical.GetChild(1)->GetContent() << std::endl;

}
