#include <iostream>
#include <string>
#include <functional>
#include <iomanip>

// Solve Mingw error: '::hyport' has not been declared 
#include <math.h>

//#define hypot _hypot

/// C-API header to Python Native Interface API, similar to Java JNI
/// (Java Native Interface)
#include <Python.h>
#include <unistd.h>  // Exports getpid()
#include "monitor.cpp"
struct DLLInitialization
{
	DLLInitialization(){
		int pid;
		pid = getpid();       
		std::cerr << " [TRACE] Python module DLL loaded by process PID = <"
				  << pid << "> "
				  << std::endl;
		std::cerr << " [TRACE] Attach the debugger with: $ gdb -pid=" << pid << "\n";
	}
	~DLLInitialization(){
		std::cerr << " [TRACE] DLL native DLL unloaded OK." << std::endl;
	}	
};

DLLInitialization dllinit_hook;

auto monitorApp(PyObject* self, PyObject* args)->PyObject*;

static PyMethodDef ModuleFunctions [] =
{
	{ "monitorApp", monitorApp, METH_VARARGS,"description"}
	// Sentinel value used to indicate the end of function listing.
	// All function listing must end with this value.
	,{nullptr, nullptr, 0, nullptr}									
};

/* Module definition */
static struct PyModuleDef ModuleDefinitions {
	PyModuleDef_HEAD_INIT,
	// Module name as string 
	"mymodule",
	// Module documentation (docstring)
	"A sample C++ native-code module for python3.",
	-1,
	// Functions exposed to the module 
	ModuleFunctions
};

/** Module Initialization function: must have this name schema
 *  PyInit_<ModuleName> where ModuleName is the same base name of theWW
 *  shared library ModuleName.so (on Linux) or ModuleName.pyd (on Windows)
 */
PyMODINIT_FUNC PyInit_mymodule(void)
{
	Py_Initialize();
	PyObject* pModule = PyModule_Create(&ModuleDefinitions);
	PyModule_AddObject(pModule, "version", Py_BuildValue("s", "version 0.1-Alpha"));
	return pModule;
}

auto monitorApp(PyObject* self, PyObject* args) -> PyObject*
{
	std::cerr << " =>> Printing numeric range " << "\n";	
	int    pid;
	// Extract function argument from tuple argument object
	// "if" => i - Extract integer
	//      => f - Extract float (IEEE754 32 bits float point)
	if(!PyArg_ParseTuple(args, "i", &pid)){
		PyErr_SetString(PyExc_RuntimeError, "Invalid argument");
		// Always return null on failure 
		return nullptr; 
	}

	if(pid <= 0){
		PyErr_SetString( PyExc_RuntimeError
						 ,"Invalid argument: n supposed to be greater than zero.");
		return nullptr;
	}	
	monitorProcess(pid);
	Py_RETURN_NONE;
}