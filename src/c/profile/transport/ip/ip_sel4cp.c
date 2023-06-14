// Copyright 2017-present Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <uxr/client/profile/transport/ip/ip.h>
#include <uxr/client/config.h>

#include <stdbool.h>

bool uxr_ip_to_locator(
        char const* ip,
        uint16_t port,
        uxrIpProtocol ip_protocol,
        TransportLocator* locator)
{
    (void) ip;
    (void) port;
    (void) ip_protocol;
    (void) locator;
    return true;
}

bool uxr_locator_to_ip(
        TransportLocator const* locator,
        char* ip,
        size_t size,
        uint16_t* port,
        uxrIpProtocol* ip_protocol)
{
    (void) locator;
    (void) ip;
    (void) size;
    (void) port;
    (void) ip_protocol;
    return true;
}
