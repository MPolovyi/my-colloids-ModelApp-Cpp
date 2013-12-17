#include "stdafx.h"
#include "Lattice.h"
#include "World.h"

#define WEIGHTS {4/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/36.0, 1/36.0, 1/36.0, 1/36.0}
#define WEIGHTS_BOUNDARY {4/9.0, 1/9.0, 1/9.0, 1/9.0, 1/36.0, 1/36.0}
#define WEIGHTS_CORNER {4/9.0, 1/9.0, 1/9.0, 1/36.0}

CLattice::CLattice(void)
{
}

CLattice::CLattice(POINT aPoint)
{
	m_Coord = aPoint;
}

CLattice::CLattice(double _x, double _y, DWORD _flag, CDC* _cdc)
{
	m_cdc = _cdc;
	m_Directions.reserve(NEIGHBOUR_GRID_COUNT);
	m_Neighbours.reserve(NEIGHBOUR_GRID_COUNT);

	m_flags = _flag;
	m_Coord.x = _x + 10;
	m_Coord.y = _y + 10;


	double OutForce[] = {0,0};
	m_outerForce = vector<double>(OutForce, OutForce+2);
}

void CLattice::Init()
{
	Shrink();
	
	Weights();
	Force();

	MacroDensity(m_PhysCoord.x, m_PhysCoord.y);

	MicroDensity();
	MicroEqDensity();

	m_microDensityAfterTime = m_microDensity;
	Draw(m_cdc,0);
}

CLattice::~CLattice(void)
{
}

void CLattice::StreamAndCollide()
{
	for (int i = 0; i < m_NeighCount; i++)
	{
		auto ForceVar = m_Force[i];
		double collision = (m_microDensity[i]  - m_microEqDensity[i] + ForceVar)/5;
		double NewFi = m_microDensity[i] - collision;
		m_Neighbours[i].first->NewF(NewFi, m_Neighbours[i].second);
	}
}


void CLattice::AddToNeighbours(CLattice* _lattice, int dx, int dy, int nghb)
{
	pair<CLattice*,int> tmp(_lattice, GetIndexOfTransition(dx, dy));
	m_Neighbours.push_back(tmp);

	int arr[] = {dx,dy};
	vector<int> vect(arr,arr+2);

	m_Directions.push_back(vect);
}

