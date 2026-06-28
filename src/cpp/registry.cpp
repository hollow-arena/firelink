#include "registry.h"

static wstring PyStrToWStr(PyObject* obj)
{
    Py_ssize_t size;
    wchar_t* buf = PyUnicode_AsWideCharString(obj, &size);
    if (!buf) return {};
    wstring result(buf, size);
    PyMem_Free(buf);
    return result;
}

vector<UDFInfo> FetchRegistry()
{
    vector<UDFInfo> result;

    PyObject* pModule = PyImport_ImportModule("firelink");
    if (!pModule) return result;

    PyObject* pFunc = PyObject_GetAttrString(pModule, "get_registry");
    Py_DECREF(pModule);
    if (!pFunc) return result;

    PyObject* pList = PyObject_CallNoArgs(pFunc);
    Py_DECREF(pFunc);
    if (!pList) return result;

    Py_ssize_t count = PyList_Size(pList);
    for (Py_ssize_t i = 0; i < count; i++)
    {
        PyObject* pDict = PyList_GetItem(pList, i); // borrowed

        UDFInfo info;
        info.name        = PyStrToWStr(PyDict_GetItemString(pDict, "name"));
        info.description = PyStrToWStr(PyDict_GetItemString(pDict, "description"));

        PyObject* pParams = PyDict_GetItemString(pDict, "params"); // borrowed
        if (pParams && PyDict_Check(pParams))
        {
            PyObject *key, *val;
            Py_ssize_t pos = 0;
            while (PyDict_Next(pParams, &pos, &key, &val))
                info.params[PyStrToWStr(key)] = PyStrToWStr(val);
        }

        result.push_back(move(info));
    }

    if (PyErr_Occurred())
        PyErr_Clear();

    Py_DECREF(pList);
    return result;
}
