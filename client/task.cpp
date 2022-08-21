#include "task.hpp"

#include "client.hpp"
#include "config.hpp"
#include "source.hpp"

#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <iostream>
#include <thread>

using namespace std::chrono_literals;

namespace {
constexpr auto numberOfPacketsInPackOfPackets = 1000;
constexpr auto numberOfPacketsOfPackets = numberOfPacketsInPackOfPackets * 2;

constexpr auto sleepDurationBetweenEachPacket = 10ms;
constexpr auto sleepDurationBetweenPackOfPackets = 10s;
}  // namespace

void Task::Execute() {
  for (size_t i = 0; i < numberOfPacketsOfPackets;) {
    const auto &packet = m_source.TakeNext();
    if (!packet) {
      break;
    }

    ExecuteIteration(*packet);

    if (++i >= numberOfPacketsOfPackets) {
      break;
    }

    const auto &sleepDuration = numberOfPacketsInPackOfPackets == 0
                                    ? sleepDurationBetweenEachPacket
                                    : sleepDurationBetweenPackOfPackets;
    std::this_thread::sleep_for(sleepDuration);
  }
}

void Task::ExecuteIteration(const Packet &packet) {
  m_client.Send(packet);

  if constexpr (Config::isManySupported) {
    m_reportOut << m_name << " ";
  }

  m_reportOut << "Sent: #" << packet.getId() << "\t#"
              << packet.GetTime().time_of_day() << std::endl;
}
