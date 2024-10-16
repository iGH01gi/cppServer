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


// 32바이트 정렬을 위한 구조체 정의
DECLSPEC_ALIGN(32)
struct BigStruct {
	char data[30]; // 30바이트 크기
};

// 16바이트 정렬을 위한 SListEntry 구조체
DECLSPEC_ALIGN(16)
struct SListEntry {
	SListEntry* next; // 다음 항목을 가리키는 포인터
};

// MyClass 정의
class MyClass {
public:
	SListEntry entry; // SListEntry를 멤버로 사용
	BigStruct bigData; // 30바이트 크기의 멤버 추가
};

int main()
{
	MyClass myObject;

	std::cout << "Size of MyClass: " << sizeof(MyClass) << std::endl;
	//entry의 크기
	std::cout << "Size of entry: " << sizeof(myObject.entry) << std::endl;
	//bigData의 크기
	std::cout << "Size of bigData: " << sizeof(myObject.bigData) << std::endl;
	std::cout << "Address of entry: " << &myObject.entry << std::endl;
	std::cout << "Address of bigData: " << &myObject.bigData << std::endl;

	// 16바이트 및 30바이트 정렬 확인
	std::cout << "Address of entry is " << ((reinterpret_cast<uintptr_t>(&myObject.entry) % 16 == 0) ? "aligned to 16 bytes." : "NOT aligned to 16 bytes.") << std::endl;
	std::cout << "Address of bigData is " << ((reinterpret_cast<uintptr_t>(&myObject.bigData) % 32 == 0) ? "aligned to 32 bytes." : "NOT aligned to 32 bytes.") << std::endl;

	//내 pc의 page크기를 알아보기 위한 코드를 실행
		/*//SYSTEM_INFO si;
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	// 페이지 크기 출력
	std::cout << "Page size: " << si.dwPageSize << " bytes" << std::endl;*/

	/*int n = 10;

	fnc(move(n));

	fnc("hwan");*/

	//fnc(1.123);
	/*int&& a = 1;
	print(forward<int>(a));*/


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
