/*
 * Arctic MMORPG Server Software
 * Copyright (c) 2008-2010 Arctic Server Team
 * See COPYING for license details.
 */

#ifndef CONDITION_H
#define CONDITION_H

#ifdef WIN32
// #include <windows.h>
#define MAX_AWAITING_THREADS 10

struct list_entry
{
	HANDLE semaphore;
	long count;
	bool notified;
};

class Condition
{
public:
	ARCTIC_INLINE Condition(Mutex * mutex) : m_nLockCount(0), m_externalMutex(mutex)
	{
		  ::InitializeCriticalSection(&m_critsecWaitSetProtection);
	}

	~Condition()
	{
		::DeleteCriticalSection(&m_critsecWaitSetProtection);
		assert(m_deqWaitSet.empty());
	}

	ARCTIC_INLINE void BeginSynchronized()
	{
		m_externalMutex->Acquire();
		++m_nLockCount;
	}

	ARCTIC_INLINE void EndSynchronized()
	{
		assert(LockHeldByCallingThread());
		--m_nLockCount;
		m_externalMutex->Release();
	}

	DWORD Wait(time_t timeout)
	{
		DWORD dwMillisecondsTimeout = (DWORD)timeout * 1000;
		BOOL bAlertable = FALSE;
		ASSERT(LockHeldByCallingThread());

		// Enter a new event handle into the wait set.
		HANDLE hWaitEvent = Push();
		if( NULL == hWaitEvent )
			return WAIT_FAILED;

		// Store the current lock count for re-acquisition.
		int nThisThreadsLockCount = m_nLockCount;
		m_nLockCount = 0;

		// Release the synchronization lock the appropriate number of times.
		// Win32 allows no error checking here.
		for( int i=0; i<nThisThreadsLockCount; ++i)
		{
			//::LeaveCriticalSection(&m_critsecSynchronized);
			m_externalMutex->Release();
		}

		// NOTE: Conceptually, releasing the lock and entering the wait
		// state is done in one atomic step. Technically, that is not
		// true here, because we first leave the critical section and
		// then, in a separate line of code, call WaitForSingleObjectEx.
		// The reason why this code is correct is that our thread is placed
		// in the wait set *before* the lock is released. Therefore, if
		// we get preempted right here and another thread notifies us, then
		// that notification will *not* be missed: the wait operation below
		// will find the event signalled.

		// Wait for the event to become signalled.
		DWORD dwWaitResult = ::WaitForSingleObjectEx(
			hWaitEvent,
			dwMillisecondsTimeout,
			bAlertable
			);

		// If the wait failed, store the last error because it will get
		// overwritten when acquiring the lock.
		DWORD dwLastError = 0;
		if( WAIT_FAILED == dwWaitResult )
			dwLastError = ::GetLastError();

		// Acquire the synchronization lock the appropriate number of times.
		// Win32 allows no error checking here.
		for( int j=0; j<nThisThreadsLockCount; ++j)
		{
			//::EnterCriticalSection(&m_critsecSynchronized);
			m_externalMutex->Acquire();
		}

		// Restore lock count.
		m_nLockCount = nThisThreadsLockCount;

		// Close event handle
		if( ! CloseHandle(hWaitEvent) )
			return WAIT_FAILED;

		if( WAIT_FAILED == dwWaitResult )
			::SetLastError(dwLastError);

		return dwWaitResult;
	}

	DWORD Wait()
	{
		DWORD dwMillisecondsTimeout = INFINITE;
		BOOL bAlertable = FALSE;
		ASSERT(LockHeldByCallingThread());

		// Enter a new event handle into the wait set.
		HANDLE hWaitEvent = Push();
		if( NULL == hWaitEvent )
			return WAIT_FAILED;

		// Store the current lock count for re-acquisition.
		int nThisThreadsLockCount = m_nLockCount;
		m_nLockCount = 0;

		// Release the synchronization lock the appropriate number of times.
		// Win32 allows no error checking here.
		for( int i=0; i<nThisThreadsLockCount; ++i)
		{
			// ::LeaveCriticalSection(&m_critsecSynchronized);
			m_externalMutex->Release();
		}

		// NOTE: Conceptually, releasing the lock and entering the wait
		// state is done in one atomic step. Technically, that is not
		// true here, because we first leave the critical section and
		// then, in a separate line of code, call WaitForSingleObjectEx.
		// The reason why this code is correct is that our thread is placed
		// in the wait set *before* the lock is released. Therefore, if
		// we get preempted right here and another thread notifies us, then
		// that notification will *not* be missed: the wait operation below
		// will find the event signalled.

		// Wait for the event to become signalled.
		DWORD dwWaitResult = ::WaitForSingleObjectEx(
			hWaitEvent,
			dwMillisecondsTimeout,
			bAlertable
			);

		// If the wait failed, store the last error because it will get
		// overwritten when acquiring the lock.
		DWORD dwLastError = 0;
		if( WAIT_FAILED == dwWaitResult )
			dwLastError = ::GetLastError();

		// Acquire the synchronization lock the appropriate number of times.
		// Win32 allows no error checking here.
		for( int j=0; j<nThisThreadsLockCount; ++j)
		{
			//::EnterCriticalSection(&m_critsecSynchronized);
			m_externalMutex->Acquire();
		}

		// Restore lock count.
		m_nLockCount = nThisThreadsLockCount;

		// Close event handle
		if( ! CloseHandle(hWaitEvent) )
			return WAIT_FAILED;

		if( WAIT_FAILED == dwWaitResult )
			::SetLastError(dwLastError);

		return dwWaitResult;

	}

