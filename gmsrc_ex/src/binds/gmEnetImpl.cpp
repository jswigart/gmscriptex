
#include <vector>

#include "enet/enet.h"

#include "gmEnetImpl.h"

//////////////////////////////////////////////////////////////////////////

ENetHost *gHost = 0;
ENetHost *gClient = 0;

typedef std::vector<ENetHost*> ClientList;
ClientList		gClientList;

bool CreateHost(const char *a_ip, unsigned short a_port, int a_maxclients)
{
	ENetAddress addr;
	addr.host = ENET_HOST_ANY;
	addr.port = a_port;

	if(a_ip && enet_address_set_host(&addr, a_ip) != 0)
		return false;

	ENetHost *Host = enet_host_create(&addr,a_maxclients,0,0);
	if(!Host)
		return false;

	gHost = Host;
	return true;
}

void DestroyHost()
{
	enet_host_destroy(gHost);
	gHost = 0;
}

//////////////////////////////////////////////////////////////////////////

bool CreateClient()
{
	ENetHost *Host = enet_host_create(NULL,1,0,0);
	if(!Host)
		return false;

	gClient = Host;
	return true;
}

void DestroyClient()
{
	enet_host_destroy(gClient);
	gClient = 0;
}
