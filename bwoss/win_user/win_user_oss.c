/* 
 * Copyright (c) 2009 Tianjin Zhongke Blue Whale 
 *               Information Technologies Co., Ltd
 * 
 * bwlib.h - This file contains all the lock function prototypes
 * that are exported by winOS.
 * 
 * 
 * Dependencies:
 * win_user_oss.h
 *
 * ChangeLog: 2009-12-2 Initial Created
 * 
 * ToDo:
 *  None
 */

 /* 
  * Copyright (c) 2009 Institute of Computing Technology,
  *                    Chinese Academy of Sciences
  * 
  * Author:  
  */
#include "win_user_oss.h"




////global variable
int m_nLockCount;

int m_nWaitingWriters;
int m_nWaitingReaders;

HANDLE m_hReaderEvent;
HANDLE m_hWriterEvent;
HANDLE m_hLockCountMutex;


//// tool functions
int waiting_writer();
int increment_writers();
int decrement_writers();

int waiting_reader();
int increment_readers();
int decrement_readers();

void initialize_lock()
{
    m_nLockCount = 0;
    m_nWaitingReaders = 0;
	m_nWaitingReaders = 0;
	
	m_hReaderEvent = CreateEvent(NULL, 0, 0, NULL); 
	m_hWriterEvent = CreateEvent(NULL, 0, 0, NULL);
	m_hLockCountMutex = CreateMutex(NULL, 0, NULL);
}

void clean_lock()
{
	
	ReleaseMutex(m_hLockCountMutex);
	
	CloseHandle(m_hLockCountMutex);
	CloseHandle(m_hWriterEvent);
	CloseHandle(m_hReaderEvent);
}
int lock_write()
{
	if (waiting_writer() == 0)
	{
		return 0;
	}
	
	// writers compete with readers and fellow-writers ...
	while (m_nLockCount)
	{
		if (WaitForSingleObject(m_hWriterEvent, INFINITE) != WAIT_OBJECT_0)
		{
			return 0;
		}
	}
	
	if (increment_writers() == 0)
	{
		return 0;
	}
	
	return 1;
}

int unlock_write()
{
	if (decrement_writers() == 0)
	{
		return 0;
	}
	
	// Readers are preferred in the following section....
	if (m_nWaitingWriters && !m_nWaitingReaders)
	{
		// when no readers are waiting... signal writers, if any
		if (!SetEvent(m_hWriterEvent)) // will release one waiting writer
		{
			return 0;
		}
	}
	else
	{
		while (m_nWaitingReaders > 0)
		{
			if (!SetEvent(m_hReaderEvent)) // will release ALL waiting readers
			{
				return 0;
			}
		}
	}
	
	return 1;
}

int lock_read()
{
	if (waiting_reader() == 0)
	{
		return 0;
	}
	
	if (m_nLockCount < 0)
	{
		// a reader thread must wait for the read event.. if a writer is holding lock
		if (WaitForSingleObject(m_hReaderEvent, INFINITE) != WAIT_OBJECT_0)
		{
			return 0;
		}
		
		ResetEvent(m_hReaderEvent);
	}
	
	if (increment_readers() == 0)
	{
		return 0;
	}
	
	return 1;
}

int unlock_read()
{
	if (decrement_readers() == 0)
	{
		return 0;
	}
	
	if (!m_nWaitingReaders && !m_nLockCount)
	{
		if (!SetEvent(m_hWriterEvent)) // will release one waiting writer
		{
			return 0;
		}
	}
	
	return 1;
}

int get_lock_count()
{
	int nCount = 0;
	
	if (WaitForSingleObject(m_hLockCountMutex, INFINITE) != WAIT_OBJECT_0)
	{
		return 0;
	}
	
	nCount = m_nLockCount;
	
	ReleaseMutex(m_hLockCountMutex);
	
	return nCount;
}

int get_waiting_writers()
{
	int nCount = 0;
	
	if (WaitForSingleObject(m_hLockCountMutex, INFINITE) != WAIT_OBJECT_0)
	{
		return 0;
	}
	
	nCount = m_nWaitingWriters;
	
	ReleaseMutex(m_hLockCountMutex);
	
	return nCount;
}

int get_waiting_readers()
{
	int nCount = 0;
	
	if (WaitForSingleObject(m_hLockCountMutex, INFINITE) != WAIT_OBJECT_0)
	{
		return 0;
	}
	
	nCount = m_nWaitingReaders;
	
	ReleaseMutex(m_hLockCountMutex);
	
	return nCount;
}

int waiting_writer()
{
	if(WaitForSingleObject(m_hLockCountMutex, INFINITE) != WAIT_OBJECT_0)
	{
		return 0;
	}
	
	m_nWaitingWriters++;
	
	ReleaseMutex(m_hLockCountMutex);
	
	return 1;
}

int increment_writers()
{
	if (WaitForSingleObject(m_hLockCountMutex, INFINITE) != WAIT_OBJECT_0)
	{
		return 0;
	}
	
	// Only one thread can obtain a write lock .. so lock count goes underground
	// InterlockedDecrement() could also be used
	if (m_nLockCount == 0)
	{
		m_nLockCount = -1;
		m_nWaitingWriters--;
	}
	
	ReleaseMutex(m_hLockCountMutex);
	
	return 1;
}

int decrement_writers()
{
	if (WaitForSingleObject(m_hLockCountMutex, INFINITE) != WAIT_OBJECT_0)
	{
		return 0;
	}
	
	if (m_nLockCount == -1)
	{
		m_nLockCount = 0;
	}
	
	ReleaseMutex(m_hLockCountMutex);
	
	return 1;
}

int waiting_reader()
{
	if (WaitForSingleObject(m_hLockCountMutex, INFINITE) != WAIT_OBJECT_0)
	{
		return 0;
	}

	// One more thread is waiting on read event
	m_nWaitingReaders++;

	ReleaseMutex(m_hLockCountMutex);

	return 1;
}

int increment_readers()
{
	if (WaitForSingleObject(m_hLockCountMutex, INFINITE) != WAIT_OBJECT_0)
	{
		return 0;
	}
	
	// One more thread has obtained a read lock and is no longer waiting
	if (m_nLockCount >= 0)
	{
		m_nLockCount++;
		m_nWaitingReaders--;
	}
	
	ReleaseMutex(m_hLockCountMutex);
	
	return 1;
}

int decrement_readers()
{
	if (WaitForSingleObject(m_hLockCountMutex, INFINITE) != WAIT_OBJECT_0)
	{
		return 0;
	}

	if (m_nLockCount > 0)
	{
		// One less thread holding read lock
		m_nLockCount--;
	}
	
	ReleaseMutex(m_hLockCountMutex);
	
	return 1;
}






