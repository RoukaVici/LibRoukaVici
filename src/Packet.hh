#pragma once

#include <string>

/// This namespace handles making valid packets from input parameters to send to RoukaVici
namespace Packet {
    /// The early beta version. Not compatible with any other version, not recommended ever, mostly here for debugging
    /**
     * [R][motor][intensity]
     */
    const std::string v0(const char motor, const char intensity);
    /// v1 is the first real version, it includes a version number and is designed to be compatible with future versions.
    /**
     * ['R'][1][motor][intensity]
     */
    const std::string v1(const char motor, const char intensity);
};