#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")
#include "ipheader.h"

int main()
{
    /* Feel free to modify this function to test different things */
    
    unsigned char bytes[] = {
        0x45, 0x00, 0x01, 0xd3, 0xda, 0x8d, 0x40, 0x00,
        0x40, 0x06, 0x8c, 0xd5, 0xc0, 0xa8, 0x01, 0x46,
        0x6c, 0xa0, 0xa3, 0x33 };
    
    struct ipHeader ip;
    
    parseIp(&ip, bytes);
    printIp(&ip);
    hexdump(bytes, sizeof(bytes));

    return 0;
}
