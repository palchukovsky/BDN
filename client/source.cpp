
#include "source.hpp"

std::optional<Packet> Source::TakeNext() const {
  if (m_next >= 2) {
    return {};
  }

  std::optional<Packet> result{
      std::in_place, m_next,
      boost::posix_time::microsec_clock::universal_time()};

  ++m_next;

  return result;
}
