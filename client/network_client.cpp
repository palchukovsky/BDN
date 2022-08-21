
#include "network_client.hpp"

#include "lib/packet.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace asio = boost::asio;
using asio::ip::tcp;
using asio::ip::udp;

////////////////////////////////////////////////////////////////////////////////

struct TcpClient::Impl {
  asio::io_context m_context{};
  tcp::socket m_socket{m_context};
};

TcpClient::TcpClient(const std::string_view &host,
                     const std::string_view &service)
    : m_pimpl(std::make_unique<Impl>()) {
  tcp::resolver resolver{m_pimpl->m_context};
  asio::connect(m_pimpl->m_socket, resolver.resolve(tcp::v4(), host, service));
}

TcpClient::~TcpClient() = default;

void TcpClient::Send(const Packet &) {
  boost::array<char, 1> bufferData = {{0}};
  const auto &buffer = asio::buffer(bufferData);

  if (m_pimpl->m_socket.send(buffer) != buffer.size()) {
    throw std::runtime_error("Failed to send data into TCP connection");
  }
}

////////////////////////////////////////////////////////////////////////////////

struct UdpClient::Impl {
  asio::io_context m_context{};

  const udp::resolver::results_type m_endpoints;

  udp::socket m_socket{m_context};

  Impl(const std::string_view &host, const std::string_view &service)
      : m_endpoints(Resolve(host, service)) {}

 private:
  udp::resolver::results_type Resolve(const std::string_view &host,
                                      const std::string_view &service) {
    udp::resolver resolver{m_context};
    return resolver.resolve(udp::v4(), host, service);
  }
};

UdpClient::UdpClient(const std::string_view &host,
                     const std::string_view &service)
    : m_pimpl(std::make_unique<Impl>(host, service)) {
  m_pimpl->m_socket.open(udp::v4());
}

UdpClient::~UdpClient() = default;

void UdpClient::Send(const Packet &) {
  boost::array<char, 1> bufferData = {{0}};
  const auto buffer = boost::asio::buffer(bufferData);

  for (const auto &endpoint : m_pimpl->m_endpoints) {
    if (m_pimpl->m_socket.send_to(buffer, endpoint) != buffer.size()) {
      throw std::runtime_error("Failed to send data into UDP connection");
    }
  }
}

////////////////////////////////////////////////////////////////////////////////