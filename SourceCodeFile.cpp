#include <string.h>
#include "common.h"
#include "SyntaxNodeScope.h"
#include "Scanner.h"
#include "SyntaxContent.h"
#include "SourceCodeFile.h"

void ProcDefEnter(const Lexical &lexical,  Content &content);
void ProcDefExit(const Lexical &lexical, Content &content);
void VariableDef(const Lexical &lexical, Content &content);
SourceCodeFile::SourceCodeFile(const char *fileName):
	m_file_name(fileName), m_implicit(0){
	m_scopes.push(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(0)));
	m_config = GenerateConfig0();
		m_config->BindActionFunction("ProcDef", &ProcDefEnter, &ProcDefExit);
		m_config->BindActionFunction("VariableDef", &VariableDef);
}

SourceCodeFile::~SourceCodeFile() {
	m_scopes.pop();
}

void SourceCodeFile::Parse() throw (std::string) {
	SyntaxContent content(m_file_name, *m_config);
	content.Load();
	content.Parse();
	content.ForeachTryCommandAction();
}

void SourceCodeFile::OutputFile(std::unique_ptr<Output>& output) throw (std::exception) {
	m_scopes.top()->OutputFile(output);
}
bool SourceCodeFile::SearchKeyWord(const std::string keyWord, const Lexical &lexical) {
	return lexical.ForeachTopLeftRigthInterrupt([&](const Lexical &current){return keyWord == current.GetContent();});
}
std::shared_ptr<DataType> SourceCodeFile::ProduceDataType(const Lexical &lexical) {
	bool isConst = SearchKeyWord("const", lexical);
	bool isStatic = SearchKeyWord("static", lexical);
	bool isVolatile = SearchKeyWord("volatile", lexical);
	if (SearchKeyWord("int", lexical)) {		
		return std::shared_ptr<DataType>(new DataTypeInt(isConst, isStatic, isVolatile));
	}
	else if (SearchKeyWord("void", lexical)) {		
		return std::shared_ptr<DataType>(new DataTypeVoid(isConst, isStatic, isVolatile));
	}
	else {
		lexical.Error(" undefined");
	}
}

void ProcDefEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	const std::string &procName = lexical.GetChild(1)->GetContent();
	std::cout << "ProcDef:" << procName << std::endl;
	std::shared_ptr<SyntaxNodeProcDef> procDef(new SyntaxNodeProcDef(*syntax.GetCurrentScope(),
			lexical.GetLineNO(),
			procName.c_str(),
		SourceCodeFile::ProduceDataType(*lexical.GetChild(0))));
	syntax.PushScope(procDef->GetBody());
}

void ProcDefExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void VariableDef(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	const std::string &varName = lexical.GetChild(1)->GetContent();
	syntax.GetCurrentScope()->DecalreVariable(varName.c_str(), 
		SourceCodeFile::ProduceDataType(*lexical.GetChild(0)));
}
