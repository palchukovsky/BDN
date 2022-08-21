
#pragma once

#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <stddef.h>

class Packet {
 public:
  using Time = boost::posix_time::ptime;

 public:
  explicit Packet(size_t id, const Time &time);
  Packet(const Packet &) = delete;
  Packet(Packet &&) = default;
  Packet &operator=(const Packet &) = delete;
  Packet &operator=(Packet &&) = default;

 public:
  size_t getId() const { return m_id; }
  const Time &GetTime() const { return m_time; }

 private:
  size_t m_id;
  Time m_time;
};