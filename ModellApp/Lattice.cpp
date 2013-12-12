#include "stdafx.h"
#include "Lattice.h"


CLattice::CLattice(void)
{
}

CLattice::CLattice(POINT aPoint)
{
	m_Coord = aPoint;
}

CLattice::CLattice(double _x, double _y, DWORD _flag)
{
	m_Directions.reserve(NEIGBOUR_GRID_COUNT);
	m_Neighbours.reserve(NEIGBOUR_GRID_COUNT);

	for (int i=0;i<9;i++)
	{
		vector<int> row;
		for (int j=0;j<2;j++)
		{
			//row.push_back(Coord[i][j]);
		}
		//m_Coordinates.push_back(row);
	}

	m_flags = _flag;
	m_Coord.x = _x;
	m_Coord.y = _y;
}

CLattice::~CLattice(void)
{
}

void CLattice::Draw(CDC* pDC, int _scale_x, int _scale_y)
{
	// Create a pen for this object and initialize it
	CPen aPen;
	CreatePen(aPen);

	CPen* pOldPen = pDC->SelectObject(&aPen);  // Select the pen

	// Select a null brush
	CBrush* pOldBrush = dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));
	
	// Now draw the circle
	pDC->Ellipse(_scale_x*m_Coord.x-m_radius, _scale_y*m_Coord.y+m_radius,
				_scale_x*m_Coord.x+m_radius, _scale_y*m_Coord.y-m_radius);

	pDC->SelectObject(pOldPen);                // Restore the old pen
	pDC->SelectObject(pOldBrush);              // Restore the old brush
}

void CLattice::AddToNeighbours(CLattice &_lattice,int dx, int dy, int nghb)
{
	m_Neighbours.push_back(&_lattice);

	int arr[] = {dx,dy};
	vector<int> vect(arr,arr+2);

	m_Directions.push_back(vect);
}


int CLattice::Speed()
{
	//TODO: check whether MacV implemented correctly, or consider adding of own vector class

	double spd = NMath::Abs(MacroVelocity());
	return (int) (40 * spd/NMath::Abs(m_outerForce));
}

double CLattice::GetMacroDensity()
{
	return  NMath::Sum(m_microDensity);
}

//TODO: Create some method for transversion of coordinates from pixels into meters and vise versa. Consider coords in CLattice as meters.

double* CLattice:: f()
{
	return &m_microDensity[0];
}

double* CLattice:: fEq()
{
	return &m_microEqDensity[0];
}

double* CLattice::Force()
{
	double *tmp = new double[NEIGBOUR_GRID_COUNT];

	for (int i = 0; i < NEIGBOUR_GRID_COUNT; i++)
	{
		if (m_Coord.y<500)
		{
			double someRndY = rand() % 1;
			vector<double> NewForce;
			
			NewForce.push_back(m_outerForce[0]);
			NewForce.push_back(m_outerForce[1]);

			tmp[i] = m_weights[i] * (NMath::DotProduct(NewForce , m_Directions[i]));
		}
		else
		{
			vector<double> NewForce;
			NewForce.push_back(m_outerForce[0]);
			NewForce.push_back(m_outerForce[1]);

			tmp[i] = m_weights[i] * (NMath::DotProduct(NewForce , m_Directions[i]));
		}

	}
	m_Force = tmp;
	delete tmp;
	return m_Force;
}


void CLattice::Shrink()
{
	m_Directions.shrink_to_fit();
	m_Neighbours.shrink_to_fit();
}