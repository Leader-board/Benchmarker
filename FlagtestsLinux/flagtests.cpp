#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#define opt1 132
#define opt2 46
#define opt3 16
// the set of optimisations that get enabled between O0 and O1
const char* optimisations[opt1] = { "-faggressive-loop-optimizations","-fasynchronous-unwind-tables",
"-fauto-inc-dec",
"-fbranch-count-reg","-fchkp-check-incomplete-type",
"-fchkp-check-read",
"-fchkp-check-write","-fchkp-instrument-calls",
"-fchkp-narrow-bounds",
"-fchkp-optimize","-fchkp-store-bounds",
"-fchkp-use-static-bounds","-fchkp-use-static-const-bounds",
"-fchkp-use-wrappers","-fcombine-stack-adjustments",
"-fcommon",
"-fcompare-elim",
"-fcprop-registers","-fdefer-pop",
"-fdelete-null-pointer-checks",
"-fdwarf2-cfi-asm","-fearly-inlining",
"-feliminate-unused-debug-types",
"-fexceptions","-fforward-propagate",
"-ffp-int-builtin-inexact",
"-ffunction-cse",
"-fgcse-lm","-fgnu-runtime",
"-fgnu-unique",
"-fguess-branch-probability",
"-fident","-fif-conversion",
"-fif-conversion2",
"-finline",
"-finline-atomics","-finline-functions-called-once",
"-fipa-profile",
"-fipa-pure-const","-fipa-reference",
"-fira-hoist-pressure",
"-fira-share-save-slots","-fira-share-spill-slots",
"-fivopts",
"-fkeep-static-consts","-fleading-underscore",
"-flifetime-dse",
"-flto-odr-type-merging",
"-fmath-errno","-fmerge-constants",
"-fmerge-debug-strings",
"-fmove-loop-invariants","-fomit-frame-pointer",
"-fpeephole",
"-fplt",
"-fprefetch-loop-arrays","-freg-struct-return",
"-freorder-blocks",
"-fsched-critical-path-heuristic","-fsched-dep-count-heuristic",
"-fsched-group-heuristic",
"-fsched-interblock","-fsched-last-insn-heuristic",
"-fsched-rank-heuristic",
"-fsched-spec","-fsched-spec-insn-heuristic",
"-fsched-stalled-insns-dep",
"-fschedule-fusion","-fsemantic-interposition",
"-fshow-column",
"-fshrink-wrap","-fshrink-wrap-separate",
"-fsigned-zeros",
"-fsplit-ivs-in-unroller","-fsplit-wide-types",
"-fssa-backprop",
"-fssa-phiopt",
"-fstdarg-opt","-fstrict-volatile-bitfields",
"-fsync-libcalls",
"-ftoplevel-reorder","-ftrapping-math",
"-ftree-bit-ccp",
"-ftree-builtin-call-dce",
"-ftree-ccp","-ftree-ch",
"-ftree-coalesce-vars",
"-ftree-copy-prop",
"-ftree-cselim",
"-ftree-dce","-ftree-dominator-opts",
"-ftree-dse",
"-ftree-forwprop",
"-ftree-fre","-ftree-loop-if-convert",
"-ftree-loop-im",
"-ftree-loop-ivcanon","-ftree-loop-optimize",
"-ftree-parallelize-loops=4",
"-ftree-phiprop",
"-ftree-pta","-ftree-reassoc",
"-ftree-scev-cprop",
"-ftree-sink",
"-ftree-slsr",
"-ftree-sra","-ftree-ter",
"-funit-at-a-time",
"-funwind-tables",
"-fverbose-asm","-fzero-initialized-in-bss",
"-m128bit-long-double",
"-m64",
"-m80387","-malign-stringops",
"-mavx256-split-unaligned-load","-mavx256-split-unaligned-store",
"-mfancy-math-387",
"-mfp-ret-in-387",
"-mfxsr","-mglibc",
"-mieee-fp",
"-mlong-double-80",
"-mmmx",
"-mno-sse4",
"-mpush-args",
"-mred-zone","-msse",
"-msse2",
"-mstv",
"-mtls-direct-seg-refs",
"-mvzeroupper" };
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