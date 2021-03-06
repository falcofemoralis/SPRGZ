#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <CommCtrl.h>

extern DWORD threadStatus;

#define ID_BTN 20
#define ID_CB 30
#define ID_TEXT 40

// ��� �����
#define PAUSE 2
#define WORKING 1
#define CANCELED 0

// id UI ��������� 
#define btn_stop_id ID_BTN
#define btn_pause_id ID_BTN + 1
#define btn_startRead_id ID_BTN + 2
#define btn_startWrite_id ID_BTN + 3
#define cb_list_files_id ID_CB
#define cb_list_disks_id ID_CB + 1
#define cb_list_buffers_id ID_CB + 2
#define cb_list_testCounts_id ID_CB + 3
#define cb_list_modes_id ID_CB + 4
#define cb_buffering_id ID_CB + 5
#define text_read_id ID_TEXT
#define text_write_id ID_TEXT + 1	

// ��������� ����� �������
#define SEND_TEST_RESULT WM_APP + 1
#define SEND_PROGRESS_BAR_UPDATE WM_APP + 2

// ��������� �������, ������������ �� ���� ��� ���� �������� ��� ������������ ����� � ����������
struct Config {
    DWORD bufferSize;
    CONST TCHAR* mode;
    DWORD32 fileSize;
    CONST TCHAR* disk;
    DWORD countTests;
    DWORD typeTest;
    DWORD parentThreadId;
    BOOL isBuffering;
};

// ��������� � ����������� view ��������: x,y - ���������� �������, width,height - ������� view
struct ViewParam {
    DWORD x, y;
    DWORD width, height;
};

/////////////////////////////////// ������� ��� �������� ����������� ��������� ///////////////////////////////////

LRESULT CALLBACK wndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
VOID createBox(CONST TCHAR* nameBtn, ViewParam* params, HWND& hwnd, DWORD atr);
HWND createCombobox(CONST TCHAR* nameBox, ViewParam* params, CONST TCHAR* values[], DWORD countValues, DWORD id, HWND& hwnd);
HWND createButton(CONST TCHAR* nameBtn, ViewParam* params, DWORD id, HWND& hwnd);
HWND createText(CONST TCHAR* nameBtn, ViewParam* params, DWORD id, HWND& hwnd, DWORD isBold, DWORD size);
HWND createProgressBar(ViewParam* params, DWORD id, HWND& hwnd);
HWND* createRadioBtnGroup(CONST TCHAR* nameBtn, ViewParam* params, CONST TCHAR* values[], DWORD countValues, DWORD id, HWND& hwnd);
HWND createCheckBox(CONST TCHAR* text, ViewParam* params, DWORD id, HWND& hwnd);
VOID onCreate(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
VOID onCommand(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
VOID initConfig();
VOID startTest(DWORD);
VOID pauseTest();
VOID stopTest();
VOID setResult(TCHAR*);
