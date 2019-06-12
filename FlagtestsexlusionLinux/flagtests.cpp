/*
Similar to the original version but with each optimisation flag set to disabled rather than enabling. Has no use on /O0.
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#define opt1 43
#define opt2 46
#define opt3 16
// the set of optimisations that get enabled between O0 and O1
const char* optimisations[opt1] = { "-fno-auto-inc-dec",
"-fno-branch-count-reg",
"-fno-combine-stack-adjustments",
"-fno-compare-elim",
"-fno-cprop-registers",
"-fno-dce",
"-fno-defer-pop",
"-fno-dse",
"-fno-forward-propagate",
"-fno-guess-branch-probability",
"-fno-if-conversion",
"-fno-if-conversion2",
"-fno-inline-functions-called-once",
"-fno-ipa-profile",
"-fno-ipa-pure-const",
"-fno-ipa-reference",
"-fno-merge-constants",
"-fno-move-loop-invariants",
"-fno-omit-frame-pointer",
"-fno-reorder-blocks",
"-fno-shrink-wrap",
"-fno-shrink-wrap-separate",
"-fno-split-wide-types",
"-fno-ssa-backprop",
"-fno-ssa-phiopt",
"-fno-tree-bit-ccp",
"-fno-tree-ccp",
"-fno-tree-ch",
"-fno-tree-coalesce-vars",
"-fno-tree-copy-prop",
"-fno-tree-dce",
"-fno-tree-dominator-opts",
"-fno-tree-dse",
"-fno-tree-forwprop",
"-fno-tree-fre",
"-fno-tree-phiprop",
"-fno-tree-pta",
"-fno-tree-scev-cprop",
"-fno-tree-sink",
"-fno-tree-slsr",
"-fno-tree-sra",
"-fno-tree-ter",
"-fno-unit-at-a-time" };
// the set of optimisations that get enabled between O1 and O2
const char* optimisations2[opt2] = { "-fno-align-functions",
"-fno-align-jumps",
"-fno-align-labels",
"-fno-align-loops",
"-fno-caller-saves",
"-fno-code-hoisting",
"-fno-crossjumping",
"-fno-cse-follow-jumps",
"-fno-cse-skip-blocks",
"-fno-delete-null-pointer-checks",
"-fno-devirtualize",
"-fno-devirtualize-speculatively",
"-fno-expensive-optimizations",
"-fno-gcse",
"-fno-gcse-lm",
"-fno-hoist-adjacent-loads",
"-fno-inline-small-functions",
"-fno-indirect-inlining",
"-fno-ipa-bit-cp",
"-fno-ipa-cp",
"-fno-ipa-icf",
"-fno-ipa-ra",
"-fno-ipa-sra",
"-fno-ipa-vrp",
"-fno-isolate-erroneous-paths-dereference",
"-fno-lra-remat",
"-fno-optimize-sibling-calls",
"-fno-optimize-strlen",
"-fno-partial-inlining",
"-fno-peephole2",
"-fno-reorder-blocks-algorithm=stc",
"-fno-reorder-blocks-and-partition",
"-fno-reorder-functions",
"-fno-rerun-cse-after-loop",
"-fno-schedule-insns",
"-fno-schedule-insns2",
"-fno-sched-interblock",
"-fno-sched-spec",
"-fno-store-merging",
"-fno-strict-aliasing",
"-fno-thread-jumps",
"-fno-tree-builtin-call-dce",
"-fno-tree-pre",
"-fno-tree-switch-conversion",
"-fno-tree-tail-merge",
"-fno-tree-vrp" };
// the set of optimisations that get enabled between O2 and O3
const char* optimisations3[opt3] = { "-fno-gcse-after-reload",
"-fno-inline-functions",
"-fno-ipa-cp-clone",
"-fno-loop-interchange",
"-fno-loop-unroll-and-jam",
"-fno-peel-loops",
"-fno-predictive-commoning",
"-fno-split-paths",
"-fno-tree-loop-distribute-patterns",
"-fno-tree-loop-distribution",
"-fno-tree-loop-vectorize",
"-fno-tree-partial-pre",
"-fno-tree-slp-vectorize",
"-fno-unswitch-loops",
"-fno-vect-cost-model",
"-fno-version-loops-for-strides"
};
using namespace std;
int main(int argc, char* argv[])
{
	int mode = -1; // O1, O2 or O3?
	if (argc != 3)
	{
		printf("Arguments: flag filename\n");
		exit(-1);
	}
	else if (strcmp(argv[1], "O1") == 0)
	{
		mode = 1;
	}
	else if (strcmp(argv[1], "O2") == 0)
	{
		mode = 2;
	}
	else if (strcmp(argv[1], "O3") == 0)
	{
		mode = 3;
	}
	else
	{
		printf("Arguments: flag filename\n");
		exit(-1);
	}
	if (mode == 1)
	{
		for (int i = 0; i < opt1 * 1 - 1; i++)
		{
			string str = "g++";
			str = str + " -o " + "bench " + "benchmark.cpp " + optimisations2[i % opt1] + " -O1";
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
			str = str + " -o " + "bench " + "benchmark.cpp " + optimisations2[i % opt2] + " -O2";
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
			str = str + " -o " + "bench " + "benchmark.cpp " + optimisations3[i % opt3] + " -O3";
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
