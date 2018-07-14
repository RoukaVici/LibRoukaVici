#include "Packet.hh"

const std::string Packet::v0(const char motor, const char intensity)
{
      char msg[2] = {motor, intensity};
      return std::string(msg);
}

const std::string Packet::v1(const char motor, const char intensity)
{
      char msg[4] = {'R', 1, motor, intensity};
      return std::string(msg);
}