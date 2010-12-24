/*
 * PythonWrapper.cpp
 *
 *  Created on: 24 déc. 2010
 *      Author: canard
 */

#include "PythonWrapper.h"
#include <boost/python.hpp>
#include <string>
#include "PythonModule.h"
#include "Event.h"

using namespace boost::python;


PythonWrapper::PythonWrapper() {
}

PythonWrapper::~PythonWrapper() {
}

namespace
{
	void (PythonModule::*addActionOnEvent_Event_String)(const Event&, const std::string&) = &PythonModule::addActionOnEvent;

	BOOST_PYTHON_MODULE(NoTouchScreenMod)
	{
		class_<PythonModule>("NoTouchScreenConfig")
			.def("getNum",&PythonModule::getNum)
			.def("addActionOnEvent",addActionOnEvent_Event_String);
	}
}

void PythonWrapper::test()
{
	try {
		PyImport_AppendInittab( "NoTouchScreenMod", &initNoTouchScreenMod );
		Py_Initialize();
		object main_module = import("__main__");
		object main_namespace = main_module.attr("__dict__");

		// Buit ins types of python such as True/False
		object builtins_module = import("__builtin__");
		main_namespace["__builtins__"] = builtins_module;

		// Our modules
		object nts_module = import("NoTouchScreenMod");
		main_namespace["NoTouchScreenMod"] = nts_module;

		// Exec
		str strPyFileName("etc/config.py");
		object objectScriptRun = exec_file( strPyFileName, main_namespace, main_namespace );
	}
	catch( error_already_set& )
	{
		PyErr_Print();
	}
}
