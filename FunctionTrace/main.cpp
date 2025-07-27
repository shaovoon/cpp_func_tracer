#include <cstdio>
#include "FunctionTracer.h"

void MyFunc()
{
	FT;
}

int main()
{
	FunctionTracer::EnablePrintFileLocation(false);

	FT;
	
	MyFunc();
	
	return 0;
}
