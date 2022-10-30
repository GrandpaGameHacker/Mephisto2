#pragma once
#include <memory>
#include <Core/MephistoAssert.h>

class IObject
{
public:
	IObject() = default;
	virtual ~IObject() { OnDestroy(); };
	virtual void Tick(float DeltaTime) {};
	virtual void OnBeginPlay(){};
	virtual void OnEndPlay() {};
	virtual void OnDestroy() {};
	virtual void Destroy() { MEPH_ASSERT(false); }
};