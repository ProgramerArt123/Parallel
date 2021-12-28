#ifndef __SERIAL_OUTPUT_H__
#define __SERIAL_OUTPUT_H__

#include "Output.h"

class SerialOutput : public Output {
public:
	explicit SerialOutput(const char *filePath);

	void Assignment(SyntaxNodeAssignment &assign, std::unique_ptr<Output>& output) override;

	void ProcessScope(SyntaxNodeScope &scope, std::unique_ptr<Output>& output) override;
private:

	void ComputeOne(const SyntaxNodeCompute &one, const char *instructions, std::unique_ptr<Output>& output) override;


};

#endif