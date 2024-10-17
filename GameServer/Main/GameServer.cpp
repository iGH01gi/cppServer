#include "pch.h"
#include <thread>
#include <iostream>


#include "Memory.h"
#include "ThreadManager.h"




class Knight 
{
public:
	int32 _hp = rand() % 1000;
};

int main()
{
	//오브젝트풀 사용 예시
	shared_ptr<Knight> sptr = ObjectPool<Knight>::MakeShared();
	//메모리풀 사용 예시
	shared_ptr<Knight> sptr2 = MakeShared<Knight>();

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([]()
			{
				while (true)
				{
					Knight* knight = inew<Knight>();

					cout << knight->_hp << endl;

					this_thread::sleep_for(10ms);

					idelete(knight);
				}
			});
	}

	GThreadManager->Join();
}