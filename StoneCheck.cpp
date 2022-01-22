// StoneCheck.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "StoneCheck.h"
#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <string>
#include <windows.h>
#include <intrin.h>
#include <thread>
#include <stdint.h>


//  Windows
#ifdef _WIN32

uint64_t rdtsc() {
    return __rdtsc();
}

//  Linux/GCC
#else

uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

#endif


#pragma warning(disable : 4996)
using namespace std;

#define MAX_LOADSTRING 100
#define instrN 50;
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окно
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_STONECHECK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STONECHECK));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STONECHECK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_STONECHECK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, (WS_POPUP | WS_OVERLAPPEDWINDOW),
       (GetSystemMetrics(SM_CXVIRTUALSCREEN) - 300) / 2, (GetSystemMetrics(SM_CYVIRTUALSCREEN) - 300) / 2,
       300, 300, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

class InstructionSet
{
    // forward declarations
    class InstructionSet_Internal;

public:
    // getters
    static std::string Vendor(void) { return CPU_Rep.vendor_; }
    static std::string Brand(void) { return CPU_Rep.brand_; }

    static bool SSE3(void) { return CPU_Rep.f_1_ECX_[0]; }
    static bool PCLMULQDQ(void) { return CPU_Rep.f_1_ECX_[1]; }
    static bool MONITOR(void) { return CPU_Rep.f_1_ECX_[3]; }
    static bool SSSE3(void) { return CPU_Rep.f_1_ECX_[9]; }
    static bool FMA(void) { return CPU_Rep.f_1_ECX_[12]; }
    static bool CMPXCHG16B(void) { return CPU_Rep.f_1_ECX_[13]; }
    static bool SSE41(void) { return CPU_Rep.f_1_ECX_[19]; }
    static bool SSE42(void) { return CPU_Rep.f_1_ECX_[20]; }
    static bool MOVBE(void) { return CPU_Rep.f_1_ECX_[22]; }
    static bool POPCNT(void) { return CPU_Rep.f_1_ECX_[23]; }
    static bool AES(void) { return CPU_Rep.f_1_ECX_[25]; }
    static bool XSAVE(void) { return CPU_Rep.f_1_ECX_[26]; }
    static bool OSXSAVE(void) { return CPU_Rep.f_1_ECX_[27]; }
    static bool AVX(void) { return CPU_Rep.f_1_ECX_[28]; }
    static bool F16C(void) { return CPU_Rep.f_1_ECX_[29]; }
    static bool RDRAND(void) { return CPU_Rep.f_1_ECX_[30]; }

    static bool MSR(void) { return CPU_Rep.f_1_EDX_[5]; }
    static bool CX8(void) { return CPU_Rep.f_1_EDX_[8]; }
    static bool SEP(void) { return CPU_Rep.f_1_EDX_[11]; }
    static bool CMOV(void) { return CPU_Rep.f_1_EDX_[15]; }
    static bool CLFSH(void) { return CPU_Rep.f_1_EDX_[19]; }
    static bool MMX(void) { return CPU_Rep.f_1_EDX_[23]; }
    static bool FXSR(void) { return CPU_Rep.f_1_EDX_[24]; }
    static bool SSE(void) { return CPU_Rep.f_1_EDX_[25]; }
    static bool SSE2(void) { return CPU_Rep.f_1_EDX_[26]; }

