
#include "common.h"
#include "SyntaxNodeScope.h"
#include "Scanner.h"
#include "SyntaxContent.h"
#include "SourceCodeFile.h"

void ProcDefEnter(const Lexical &lexical,  Content &content);
void ProcDefExit(const Lexical &lexical, Content &content);
SourceCodeFile::SourceCodeFile(const char *fileName):
	m_file_name(fileName), m_implicit(0){
	m_scopes.push(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(0)));
	m_config = GenerateConfig0();
		m_config->BindActionFunction("ProcDef", &ProcDefEnter, &ProcDefExit);
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


void ProcDefEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	const std::string &procName = lexical.GetChild(1)->GetContent();
	std::cout << "ProcDef:" << procName << std::endl;
	SyntaxNodeProcDef *procDef = new SyntaxNodeProcDef(*syntax.GetCurrentScope(),
		lexical.GetLineNO(), procName.c_str(),
		std::shared_ptr<DataType>(new DataTypeVoid(false, false, false)));
	std::shared_ptr<SyntaxNode> current(procDef);
	syntax.PushScope(procDef->GetBody());
}

void ProcDefExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}