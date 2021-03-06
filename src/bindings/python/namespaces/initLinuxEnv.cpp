/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/


#include <python2.7/Python.h>

#include <PythonBindings.h>
#include <Registers.h>
#include <Syscalls.h>

extern const char*syscallmap[];

void initLinuxEnv(PyObject *idLinuxClassDict) {
  for (unsigned int i = 0; i < NB_SYSCALL; ++i)
    PyDict_SetItemString(idLinuxClassDict, syscallmap[i], PyLong_FromUint(i));
}
