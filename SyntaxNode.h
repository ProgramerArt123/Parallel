#ifndef __SYNTAX_NODE_H__
#define __SYNTAX_NODE_H__

#include <list>
#include <vector>
#include <set>
#include <memory>
#include <exception>
#include <iostream>
#include <sstream>
#include "SyntaxNodeType.h"
#include "GenerateParallelResult.h"
#include "Output.h"
#include "DataTypeType.h"

class Lexical;
class Parallel;
class SyntaxNodeScope;
class DataType;

class SyntaxNode {
public:
	explicit SyntaxNode(int line, const char *content = "", int priority = 0);
	explicit SyntaxNode(SyntaxNodeScope &outer, int line, const char *content = "", int priority = 0);
	virtual ~SyntaxNode();
	virtual void FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives);

	std::shared_ptr<SyntaxNode> AddChild(SyntaxNode *child);

	void AddChild(std::shared_ptr<SyntaxNode> child);

	void AddChildFront(std::shared_ptr<SyntaxNode> child);

	void AddChildBack(std::shared_ptr<SyntaxNode> child);

	virtual GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception);

	GENERATE_PARALLEL_RESULT GenerateParallelSelf(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel);

	const char* GetContent()const;

	size_t GetChildrenCount();

	SYNTAX_NODE_TYPE GetType();

	int GetLine();
	
	bool IsOutermost() const;
	
	SyntaxNodeScope *GetOuter() const;
	
	size_t SetResultPos(size_t pos);
	
	size_t GetResultPos() const;

	virtual void OutputInstructions(std::unique_ptr<Output>& output);

	virtual bool IsSameDataType(DATA_TYPE_TYPE type);
	
	virtual void ArgmentCache(uint32_t index, std::unique_ptr<Output>& output);	
	
	friend std::ostream &operator<<(std::ostream &out, SyntaxNode &node);
protected:
	static uint64_t StatisticsKeyWord(const std::string keyWord, const Lexical &lexical);
	void InsertChild(std::shared_ptr<SyntaxNode> &child,
		std::list<std::shared_ptr<SyntaxNode>>::iterator childItor);

	std::list<std::shared_ptr<SyntaxNode>>::iterator RemoveChild(
		std::list<std::shared_ptr<SyntaxNode>>::iterator childItor);

	std::list<std::shared_ptr<SyntaxNode>>::iterator MoveChild(
		std::list<std::shared_ptr<SyntaxNode>>::iterator childItor);

	void SetDeep(int deep);
	
	static std::shared_ptr<DataType> ProduceDataType(const Lexical &lexical);
	
	void Error(uint64_t line, const std::string &info)const throw (std::string);
public:
	std::list<std::shared_ptr<SyntaxNode>> m_children;
	int m_generate_line = 0;
protected:
	std::string m_content;
	int m_deep = 0;
	SyntaxNodeScope *m_outer = NULL;
	
	SYNTAX_NODE_TYPE m_type = SYNTAX_NODE_TYPE_NONE;

	uint64_t m_parallel_index = UINT64_MAX;

	const int m_line = 0;
	
	size_t m_result_pos = 0;

protected:
	friend class SerialOutput;
	friend class ParallelOutput;
private:
	
	static bool SearchKeyWord(const std::string keyWord, const Lexical &lexical);
};


#endif