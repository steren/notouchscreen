/*
 * PythonWrapper.cpp
 *
 *  Created on: 24 déc. 2010
 *      Author: canard
 */

#include "PythonWrapper.h"
#include <boost/python.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <string>
#include <iostream>
#include "PythonModule.h"
#include "Event.h"
#include "NoTouchScreenException.h"

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
		boost::filesystem::path configFile("etc/config.py");

		if( ! boost::filesystem::exists(configFile) )
			throw NoTouchScreenException(boost::str(boost::format("The config file %1% has not been found.") % configFile));

		object objectScriptRun = exec_file(configFile.file_string().c_str(), main_namespace, main_namespace );
	}
	catch( error_already_set& )
	{
		PyErr_Print();
	}
}
