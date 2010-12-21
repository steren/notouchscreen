/*
 * main entry point
 *
 *  Created on: 16 déc. 2010
 *      @author canard (jeanbernard.jansen@gmail.com)
 *      @author steren (steren.giannini@gmail.com)
 */

#include "NoTouchScreen.h"
#include "utils/BoostProgramOptions.h"

#include <string>
#include <iostream>

#include "ActionManager.h"
#include "NoTouchScreenException.h"

#include "config.h"
#ifdef WINDOWS
	#define NoTouchScreenDefaultConfigFile "ConfigWindows"
#endif
#ifdef LINUX
	#define NoTouchScreenDefaultConfigFile "./etc/ConfigLinux"
#endif

int main(int argc, char * argv[])
{
	// Declare the supported options.
	std::string OptionsConfigFile;
	po::options_description desc("Allowed options");
	desc.add_options()
	    ("help", "Prints this help message")
	    ("config", po::value< std::string >(&OptionsConfigFile)->default_value(NoTouchScreenDefaultConfigFile), "Override the default config file")
	;

	// Parsing
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if( vm.count("help") )
	{
	    std::cout << desc << std::endl;
	    return 0;
	}

	try
	{
		ActionManager::Instance().FillRegisterWithConfigFile(OptionsConfigFile);

		NoTouchScreen instance;
		instance.MainLoop();
	}
	catch(NoTouchScreenException& e)
	{
		e.print();
	}

	return 0;
}
