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

void ForStateEnter(const Lexical &lexical, Content &content); 
void ForStateExit(const Lexical &lexical, Content &content);

void WhileStateEnter(const Lexical &lexical, Content &content); 
void WhileStateExit(const Lexical &lexical, Content &content);

void DoWhileStateEnter(const Lexical &lexical, Content &content); 
void DoWhileStateExit(const Lexical &lexical, Content &content);

void IfStateEnter(const Lexical &lexical, Content &content);
void IfStateExit(const Lexical &lexical, Content &content);
void ElseIfStateEnter(const Lexical &lexical, Content &content);
void ElseIfStateExit(const Lexical &lexical, Content &content);
void ElseStateEnter(const Lexical &lexical, Content &content);
void ElseStateExit(const Lexical &lexical, Content &content);


void SwitchStateEnter(const Lexical &lexical, Content &content);
void SwitchStateExit(const Lexical &lexical, Content &content);
void CaseStateEnter(const Lexical &lexical, Content &content);
void CaseStateExit(const Lexical &lexical, Content &content);

void VariableDef(const Lexical &lexical, Content &content);

void ProcCall(const Lexical &lexical, Content &content);
SourceCodeFile::SourceCodeFile(const char *fileName):
	m_file_name(fileName){
	m_config = GenerateConfig0();
		m_config->BindActionFunction("ProcDef", &ProcDefEnter, &ProcDefExit);
		m_config->BindActionFunction("VariableDef", &VariableDef);
		
		m_config->BindActionFunction("EnumDef", &EnumDef);
		m_config->BindActionFunction("StructDef", &StructDefEnter, &StructDefExit);
		m_config->BindActionFunction("UnionDef", &UnionDefEnter, &UnionDefExit);
		
		m_config->BindActionFunction("ForState", &ForStateEnter, &ForStateExit);
		m_config->BindActionFunction("WhileState", &WhileStateEnter, &WhileStateExit);
		m_config->BindActionFunction("DoWhileState", &DoWhileStateEnter, &DoWhileStateExit);
		
		m_config->BindActionFunction("IfState", &IfStateEnter, &IfStateExit);
		m_config->BindActionFunction("ElseIfState", &ElseIfStateEnter, &ElseIfStateExit);
		m_config->BindActionFunction("ElseState", &ElseStateEnter, ElseStateExit);
		
		m_config->BindActionFunction("Switch", &SwitchStateEnter, &SwitchStateExit);
		m_config->BindActionFunction("Case", &CaseStateEnter, CaseStateExit);
		
		m_config->BindActionFunction("ProcCall", &ProcCall);
		
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
	const std::string &varName = lexical.GetChild(1)->GetChild(1)->GetContent();
	syntax.GetCurrentScope()->DefineVariable(lexical);
}

void EnumDef(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	const std::string &enumName = lexical.GetChild(1)->GetContent();
	std::cout << "EnumDef:" << enumName << std::endl;
	syntax.GetCurrentScope()->DefineEnum(lexical);
}

void StructDefEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	const std::string &structName = lexical.GetChild(1)->GetChild(0)->GetContent();
	std::cout << "StructDef:" << structName << std::endl;
	syntax.PushScope(syntax.GetCurrentScope()->DefineStruct(lexical));
} 
void StructDefExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void UnionDefEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	const std::string &uinonName = lexical.GetChild(1)->GetChild(0)->GetContent();
	std::cout << "UnionDef:" << uinonName << std::endl;
	syntax.PushScope(syntax.GetCurrentScope()->DefineUnion(lexical));
}
void UnionDefExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void ForStateEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PushScope(syntax.GetCurrentScope()->AppendFor(lexical));
}
void ForStateExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void WhileStateEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PushScope(syntax.GetCurrentScope()->AppendWhile(lexical));
}

void WhileStateExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void DoWhileStateEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PushScope(syntax.GetCurrentScope()->AppendDoWhile(lexical));
}
void DoWhileStateExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void IfStateEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PushScope(syntax.GetCurrentScope()->AppendIf(lexical));
}
void IfStateExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void ElseIfStateEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PushScope(syntax.GetCurrentScope()->AppendElseIf(lexical));
}
void ElseIfStateExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void ElseStateEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PushScope(syntax.GetCurrentScope()->AppendElse(lexical));
}
void ElseStateExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void SwitchStateEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PushScope(syntax.GetCurrentScope()->AppendSwitch(lexical));
}
void SwitchStateExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void CaseStateEnter(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PushScope(syntax.GetCurrentScope()->AppendCase(lexical));
}
void CaseStateExit(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	syntax.PopScope();
}

void ProcCall(const Lexical &lexical, Content &content) {
	SyntaxContent &syntax = static_cast< SyntaxContent &>(content);
	const std::string &callName = lexical.GetChild(0)->GetContent();
	std::cout << "ProcCall:" << callName << std::endl;
	syntax.GetCurrentScope()->AppendProcCall(lexical);
}