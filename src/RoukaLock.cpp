#include "RoukaLock.hh"

RoukaLock::RoukaLock()
{
  this->m = new std::mutex();
}

RoukaLock::~RoukaLock()
{
  delete this->m;
}

void RoukaLock::lock()
{
  this->m->lock();
}

void RoukaLock::unlock()
{
  this->m->unlock();
}
