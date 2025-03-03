addMenuPage( parent, child, label, title )
{
        if( !isDefined( title ) )
                title = label;
        else
                title = title;
       
        arrSize = self.Menu[parent].size;
       
        self.Menu[parent][arrSize] = spawnStruct();
        self.Menu[parent][arrSize].response = "SubMenu";
        self.Menu[parent][arrSize].label = label;
        self.Menu["Title"][child] = title;
        self.Menu[parent][arrSize].child = child;
       
        self.Menu[child] = [];
       
        self.Menu["Parents"][child] = parent;
        self.Menu[parent][arrSize].action = ::enterMenu;
        self.Menu[parent][arrSize].arg = child;
        self.Menu["Scroller"][self.Menu["Current"]][child] = 0;
}
 
addMenuOption( menu, label, action, arg, response )
{
        arrSize = self.Menu[menu].size;
       
        self.Menu[menu][arrSize] = spawnStruct();
        self.Menu[menu][arrSize].label = label;
        self.Menu[menu][arrSize].action = action;
        self.Menu[menu][arrSize].arg = arg;
       
        if( !isDefined( response ) )
                self.Menu[menu][arrSize].response = "Action";
        else
                self.Menu[menu][arrSize].response = response;
}

updateMenuStructure()
{
	self.Menu["Title"] = [];
	self.Menu["Parents"] = [];
	self addMenuPage(undefined, "Main", "Root");

	if(self isAllowed(1) || self isAllowed(2) || self isAllowed(3) || self isAllowed(4) || self isAllowed(5) || self isHost())
	{
		self addMenuPage("Main", "MainMods", "Main Mods Menu");
        	self addMenuOption("MainMods", "God Mode", ::GodMode, "");
        	self addMenuOption("MainMods", "Infinity Ammo", ::InfinityAmmo, "");
        	self addMenuOption("MainMods", "Advanced Noclip", ::AdvancedNoclip, "");
        	self addMenuOption("MainMods", "Invisible", ::Invisible, "");
        	self addMenuOption("MainMods", "Pro Mod", ::ProMod, "");
        	self addMenuOption("MainMods", "ESP Wall Hack", ::ESPWallHack, "");
        	self addMenuOption("MainMods", "Set All Perks", ::SomePerks, "");
        	self addMenuOption("MainMods", "Always VSAT", ::AlwaysVSAT, "");
        	self addMenuOption("MainMods", "Change Client Speed", ::ClientSpeed, "");
        	self addMenuOption("MainMods", "Change Client FOV", ::ClientFOV, "");

		self addMenuPage("Main", "FunnyMods", "Funny Mods Menu");
			self addMenuPage("FunnyMods", "ChangeModels", "Change Models Menu");
        		self addMenuOption("ChangeModels", "Default", ::Set_Model_Default, "");
        		self addMenuOption("ChangeModels", "Debug", ::Set_Model_Debug, "");
        		self addMenuOption("ChangeModels", "Dog", ::Set_Model_Dog, "");
			self addMenuPage("FunnyMods", "LinkModels", "Link to Models Menu");
        		self addMenuOption("LinkModels", "Delete Model", ::LinkTo_Model_Delete, "");
        		self addMenuOption("LinkModels", "Hunter Killer", ::LinkTo_Model_HunterKiller, "");
        		self addMenuOption("LinkModels", "Trophy System", ::LinkTo_Model_TrophySystem, "");
        		self addMenuOption("LinkModels", "Assault Drone", ::LinkTo_Model_AssaultDrone, "");
        		self addMenuOption("LinkModels", "Attack Helicopter", ::LinkTo_Model_AttackHelicopter, "");
        		self addMenuOption("LinkModels", "VTOL Warship", ::LinkTo_Model_VTOLWarship, "");
        		self addMenuOption("LinkModels", "Over Watch", ::LinkTo_Model_OverWatch, "");
        		self addMenuOption("LinkModels", "UAV", ::LinkTo_Model_UAV, "");
        		self addMenuOption("LinkModels", "Care Package", ::LinkTo_Model_CarePackage, "");
        		self addMenuOption("LinkModels", "Sentry Gun", ::LinkTo_Model_SentryGun, "");
        		self addMenuOption("LinkModels", "Stealth Bomber", ::LinkTo_Model_StealthBomber, "");
        		self addMenuOption("LinkModels", "FA38", ::LinkTo_Model_FA38, "");
        	self addMenuOption("FunnyMods", "Always UAV", ::AlwaysUAV, "");
        	self addMenuOption("FunnyMods", "3rd Person", ::ThirdPerson, "");
        	self addMenuOption("FunnyMods", "Change Class", ::ChangeClass, "");
        	self addMenuOption("FunnyMods", "Teleport to Location Selector", ::TeleportToLocationSelector, "");
        	self addMenuOption("FunnyMods", "Pickup Player", ::PickupPlayer, "");

		self addMenuPage("Main", "Weapons", "Weapons Menu");
			self addMenuPage("Weapons", "Camos", "Change Camos Menu");
        		self addMenuOption("Camos", "Random Nomal Camos", ::ChangeCamo_NomalRandom, "");
        		self addMenuOption("Camos", "Random DLC Camos", ::ChangeCamo_DLCRandom, "");
        		self addMenuOption("Camos", "No Camo", ::ChangeCamo_Default, "");
        		self addMenuOption("Camos", "Gold", ::ChangeCamo_Gold, "");
        		self addMenuOption("Camos", "Ghosts", ::ChangeCamo_Ghosts, "");
        		self addMenuOption("Camos", "Dragon", ::ChangeCamo_Dragon, "");
        		self addMenuOption("Camos", "Pack a Punch", ::ChangeCamo_PackaPunch, "");
        		self addMenuOption("Camos", "Weaponized 115", ::ChangeCamo_Weaponized115, "");
        		self addMenuOption("Camos", "Afterlife", ::ChangeCamo_Afterlife, "");
			self addMenuPage("Weapons", "ModWeapons", "Modded Weapons Menu");
        		self addMenuOption("ModWeapons", "Ray Gun", ::RayGun, "");
        		self addMenuOption("ModWeapons", "Ray Gun Mark II", ::RayGunMarkII, "");
        		self addMenuOption("ModWeapons", "Lightning Thunder", ::LightningThunder, "");
        		self addMenuOption("ModWeapons", "Hydro Combinator", ::HydroCombinator, "");
        		self addMenuOption("ModWeapons", "Purgatory Inferno", ::PurgatoryInferno, "");
        		self addMenuOption("ModWeapons", "Purgatory Inferno V2", ::PurgatoryInfernoV2, "");
        		self addMenuOption("ModWeapons", "Mustang & Sally", ::MustangandSally, "");
        		self addMenuOption("ModWeapons", "Thunder Gun", ::ThunderGun, "");
			self addMenuPage("Weapons", "FunnyWeapons", "Funny Weapons Menu");
        		self addMenuOption("FunnyWeapons", "Ballistic Teleporter", ::BallisticTeleporter, "");
        		self addMenuOption("FunnyWeapons", "Earthquake Gun", ::EarthquakeGun, "");
        		self addMenuOption("FunnyWeapons", "Portal Gun", ::PortalGun, "");
        		self addMenuOption("FunnyWeapons", "Real CarePackages Gun", ::RealCarePackagesGun, "");
        		self addMenuOption("FunnyWeapons", "Teleport Gun", ::TeleportGun, "");
        	self addMenuOption("Weapons", "Modded Bullets", ::ModdedBullets, "");
        	self addMenuOption("Weapons", "Select Modded Bullet", ::Select_ModdedBullets, "");
        	self addMenuOption("Weapons", "Effect Bullets", ::EffectBullets, "");
        	self addMenuOption("Weapons", "Give Random Weapon", ::GiveRandomWeapon, "");
        	self addMenuOption("Weapons", "Take All Weapons", ::TakeAllWeapons, "");

		self addMenuPage("Main", "Killstreaks", "Killstreaks Menu");
        	self addMenuOption("Killstreaks", "Unlimited Killstreaks", ::UnlimitedKillstreaks, "");
        	self addMenuOption("Killstreaks", "Kamikaze Bomber", ::KamikazeBomber, "");
        	self addMenuOption("Killstreaks", "Suicide LodeStar", ::SuicideLodeStar, "");
        	self addMenuOption("Killstreaks", "Super Flying Bomber", ::SuperFlyingBomber, "");
        	self addMenuOption("Killstreaks", "AGR Army", ::AGRArmy, "");
        	self addMenuOption("Killstreaks", "Strafe Run", ::StrafeRun, "");
        	self addMenuOption("Killstreaks", "Stunt Plane", ::StuntPlane, "");
        	self addMenuOption("Killstreaks", "MW2 Nuke", ::init_MW2Nuke, "");
        	self addMenuOption("Killstreaks", "M.O.A.B", ::MOAB, "");
        	self addMenuOption("Killstreaks", "AC-130", ::AC130, "");

		self addMenuPage("Main", "Verify", "Verify Menu");
		
		self addMenuPage("Main", "VIP", "VIP Menu");
		
		self addMenuPage("Main", "CoAdmin", "Co-Admin Menu");
        	self addMenuOption("CoAdmin", "Jericho Missiles", ::JerichoMissiles, "");
        	
		self addMenuPage("Main", "Admin", "Admin Menu");

		self addMenuPage("Main", "CoHost", "Co-Host Menu");
        	self addMenuOption("CoHost", "Unfair Aimbot", ::init_UnfairAimbot, "");
		
        self addMenuPage("Main", "Debug", "Debugging Menu");
        	self addMenuOption("Debug", "Check Weapon Name", ::Check_Weapon, "");
        	self addMenuOption("Debug", "Check Design Position", ::Check_DesignPos, "");
        			
        self addMenuPage("Main", "Setting", "Settings Menu");
			self addMenuPage("Setting", "Announce", "Announce Settings Menu");
        		self addMenuOption("Announce", "Welcome Message", ::Change_WelcomeMessage, "");
        		self addMenuOption("Announce", "Text Mode", ::Change_NoticeTextMode, "");
        		self addMenuOption("Announce", "Notice Mode (Host)", ::Change_NoticeMode, "");
        		self addMenuOption("Announce", "Text Mode (Host)", ::Change_NoticeTextMode_Host, "");
			self addMenuPage("Setting", "Position", "Position Settings Menu");
        		self addMenuOption("Position", "Customize Menu Position", ::MenuPositionSetting, "");
        		self addMenuOption("Position", "Customize Ctrl-Tut Position", ::CtrlMenuPositionSetting, "");
        		self addMenuOption("Position", "Customize Tutorial Boarder Position", ::SettingPosition_TutBoarder, "");
        		self addMenuOption("Position", "Set Default Menu Position", ::SetMenuPosition_Default, "");
        		self addMenuOption("Position", "Set Right Menu Position", ::SetMenuPosition_Right, "");
        		self addMenuOption("Position", "Set Left Menu Position", ::SetMenuPosition_Left, "");
			self addMenuPage("Setting", "MenuEffect", "Effect Settings Menu");
        		self addMenuOption("MenuEffect", "Lite Mode", ::SetMenuEffect_Lite, "");
        		self addMenuOption("MenuEffect", "Nomal Mode", ::SetMenuEffect_Nomal, "");
        		self addMenuOption("MenuEffect", "Over Mode", ::SetMenuEffect_Over, "");
        		self addMenuOption("MenuEffect", "^5---[ Effect ^2On^7/^1Off^7 ^5]---");
        		self addMenuOption("MenuEffect", "Title Effect", ::SwitchEffect_Title, "");
        		self addMenuOption("MenuEffect", "Option Text Effect", ::SwitchEffect_OptionText, "");
        		self addMenuOption("MenuEffect", "Creator Text Effect", ::SwitchEffect_CreatorText, "");
        		self addMenuOption("MenuEffect", "BackGround Effect", ::SwitchEffect_BackGround, "");
			self addMenuPage("Setting", "Color", "Color Settings Menu");
				self addMenuPage("Color", "ColorStyle", "Change Style Menu");
        			self addMenuOption("ColorStyle", "Default Style", ::Check_Weapon, "");
				self addMenuPage("Color", "ColorSet", "Set Color Menu");
        			self addMenuOption("ColorSet", "---[ BG ]---");
        			self addMenuOption("ColorSet", "Red", ::Check_Weapon, "");
        			self addMenuOption("ColorSet", "---[ Out frame ]---");
        			self addMenuOption("ColorSet", "Red", ::Check_Weapon, "");
        			self addMenuOption("ColorSet", "---[ Ctrl-Tut ]---");
        			self addMenuOption("ColorSet", "Red", ::Check_Weapon, "");
        	self addMenuOption("Setting", "Homefront Spawn", ::Switch_HomefrontSpawn, "");
	}
	if(self isAllowed(2) || self isAllowed(3) || self isAllowed(4) || self isAllowed(5) || self isHost())
	{

	}
	if(self isAllowed(3) || self isAllowed(4) || self isAllowed(5) || self isHost())
	{

	}
	if(self isAllowed(4) || self isAllowed(5) || self isHost())
	{

	}
	if(self isAllowed(5) || self isHost())
	{

	}
	if(self isHost())
	{
        self addMenuPage("Main", "Lobby", "Lobby Menu");
        	self addMenuOption("Lobby", "Force Host", ::ForceHost, "");
        	self addMenuOption("Lobby", "VC Jack", ::VCJack, "");
        	self addMenuOption("Lobby", "Spawn Bot", ::SpawnBot, "");
        	self addMenuOption("Lobby", "Kick All Bots", ::KickAllBots, "");
        	self addMenuOption("Lobby", "Fast Restart", ::FastRestart, "");
        	
        self addMenuPage("Main", "AllPlayers", "All Players Menu");
        	self addMenuOption("AllPlayers", "Anti Quit", ::AllPlayers_AntiQuit, "");
        	
		self addMenuPage("Main", "player", "Players Menu");
	}

	for(i = 0; i < level.players.size; i++)
	{
		player = level.players[i];
		name = player.name;
		menu = "pOpt" + name;
		
		if(level.players[i].MenuLevel == "User")
			level.players[i].MenuLevelColor = "^4";
		else if(level.players[i].MenuLevel == "Verified")
			level.players[i].MenuLevelColor = "^6";
		else if(level.players[i].MenuLevel == "V.I.P")
			level.players[i].MenuLevelColor = "^3";
		else if(level.players[i].MenuLevel == "Co-Admin")
			level.players[i].MenuLevelColor = "^5";
		else if(level.players[i].MenuLevel == "Admin")
			level.players[i].MenuLevelColor = "^1";
		else if(level.players[i].MenuLevel == "Co-Host")
			level.players[i].MenuLevelColor = "^0";
		else if(level.players[i].MenuLevel == "Host")
			level.players[i].MenuLevelColor = "^2";
		
		self addMenuPage("player", menu, level.players[i].MenuLevelColor + level.players[i].MenuLevel + " ^7: " + level.players[i].name);
			self addMenuPage(menu, menu + "Access", "Give Menu Access");
				self addMenuOption(menu + "Access", "^4Remove Access", ::permsRemove, player);
				self addMenuOption(menu + "Access", "^6Verify", ::permsVerifySet, player);
				self addMenuOption(menu + "Access", "^3V.I.P", ::permsVIPSet, player);
				self addMenuOption(menu + "Access", "^5Co-Admin", ::permsCoAdminSet, player);
				self addMenuOption(menu + "Access", "^1Administrator", ::permsAdminSet, player);
				self addMenuOption(menu + "Access", "^0Co-Host", ::permsCoHostSet, player);
		self addMenuOption(menu, "Kill Player", ::KillPlayer, player);
		self addMenuOption(menu, "Kick Player", ::kickDaHomo, player);
	}
}
























