// CvSolarSystem.cpp
// The first step to handling planets, solar systems, etc. in C++!
// How hard can it be?

#include "CvGameCoreDLL.h"
#include "CvGlobals.h"
#include "CvGameCoreUtils.h"

#include "CvDLLInterfaceIFaceBase.h"

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
	m_eSunType = 0;
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

	pStream->Write(m_eSunType);
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

void CvSolarSystem::setSelectedPlanet(int iID)
{
	CvDLLInterfaceIFaceBase* pInterface = gDLL->getInterfaceIFace();

	// ...this almost certainly needs to be error-checked...
	m_iSelectedPlanet = iID;

	// Use the interface iface to do the isCityScreenUp stuff
	if (pInterface->isCityScreenUp())
	{
		pInterface->setDirty(CitizenButtons_DIRTY_BIT, true);
	}
}

void CvSolarSystem::setBuildingPlanetRing(int iID)
{
	CvDLLInterfaceIFaceBase* pInterface = gDLL->getInterfaceIFace();	
	int iOldBuildingPlanetRing = getBuildingPlanetRing();
	int iNumBuildingTypes = GC.getNumBuildingInfos();
	int iBuilding;
	CvCity* pCity = getCity();
	CvPlanet* pPlanet;

	m_iBuildingPlanetRing = iID;
	// In this case, we are doing map setup so none of the following stuff is relevant
	if (pCity == NULL || iOldBuildingPlanetRing == -1)
	{
		return;
	}

	// Save and load planet building production
	pPlanet = getPlanet(iOldBuildingPlanetRing);
	for (iBuilding = 0; iBuilding < iNumBuildingTypes; iBuilding++)
	{
		pPlanet->setBuildingProduction((BuildingTypes)iBuilding, pCity->getBuildingProduction((BuildingTypes)iBuilding));
	}

	pPlanet = getPlanet(m_iBuildingPlanetRing);
	for (iBuilding = 0; iBuilding < iNumBuildingTypes; iBuilding++)
	{
		pCity->setBuildingProduction((BuildingTypes)iBuilding, pPlanet->getBuildingProduction((BuildingTypes)iBuilding));
	}


	// Use the interface iface to do the isCityScreenUp stuff
	if (pInterface->isCityScreenUp())
	{
		pInterface->setDirty(CitizenButtons_DIRTY_BIT, true);
		pInterface->setDirty(InfoPane_DIRTY_BIT, true);
	}
}

void CvSolarSystem::addPlanet(PlanetTypes ePlanetType, int iPlanetSize, int iOrbitRing, bool bMoon, bool bRings)
{
	bool bLoading = false;
	CvPlanet* pPlanet;

	if (ePlanetType != NO_PLANET)
	{
		bLoading = true;
	}

	if (getNumPlanets() < MAX_PLANETS || bLoading)
	{
		pPlanet = &m_apPlanets[iOrbitRing - 1];
		// This may introduce an error of some sort. What if the planet isn't empty...?
		// Turns out the Python doesn't even try to handle this. Checking if type != NO_PLANET should be sufficient
		// I feel like this should not be a void function and should return an error code, since it has failure conditions...
		if (pPlanet != NULL && pPlanet->getPlanetType() == NO_PLANET)
		{
			pPlanet->init(getX(), getY(), ePlanetType, iPlanetSize, iOrbitRing, bMoon, bRings);
			if (getBuildingPlanetRing() == -1)
				setBuildingPlanetRing(iOrbitRing);
			if (bLoading)
				m_iNumPlanets += 1;
		}
	}
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

	for (iPlanet = 0; iPlanet < MAX_PLANETS; iPlanet++)
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
	for (iPlanetLoop = 0; iPlanetLoop < MAX_PLANETS; iPlanetLoop++)
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

void CvSolarSystem::updateDisplay()
{
	// We need to add other planet XML here first. 
}