
#include "ZkLock.h"
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "usage: ./test_zk /bb/match.1 192.168.60.103:2180,192.168.60.103:2181,192.168.60.103:2182" << endl;
		return 0;
	}

	cout << "lock name: " << argv[1] << endl;
	cout << "lock cluster: " << argv[2] << endl;

	string sCluster = argv[2];
	ZkLock L(argv[1]);

	bool bPrimary = false;
	bool bConnected = false;
	while (true)
	{
		if (L.isExpired())
		{
			bPrimary = false;
			bConnected = false;
			L.connect(sCluster);
			continue;
		}

		if (L.isConnecting())
		{
			bPrimary = false;
			bConnected = false;
			sleep(1);
			continue;
		}

		if (L.isConnected())
		{
			if (!bConnected)
			{
				L.init();
				bConnected = true;
				cout << "i am slave when connect zk" << endl;
			}

			if (!bPrimary)
			{
				L.lock();
				if (L.isOwner())
				{
					cout << "i am primary, ver=" << L.getVer() << endl;
					bPrimary = true;
				}
			}

			sleep(1);
		}
	}

	return 0;
}

