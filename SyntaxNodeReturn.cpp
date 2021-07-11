#include "SyntaxNodeReturn.h"
#include "common.h"

SyntaxNodeReturn::SyntaxNodeReturn():
	SyntaxNode("*"){
	m_type = SYNTAX_NODE_TYPE_RETURN;
}

SyntaxNodeReturn::~SyntaxNodeReturn() {

}

void SyntaxNodeReturn::FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	effectives.insert(self);
}

void SyntaxNodeReturn::generate(std::stringstream& output) {
	SYNTAX_NODE_TYPE value = m_children.front()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == value) {
		const int intValue = static_cast<SyntaxNodeNumber *>(m_children.front().get())->GetValue();
		output << '\t' << "movq	$" << std::to_string(intValue) << ", %rax" << std::endl;
	}
	else {
		
	}
}