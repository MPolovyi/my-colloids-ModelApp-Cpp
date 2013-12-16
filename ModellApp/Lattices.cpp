#include "stdafx.h"
#include "Lattices.h"





#pragma region IndexOfNeigboursMicroDensity

int CLattice_Mid::GetIndexOfTransition(int dx, int dy)
{
	if( 0==dx && 0==dy)  {return 0;}
	if( 1==dx && 0==dy)  {return 1;}
	if( 0==dx && -1==dy) {return 2;}
	if(-1==dx && 0==dy)  {return 3;}
	if(0==dx && 1==dy)   {return 4;}
	if( 1==dx && -1==dy) {return 5;}
	if(-1==dx && -1==dy) {return 6;}
	if(-1==dx && 1==dy)  {return 7;}
	if( 1==dx && 1==dy)  {return 8;}
	else{return -1;}
}

int CLattice_Top::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)  {return 0;}
	if (1==dx && 0==dy)	 {return 1;}
	if (-1==dx && 0==dy) {return 3;}
	if (0==dx && 1==dy)  {return 4;}
	if (-1==dx && 1==dy) {return 6;}
	if (1==dx && 1==dy)  {return 8;}
	else{return -1;}
}

int CLattice_Right::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)   {return 0;}
	if (0==dx && -1==dy)  {return 2;}
	if (-1==dx && 0==dy)  {return 3;}
	if (0==dx && 1==dy)   {return 4;}
	if (-1==dx && -1==dy) {return 6;}
	if (-1==dx && 1==dy)  {return 7;}
	else{return -1;}
}

int CLattice_Left::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)  {return 0;}
	if (1==dx && 0==dy)	 {return 1;}
	if (0==dx && -1==dy) {return 2;}
	if (0==dx && 1==dy)  {return 4;}
	if (1==dx && -1==dy) {return 5;}
	if (1==dx && 1==dy)  {return 8;}
	else{return -1;}
}

int CLattice_Bottom::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)   {return 0;}
	if (1==dx && 0==dy)	  {return 1;}
	if (0==dx && -1==dy)  {return 2;}
	if (-1==dx && 0==dy)  {return 3;}
	if (1==dx && -1==dy)  {return 5;}
	if (-1==dx && -1==dy) {return 6;}
	else{return -1;}
}

int CLattice_Top_Left::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)  {return 0;}
	if (1==dx && 0==dy)  {return 1;}
	if (0==dx && 1==dy)  {return 4;}
	if (1==dx && 1==dy)  {return 8;}
	else{return -1;}
}

int CLattice_Top_Right::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)  {return 0;}
	if (-1==dx && 0==dy) {return 2;}
	if (0==dx && 1==dy)  {return 3;}
	if (-1==dx && 1==dy) {return 7;}
	else{return -1;}
}

int CLattice_Bottom_Left::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)  {return 0;}
	if (1==dx && 0==dy)  {return 1;}
	if (0==dx && -1==dy) {return 2;}
	if (1==dx && -1==dy) {return 5;}
	else{return -1;}
}

int CLattice_Bottom_Right::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)   {return 0;}
	if (0==dx && -1==dy)  {return 2;}
	if (-1==dx && 0==dy)  {return 3;}
	if (-1==dx && -1==dy) {return 6;}
	else{return -1;}
}
#pragma endregion IndexOfNeigboursMicroDensity