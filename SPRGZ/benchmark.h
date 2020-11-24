#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdio.h>
#include <strsafe.h>
#include <utility>   
#include <CommCtrl.h>

#define KB 1024
#define MB KB*1024
#define GB MB*1024
#define RESULT pair <DWORD, DOUBLE>

using namespace std;

// ��������� �������, ������������ �� ���� ��� ���� �������� ��� ������������ ����� � ����������
struct Config {
    DWORD bufferSize;
    DWORD mode;
    DWORD32 fileSize;
	CONST TCHAR* disk;
    DWORD countTests;
};
extern Config userConfig;

DWORD WINAPI writeTest(LPVOID); // ���� �� ������
DWORD WINAPI readTest(LPVOID); // ���� �� ������
DWORD getModeFromType(CONST TCHAR*);
RESULT writeToFile(HANDLE, DWORD);
RESULT readFromFile(HANDLE, DWORD, DWORD);
VOID ExitTestThread(HANDLE&);
VOID SaveResults(DOUBLE*, DWORD, TCHAR[]);
VOID createTestFile(TCHAR[]);

