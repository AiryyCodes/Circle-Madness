#include <cstdio>
#include <cstdlib>

#include "window.h"

int main(void)
{
    if (!window_init("Youtube Game", 1280, 720))
    {
        printf("Failed to initialize window.\n");
        return EXIT_FAILURE;
    }

    window_tick();

    window_cleanup();

    return EXIT_SUCCESS;
}