    static bool FSGSBASE(void) { return CPU_Rep.f_7_EBX_[0]; }
    static bool BMI1(void) { return CPU_Rep.f_7_EBX_[3]; }
    static bool HLE(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[4]; }
    static bool AVX2(void) { return CPU_Rep.f_7_EBX_[5]; }
    static bool BMI2(void) { return CPU_Rep.f_7_EBX_[8]; }
    static bool ERMS(void) { return CPU_Rep.f_7_EBX_[9]; }
    static bool INVPCID(void) { return CPU_Rep.f_7_EBX_[10]; }
    static bool RTM(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[11]; }
    static bool AVX512F(void) { return CPU_Rep.f_7_EBX_[16]; }
    static bool RDSEED(void) { return CPU_Rep.f_7_EBX_[18]; }
    static bool ADX(void) { return CPU_Rep.f_7_EBX_[19]; }
    static bool AVX512PF(void) { return CPU_Rep.f_7_EBX_[26]; }
    static bool AVX512ER(void) { return CPU_Rep.f_7_EBX_[27]; }
    static bool AVX512CD(void) { return CPU_Rep.f_7_EBX_[28]; }
    static bool SHA(void) { return CPU_Rep.f_7_EBX_[29]; }

    static bool PREFETCHWT1(void) { return CPU_Rep.f_7_ECX_[0]; }

    static bool LAHF(void) { return CPU_Rep.f_81_ECX_[0]; }
    static bool LZCNT(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_81_ECX_[5]; }
    static bool ABM(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[5]; }
    static bool SSE4a(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[6]; }
    static bool XOP(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[11]; }
    static bool TBM(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[21]; }

    static bool SYSCALL(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[11]; }
    static bool MMXEXT(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[22]; }
    static bool RDTSCP(void) { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[27]; }
    static bool _3DNOWEXT(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[30]; }
    static bool _3DNOW(void) { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[31]; }

private:
    static const InstructionSet_Internal CPU_Rep;

    class InstructionSet_Internal
    {
    public:
        InstructionSet_Internal()
            : nIds_{ 0 },
            nExIds_{ 0 },
            isIntel_{ false },
            isAMD_{ false },
            f_1_ECX_{ 0 },
            f_1_EDX_{ 0 },
            f_7_EBX_{ 0 },
            f_7_ECX_{ 0 },
            f_81_ECX_{ 0 },
            f_81_EDX_{ 0 },
            data_{},
            extdata_{}
        {
            //int cpuInfo[4] = {-1};
            std::array<int, 4> cpui;

            // Calling __cpuid with 0x0 as the function_id argument
            // gets the number of the highest valid function ID.
            __cpuid(cpui.data(), 0);
            nIds_ = cpui[0];

            for (int i = 0; i <= nIds_; ++i)
            {
                __cpuidex(cpui.data(), i, 0);
                data_.push_back(cpui);
            }

            // Capture vendor string
            char vendor[0x20];
            memset(vendor, 0, sizeof(vendor));
            *reinterpret_cast<int*>(vendor) = data_[0][1];
            *reinterpret_cast<int*>(vendor + 4) = data_[0][3];
            *reinterpret_cast<int*>(vendor + 8) = data_[0][2];
            vendor_ = vendor;
            if (vendor_ == "GenuineIntel")
            {
                isIntel_ = true;
            }
            else if (vendor_ == "AuthenticAMD")
            {
                isAMD_ = true;
            }

            // load bitset with flags for function 0x00000001
            if (nIds_ >= 1)
            {
                f_1_ECX_ = data_[1][2];
                f_1_EDX_ = data_[1][3];
            }

            // load bitset with flags for function 0x00000007
            if (nIds_ >= 7)
            {
                f_7_EBX_ = data_[7][1];
                f_7_ECX_ = data_[7][2];
            }

            // Calling __cpuid with 0x80000000 as the function_id argument
            // gets the number of the highest valid extended ID.
            __cpuid(cpui.data(), 0x80000000);
            nExIds_ = cpui[0];

            char brand[0x40];
            memset(brand, 0, sizeof(brand));

            for (int i = 0x80000000; i <= nExIds_; ++i)
            {
                __cpuidex(cpui.data(), i, 0);
                extdata_.push_back(cpui);
            }

            // load bitset with flags for function 0x80000001
            if (nExIds_ >= 0x80000001)
            {
                f_81_ECX_ = extdata_[1][2];
                f_81_EDX_ = extdata_[1][3];
            }

            // Interpret CPU brand string if reported
            if (nExIds_ >= 0x80000004)
            {
                memcpy(brand, extdata_[2].data(), sizeof(cpui));
                memcpy(brand + 16, extdata_[3].data(), sizeof(cpui));
                memcpy(brand + 32, extdata_[4].data(), sizeof(cpui));
                brand_ = brand;
            }
        };

