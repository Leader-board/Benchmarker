#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#define opt1 43
#define opt2 46
#define opt3 16
// the set of optimisations that get enabled between O0 and O1
const char* optimisations[opt1] = { "-fauto-inc-dec",
"-fbranch-count-reg",
"-fcombine-stack-adjustments",
"-fcompare-elim",
"-fcprop-registers",
"-fdce",
"-fdefer-pop",
"-fdse",
"-fforward-propagate",
"-fguess-branch-probability",
"-fif-conversion",
"-fif-conversion2",
"-finline-functions-called-once",
"-fipa-profile",
"-fipa-pure-const",
"-fipa-reference",
"-fmerge-constants",
"-fmove-loop-invariants",
"-fomit-frame-pointer",
"-freorder-blocks",
"-fshrink-wrap",
"-fshrink-wrap-separate",
"-fsplit-wide-types",
"-fssa-backprop",
"-fssa-phiopt",
"-ftree-bit-ccp",
"-ftree-ccp",
"-ftree-ch",
"-ftree-coalesce-vars",
"-ftree-copy-prop",
"-ftree-dce",
"-ftree-dominator-opts",
"-ftree-dse",
"-ftree-forwprop",
"-ftree-fre",
"-ftree-phiprop",
"-ftree-pta",
"-ftree-scev-cprop",
"-ftree-sink",
"-ftree-slsr",
"-ftree-sra",
"-ftree-ter",
"-funit-at-a-time" };
// the set of optimisations that get enabled between O1 and O2
const char* optimisations2[opt2] = { "-falign-functions",
"-falign-jumps",
"-falign-labels",
"-falign-loops",
"-fcaller-saves",
"-fcode-hoisting",
"-fcrossjumping",
"-fcse-follow-jumps",
"-fcse-skip-blocks",
"-fdelete-null-pointer-checks",
"-fdevirtualize",
"-fdevirtualize-speculatively",
"-fexpensive-optimizations",
"-fgcse",
"-fgcse-lm",
"-fhoist-adjacent-loads",
"-finline-small-functions",
"-findirect-inlining",
"-fipa-bit-cp",
"-fipa-cp",
"-fipa-icf",
"-fipa-ra",
"-fipa-sra",
"-fipa-vrp",
"-fisolate-erroneous-paths-dereference",
"-flra-remat",
"-foptimize-sibling-calls",
"-foptimize-strlen",
"-fpartial-inlining",
"-fpeephole2",
"-freorder-blocks-algorithm=stc",
"-freorder-blocks-and-partition",
"-freorder-functions",
"-frerun-cse-after-loop",
"-fschedule-insns",
"-fschedule-insns2",
"-fsched-interblock",
"-fsched-spec",
"-fstore-merging",
"-fstrict-aliasing",
"-fthread-jumps",
"-ftree-builtin-call-dce",
"-ftree-pre",
"-ftree-switch-conversion",
"-ftree-tail-merge",
"-ftree-vrp" };
// the set of optimisations that get enabled between O2 and O3
const char* optimisations3[opt3] = { "-fgcse-after-reload",
"-finline-functions",
"-fipa-cp-clone",
"-floop-interchange",
"-floop-unroll-and-jam",
"-fpeel-loops",
"-fpredictive-commoning",
"-fsplit-paths",
"-ftree-loop-distribute-patterns",
"-ftree-loop-distribution",
"-ftree-loop-vectorize",
"-ftree-partial-pre",
"-ftree-slp-vectorize",
"-funswitch-loops",
"-fvect-cost-model",
"-fversion-loops-for-strides"
};
using namespace std;
int main(int argc, char* argv[])
{
	int mode = -1; // O1 or O2?
	if (argc !=3)
	{
		printf("Arguments: flag filename\n");
		exit(-1);
	}
	else if (strcmp(argv[1], "O0") == 0)
	{
		mode = 1;
	}
	else if (strcmp(argv[1], "O1") == 0)
	{
		mode = 2;
	}
	else if (strcmp(argv[1], "O2") == 0)
	{
		mode = 3;
	}
	elsegggggggg
	{
		printf("Arguments: flag filename\n");
		exit(-1);
	}
	if (mode == 1)
	{
		for (int i = 0; i < opt1 * 1 - 1; i++)
		{
			string str = "g++";
			str = str + " -o " + "bench " + "benchmark.cpp " + optimisations[i % opt1];
			const char* c = str.c_str();
			system(c);
			string str2 = "./bench ";
			str2 = str2 + argv[2] + " " + optimisations[i % opt1];
			const char* c2 = str2.c_str();
			system(c2);
		}
	}
	else if (mode == 2)
	{
		for (int i = 0; i < opt2 * 1 - 1; i++)
		{
			string str = "g++";
			str = str + " -o " + "bench " + "benchmark.cpp " + optimisations2[i % opt2] + " -O1";
			const char* c = str.c_str();
			system(c);
			string str2 = "./bench ";
			str2 = str2 + argv[2] + " " + optimisations2[i % opt1];
			const char* c2 = str2.c_str();
			system(c2);
		}
	}
	else if (mode == 3)
	{
		for (int i = 0; i < opt3 * 1 - 1; i++)
		{
			string str = "g++";
			str = str + " -o " + "bench " + "benchmark.cpp " + optimisations3[i % opt3] + " -O2";
			const char* c = str.c_str();
			system(c);
			string str2 = "./bench ";
			str2 = str2 + argv[2] + " " + optimisations3[i % opt1];
			const char* c2 = str2.c_str();
			system(c2);
		}
	}
	return 0;
}