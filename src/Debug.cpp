#include <iostream>
#include <string>
#include <fstream>
#include "Debug.hh"
#include "RoukaLock.hh"

static int debugMethod = 0;
static DebugCallback cb = nullptr;
static std::string outputFileName = "./RoukaViciLog.txt";
static RoukaLock *lock = new RoukaLock();


int Debug::GetLogMode()
{
  return debugMethod;
}

void Debug::SetLogMode(const int method)
{
  lock->lock();
  switch (method)
    {
    case 0: debugMethod = 0; break;
    case 1: debugMethod = 1; break;
    case 2: debugMethod = 2; break;

    case 3: debugMethod = 2; break;
    case 4: debugMethod = 4; break;

    default: debugMethod = 0; break;
    }
  if (method == 3)
  {
    lock->unlock();
    Debug::Log("UnityDebug mode is deprecated and will be removed in later versions. "
    "Please use debugMethod=2 (regular callback) instead", true);
    lock->lock();
  }
  lock->unlock();
}

void Debug::SetLogFile(const std::string& name)
{
  lock->lock();
  outputFileName = name;
  lock->unlock();
}

void Debug::RegisterCallback(DebugCallback callback)
{
  lock->lock();
  if (callback)
    {
      cb = callback;
    }
  lock->unlock();
}

static void stdOut(const std::string& msg)
{
  std::cout << msg << std::endl;
}

static void stdErr(const std::string& msg)
{
  std::cerr << msg << std::endl;
}

static void fileLog(const std::string& msg)
{
  std::ofstream file;
  file.open(outputFileName, std::ios_base::app);
  file << msg << std::endl;
}

static void callback(const std::string& msg)
{
  if (cb)
    {
      cb(msg.c_str());
    }
}

void Debug::Log(const std::string& msg, bool force)
{
  const std::string logMsg = "[LibRV.LOG] " + msg;
  // If we're not in Verbose mode, check if the message should be forced through, otherwise ignore it
  // If we're in verbose mode, it goes through either way
  lock->lock();
#ifndef ROUKAVERBOSE
  if (force)
#else
    (void)(force);
#endif
  switch (debugMethod) {
  case 0: stdOut(logMsg); break;
  case 1: fileLog(logMsg); break;
  case 2: callback(logMsg); break;
  case 4: break;
  }
  lock->unlock();
}

// Error messages are always shown, no need for 2nd param
// Err writes to std::cerr, not std::cout
void Debug::Err(const std::string& msg)
{
  lock->lock();
  const std::string errMsg = "[LibRV.ERR] " + msg;
  switch (debugMethod) {
  case 0: stdErr(errMsg); break;
  case 1: fileLog(errMsg); break;
  case 2: callback(errMsg); break;
  case 4: break;
  }
  lock->unlock();
}