        int nIds_;
        int nExIds_;
        std::string vendor_;
        std::string brand_;
        bool isIntel_;
        bool isAMD_;
        std::bitset<32> f_1_ECX_;
        std::bitset<32> f_1_EDX_;
        std::bitset<32> f_7_EBX_;
        std::bitset<32> f_7_ECX_;
        std::bitset<32> f_81_ECX_;
        std::bitset<32> f_81_EDX_;
        std::vector<std::array<int, 4>> data_;
        std::vector<std::array<int, 4>> extdata_;
    };
};

const InstructionSet::InstructionSet_Internal InstructionSet::CPU_Rep;


/* Converter */
LPWSTR ConvertToLPWSTR(const string& s)
{
    LPWSTR ws = new wchar_t[s.size() + 1]; // +1 for zero at the end
    copy(s.begin(), s.end(), ws);
    ws[s.size()] = 0; // zero at the end
    return ws;
}

/* Supported non supported getter */
LPWSTR Support(bool Instruction)
{
    string supported = "Yes";
    string nonsupported = "No";
    LPWSTR support;
    Instruction ? support = ConvertToLPWSTR(supported) : support = ConvertToLPWSTR(nonsupported);
    return support;
}

typedef BOOL(WINAPI* LPFN_GLPI)(
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
    PDWORD);


// Helper function to count set bits in the processor mask.
DWORD CountSetBits(ULONG_PTR bitMask)
{
    DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
    DWORD bitSetCount = 0;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
    DWORD i;

    for (i = 0; i <= LSHIFT; ++i)
    {
        bitSetCount += ((bitMask & bitTest) ? 1 : 0);
        bitTest /= 2;
    }

    return bitSetCount;
}

//int _cdecl _tmain()
//{
//    LPFN_GLPI glpi;
//    BOOL done = FALSE;
//    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
//    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
//    DWORD returnLength = 0;
//    DWORD logicalProcessorCount = 0;
//    DWORD numaNodeCount = 0;
//    DWORD processorCoreCount = 0;
//    DWORD processorL1CacheCount = 0;
//    DWORD processorL2CacheCount = 0;
//    DWORD processorL3CacheCount = 0;
//    DWORD processorPackageCount = 0;
//    DWORD byteOffset = 0;
//    PCACHE_DESCRIPTOR Cache;
//
//    glpi = (LPFN_GLPI)GetProcAddress(
//        GetModuleHandle(TEXT("kernel32")),
//        "GetLogicalProcessorInformation");
//    if (NULL == glpi)
//    {
//        //_tprintf(TEXT("\nGetLogicalProcessorInformation is not supported.\n"));
//        return (1);
//    }
//
//    while (!done)
//    {
//        DWORD rc = glpi(buffer, &returnLength);
//
//        if (FALSE == rc)
//        {
//            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
//            {
//                if (buffer)
//                    free(buffer);
//
//                buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
//                    returnLength);
//
//                if (NULL == buffer)
//                {
//                    //_tprintf(TEXT("\nError: Allocation failure\n"));
//                    return (2);
//                }
//            }
//            else
//            {
//                //_tprintf(TEXT("\nError %d\n"), GetLastError());
//                return (3);
//            }
//        }
//        else
//        {
//            done = TRUE;
//        }
//    }
//
//    ptr = buffer;
//
//    while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
//    {
//        switch (ptr->Relationship)
//        {
//        case RelationNumaNode:
//            // Non-NUMA systems report a single record of this type.
//            numaNodeCount++;
//            break;
//
//        case RelationProcessorCore:
//            processorCoreCount++;
//
//            // A hyperthreaded core supplies more than one logical processor.
//            logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
//            break;
//
//        case RelationCache:
//            // Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache. 
//            Cache = &ptr->Cache;
//            if (Cache->Level == 1)
//            {
//                processorL1CacheCount++;
//            }
//            else if (Cache->Level == 2)
//            {
//                processorL2CacheCount++;
//            }
//            else if (Cache->Level == 3)
//            {
//                processorL3CacheCount++;
//            }
//            break;
//
//        case RelationProcessorPackage:
//            // Logical processors share a physical package.
//            processorPackageCount++;
//            break;
//        }
//        byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
//        ptr++;
//
//        free(buffer);
//
//        return 0;
//    }
//};


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
};

