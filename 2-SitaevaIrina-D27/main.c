#include <stdio.h>
#include <windows.h>
#include <psapi.h>
#include "queen_solver.h"

#define STRESS_TEST_BOARD_SIZE 10
#define DIV 1048576

/*
 
Working time 0.005636 s

Memory usage: 3276 MB

WindowsBuildLabEx                                       : 19041.1.amd64fre.vb_release.191206-1406
WindowsCurrentVersion                                   : 6.3
WindowsVersion                                          : 2009

CsManufacturer                                          : ASUSTeK COMPUTER INC.
CsModel                                                 : VivoBook_ASUSLaptop X512FL_A512FL
CsName                                                  : DESKTOP-SSQ2LLG
CsNumberOfLogicalProcessors                             : 8
CsNumberOfProcessors                                    : 1
CsProcessors                                            : {Intel(R) Core(TM) i5-8265U CPU @ 1.60GHz}

CsSystemType                                            : x64-based PC
CsTotalPhysicalMemory                                   : 8434110464
CsPhyicallyInstalledMemory                              : 8388608

OsForegroundApplicationBoost                            : Maximum
OsTotalVisibleMemorySize                                : 8236436
OsFreePhysicalMemory                                    : 2989568
OsTotalVirtualMemorySize                                : 11513236
OsFreeVirtualMemory                                     : 3871052
OsInUseVirtualMemory                                    : 7642184
OsTotalSwapSpaceSize                                    :
OsSizeStoredInPagingFiles                               : 3276800
OsFreeSpaceInPagingFiles                                : 3080404
*/

int main(){
	LARGE_INTEGER start, end, freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	
	Cell* ans = queen_task_solver(STRESS_TEST_BOARD_SIZE);
	for (unsigned i = 0; i < STRESS_TEST_BOARD_SIZE; i++)
		fprintf(stdout, "%u %u\n", ans[i].row, ans[i].colomn);
	
	QueryPerformanceCounter(&end);
	printf("Working time %f\n", (double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
	HINSTANCE hProcHandle = GetModuleHandle(NULL);
	PROCESS_MEMORY_COUNTERS_EX memory;
	GetProcessMemoryInfo(hProcHandle, &memory, sizeof(memory));
	
	printf("\nMemory usage: %u MB", memory.PrivateUsage/DIV);
	return 0;
}







