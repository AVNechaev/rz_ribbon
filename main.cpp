#include "ribbonapp.h"

int main(int argc, char *argv[])
{    
    RibbonApp a(argc, argv);

    a.start();
    return a.exec();
}
