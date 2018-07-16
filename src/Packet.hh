#pragma once

#include <string>

/// This namespace handles making and reading valid packets to and from the glove
/**
 * There are two kinds of packet headers:
 * * Handshake (3 bytes): [H][min api supported][max api supported]
 * No data for a handshake packet
 * * Vibration (3 bytes): [R][api version][data bytes to read]
 * A vibration packet is a vibration header + data, the data depends on the API version
 */
namespace Packet {
    /// The early beta version. Not compatible with any other version, not recommended ever, mostly here for debugging.
    /**
     * APIv0 is not a valid number recognized by the handshake protocol. 0 is an error value. This is unusable with an actual glove.
     * [motor#][intensity]
     */
    const std::string v0(const char motor, const char intensity);
    /// v1 is the first real version, it includes a version number and is designed to be compatible with future versions.
    /**
     * Just a wrapper around v0. Data is:
     * [motor#][intensity]
     * Total packet (header+data) looks like
     * ['R'][1][2][motor#][intensity]
    */
    const std::string v1(const char motor, const char intensity);

    /// Generates a handshake packet from min and max supported API versions (included)
    /**
     * ['H'][min][max]
     * Note that we'll expect a reply of the form:
     * ['H'][apiLevel]
     */
    const std::string Handshake(char min, char max);
    
    /// Check the response from the glove
    char HandshakeResult(char buffer[], char minAPI, char maxAPI);
};