#include "common.h"

#include "SyntaxNodeInc.h"

SyntaxNodeInc::SyntaxNodeInc(SyntaxNodeScope &outer, bool isBack)
	: SyntaxNodeCompute(outer, "++")
	, m_is_back(isBack) {
	m_type = SYNTAX_NODE_TYPE_INC;
}

SyntaxNodeInc::~SyntaxNodeInc() {

}

void SyntaxNodeInc::OutputInstructions(std::unique_ptr<Output>& output) {
	SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>(m_children.front().get());
	variable->OutputInstructions(output);
	output->GetStream() << '\t' << "movq	-" << 
		m_children.front()->GetResultPos() << "(%rbp), %rax" << std::endl;
	GetOuter()->PopCache();
	if (m_is_back){		
		output->GetStream() << '\t' << "movq	%rax, -" << 
			SetResultPos(GetOuter()->PushCache()) << "(%rbp)" << std::endl;
		output->GetStream() << "\taddq	$1, %rax" << std::endl;
		output->GetStream() << '\t' << "movq	%rax, -" << 
			variable->GetScopeStackTopOffset() << "(%rbp)" << std::endl;
	}
	else{
		output->GetStream() << "\taddq	$1, %rax" << std::endl;
		output->GetStream() << '\t' << "movq	%rax, -" << 
			variable->GetScopeStackTopOffset() << "(%rbp)" << std::endl;
		output->GetStream() << '\t' << "movq	%rax, -" << 
			SetResultPos(GetOuter()->PushCache()) << "(%rbp)" << std::endl;
	}
}

