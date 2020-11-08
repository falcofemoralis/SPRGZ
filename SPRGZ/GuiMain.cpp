#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <CommCtrl.h>

#define cb_list_disks_id 1
#define cb_list_buffers_id 2
#define cb_list_testCounts_id 3
#define cb_list_types_id 4
#define btn_stop_id 5
#define btn_pause_id 6
#define btn_start_id 7

#define KB 1024
#define MB KB*1024
#define GB MB*1024

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

const char* types[] = { "WRITE_THROUGH", "RANDOM_ACCESS", "SEQUENTIAL", "NO_BUFFERING"};
const char* buffNames[] = { "1 KB", "4 KB", "8 KB", "1 MB", "2 MB", "4 MB", "8 MB", "16 MB" };
int buffSizes[] = { 1 * KB, 4 * KB, 8 * KB, 1 * MB, 2 * MB, 4 * MB, 8 * MB, 16 * MB };
const char* disks[] = { "���� �", "���� �" };
const char* testCounts[] = { "1", "2", "3", "4", "5" };

struct Config {
	int bufferSize;
	const char* type;
	const char* diskPath;
};

Config userConfig;


int main() {
	WNDCLASS wcl;

	memset(&wcl, 0, sizeof(WNDCLASS));
	wcl.lpszClassName = "my window";
	wcl.lpfnWndProc = WndProc;
	RegisterClass(&wcl);

	HWND hwnd;
	hwnd = CreateWindow("my Window", "Disk benchmark", WS_OVERLAPPEDWINDOW, 10, 10, 550, 480, NULL, NULL, NULL, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}

	return 0;
}

// ��������� � ����������� view ��������: x,y - ���������� �������, width,height - ������� view
struct ViewParam {
	int x, y;
	int width, height;
};

// ������� �������� Combobox
void createCombobox(const char* nameBox, ViewParam* params, const char* values[], int countValues, int id, HWND& hwnd) {
	HWND dropList;
	dropList = CreateWindow("combobox", nameBox, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, params->x, params->y, params->width, params->height, hwnd, (HMENU)id, NULL, NULL);

	for (int i = 0; i < countValues; ++i)
		SendMessage(dropList, CB_ADDSTRING, 0, LPARAM(values[i]));
	SendMessage(dropList, CB_SETCURSEL, 0, 0);
}

void createButton(const char* nameBtn, ViewParam* params, int id, HWND& hwnd) {
	HWND btn_start = CreateWindow("button", nameBtn, WS_VISIBLE | WS_CHILD, params->x, params->y, params->width, params->height, hwnd, (HMENU)id, NULL, NULL);
}

void createText(const char* nameBtn, ViewParam* params, int id, HWND& hwnd) {
	HWND btn_start = CreateWindow("static", nameBtn, WS_VISIBLE | WS_CHILD | SS_CENTER, params->x, params->y, params->width, params->height, hwnd, (HMENU)id, NULL, NULL);
}

void createProgressBar(ViewParam* params, int id, HWND& hwnd) {
	HWND progBar = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_VISIBLE | WS_CHILD, params->x, params->y, params->width, params->height, hwnd, (HMENU)id, NULL, NULL);

	//��������� �������� 0-2
	SendMessage(progBar, PBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 2));

	//��������� ���
	SendMessage(progBar, PBM_SETSTEP, (WPARAM)1, 0); //��� 1

	//����������� ��������� �� 1 �������
	SendMessage(progBar, PBM_STEPIT, 0, 0);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
	case WM_CREATE:
		ViewParam params;

		createCombobox("�����", new ViewParam{ 10, 10, 180, 400 }, disks, sizeof(disks) / sizeof(disks[0]), cb_list_disks_id, hwnd);
		createCombobox("���-�� ������", new ViewParam{ 200, 10, 50, 500 }, testCounts, sizeof(testCounts) / sizeof(testCounts[0]), cb_list_testCounts_id, hwnd);
		createCombobox("������ ������", new ViewParam{ 260, 10, 100, 500 }, buffNames, sizeof(buffNames) / sizeof(buffNames[0]), cb_list_buffers_id, hwnd);
		createCombobox("����", new ViewParam{ 370, 10, 150, 500 }, types, sizeof(types) / sizeof(types[0]), cb_list_types_id, hwnd);

		createButton("�����", new ViewParam{ 400, 40, 120, 30 }, btn_start_id, hwnd);
		createButton("�����", new ViewParam{ 400, 80, 120, 30 }, btn_pause_id, hwnd);
		createButton("����", new ViewParam{ 400, 120, 120, 30 }, btn_stop_id, hwnd);

		createButton("�����", new ViewParam{ 400, 40, 120, 30 }, btn_start_id, hwnd);
		createButton("�����", new ViewParam{ 400, 80, 120, 30 }, btn_pause_id, hwnd);
		createButton("����", new ViewParam{ 400, 120, 120, 30 }, btn_stop_id, hwnd);


		createText("������", new ViewParam{ 50, 60, 100, 20 }, NULL, hwnd);
		createText("������", new ViewParam{ 250, 60, 100, 20 }, NULL, hwnd);

		createText("130 MB/s", new ViewParam{ 50, 100, 100, 20 }, NULL, hwnd);
		createText("250 MB/s", new ViewParam{ 250, 100, 100, 20 }, NULL, hwnd);

		createProgressBar(new ViewParam{ 10, 160, 510, 30 }, NULL, hwnd);
		break;
	case WM_COMMAND:

		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			int selectedId = SendMessage(HWND(lParam), CB_GETCURSEL, 0, 0);
			switch (LOWORD(wParam))
			{
			case cb_list_types_id:
				userConfig.type = types[selectedId];
				break;
			case cb_list_buffers_id:
				userConfig.bufferSize = buffSizes[selectedId];
				break;
			}
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProcA(hwnd, message, wParam, lParam);
}
