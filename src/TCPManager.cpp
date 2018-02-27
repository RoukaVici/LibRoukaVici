
#include <iostream>

// Linux network includes
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <cstring>

#include <string.h>
#include <errno.h>

#include "TCPManager.hh"

const int PORT = 4848;
const char * const HOST = "192.168.1.98";

TCPManager::TCPManager() : sd(-1)
{
}

TCPManager::~TCPManager()
{
  shutdown(sd, 0);
}

/// Finds the Raspberry Pi
/**
 * Return codes:
 * 0: Success
 * 1: Bad IP
 * 2: Could not resolve host
 * 3: Could not connect to host
 */
int TCPManager::FindRPi()
{
  int ret;
  struct sockaddr_in server;
  struct in_addr ipv4addr;
  struct hostent *hp;

  sd = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;

  std::memset(&ipv4addr, 0, sizeof(ipv4addr));
  if (!inet_aton(HOST, &ipv4addr))
    {
      std::cerr << "Can't parse IP: " << HOST << std::endl;
      return 1;
    }

  hp = gethostbyaddr((const void*)&ipv4addr, sizeof(ipv4addr), AF_INET);
  if (hp == NULL)
    {
      std::cerr << "Could not resolve " << HOST << ": " << strerror(h_errno) <<std::endl;
      return 2;
    }

  std::memcpy(&(server.sin_addr.s_addr), hp->h_addr, hp->h_length);
  server.sin_port = htons(PORT);

  if (connect(sd, (const sockaddr *)&server, sizeof(server)) < 0)
    {
      std::cerr << "Could not connect: " << strerror(errno) << std::endl;
      return 3;
    }
  return 0;
}

void TCPManager::WriteToRPi(const std::string& msg)
{
  send(sd, msg.c_str(), msg.length(), 0);
}
