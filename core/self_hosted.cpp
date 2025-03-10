#include "self_hosted.h"
#include "port.h"
#include "util.h"

std::string requestLicense(InetAddress address) {
  int sockfd = OsSocket::connectTcpSocket(address);
  if (sockfd < 0) {
    exit(1);
  }

  std::string readBuffer;
  readBuffer.resize(8192);

  std::string request = "GET /license.json HTTP/1.1\n"
                        "Host: app.husarnet.com\n"
                        "User-Agent: husarnet\n"
                        "Accept: */*\n\n";

  SOCKFUNC(send)(sockfd, request.data(), request.size(), 0);
  size_t len = SOCKFUNC(recv)(sockfd, (char*)readBuffer.data(), readBuffer.size(), 0);
  size_t pos = readBuffer.find("\r\n\r\n");

  // second condition makes no sense
  // if (pos == std::string::npos || readBuffer.find("HTTP/1.1 200") != std::string::npos) {
  if (pos == std::string::npos) {
    LOG("invalid response from the server: %s", readBuffer.c_str());
    exit(1);
  }
  pos += 4;
  return readBuffer.substr(pos, len - pos);
}
