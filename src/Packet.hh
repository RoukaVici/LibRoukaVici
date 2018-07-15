#pragma once

#include <string>

/// This namespace handles making valid packets from input parameters to send to RoukaVici
namespace Packet {
    /// The early beta version. Not compatible with any other version, not recommended ever, mostly here for debugging.
    /**
     * APIv0 is not a valid number recognized by the handshake protocol. 0 is an error value. This is unusable with an actual glove.
     * [motor][intensity]
     */
    const std::string v0(const char motor, const char intensity);
    /// v1 is the first real version, it includes a version number and is designed to be compatible with future versions.
    /**
     * Total packet (header+data) looks like
     * ['R'][1][2][motor#][intensity]
    */
    const std::string v1(const char motor, const char intensity);

    /// Generates a handshake packet from min and max supported API versions (included)
    /**
     * ['H'][min][max]
     */
    const std::string Handshake(char min, char max);
};