#include "udp_transport_datagram_internal.h"

#include <stdbool.h>

bool uxr_init_udp_transport_datagram(
        uxrUDPTransportDatagram* transport)
{
    (void) transport;
    return true;
}

bool uxr_close_udp_transport_datagram(
        uxrUDPTransportDatagram* transport)
{
    (void) transport;
    return true;
}

bool uxr_udp_send_datagram_to(
        uxrUDPTransportDatagram* transport,
        const uint8_t* buf,
        size_t len,
        const TransportLocator* locator)
{
    (void) transport;
    (void) buf;
    (void) len;
    (void) locator;
    return true;
}

bool uxr_udp_recv_datagram(
        uxrUDPTransportDatagram* transport,
        uint8_t** buf,
        size_t* len,
        int timeout)
{
    (void) transport;
    (void) buf;
    (void) len;
    (void) timeout;
    return true;
}

void uxr_bytes_to_ip(
        const uint8_t* bytes,
        char* ip)
{
    (void) bytes;
    (void) ip;
}
