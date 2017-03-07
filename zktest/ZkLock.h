
#ifndef ZKLOCK_H_
#define ZKLOCK_H_

#include <string>

struct zhandle;
struct zkr_lock_mutex;

enum ZkLockState
{
	ZkLockState_None		= 0,
	ZkLockState_Connecting	= 1,
	ZkLockState_Connected	= 2,
};

class ZkLock
{
public:
	ZkLock(std::string sPath);
	~ZkLock();

	int connect(const std::string & sCluster);
	void setConnected() {m_iState = ZkLockState_Connected;}
	bool isConnected()  {return (m_iState == ZkLockState_Connected);}
	bool isConnecting() {return (m_iState == ZkLockState_Connecting);}

	int init();
	int lock();
	int unlock();

	bool isOwner();
	int getVer();

private:
	zhandle *				m_pZh;
	std::string				m_sPath;
	volatile int			m_iState;
	zkr_lock_mutex *		m_pMux;
};

#endif // ZKLOCK_H_

