#pragma once

#include <mutex>

class		RoukaLock
{
public:
  RoukaLock();
  ~RoukaLock();

  void lock();
  void unlock();
private:
  std::mutex *m;
};

