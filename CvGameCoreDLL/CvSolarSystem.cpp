// CvSolarSystem.cpp
// The first step to handling planets, solar systems, etc. in C++!
// How hard can it be?

#include "CvGameCoreDLL.h"
#include "CvGlobals.h"
#include "CvGameCoreUtils.h"

#include "CvPlanet.h"
#include "CvPlot.h"
#include "CvSolarSystem.h"

CvSolarSystem::CvSolarSystem()
{
	reset();
}


CvSolarSystem::~CvSolarSystem()
{
	uninit();
}

void CvSolarSystem::init(int iX, int iY)
{
	// Init saved data
	reset(iX, iY);

	// Init non-saved data

	// Init other game data
}

void CvSolarSystem::reset(int iX, int iY)
{
	uninit();

	m_iX = iX;
	m_iY = iY;

	m_iNumPlanets = 0;
	m_iSunType = 0;
	m_iSelectedPlanet = 0;
	m_iBuildingPlanetRing = 0;

	m_bNeedsUpdate = false;
}

void CvSolarSystem::uninit()
{
	// ???
}

void CvSolarSystem::write(FDataStreamBase* pStream)
{
	uint uiFlag=0;
	pStream->Write(uiFlag);		// flag for expansion

	pStream->Write(m_iX);
	pStream->Write(m_iY);

	pStream->Write(m_iSunType);
	pStream->Write(m_iSelectedPlanet);
	pStream->Write(m_iBuildingPlanetRing);
	pStream->Write(m_bNeedsUpdate);
}

void CvSolarSystem::read(FDataStreamBase* pStream)
{
	uint uiFlag=0;
	pStream->Read(&uiFlag);	// flags for expansion

	pStream->Read(&m_iX);
	pStream->Read(&m_iY);

	pStream->Read(&m_iSunType);
	pStream->Read(&m_iSelectedPlanet);
	pStream->Read(&m_iBuildingPlanetRing);
	pStream->Read(&m_bNeedsUpdate);
}

int CvSolarSystem::getNumPlanets()
{
	return m_iNumPlanets;
}

int CvSolarSystem::getSunType()
{
	return m_iSunType;
}

int CvSolarSystem::getSelectedPlanet()
{
	return m_iSelectedPlanet;	
}

int CvSolarSystem::getBuildingPlanetRing()
{
	return m_iBuildingPlanetRing;
}

bool CvSolarSystem::isNeedsUpdate()
{
	return m_bNeedsUpdate;
}

void CvSolarSystem::setNeedsUpdate(bool bValue)
{
	m_bNeedsUpdate = bValue;
}