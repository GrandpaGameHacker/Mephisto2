#pragma once

namespace ME::Utility
{
	class DelegateBase
	{
		DelegateBase() {};
		virtual ~DelegateBase() {};
		virtual void operator()() = 0;
	};
}

