#include <string.h>
#include "common.h"
#include "SyntaxNodeScope.h"
#include "Scanner.h"
#include "SyntaxContent.h"
#include "SourceCodeFile.h"

void ProcDefEnter(const Lexical &lexical,  Content &content);
void ProcDefExit(const Lexical &lexical, Content &content);

void EnumDef(const Lexical &lexical, Content &content); 

void StructDefEnter(const Lexical &lexical, Content &content); 
void StructDefExit(const Lexical &lexical, Content &content);

void UnionDefEnter(const Lexical &lexical, Content &content); 
void UnionDefExit(const Lexical &lexical, Content &content);

void VariableDef(const Lexical &lexical, Content &content);
SourceCodeFile::SourceCodeFile(const char *fileName):
	m_file_name(fileName){
	m_config = GenerateConfig0();
		m_config->BindActionFunction("ProcDef", &ProcDefEnter, &ProcDefExit);
		m_config->BindActionFunction("VariableDef", &VariableDef);
		
		m_config->BindActionFunction("EnumDef", &EnumDef);
		m_config->BindActionFunction("StructDef", &StructDefEnter, &StructDefExit);
		m_config->BindActionFunction("UnionDef", &UnionDefEnter, &UnionDefExit);
	m_content.reset(new SyntaxContent(m_file_name, *m_config));
}

SourceCodeFile::~SourceCodeFile() {
}

void SourceCodeFile::Parse() throw (std::string) {
	m_content->Load();
	m_content->Parse();
	m_content->ForeachTryCommandAction();
}

void SourceCodeFile::OutputFile(std::unique_ptr<Output>& output) throw (std::exception) {
	//m_scopes.top()->OutputFile(output);
	m_content->GetCurrentScope()->OutputFile(output);
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
	else if (SearchKeyWord("double", lexical)) {		
		return std::shared_ptr<DataType>(new DataTypeDouble(isConst, isStatic, isVolatile));
	}
	else {
		lexical.Error(" undefined");
	}
}

void ProcDefEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	const std::string &procName = lexical.GetChild(1)->GetContent();
	std::cout << "ProcDef:" << procName << std::endl;
	syntax.PushScope(syntax.GetCurrentScope()->DefineProc(lexical));
}

void ProcDefExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void VariableDef(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	const std::string &varName = lexical.GetChild(1)->GetContent();
	syntax.GetCurrentScope()->DefineVariable(lexical);
}

void EnumDef(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	const std::string &enumName = lexical.GetChild(1)->GetContent();
	std::cout << "EnumDef:" << enumName << std::endl;
	syntax.GetCurrentScope()->DefineEnum(lexical);
}

void StructDefEnter(const Lexical &lexical, Content &content) {
} 
void StructDefExit(const Lexical &lexical, Content &content) {
}

void UnionDefEnter(const Lexical &lexical, Content &content) {
}
void UnionDefExit(const Lexical &lexical, Content &content) {
}