#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdio.h>
#include <strsafe.h>
#include <utility>   

#define KB 1024
#define MB KB*1024
#define GB MB*1024
#define RESULT pair <DWORD, DOUBLE>

using namespace std;

// ��������� �������, ������������ �� ���� ��� ���� �������� ��� ������������ ����� � ����������
struct Config {
    DWORD bufferSize;
    DWORD mode;
    DWORD fileSize;
    const TCHAR* disk;
    DWORD countTests;
};
extern Config userConfig;

void writeTest(); // ���� �� ������
void readTest(); // ���� �� ������
int getModeFromType(const char* type);
//int getDisks(const char* disks[]);