void CLattice::MacroDensity(int x, int y)
{
	m_macroDensity = 1;
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

double* CLattice::Force()
{
	double *tmp = new double[m_NeighCount];

	for (int i = 0; i < m_NeighCount; i++)
	{
		if (m_Coord.y<500)
		{
			double someRndY = rand() % 1;
			vector<double> NewForce;
			
			NewForce.push_back(m_outerForce[0]);
			NewForce.push_back(m_outerForce[1]);

			
			tmp[i] = m_weights[i] * (NMath::DotProduct(NewForce , m_Directions[i]));
			auto tempdebug = tmp[i];
		}
		else
		{
			vector<double> NewForce;
			NewForce.push_back(m_outerForce[0]);
			NewForce.push_back(m_outerForce[1]);

			tmp[i] = m_weights[i] * (NMath::DotProduct(NewForce , m_Directions[i]));
		}

	}
	m_Force = vector<double>(tmp, tmp+m_NeighCount);
	delete [] tmp;
	return &m_Force[0];
}

void CLattice::NewF( double nF,int i )
{
	m_microDensityAfterTime[i] = nF;
}

void CLattice::UpdateDensity()
{
	m_microDensity = m_microDensityAfterTime;
}

double* CLattice::MicroDensity()
{
	
	if (m_Coord.x>200 && m_Coord.x<220 && m_Coord.y>200 && m_Coord.y<800)
	{
		//double[] tmp = {1/54.0, 20/54.0, 26/54.0, 1/54.0, 1/54.0, 1/54.0, 1/54.0, 1/54.0, 1/54.0};
		double  tmp[] = {1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0};
		for (int i = 0; i < m_NeighCount; i++)
		{
			tmp[i] = m_macroDensity * tmp[i];
		}

		m_microDensity = vector<double>(tmp,tmp+sizeof(tmp)/sizeof(tmp[0]));
		return &m_microDensity[0];
	}
	else
	{
		double  tmp[] = {1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0};
		for (int i = 0; i < m_NeighCount; i++)
		{
			tmp[i] = m_macroDensity * tmp[i];
		}

		m_microDensity = vector<double>(tmp,tmp+sizeof(tmp)/sizeof(tmp[0]));
		return &m_microDensity[0];
	}
}

double* CLattice::MicroEqDensity()
{
	double *tmp = new double[m_Directions.size()];
	vector<double> Velocity = MacroVelocity();

	if (m_flags & IS_BOUNDARY & ~IS_TRANSITION)
	{
		Velocity[0] = 0;
		Velocity[1] = 0;
	}
	for (int i = 0; i < m_NeighCount; i++)
	{
		// omega_i * rho * (1 + 3(e_i,u) + 9*(e_i,u)^2 / 2 - 3*u^2/2), где (e_i,u) - скал€рное произведение
		tmp[i] = m_weights[i]*GetMacroDensity()*
			(1 + 3*(NMath::DotProduct(m_Directions[i],Velocity) +
			9*(std::pow(NMath::DotProduct(m_Directions[i],Velocity), 2))/2 - 3*(NMath::DotProduct(Velocity,Velocity))/2));
	}

	m_microEqDensity = vector<double>(tmp, tmp+m_Directions.size());
	delete [] tmp;
	return &m_microEqDensity[0];
}

vector<double> CLattice::MacroVelocity()
{
	double a[] = {0,0};
	vector<double> velocity = vector<double>(a,a+2);
	int length = m_Neighbours.size();
	double *tmp1 = new double[length];

	for (int i = 1; i < length; i++)
	{
		tmp1[i] = (1/GetMacroDensity())*m_microDensity[i]*m_Directions[i][0];
		velocity[0]+=tmp1[i];
	}

	
	for (int i = 1; i < length; i++)
	{
		tmp1[i] = (1/GetMacroDensity())*m_microDensity[i]*m_Directions[i][1];
		velocity[1]+=tmp1[i];
	}

	delete [] tmp1;
	return velocity;
}

double* CLattice::Weights()
{
	if (m_weights.size() > 0)
	{
		return &m_weights[0];
	}
		
	if (m_flags & IS_CORNER)
	{
		double tmp[] = WEIGHTS_CORNER;
		m_weights = vector<double>(tmp,tmp+sizeof(tmp)/sizeof(tmp[0]));
	}
	else if (m_flags & IS_TRANSITION)
	{
		double tmp[] = WEIGHTS;
		m_weights = vector<double>(tmp,tmp+sizeof(tmp)/sizeof(tmp[0]));
	}
	else if (m_flags & IS_BOUNDARY)
	{
		double tmp[] = WEIGHTS_BOUNDARY;
		m_weights = vector<double>(tmp,tmp+sizeof(tmp)/sizeof(tmp[0]));
	}
	else
	{
		double tmp[] = WEIGHTS;
		m_weights = vector<double>(tmp,tmp+sizeof(tmp)/sizeof(tmp[0]));
	}
	return &m_weights[0];
}


void CLattice::Draw(CDC* pDC, int _scale_velocity)
{
	// Create a pen for this object and initialize it
	CPen aPen;
	CreatePen(aPen);

	CPen* pOldPen = pDC->SelectObject(&aPen);  // Select the pen

	// Select a null brush
	CBrush* pOldBrush = dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));

	// Now draw the circle
	pDC->Ellipse(m_Coord.x-m_radius, m_Coord.y+m_radius,
		m_Coord.x+m_radius, m_Coord.y-m_radius);

	auto velocity = MacroVelocity();

	pDC->MoveTo(m_Coord.x, m_Coord.y);

	CPen BluePen(PS_SOLID, 2, RGB(0, 20, 200));
	CPen* pOldPen2 = pDC->SelectObject(&BluePen);
	pDC->LineTo(m_Coord.x + velocity[0] * _scale_velocity, m_Coord.y + velocity[1] * _scale_velocity);
	pDC->SelectObject(pOldPen2);

	//CPen GreenPen(PS_SOLID, 2, RGB(0, 200, 50));
	//CPen* pOldPen2 = pDC->SelectObject(&GreenPen);
	//for (int i=0; i<m_NeighCount; i++)
	//{
	//	pDC->MoveTo(m_Coord.x, m_Coord.y);
	//	auto f1 = m_Directions[i][0] * f()[i] * 50;
	//	auto f2 = m_Directions[i][1] * f()[i] * 50;
	//	pDC->LineTo(m_Coord.x + f1, m_Coord.y + f2);
	//}
	//pDC->SelectObject(pOldPen2);

	pDC->SelectObject(pOldPen);                // Restore the old pen
	pDC->SelectObject(pOldBrush);              // Restore the old brush
}

void CLattice::Shrink()
{
	m_Directions.shrink_to_fit();
	m_Neighbours.shrink_to_fit();
	m_NeighCount = m_Neighbours.size();
}


