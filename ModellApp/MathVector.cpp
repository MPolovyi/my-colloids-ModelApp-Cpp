#include "stdafx.h"
#include "MathVector.h"

namespace NMath{
	template<class T>
	CMathVector<T>::CMathVector(vector<T>& _coords)
	{
		m_Coords = _coords;
	}

	template<class T>
	CMathVector<T>::~CMathVector(void)
	{
	}

	template<class A, class B>
	auto  DotProduct(CMathVector<A> _a, CMathVector<B> _b) -> decltype(_a.m_Coords[0]*_b->m_Coords[0])
	{
		decltype(_a.m_Coord[0]*_b->m_Coord[0]) DotProduct;

		for (int i=0; i<_a.size(); i++)
		{
			DotProduct += _a.m_Coords[i] * _b.m_Coords[i];
		}

		return DotProduct;
	}
}