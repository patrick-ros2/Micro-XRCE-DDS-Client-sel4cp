#include <uxr/client/profile/transport/ip/udp/udp_transport_sel4cp.h>
#include "udp_transport_internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool uxr_init_udp_platform(
        uxrUDPPlatform* platform,
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

bool uxr_close_udp_platform(
        uxrUDPPlatform* platform)
{
    (void) platform;
    return true;
}

size_t uxr_write_udp_data_platform(
        uxrUDPPlatform* platform,
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

size_t uxr_read_udp_data_platform(
        uxrUDPPlatform* platform,
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
