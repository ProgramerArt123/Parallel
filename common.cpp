#include "common.h"

std::unique_ptr<SourceCodeFile> source;

void PushStatement() {
	source->m_scopes.top()->PushStatement();
}

void PushReturn() {
	source->m_scopes.top()->PushReturn();
}

void PushAssignmentStatement() {
	source->m_scopes.top()->PushAssignmentStatement();
}
void PushInitStatement() {
	source->m_scopes.top()->PushInitStatement();
}
void DecalreVariable() {
//	source->m_scopes.top()->DecalreVariable();
}
void SetVariableName(const char *variable){
//	source->m_scopes.top()->SetVariableName(variable);
}
void PushAddAssign(const char *variable) {
	source->m_scopes.top()->PushAddAssign(variable);
}
void PushAdd() {
	source->m_scopes.top()->PushAdd();
}

void PushSub() {
	source->m_scopes.top()->PushSub();
}

void PushMul() {
	source->m_scopes.top()->PushMul();
}

void PushDiv() {
	source->m_scopes.top()->PushDiv();
}

void PushMod() {
	source->m_scopes.top()->PushMod();
}
void PushInc(const char *variable, bool isBack) {
	source->m_scopes.top()->PushInc(variable, isBack);
}
void PushBlock() {
	source->m_scopes.top()->PushBlock();
}

void PushString(const char *itera) {
	source->m_scopes.top()->PushString(itera);
}

void PushNumber(int number) {
	source->m_scopes.top()->PushNumber(number);
}

void PushVariable(const char *name) {
	source->m_scopes.top()->PushVariable(name);
}

void AddArgment(uint64_t argment) {
	source->m_scopes.top()->AddArgment(argment);
}

void PushLoopEnter() {
	source->m_scopes.push(source->m_scopes.top()->PushLoopEnter());
}

void PushLoopExit() {
	source->m_scopes.pop(); source->m_scopes.top()->PushLoopExit();
}



void AddParam(const char *param) {
	source->m_scopes.top()->AddParam(param);
}

void PushProcCallEnter(const char *name) {
	source->m_scopes.push(source->m_scopes.top()->PushProcCallEnter(name));
}

void PushProcCallExit() {
	source->m_scopes.pop(); source->m_scopes.top()->PushProcCallExit();
}

void PushType(const char *type, bool isConst){
	source->m_scopes.top()->PushType(type, isConst);
}