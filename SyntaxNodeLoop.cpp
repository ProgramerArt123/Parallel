#include "SyntaxNodeLoop.h"
#include "common.h"

SyntaxNodeLoop::SyntaxNodeLoop(Scope &outter) :
	m_body(std::shared_ptr<Scope>(new Scope(outter))){
	m_type = SYNTAX_NODE_TYPE_LOOP;
}

SyntaxNodeLoop::~SyntaxNodeLoop() {

}

std::shared_ptr<Scope> &SyntaxNodeLoop::GetBody() {
	return m_body;
}


void SyntaxNodeLoop::generate(std::stringstream& output) {
	static int loopCount = 0;
	output << '\t' << "movq    $1, %rcx" << std::endl;
	output << '\t' << "jmp	.LL" << std::to_string(loopCount) << std::endl;
	output << ".LL" << std::to_string(loopCount+1) << ":" << std::endl;
	output << '\t' << "addq    $1,  %rcx" << std::endl;
	output << ".LL" << std::to_string(loopCount) << ":" << std::endl;
	m_body->LoopGenerate(output);
	output << '\t' << "setle   %al" << std::endl;
	output << '\t' << "testb   %al, %al" << std::endl;
	output << '\t' << "jne	.LL" << std::to_string(loopCount+1) << "" << std::endl;
	loopCount += 2;
}
