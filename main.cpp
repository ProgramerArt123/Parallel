#include <iostream>

#include "common.h"

#include "SerialOutput.h"
#include "ParallelOutput.h"
#include "SourceCodeFile.h"

int main() {
	try {
		source.reset(new SourceCodeFile("test.p"));
		source->Parse();
		std::unique_ptr<Output> serial(new SerialOutput("test1.s"));
		source->OutputFile(serial);
		std::unique_ptr<Output> parallel(new ParallelOutput("test2.s"));
		source->OutputFile(parallel);
	}
	catch (const std::string &e) {
		std::cerr << e << std::endl;
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}