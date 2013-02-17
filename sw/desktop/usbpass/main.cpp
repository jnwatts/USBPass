#include <QCoreApplication>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "usbpassdevice.h"

#define CMD_SET_KEY "setkey"
#define CMD_SET_NUM_KEYS "setnumkeys"
#define CMD_SET_QUICKKEY "setquickkey"
#define CMD_SET_ACTION "setaction"
#define CMD_RESET "reset"

void usage(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    USBPassDevice usbpass;
    int retval = 0;

    //TODO: Parse args for serial number and such
    //  using getopt_long()
    if (argc < 2) {
        usage(argc, argv);
        return 1;
    }

    usbpass.open();
    if (strncmp(argv[1], CMD_SET_KEY, strlen(CMD_SET_KEY)) == 0) {
        if (argc < 5) {
            usage(argc, argv);
            retval = 1;
        } else {
            usbpass.set_key(atoi(argv[2]),
                            argv[3],
                            argv[4]);
        }
    } else if (strncmp(argv[1], CMD_SET_NUM_KEYS, strlen(CMD_SET_NUM_KEYS)) == 0) {
        if (argc < 3) {
            usage(argc, argv);
            retval = 1;
        } else {
            usbpass.set_num_keys(atoi(argv[2]));
        }
    } else if (strncmp(argv[1], CMD_SET_QUICKKEY, strlen(CMD_SET_QUICKKEY)) == 0) {
        if (argc < 4) {
            usage(argc, argv);
            retval = 1;
        } else {
            usbpass.set_quick_key(atoi(argv[2]),
                                  atoi(argv[3]));
        }
    } else if (strncmp(argv[1], CMD_SET_QUICKKEY, strlen(CMD_SET_QUICKKEY)) == 0) {
        if (argc < 4) {
            usage(argc, argv);
            retval = 1;
        } else {
            usbpass.set_action(atoi(argv[2]),
                                  atoi(argv[3]));
        }
    } else if (strncmp(argv[1], CMD_RESET, strlen(CMD_RESET)) == 0) {
        usbpass.reset();
    }

    usbpass.close();

    return retval;
}

void usage(int argc, char *argv[])
{
    assert(argc >= 1);
    fprintf(stderr,
            "Usage: %s <command> <args>\n"
            "Commands:\n"
            "  " CMD_SET_KEY " <index> <key> <name>\n"
            "  " CMD_SET_NUM_KEYS " <count>\n"
            "  " CMD_SET_QUICKKEY " <quick_index> <key_index>\n"
            "  " CMD_SET_ACTION" <button_id> <action_id>\n"
            "  " CMD_RESET "\n",
            argv[0]
            );
}
