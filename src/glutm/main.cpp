#include "main.h"

/*! \file
    \ingroup GlutMaster
*/

#include <glutm/master.h>
#include <misc/string.h>

#if defined(GLUTM_WIN32) && !defined(GLUTM_SAVER)

#include <windows.h>

int WINAPI   WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow)
{
    // Pass command line to GlutMain

    std::vector<std::string> arg;
    arg.push_back(std::string());       // Todo: program name

    if (strlen(lpCmdLine))
        arg.push_back(lpCmdLine);

    if (GlutMain(arg))
    {
        if (GlutMaster::active())
            GlutMaster::mainLoop();

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

#endif

int main(int argc,char** argv)
{
    bool ok;

    {
        // Convert args into vector of strings,
        // and free memory before going into
        // main GLUT loop

        std::vector<std::string> arg(argc);
        for (int i=0; i<argc; i++)
            arg[i] = argv[i];

        ok = GlutMain(arg);
    }

    if (ok)
    {
        if (GlutMaster::active())
          GlutMaster::mainLoop();

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}



