#pragma once

#include "client.hpp"

#include <string_view>

////////////////////////////////////////////////////////////////////////////////

class TcpClient : public Client {
 public:
  explicit TcpClient(const std::string_view &serverHost,
                     const std::string_view &serverService);
  ~TcpClient() override;

 public:
  void Send(const Packet &) override;

 private:
  struct Impl;
  const std::unique_ptr<Impl> m_pimpl;
};

////////////////////////////////////////////////////////////////////////////////

class UdpClient : public Client {
 public:
  UdpClient(const std::string_view &serverHost,
            const std::string_view &serverService);
  ~UdpClient() override;

 public:
  void Send(const Packet &) override;

 private:
  struct Impl;
  const std::unique_ptr<Impl> m_pimpl;
};

////////////////////////////////////////////////////////////////////////////////
