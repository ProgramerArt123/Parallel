#include "common.h"

std::stack<std::shared_ptr<Scope>> scopes;

std::stringstream consts;

void PushStatement() {
	scopes.top()->PushStatement();
}

void PushReturn() {
	scopes.top()->PushReturn();
}

void PushAssignmentStatement(const char *variable) {
	scopes.top()->PushAssignmentStatement(variable);
}

void PushAdd() {
	scopes.top()->PushAdd();
}

void PushSub() {
	scopes.top()->PushSub();
}

void PushMul() {
	scopes.top()->PushMul();
}

void PushDiv() {
	scopes.top()->PushDiv();
}

void PushMod() {
	scopes.top()->PushMod();
}

void PushBlock() {
	scopes.top()->PushBlock();
}

void PushString(const char *itera) {
	scopes.top()->PushString(itera);
}

void PushNumber(int number) {
	scopes.top()->PushNumber(number);
}

void PushVariable(const char *name) {
	scopes.top()->PushVariable(name);
}

void AddArgment(uint64_t argment) {
	scopes.top()->AddArgment(argment);
}

void PushLoopEnter() {
	scopes.push(scopes.top()->PushLoopEnter());
}

void PushLoopExit() {
	scopes.pop(); scopes.top()->PushLoopExit();
}

void PushProcDefEnter(const char *name) {
	scopes.push(scopes.top()->PushProcDefEnter(name));
}

void PushProcDefExit() {
	scopes.pop(); scopes.top()->PushProcDefExit();
}

void AddParam(const char *param) {
	scopes.top()->AddParam(param);
}

void PushProcCallEnter(const char *name) {
	scopes.top()->PushProcCallEnter(name);
}

void PushProcCallExit() {
	scopes.top()->PushProcCallExit();
}