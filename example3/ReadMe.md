---
layout: post
title: Simple Boost Example No. 3
---

<pre>
========================================================================
    DYNAMIC LINK LIBRARY : example6 Project Overview
========================================================================

AppWizard has created this example6 DLL for you.

This file contains a summary of what you will find in each of the files that
make up your example6 application.


example6.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

example6.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

example6.cpp
    This is the main DLL source file.

	When created, this DLL does not export any symbols. As a result, it
	will not produce a .lib file when it is built. If you wish this project
	to be a project dependency of some other project, you will either need to
	add code to export some symbols from the DLL so that an export library
	will be produced, or you can set the Ignore Input Library property to Yes
	on the General propert page of the Linker folder in the project's Property
	Pages dialog box.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named example6.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
</pre>

Preparations on your system
---

Assumes you have a valid "Visual Studio 2010" installation (won't describe command line compilation with Microsoft Visual C++ 2010 Express here, although building the Boost libraries itself should work out of the box with it).

Have `PYTHONHOME` and `BOOSTHOME` environment variables defined, i. e.:

    BOOSTHOME=S:\Home\boost_1_46_1
	PYTHONHOME=C:\Python26

Load current Boost distribution to `%BOOSTHOME%` make a  `%HOMEDRIVE%%HOMEPATH%\user-config.jam` file containing:

	# Boost.Python user configuration file.

	#  MSVC configuration
	using msvc : 10.0 ;

	#  Python configuration
	using python
			  : 2.6 # version
			  : C:/Python26 # cmd-or-prefix
			  : C:/Python26/include # includes
			  : C:/Python26/libs # libs
			  : <toolset>msvc # condition
			  ;    

Have built library files for Boost with `bjam` at "Visual Studio Command Prompt (2010)" (which configures the needed environment by setting paths/variables):

    cd /D S:\Home\boost_1_46_1
	bootstrap.bat
	bjam toolset=msvc --build-type=complete --with-python

Settings in our Visual Studio Solution File
---

As project type have chosen Win32-DLL and left the rest on defaults in the App Wizard:
`File >> New >> Project... >> Win32 Project >> Application Type: DLL`

The Target Extension of the built DLL file is changed to `.pyd`, as this is required from Python version 2.5 on (see [this post](http://groups.google.com/group/boost-list/browse_thread/thread/93e2296dcde28088])):
`Solution >> Project >> Properties >> Configuration Properties >> General >> General >> Target Extension: .pyd`

`Solution >> Project >> Properties >> Configuration Properties >> General >> Project Defaults >> Configuration Type >> Dynamic Library (.dll)`

The directories containing the Header-Files (include) for boost and the used python engine are added
to the C/C++-Compiler settings:
`Solution >> Project >> Properties >> Configuration Properties >> C/C++ >> Additional Include Directories: $(BOOSTHOME);$(PYTHONHOME)\include`

The directories containing the Library-Files for boost and the used python engine are added
to the Linker settings:
`Solution >> Project >> Properties >> Configuration Properties >> Linker >> Additional Library Directories: $(BOOSTHOME)\stage\lib;$(PYTHONHOME)\libs`

Incremental linking is deactivated:
`Solution >> Project >> Properties >> Configuration Properties >> Linker >> Enable Incremental Linking: No (/INCREMENTAL:NO)`

The example itself is taken from [boost.python/SimpleExample](http://wiki.python.org/moin/boost.python/SimpleExample).

The project name must be the same as the module name: i. e. imaging you have `boost_example` then write `BOOST_PYTHON_MODULE(boost_example)` in the extensions `.cpp` file and the built files name will be `boost_example.pyd`, free to choose is the `*.cpp` files file name. 

When built, the `*.pyd` file is created below the solution folder (or the output folder you declared, inside Debug/Release). At a command line prompt push into that folder, append `%BOOSTHOME%\stage\lib` (where the `boost_python-XXX.dll` etc. files are found and eventually needed additional `*.dll` files too) to the `PATH` variable and append the folder containing the `*.pyd` file to the `%PYTHONPATH%` variable). Now you may run `%PYTHONHOME%\python.exe` and therein:

    >>> import boost_example
	>>> print boost_example.greet()
