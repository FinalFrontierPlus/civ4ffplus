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

// TODO: add more information to init() and reset() ?
// Slash: figure out how init and reset (and uninit, etc.) actually work...

void CvPlanet::init(int iX, int iY, int iPlanetType, int iPlanetSize, int iOrbitRing, bool bMoon, bool bRings)
{
	// Init saved data
	reset(iX, iY, iPlanetType, iPlanetSize, iOrbitRing, bMoon, bRings, true);

	// Init non-saved data

	// Init other game data

	// Initialize this to null.
	m_paiBuildings = NULL;
	m_paiBuildingProduction = NULL;
}

void CvPlanet::reset(int iX, int iY, int iPlanetType, int iPlanetSize, int iOrbitRing, bool bMoon, bool bRings, bool bConstructorCall)
{
	int iI;

	uninit();

	m_iX = iX;
	m_iY = iY;

	m_iPlanetType = iPlanetType;
	m_iPlanetSize = iPlanetSize;
	m_iOrbitRing = iOrbitRing;

	m_bMoon = bMoon;
	m_bRings = bRings;

	// Stole this from CvCity.cpp.
	if (!bConstructorCall)
	{
		m_paiBuildings = new int[GC.getNumBuildingInfos()];
		for (iI = 0; iI < GC.getNumBuildingInfos(); iI++)
		{
			//m_ppBuildings[iI] = NULL;
			m_paiBuildingProduction[iI] = 0;
			m_paiBuildings[iI] = 0;
		}
	}
}

void CvPlanet::uninit()
{
	// Destruct the arrays.
	SAFE_DELETE_ARRAY(m_paiBuildings);
	SAFE_DELETE_ARRAY(m_paiBuildingProduction);
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
	pStream->Write(m_iPopulation);

	pStream->Write(m_eBonusType);

	pStream->Write(m_bMoon);
	pStream->Write(m_bRings);
	pStream->Write(m_bDisabled);

	pStream->Write(GC.getNumBuildingInfos(), m_paiBuildings);
	pStream->Write(GC.getNumBuildingInfos(), m_paiBuildingProduction);
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
	pStream->Read(&m_iPopulation);

	pStream->Read(&m_eBonusType);

	pStream->Read(&m_bMoon);
	pStream->Read(&m_bRings);
	pStream->Read(&m_bDisabled);

	pStream->Read(GC.getNumBuildingInfos(), m_paiBuildings);
	pStream->Read(GC.getNumBuildingInfos(), m_paiBuildingProduction);
}

// Define all the basic getters.
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

int CvPlanet::getPopulation()
{
	return m_iPopulation;
}

int CvPlanet::getOrbitRing()
{
	return m_iOrbitRing;
}

BonusTypes CvPlanet::getBonusType()
{
	return (BonusTypes)m_eBonusType;
}

bool CvPlanet::isMoon()
{
	return m_bMoon;
}

bool CvPlanet::isRings()
{
	return m_bRings;
}

bool CvPlanet::isDisabled()
{
	return m_bDisabled;
}

bool CvPlanet::isBonus()
{
	if (m_eBonusType != NO_BONUS)
	{
		return true;
	}
	return false;
}

bool CvPlanet::isHasBonus(BonusTypes eBonusType)
{
	if (m_eBonusType == eBonusType)
	{
		return true;
	}
	return false;
}

// And setters (and changers).
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

void CvPlanet::setPopulation(int iValue)
{
	m_iPopulation = iValue;
}

void CvPlanet::setBonusType(BonusTypes eNewBonus)
{
	m_eBonusType = eNewBonus;
}

void CvPlanet::changePopulation(int iChange)
{
	m_iPopulation += iChange;
}

void CvPlanet::setMoon(bool bMoon)
{
	m_bMoon = bMoon;
}

void CvPlanet::setRings(bool bRings)
{
	m_bRings = bRings;
}

void CvPlanet::setDisabled(bool bDisabled)
{
	m_bDisabled = bDisabled;
}

// Check if a planet is within cultural range.
bool CvPlanet::isPlanetWithinCulturalRange()
{
	CvPlot* pPlot;
	CvCity* pCity;

	pPlot = GC.getMap().plot(getX(), getY());
	if (pPlot->isCity())
	{
		pCity = pPlot->getPlotCity();
		if (getOrbitRing() >= PLANET_RANGE_3)
		{
			if (pCity->getCultureLevel() < 3)
				return false;
		}
		else if (getOrbitRing() >= PLANET_RANGE_2) {
			if (pCity->getCultureLevel() < 2)
				return false;
		}
	}

	return true;
}

// Return the cultural range of a planet based on orbit rings.
// Defines defined in CvPlanet.h for now.
int CvPlanet::getPlanetCulturalRange()
{
	CvPlot* pPlot;

	pPlot = GC.getMap().plot(getX(), getY());
	if (pPlot->isCity())
	{
		if (getOrbitRing() >= PLANET_RANGE_3)
			return 2;
		if (getOrbitRing() >= PLANET_RANGE_2)
			return 1;
	}

	return 0;
}

