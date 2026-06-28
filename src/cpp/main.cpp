#include <windows.h>
#include <Python.h>
#include "xlcall.h"

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
