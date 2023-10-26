#pragma once
#include <iostream>
#include "kfile.h"
#include "klog.h"

void TestCompileConfig()
{
#if KDEBUG
    std::cout << "debug_mode open." << std::endl;
#endif
}

void TestFunc()
{
    KFile vsFile;
    vsFile.Open("default.vs");
    std::string vsContent;
    vsFile.Read(vsContent);
    KLog::Log(vsContent);
    vsFile.Close();

    KLog::Log(KFile::ReadFile("default_color.fs"));
}