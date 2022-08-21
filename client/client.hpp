#pragma once

#include "fwd.hpp"

#include <chrono>

class Client {
 public:
  Client() = default;
  Client(const Client &) = delete;
  Client(Client &&) = default;
  Client &operator=(const Client &) = delete;
  Client &operator=(Client &&) = default;
  virtual ~Client() = default;

  virtual void Send(const Packet &) = 0;
};
