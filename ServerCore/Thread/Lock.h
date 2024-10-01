#pragma once

/*--------------------
 *	RW Spin Lock
 ----------------------*/

/*------------------------------------------------
* 	[WWWWWWWW][WWWWWWWW][RRRRRRRR][RRRRRRRR]
*	W: WriteFlag (Exclusive Lock Owner ThreadId)
*	R: ReadFlag (Shared Lock Count)
*
*	현재 정책은 동일쓰레드가 W락잡은 상태에서 R락 잡기 가능
*	그 반대는 불가능 (따른 애들도 리드락 잡고 있을 수 있기 때문)
*	W->R (O)
*	R->W (X)
* -----------------------------------------------*/

class Lock
{
    enum : uint32
    {
        ACQUIRE_TIMEOUT_TICK = 10000,
        MAX_SPIN_COUNT = 5000,
        WRITE_THREAD_MASK = 0xFFFF'0000,
        READ_COUNT_MASK = 0x0000'FFFF,
        EMPTY_FLAG = 0x0000'0000
    };

public:
    void WriteLock(const char* name);
    void WriteUnlock(const char* name);
    void ReadLock(const char* name);
    void ReadUnlock(const char* name);

private:
    Atomic<uint32> _lockFlag = EMPTY_FLAG;
    uint16 _writeCount = 0;
};

/*----------------
    LockGuards
-----------------*/

class ReadLockGuard
{
public:
    ReadLockGuard(Lock& lock, const char* name) : _lock(lock), _name(name) { _lock.ReadLock(name); }
    ~ReadLockGuard() { _lock.ReadUnlock(_name); }

private:
    Lock& _lock;
    const char* _name;
};

class WriteLockGuard
{
public:
    WriteLockGuard(Lock& lock, const char* name) : _lock(lock), _name(name) { _lock.WriteLock(name); }
    ~WriteLockGuard() { _lock.WriteUnlock(_name); }

private:
    Lock& _lock;
    const char* _name;
};