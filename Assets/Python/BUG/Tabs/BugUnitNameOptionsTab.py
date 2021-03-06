## BugUnitNameOptionsTab
##
## Tab for the BUG Unit Name Options.
##
## Copyright (c) 2007-2008 The BUG Mod.
##
## Author: Ruff_Hi

import BugOptionsTab

class BugUnitNameOptionsTab(BugOptionsTab.BugOptionsTab):
	"BUG Unit Name Options Screen Tab"
	
	def __init__(self, screen):
		BugOptionsTab.BugOptionsTab.__init__(self, "UnitNaming", "Unit Naming")

	def create(self, screen):
		tab = self.createTab(screen)
		panel = self.createMainPanel(screen)
		column = self.addOneColumnLayout(screen, panel)
	
		left, center, right = self.addThreeColumnLayout(screen, column, "Options")
		
		self.addCheckbox(screen, left, "UnitNaming__Enabled")
		self.addCheckbox(screen, center, "MiscHover__UpdateUnitNameOnUpgrade")
		self.addCheckbox(screen, right, "UnitNaming__UseAdvanced")

		columnL, columnR = self.addTwoColumnLayout(screen, column, "UnitNaming")
		self.addTextEdit(screen, columnL, columnR, "UnitNaming__Default")
		self.addTextEdit(screen, columnL, columnR, "UnitNaming__Combat_SQUADRON")
		self.addTextEdit(screen, columnL, columnR, "UnitNaming__Combat_LIGHT_SHIP")
		self.addTextEdit(screen, columnL, columnR, "UnitNaming__Combat_CAPITAL_SHIP")
		self.addTextEdit(screen, columnL, columnR, "UnitNaming__Combat_CARRIER_SHIP")
		self.addTextEdit(screen, columnL, columnR, "UnitNaming__Combat_STARBASE")
		self.addTextEdit(screen, columnL, columnR, "UnitNaming__Combat_MISSILE")
		self.addTextEdit(screen, columnL, columnR, "UnitNaming__Combat_RECON")
		#self.addTextEdit(screen, columnL, columnR, "UnitNaming__Combat_NAVAL")
		self.addTextEdit(screen, columnL, columnR, "UnitNaming__Combat_None")
		#self.addTextEdit(screen, columnL, columnR, "UnitNaming__Combat_RECON")
		#self.addTextEdit(screen, columnL, columnR, "UnitNaming__Combat_SIEGE")
