
#include "ZkLock.h"
#include <unistd.h>

int main(int argc, char * argv[])
{
	(void)argc;
	(void)argv;

	ZkLock L("/bb/match.1");

	L.connect("192.168.60.103:2180");
	while (L.isConnecting())
	{
		sleep(1);
	}

	L.init();

	L.lock();
	while (true)
	{
		if (L.isOwner())
		{
			sleep(3);
		}
		else
		{
			sleep(1);
			L.lock();
		}
	}

	return 0;
}

