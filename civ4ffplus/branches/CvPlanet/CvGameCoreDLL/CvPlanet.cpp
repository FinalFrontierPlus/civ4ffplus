// CvSolarSystem.cpp
// The second step to handling planets, solar systems, etc. in C++!
// How hard can it be?

#include "CvGameCoreDLL.h"
#include "CvGlobals.h"
#include "CvGameCoreUtils.h"

#include "CvPlanet.h"

CvPlanet::CvPlanet()
{
	reset();
}


CvPlanet::~CvPlanet()
{
	uninit();
}

void CvPlanet::init(int iX, int iY, int iPlanetType, int iPlanetSize, int iOrbitRing, bool bMoon, bool bRings)
{
	// Init saved data
	reset(iX, iY, iPlanetType, iPlanetSize, iOrbitRing, bMoon, bRings);

	// Init non-saved data

	// Init other game data
}

void CvPlanet::reset(int iX, int iY, int iPlanetType, int iPlanetSize, int iOrbitRing, bool bMoon, bool bRings)
{
	uninit();

	m_iX = iX;
	m_iY = iY;

	m_iPlanetType = iPlanetType;
	m_iPlanetSize = iPlanetSize;
	m_iOrbitRing = iOrbitRing;

	m_bMoon = bMoon;
	m_bRings = bRings;
}

void CvPlanet::uninit()
{
	// ???
}

void CvPlanet::write(FDataStreamBase* pStream)
{
	uint uiFlag=0;
	pStream->Write(uiFlag);		// flag for expansion

	pStream->Write(m_iX);
	pStream->Write(m_iY);

	pStream->Write(m_iPlanetType);
	pStream->Write(m_iPlanetSize);
	pStream->Write(m_iOrbitRing);

	pStream->Write(m_bMoon);
	pStream->Write(m_bRings);
}

void CvPlanet::read(FDataStreamBase* pStream)
{
	uint uiFlag=0;
	pStream->Read(&uiFlag);	// flags for expansion

	pStream->Read(&m_iX);
	pStream->Read(&m_iY);

	pStream->Read(&m_iPlanetType);
	pStream->Read(&m_iPlanetSize);
	pStream->Read(&m_iOrbitRing);

	pStream->Read(&m_bMoon);
	pStream->Read(&m_bRings);
}

// Define all the getters and setters.
int CvPlanet::getX()
{
	return m_iX;
}

int CvPlanet::getY()
{
	return m_iY;
}

int CvPlanet::getPlanetType()
{
	return m_iPlanetType;
}

int CvPlanet::getPlanetSize()
{
	return m_iPlanetSize;
}

int CvPlanet::getOrbitRing()
{
	return m_iOrbitRing;
}

bool CvPlanet::isMoon()
{
	return m_bMoon;
}
bool CvPlanet::isRings()
{
	return m_bRings;
}

void CvPlanet::setPlanetType(int iPlanetType)
{
	m_iPlanetType = iPlanetType;
}

void CvPlanet::setPlanetSize(int iPlanetSize)
{
	m_iPlanetSize = iPlanetSize;
}

void CvPlanet::setOrbitRing(int iOrbitRing)
{
	m_iOrbitRing = iOrbitRing;
}

void CvPlanet::setMoon(bool bMoon)
{
	m_bMoon = bMoon;
}

void CvPlanet::setRings(bool bRings)
{
	m_bRings = bRings;
}