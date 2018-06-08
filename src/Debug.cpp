#include <iostream>
#include <string>
#include <fstream>
#include "Debug.hh"

// const
const std::string prefix = "[LibRoukaVici]";

// Local variables
int debugMethod = 0;
std::string outputFileName = "./RoukaViciLog.txt";

#ifdef _WIN32
UnityDebugCallback ucb = nullptr;
#endif
DebugCallback cb = nullptr;

int Debug::GetLogMode()
{
  return debugMethod;
}

void Debug::SetLogMode(const int method)
{
  switch (method)
    {
    case 0: debugMethod = 0; break;
    case 1: debugMethod = 1; break;
    case 2: debugMethod = 2; break;
#ifdef _WIN32
    case 3: debugMethod = 3; break;
#endif
    default: debugMethod = 0; break;
    }
}

void Debug::SetLogFile(const std::string& name)
{
  outputFileName = name;
}

void Debug::RegisterCallback(DebugCallback callback)
{
  if (callback)
    {
      cb = callback;
    }
}

void stdOut(const std::string& msg)
{
  std::cout << msg << std::endl;
}

void fileLog(const std::string& msg)
{
  std::ofstream file;
  file.open(outputFileName, std::ios_base::app);
  file << msg << std::endl;
}

void callback(const std::string& msg)
{
  if (cb)
    {
      cb(msg.c_str());
    }
}

#ifdef _WIN32
void  unityCalllback(const std::string& msg)
{
  if (ucb)
    {
      ucb(msg.c_str());
    }
}
#endif

void Debug::Log(const std::string& msg, bool force)
{
  const std::string logMsg = (msg.length() > 0 && msg[0] == '[') ? prefix + msg : prefix + " " + msg;
  // If we're not in Verbose mode, check if the message should be forced through, otherwise ignore it
  // If we're in verbose mode, it goes through either way
#ifndef ROUKAVERBOSE
  if (force)
#else
    (void)(force);
#endif
    switch (debugMethod) {
    case 0: stdOut(logMsg); break;
    case 1: fileLog(logMsg); break;
    case 2: callback(logMsg); break;
#ifdef _WIN32
    case 3: unityCallback(logMsg); break;
#endif
    }
}
