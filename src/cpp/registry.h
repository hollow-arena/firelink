#include "namespace.h"

struct UDFInfo
{
    wstring name;
    wstring description;
    map<wstring, wstring> params;
};

vector<UDFInfo> FetchRegistry();