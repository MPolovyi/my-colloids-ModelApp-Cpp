#pragma once
#include "stdafx.h"

namespace NMath
{
	template<class A, class B>
	auto DotProduct(vector<A> _a, vector<B> _b) -> decltype(_a[0] * _b[0])
	{
		decltype(_a[0]*_b[0]) DotProduct(0);

		auto length = (_a.size() > _b.size()) ? _a.size() : _b.size();

		for (int i=0; i<length; i++)
		{
			DotProduct += _a[i] * _b[i];
		}

		return DotProduct;
	}
}