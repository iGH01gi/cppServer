#include "pch.h"
#include "CoreGlobal.h"
#include "../Thread/ThreadManager.h"

ThreadManager* GThreadManager = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GThreadManager = new ThreadManager();
	}

	~CoreGlobal()
	{
		delete GThreadManager;
	}
} GCoreGlobal;

