#include "namespace.h"
#include "registry.h"

// Function registration

int registerFunctions() {
    vector<UDFInfo> funcs = FetchRegistry();

    for (const auto& func : funcs) {

    }

    return 1;
}

int unregisterFunctions() {

}

// Python function dispatch

extern "C" __declspec(dllexport) LPXLOPER12 WINAPI pyUDFDispatch(
    LPXLOPER12 a0,  LPXLOPER12 a1,  LPXLOPER12 a2,  LPXLOPER12 a3,
    LPXLOPER12 a4,  LPXLOPER12 a5,  LPXLOPER12 a6,  LPXLOPER12 a7,
    LPXLOPER12 a8,  LPXLOPER12 a9,  LPXLOPER12 a10, LPXLOPER12 a11,
    LPXLOPER12 a12, LPXLOPER12 a13, LPXLOPER12 a14, LPXLOPER12 a15,
    LPXLOPER12 a16, LPXLOPER12 a17, LPXLOPER12 a18, LPXLOPER12 a19,
    LPXLOPER12 a20, LPXLOPER12 a21, LPXLOPER12 a22, LPXLOPER12 a23,
    LPXLOPER12 a24, LPXLOPER12 a25, LPXLOPER12 a26, LPXLOPER12 a27,
    LPXLOPER12 a28, LPXLOPER12 a29, LPXLOPER12 a30, LPXLOPER12 a31)
{
    LPXLOPER12 args[] = {
        a0,  a1,  a2,  a3,  a4,  a5,  a6,  a7,
        a8,  a9,  a10, a11, a12, a13, a14, a15,
        a16, a17, a18, a19, a20, a21, a22, a23,
        a24, a25, a26, a27, a28, a29, a30, a31
    };

    int count = 0;
    while (count < 32 && args[count]->xltype != xltypeMissing) count++;

    // TODO: look up Python function by caller name, marshal args, dispatch
    // TODO: heap-allocate result with xlbitDLLFree instead of static buffer
    static XLOPER12 xErr = { .val = { .err = xlerrValue }, .xltype = xltypeErr };
    return &xErr;
}

// Required XLL entry points

extern "C" {

__declspec(dllexport) int WINAPI xlAutoOpen()
{
    if (!Py_IsInitialized())
        Py_Initialize();
    return 1;
}

__declspec(dllexport) int WINAPI xlAutoClose()
{
    if (Py_IsInitialized())
        Py_Finalize();
    return 1;
}

__declspec(dllexport) void WINAPI xlAutoFree12(LPXLOPER12 pxFree)
{
    delete pxFree;
}

__declspec(dllexport) int WINAPI xlAutoAdd()    { return 1; }
__declspec(dllexport) int WINAPI xlAutoRemove() { return 1; }

__declspec(dllexport) LPXLOPER12 WINAPI xlAddInManagerInfo12(LPXLOPER12 xAction)
{
    static XLOPER12 xInfo;
    XLOPER12 xIntAction, xTargetType;

    xTargetType.xltype = xltypeInt;
    xTargetType.val.w  = xltypeInt;
    Excel12(xlCoerce, &xIntAction, 2, xAction, &xTargetType);

    if (xIntAction.val.w == 1)
    {
        static XCHAR name[] = L"\x08" L"Firelink";
        xInfo.xltype  = xltypeStr;
        xInfo.val.str = name;
    }
    else
    {
        xInfo.xltype  = xltypeErr;
        xInfo.val.err = xlerrValue;
    }
    return &xInfo;
}

} // extern "C"
