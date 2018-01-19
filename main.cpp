//temrorary hack to allow glog.lib be linked as static
//disable __declspec(dllimport)
#define GOOGLE_GLOG_DLL_DECL

#include "ribbonapp.h"
#include "glog/logging.h"
#include <iostream>

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);

    RibbonApp a(argc, argv);

    a.start();
    return a.exec();
}
