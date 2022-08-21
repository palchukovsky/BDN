
#include "config.hpp"
#include "network_client.hpp"
#include "source.hpp"
#include "task.hpp"

#include <future>
#include <iostream>
#include <vector>

int main() {
  try {
    std::vector<std::future<void>> tasks;

    if constexpr (Config::isTcpSupported) {
      tasks.push_back(std::async([]() {
        TcpClient tcp{Config::serverHost, Config::serverServiceTcp};
        Task("TCP", tcp, Source{}, std::cout).Execute();
      }));
    }

    if constexpr (Config::isUdpSupported) {
      tasks.push_back(std::async([]() {
        UdpClient udp{Config::serverHost, Config::serverServiceUdp};

        Task("UDP", udp, Source{}, std::cout).Execute();
      }));
    }

    for (auto &task : tasks) {
      try {
        task.get();
      } catch (const std::exception &ex) {
        std::cerr << "Failed to execute task: \"" << ex.what() << "\"."
                  << std::endl;
      }
    }
  } catch (const std::exception &ex) {
    std::cerr << "Unexpected error: \"" << ex.what() << "\"." << std::endl;

    return 1;
  } catch (...) {
    std::cerr << "Unexpected UNKNOWN error." << std::endl;

    return 1;
  }

  return 0;
}