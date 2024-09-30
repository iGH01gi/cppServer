#include "pch.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <iostream>

#include "Thread/ThreadManager.h"

CoreGlobal Core;

void ThreadMain()
{
	while (true)
	{
		cout << "Hello I am thread... " << LThreadId << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
}

int main()
{
	for (int32 i = 0; i < 5; ++i)
	{
		GThreadManager->Launch(ThreadMain);

	}

	GThreadManager->Join();
}
