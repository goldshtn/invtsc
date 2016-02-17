#include <intrin.h>
#include <stdio.h>
#include <string.h>

#define CPUID_MAX_EXTENDED_LEAF  0x80000000
#define CPUID_INVARIANT_TSC_LEAF 0x80000007
#define CPUID_INVARIANT_TSC_MASK 0x00000100

int main(int argc, char *argv[])
{
	int info[4];
	unsigned long long tsc;
	int verbose;

	if (argc > 1 && strcmp(argv[1], "-h") == 0)
	{
		printf("INVTSC - Print the CPU clock cycle counter as reported by rdtsc\n\n");
		printf("Usage: invtsc [-v]\n\n");
		printf("	-v	prints whether invariant TSC is supported\n");
		return 0;
	}

	verbose = argc > 1 && strcmp(argv[1], "-v") == 0;
	if (verbose)
	{
		__cpuid(info, CPUID_MAX_EXTENDED_LEAF);
		if (info[0] >= CPUID_INVARIANT_TSC_LEAF)
		{
			__cpuid(info, CPUID_INVARIANT_TSC_LEAF);
			if ((info[3] & CPUID_INVARIANT_TSC_MASK) != 0)
			{
				printf("Invariant TSC supported.\n");
			}
			else
			{
				printf("Invariant TSC is not supported.\n");
			}
		}
	}

	tsc = __rdtsc();
	printf("%llu\n", tsc);

	return 0;
}