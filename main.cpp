#include <windows.h>
#include <shellapi.h>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include <iostream>

NOTIFYICONDATA nid;
HICON hIcon;
HWND hWnd;
UINT_PTR timerID;

byte points[16][16][8] = {
        {
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0}
        },{
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,0,0}
        },{
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0}
        },{
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0}
        },{
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,0,0}
        },{
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0}
        },{
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,0,0,0,0},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0}
        },{
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,0,0}
        },{
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0}
        },{
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,0,0,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0}
        },{
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
        }
};

byte FullBattery[16][16] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1},
        {1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1},
        {1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1},
        {1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1},
        {1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1},
        {1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1},
        {1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1},
        {1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1},
        {1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1},
        {1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1},
        {1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1},
        {1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1},
        {1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1},
        {1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

byte ErrorBattery[16][16] = {
        {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0}
};

// �o�b�e���[�c�ʂ��擾����֐�
int getBatteryLevel() {
    SYSTEM_POWER_STATUS status;
    if (GetSystemPowerStatus(&status)) {
        return static_cast<int>(status.BatteryLifePercent);
    }
    else {
        std::cerr << "�o�b�e���[�c�ʂ̎擾�Ɏ��s���܂����B" << std::endl;
        return -1;
    }
}

static int currentBatteryLevel = 0;


// �o�b�e���[�c�ʂɉ������A�C�R�����쐬����֐�
HICON createBatteryIcon(int batteryLevel) {
    HDC hdcScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, 16, 16);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);

    // �摜�f�[�^��������
    byte image[16][16] = { 0 };

    if (batteryLevel == 100) {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                image[i][j] = FullBattery[i][j];
            }
        }
    } else {
        int leftIndex = (batteryLevel < 10) ? 0 : batteryLevel / 10;
        int rightIndex = batteryLevel % 10;
        byte(*left)[8] = points[leftIndex];
        byte(*right)[8] = points[rightIndex];

        // �����ɔz�������
        for (int j = 0; j < 16; ++j) {
            for (int k = 0; k < 8; ++k) {
                image[j][k] = left[j][k]; // left������
                image[j][k + 8] = right[j][k]; // right������
            }
        }
    }

    // �r�b�g�}�b�v�ɉ摜�f�[�^��`��
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            COLORREF color = (image[y][x] == 1) ? RGB(0, 0, 0) : RGB(255, 255, 255);
            SetPixel(hdcMem, x, y, color);
        }
    }

    SelectObject(hdcMem, hOldBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);

    // �A�C�R������ݒ�
    ICONINFO iconInfo = { 0 };
    iconInfo.fIcon = TRUE; // �A�C�R�����w��
    iconInfo.xHotspot = 0;
    iconInfo.yHotspot = 0;
    iconInfo.hbmMask = hBitmap; // �}�X�N�r�b�g�}�b�v
    iconInfo.hbmColor = hBitmap; // �J���[�r�b�g�}�b�v

    // �A�C�R�����쐬
    HICON hIcon = CreateIconIndirect(&iconInfo);

    // �g�p�����r�b�g�}�b�v���폜
    DeleteObject(hBitmap);

    return hIcon;
}


// �^�X�N�g���C�A�C�R�����X�V����֐�
void updateBatteryIcon() {
    int batteryLevel = getBatteryLevel();
    if (batteryLevel != currentBatteryLevel) {
        currentBatteryLevel = batteryLevel;
        if (batteryLevel != -1) {
            HICON hNewIcon = createBatteryIcon(batteryLevel);
            if (hIcon) {
                DestroyIcon(hIcon);
            }
            hIcon = hNewIcon;
            nid.hIcon = hIcon;
            Shell_NotifyIcon(NIM_MODIFY, &nid);
        }
    }
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        timerID = SetTimer(hwnd, 1, 60000, NULL);
        break;
    case WM_TIMER:
        updateBatteryIcon();
        break;
    case WM_DESTROY:
        Shell_NotifyIcon(NIM_DELETE, &nid);
        if (hIcon) {
            DestroyIcon(hIcon);
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// ���C���֐�
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"BatteryIconClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    hWnd = CreateWindowEx(0, CLASS_NAME, L"Battery Icon", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    nid.cbSize = sizeof(nid);
    nid.hWnd = hWnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_USER + 1;
    Shell_NotifyIcon(NIM_ADD, &nid);

    updateBatteryIcon();

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}