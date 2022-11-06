#pragma once
#include "Graphics/RenderQueue.h";
#include "Threadpool/ThreadPool.h"
class IApplication
{
public:
	IApplication();
	virtual ~IApplication();
	static RenderQueue Renderer;
	static ThreadPool TaskPool;
};