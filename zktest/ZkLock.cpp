
#include "ZkLock.h"
#include "zoo_lock.h"
#include <iostream>

using namespace std;

void watcher(zhandle_t * zh, int type, int state, const char * path, void * watcherCtx)
{
	// 这个执行上下文是zookeeper api内建的线程
	ZkLock * pThis = (ZkLock *)watcherCtx;

	(void)watcherCtx;
	(void)zh;
	(void)path;

	cout << "type=" << type << " state=" << state << " path=" << path << endl;

	if (type == ZOO_SESSION_EVENT)
	{
		if (state == ZOO_CONNECTED_STATE)
		{
			pThis->setConnected();
		}
		else if (state == ZOO_EXPIRED_SESSION_STATE)
		{
			pThis->setExpired();
		}
	}
}


ZkLock::ZkLock(string sPath) : m_pZh(NULL), m_sPath(sPath), m_pMux(NULL)
{
	zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);

	m_iState = ZkLockState_Expired;
}

ZkLock::~ZkLock()
{
	m_sPath = "";
	if (m_pZh != NULL)
	{
		if (m_pMux != NULL)
		{
			zkr_lock_destroy(m_pMux);
			delete m_pMux;
			m_pMux = NULL;
		}

		zookeeper_close((zhandle_t *)m_pZh);
		m_pZh = NULL;
	}
}

bool ZkLock::isOwner()
{
	return zkr_lock_isowner(m_pMux);
}

int ZkLock::connect(const string & sCluster)
{
	if (m_pZh != NULL)
	{
		zookeeper_close((zhandle_t *)m_pZh);
		m_pZh = NULL;
	}

	zhandle_t * zh = zookeeper_init(sCluster.c_str(), ::watcher, 5 * 1000, NULL, this, 0);

	m_iState = ZkLockState_Connecting;
	m_pZh = (zhandle *)zh;
	
	return ZOK;
}

int ZkLock::init()
{
	if (m_pMux != NULL)
	{
		zkr_lock_destroy(m_pMux);
		delete m_pMux;
		m_pMux = NULL;
	}

	m_pMux = new zkr_lock_mutex();
	int iRet = zkr_lock_init(m_pMux, (zhandle_t *)m_pZh, (char *)m_sPath.c_str(), &ZOO_OPEN_ACL_UNSAFE);
	return iRet;
}

int ZkLock::lock()
{
	int iRet = zkr_lock_lock(m_pMux);
	return iRet;
}

int ZkLock::unlock()
{
	int iRet = zkr_lock_unlock(m_pMux);
	return iRet;
}

int ZkLock::getVer()
{
	if (isOwner())
	{
		char buf[128];
		int iVer = 0;
		sscanf(zkr_lock_getid(m_pMux), "x-%[0-9,a-z,A-Z]-%d", buf, &iVer);
		return iVer;
	}
	else
	{
		return -1;
	}
}

