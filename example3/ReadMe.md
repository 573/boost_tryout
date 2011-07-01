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

Load [current Boost distribution](http://www.boost.org/users/download/) to `%BOOSTHOME%` make a  `%HOMEDRIVE%%HOMEPATH%\user-config.jam` file containing:

	# Boost.Python user configuration file.

	#  MSVC configuration
	using msvc : 10.0 ;

	#  Python configuration, the first entry is taken by default by bjam.exe
	using python
			  : 2.6 # version
			  : C:/Python26 # cmd-or-prefix
			  : C:/Python26/include # includes
			  : C:/Python26/libs # libs
			  : <toolset>msvc # condition
			  ;
   
        # This section can safely be left off, but to build optionally against the 2.3
        # version of python, specify the python=2.3 switch on the bjam.exe command line
	using python
			  : 2.3 # version
			  : C:/Python23 # cmd-or-prefix
			  : C:/Python23/include # includes
			  : C:/Python23/libs # libs
			  : <toolset>msvc # condition
			  ;   

Have built library files for Boost with `bjam` at "Visual Studio Command Prompt (2010)" (which configures the needed environment by setting paths/variables):

    cd /D %BOOSTHOME%
    bootstrap.bat
    bjam toolset=msvc --build-type=complete --with-python
    echo To build the 2.3 version e. g. with the above user-config.jam settings explicitly use
    echo bjam toolset=msvc python=2.3 --build-type=complete --with-python
    pause

Important: If you already built the library files for boost for one of the python versions e. g. python26 and now wanted to build the python23 you explicitly need to 1) call bjam.exe clean or 2) manually delete the generated stage/lib or stage/debug and the bin.v2 folders in the %BOOSTHOME% folder otherwise your own custom binaries will complain about not finding the python26.dll and you'll search some ours why that version is even searched for although you told bjam.exe to link against python23, the messages when building the libraries for Boost about that aren't very explicit.

Settings in your Visual Studio Solution File
---

As project type have chosen "Win32 Console Application... DLL" and left the rest on defaults in the App Wizard:
`File >> New >> Project... >> Visual C++ >> Win32 >> Win32 Console Application >> Application Settings >> Application type: DLL`

The Target Extension of the built DLL file is changed to `.pyd`, as this is required from Python version 2.5 on (see [this post](http://groups.google.com/group/boost-list/browse_thread/thread/93e2296dcde28088)):
`Solution >> Project >> Properties >> Configuration Properties >> General >> General >> Target Extension: .pyd` (`Solution >> Project >> Properties >> Configuration Properties >> General >> Project Defaults >> Configuration Type >> Dynamic Library (.dll)`)

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

When built, the `*.pyd` file is created below the solution folder (or the output folder you declared, inside Debug/Release). At a command line prompt push into that folder, append `%BOOSTHOME%\stage\lib` (where the `boost_python-XXX.dll` - in other words your projects bundled `*.dll` files - are found) to the `PATH` variable and append the folder containing the `*.pyd` file - the build output folder - to the `%PYTHONPATH%` variable. Now you may run `%PYTHONHOME%\python.exe` and therein:

    >>> import boost_example
    >>> print boost_example.greet()

