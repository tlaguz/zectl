#include "zectl.h"

#include <stdio.h>
#include <unistd.h>

libze_error
ze_mount(libze_handle *lzeh, int argc, char **argv) {
    libze_error ret = LIBZE_ERROR_SUCCESS;
    int opt;

    opterr = 0;

    while ((opt = getopt(argc, argv, "")) != -1) {
        switch (opt) {
            default:
                fprintf(stderr, "%s mount: unknown option '-%c'\n", ZE_PROGRAM, optopt);
                ze_usage();
                return LIBZE_ERROR_UNKNOWN;
        }
    }

    argc -= optind;
    argv += optind;

    if ((argc < 1) || (argc > 2)) {
        fprintf(stderr, "%s mount: wrong number of arguments\n", ZE_PROGRAM);
        ze_usage();
        return LIBZE_ERROR_UNKNOWN;
    }

    char const *mountpoint;
    if (argc == 2) {
        mountpoint = argv[1];
    } else {
        mountpoint = NULL;
    }

    char const *boot_environment = argv[0];
    char mountpoint_buffer[LIBZE_MAX_PATH_LEN];
    if ((ret = libze_mount(lzeh, boot_environment, mountpoint, mountpoint_buffer)) ==
        LIBZE_ERROR_SUCCESS) {
        puts(mountpoint_buffer);
    }

    return ret;
}