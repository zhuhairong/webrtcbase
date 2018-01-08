#include "webrtc/base/asyncudpsocket.h"
#include "webrtc/base/socketserver.h"
#include "webrtc/base/thread.h"
#include <stdio.h>

using namespace rtc;

SocketServer* ss_;
const IPAddress kIPv4Loopback(INADDR_LOOPBACK);

static void ConnectInternal(const IPAddress& loopback)
{
	SocketAddress accept_addr;
	printf("1\n");
	scoped_ptr<AsyncSocket> client(ss_->CreateAsyncSocket(loopback.family(), SOCK_STREAM));
	printf("2\n");
	scoped_ptr<AsyncSocket> server(ss_->CreateAsyncSocket(loopback.family(), SOCK_STREAM));
	printf("3\n");
	server->Bind(SocketAddress(loopback, 0));
	printf("4\n");
	server->Listen(5);
	printf("5\n");
	server->Accept(&accept_addr);
	printf("6\n");
	client->Connect(server->GetLocalAddress());
	printf("7\n");
	scoped_ptr<AsyncSocket> accepted(server->Accept(&accept_addr));

	printf("accept_addr = %s\n", accept_addr.ToString().c_str());
	printf("accept local = %s\n", accepted->GetLocalAddress().ToString().c_str());
	printf("accept remote = %s\n", accepted->GetRemoteAddress().ToString().c_str());
	printf("client local = %s\n", client->GetLocalAddress().ToString().c_str());
	printf("client remote = %s\n", client->GetRemoteAddress().ToString().c_str());
	printf("server local = %s\n", server->GetLocalAddress().ToString().c_str());
	printf("server remote = %s\n", server->GetRemoteAddress().ToString().c_str());
}

static void ConnectWithDnsLookupInternal(const IPAddress& loopback, const std::string& host)
{
//	SocketAddress accept_addr;
//
//	scoped_ptr<AsyncSocket> client(ss_->CreateAsyncSocket(loopback.family(), SOCK_STREAM));
//
//	scoped_ptr<AsyncSocket> server(ss_->CreateAsyncSocket(loopback.family(), SOCK_STREAM));
//	server->Bind(SocketAddress(loopback, 0));
//	server->Listen(5);
//
//	SocketAddr  ess dns_addr(server->GetLocalAddress());
//	dns_addr.SetIP(host);
}
/////////////////////////////////////////////////////////////////////////////

void TestConnectIPv4()
{
	ConnectInternal(kIPv4Loopback);
}

int main()
{
	ss_ = Thread::Current()->socketserver();
	TestConnectIPv4();
	return 0;
}
