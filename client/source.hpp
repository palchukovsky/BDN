#pragma once

#include "lib/packet.hpp"

#include <optional>

class Source {
 public:
  std::optional<Packet> TakeNext() const;

 private:
  mutable size_t m_next;
};