	void Signal()
	{
		// Pop the first handle, if any, off the wait set.
		HANDLE hWaitEvent = Pop();

		// If there is not thread currently waiting, that's just fine.
		if(NULL == hWaitEvent)
			return;

		// Signal the event.
		SetEvent(hWaitEvent);
	}

	void Broadcast()
	{
		// Signal all events on the deque, then clear it. Win32 allows no
		// error checking on entering and leaving the critical section.
		//
		::EnterCriticalSection(&m_critsecWaitSetProtection);
		std::deque<HANDLE>::const_iterator it_run = m_deqWaitSet.begin();
		std::deque<HANDLE>::const_iterator it_end = m_deqWaitSet.end();
		for( ; it_run < it_end; ++it_run )
		{
			if( ! SetEvent(*it_run) )
				return;
		}
		m_deqWaitSet.clear();
		::LeaveCriticalSection(&m_critsecWaitSetProtection);
	}

private:

	HANDLE Push()
	{
		// Create the new event.
		HANDLE hWaitEvent = ::CreateEvent(
			NULL,  // no security
			FALSE, // auto-reset event
			FALSE, // initially unsignalled
			NULL   // string name
			);
		//
		if( NULL == hWaitEvent ) {
			return NULL;
		}

		// Push the handle on the deque.
		::EnterCriticalSection(&m_critsecWaitSetProtection);
		m_deqWaitSet.push_back(hWaitEvent);
		::LeaveCriticalSection(&m_critsecWaitSetProtection);

		return hWaitEvent;
	}

	HANDLE Pop()
	{
		// Pop the first handle off the deque.
		::EnterCriticalSection(&m_critsecWaitSetProtection);
		HANDLE hWaitEvent = NULL; 
		if( 0 != m_deqWaitSet.size() )
		{
			hWaitEvent = m_deqWaitSet.front();
			m_deqWaitSet.pop_front();
		}
		::LeaveCriticalSection(&m_critsecWaitSetProtection);

		return hWaitEvent;
	}

	BOOL LockHeldByCallingThread()
	{
		// BOOL bTryLockResult = ::TryEnterCriticalSection(&m_critsecSynchronized);
		BOOL bTryLockResult = m_externalMutex->AttemptAcquire();

		// If we didn't get the lock, someone else has it.
		//
		if( ! bTryLockResult )
		{
			return FALSE;
		}

		// If we got the lock, but the lock count is zero, then nobody had it.
		if( 0 == m_nLockCount )
		{
			assert( bTryLockResult );
			// ::LeaveCriticalSection(&m_critsecSynchronized);
			m_externalMutex->Release();
			return FALSE;
		}

		// Release lock once. NOTE: we still have it after this release.
		// Win32 allows no error checking here.
		assert( bTryLockResult && 0 < m_nLockCount );
		// ::LeaveCriticalSection(&m_critsecSynchronized);
		m_externalMutex->Release();

		return TRUE;
	}

	std::deque<HANDLE> m_deqWaitSet;
	CRITICAL_SECTION m_critsecWaitSetProtection;
	Mutex * m_externalMutex;
	int m_nLockCount;
};

#else

class Condition
{
public:
	ARCTIC_INLINE Condition(Mutex *m)
	{
		mut=m;
		pthread_cond_init(&cond,NULL);
	}
	ARCTIC_INLINE ~Condition()
	{
		pthread_cond_destroy(&cond);
	}

	ARCTIC_INLINE void Signal()
	{
		pthread_cond_signal(&cond);
	}
	ARCTIC_INLINE void Broadcast()
	{
		pthread_cond_broadcast(&cond);
	}
	ARCTIC_INLINE void Wait()
	{
		pthread_cond_wait(&cond,&mut->mutex);
	}
	ARCTIC_INLINE bool Wait(time_t seconds)
	{
		timespec tv;
		tv.tv_nsec = 0;
		tv.tv_sec = seconds;
		if(pthread_cond_timedwait(&cond, &mut->mutex, &tv) == 0)
			return true;
		else
			return false;
	}
	ARCTIC_INLINE void BeginSynchronized()
	{
		mut->Acquire();
	}
	ARCTIC_INLINE void EndSynchronized()
	{
		mut->Release();
	}
private:
	pthread_cond_t cond;
	Mutex *mut;

};

#endif

#endif
