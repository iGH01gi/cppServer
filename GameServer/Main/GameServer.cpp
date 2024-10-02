#include "pch.h"
#include <thread>
#include <iostream>
#include "Thread/ThreadManager.h"

class TestLock
{
	USE_LOCK;

public:
	int32 TestRead()
	{
		READ_LOCK;

		if (_queue.empty())
			return -1;

		return _queue.front();
	}

	void TestPush()
	{
		WRITE_LOCK;

		_queue.push(rand() % 100);
	}

	void TestPop()
	{
		WRITE_LOCK;

		if (!_queue.empty())
			_queue.pop();
	}

private:
	queue<int32> _queue;
};

TestLock testLock;

void ThreadWrite()
{
	while (true)
	{
		testLock.TestPush();
		this_thread::sleep_for(1ms);
		testLock.TestPop();
	}
}

void ThreadRead()
{
	while(true)
	{
		int32 value = testLock.TestRead();
		cout << value << endl;
		this_thread::sleep_for(1ms);
	}
}

template<class T>

void print(T& n) {

	std::cout << "l-value" << std::endl;
	n = 1;
	cout << n << endl;
}



template<class T>

void print(T&& n) {

	std::cout << "r-value" << std::endl;

}



template<class T>

void fnc(T&& n) {

	print(n);

}

int main()
{
	/*int n = 10;

	fnc(move(n));

	fnc("hwan");*/

	//fnc(1.123);
	int&& a = 1;
	print(forward<int>(a));


	/*for (int32 i = 0; i < 2; ++i)
	{
		GThreadManager->Launch(ThreadWrite);
	}

	for (int32 i = 0; i < 5; ++i)
	{
		GThreadManager->Launch(ThreadRead);
	}

	GThreadManager->Join();*/
}
