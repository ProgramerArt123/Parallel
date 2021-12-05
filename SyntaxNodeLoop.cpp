#include "SyntaxNodeLoop.h"
#include "common.h"

SyntaxNodeLoop::SyntaxNodeLoop(Scope &outter) :
	SyntaxNode(*static_cast<SyntaxNode *>(&outter), "LOOP"),
	m_body(std::shared_ptr<Scope>(new Scope(outter, "LOOP"))){
	m_type = SYNTAX_NODE_TYPE_LOOP;
}

SyntaxNodeLoop::~SyntaxNodeLoop() {

}

void SyntaxNodeLoop::FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	effectives.insert(self);
	m_body->FindEffectives();
}

GENERATE_PARALLEL_RESULT SyntaxNodeLoop::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) {
	m_body->GenerateParallel();
	return GENERATE_PARALLEL_RESULT_COMPLETED;
}

std::shared_ptr<Scope> &SyntaxNodeLoop::GetBody() {
	return m_body;
}


void SyntaxNodeLoop::OutputSerial(std::stringstream& output) {
	static int loopCount = 0;
	output << '\t' << "movq    $1, %rcx" << std::endl;
	output << '\t' << "jmp	.LL" << std::to_string(loopCount) << std::endl;
	output << ".LL" << std::to_string(loopCount+1) << ":" << std::endl;
	output << '\t' << "addq    $1,  %rcx" << std::endl;
	output << ".LL" << std::to_string(loopCount) << ":" << std::endl;
	m_body->LoopGenerateSerial(output);
	output << '\t' << "setl   %al" << std::endl;
	output << '\t' << "testb   %al, %al" << std::endl;
	output << '\t' << "jne	.LL" << std::to_string(loopCount+1) << "" << std::endl;
	loopCount += 2;
}

void SyntaxNodeLoop::OutputParallel(std::stringstream& output) {
	static int loopCount = 0;
	output << '\t' << "movq    $1, %rcx" << std::endl;
	output << '\t' << "jmp	.LL" << std::to_string(loopCount) << std::endl;
	output << ".LL" << std::to_string(loopCount + 1) << ":" << std::endl;
	output << '\t' << "addq    $1,  %rcx" << std::endl;
	output << ".LL" << std::to_string(loopCount) << ":" << std::endl;
	m_body->LoopGenerateParallel(output);
	output << '\t' << "setl   %al" << std::endl;
	output << '\t' << "testb   %al, %al" << std::endl;
	output << '\t' << "jne	.LL" << std::to_string(loopCount + 1) << "" << std::endl;
	loopCount += 2;
}