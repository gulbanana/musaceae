#include <engine/core.h>
#include "Windows.h"
using namespace std;

void debug::print(string output)
{
	OutputDebugStringA(output.c_str());
}