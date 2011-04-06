---
layout: post
title: Simple Boost Example No. 1
---

<pre>
========================================================================
    CONSOLE APPLICATION : example Project Overview
========================================================================

AppWizard has created this example application for you.

This file contains a summary of what you will find in each of the files that
make up your example application.


example.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

example.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

example.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named example.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
</pre>

Preparations on your system
---

Assumes you have a valid "Visual Studio 2010" installation (won't describe command line compilation with Microsoft Visual C++ 2010 Express here, although building the Boost libraries itself should work out of the box with it).

Have `BOOSTHOME` environment variable defined, i. e.:

    BOOSTHOME=S:\Home\boost_1_46_1

Load [current Boost distribution](http://www.boost.org/users/download/) to `%BOOSTHOME%`.

Settings in your Visual Studio Solution File
---

As project type have chosen "Win32 Console Application" and left the rest on defaults in the App Wizard:
`File >> New >> Project... >> Visual C++ >> Win32 >> Win32 Console Application >> Application Settings >> Application type: Console application`

The directories containing the Header-Files (include) for boost are added
to the C/C++-Compiler settings:
`Solution >> Project >> Properties >> Configuration Properties >> C/C++ >> Additional Include Directories: $(BOOSTHOME)`

Incremental linking is deactivated:
`Solution >> Project >> Properties >> Configuration Properties >> Linker >> Enable Incremental Linking: No (/INCREMENTAL:NO)`

The example itself is taken from ["Build a simple program using Boost"](http://www.boost.org/doc/libs/1_46_1/more/getting_started/windows.html#build-a-simple-program-using-boost).

At a command line prompt push into the output folder. Now you may run the built app as shown at the linked web page above.

