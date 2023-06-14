#include <uxr/client/profile/transport/ip/tcp/tcp_transport_sel4cp.h>
#include "tcp_transport_internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool uxr_init_tcp_platform(
        uxrTCPPlatform* platform,
        uxrIpProtocol ip_protocol,
        const char* ip,
        const char* port)
{
    (void) platform;
    (void) ip_protocol;
    (void) ip;
    (void) port;
    bool rv = true;
    return rv;
}

bool uxr_close_tcp_platform(
        uxrTCPPlatform* platform)
{
    (void) platform;
    return true;
}

size_t uxr_write_tcp_data_platform(
        uxrTCPPlatform* platform,
        const uint8_t* buf,
        size_t len,
        uint8_t* errcode)
{
    (void) platform;
    (void) buf;
    (void) len;
    (void) errcode;
    size_t rv = 0;
    return rv;
}

size_t uxr_read_tcp_data_platform(
        uxrTCPPlatform* platform,
        uint8_t* buf,
        size_t len,
        int timeout,
        uint8_t* errcode)
{
    (void) platform;
    (void) buf;
    (void) len;
    (void) timeout;
    (void) errcode;
    size_t rv = 0;
    return rv;
}

void uxr_disconnect_tcp_platform(
        struct uxrTCPPlatform* platform)
{
    (void) platform;
}
