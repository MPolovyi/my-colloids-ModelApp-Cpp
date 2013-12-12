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

	template<class A>
	auto Abs(vector<A> _a) -> decltype(_a[0])
	{
		decltype(_a[0]) mod;

		for (int i; i<_a.size(); i++)
		{
			mod+= _a[i]*_a[i];
		}
		return std::pow(mod,0.5);
	}

	template<class A>
	auto Sum(vector<A> _a) -> decltype(_a[0])
	{
		decltype(_a[0]) mod;

		for (int i; i<_a.size(); i++)
		{
			mod+= _a[i];
		}
		return mod;
	}
}