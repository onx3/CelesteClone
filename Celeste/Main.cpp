#include "Celeste_lib.h"
#include "platform.h"
#include "ThirdParty/glcorearb.h"
#include "gl_renderer.h"


int main()
{
    platform_create_window(1200, 720, "Celeste");

    while (running)
    {
        // Update
        platform_update_window();
    }

    return 0;
}