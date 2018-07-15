#include "Packet.hh"

/// This function adds the header to a data packet
const std::string vibrationHeader(char apiNumber, const std::string& data)
{
      const char buff[3] = {'R', apiNumber, static_cast<char>(data.length())};
      return std::string(buff) + data;
}

const std::string Packet::v0(const char motor, const char intensity)
{
      char msg[2] = {motor, intensity};
      return std::string(msg);
}

const std::string Packet::v1(const char motor, const char intensity)
{
      // The initial buffer
      const char buff[2] = {motor, intensity};
      // The data packet created from the buffer
      std::string data(buff, 2);
      return vibrationHeader(1, data);
}

const std::string Packet::Handshake(char min, char max)
{
      const char buff[3] = {'H', min, max};
      return std::string(buff);
}