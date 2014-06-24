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
	reset(iX, iY, true);

	// Init non-saved data

	// Init other game data
	m_apPlanets = NULL;
}

void CvSolarSystem::reset(int iX, int iY, bool bConstructorCall)
{
	int i;

	uninit();

	m_iX = iX;
	m_iY = iY;

	m_iNumPlanets = 0;
	m_iSunType = 0;
	m_iSelectedPlanet = 0;
	m_iBuildingPlanetRing = 0;

	m_bNeedsUpdate = false;

	if (!bConstructorCall)
	{
		for (i = 0; i < MAX_PLANETS; i++)
		{
			m_apPlanets[i] = CvPlanet();
		}
	}
}

void CvSolarSystem::uninit()
{
	SAFE_DELETE_ARRAY(m_apPlanets);
}

void CvSolarSystem::write(FDataStreamBase* pStream)
{
	int i;

	uint uiFlag=0;
	pStream->Write(uiFlag);		// flag for expansion

	pStream->Write(m_iX);
	pStream->Write(m_iY);

	pStream->Write(m_iSunType);
	pStream->Write(m_iSelectedPlanet);
	pStream->Write(m_iBuildingPlanetRing);
	pStream->Write(m_bNeedsUpdate);

	// This code will almost certainly not do the right thing. (nor will read code).
	// Fix later!
	for (i = 0; i < MAX_PLANETS; i++)
	{
		m_apPlanets[i].write(pStream);
	}
}

void CvSolarSystem::read(FDataStreamBase* pStream)
{
	int i;

	uint uiFlag=0;
	pStream->Read(&uiFlag);	// flags for expansion

	pStream->Read(&m_iX);
	pStream->Read(&m_iY);

	pStream->Read(&m_eSunType);
	pStream->Read(&m_iSelectedPlanet);
	pStream->Read(&m_iBuildingPlanetRing);
	pStream->Read(&m_bNeedsUpdate);

	for (i = 0; i < MAX_PLANETS; i++)
	{
		m_apPlanets[i].read(pStream);
	}
}

int CvSolarSystem::getNumPlanets()
{
	return m_iNumPlanets;
}

SunTypes CvSolarSystem::getSunType()
{
	return (SunTypes)m_eSunType;
}

void CvSolarSystem::setSunType(SunTypes eNewValue)
{
	m_eSunType = eNewValue;
}

int CvSolarSystem::getSelectedPlanet()
{
	return m_iSelectedPlanet;	
}

int CvSolarSystem::getBuildingPlanetRing()
{
	return m_iBuildingPlanetRing;
}

int CvSolarSystem::getX()
{
	return m_iX;
}

int CvSolarSystem::getY()
{
	return m_iY;
}

CvPlanet* CvSolarSystem::getPlanetByIndex(int iPlanet)
{
	if (iPlanet > MAX_PLANETS || iPlanet < 0)
	{
		return NULL;
	}
	return &m_apPlanets[iPlanet];
}

CvPlanet* CvSolarSystem::getPlanet(int iRingID)
{
	// The Python implementation doesn't guarantee index = ring ID - 1.
	// We do, because C++ (yay)
	CvPlanet* pPlanet = getPlanetByIndex(iRingID - 1);
	if (pPlanet == NULL)
	{
		// Throw an error message? But I don't understand how to do FAssertMsg, so.
	}
	return pPlanet;
}

int CvSolarSystem::getOwner()
{
	CvCity* pCity;

	pCity = getCity();
	if (pCity != NULL)
	{
		return pCity->getOwner();
	}
	return NO_PLAYER;
}

CvCity* CvSolarSystem::getCity()
{
	CvCity* pCity;
	CvPlot* pPlot;

	pPlot = GC.getMap().plot(getX(), getY());
	if (pPlot->isCity())
	{
		pCity = pPlot->getPlotCity();
	}
	return pCity;
}

int CvSolarSystem::getPopulation()
{
	int iPopulation = 0;
	int iPlanet;
	CvPlanet* pPlanet;

	for (iPlanet = 0; iPlanet < MAX_PLANETS; i++)
	{
		pPlanet = getPlanetByIndex(iPlanet);
		if (pPlanet != NULL)
		{
			iPopulation += pPlanet->getPopulation();
		}
	}

	return iPopulation;
}

int CvSolarSystem::getPopulationLimit(bool bFactorHappiness)
{
	int iPlanetPopLimit = 0;
	int iHappyPopLimit = 0;
	int iPlanetLoop;
	CvCity* pCity = getCity();
	CvPlanet* pPlanet;

	// Loop through all planets and get the sum of their pop limits
	for (iPlanetLoop = 0; iPlanetLoop < MAX_PLANETS; i++)
	{
		pPlanet = getPlanetByIndex(iPlanetLoop);
		if (pPlanet != NULL)
		{
			iPlanetPopLimit += pPlanet->getPopulationLimit((PlayerTypes)getOwner());
		}
	}

	if (pCity != NULL)
	{
		iHappyPopLimit = pCity->getPopulation();
		if (bFactorHappiness)
		{
			iHappyPopLimit -= pCity->angryPopulation(0);
		} else {
			iHappyPopLimit = iPlanetPopLimit;
		}
	}

	return std::min(iPlanetPopLimit, iHappyPopLimit);
}

bool CvSolarSystem::isNeedsUpdate()
{
	return m_bNeedsUpdate;
}

void CvSolarSystem::setNeedsUpdate(bool bValue)
{
	m_bNeedsUpdate = bValue;
}