#pragma once

#include "source.hpp"

#include "fwd.hpp"

#include <iosfwd>
#include <string>

class Task {
 public:
  Task(std::string name, Client &client, Source source, std::ostream &reportOut)
      : m_name(std::move(name)),
        m_client(client),
        m_source(std::move(source)),
        m_reportOut(reportOut) {}
  Task(const Task &) = delete;
  Task(Task &&) = delete;
  Task &operator=(const Task &) = delete;
  Task &operator=(Task &&) = delete;

  void Execute();

 private:
  void ExecuteIteration(const Packet &packet);

 private:
  const std::string m_name;
  Client &m_client;
  const Source m_source;
  std::ostream &m_reportOut;
};
