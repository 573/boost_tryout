---
layout: post
title: Simple Boost Example No. 4 (test cases)
---

Preparations on your system
---

Assumes you have a valid "Visual Studio 2010" installation (won't describe command line compilation with Microsoft Visual C++ 2010 Express here, although building the Boost libraries itself should work out of the box with it).

Have `BOOSTHOME` environment variables defined, i. e.:

    BOOSTHOME=S:\Home\boost_1_46_1

Load [current Boost distribution](http://www.boost.org/users/download/) to `%BOOSTHOME%`. Have built library files for Boost with `bjam` at "Visual Studio Command Prompt (2010)" (which configures the needed environment by setting paths/variables):

    cd /D %BOOSTHOME%
    bootstrap.bat
    bjam toolset=msvc --build-type=complete --with-test
    pause

Important: If you already built the library files for boost 1) call bjam.exe clean or 2) manually delete the generated stage/lib or stage/debug and the bin.v2 folders in the %BOOSTHOME% folder.

Settings in your Visual Studio Solution File
---

The directories containing the Header-Files (include) for boost are added to the C/C++-Compiler settings:
`Solution >> Project >> Properties >> Configuration Properties >> C/C++ >> Additional Include Directories: $(BOOSTHOME)`

The directories containing the Library-Files for boost are added to the Linker settings:
`Solution >> Project >> Properties >> Configuration Properties >> Linker >> Additional Library Directories: $(BOOSTHOME)\stage\lib`

Incremental linking is deactivated:
`Solution >> Project >> Properties >> Configuration Properties >> Linker >> Enable Incremental Linking: No (/INCREMENTAL:NO)`

Linking for subsystem Console is activated:
`Solution >> Project >> Properties >> Configuration Properties >> Linker >> System >> SubSystem: Console (/SUBSYSTEM:CONSOLE)`

The execution of the tests is triggered as a post-build event:
`Solution >> Project >> Properties >> Configuration Properties >> Build Events >> Post-Build Event >> Command Line: "$(OutputPath)$(TargetName)$(TargetExt)" --result_code=no --report_level=no`

The example itself is taken from [unit-testing-mit-boost-test](http://www.roth-soft.de/unit-testing-mit-boost-test).