// Обработчик сообщений для окна "О программе".

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static wchar_t cores[100];
    static wchar_t threads[100];
    static wchar_t baseFrequency[100];
    static wchar_t maxFrequency[100];
    static wchar_t busFrequency[100];
    static wchar_t curFrequency[100];
    static wchar_t cashe[100];
    static int frequencyInfo[4] = { 0, 0, 0, 0 };
    static int casheInfo[4] = { -1 };
    static int nL2Associativity = 0;
    static int timeLeft = 1800;
    static unsigned __int64 nStartTime, nEndTime, nTimeDiff, nFreq, nStart, nEnd, nDiff;

    LPFN_GLPI glpi;
    BOOL done = FALSE;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
    DWORD returnLength = 0;
    DWORD logicalProcessorCount = 0;
    DWORD numaNodeCount = 0;
    DWORD processorCoreCount = 0;
    DWORD processorL1CacheCount = 0;
    DWORD processorL2CacheCount = 0;
    DWORD processorL3CacheCount = 0;
    DWORD processorPackageCount = 0;
    DWORD byteOffset = 0;
    PCACHE_DESCRIPTOR Cache;

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
       

        SetTimer(hDlg, 1, 1000, NULL);
        SetDlgItemInt(hDlg, ID_CURF, (unsigned __int64)(((double)nDiff) / (((double)nTimeDiff) / nFreq)), 0);

        /* Cores and Threads getter */
        glpi = (LPFN_GLPI)GetProcAddress(
            GetModuleHandle(TEXT("kernel32")),
            "GetLogicalProcessorInformation");
        while (!done)
        {
            DWORD rc = glpi(buffer, &returnLength);
            if (FALSE == rc)
            {
                if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
                {
                    if (buffer)
                        free(buffer);
                    buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
                        returnLength);
                    if (NULL == buffer)
                    {
                        return (2);
                    }
                }
                else
                {
                    return (3);
                }
            }
            else
            {
                done = TRUE;
            }
        }

        ptr = buffer;

        while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
        {
            switch (ptr->Relationship)
            {
            case RelationNumaNode:
                // Non-NUMA systems report a single record of this type.
                numaNodeCount++;
                break;

            case RelationProcessorCore:
                processorCoreCount++;

                // A hyperthreaded core supplies more than one logical processor.
                logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
                break;

            case RelationCache:
                // Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache. 
                Cache = &ptr->Cache;
                if (Cache->Level == 1)
                {
                    processorL1CacheCount++;
                }
                else if (Cache->Level == 2)
                {
                    processorL2CacheCount++;
                }
                else if (Cache->Level == 3)
                {
                    processorL3CacheCount++;
                }
                break;

            case RelationProcessorPackage:
                // Logical processors share a physical package.
                processorPackageCount++;
                break;
            }
            byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
            ptr++;
        }

        /* Frequency getter */
        __cpuid(frequencyInfo, 0);   // Частота CPU связана с аппаратным обеспечением, поэтому нет никакого общего метода  
      if (frequencyInfo[0] >= 0x16)  // который вы можете применить, чтобы получить его, он также зависит от используемого вами OS.*/
            __cpuid(frequencyInfo, 0x16);

        /* Cache getter */
        __cpuid(casheInfo, 0x80000006);
        nL2Associativity = (casheInfo[2] >> 12) & 0xf;

        /* Convert */
        wsprintf(cores, L"%d", processorCoreCount);
        wsprintf(threads, L"%d", logicalProcessorCount);
        wsprintf(cashe, L"%d", nL2Associativity);
        wsprintf(baseFrequency, L"%d", frequencyInfo[0]);
        wsprintf(maxFrequency, L"%d", frequencyInfo[1]);
        wsprintf(busFrequency, L"%d", frequencyInfo[2]);
       
        /* Outputs */
        SetDlgItemText(hDlg, ID_NAME, ConvertToLPWSTR(InstructionSet::Brand()));
        SetDlgItemText(hDlg, ID_CODENAME, ConvertToLPWSTR(InstructionSet::Vendor()));
        SetDlgItemText(hDlg, ID_THREADS, threads);
        SetDlgItemText(hDlg, ID_CORES, cores);
        SetDlgItemText(hDlg, ID_BASEF, baseFrequency);
        SetDlgItemText(hDlg, ID_MAXF, maxFrequency);
        SetDlgItemText(hDlg, ID_BUSF, busFrequency);
        SetDlgItemText(hDlg, ID_CURF, curFrequency);
        SetDlgItemText(hDlg, ID_CASHE, cashe);
        
        /* Instructions Outputs */
        SetDlgItemText(hDlg, ID_3DNOW, Support(InstructionSet::_3DNOW()));
        SetDlgItemText(hDlg, ID_3DNOWEXT, Support(InstructionSet::_3DNOWEXT()));
        SetDlgItemText(hDlg, ID_ABM, Support(InstructionSet::ABM()));
        SetDlgItemText(hDlg, ID_ADX, Support(InstructionSet::ADX()));
        SetDlgItemText(hDlg, ID_AES, Support(InstructionSet::AES()));
        SetDlgItemText(hDlg, ID_AVX, Support(InstructionSet::AVX()));
        SetDlgItemText(hDlg, ID_AVX2,Support(InstructionSet::AVX2()));
        SetDlgItemText(hDlg, ID_AVX512CD, Support(InstructionSet::AVX512CD()));
        SetDlgItemText(hDlg, ID_AVX512ER,Support(InstructionSet::AVX512ER()));
        SetDlgItemText(hDlg, ID_AVX512F, Support(InstructionSet::AVX512PF()));
        SetDlgItemText(hDlg, ID_AVX512F, Support(InstructionSet::AVX512PF()));
        SetDlgItemText(hDlg, ID_BMI1, Support(InstructionSet::BMI1()));
        SetDlgItemText(hDlg, ID_BMI2, Support(InstructionSet::BMI2()));
        SetDlgItemText(hDlg, ID_CLFSH, Support(InstructionSet::CLFSH()));
        SetDlgItemText(hDlg, ID_CMPXCHG16B, Support(InstructionSet::CMPXCHG16B()));
        SetDlgItemText(hDlg, ID_CX8, Support(InstructionSet::CX8()));
        SetDlgItemText(hDlg, ID_ERMS, Support(InstructionSet::ERMS()));
        SetDlgItemText(hDlg, ID_F16C, Support(InstructionSet::F16C()));
        SetDlgItemText(hDlg, ID_FMA, Support(InstructionSet::FMA()));
        SetDlgItemText(hDlg, ID_FSGSBASE, Support(InstructionSet::FSGSBASE()));
        SetDlgItemText(hDlg, ID_FXSR, Support(InstructionSet::FXSR()));
        SetDlgItemText(hDlg, ID_HLE, Support(InstructionSet::HLE()));
        SetDlgItemText(hDlg, ID_INVPCID, Support(InstructionSet::INVPCID()));
        SetDlgItemText(hDlg, ID_LAHF, Support(InstructionSet::LAHF()));
        SetDlgItemText(hDlg, ID_LZCNT, Support(InstructionSet::LZCNT()));
        SetDlgItemText(hDlg, ID_MMX, Support(InstructionSet::MMX()));
        SetDlgItemText(hDlg, ID_MMXEXT, Support(InstructionSet::MMXEXT()));
        SetDlgItemText(hDlg, ID_MONITOR, Support(InstructionSet::MONITOR()));
        SetDlgItemText(hDlg, ID_MOVBE, Support(InstructionSet::MOVBE()));
        SetDlgItemText(hDlg, ID_MSR, Support(InstructionSet::MSR()));
        SetDlgItemText(hDlg, ID_OSXSAVE, Support(InstructionSet::OSXSAVE()));
        SetDlgItemText(hDlg, ID_PCLMULQDQ, Support(InstructionSet::PCLMULQDQ()));
        SetDlgItemText(hDlg, ID_POPCNT, Support(InstructionSet::POPCNT()));
        SetDlgItemText(hDlg, ID_PREFETCHWT1, Support(InstructionSet::PREFETCHWT1()));
        SetDlgItemText(hDlg, ID_RDRAND, Support(InstructionSet::RDRAND()));
        SetDlgItemText(hDlg, ID_RDSEED, Support(InstructionSet::RDSEED()));
        SetDlgItemText(hDlg, ID_RDTSCP, Support(InstructionSet::RDTSCP()));
        SetDlgItemText(hDlg, ID_RTM, Support(InstructionSet::RTM()));
        SetDlgItemText(hDlg, ID_SEP, Support(InstructionSet::SEP()));
        SetDlgItemText(hDlg, ID_SHA, Support(InstructionSet::SHA()));
        SetDlgItemText(hDlg, ID_SSE, Support(InstructionSet::SSE()));
        SetDlgItemText(hDlg, ID_SSE2, Support(InstructionSet::SSE2()));
        SetDlgItemText(hDlg, ID_SSE3, Support(InstructionSet::SSE3()));
        SetDlgItemText(hDlg, ID_SSE41, Support(InstructionSet::SSE41()));
        SetDlgItemText(hDlg, ID_SSE42, Support(InstructionSet::SSE42()));
        SetDlgItemText(hDlg, ID_SSE4a, Support(InstructionSet::SSE4a()));
        SetDlgItemText(hDlg, ID_SSSE3, Support(InstructionSet::SSSE3()));
        SetDlgItemText(hDlg, ID_SYSCALL, Support(InstructionSet::SYSCALL()));
        SetDlgItemText(hDlg, ID_TBM, Support(InstructionSet::TBM()));
        SetDlgItemText(hDlg, ID_XOP, Support(InstructionSet::XOP()));
        SetDlgItemText(hDlg, ID_XSAVE, Support(InstructionSet::XSAVE()));
        break;
     case WM_TIMER:
        
        SetDlgItemInt(hDlg, ID_CURF,  (unsigned __int64)(((double)nDiff) / (((double)nTimeDiff) / nFreq))/1000000, 0);
         
         return TRUE;
    case WM_COMMAND:
        //while (1)
        //{
        //    if (QueryPerformanceFrequency((LARGE_INTEGER*)&nFreq))
        //    {
        //        QueryPerformanceCounter((LARGE_INTEGER*)&nStartTime);
        //        nStart = __rdtsc();
        //        QueryPerformanceCounter((LARGE_INTEGER*)&nEndTime);
        //        nEnd = __rdtsc();
        //        nDiff = nEnd - nStart;
        //        nTimeDiff = nEndTime - nStartTime;
        //        // I get for example nFrequency = 3292376364 for 3.29 GHz
        //    }
        //}

            SetTimer(hDlg, 1, 100, NULL);
          // SetDlgItemInt(hDlg, ID_CURF, (unsigned __int64)(((double)nDiff) / (((double)nTimeDiff) / nFreq))/10000, 0);
        
        switch (LOWORD(wParam)) 
        {
        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
         break;
        }
    }
    return (INT_PTR)FALSE;
}
