#include "stdafx.h"
#include "Lattice.h"
#include "World.h"

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
		for (int i = 0; i < NEIGBOUR_GRID_COUNT; i++)
		{
			tmp[i] = m_macroDensity * tmp[i];
		}

		m_microDensity = vector<double>(tmp,tmp+sizeof(tmp)/sizeof(tmp[0]));
		return &m_microDensity[0];
	}
	else
	{
		double  tmp[] = {1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0};
		for (int i = 0; i < NEIGBOUR_GRID_COUNT; i++)
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
	if (m_flags & IS_BOUNDARY & !IS_TRANSITION)
	{
		Velocity[0] = 0;
		Velocity[1] = 0;
	}
	for (int i = 0; i < NEIGBOUR_GRID_COUNT; i++)
	{
		// omega_i * rho * (1 + 3(e_i,u) + 9*(e_i,u)^2 / 2 - 3*u^2/2), где (e_i,u) - скал€рное произведение
		tmp[i] = m_weights[i]*GetMacroDensity()*
			(1 + 3*(NMath::DotProduct(m_Directions[i],Velocity) +
			9*(std::pow(NMath::DotProduct(m_Directions[i],Velocity), 2))/2 - 3*(NMath::DotProduct(Velocity,Velocity))/2));
	}
	m_microEqDensity = vector<double>(tmp, tmp+sizeof(tmp)/sizeof(tmp[0]));
	delete [] tmp;
	return &m_microEqDensity[0];
}

vector<double>  CLattice::MacroVelocity()
{
	double a[] = {0,0};
	vector<double> velocity = vector<double>(a,a+2);

	double *tmp1 = new double[NEIGBOUR_GRID_COUNT];

	for (int i = 1; i < NEIGBOUR_GRID_COUNT; i++)
	{
		tmp1[i] = (1/GetMacroDensity())*m_microDensity[i]*m_Directions[i][0];
		velocity[0]+=tmp1[i];
	}

	
	for (int i = 1; i < NEIGBOUR_GRID_COUNT; i++)
	{
		tmp1[i] = (1/GetMacroDensity())*m_microDensity[i]*m_Directions[i][1];
		velocity[1]+=tmp1[i];
	}

	delete [] tmp1;
	return velocity;
}



void CLattice::Shrink()
{
	m_Directions.shrink_to_fit();
	m_Neighbours.shrink_to_fit();
}