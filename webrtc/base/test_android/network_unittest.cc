#include <stdio.h>
#include "webrtc/base/network.h"
#include "webrtc/base/socketaddress.h"
#include <vector>
#include <unistd.h>

using namespace rtc;

class NetworkTest : public sigslot::has_slots<> , public BasicNetworkManager
{
public:
	NetworkTest()
		:callback_called(false)
	{
	}

	void OnNetworkChanged()
	{
		callback_called = true;
	}

	void MergeNetworkList(	const NetworkManager::NetworkList& list, bool* changed)
	{
		BasicNetworkManager::MergeNetworkList(list, changed);
	}

	bool IsIgnoredNetwork(const Network& network)
	{
		return BasicNetworkManager::IsIgnoredNetwork(network);
	}

	NetworkManager::NetworkList GetNetworks(bool include_ignored)
	{
		NetworkManager::NetworkList list;
		BasicNetworkManager::CreateNetworks(include_ignored, &list);
		return list;
	}

protected:
	bool callback_called;
};

void test1()
{
	Network ipv4_network1("test_eth0", "Test Network Adapter 1", IPAddress(0x12345600U), 24);
	printf("network name:%s\n", ipv4_network1.name().c_str());
	printf("network description:%s\n", ipv4_network1.description().c_str());

	Network ipv4_network2("test_eth1", "Test Network Adapter 2", IPAddress(0x000100000U), 16);
	NetworkTest network_manager;
	int isIgnored = network_manager.IsIgnoredNetwork(ipv4_network1);
	printf("ignored network1:%d\n", isIgnored);
	isIgnored = network_manager.IsIgnoredNetwork(ipv4_network2);
	printf("ignored network2:%d\n", isIgnored);
}

void test2()
{
	NetworkTest network_manager;
	NetworkManager::NetworkList result = network_manager.GetNetworks(true);
	NetworkManager::NetworkList::iterator it;

	for(it = result.begin(); it != result.end(); ++it)
	{
		sockaddr_storage storage;
		memset(&storage, 0, sizeof(storage));
		IPAddress ip = (*it)->GetBestIP();
		SocketAddress bindaddress(ip, 0);
		bindaddress.SetScopeID((*it)->scope_id());

		int fd = static_cast<int>(socket(ip.family(), SOCK_STREAM, IPPROTO_TCP));
		if(fd > 0)
		{
			size_t ipsize = bindaddress.ToSockAddrStorage(&storage);
			int success = ::bind(fd, reinterpret_cast<sockaddr*>(&storage), static_cast<int>(ipsize));

			printf("success:%d\n", success);
			close(fd);
		}
		delete(*it);
	}
}

int main()
{
	test1();
	test2();
	return 0;
}
