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
	m_pabBuildings = NULL;
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
		m_pabBuildings = new int[GC.getNumBuildingInfos()];
		for (iI = 0; iI < GC.getNumBuildingInfos(); iI++)
		{
			//m_ppBuildings[iI] = NULL;
			m_paiBuildingProduction[iI] = 0;
			m_pabBuildings[iI] = false;
		}
	}
}

void CvPlanet::uninit()
{
	// Destruct the arrays.
	SAFE_DELETE_ARRAY(m_pabBuildings);
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

	pStream->Write(GC.getNumBuildingInfos(), m_pabBuildings);
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

	pStream->Read(GC.getNumBuildingInfos(), m_pabBuildings);
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

bool CvPlanet::isHasBuilding(BuildingTypes eBuildingType)
{
	if (eBuildingType != NO_BUILDING)
	{
		return m_pabBuildings[eBuildingType];
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

void CvPlanet::setHasBuilding(BuildingTypes eBuildingType, bool bValue)
{
	if (eBuildingType != NO_BUILDING)
	{
		m_pabBuildings[eBuildingType] = bValue;
	}
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

// Returns the current maximum population limit for the planet.
int CvPlanet::getPopulationLimit(PlayerTypes eOwner)
{
	int iMaxPop;
	int iBuildingLoop;
	int iCivicOptionLoop;
	int iCivicLoop;
	int iPopCapIncrease;

	if (isDisabled())
	{
		return 0;
	}

	if (!isPlanetWithinCulturalRange())
	{
		return 0;
	}

	// Hardcoding this for now. Fix with enums / arrays / defines / ... / ...
	iMaxPop = getPlanetSize() + 1;

	// Population cap increases from buildings
	for (iBuildingLoop = 0; iBuildingLoop < GC.getNumBuildingInfos(); iBuildingLoop++)
	{
		if (isHasBuilding((BuildingTypes)iBuildingLoop))
		{
			iPopCapIncrease = GC.getBuildingInfo((BuildingTypes)iBuildingLoop).getPlanetPopCapIncrease();
			iMaxPop += iPopCapIncrease;
		}
	}

	// Population cap increases from a player's civics.
	if (eOwner != NO_PLAYER)
	{
		CvPlayer& pPlayer = GET_PLAYER(eOwner);
		for (iCivicOptionLoop = 0; iCivicOptionLoop < GC.getNumCivicOptionInfos(); iCivicOptionLoop++)
		{
			for (iCivicLoop = 0; iCivicLoop < GC.getNumCivicInfos(); iCivicLoop++)
			{
				if (pPlayer.getCivics((CivicOptionTypes)iCivicOptionLoop) == (CivicTypes)iCivicLoop)
				{
					iPopCapIncrease = GC.getCivicInfo((CivicTypes)iCivicLoop).getPlanetPopCapIncrease();
					iMaxPop += iPopCapIncrease;
				}
			}
		}

	}

	return iMaxPop;
}

// Get the total and base yields of the planet.
int CvPlanet::getTotalYield(PlayerTypes eOwner, YieldTypes eYield)
{
	return getBaseYield(eYield) + getExtraYield(eOwner, eYield);
}

// Get the base yield; this is a table sitting in a Python file, sadly.
int CvPlanet::getBaseYield(YieldTypes eYield)
{
	// ???
	// We avoided the hardcoding issue in getPopulationLimit() barely, but can't do it for getBaseYield.
	// We need to move the yield data into the DLL somehow...
	// ...or add CvPlanetInfo (CIV4PlanetInfos.xml).
	// I think we need to do that.

	return 0;
}

// Get the extra yield using civics and buildings.
int CvPlanet::getExtraYield(PlayerTypes eOwner, YieldTypes eYield)
{
	int iExtraYield = 0;
	int iYieldChange;
	int iBuildingLoop;
	int iTraitLoop;
	int iCivicOption;
	int iCivic;

	CvPlayer& pPlayer = GET_PLAYER((PlayerTypes)eOwner);

	// Compute yields from buildings.
	for (iBuildingLoop = 0; iBuildingLoop < GC.getNumBuildingInfos(); iBuildingLoop++)
	{
		if (isHasBuilding((BuildingTypes)iBuildingLoop))
		{
			iYieldChange = GC.getBuildingInfo((BuildingTypes)iBuildingLoop).getPlanetYieldChanges(eYield);
			// Yields from buildings that require a trait
			for (iTraitLoop = 0; iTraitLoop < GC.getNumTraitInfos(); iTraitLoop++)
			{
				if (pPlayer.hasTrait((TraitTypes)iTraitLoop))
				{
					iYieldChange += GC.getBuildingInfo((BuildingTypes)iBuildingLoop).getTraitPlanetYieldChange(iTraitLoop, eYield);
				}
			}
			iExtraYield += iYieldChange;
		}
	}

	// Compute yields from civics.
	for (iCivicOption = 0; iCivicOption < GC.getNumCivicOptionInfos(); iCivicOption++)
	{
		for (iCivic = 0; iCivic < GC.getNumCivicInfos(); iCivic++)
		{
			if (pPlayer.getCivics((CivicOptionTypes)iCivicOption) == (CivicTypes)iCivic)
			{
				iYieldChange = GC.getCivicInfo((CivicTypes)iCivic).getPlanetYieldChanges(eYield);
				iExtraYield += iYieldChange;
			}
		}
	}

	// CP - add golden age effect, thanks for the idea of doing it here go to TC01
	if (pPlayer.isGoldenAge())
	{
		if ((getBaseYield(eYield) + iExtraYield) >= GC.getYieldInfo(eYield).getGoldenAgeYieldThreshold())
		{
			iExtraYield += GC.getYieldInfo(eYield).getGoldenAgeYield();
		}
	}

	return iExtraYield;
}