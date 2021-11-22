#include <iostream>

void yyerror(char* e);

#include "common.h"

#include "lex.yy.c"
#include "y.tab.c"

void yyerror(char* e) {
	int line = yyget_lineno();
	printf("line:%d\n", line);
	perror(e);
};



int main() {
	std::cout << "Hello World!" << std::endl;
	
	scopes.push(std::shared_ptr<Scope>(new Scope));

	FILE *in = fopen("/mnt/hgfs/H/Users/Administrator/source/repos/ConsoleApplication1/ConsoleApplication1/test.p", "r");
	if (in) {
		printf("123\n");
		yyin = in;
		yyparse();
		fclose(in);
	}
	else {
		printf("456\n");
	}
	
	//tree.AddChild(current);
	std::cout << scopes.top() << std::endl;

	//std::shared_ptr<SyntaxNode> root = tree.AddChild(new SyntaxNode("="));

	//std::shared_ptr<SyntaxNode> a(new SyntaxNode("a", 3));
	//std::shared_ptr<SyntaxNode> b(new SyntaxNode("b", 3));
	//{
	//	root->AddChild(new SyntaxNode("c", 3));
	//}
	//	
	//{
	//	std::shared_ptr<SyntaxNode> sub = root->AddChild(new SyntaxNode("-", 1));

	//	{
	//		std::shared_ptr<SyntaxNode> add = sub->AddChild(new SyntaxNode("+", 1));

	//		{

	//			std::shared_ptr<SyntaxNode> add1 = add->AddChild(new SyntaxNode("+", 1));

	//			{
	//				std::shared_ptr<SyntaxNode> mul = add1->AddChild(new SyntaxNode("*", 2));
	//				mul->AddChild(a);
	//				mul->AddChild(b);
	//			}

	//			{
	//				std::shared_ptr<SyntaxNode> mul = add1->AddChild(new SyntaxNode("*", 2));
	//				mul->AddChild(a);
	//				mul->AddChild(b);
	//			}

	//		}

	//		{
	//			std::shared_ptr<SyntaxNode> div = add->AddChild(new SyntaxNode("/", 2));
	//			div->AddChild(a);
	//			div->AddChild(b);
	//		}
	//	}

	//	{
	//		std::shared_ptr<SyntaxNode> mod = sub->AddChild(new SyntaxNode("%", 2));
	//		mod->AddChild(a);
	//		mod->AddChild(b);
	//	}

	//}
	//
	//std::cout << tree << std::endl;

	try {
		//scopes.top()->ChangeChildrenPositionByDepend();
		//std::cout << scopes.top() << std::endl;
		scopes.top()->FindEffectives();
		scopes.top()->GenerateParallel();
		scopes.top()->OutputSerial("test.s");
		scopes.top()->OutputParallel("test2.s");
	}
	catch (const std::exception &e) {
		std::cout << *scopes.top() << std::endl;
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}