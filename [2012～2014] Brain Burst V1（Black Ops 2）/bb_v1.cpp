#include maps/mp/_utility;
#include common_scripts/utility;
#include maps/mp/gametypes/_rank;
#include maps/mp/gametypes/_globallogic;
#include maps/mp/gametypes/_hud;
#include maps/mp/gametypes/_hud_util;
#include maps/mp/gametypes/_hud_message;
#include maps/mp/gametypes/_weapons;
#include maps/mp/teams/_teams;

init()
{
	level.clientid = 0;
	level thread onplayerconnect();
	
	//Menu Design Alpha Down
	precacheShader("line_horizontal");
	level.icontest = "line_horizontal";
	//JetPack
	precacheModel("projectile_hellfire_missile");
	level._effect["flak20_fire_fx"] = loadfx("weapon/tracer/fx_tracer_flak_single_noExp");
	//Models
	precacheModel("defaultactor");
	precacheModel("german_shepherd");
	precacheModel("t6_wpn_tablet_view");
	precacheModel("t6_wpn_supply_drop_ally");
	precacheModel("t6_wpn_supply_drop_axis");
	precacheModel("mp_flag_green");
	precacheModel("mp_flag_red");
	//Capackage Heli
	precacheVehicle("heli_guard_mp");
	precacheModel("veh_t6_drone_overwatch_light");
	level.CareHeli_marker_smoke = loadfx("env/smoke/fx_smoke_supply_drop_blue_mp");
	//Smoke Monster
	level.fx_smokegrenade_single = "smoke_center_mp";
	precacheitem( level.fx_smokegrenade_single );
}
onplayerconnect()
{
	for(;;)
	{
		level waittill("connecting", player);
		player thread onplayerspawned();
		player.clientid = level.clientid;
		level.clientid++;
		player.Verified = false;
		player.VIP = false;
		player.Admin = false;
		player.CoHost = false;
		player.Host = false;
		player.MyAccess = "";
	}
}
onplayerspawned()
{
	self endon("disconnect");
	level endon("game_ended");
	self endon("menuinit_one");
	for(;;)
	{
		self waittill( "spawned_player" );
		wait 0.1;
		if(self isHost() || self.Host == true)
		{
   			self notify("spawn_menudouble");
			wait 0.1;
			self thread MenuWelcome();
			wait 0.1;
			self.Verified = true;
			self.VIP = true;
			self.Admin = true;
			self.CoHost = true;
			self.Host = true;
			self.MyAccess = "^2H";
			if(self.givestBind == 0)
			{
				self thread doStlhBind();
				self.givestBind = 1;
			}
		}
		else if (self.CoHost == true)
		{
   			self notify("spawn_menudouble");
			wait 0.1;
			self thread MenuWelcome();
			wait 0.1;
			self.Verified = true;
			self.VIP = true;
			self.Admin = true;
			self.CoHost = true;
			self.Host = false;
			self.MyAccess = "^5Co";
		}
		else if (self.Admin == true)
		{
   			self notify("spawn_menudouble");
			wait 0.1;
			self thread MenuWelcome();
			wait 0.1;
			self.Verified = true;
			self.VIP = true;
			self.Admin = true;
			self.MyAccess = "^1Ad";
		}
		else if (self.VIP == true)
		{
   			self notify("spawn_menudouble");
			wait 0.1;
			self thread MenuWelcome();
			wait 0.1;
			self.Verified = true;
			self.VIP = true;
			self.MyAccess = "^3Vi";
		}
		else if (self.Verified == true)
		{
   			self notify("spawn_menudouble");
			wait 0.1;
			self thread MenuWelcome();
			wait 0.1;
			self.Verified = true;
			self.MyAccess = "^6Ve";
		}
		else if (self.Verified == false)
		{
			self.MyAccess = "";
		}
		if(self.Host == true || self.CoHost == true || self.Admin == true || self.VIP == true || self.Verified == true)
		{
			if (self.MenuInit == 0)
			{
				self thread initFirstMenuGive();
			}
		}
		wait 0.03;
	}
}
setplayermenugive()
{
	self endon("disconnect");
	level endon("game_ended");
	self endon("spawn_menudouble");
	for(;;)
	{
		self waittill("sad_menugive");
		wait 0.1;
		if(self isHost() || self.Host == true)
		{
			self thread onplayerspawned();
			wait 0.1;
			self thread MenuWelcome();
			wait 0.1;
			self.Verified = true;
			self.VIP = true;
			self.Admin = true;
			self.CoHost = true;
			self.Host = true;
			self.MyAccess = "^2H";
		}
		else if (self.CoHost == true)
		{
			self thread onplayerspawned();
			wait 0.1;
			self thread MenuWelcome();
			wait 0.1;
			self.Verified = true;
			self.VIP = true;
			self.Admin = true;
			self.CoHost = true;
			self.Host = false;
			self.MyAccess = "^5Co";
			self thread initFirstMenuGive();
		}
		else if (self.Admin == true)
		{
			self thread onplayerspawned();
			wait 0.1;
			self thread MenuWelcome();
			wait 0.1;
			self.Verified = true;
			self.VIP = true;
			self.Admin = true;
			self.MyAccess = "^1Ad";
			self thread initFirstMenuGive();
		}
		else if (self.VIP == true)
		{
			self thread onplayerspawned();
			wait 0.1;
			self thread MenuWelcome();
			wait 0.1;
			self.Verified = true;
			self.VIP = true;
			self.MyAccess = "^3Vi";
			self thread initFirstMenuGive();
		}
		else if (self.Verified == true)
		{
			self thread onplayerspawned();
			wait 0.1;
			self thread MenuWelcome();
			wait 0.1;
			self.Verified = true;
			self.MyAccess = "^6Ve";
			self thread initFirstMenuGive();
		}
		else if (self.Verified == false)
		{
			self.MyAccess = "";
		}
		wait 0.03;
	}
}
initFirstMenuGive()
{
	self notify("stop_BuildMenu");
	wait 0.1;
	if (self.MenuInitDesigns == 0)
	{
		self.Menu = spawnstruct();
		self InitialisingMenu();
		initOverFlowFix();
		self.MenuInitDesigns = 1;
	}
	self MenuStructure();
	self thread BuildMenu();
	self.MenuInit = 1;
}
initOverFlowFix()
{
	self.stringTable = [];
	self.stringTableEntryCount = 0;
	self.textTable = [];
	self.textTableEntryCount = 0;

	if(isDefined(level.anchorText) == false)
	{
		level.anchorText = createServerFontString("default",1.5);
		level.anchorText setText("anchor");
		level.anchorText.alpha = 0;

		level.stringCount = 0;
		level thread monitorOverflow();
	}
}
monitorOverflow()
{
	level endon("disconnect");

	for(;;)
	{
		if(level.stringCount >= 60)
		{
			level.anchorText clearAllTextAfterHudElem();
			level.stringCount = 0;

			foreach(player in level.players)
			{
				player purgeTextTable();
				player purgeStringTable();
				player recreateText();
			}
		}
		wait 0.05;
	}
}
purgeTextTable()
{
	textTable = [];
       
	foreach(entry in self.textTable)
	{
		if(entry.id != -1)
			textTable[textTable.size] = entry;
	}

	self.textTable = textTable;
}
purgeStringTable()
{
	stringTable = [];

	foreach(entry in self.textTable)
		stringTable[stringTable.size] = getStringTableEntry(entry.stringId);

	self.stringTable = stringTable;
}
getStringTableEntry(id)
{
	stringTableEntry = -1;

	foreach(entry in self.stringTable)
	{
		if(entry.id == id)
		{
			stringTableEntry = entry;
			break;
		}
	}

	return stringTableEntry;
}
recreateText()
{
	foreach(entry in self.textTable)
		entry.element setSafeText(self, lookUpStringById(entry.stringId));
}
lookUpStringById(id)
{
	string = "";

	foreach(entry in self.stringTable)
	{
		if(entry.id == id)
		{
			string = entry.string;
			break;
		}
	}

	return string;
}
setSafeText(player, text)
{
	stringId = player getStringId(text);

	if(stringId == -1)
	{
		player addStringTableEntry(text);
		stringId = player getStringId(text);
	}

	player editTextTableEntry(self.textTableIndex, stringId);

	self setText(text);
}
getStringId(string)
{
	id = -1;

	foreach(entry in self.stringTable)
	{
		if(entry.string == string)
		{
			id = entry.id;
			break;
		}
	}

	return id;
}
addStringTableEntry(string)
{
	entry = spawnStruct();
	entry.id = self.stringTableEntryCount;
	entry.string = string;

	self.stringTable[self.stringTable.size] = entry;
	self.stringTableEntryCount++;
	level.stringCount++;
}
editTextTableEntry(id, stringId)
{
	foreach(entry in self.textTable)
	{
		if(entry.id == id)
		{
			entry.stringId = stringId;
			break;
		}
	}
}
clear(player)
{
	if(self.type == "text")
		player deleteTextTableEntry(self.textTableIndex);

	self destroy();
}
deleteTextTableEntry(id)
{
	foreach(entry in self.textTable)
	{
		if(entry.id == id)
		{
			entry.id = -1;
			entry.stringId = -1;
		}
	}
}
createText(font, fontscale, align, relative, x, y, sort, text, colour, alphaa, gcolor, galpha)
{
	textElem = CreateFontString(font, fontscale);
	textElem setText(text);
	textElem setPoint(align, relative, x, y);
	textElem.sort = sort;
	textElem.colour = color;
	textElem.alphaa = alpha;
	textElem.gcolor = glowColor;
	textElem.galpha = glowAlpha;
	textElem.hideWhenInMenu = true;
	textElem.type = "text";

	addTextTableEntry(textElem, getStringId(text));
	textElem setSafeText(self, text);

	return textElem;
}
addTextTableEntry(element, stringId)
{
	entry = spawnStruct();
	entry.id = self.textTableEntryCount;
	entry.element = element;
	entry.stringId = stringId;

	element.textTableIndex = entry.id;

	self.textTable[self.textTable.size] = entry;
	self.textTableEntryCount++;
}
BuildMenu()
{
	self endon("disconnect");
	self endon("stop_BuildMenu");
	self.MenuOpen = false;
	
	for(;;)
	{
		self thread MenuDeath();
		if(self adsButtonPressed() && self meleeButtonPressed() && self.MenuOpen == false)
		{
			self MenuOpening();
			self LoadMenu("Main Menu");
		}
		else if(self adsButtonPressed() && self actionSlotTwoButtonPressed() && self.MenuOpen == true)
		{
			if(isDefined(self.Menu.System["MenuPrevious"][self.Menu.System["MenuRoot"]]))
			{
				self.Menu.System["MenuCurser"] = 0;
				self SubMenu(self.Menu.System["MenuPrevious"][self.Menu.System["MenuRoot"]]);
				wait 0.03;
			}
			else
			{
				self MenuClosing();
				wait 0.03;
			}
		}
		else if (self actionslotonebuttonpressed() && self.MenuOpen == true)
		{
			self.Menu.System["MenuCurser"] -= 1;
			if (self.Menu.System["MenuCurser"] < 0)
			{
				self.Menu.System["MenuCurser"] = self.Menu.System["MenuTexte"][self.Menu.System["MenuRoot"]].size - 1;
			}
			self.Menu.Material["Scrollbar"] elemMoveY(.2, 60 + (self.Menu.System["MenuCurser"] * 13.2));
			wait 0.03;
		}
		else if (self actionslottwobuttonpressed() && self.MenuOpen == true)
		{
			self.Menu.System["MenuCurser"] += 1;
			if (self.Menu.System["MenuCurser"] >= self.Menu.System["MenuTexte"][self.Menu.System["MenuRoot"]].size)
			{
				self.Menu.System["MenuCurser"] = 0;
			}
			self.Menu.Material["Scrollbar"] elemMoveY(.2, 60 + (self.Menu.System["MenuCurser"] * 13.2));
			wait 0.03;
		}
		else if(self UseButtonPressed() && self.MenuOpen == true)
		{
			wait 0.03;
			if(self.Menu.System["MenuRoot"]=="Clients Menu") self.Menu.System["ClientIndex"]=self.Menu.System["MenuCurser"];
				self thread [[self.Menu.System["MenuFunction"][self.Menu.System["MenuRoot"]][self.Menu.System["MenuCurser"]]]](self.Menu.System["MenuInput"][self.Menu.System["MenuRoot"]][self.Menu.System["MenuCurser"]]);
			wait 0.12;
		}
		wait 0.05;
	}
}	

MenuStructure()
{
	self endon("change_Jap");
	self endon("change_Eng");
	if (self.Verified == true)
	{
		self MainMenu("Main Menu", undefined);
		self MenuOption("Main Menu", 0, "Weakly Cheats", ::SubMenu, "Sub Menu 3");
		self MenuOption("Main Menu", 1, "Chat", ::SubMenu, "Sub Menu 4");
		self MenuOption("Main Menu", 2, "Design", ::SubMenu, "Sub Menu 13");
		self MenuOption("Main Menu", 3, "Laungage", ::SubMenu, "Sub Menu 14");
	}
	if (self.VIP == true)
	{
		self MenuOption("Main Menu", 4, "Funny Mods", ::SubMenu, "Sub Menu 2");
		self MenuOption("Main Menu", 5, "VIP", ::SubMenu, "Sub Menu 6 (Admin)");
		self MenuOption("Main Menu", 6, "Account Hack", ::SubMenu, "Sub Menu 10");
	}
	if (self.Admin == true)
	{
		self MenuOption("Main Menu", 7, "Weapons", ::SubMenu, "Sub Menu 5 (VIP)");
		self MenuOption("Main Menu", 8, "Admin", ::SubMenu, "Sub Menu 7 (Host)");
	}
	if (self.CoHost == true)
	{
		self MenuOption("Main Menu", 9, "Co-Host", ::SubMenu, "Sub Menu 8");
		self MenuOption("Main Menu", 10, "Forge", ::SubMenu, "Forge Menu");
		self MenuOption("Main Menu", 11, "Spawns", ::SubMenu, "Sub Menu 9");
		self MenuOption("Main Menu", 12, "Players", ::SubMenu, "Clients Menu");
	}
	if (self.Host == true)
	{
		self MenuOption("Main Menu", 13, "All Players", ::SubMenu, "All Clients");
		self MenuOption("Main Menu", 14, "Lobby Mods", ::SubMenu, "Sub Menu 11");
		self MenuOption("Main Menu", 15, "Host", ::SubMenu, "Sub Menu 12");
	}

	self MainMenu("Sub Menu 2", "Main Menu");
	self MenuOption("Sub Menu 2", 0, "^2Set Visions", ::SubMenu, "Visions List");
	self MenuOption("Sub Menu 2", 1, "Change Models", ::SubMenu, "Models List");
	self MenuOption("Sub Menu 2", 2, "^7Team Change", ::initTeamChange);
	self MenuOption("Sub Menu 2", 3, "Clone Player", ::ClonePlayer);
	self MenuOption("Sub Menu 2", 4, "Earthquake", ::Quake);
	self MenuOption("Sub Menu 2", 5, "Save/Set Location", ::saveandload);
	self MenuOption("Sub Menu 2", 6, "Mulit Jump", ::Toggle_Multijump);
	self MenuOption("Sub Menu 2", 7, "Teleport to Croshair", ::TpToCrHr);
	self MenuOption("Sub Menu 2", 8, "Rocket Teleporter", ::initRocketTeleport);
	self MenuOption("Sub Menu 2", 9, "SpecNade", ::initSpecNade);
	self MenuOption("Sub Menu 2", 10, "Riot Man", ::initRiotMan);
	self MenuOption("Sub Menu 2", 11, "Plant Bomb (^1S&D^7)", ::PlantBomb);
	self MenuOption("Sub Menu 2", 12, "Defuse Bomb (^1S&D^7)", ::DefuseBomb);

	self MainMenu("Visions List", "Sub Menu 2");
	self MenuOption("Visions List", 0, "EMP", ::empV);
	self MenuOption("Visions List", 1, "Thermal", ::Thermalv);
	self MenuOption("Visions List", 2, "Black and White", ::BWV);
	self MenuOption("Visions List", 3, "Light", ::LVis);
	self MenuOption("Visions List", 4, "Enhanced", ::EV);
	
	self MainMenu("Models List", "Sub Menu 2");
	self MenuOption("Models List", 0, "Default Model", ::setDefoModel);
	self MenuOption("Models List", 1, "Debug Model", ::SetModelDefoact);
	self MenuOption("Models List", 2, "Dog", ::SetModelDog);
	self MenuOption("Models List", 3, "Trophy System", ::SetModelTrosys);
	self MenuOption("Models List", 4, "Assault Drone", ::SetModelAssaDro);
	self MenuOption("Models List", 5, "Sentry Gun", ::SetModelTurret);
	self MenuOption("Models List", 6, "Care Package", ::SetModelCareP);
	self MenuOption("Models List", 7, "Hunter Killer", ::SetModelHKiller);
	self MenuOption("Models List", 8, "UAV", ::SetModelUAV);
	self MenuOption("Models List", 9, "Little Bird", ::SetModelOverwatch);
	self MenuOption("Models List", 10, "Attack Helicopter", ::SetModelAttackHeli);
	self MenuOption("Models List", 11, "VTOL Warship", ::SetModelOspley);
	self MenuOption("Models List", 12, "Stealth Bomber", ::SetModelStealth);
	self MenuOption("Models List", 13, "Harrier", ::SetModelHarrier);
	
	self MainMenu("Sub Menu 3", "Main Menu");
	self MenuOption("Sub Menu 3", 0, "Always UAV", ::doUAV);
	self MenuOption("Sub Menu 3", 1, "Set All Perks", ::setAllPerks);
	self MenuOption("Sub Menu 3", 2, "3rd Person", ::giveTP);
	self MenuOption("Sub Menu 3", 3, "Change Class", ::ChangeClass);
	self MenuOption("Sub Menu 3", 4, "Max Ammo", ::giveMaxAmmo);
	self MenuOption("Sub Menu 3", 5, "Auto Drop-Shot", ::AutoDropshot);
	self MenuOption("Sub Menu 3", 6, "Display HP", ::initHealthBar);
	self MenuOption("Sub Menu 3", 7, "Clear All Perks", ::doClearPerks);
	self MenuOption("Sub Menu 3", 8, "Suicide", ::doSuicide);
	
	self MainMenu("Sub Menu 4", "Main Menu");
	self MenuOption("Sub Menu 4", 0, "^5These Option is look at All Players.");
	self MenuOption("Sub Menu 4", 1, "^7This Mod Menu Info", ::doChatPatchInfo);
	self MenuOption("Sub Menu 4", 2, "NextGenUpdate", ::doChatGSCTalk);
	self MenuOption("Sub Menu 4", 3, "Introduce ^1" + self.name, ::doChatMyIntro);
	self MenuOption("Sub Menu 4", 4, "^7Lobby Host Info", ::doChatLobbyHost);
	self MenuOption("Sub Menu 4", 5, "^5--Fake Typewriter--");
	self MenuOption("Sub Menu 4", 6, "You must use RTE Tool, change Host Name");
	self MenuOption("Sub Menu 4", 7, "^7Typewriter", ::doChatTypewriter);
	
	self MainMenu("Sub Menu 5 (VIP)", "Main Menu");
	self MenuOption("Sub Menu 5 (VIP)", 0, "^2Give Weapons", ::SubMenu, "Weapons List");
	self MenuOption("Sub Menu 5 (VIP)", 1, "^7Take Weapons", ::TakeWeapon);
	self MenuOption("Sub Menu 5 (VIP)", 2, "^2Modded Bullets", ::SubMenu, "Bullets List");
	self MenuOption("Sub Menu 5 (VIP)", 3, "Special Bullets", ::SubMenu, "LTBullets List");
	self MenuOption("Sub Menu 5 (VIP)", 4, "Effect Bullets", ::SubMenu, "EffectB List");
	self MenuOption("Sub Menu 5 (VIP)", 5, "^7Teleport Gun", ::ToggleTeleportGun);
	self MenuOption("Sub Menu 5 (VIP)", 6, "Earthquake Gun", ::doEarthQGun);
	self MenuOption("Sub Menu 5 (VIP)", 7, "Thunder Gun", ::ThunGun);
	
	self MainMenu("Bullets List", "Sub Menu 5 (VIP)");
	self MenuOption("Bullets List", 0, "^3On/Off Projectiles", ::initMagicBullet);
	self MenuOption("Bullets List", 1, "^7R-870 MCS", ::selectMBmcs);
	self MenuOption("Bullets List", 2, "SMAW", ::selectMBsmaw);
	self MenuOption("Bullets List", 3, "Grenade", ::selectMBgrenade);
	self MenuOption("Bullets List", 4, "A.G.R Rocket", ::selectMBagr);
	self MenuOption("Bullets List", 5, "Warthog Rocket", ::selectMBwarthog);
	self MenuOption("Bullets List", 6, "Loadstar", ::selectMBlstar);
	self MenuOption("Bullets List", 7, "Mortar Missile Burner", ::selectMBburner);
	self MenuOption("Bullets List", 8, "Remote Mortar Missile", ::selectMBrmmm);
	self MenuOption("Bullets List", 9, "Heli Gunner Missile", ::selectMBhgr);
	self MenuOption("Bullets List", 10, "Swarm", ::selectMBswarm);
	self MenuOption("Bullets List", 11, "Hanter Killer", ::selectMBhkill);
	
	self MainMenu("LTBullets List", "Sub Menu 5 (VIP)");
	self MenuOption("LTBullets List", 0, "^3On/Off Projectiles", ::initMagicGrenade);
	self MenuOption("LTBullets List", 1, "^7Frag", ::selectMLTfrag);
	self MenuOption("LTBullets List", 2, "Semtex", ::selectMLTstick);
	self MenuOption("LTBullets List", 3, "Concussion", ::selectMLTconc);
	self MenuOption("LTBullets List", 4, "Flash", ::selectMLTflash);
	self MenuOption("LTBullets List", 5, "EMP", ::selectMLTemp);
	self MenuOption("LTBullets List", 6, "Smoke Grenade", ::selectMLTbetty);
	self MenuOption("LTBullets List", 7, "Sensor", ::selectMLTsensor);
	self MenuOption("LTBullets List", 8, "C4", ::selectMLTshock);
	self MenuOption("LTBullets List", 9, "Claymore", ::selectMLTclaym);
	self MenuOption("LTBullets List", 10, "Trophy System", ::selectMLTtrosy);
	self MenuOption("LTBullets List", 11, "C-Axe", ::selectMLTaxe);
	self MenuOption("LTBullets List", 12, "Shock Charge", ::selectMLTc4);

	self MainMenu("Weapons List", "Sub Menu 5 (VIP)");
	self MenuOption("Weapons List", 0, "Death Machine", ::giveWdmachine);
	self MenuOption("Weapons List", 1, "War Machine", ::giveWWMachine);
	self MenuOption("Weapons List", 2, "AN-94", ::giveWan);
	self MenuOption("Weapons List", 3, "LSAT", ::giveWlsat);
	self MenuOption("Weapons List", 4, "Peacekeeper", ::giveWpkeep);
	self MenuOption("Weapons List", 5, "SCAR-H", ::giveWscar);
	self MenuOption("Weapons List", 6, "Balista", ::giveWbalista);
	self MenuOption("Weapons List", 7, "DSR 50", ::giveWdsr);
	self MenuOption("Weapons List", 8, "R-870 MCS", ::giveWmcs);
	self MenuOption("Weapons List", 9, "Crossbow", ::giveWcrsb);
	self MenuOption("Weapons List", 10, "RPG", ::giveWrpg);
	self MenuOption("Weapons List", 11, "Random Weapons", ::giveRWeapon);
	self MenuOption("Weapons List", 12, "Default Weapon", ::giveWdefowep);
	
	self MainMenu("EffectB List", "Sub Menu 5 (VIP)");
	self MenuOption("EffectB List", 0, "Explosive Bullets", ::ExpBultOn);
	self MenuOption("EffectB List", 1, "Non-FX Ex-Bullets", ::initNonFXExpBult);
	self MenuOption("EffectB List", 2, "Water Bullets", ::initWGun);
	self MenuOption("EffectB List", 3, "EMP Bullets", ::initEMPBullets);
	self MenuOption("EffectB List", 4, "Nuke Bullets", ::initNukeBullets);

	self MainMenu("Sub Menu 6 (Admin)", "Main Menu");
	self MenuOption("Sub Menu 6 (Admin)", 0, "^2Give Killstreaks", ::SubMenu, "Kstreak List");
	self MenuOption("Sub Menu 6 (Admin)", 1, "^7Unlimited Killstreaks", ::doKillstreaks);
	self MenuOption("Sub Menu 6 (Admin)", 2, "Always VSAT", ::alwaysVSAT);
	self MenuOption("Sub Menu 6 (Admin)", 3, "Walk Speed Change", ::doClientsSpeed);
	self MenuOption("Sub Menu 6 (Admin)", 4, "Ninja Mode", ::doNinja);
	self MenuOption("Sub Menu 6 (Admin)", 5, "Teleport the iPad", ::TeleportWithiPad);
	self MenuOption("Sub Menu 6 (Admin)", 6, "Jet Pack", ::doJetPack);
	self MenuOption("Sub Menu 6 (Admin)", 7, "Walking Loadstar", ::walkingLoadestar);
	self MenuOption("Sub Menu 6 (Admin)", 8, "Human Torch", ::initHTorch);
	self MenuOption("Sub Menu 6 (Admin)", 9, "Water Fountain", ::initWFountain);
	self MenuOption("Sub Menu 6 (Admin)", 10, "Smoke Monster", ::initSmokeMonster);

	self MainMenu("Kstreak List", "Sub Menu 6 (Admin)");
	self MenuOption("Kstreak List", 0, "UAV", ::KSGiveUAV);
	self MenuOption("Kstreak List", 1, "RC-XD", ::KSGiveRC);
	self MenuOption("Kstreak List", 2, "Hunter Killer", ::KSGiveHunt);
	self MenuOption("Kstreak List", 3, "Care Package", ::KSGiveCare);
	self MenuOption("Kstreak List", 4, "Counter UAV", ::KSGiveCUAV);
	self MenuOption("Kstreak List", 5, "Gaurdian", ::KSGiveGaurd);
	self MenuOption("Kstreak List", 6, "Hellstorm Missile", ::KSGiveHell);
	self MenuOption("Kstreak List", 7, "Lightning Strike", ::KSGiveLS);
	self MenuOption("Kstreak List", 8, "Sentry Gun", ::KSGiveSG);
	self MenuOption("Kstreak List", 9, "A.G.R", ::KSGiveAG);
	self MenuOption("Kstreak List", 10, "Stealth Chopper", ::KSGiveSC);
	self MenuOption("Kstreak List", 11, "Orbital VSAT", ::KSGiveVSAT);
	self MenuOption("Kstreak List", 12, "Escort Drone", ::KSGiveED);
	self MenuOption("Kstreak List", 13, "EMP System", ::KSGiveEMP);
	self MenuOption("Kstreak List", 14, "Warthog", ::KSGiveWH);
	self MenuOption("Kstreak List", 15, "Loadestar", ::KSGiveLST);
	self MenuOption("Kstreak List", 16, "VTOL Warship", ::KSGiveVW);
	self MenuOption("Kstreak List", 17, "Swarm", ::KSGiveSwarm);
	
	self MainMenu("Sub Menu 7 (Host)", "Main Menu");
	self MenuOption("Sub Menu 7 (Host)", 0, "God Mode", ::giveGod);
	self MenuOption("Sub Menu 7 (Host)", 1, "Infinity Ammo", ::doInfAmmo);
	self MenuOption("Sub Menu 7 (Host)", 2, "Invisible", ::InvisibleOn);
	self MenuOption("Sub Menu 7 (Host)", 3, "Advanced No Clip", ::doNoClip);
	self MenuOption("Sub Menu 7 (Host)", 4, "Forge Mode", ::ForgeON);
	self MenuOption("Sub Menu 7 (Host)", 5, "UFO Mode", ::UFOMode);
	self MenuOption("Sub Menu 7 (Host)", 6, "^2Aimbot Setting", ::SubMenu, "Aimbot List");

	self MainMenu("Aimbot List", "Sub Menu 7 (Host)");
	self MenuOption("Aimbot List", 0, "On/Off Aimbot", ::initEnstoneAimbot);
	self MenuOption("Aimbot List", 1, "On/Off Aiming Required", ::aimingMethod);
	self MenuOption("Aimbot List", 2, "Change Aiming Position", ::changeAimingPos);
	self MenuOption("Aimbot List", 3, "Stealth Aimbot (Head)", ::doStealthAimbots);
	
	self MainMenu("Sub Menu 8", "Main Menu");
	self MenuOption("Sub Menu 8", 0, "Unfair Aimbot", ::switchUnfairAimbot);
	self MenuOption("Sub Menu 8", 1, "Kamikaze Bomber", ::kamikaze);
	self MenuOption("Sub Menu 8", 2, "Jericho Missiles", ::JeriMissOn);
	self MenuOption("Sub Menu 8", 3, "Strafe Run", ::doStrafeRunz);
	self MenuOption("Sub Menu 8", 4, "Pokemon", ::pokeBall);
	self MenuOption("Sub Menu 8", 5, "Matrix Mode", ::initMatrix);
	self MenuOption("Sub Menu 8", 6, "All Player Teleport to .Loc", ::initAPulTele);
	self MenuOption("Sub Menu 8", 7, "Stealth Bind", ::initStlhBind);
	
	self MainMenu("Forge Menu", "Main Menu");
	self MenuOption("Forge Menu", 0, "Advanced Forge Mode", ::ForgeMode);
	self MenuOption("Forge Menu", 1, "Fast Object Delete", ::initFastDelete);
	self MenuOption("Forge Menu", 2, "Spawn Warpzone", ::initTeletoFlag);
	self MenuOption("Forge Menu", 3, "Create Slope", ::ForgeRamp);
	self MenuOption("Forge Menu", 4, "Create Wall", ::ForgeWall);
	self MenuOption("Forge Menu", 5, "Create Floor", ::ForgeGrids);
	self MenuOption("Forge Menu", 6, "Bunker", ::initSpawnBunker);
	self MenuOption("Forge Menu", 7, "Sky Plaza", ::initSkyPlaza);
	self MenuOption("Forge Menu", 8, "Prison Break", ::initPrison);
	self MenuOption("Forge Menu", 9, "Escalatore", ::Escalatore);

	self MainMenu("Sub Menu 9", "Main Menu");
	self MenuOption("Sub Menu 9", 0, "^2Turrets", ::SubMenu, "Turret List");
	self MenuOption("Sub Menu 9", 1, "Object Bullets", ::SubMenu, "SpawnB List");
	self MenuOption("Sub Menu 9", 2, "Give Boxes", ::SubMenu, "GiveB List");
	self MenuOption("Sub Menu 9", 3, "^7Shoot Real Carepackages", ::doCpGunBeta);
	self MenuOption("Sub Menu 9", 4, "Land Mines", ::doMineSpawner);
	self MenuOption("Sub Menu 9", 5, "Auto Killer", ::IMSMW3);
	self MenuOption("Sub Menu 9", 6, "Drivable Car", ::spawnDrivableCar);
	self MenuOption("Sub Menu 9", 7, "Controll Helicopter", ::CareHeli);
	self MenuOption("Sub Menu 9", 8, "^2Ace Combat", ::SubMenu, "Jet List");
	self MenuOption("Sub Menu 9", 9, "Pilot Aircraft", ::SubMenu, "Heli List");
	
	self MainMenu("GiveB List", "Sub Menu 9");
	self MenuOption("GiveB List", 0, "^2Basic Cheats", ::SubMenu, "GiveB1 List");
	self MenuOption("GiveB List", 1, "Funny Actions", ::SubMenu, "GiveB2 List");
	self MenuOption("GiveB List", 2, "Weapon Mods", ::SubMenu, "GiveB3 List");
	self MenuOption("GiveB List", 3, "Extra Mods", ::SubMenu, "GiveB4 List");
	
	self MainMenu("GiveB1 List", "GiveB List");
	self MenuOption("GiveB1 List", 0, "God Mode", ::giveBoxGod);
	self MenuOption("GiveB1 List", 1, "Infinity Ammo", ::giveBoxInf);
	self MenuOption("GiveB1 List", 2, "3rd Person", ::giveBox3rd);
	self MenuOption("GiveB1 List", 3, "Thermal Vision", ::giveBoxNV);
	self MenuOption("GiveB1 List", 4, "Walk Speed Change", ::giveBoxWalk);
	self MenuOption("GiveB1 List", 5, "Random Weapons", ::giveBoxRWep);
	self MenuOption("GiveB1 List", 6, "Display HP", ::giveBoxDHP);
	
	self MainMenu("GiveB2 List", "GiveB List");
	self MenuOption("GiveB2 List", 0, "Advanced No Clip", ::giveBoxNoc);
	self MenuOption("GiveB2 List", 1, "Advanced Forge Mode", ::giveBoxForg);
	self MenuOption("GiveB2 List", 2, "Mulit Jump", ::giveBoxJump);
	self MenuOption("GiveB2 List", 3, "Ninja Mode", ::giveBoxNinj);
	self MenuOption("GiveB2 List", 4, "Human Torch", ::giveBoxFire);
	
	self MainMenu("GiveB3 List", "GiveB List");
	self MenuOption("GiveB3 List", 0, "Explosive Bullets", ::giveBoxExBu);
	self MenuOption("GiveB3 List", 1, "EMP Bullets", ::giveBoxEMP);
	self MenuOption("GiveB3 List", 2, "Modded Bullets", ::giveBoxMgBl);
	self MenuOption("GiveB3 List", 3, "Rocket Teleporter", ::giveBoxRPG);
	self MenuOption("GiveB3 List", 4, "Jericho Missiles", ::giveBoxJMis);
	
	self MainMenu("GiveB4 List", "GiveB List");
	self MenuOption("GiveB4 List", 0, "Drivable Car", ::giveBoxCar);
	self MenuOption("GiveB4 List", 1, "Ace Combat", ::giveBoxAC);
	self MenuOption("GiveB4 List", 2, "Pilot Aircraft", ::giveBoxHeli);
	
	self MainMenu("Heli List", "Sub Menu 9");
	self MenuOption("Heli List", 0, "^5-Public-"); 
	self MenuOption("Heli List", 1, "^3Spawn Helicopter", ::initPilotHeli); 
	self MenuOption("Heli List", 2, "^7Overwatch", ::PHeliModellb);
	self MenuOption("Heli List", 3, "Attack Heli", ::PHeliModelah);
	self MenuOption("Heli List", 4, "A10 Thunderbolt", ::PHeliModela10);
	self MenuOption("Heli List", 5, "Pegasus", ::PHeliModelstlh);
	self MenuOption("Heli List", 6, "^5-Self-"); 
	self MenuOption("Heli List", 7, "^3Spawn Helicopter", ::initPilotHeliMe); 
	self MenuOption("Heli List", 8, "^7Overwatch", ::PHeliModellbMe);
	self MenuOption("Heli List", 9, "Attack Heli", ::PHeliModelahMe);
	self MenuOption("Heli List", 10, "A10 Thunderbolt", ::PHeliModela10Me);
	self MenuOption("Heli List", 11, "Pegasus", ::PHeliModelstlhMe);
	self MenuOption("Heli List", 12, "VTOL Warship", ::PHeliModelvtolMe);
	self MenuOption("Heli List", 13, "FA38", ::PHeliModelfaMe);
	self MenuOption("Heli List", 14, "C-UAV", ::PHeliModelcuavMe);

	self MainMenu("Turret List", "Sub Menu 9");
	self MenuOption("Turret List", 0, "Projectiles: Turret", ::spawnturret1);
	self MenuOption("Turret List", 1, "Projectiles: Hellstorm", ::spawnturret2);
	self MenuOption("Turret List", 2, "Projectiles: Warthog", ::spawnturret3);
	self MenuOption("Turret List", 3, "Projectiles: Chopper Gunner", ::spawnturret4);
	
	self MainMenu("SpawnB List", "Sub Menu 9");
	self MenuOption("SpawnB List", 0, "^3On/Off Projectiles", ::initSpawnBullet);
	self MenuOption("SpawnB List", 1, "^7Carepackage (Friendly)", ::carepBullets);
	self MenuOption("SpawnB List", 2, "Carepackage (Enemy)", ::redcareBullets);
	self MenuOption("SpawnB List", 3, "Carepackage (Detect)", ::detcareBullets);
	self MenuOption("SpawnB List", 4, "Carepackage (HQ)", ::hqcareBullets);
	self MenuOption("SpawnB List", 5, "A.G.R Drone", ::agrBullets);
	self MenuOption("SpawnB List", 6, "Drone Package", ::droneBullets);
	self MenuOption("SpawnB List", 7, "Debug Model", ::defacBullets);
	self MenuOption("SpawnB List", 8, "Dog", ::dogBullets);
	self MenuOption("SpawnB List", 9, "Sentry Gun", ::turretBullets);
	self MenuOption("SpawnB List", 10, "Little Bird", ::lbirdBullets);
	self MenuOption("SpawnB List", 11, "Stealth Bomber", ::sbombBullets);
	self MenuOption("SpawnB List", 12, "VTOL Warship", ::vtolBullets);

	self MainMenu("Jet List", "Sub Menu 9");
	self MenuOption("Jet List", 0, "^5--Public--");
	self MenuOption("Jet List", 1, "^3Spawn Jet", ::initFlyableJet);
	self MenuOption("Jet List", 2, "^7A10 Thunderbolt", ::setFJetMatb);
	self MenuOption("Jet List", 3, "Lightning Strike", ::setFJetMharr);
	self MenuOption("Jet List", 4, "Stealth Bomber", ::setFJetMstb);
	self MenuOption("Jet List", 5, "UAV", ::setFJetMuav);
	self MenuOption("Jet List", 6, "VTOL Warship", ::setFJetMvtol);
	self MenuOption("Jet List", 7, "^5--Self--");
	self MenuOption("Jet List", 8, "^3Spawn Jet", ::initFlyableJetMe);
	self MenuOption("Jet List", 9, "^7A10 Thunderbolt", ::setFJetMatbMe);
	self MenuOption("Jet List", 10, "Lightning Strike", ::setFJetMharrMe);
	self MenuOption("Jet List", 11, "Stealth Bomber", ::setFJetMstbMe);
	self MenuOption("Jet List", 12, "Counter UAV", ::setFJetMcuav);
	
	self MainMenu("Sub Menu 10", "Main Menu");
	self MenuOption("Sub Menu 10", 0, "Set Prestige 11th", ::doMaster);
	self MenuOption("Sub Menu 10", 1, "Set Level 55", ::doRank);
	self MenuOption("Sub Menu 10", 2, "Unlock All Trophys", ::unlockAllCheevos);
	self MenuOption("Sub Menu 10", 3, "Unlock Camos", ::doAllUnlockCamos);
	self MenuOption("Sub Menu 10", 4, "Colored Classes", ::ColoredClass);
	self MenuOption("Sub Menu 10", 5, "Derank", ::selfDerank);

	self MainMenu("Sub Menu 11", "Main Menu");
	self MenuOption("Sub Menu 11", 0, "^2Game Settings", ::SubMenu, "Game Setting");
	self MenuOption("Sub Menu 11", 1, "bot Settings", ::SubMenu, "bot Setting");
	self MenuOption("Sub Menu 11", 2, "Do-Heart Settings", ::SubMenu, "DoH List");
	self MenuOption("Sub Menu 11", 3, "Custom Gamemode", ::SubMenu, "Gametype List");
	self MenuOption("Sub Menu 11", 4, "Change Maps", ::SubMenu, "Map List");
	self MenuOption("Sub Menu 11", 5, "^7Fast Restart", ::doFastRestart);
	self MenuOption("Sub Menu 11", 6, "^1E^0N^1D G^0A^1M^0E", ::EndGame);
	self MenuOption("Sub Menu 11", 7, "^3S^5tuf^1f ^3R^5ol^1l", ::initCredit);
	
	self MainMenu("bot Setting", "Sub Menu 11");
	self MenuOption("bot Setting", 0, "Spawn bot", ::SpawnBot("autoassign"));
	self MenuOption("bot Setting", 1, "Kick All bots", ::kickAllBots);
	
	self MainMenu("DoH List", "Sub Menu 11");
	self MenuOption("DoH List", 0, "Lobby Info Do Heart V1", ::doTradeMark);
	self MenuOption("DoH List", 1, "MW2 Type Hostname Do Heart V2", ::tgHeart);
	self MenuOption("DoH List", 2, "Introduction Do Heart V3", ::doHeartx);
	self MenuOption("DoH List", 3, "Spinning ^1" + level.hostname, ::InitSpinText);
	self MenuOption("DoH List", 4, "^7Patch Name Scrolltext", ::initScrollDH);
	self MenuOption("DoH List", 5, "^525 ^3Niconico Mode ^525", ::initNiconico);

	self MainMenu("Game Setting", "Sub Menu 11");
	self MenuOption("Game Setting", 0, "Super Jump", ::ToggleSuperJump);
	self MenuOption("Game Setting", 1, "Super Speed", ::lobbySpeed);
	self MenuOption("Game Setting", 2, "Moon Gravity", ::initGravity);
	self MenuOption("Game Setting", 3, "Timescale Change", ::doSpeedX2);
	self MenuOption("Game Setting", 4, "Ranked Match", ::ToggleRanked);
	self MenuOption("Game Setting", 5, "Unlimited Game", ::InfGame);
	self MenuOption("Game Setting", 6, "Super Rappid Fire", ::rapidFire);
	self MenuOption("Game Setting", 7, "Long Knife", ::initMRange);
	self MenuOption("Game Setting", 8, "Remove Death Barrier", ::deathBarrier);
	self MenuOption("Game Setting", 9, "Rocket Rain", ::initRocketRain);
	self MenuOption("Game Setting", 10, "VoiceChat Jack", ::hearETlobby);
	self MenuOption("Game Setting", 11, "Camper Kill", ::initCampKill);
	self MenuOption("Game Setting", 12, "XP Lobby", ::initXPLobby);

	self MainMenu("Gametype List", "Sub Menu 11");
	self MenuOption("Gametype List", 0, "Sniper Lobby", ::initSniperLobby);
	self MenuOption("Gametype List", 1, "Nomal Lobby", ::initNomalLobby);
	
	self MainMenu("Map List", "Sub Menu 11");
	self MenuOption("Map List", 0, "Nuketown", ::Nuketown);
	self MenuOption("Map List", 1, "Hijacked", ::Hijacked);
	self MenuOption("Map List", 2, "Express", ::Express);
	self MenuOption("Map List", 3, "Meltdown", ::Meltdown);
	self MenuOption("Map List", 4, "Drone", ::Drone);
	self MenuOption("Map List", 5, "Carrier", ::Carrier);
	self MenuOption("Map List", 6, "Overflow", ::Overflow);
	self MenuOption("Map List", 7, "Slums", ::Slums);
	self MenuOption("Map List", 8, "Turbine", ::Turbine);
	self MenuOption("Map List", 9, "Raid", ::Raid);
	self MenuOption("Map List", 10, "Aftermath", ::Aftermath);
	self MenuOption("Map List", 11, "Cargo", ::Cargo);
	self MenuOption("Map List", 12, "Standoff", ::Standoff);
	self MenuOption("Map List", 13, "Plaza", ::Plaza);
	self MenuOption("Map List", 14, "Yemen", ::Yemen);
	self MenuOption("Map List", 15, "^2DLC Maps", ::SubMenu, "DLC List");
	
	self MainMenu("DLC List", "Sub Menu 11");
	self MenuOption("DLC List", 0, "Dig", ::mp_dig);
	self MenuOption("DLC List", 1, "Pod", ::mp_pod);
	self MenuOption("DLC List", 2, "Takeoff", ::mp_takeoff);
	self MenuOption("DLC List", 3, "Frost", ::mp_frostbite);
	self MenuOption("DLC List", 4, "Mirage", ::mp_mirage);
	self MenuOption("DLC List", 5, "Hydro", ::mp_hydro);
	self MenuOption("DLC List", 6, "Grind", ::mp_skate);
	self MenuOption("DLC List", 7, "Downhill", ::mp_downhill);
	self MenuOption("DLC List", 8, "Encore", ::mp_concert);
	self MenuOption("DLC List", 9, "Vertigo", ::mp_vertigo);
	self MenuOption("DLC List", 10, "Magma", ::mp_magma);
	self MenuOption("DLC List", 11, "Studio", ::mp_studio);
	self MenuOption("DLC List", 12, "Rush", ::mp_paintball);
	self MenuOption("DLC List", 13, "Cove", ::mp_castaway);
	self MenuOption("DLC List", 14, "Detour", ::mp_bridge);
	self MenuOption("DLC List", 15, "Uplink", ::mp_uplink);

	self MainMenu("Sub Menu 12", "Main Menu");
	self MenuOption("Sub Menu 12", 0, "Force Host", ::forcehost);

	self MainMenu("Clients Menu", "Main Menu");
	for (p = 0; p < level.players.size; p++)
	{
		player = level.players[p];
		name = player getName();
		self MenuOption("Clients Menu", p, player.MyAccess + " ^7" + name, ::SubMenu, "Client Function");
	}
	self thread MonitorPlayers();
	
	self MainMenu("Client Function", "Clients Menu");
	self MenuOption("Client Function", 0, "^6Verify Player", ::Verify);
	self MenuOption("Client Function", 1, "^3VIP Player", ::doVIP);
	self MenuOption("Client Function", 2, "^1Admin Player", ::doAdmin);
	self MenuOption("Client Function", 3, "^5Co-Host Player", ::doCoHost);
	self MenuOption("Client Function", 4, "^4Unverified Player", ::doUnverif);
	self MenuOption("Client Function", 5, "^7-----");
	self MenuOption("Client Function", 6, "Teleport to me", ::doTeleportToMe);
	self MenuOption("Client Function", 7, "Teleport to him", ::doTeleportToHim);
	self MenuOption("Client Function", 8, "Kick Player", ::doKickPlayer);
	self MenuOption("Client Function", 9, "^2Basic Cheats", ::SubMenu, "Player Basic");
	self MenuOption("Client Function", 10, "Funny Mods", ::SubMenu, "Player Funny");
	self MenuOption("Client Function", 11, "Strong Hacks", ::SubMenu, "Player Strong");
	
	self MainMenu("Player Basic", "Client Function");
	self MenuOption("Player Basic", 0, "God Mode", ::playerGod);
	self MenuOption("Player Basic", 1, "Infinity Ammo", ::playerInfa);
	self MenuOption("Player Basic", 2, "Invisible", ::playerHide);
	self MenuOption("Player Basic", 3, "Set All Perks", ::playerPerk);
	self MenuOption("Player Basic", 4, "Always UAV", ::playerUAV);
	self MenuOption("Player Basic", 5, "Walk Speed Change", ::playerSpeed);
	self MenuOption("Player Basic", 6, "Give Death Machine", ::playerDMachi);
	self MenuOption("Player Basic", 7, "Give Random Weapons", ::playerRWeap);
	self MenuOption("Player Basic", 8, "Team Change", ::playerTChange);
	self MenuOption("Player Basic", 9, "Suicide", ::playerDeath);
	
	self MainMenu("Player Funny", "Client Function");
	self MenuOption("Player Funny", 0, "Advanced No Clip", ::playerNoclip);
	self MenuOption("Player Funny", 1, "Mulit Jump", ::playerMJump);
	self MenuOption("Player Funny", 2, "Ninja Mode", ::playerNinja);
	self MenuOption("Player Funny", 3, "Smoke Monster", ::playerSmokeM);
	self MenuOption("Player Funny", 4, "Forge Mode", ::playerForge);
	self MenuOption("Player Funny", 5, "Advanced Forge Mode", ::playerAdvFor);
	self MenuOption("Player Funny", 6, "Drivable Car", ::playerDCar);
	self MenuOption("Player Funny", 7, "Ace Combat", ::playerJet);
	self MenuOption("Player Funny", 8, "Pilot Aircraft", ::playerHeli);
	
	self MainMenu("Player Strong", "Client Function");
	self MenuOption("Player Strong", 0, "Explosive Bullets", ::playerExBul);
	self MenuOption("Player Strong", 1, "Modded Bullets", ::playerMGB);

	self MainMenu("All Clients", "Main Menu");
	self MenuOption("All Clients", 0, "God Mode", ::doGodAllPlayer);
	self MenuOption("All Clients", 1, "Infinity Ammo", ::doInfAmmAllPlayer);
	self MenuOption("All Clients", 2, "Advanced Noclip", ::doNocAllPlayer);
	self MenuOption("All Clients", 3, "Advanced Forge Mode", ::APadvForge);
	self MenuOption("All Clients", 4, "Explosive Bullets", ::doExpBulAllPlayer);
	self MenuOption("All Clients", 5, "Give Death Machine", ::doGiveDMAllPlayer);
	self MenuOption("All Clients", 6, "Take All Weapons", ::APtakeWeapon);
	self MenuOption("All Clients", 7, "Max Rank", ::maxAllRank);
	self MenuOption("All Clients", 8, "Give Admin", ::playerAdmin);
	self MenuOption("All Clients", 9, "Give Unverified", ::playerUnv);
	self MenuOption("All Clients", 10, "Freeze", ::doFreezeAllPlayer);
	self MenuOption("All Clients", 11, "Kill All", ::AllPlayersKilled);
	self MenuOption("All Clients", 12, "Anti-Quit", ::doAntiQuitAllPlayer);
	self MenuOption("All Clients", 13, "Teleport to me", ::AllTeleportToMe);
	self MenuOption("All Clients", 14, "Teleport to Crosshair", ::teleToCrosshairs);

	self MainMenu("Sub Menu 13", "Main Menu");
	self MenuOption("Sub Menu 13", 0, "^5Sky Marine Style", ::menuSky);
	self MenuOption("Sub Menu 13", 1, "^1Crimson Style", ::menuCrimson);
	self MenuOption("Sub Menu 13", 2, "^3Electronic Style", ::menuElectro);
	self MenuOption("Sub Menu 13", 3, "^4Daemon Style", ::menuDaemon);
	self MenuOption("Sub Menu 13", 4, "^23-Prism Style", ::menuPrism);
	self MenuOption("Sub Menu 13", 5, "^17^2t^3h ^4A^5r^6t ^7S^1t^2y^3l^4e", ::domenuRain);
	self MenuOption("Sub Menu 13", 6, "^7Revolution Style", ::menuRevo);
	self MenuOption("Sub Menu 13", 7, "NextGenUpdate Style", ::menuNgu);
	self MenuOption("Sub Menu 13", 8, "Default Style", ::menuDefault);

	self MainMenu("Sub Menu 14", "Main Menu");
	self MenuOption("Sub Menu 14", 0, "Japanese", ::changeJap);
	self MenuOption("Sub Menu 14", 1, "English", ::changeEng);
}

MenuStructure_JP()
{
	self endon("change_Jap");
	self endon("change_Eng");
	if (self.Verified == true)
	{
		self MainMenu("Main Menu", undefined);
		self MenuOption("Main Menu", 0, "Yowai Ti-to", ::SubMenu, "Sub Menu 3");
		self MenuOption("Main Menu", 1, "Kaiwa", ::SubMenu, "Sub Menu 4");
		self MenuOption("Main Menu", 2, "Iro wo Henkou", ::SubMenu, "Sub Menu 13");
		self MenuOption("Main Menu", 3, "Gengo Settei", ::SubMenu, "Sub Menu 14");
	}
	if (self.VIP == true)
	{
		self MenuOption("Main Menu", 4, "Omoshiroi Ti-to", ::SubMenu, "Sub Menu 2");
		self MenuOption("Main Menu", 5, "Hutuu no Ti-to", ::SubMenu, "Sub Menu 6 (Admin)");
		self MenuOption("Main Menu", 6, "Account Hack", ::SubMenu, "Sub Menu 10");
	}
	if (self.Admin == true)
	{
		self MenuOption("Main Menu", 7, "Buki", ::SubMenu, "Sub Menu 5 (VIP)");
		self MenuOption("Main Menu", 8, "Tuyoi Ti-to", ::SubMenu, "Sub Menu 7 (Host)");
	}
	if (self.CoHost == true)
	{
		self MenuOption("Main Menu", 9, "Yabai Ti-to", ::SubMenu, "Sub Menu 8");
		self MenuOption("Main Menu", 10, "Ie Tsukuri", ::SubMenu, "Forge Menu");
		self MenuOption("Main Menu", 11, "Object Seisei", ::SubMenu, "Sub Menu 9");
		self MenuOption("Main Menu", 12, "Tanin", ::SubMenu, "Clients Menu");
	}
	if (self.Host == true)
	{
		self MenuOption("Main Menu", 13, "Zennin", ::SubMenu, "All Clients");
		self MenuOption("Main Menu", 14, "Heya Zentai", ::SubMenu, "Sub Menu 11");
		self MenuOption("Main Menu", 15, "Host Nomi", ::SubMenu, "Sub Menu 12");
	}

	self MainMenu("Sub Menu 2", "Main Menu");
	self MenuOption("Sub Menu 2", 0, "^2Gasitu Henkou", ::SubMenu, "Visions List");
	self MenuOption("Sub Menu 2", 1, "Sugata Henkou", ::SubMenu, "Models List");
	self MenuOption("Sub Menu 2", 2, "^7Team Henkou", ::initTeamChange);
	self MenuOption("Sub Menu 2", 3, "Clone wo Tukuru", ::ClonePlayer);
	self MenuOption("Sub Menu 2", 4, "Zisin", ::Quake);
	self MenuOption("Sub Menu 2", 5, "Teleport Hozon Siki", ::saveandload);
	self MenuOption("Sub Menu 2", 6, "Jump x999", ::Toggle_Multijump);
	self MenuOption("Sub Menu 2", 7, "Aim saki ni Teleport", ::TpToCrHr);
	self MenuOption("Sub Menu 2", 8, "RPG de Teleporter", ::initRocketTeleport);
	self MenuOption("Sub Menu 2", 9, "Grenade de Teleport", ::initSpecNade);
	self MenuOption("Sub Menu 2", 10, "Riot Man", ::initRiotMan);
	self MenuOption("Sub Menu 2", 11, "Bakudan Setti (^1S&D^7)", ::PlantBomb);
	self MenuOption("Sub Menu 2", 12, "Bakudan Kaijo (^1S&D^7)", ::DefuseBomb);

	self MainMenu("Visions List", "Sub Menu 2");
	self MenuOption("Visions List", 0, "EMP", ::empV);
	self MenuOption("Visions List", 1, "Thermal", ::Thermalv);
	self MenuOption("Visions List", 2, "Black and White", ::BWV);
	self MenuOption("Visions List", 3, "Light", ::LVis);
	self MenuOption("Visions List", 4, "Enhanced", ::EV);
	
	self MainMenu("Models List", "Sub Menu 2");
	self MenuOption("Models List", 0, "Default Model", ::setDefoModel);
	self MenuOption("Models List", 1, "Debug Model", ::SetModelDefoact);
	self MenuOption("Models List", 2, "Dog", ::SetModelDog);
	self MenuOption("Models List", 3, "Trophy System", ::SetModelTrosys);
	self MenuOption("Models List", 4, "Assault Drone", ::SetModelAssaDro);
	self MenuOption("Models List", 5, "Sentry Gun", ::SetModelTurret);
	self MenuOption("Models List", 6, "Care Package", ::SetModelCareP);
	self MenuOption("Models List", 7, "Hunter Killer", ::SetModelHKiller);
	self MenuOption("Models List", 8, "UAV", ::SetModelUAV);
	self MenuOption("Models List", 9, "Little Bird", ::SetModelOverwatch);
	self MenuOption("Models List", 10, "Attack Helicopter", ::SetModelAttackHeli);
	self MenuOption("Models List", 11, "VTOL Warship", ::SetModelOspley);
	self MenuOption("Models List", 12, "Stealth Bomber", ::SetModelStealth);
	self MenuOption("Models List", 13, "Harrier", ::SetModelHarrier);
	
	self MainMenu("Sub Menu 3", "Main Menu");
	self MenuOption("Sub Menu 3", 0, "Zyouzi UAV", ::doUAV);
	self MenuOption("Sub Menu 3", 1, "Zen Perks Get", ::setAllPerks);
	self MenuOption("Sub Menu 3", 2, "3rd Person", ::giveTP);
	self MenuOption("Sub Menu 3", 3, "Class wo Henkou", ::ChangeClass);
	self MenuOption("Sub Menu 3", 4, "Tama Kaihuku", ::giveMaxAmmo);
	self MenuOption("Sub Menu 3", 5, "Auto de Huseuti", ::AutoDropshot);
	self MenuOption("Sub Menu 3", 6, "HP Hyouzi", ::initHealthBar);
	self MenuOption("Sub Menu 3", 7, "Zen Perks Sakujo", ::doClearPerks);
	self MenuOption("Sub Menu 3", 8, "Zisatu", ::doSuicide);
	
	self MainMenu("Sub Menu 4", "Main Menu");
	self MenuOption("Sub Menu 4", 0, "^5Kono Koumoku ha Zennin ni Miemasu");
	self MenuOption("Sub Menu 4", 1, "^7Kono Mod Menu wo Syoukai", ::doChatPatchInfo);
	self MenuOption("Sub Menu 4", 2, "NextGenUpdate ni Tuite", ::doChatGSCTalk);
	self MenuOption("Sub Menu 4", 3, "Ziko Syoukai ^1" + self.name, ::doChatMyIntro);
	self MenuOption("Sub Menu 4", 4, "^7Host no Zyouhou", ::doChatLobbyHost);
	self MenuOption("Sub Menu 4", 5, "^5--Fake Typewriter--");
	self MenuOption("Sub Menu 4", 6, "RTE de Host no Namae wo Kaetene");
	self MenuOption("Sub Menu 4", 7, "^7Typewriter", ::doChatTypewriter);
	
	self MainMenu("Sub Menu 5 (VIP)", "Main Menu");
	self MenuOption("Sub Menu 5 (VIP)", 0, "^2Buki wo Nyuusyu", ::SubMenu, "Weapons List");
	self MenuOption("Sub Menu 5 (VIP)", 1, "^7Buki wo Nakusu", ::TakeWeapon);
	self MenuOption("Sub Menu 5 (VIP)", 2, "^2Tama Henkou", ::SubMenu, "Bullets List");
	self MenuOption("Sub Menu 5 (VIP)", 3, "Tama Henkou V2", ::SubMenu, "LTBullets List");
	self MenuOption("Sub Menu 5 (VIP)", 4, "Effect wo Utidasu", ::SubMenu, "EffectB List");
	self MenuOption("Sub Menu 5 (VIP)", 5, "^7Teleport Zyuu", ::ToggleTeleportGun);
	self MenuOption("Sub Menu 5 (VIP)", 6, "Zisin Zyuu", ::doEarthQGun);
	self MenuOption("Sub Menu 5 (VIP)", 7, "Thunder Gun", ::ThunGun);
	
	self MainMenu("Bullets List", "Sub Menu 5 (VIP)");
	self MenuOption("Bullets List", 0, "^3Tama no On/Off", ::initMagicBullet);
	self MenuOption("Bullets List", 1, "^7R-870 MCS", ::selectMBmcs);
	self MenuOption("Bullets List", 2, "SMAW", ::selectMBsmaw);
	self MenuOption("Bullets List", 3, "Grenade", ::selectMBgrenade);
	self MenuOption("Bullets List", 4, "A.G.R Rocket", ::selectMBagr);
	self MenuOption("Bullets List", 5, "Warthog Rocket", ::selectMBwarthog);
	self MenuOption("Bullets List", 6, "Loadstar", ::selectMBlstar);
	self MenuOption("Bullets List", 7, "Mortar Missile Burner", ::selectMBburner);
	self MenuOption("Bullets List", 8, "Remote Mortar Missile", ::selectMBrmmm);
	self MenuOption("Bullets List", 9, "Heli Gunner Missile", ::selectMBhgr);
	self MenuOption("Bullets List", 10, "Swarm", ::selectMBswarm);
	self MenuOption("Bullets List", 11, "Hanter Killer", ::selectMBhkill);
	
	self MainMenu("LTBullets List", "Sub Menu 5 (VIP)");
	self MenuOption("LTBullets List", 0, "^3Tama no On/Off", ::initMagicGrenade);
	self MenuOption("LTBullets List", 1, "^7Frag", ::selectMLTfrag);
	self MenuOption("LTBullets List", 2, "Semtex", ::selectMLTstick);
	self MenuOption("LTBullets List", 3, "Concussion", ::selectMLTconc);
	self MenuOption("LTBullets List", 4, "Flash", ::selectMLTflash);
	self MenuOption("LTBullets List", 5, "EMP", ::selectMLTemp);
	self MenuOption("LTBullets List", 6, "Smoke Grenade", ::selectMLTbetty);
	self MenuOption("LTBullets List", 7, "Sensor", ::selectMLTsensor);
	self MenuOption("LTBullets List", 8, "C4", ::selectMLTshock);
	self MenuOption("LTBullets List", 9, "Claymore", ::selectMLTclaym);
	self MenuOption("LTBullets List", 10, "Trophy System", ::selectMLTtrosy);
	self MenuOption("LTBullets List", 11, "C-Axe", ::selectMLTaxe);
	self MenuOption("LTBullets List", 12, "Shock Charge", ::selectMLTc4);

	self MainMenu("Weapons List", "Sub Menu 5 (VIP)");
	self MenuOption("Weapons List", 0, "Death Machine", ::giveWdmachine);
	self MenuOption("Weapons List", 1, "War Machine", ::giveWWMachine);
	self MenuOption("Weapons List", 2, "AN-94", ::giveWan);
	self MenuOption("Weapons List", 3, "LSAT", ::giveWlsat);
	self MenuOption("Weapons List", 4, "Peacekeeper", ::giveWpkeep);
	self MenuOption("Weapons List", 5, "SCAR-H", ::giveWscar);
	self MenuOption("Weapons List", 6, "Balista", ::giveWbalista);
	self MenuOption("Weapons List", 7, "DSR 50", ::giveWdsr);
	self MenuOption("Weapons List", 8, "R-870 MCS", ::giveWmcs);
	self MenuOption("Weapons List", 9, "Crossbow", ::giveWcrsb);
	self MenuOption("Weapons List", 10, "RPG", ::giveWrpg);
	self MenuOption("Weapons List", 11, "Random de Nyuusyu", ::giveRWeapon);
	self MenuOption("Weapons List", 12, "Default Weapon", ::giveWdefowep);
	
	self MainMenu("EffectB List", "Sub Menu 5 (VIP)");
	self MenuOption("EffectB List", 0, "Bakuhatu", ::ExpBultOn);
	self MenuOption("EffectB List", 1, "Syougeki-Ha", ::initNonFXExpBult);
	self MenuOption("EffectB List", 2, "Mizu Zokusei", ::initWGun);
	self MenuOption("EffectB List", 3, "EMP", ::initEMPBullets);
	self MenuOption("EffectB List", 4, "Nuke (^1Nuketown^7)", ::initNukeBullets);

	self MainMenu("Sub Menu 6 (Admin)", "Main Menu");
	self MenuOption("Sub Menu 6 (Admin)", 0, "^2Killstreaks wo Get", ::SubMenu, "Kstreak List");
	self MenuOption("Sub Menu 6 (Admin)", 1, "^7Killstreaks Mugen", ::doKillstreaks);
	self MenuOption("Sub Menu 6 (Admin)", 2, "Zyouzi VSAT", ::alwaysVSAT);
	self MenuOption("Sub Menu 6 (Admin)", 3, "Ugoku Speed Henkou", ::doClientsSpeed);
	self MenuOption("Sub Menu 6 (Admin)", 4, "Ninja Mode", ::doNinja);
	self MenuOption("Sub Menu 6 (Admin)", 5, "iPad de Teleport", ::TeleportWithiPad);
	self MenuOption("Sub Menu 6 (Admin)", 6, "Jet Pack", ::doJetPack);
	self MenuOption("Sub Menu 6 (Admin)", 7, "Aruku Loadstar", ::walkingLoadestar);
	self MenuOption("Sub Menu 6 (Admin)", 8, "Honoo no Karada", ::initHTorch);
	self MenuOption("Sub Menu 6 (Admin)", 9, "Mizu Sibuki", ::initWFountain);
	self MenuOption("Sub Menu 6 (Admin)", 10, "Smoke Zigoku", ::initSmokeMonster);

	self MainMenu("Kstreak List", "Sub Menu 6 (Admin)");
	self MenuOption("Kstreak List", 0, "UAV", ::KSGiveUAV);
	self MenuOption("Kstreak List", 1, "RC-XD", ::KSGiveRC);
	self MenuOption("Kstreak List", 2, "Hunter Killer", ::KSGiveHunt);
	self MenuOption("Kstreak List", 3, "Care Package", ::KSGiveCare);
	self MenuOption("Kstreak List", 4, "Counter UAV", ::KSGiveCUAV);
	self MenuOption("Kstreak List", 5, "Gaurdian", ::KSGiveGaurd);
	self MenuOption("Kstreak List", 6, "Hellstorm Missile", ::KSGiveHell);
	self MenuOption("Kstreak List", 7, "Lightning Strike", ::KSGiveLS);
	self MenuOption("Kstreak List", 8, "Sentry Gun", ::KSGiveSG);
	self MenuOption("Kstreak List", 9, "A.G.R", ::KSGiveAG);
	self MenuOption("Kstreak List", 10, "Stealth Chopper", ::KSGiveSC);
	self MenuOption("Kstreak List", 11, "Orbital VSAT", ::KSGiveVSAT);
	self MenuOption("Kstreak List", 12, "Escort Drone", ::KSGiveED);
	self MenuOption("Kstreak List", 13, "EMP System", ::KSGiveEMP);
	self MenuOption("Kstreak List", 14, "Warthog", ::KSGiveWH);
	self MenuOption("Kstreak List", 15, "Loadestar", ::KSGiveLST);
	self MenuOption("Kstreak List", 16, "VTOL Warship", ::KSGiveVW);
	self MenuOption("Kstreak List", 17, "Swarm", ::KSGiveSwarm);
	
	self MainMenu("Sub Menu 7 (Host)", "Main Menu");
	self MenuOption("Sub Menu 7 (Host)", 0, "Muteki", ::giveGod);
	self MenuOption("Sub Menu 7 (Host)", 1, "Tama Mugen", ::doInfAmmo);
	self MenuOption("Sub Menu 7 (Host)", 2, "Toumei", ::InvisibleOn);
	self MenuOption("Sub Menu 7 (Host)", 3, "Sora wo Tobu", ::doNoClip);
	self MenuOption("Sub Menu 7 (Host)", 4, "Mono wo Hakobu", ::ForgeON);
	self MenuOption("Sub Menu 7 (Host)", 5, "Sora wo Tobu V2", ::UFOMode);
	self MenuOption("Sub Menu 7 (Host)", 6, "^2Auto Aim Settei", ::SubMenu, "Aimbot List");

	self MainMenu("Aimbot List", "Sub Menu 7 (Host)");
	self MenuOption("Aimbot List", 0, "Auto Aim On/Off", ::initEnstoneAimbot);
	self MenuOption("Aimbot List", 1, "Aim sitara Hatudou", ::aimingMethod);
	self MenuOption("Aimbot List", 2, "Aim Basyo wo Henkou", ::changeAimingPos);
	self MenuOption("Aimbot List", 3, "Barenikui Auto Aim", ::doStealthAimbots);
	
	self MainMenu("Sub Menu 8", "Main Menu");
	self MenuOption("Sub Menu 8", 0, "Saikyou no Auto Aim", ::switchUnfairAimbot);
	self MenuOption("Sub Menu 8", 1, "Kamikaze Tokkoutai", ::kamikaze);
	self MenuOption("Sub Menu 8", 2, "Missile Touka", ::JeriMissOn);
	self MenuOption("Sub Menu 8", 3, "Strafe Run", ::doStrafeRunz);
	self MenuOption("Sub Menu 8", 4, "Pokemon", ::pokeBall);
	self MenuOption("Sub Menu 8", 5, "L1 de Slow Motion", ::initMatrix);
	self MenuOption("Sub Menu 8", 6, "Tune ni Zidou Teleport", ::initAPulTele);
	self MenuOption("Sub Menu 8", 7, "Stealth Bind", ::initStlhBind);
	
	self MainMenu("Forge Menu", "Main Menu");
	self MenuOption("Forge Menu", 0, "Minecraft Mode", ::ForgeMode);
	self MenuOption("Forge Menu", 1, "Subayaku Mono wo Kesu", ::initFastDelete);
	self MenuOption("Forge Menu", 2, "Waorzone wo Tukuru", ::initTeletoFlag);
	self MenuOption("Forge Menu", 3, "Kaidan wo Tukuru", ::ForgeRamp);
	self MenuOption("Forge Menu", 4, "Kabe wo Tukuru", ::ForgeWall);
	self MenuOption("Forge Menu", 5, "Yuka wo Tukuru", ::ForgeGrids);
	self MenuOption("Forge Menu", 6, "Ie", ::initSpawnBunker);
	self MenuOption("Forge Menu", 7, "Huyuu Yousai", ::initSkyPlaza);
	self MenuOption("Forge Menu", 8, "Rougoku", ::initPrison);
	self MenuOption("Forge Menu", 9, "Sokuseki Kaidan", ::Escalatore);

	self MainMenu("Sub Menu 9", "Main Menu");
	self MenuOption("Sub Menu 9", 0, "^2Turrets", ::SubMenu, "Turret List");
	self MenuOption("Sub Menu 9", 1, "Object wo Utidasu", ::SubMenu, "SpawnB List");
	self MenuOption("Sub Menu 9", 2, "Hako kara Ti-to", ::SubMenu, "GiveB List");
	self MenuOption("Sub Menu 9", 3, "^7Carepackages wo Utidasu", ::doCpGunBeta);
	self MenuOption("Sub Menu 9", 4, "Zirai", ::doMineSpawner);
	self MenuOption("Sub Menu 9", 5, "Zidou Kill", ::IMSMW3);
	self MenuOption("Sub Menu 9", 6, "Kuruma wo Unten", ::spawnDrivableCar);
	self MenuOption("Sub Menu 9", 7, "Helicopter wo Seigyo", ::CareHeli);
	self MenuOption("Sub Menu 9", 8, "^2Ace Combat", ::SubMenu, "Jet List");
	self MenuOption("Sub Menu 9", 9, "Hikouki Souzyuu", ::SubMenu, "Heli List");
	
	self MainMenu("GiveB List", "Sub Menu 9");
	self MenuOption("GiveB List", 0, "^2Hutuu no Ti-to", ::SubMenu, "GiveB1 List");
	self MenuOption("GiveB List", 1, "Omoshiroi Ti-to", ::SubMenu, "GiveB2 List");
	self MenuOption("GiveB List", 2, "Buki", ::SubMenu, "GiveB3 List");
	self MenuOption("GiveB List", 3, "Sonota", ::SubMenu, "GiveB4 List");
	
	self MainMenu("GiveB1 List", "GiveB List");
	self MenuOption("GiveB1 List", 0, "Muteki", ::giveBoxGod);
	self MenuOption("GiveB1 List", 1, "Tama Mugen", ::giveBoxInf);
	self MenuOption("GiveB1 List", 2, "3rd Person", ::giveBox3rd);
	self MenuOption("GiveB1 List", 3, "Thermal Vision", ::giveBoxNV);
	self MenuOption("GiveB1 List", 4, "Aruku Speed Henkou", ::giveBoxWalk);
	self MenuOption("GiveB1 List", 5, "Buki wo Random de Get", ::giveBoxRWep);
	self MenuOption("GiveB1 List", 6, "HP Hyouzi", ::giveBoxDHP);
	
	self MainMenu("GiveB2 List", "GiveB List");
	self MenuOption("GiveB2 List", 0, "Sora wo Tobu", ::giveBoxNoc);
	self MenuOption("GiveB2 List", 1, "Minecraft Mode", ::giveBoxForg);
	self MenuOption("GiveB2 List", 2, "Mugen Jump", ::giveBoxJump);
	self MenuOption("GiveB2 List", 3, "Ninja Mode", ::giveBoxNinj);
	self MenuOption("GiveB2 List", 4, "Honoo no Karada", ::giveBoxFire);
	
	self MainMenu("GiveB3 List", "GiveB List");
	self MenuOption("GiveB3 List", 0, "Bakuhatu suru Tama", ::giveBoxExBu);
	self MenuOption("GiveB3 List", 1, "EMP wo Utidasu", ::giveBoxEMP);
	self MenuOption("GiveB3 List", 2, "Tama wo Kakikaeru", ::giveBoxMgBl);
	self MenuOption("GiveB3 List", 3, "RPG de Teleporter", ::giveBoxRPG);
	self MenuOption("GiveB3 List", 4, "Missile Touka", ::giveBoxJMis);
	
	self MainMenu("GiveB4 List", "GiveB List");
	self MenuOption("GiveB4 List", 0, "Kuruma wo Unten", ::giveBoxCar);
	self MenuOption("GiveB4 List", 1, "Ace Combat", ::giveBoxAC);
	self MenuOption("GiveB4 List", 2, "Hikouki Souzyuu", ::giveBoxHeli);
	
	self MainMenu("Heli List", "Sub Menu 9");
	self MenuOption("Heli List", 0, "^5-Minnna-"); 
	self MenuOption("Heli List", 1, "^3Heli wo Yobu", ::initPilotHeli); 
	self MenuOption("Heli List", 2, "^7Overwatch", ::PHeliModellb);
	self MenuOption("Heli List", 3, "Attack Heli", ::PHeliModelah);
	self MenuOption("Heli List", 4, "A10 Thunderbolt", ::PHeliModela10);
	self MenuOption("Heli List", 5, "Pegasus", ::PHeliModelstlh);
	self MenuOption("Heli List", 6, "^5-Zibun-"); 
	self MenuOption("Heli List", 7, "^3Heli wo Yobu", ::initPilotHeliMe); 
	self MenuOption("Heli List", 8, "^7Overwatch", ::PHeliModellbMe);
	self MenuOption("Heli List", 9, "Attack Heli", ::PHeliModelahMe);
	self MenuOption("Heli List", 10, "A10 Thunderbolt", ::PHeliModela10Me);
	self MenuOption("Heli List", 11, "Pegasus", ::PHeliModelstlhMe);
	self MenuOption("Heli List", 12, "VTOL Warship", ::PHeliModelvtolMe);
	self MenuOption("Heli List", 13, "FA38", ::PHeliModelfaMe);
	self MenuOption("Heli List", 14, "C-UAV", ::PHeliModelcuavMe);

	self MainMenu("Turret List", "Sub Menu 9");
	self MenuOption("Turret List", 0, "Tama: Turret", ::spawnturret1);
	self MenuOption("Turret List", 1, "Tama: Hellstorm", ::spawnturret2);
	self MenuOption("Turret List", 2, "Tama: Warthog", ::spawnturret3);
	self MenuOption("Turret List", 3, "Tama: Chopper Gunner", ::spawnturret4);
	
	self MainMenu("SpawnB List", "Sub Menu 9");
	self MenuOption("SpawnB List", 0, "^3Tama no On/Off", ::initSpawnBullet);
	self MenuOption("SpawnB List", 1, "^7Carepackage (Friendly)", ::carepBullets);
	self MenuOption("SpawnB List", 2, "Carepackage (Enemy)", ::redcareBullets);
	self MenuOption("SpawnB List", 3, "Carepackage (Detect)", ::detcareBullets);
	self MenuOption("SpawnB List", 4, "Carepackage (HQ)", ::hqcareBullets);
	self MenuOption("SpawnB List", 5, "A.G.R Drone", ::agrBullets);
	self MenuOption("SpawnB List", 6, "Drone Package", ::droneBullets);
	self MenuOption("SpawnB List", 7, "Debug Model", ::defacBullets);
	self MenuOption("SpawnB List", 8, "Dog", ::dogBullets);
	self MenuOption("SpawnB List", 9, "Sentry Gun", ::turretBullets);
	self MenuOption("SpawnB List", 10, "Little Bird", ::lbirdBullets);
	self MenuOption("SpawnB List", 11, "Stealth Bomber", ::sbombBullets);
	self MenuOption("SpawnB List", 12, "VTOL Warship", ::vtolBullets);

	self MainMenu("Jet List", "Sub Menu 9");
	self MenuOption("Jet List", 0, "^5--Minnna--");
	self MenuOption("Jet List", 1, "^3Jet wo Yobu", ::initFlyableJet);
	self MenuOption("Jet List", 2, "^7A10 Thunderbolt", ::setFJetMatb);
	self MenuOption("Jet List", 3, "Lightning Strike", ::setFJetMharr);
	self MenuOption("Jet List", 4, "Stealth Bomber", ::setFJetMstb);
	self MenuOption("Jet List", 5, "UAV", ::setFJetMuav);
	self MenuOption("Jet List", 6, "VTOL Warship", ::setFJetMvtol);
	self MenuOption("Jet List", 7, "^5--Zibun--");
	self MenuOption("Jet List", 8, "^3Jet wo Yobu", ::initFlyableJetMe);
	self MenuOption("Jet List", 9, "^7A10 Thunderbolt", ::setFJetMatbMe);
	self MenuOption("Jet List", 10, "Lightning Strike", ::setFJetMharrMe);
	self MenuOption("Jet List", 11, "Stealth Bomber", ::setFJetMstbMe);
	self MenuOption("Jet List", 12, "Counter UAV", ::setFJetMcuav);
	
	self MainMenu("Sub Menu 10", "Main Menu");
	self MenuOption("Sub Menu 10", 0, "Prestige 11th", ::doMaster);
	self MenuOption("Sub Menu 10", 1, "Level 55", ::doRank);
	self MenuOption("Sub Menu 10", 2, "Trophys Zenkai", ::unlockAllCheevos);
	self MenuOption("Sub Menu 10", 3, "Meisai Zenkai", ::doAllUnlockCamos);
	self MenuOption("Sub Menu 10", 4, "Class Mei ni Iro", ::ColoredClass);
	self MenuOption("Sub Menu 10", 5, "Level 1", ::selfDerank);

	self MainMenu("Sub Menu 11", "Main Menu");
	self MenuOption("Sub Menu 11", 0, "^2Game Settei", ::SubMenu, "Game Setting");
	self MenuOption("Sub Menu 11", 1, "bot Settei", ::SubMenu, "bot Setting");
	self MenuOption("Sub Menu 11", 2, "Koukoku Settei", ::SubMenu, "DoH List");
	self MenuOption("Sub Menu 11", 3, "Custom Gamemode", ::SubMenu, "Gametype List");
	self MenuOption("Sub Menu 11", 4, "Map Henkou", ::SubMenu, "Map List");
	self MenuOption("Sub Menu 11", 5, "^7Game wo Restart", ::doFastRestart);
	self MenuOption("Sub Menu 11", 6, "Game Syuuryou", ::EndGame);
	self MenuOption("Sub Menu 11", 7, "Ending", ::initCredit);
	
	self MainMenu("bot Setting", "Sub Menu 11");
	self MenuOption("bot Setting", 0, "bot wo Yobu", ::SpawnBot("autoassign"));
	self MenuOption("bot Setting", 1, "bot nomi wo Kick", ::kickAllBots);
	
	self MainMenu("DoH List", "Sub Menu 11");
	self MenuOption("DoH List", 0, "Heya no Senden", ::doTradeMark);
	self MenuOption("DoH List", 1, "Host mei no Hyouzi", ::tgHeart);
	self MenuOption("DoH List", 2, "AsTy no Koukoku", ::doHeartx);
	self MenuOption("DoH List", 3, "Kaiten -> ^1" + level.hostname, ::InitSpinText);
	self MenuOption("DoH List", 4, "^7Menu no Koukoku", ::initScrollDH);
	self MenuOption("DoH List", 5, "^525 ^3Niconico Mode ^525", ::initNiconico);

	self MainMenu("Game Setting", "Sub Menu 11");
	self MenuOption("Game Setting", 0, "Jump-Ryoku", ::ToggleSuperJump);
	self MenuOption("Game Setting", 1, "Ugoku Speed", ::lobbySpeed);
	self MenuOption("Game Setting", 2, "Zyuuryoku", ::initGravity);
	self MenuOption("Game Setting", 3, "Zikan no Sokudo", ::doSpeedX2);
	self MenuOption("Game Setting", 4, "Koukai Match", ::ToggleRanked);
	self MenuOption("Game Setting", 5, "Zikan Mugen", ::InfGame);
	self MenuOption("Game Setting", 6, "Tyou-Rensya", ::rapidFire);
	self MenuOption("Game Setting", 7, "En-Kyori Naifu", ::initMRange);
	self MenuOption("Game Setting", 8, "Sinu Kabe wo Kesu", ::deathBarrier);
	self MenuOption("Game Setting", 9, "Rocket no Ame", ::initRocketRain);
	self MenuOption("Game Setting", 10, "VC wo Kiku", ::hearETlobby);
	self MenuOption("Game Setting", 11, "Imo Koroshi", ::initCampKill);
	self MenuOption("Game Setting", 12, "XP Lobby", ::initXPLobby);

	self MainMenu("Gametype List", "Sub Menu 11");
	self MenuOption("Gametype List", 0, "Sniper Lobby", ::initSniperLobby);
	self MenuOption("Gametype List", 1, "Nomal Lobby", ::initNomalLobby);
	
	self MainMenu("Map List", "Sub Menu 11");
	self MenuOption("Map List", 0, "Nuketown", ::Nuketown);
	self MenuOption("Map List", 1, "Hijacked", ::Hijacked);
	self MenuOption("Map List", 2, "Express", ::Express);
	self MenuOption("Map List", 3, "Meltdown", ::Meltdown);
	self MenuOption("Map List", 4, "Drone", ::Drone);
	self MenuOption("Map List", 5, "Carrier", ::Carrier);
	self MenuOption("Map List", 6, "Overflow", ::Overflow);
	self MenuOption("Map List", 7, "Slums", ::Slums);
	self MenuOption("Map List", 8, "Turbine", ::Turbine);
	self MenuOption("Map List", 9, "Raid", ::Raid);
	self MenuOption("Map List", 10, "Aftermath", ::Aftermath);
	self MenuOption("Map List", 11, "Cargo", ::Cargo);
	self MenuOption("Map List", 12, "Standoff", ::Standoff);
	self MenuOption("Map List", 13, "Plaza", ::Plaza);
	self MenuOption("Map List", 14, "Yemen", ::Yemen);
	self MenuOption("Map List", 15, "^2DLC Maps", ::SubMenu, "DLC List");
	
	self MainMenu("DLC List", "Sub Menu 11");
	self MenuOption("DLC List", 0, "Dig", ::mp_dig);
	self MenuOption("DLC List", 1, "Pod", ::mp_pod);
	self MenuOption("DLC List", 2, "Takeoff", ::mp_takeoff);
	self MenuOption("DLC List", 3, "Frost", ::mp_frostbite);
	self MenuOption("DLC List", 4, "Mirage", ::mp_mirage);
	self MenuOption("DLC List", 5, "Hydro", ::mp_hydro);
	self MenuOption("DLC List", 6, "Grind", ::mp_skate);
	self MenuOption("DLC List", 7, "Downhill", ::mp_downhill);
	self MenuOption("DLC List", 8, "Encore", ::mp_concert);
	self MenuOption("DLC List", 9, "Vertigo", ::mp_vertigo);
	self MenuOption("DLC List", 10, "Magma", ::mp_magma);
	self MenuOption("DLC List", 11, "Studio", ::mp_studio);
	self MenuOption("DLC List", 12, "Rush", ::mp_paintball);
	self MenuOption("DLC List", 13, "Cove", ::mp_castaway);
	self MenuOption("DLC List", 14, "Detour", ::mp_bridge);
	self MenuOption("DLC List", 15, "Uplink", ::mp_uplink);

	self MainMenu("Sub Menu 12", "Main Menu");
	self MenuOption("Sub Menu 12", 0, "Kyousei Host", ::forcehost);

	self MainMenu("Clients Menu", "Main Menu");
	for (p = 0; p < level.players.size; p++)
	{
		player = level.players[p];
		name = player getName();
		self MenuOption("Clients Menu", p, player.MyAccess + " ^7" + name, ::SubMenu, "Client Function");
	}
	self thread MonitorPlayers();
	
	self MainMenu("Client Function", "Clients Menu");
	self MenuOption("Client Function", 0, "^6Menu wo Watasu Lv1", ::Verify);
	self MenuOption("Client Function", 1, "^3Menu wo Watasu Lv2", ::doVIP);
	self MenuOption("Client Function", 2, "^1Menu wo Watasu Lv3", ::doAdmin);
	self MenuOption("Client Function", 3, "^5Menu wo Watasu Lv4", ::doCoHost);
	self MenuOption("Client Function", 4, "^4Menu wo Kesu Lv0", ::doUnverif);
	self MenuOption("Client Function", 5, "^7-----");
	self MenuOption("Client Function", 6, "Zibun ni Teleport", ::doTeleportToMe);
	self MenuOption("Client Function", 7, "Aite he Teleport", ::doTeleportToHim);
	self MenuOption("Client Function", 8, "Kick", ::doKickPlayer);
	self MenuOption("Client Function", 9, "^2Hutuu no Ti-to", ::SubMenu, "Player Basic");
	self MenuOption("Client Function", 10, "Omoshiroi Ti-to", ::SubMenu, "Player Funny");
	self MenuOption("Client Function", 11, "Tuyoi Ti-to", ::SubMenu, "Player Strong");
	
	self MainMenu("Player Basic", "Client Function");
	self MenuOption("Player Basic", 0, "Muteki", ::playerGod);
	self MenuOption("Player Basic", 1, "Tama Mugen", ::playerInfa);
	self MenuOption("Player Basic", 2, "Toumei", ::playerHide);
	self MenuOption("Player Basic", 3, "Zen-Perks Get", ::playerPerk);
	self MenuOption("Player Basic", 4, "Zyouji UAV", ::playerUAV);
	self MenuOption("Player Basic", 5, "Aruku Speed Henkou", ::playerSpeed);
	self MenuOption("Player Basic", 6, "Death Machine Get", ::playerDMachi);
	self MenuOption("Player Basic", 7, "Random de Buki Get", ::playerRWeap);
	self MenuOption("Player Basic", 8, "Team Henkou", ::playerTChange);
	self MenuOption("Player Basic", 9, "Zisatu", ::playerDeath);
	
	self MainMenu("Player Funny", "Client Function");
	self MenuOption("Player Funny", 0, "Sora wo Tobu", ::playerNoclip);
	self MenuOption("Player Funny", 1, "Mugen Jump", ::playerMJump);
	self MenuOption("Player Funny", 2, "Ninja Mode", ::playerNinja);
	self MenuOption("Player Funny", 3, "Smoke Zigoku", ::playerSmokeM);
	self MenuOption("Player Funny", 4, "Mono wo Hakobu", ::playerForge);
	self MenuOption("Player Funny", 5, "Minecraft Mode", ::playerAdvFor);
	self MenuOption("Player Funny", 6, "Kuruma wo Unten", ::playerDCar);
	self MenuOption("Player Funny", 7, "Ace Combat", ::playerJet);
	self MenuOption("Player Funny", 8, "Hikouki Souzyuu", ::playerHeli);
	
	self MainMenu("Player Strong", "Client Function");
	self MenuOption("Player Strong", 0, "Tama Bakuhatu", ::playerExBul);
	self MenuOption("Player Strong", 1, "Tama Kakikae", ::playerMGB);

	self MainMenu("All Clients", "Main Menu");
	self MenuOption("All Clients", 0, "Muteki", ::doGodAllPlayer);
	self MenuOption("All Clients", 1, "Tama Mugen", ::doInfAmmAllPlayer);
	self MenuOption("All Clients", 2, "Sora wo Tobu", ::doNocAllPlayer);
	self MenuOption("All Clients", 3, "Minecraft Mode", ::APadvForge);
	self MenuOption("All Clients", 4, "Tama Bakuhatu", ::doExpBulAllPlayer);
	self MenuOption("All Clients", 5, "Death Machine Get", ::doGiveDMAllPlayer);
	self MenuOption("All Clients", 6, "Buki wo Kesu", ::APtakeWeapon);
	self MenuOption("All Clients", 7, "Level 55", ::maxAllRank);
	self MenuOption("All Clients", 8, "Menu wo Watasu Lv3", ::playerAdmin);
	self MenuOption("All Clients", 9, "Menu wo Kesu Lv0", ::playerUnv);
	self MenuOption("All Clients", 10, "Freeze", ::doFreezeAllPlayer);
	self MenuOption("All Clients", 11, "Zennin Kill", ::AllPlayersKilled);
	self MenuOption("All Clients", 12, "Taisyutu Hukanou", ::doAntiQuitAllPlayer);
	self MenuOption("All Clients", 13, "Zibun ni Teleport", ::AllTeleportToMe);
	self MenuOption("All Clients", 14, "Aim Saki ni Teleport", ::teleToCrosshairs);

	self MainMenu("Sub Menu 13", "Main Menu");
	self MenuOption("Sub Menu 13", 0, "^5Sky Marine Style", ::menuSky);
	self MenuOption("Sub Menu 13", 1, "^1Crimson Style", ::menuCrimson);
	self MenuOption("Sub Menu 13", 2, "^3Electronic Style", ::menuElectro);
	self MenuOption("Sub Menu 13", 3, "^4Daemon Style", ::menuDaemon);
	self MenuOption("Sub Menu 13", 4, "^23-Prism Style", ::menuPrism);
	self MenuOption("Sub Menu 13", 5, "^17^2t^3h ^4A^5r^6t ^7S^1t^2y^3l^4e", ::domenuRain);
	self MenuOption("Sub Menu 13", 6, "^7Revolution Style", ::menuRevo);
	self MenuOption("Sub Menu 13", 7, "NextGenUpdate Style", ::menuNgu);
	self MenuOption("Sub Menu 13", 8, "Default Style", ::menuDefault);

	self MainMenu("Sub Menu 14", "Main Menu");
	self MenuOption("Sub Menu 14", 0, "Nihongo", ::changeJap);
	self MenuOption("Sub Menu 14", 1, "Eigo", ::changeEng);
}

changeJap()
{
    self thread MenuClosing();
    self notify("change_Jap");
    self thread MenuStructure_JP();
}
changeEng()
{
    self thread MenuClosing();
    self notify("change_Eng");
    self thread MenuStructure();
}

MonitorPlayers()
{
	self endon("disconnect");
	self endon("change_Jap");
	self endon("change_Eng");
	for(;;)
	{
		for(p = 0; p < level.players.size; p++)
		{
			player = level.players[p];
			name = player getName();
			self.Menu.System["MenuTexte"]["Clients Menu"][p] = player.MyAccess + " ^7" + name;
			self.Menu.System["MenuFunction"]["Clients Menu"][p] = ::SubMenu;
			self.Menu.System["MenuInput"]["Clients Menu"][p] = "Client Function";
			wait 0.05;
		}
		wait 0.05;
	}
}
getName()
{
	name = getSubStr(self.name, 0, self.name.size);
	for(i = 0; i < name.size; i++)
	{
		if(name[i]=="]")
			break;
	}
	if(name.size != i)
		name = getSubStr(name, i + 1, name.size);
	
	return name;
}
MainMenu(Menu, Return)
{
	self.Menu.System["GetMenu"] = Menu;
	self.Menu.System["MenuCount"] = 0;
	self.Menu.System["MenuPrevious"][Menu] = Return;
}
MenuOption(Menu, Index, Texte, Function, Input)
{
	self.Menu.System["MenuTexte"][Menu][Index] = Texte;
	self.Menu.System["MenuFunction"][Menu][Index] = Function;
	self.Menu.System["MenuInput"][Menu][Index] = Input;
}
SubMenu(input)
{
	self freezecontrols(false);
	self.Menu.System["MenuCurser"] = 0;
	self.Menu.System["Title"] fadeAlphaChange(.1, 0);
	self.Menu.System["Texte"] fadeAlphaChange(.1, 0);
	wait 0.1;
	self.Menu.System["Title"] destroy();
	self.Menu.System["Texte"] destroy();
	self thread LoadMenu(input);

	if(self.Menu.System["MenuRoot"]=="Sub Menu 1")
	{
		self.Menu.System["Title"] destroy();
		self.Menu.System["Title"] = self createFontString("default", 1.4);
		self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^1Main Mods Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 2")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^2Funny Mods Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 3")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^3Weakly Cheats Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 4")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^4Chat Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 5 (VIP)")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^5Weapons Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 6 (Admin)")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^6VIP Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 7 (Host)")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^7Admin Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 8")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^8Co-Host Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 9")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^9Spawns Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 10")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^1Account Hack Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 11")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^2Lobby Mods Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 12")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^3Host Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Clients Menu")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^4Players Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="All Clients")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^5All Players Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 13")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^6Design Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Sub Menu 14")
	{
	    self.Menu.System["Title"] destroy();
	    self.Menu.System["Title"] = self createFontString("default", 1.4);
	    self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	    self.Menu.System["Title"].sort = 3;
	    self.Menu.System["Title"].alpha = 0;
	    self.Menu.System["Title"] setText("^7Laungage Menu");
	}
	else if(self.Menu.System["MenuRoot"]=="Client Function")
	{
		self.Menu.System["Title"] destroy();
		player = level.players[self.Menu.System["ClientIndex"]];
		self.Menu.System["Title"] = self createFontString("default", 1.4);
		self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
		self.Menu.System["Title"] setText("[" + player.MyAccess + "^7] " + player.name);
		self.Menu.System["Title"].sort = 3;
		self.Menu.System["Title"].alpha = 0;
	}
	
	self.Menu.System["Title"] fadeAlphaChange(.1, 1);
}
LoadMenu(menu)
{
	self.Menu.System["MenuCurser"] = 0;
	self.Menu.System["MenuRoot"] = menu;
	self.Menu.System["Title"] = self createFontString("default", 1.4);
	self.Menu.System["Title"] setPoint("LEFT", "TOP", 125, 40);
	self.Menu.System["Title"] setText("^1M^2a^3i^4n ^5M^6e^7n^8u");
	self.Menu.System["Title"].sort = 1;
	self.Menu.System["Title"].alpha = 0;
	self.Menu.System["Title"] fadeAlphaChange(.1, 1);
	string = "";
	for(i=0;i<self.Menu.System["MenuTexte"][Menu].size;i++) string += self.Menu.System["MenuTexte"][Menu][i] + "\n";
	self.Menu.System["Texte"] = self createFontString("default", 1.1);
	self.Menu.System["Texte"] setPoint("LEFT", "TOP", 125, 60);
	self.Menu.System["Texte"] setText(string);
	self.Menu.System["Texte"].sort = 3;
	self.Menu.System["Texte"].alpha = 0;
	self.Menu.Material["Scrollbar"] elemMoveY(.2, 60 + (self.Menu.System["MenuCurser"] * 13.2));
	self.Menu.System["Texte"] fadeAlphaChange(.1, 1);
}
SetMaterial(align, relative, x, y, width, height, colour, shader, sort, alpha)
{
	hud = newClientHudElem(self);
	hud.elemtype = "icon";
	hud.color = colour;
	hud.alpha = alpha;
	hud.sort = sort;
	hud.children = [];
	hud setParent(level.uiParent);
	hud setShader(shader, width, height);
	hud setPoint(align, relative, x, y);
	return hud;
}
drawShader(shader, x, y, width, height, color, alpha, sort)
{
	hud = newClientHudElem(self);
	hud.elemtype = "icon";
	hud.color = color;
	hud.alpha = alpha;
	hud.sort = sort;
	hud.children = [];
	hud setParent(level.uiParent);
	hud setShader(shader, width, height);
	hud.x = x;
	hud.y = y;
	return hud;
}
drawText(text, font, fontScale, x, y, color, alpha, glowColor, glowAlpha, sort)
{
	hud = self createFontString(font, fontScale);
	hud setText(text);
	hud.x = x;
	hud.y = y;
	hud.color = color;
	hud.alpha = alpha;
	hud.glowColor = glowColor;
	hud.glowAlpha = glowAlpha;
	hud.sort = sort;
	hud.alpha = alpha;
	return hud;
}
MenuDeath()
{
	self waittill("death");
	if(self.MenuOpen == true)
	{
		self MenuClosing();
	}
}
InitialisingMenu()
{
	self.Menu.Material["Background"] = self SetMaterial("LEFT", "TOP", 120, -1000, 240, 1000, (0, 0, 0), "white", 0, 0.76);
	self.Menu.Material["Scrollbar"] = self SetMaterial("LEFT", "TOP", 120, -1000, 240, 13, (0.180, 0.210, 0.40), "white", 1, 0.6);
	self.Menu.Material["BorderMiddle"] = self SetMaterial("LEFT", "TOP", 119, -1000, 240, 3, (0.90, 0.140, 0.220), "white", 1, 0.6);
	self.Menu.Material["BorderLeft"] = self SetMaterial("LEFT", "TOP", 360, -1000, 3, 1000, (0.90, 0.140, 0.220), "white", 1, 0.6);
	self.Menu.Material["BorderRight"] = self SetMaterial("LEFT", "TOP", 120, -1000, 3, 1000, (0.90, 0.140, 0.220), "white", 1, 0.6);
	self.bghorizon = self drawShader(level.icontest, -400, -100, 1000, 1000, (0.392, 0.066, 0.949), 0, 0);
}

MenuOpening()
{
	self freezecontrols(false);
	self.titleHeart = self drawText("^1B^5rain ^1B^5urst ^3V1\nby.^1A^2s^3T^5y", "objective", 1.7, 239, -1000, (1, 1, 1), 0, (1, 0, 0), 1, 1);
	self.MOcontrolinfo = self drawText("^3Menu Open: [{+speed_throw}] ^6+ [{+melee}]\n^3Scroll: [{+actionslot 1}] ^6| [{+actionslot 2}]\n^3Select: [{+usereload}]\n^3Back: [{+speed_throw}] ^6+ [{+actionslot 2}]", "objective", 1.2, 40, 335, (1, 1, 1), 0, (0.8, 0.451, 0.949), 1, 1);
	
	self thread titleEffect();
	self thread titleEffect2();

	self.Menu.Material["Background"] elemMove(.3, 120, 0);
	self.Menu.Material["Scrollbar"] elemMove(.3, 120, 60);
	self.Menu.Material["BorderLeft"] elemMove(.3, 119, 0);
	self.Menu.Material["BorderRight"] elemMove(.3, 360, 0);
	self.Menu.Material["BorderMiddle"] elemMove(.3, 120, 50);
	self.titleHeart elemMove(.3, 239, -25);
	self.titleHeart fadeAlphaChange(.3, 1);
	self.bghorizon fadeAlphaChange(.3, 1);
	self.MOcontrolinfo fadeAlphaChange(.3, 1);

	self.MenuOpen = true;
}
MenuClosing()
{    
	self freezecontrols(false);
	self.bghorizon fadeAlphaChange(.3, 0);
	self.titleHeart fadeAlphaChange(.3, 0);
	self.MOcontrolinfo fadeAlphaChange(.3, 0);
	self.Menu.System["Title"] fadeAlphaChange(.3, 0);
	self.Menu.System["Texte"] fadeAlphaChange(.3, 0);
	
	if (self.MenuPattern == 0)
	{
		self.titleHeart elemMove(.3, 239, 1000);
		self.Menu.Material["Background"] elemMove(.3, 120, 1000);
		self.Menu.Material["Scrollbar"] elemMove(.3, 120, 1000);
		self.Menu.Material["BorderLeft"] elemMove(.3, 119, 1000);
		self.Menu.Material["BorderRight"] elemMove(.3, 360, 1000);
		self.Menu.Material["BorderMiddle"] elemMove(.3, 120, 1000);
		self.MenuPattern = 1;
	}
	else if (self.MenuPattern == 1)
	{
		self.titleHeart elemMove(.3, -1000, -20);
		self.Menu.Material["Background"] elemMove(.3, -1000, 0);
		self.Menu.Material["Scrollbar"] elemMove(.3, -1000, 60);
		self.Menu.Material["BorderLeft"] elemMove(.3, -1000, 0);
		self.Menu.Material["BorderRight"] elemMove(.3, -1000, 0);
		self.Menu.Material["BorderMiddle"] elemMove(.3, -1000, 50);
		self.MenuPattern = 2;
	}
	else if (self.MenuPattern == 2)
	{
		self.titleHeart elemMove(.3, 1000, -20);
		self.Menu.Material["Background"] elemMove(.3, 1000, 0);
		self.Menu.Material["Scrollbar"] elemMove(.3, 1000, 60);
		self.Menu.Material["BorderLeft"] elemMove(.3, 1000, 0);
		self.Menu.Material["BorderRight"] elemMove(.3, 1000, 0);
		self.Menu.Material["BorderMiddle"] elemMove(.3, 1000, 50);
		self.MenuPattern = 3;
	}
	else if (self.MenuPattern == 3)
	{
		self.titleHeart elemMove(.3, 239, -1000);
		self.Menu.Material["Background"] elemMove(.3, 120, -1000);
		self.Menu.Material["Scrollbar"] elemMove(.3, 120, -1000);
		self.Menu.Material["BorderLeft"] elemMove(.3, 119, -1000);
		self.Menu.Material["BorderRight"] elemMove(.3, 360, -1000);
		self.Menu.Material["BorderMiddle"] elemMove(.3, 120, -1000);
		self.MenuPattern = 0;
	}
	
	self notify("stop_titleEffect");
	wait 0.3;
	self.Menu.System["Title"] clear(self);
	self.Menu.System["Texte"] clear(self);
	self.titleHeart clear(self);
	self.MOcontrolinfo clear(self);
	wait 0.03;
	self.MenuOpen = false;
}
titleEffect()
{
	self endon("disconnect");
	self endon("stop_titleEffect");
	for (;;)
	{
		self.titleHeart doTxtSizeTime(0.5, 1.7);
		wait 0.5;
		self.titleHeart doTxtSizeTime(0.5, 2.2);
		wait 0.5;
	}
}
titleEffect2()
{
	self endon("disconnect");
	self endon("stop_titleEffect");
	for (;;)
	{
		self.titleHeart elemGColor(0.1, (1, 0, 0));
		wait 0.1;
		self.titleHeart elemGColor(0.1, (0, 1, 0));
		wait 0.1;
		self.titleHeart elemGColor(0.1, (0, 0, 1));
		wait 0.1;
		self.titleHeart elemGColor(0.1, (1, 0, 1));
		wait 0.1;
		self.titleHeart elemGColor(0.1, (0, 1, 1));
		wait 0.1;
		self.titleHeart elemGColor(0.1, (0, 0, 1));
		wait 0.1;
		self.titleHeart elemGColor(0.1, (1, 1, 0));
		wait 0.1;
		self.titleHeart elemGColor(0.1, (1, 1, 1));
		wait 0.1;
	}
}

elemMove(time, inputx, inputy)
{
	self moveOverTime(time);
	self.x = inputx;
	self.y = inputy;
}
elemMoveY(time, input)
{
	self moveOverTime(time);
	self.y = input;
}
elemMoveX(time, input)
{
	self moveOverTime(time);
	self.x = input;
}
elemFade(time, alpha)
{
	self moveOverTime(time);
	self.alpha = alpha;
}
elemGColor(time, g_color)
{
	self fadeOverTime(time);
	self.glowColor = g_color;
}
colorChange(time, colour)
{
	self fadeOverTime(time);
	self.color = colour;
}
fadeAlphaChange(time, alpha)
{
	self fadeOverTime(time);
	self.alpha = alpha;
}
doTxtSizeTime(time, size)
{
	self ChangeFontScaleOverTime(time);
	self.fontscale = size;
}

doUnverif()
{
	player = level.players[self.Menu.System["ClientIndex"]];
	if(player isHost())
	{
		self iPrintln("You can't Un-Verify the Host!");
	}
	else
	{
		player MenuClosing();
		wait 0.1;
		player notify("stop_BuildMenu");
		wait 0.1;
		player sadUnverifMe();
		wait 0.1;
		player suicide();
		player notify("stop_stBind");
		self iPrintln( player.name + " is ^1Unverfied" );
	}
}
sadUnverifMe()
{
	self.Verified = false;
	self.VIP = false;
	self.Admin = false;
	self.CoHost = false;
    self.Host = false;
}
Verify()
{
	player = level.players[self.Menu.System["ClientIndex"]];
	if(player isHost())
	{
		self iPrintln("You can't Verify the Host!");
	}
	else
	{
		player MenuClosing();
		wait 0.1;
		player notify("stop_BuildMenu");
		player notify("menuinit_one");
		wait 0.1;
		player sadUnverifMe();
		wait 0.1;
		player.Verified = true;
		player.VIP = false;
		player.Admin = false;
		player.CoHost = false;
		player.Host = false;
		player thread setplayermenugive();
		wait 0.1;
		player notify("sad_menugive");
		player notify("stop_stBind");
		self iPrintln( player.name + " is ^1Verified" );
	}
}
doVIP()
{
	player = level.players[self.Menu.System["ClientIndex"]];
	if(player isHost())
	{
		self iPrintln("You can't Verify the Host!");
	}
	else
	{
		player MenuClosing();
		wait 0.1;
		player notify("stop_BuildMenu");
		player notify("menuinit_one");
		wait 0.1;
		player sadUnverifMe();
		wait 0.1;
		player.Verified = true;
		player.VIP = true;
		player.Admin = false;
		player.CoHost = false;
		player.Host = false;
		player thread setplayermenugive();
		wait 0.1;
		player notify("sad_menugive");
		player notify("stop_stBind");
		self iPrintln( player.name + " is ^3VIP" );
	}
}
doAdmin()
{
	player = level.players[self.Menu.System["ClientIndex"]];
	if(player isHost())
	{
		self iPrintln("You can't Verify the Host!");
	}
	else
	{
		player MenuClosing();
		wait 0.1;
		player notify("stop_BuildMenu");
		player notify("menuinit_one");
		wait 0.1;
		player sadUnverifMe();
		wait 0.1;
		player.Verified = true;
		player.VIP = true;
		player.Admin = true;
		player.CoHost = false;
		player.Host = false;
		player thread setplayermenugive();
		wait 0.1;
		player notify("sad_menugive");
		player notify("stop_stBind");
		self iPrintln( player.name + " is ^1Admin" );
	}
}
doCoHost()
{
	player = level.players[self.Menu.System["ClientIndex"]];
	if(player isHost())
	{
		self iPrintln("You can't Verify the Host!");
	}
	else
	{
		if (player.CoHost == false)
		{
			player MenuClosing();
			wait 0.1;
			player notify("stop_BuildMenu");
			player notify("menuinit_one");
			wait 0.1;
			player sadUnverifMe();
			wait 0.1;
			player.Verified = true;
			player.VIP = true;
			player.Admin = true;
			player.CoHost = true;
		    player.Host = false;
			player thread setplayermenugive();
			wait 0.1;
			player notify("sad_menugive");
			player notify("stop_stBind");
			player thread doStlhBind();
			self iPrintln( player.name + " is ^5Co-Host" );
		}
	}
}

//-----[ Functions ]-----

callOnText(load, word, word2, color, glowc)
{
	load = self drawText("^5" + word + ": ^2On" + "\n" + word2, "objective", 1.5, 0, 200, color, 0, glowc, 1, 1);
	load fadeAlphaChange(.2, 1);
	wait 3;
	load fadeAlphaChange(.2, 0);
	wait 0.3;
	load destroy();
}
callOffText(load, word, word2, color, glowc)
{
	load = self drawText("^5" + word + ": ^1Off" + "\n" + word2, "objective", 1.5, 0, 200, color, 0, glowc, 1, 1);
	load fadeAlphaChange(.2, 1);
	wait 3;
	load fadeAlphaChange(.2, 0);
	wait 0.3;
	load destroy();
}
callInfoText(load, word, word2, color, glowc)
{
	load = self drawText(word + "\n" + word2, "objective", 1.5, 0, 200, color, 0, glowc, 1, 1);
	load fadeAlphaChange(.2, 1);
	wait 3;
	load fadeAlphaChange(.2, 0);
	wait 0.3;
	load destroy();
}

Test()
{
	self iPrintlnbold("This Function is not Build yet.");
}

MenuWelcome()
{
	notifyData = spawnstruct();
	notifyData.titleText = "^3Welcome to ^1" + level.hostname + "^3's ^4G^2S^4C ^6Lobby";
	notifyData.notifyText = "^3Hello, ^5" + self.name + "^3. You can using the ^1Mod Menu!";
	notifyData.glowColor = (0.3, 0.6, 0.3);
	notifyData.duration = 8;
	notifyData.font = "objective";
	notifyData.hideWhenInMenu = false;
	self thread maps\mp\gametypes\_hud_message::notifyMessage(notifyData);
	
	if (self.initCDSawned == 0)
	{
		self.controlinfo = self drawText("^3Menu Open: [{+speed_throw}] ^6+ [{+melee}]\n^3Scroll: [{+actionslot 1}] ^6| [{+actionslot 2}]\n^3Select: [{+usereload}]\n^3Back: [{+speed_throw}] ^6+ [{+actionslot 2}]", "objective", 1.5, -190, 75, (1, 1, 1), 0, (0.278, 0.671, 0.961), 1, 1);
		self.initCDSawned = 1;
	}
	self MenuControlInfo();
}
MenuControlInfo()
{
	self.controlinfo fadeAlphaChange(.3, 1);
	wait 10;
	self.controlinfo fadeAlphaChange(.3, 0);
	wait 0.3;
	self.controlinfo destroy();
	self.initCDSawned = 0;
}

initStlhBind()
{
	if(self.stBindOn == 0)
	{
		self.stBindOn = 1;
		self notify("stop_stBind");
		self iPrintlnbold("^5Stealth Bind: ^1Off");
	}
	else
	{
		self.stBindOn = 0;
		self thread doStlhBind();
		self iPrintlnbold("^5Stealth Bind: ^2On");
	}
}
doStlhBind()
{
	self endon("disconnect");
	self endon("stop_stBind");
	for(;;)
	{
		if(self adsButtonPressed())
		{
			if(self getStance() == "crouch")
			{
				if(self actionSlotOneButtonPressed())
				{
					self giveGod();
				}
				if(self actionSlotThreeButtonPressed())
				{
					self doInfAmmo();
				}
				if(self actionSlotFourButtonPressed())
				{
					self doStealthAimbots();
				}
			}
			if(self getStance() == "prone")
			{
				if(self actionSlotOneButtonPressed())
				{
					self doNoClip();
				}
				if(self actionSlotThreeButtonPressed())
				{
					self ForgeON();
				}
				if(self actionSlotFourButtonPressed())
				{
					self ExpBultOn();
				}
			}
		}
		if(self getStance() == "crouch" && self actionSlotOneButtonPressed() && self useButtonPressed())
		{
			self doClientsSpeed();
		}
		if(self getStance() == "crouch" && self actionSlotThreeButtonPressed() && self useButtonPressed())
		{
			self InvisibleOn();
		}
		if(self getStance() == "crouch" && self actionSlotFourButtonPressed() && self useButtonPressed())
		{
			self givespPerk();
			self iPrintlnbold("^3Set ^6All Perks");
		}
		if(self getStance() == "prone" && self actionSlotOneButtonPressed() && self useButtonPressed())
		{
			self KSGiveLST();
		}
		if(self getStance() == "prone" && self actionSlotThreeButtonPressed() && self useButtonPressed())
		{
			self doUAV();
		}
		if(self getStance() == "prone" && self actionSlotFourButtonPressed() && self useButtonPressed())
		{
			self selectMBburner();
			self initMagicBullet();
		}
		if(self getStance() == "prone" && self changeSeatButtonPressed() && self actionSlotTwoButtonPressed())
		{
			self doChatTypewriter();
		}
		wait 0.05;
	}
}

//-----[ Weakly Cheats Menu ]-----

doUAV()
{
	if (self.uav == 0)
	{
		self.uav = 1;
		self setclientuivisibilityflag("g_compassShowEnemies", 1);
		self iPrintlnbold("^5UAV: ^2On");
	}
	else
	{
		self.uav = 0;
		self setclientuivisibilityflag("g_compassShowEnemies", 0);
		self iprintlnbold("^5UAV: ^1Off");
	}
}

doSuicide()
{
	self suicide();
	self iPrintlnbold("^3You ^1Died ^5XD");
}

ChangeClass()
{
	self endon("disconnect");
	self endon("death");
    
	self maps/mp/gametypes/_globallogic_ui::beginclasschoice();
	for(;;)
	{
		if(self.pers["changed_class"])
		self maps/mp/gametypes/_class::giveloadout(self.team, self.class);
		wait 0.05;
	}
}

setAllPerks()
{
	self clearperks();
	self setperk("specialty_additionalprimaryweapon");
	self setperk("specialty_armorpiercing");
	self setperk("specialty_armorvest");
	self setperk("specialty_bulletaccuracy");
	self setperk("specialty_bulletdamage");
	self setperk("specialty_bulletflinch");
	self setperk("specialty_bulletpenetration");
	self setperk("specialty_deadshot");
	self setperk("specialty_delayexplosive");
	self setperk("specialty_detectexplosive");
	self setperk("specialty_disarmexplosive");
	self setperk("specialty_earnmoremomentum");
	self setperk("specialty_explosivedamage");
	self setperk("specialty_extraammo");
	self setperk("specialty_fallheight");
	self setperk("specialty_fastads");
	self setperk("specialty_fastequipmentuse");
	self setperk("specialty_fastladderclimb");
	self setperk("specialty_fastmantle");
	self setperk("specialty_fastmeleerecovery");
	self setperk("specialty_fastreload");
	self setperk("specialty_fasttoss");
	self setperk("specialty_fastweaponswitch");
	self setperk("specialty_finalstand");
	self setperk("specialty_fireproof");
	self setperk("specialty_flakjacket");
	self setperk("specialty_flashprotection");
	self setperk("specialty_gpsjammer");
	self setperk("specialty_grenadepulldeath");
	self setperk("specialty_healthregen");
	self setperk("specialty_holdbreath");
	self setperk("specialty_immunecounteruav");
	self setperk("specialty_immuneemp");
	self setperk("specialty_immunemms");
	self setperk("specialty_immunenvthermal");
	self setperk("specialty_immunerangefinder");
	self setperk("specialty_killstreak");
	self setperk("specialty_longersprint");
	self setperk("specialty_loudenemies");
	self setperk("specialty_marksman");
	self setperk("specialty_movefaster");
	self setperk("specialty_nomotionsensor");
	self setperk("specialty_noname");
	self setperk("specialty_nottargetedbyairsupport");
	self setperk("specialty_nokillstreakreticle");
	self setperk("specialty_nottargettedbysentry");
	self setperk("specialty_pin_back");
	self setperk("specialty_pistoldeath");
	self setperk("specialty_proximityprotection");
	self setperk("specialty_quickrevive");
	self setperk("specialty_quieter");
	self setperk("specialty_reconnaissance");
	self setperk("specialty_rof");
	self setperk("specialty_scavenger");
	self setperk("specialty_showenemyequipment");
	self setperk("specialty_stunprotection");
	self setperk("specialty_shellshock");
	self setperk("specialty_sprintrecovery");
	self setperk("specialty_showonradar");
	self setperk("specialty_stalker");
	self setperk("specialty_twogrenades");
	self setperk("specialty_twoprimaries");
	self setperk("specialty_unlimitedsprint");
	self iPrintlnbold("^3Set ^6All Perks");
}

giveMaxAmmo()
{
	currentWeapon = self getCurrentWeapon();
	if (currentWeapon != "none")
	{
		self setweaponammoclip(currentWeapon, weaponclipsize(currentWeapon));
		self givemaxammo(currentWeapon);
	}
	currentoffhand = self getcurrentoffhand();
	if (currentoffhand != "none")
	self givemaxammo(currentoffhand);
	self iPrintlnbold("^3Give ^6Max Ammo!!");
}

doClearPerks()
{
	self clearperks();
	self iPrintlnbold("^3Perks ^1Cleared ^5-n-");
}

//===< 3rd Person >===

giveTP()
{
	if (self.TPP == 0)
	{
		self.TPP = 1;
		self iPrintlnbold("^5Third Person: ^2On");
		self setclientthirdperson(1);
		self thread loopTPerson();
	}
	else
	{
		self.TPP = 0;
		self iPrintlnbold("^5Third Person: ^1Off");
		self notify("stop_loopTPerson");
		self setclientthirdperson(0);
	}
}
loopTPerson()
{
	self endon("disconnect");
	self endon("stop_loopTPerson");
	for(;;)
	{
		self waittill("spawned_player");
		self setclientthirdperson(1);
	}
}

//===< Auto Drop-Shot >===

AutoDropshot()
{
	if(self.Drop == 0)
	{
		self.Drop = 1;
		self iPrintlnbold("^5Auto Drop-Shot: ^2On");
		self thread DropTheBase();
	}
	else
	{
		self.Drop = 0;
		self iPrintlnbold("^5Auto Drop-Shot: ^1Off");
		self notify("stop_drop");
	}
}
DropTheBase()
{
	self endon("disconnect");
	self endon("stop_drop");
	for(;;)
	{
		self waittill ("weapon_fired");
		self setStance("prone");
	}
}

//===< Health Bar >===

initHealthBar()
{
	if(self.hBarOn == 0)
	{
		self.hBarOn = 1;
		self iPrintlnbold("^5Display HP: ^2On");
		self thread drawHPBar();
		self thread doHealthBar();
	}
	else
	{
		self.hBarOn = 0;
		self iPrintlnbold("^5Display HP: ^1Off");
		self notify("stop_healthBar");
		self.healthBar destroyElem();
		self.healthText destroy();
	}
}
drawHPBar()
{
	self.healthBar = self createBar((1,1,1),150,11);
	self.healthBar setPoint("CENTER","TOP",0,42);
	self.healthText = self createFontString("default",1.5);
	self.healthText setPoint("CENTER","TOP",0,22);
	self.healthText setText("^4--^6Hit Point^4--");
}
doHealthBar()
{
	self endon("disconnect");
	self endon("stop_healthBar");
	for(;;)
	{
		self.healthBar updateBar(self.health / self.maxhealth);
		if(self.health == 0)
		{
			self.healthBar destroyElem();
			self.healthText destroy();
			self waittill("spawned_player");
			self thread drawHPBar();
		}
		wait 0.5;
	}
}

//-----[ Chats Menu ]-----

initChatMessage(word, time)
{
	foreach(p in level.players)
	p thread maps\mp\gametypes\_hud_message::hintMessage(word, time);
}
doChatPatchInfo()
{
	initChatMessage("^8" + self.name + ":\n^3This ^1Mod Menu ^3Created by ^1A^2s^3T^5y^3\nPlease Visit here: ^5http://ngumodhaxasty.blog.fc2.com/", 15);
}
doChatGSCTalk()
{
	initChatMessage("^8" + self.name + ":\n^3Hack, Cheat, Glitch\nDebug, Programming...etc\n^2Variety of Techniques Topic --->\n^5http://www.nextgenupdate.com/", 15);
}
doChatMyIntro()
{
	initChatMessage("^8" + self.name + ":\n^3Hello, Everyone.\nI am ^1Japanese PS3 Hacker.\n^5Please Enjoy this Modded Lobby! ^v^", 12);
}
doChatLobbyHost()
{
	if (self isHost())
	{
		level.hostiss = self.name;
	}
	initChatMessage("^8" + self.name + ": ^3This Lobby's Host is ^5" + level.hostiss + "^3.", 7);
}
doChatTypewriter()
{
	if (self isHost())
	{
		level.hostiss = self.name;
	}
	initChatMessage(level.hostiss, 5);
}

//-----[ Design Menu ]-----

menuStyleSwitch(time, c1, c2, c3, c4, c5, c6)
{
	self.Menu.Material["Background"] colorChange(time, c1);
	self.Menu.Material["Scrollbar"] colorChange(time, c2);
	self.Menu.Material["BorderLeft"] colorChange(time, c3);
	self.Menu.Material["BorderRight"] colorChange(time, c4);
	self.Menu.Material["BorderMiddle"] colorChange(time, c5);
	self.bghorizon colorChange(time, c6);
}
menuSky()
{
	menuStyleSwitch(.5, (0, 1, 1), (0.12, 0.56, 1), (0.12, 0.56, 1), (0.12, 0.56, 1), (0.12, 0.56, 1), (0.156, 0.964, 0.980));
}
menuRevo()
{
	menuStyleSwitch(.5, (0, 0, 0), (0, 0.949, 0.239), (0, 0.949, 0.239), (0, 0.949, 0.239), (0, 0.949, 0.239), (0.475, 0.820, 0.094));
}
menuNgu()
{
	menuStyleSwitch(.5, (1, 1, 1), (0.212, 0.769, 0.980), (0.212, 0.769, 0.980), (0.212, 0.769, 0.980), (0.212, 0.769, 0.980), (0.894, 0.894, 0.894));
}
menuDefault()
{
	menuStyleSwitch(.5, (0, 0, 0), (0.180, 0.210, 0.40), (0.90, 0.140, 0.220), (0.90, 0.140, 0.220), (0.90, 0.140, 0.220), (0.392, 0.066, 0.949));
}
menuCrimson()
{
	menuStyleSwitch(.5, (0.941, 0.392, 0.160), (0.890, 0.062, 0.215), (0.890, 0.062, 0.215), (0.890, 0.062, 0.215), (0.890, 0.062, 0.215), (0.909, 0.301, 0.062));
}
menuElectro()
{
	menuStyleSwitch(.5, (0.874, 0.901, 0.125), (0, 0, 0), (0.862, 0.968, 0.968), (0.862, 0.968, 0.968), (0.862, 0.968, 0.968), (0.839, 0.839, 0.058));
}
menuDaemon()
{
	menuStyleSwitch(.5, (0.094, 0.250, 0.678), (.5, 0, 0.749), (0.714, 0.149, 0.819), (0.714, 0.149, 0.819), (0.714, 0.149, 0.819), (0.058, 0.176, 0.501));
}
menuPrism()
{
	menuStyleSwitch(.5, (0.329, 0.890, 0.376), (0.968, 0.282, 0.282), (0.160, 0.870, 0.940), (0.160, 0.870, 0.940), (0.160, 0.870, 0.940), (0.054, 0.929, 0.188));
}
domenuRain()
{
	if(self.rainbow == 0)
	{
		self.rainbow = 1;
		self iPrintlnbold("^3Change Design to ^67th Art Style");
		menuRain();
	}
	else
	{
		self.rainbow = 0;
		self iPrintlnbold("^37th Art Style ^6to Stop!");
		self notify("stop_rain");
	}
}
menuRain()
{
	self endon("disconnect");
	self endon("stop_rain");
	for(;;)
	{
		menuSky();
		wait .5;
		menuCrimson();
		wait .5;
		menuElectro();
		wait .5;
		menuDaemon();
		wait .5;
		menuPrism();
		wait .5;
		menuRevo();
		wait .5;
		menuNgu();
		wait .5;
		menuDefault();
		wait .5;
	}
}

//-----[ Funny Mods Menu ]-----

ClonePlayer()
{
	self cloneplayer(1);
	self iPrintlnbold("^5Clone ^2Spawned");
}

Quake()
{ 
	earthquake(0.6, 10, self.origin, 100000);
	self iPrintlnbold("^5Earthquake ^1Hit!!");
}

TpToCrHr()
{
	self setorigin(bullettrace(self gettagorigin("j_head"), self gettagorigin("j_head") + anglesToForward(self getplayerangles()) * 1000000, 0, self)["position"]);
	self iPrintlnbold("^6Teleported!");
}

DefuseBomb()
{
	if(getDvar("g_gametype")=="sd")
	{
		if (level.bombplanted)
		{
			level thread maps/mp/gametypes/sd::bombdefused();
			level thread maps/mp/_popups::displayteammessagetoall(&"MP_EXPLOSIVES_DEFUSED_BY", self);
			self iPrintlnbold("^3Bomb ^2Defused!");
		}
		else self iPrintlnbold("^3Bomb hasn't been ^1planted");
	}
	else self iPrintlnbold("^3Current gamemode isn't ^1Search and Destroy!");
}

PlantBomb()
{
	if(getDvar("g_gametype")=="sd")
	{
		if (!level.bombplanted)
		{
			level thread maps/mp/gametypes/sd::bombplanted(level.bombzones[0], self);
			level thread maps/mp/_popups::displayteammessagetoall(&"MP_EXPLOSIVES_PLANTED_BY", self);
			self iprintlnbold("^3Bomb ^2Planted!");
		}
		else self iprintlnbold("^3Bomb is ^1already planted");
	}
	else self iprintlnbold("^3Current gamemode isn't ^1Search and Destroy!");
}

initTeamChange()
{
	if(self.TeamPattern == 0)
	{
		self.TeamPattern = 1;
		self iPrintlnbold("^3Team changed to ^6axis");
		self thread changeteam("axis");
	}
	else
	{
		self.TeamPattern = 1;
		self iPrintlnbold("^3Team changed to ^6allies");
		self thread changeteam("allies");
	}
}
changeteam(team)
{
	if (self.sessionstate != "dead")
	{
		self.switching_teams = 1;
		self.joining_team = team;
		self.leaving_team = self.pers["team"];
		self suicide();
	}
	self.pers["team"] = team;
	self.team = team;
	self.sessionteam = self.pers["team"];
	if (!level.teambased)
	{
		self.ffateam = team;
	}
	self maps/mp/gametypes/_globallogic_ui::updateobjectivetext();
	self maps/mp/gametypes/_spectating::setspectatepermissions();
	self setclientscriptmainmenu( game["menu_class" ]);
	self openmenu( game["menu_class" ]);
	self notify("end_respawn");
}

//===< Riot Man >===

initRiotMan()
{
	if(self.riotManOn == 0)
	{
		self.riotManOn = 1;
		self iPrintlnbold("^5Riot Man: ^2On");
		doRiotMan();
		offRiotMan();
	}
	else
	{
		self.riotManOn = 0;
		self iPrintlnbold("^5Riot Man: ^1Off");
		self suicide();
	}
}
doRiotMan()
{
		self setclientthirdperson(1);
		self giveWeapon("riotshield_mp",0);
		self AttachShieldModel("t6_wpn_shield_carry_world","back_low");
		self giveWeapon("riotshield_mp",0);
		self AttachShieldModel("t6_wpn_shield_carry_world","j_head");
		self giveWeapon("riotshield_mp",0);
		self AttachShieldModel("t6_wpn_shield_carry_world","tag_weapon_left");
}
offRiotMan()
{
	self endon("disconnect");
	self endon("stop_loopRiotMan");
	for(;;)
	{
		self waittill("death");
		self.riotManOn = 0;
		self notify("stop_loopRiotMan");
	}
}

//===< Rocket Teleporter >===

initGiveWeap(code, name, enab)
{
	self giveWeapon(code, 0, false);
	self switchToWeapon(code);
	self givemaxammo(code);
	self setWeaponAmmoClip(code, weaponClipSize(self getCurrentWeapon()));
	if(enab == 1)
	{
		self iPrintlnbold("^3Give Weapon to ^2" + name);
	}
	else
	{

	}
}
initRocketTeleport()
{
	if(self.rocketTeleOn == 0)
	{
		self.rocketTeleOn = 1;
		self iPrintlnbold("^5Rocket Teleporter: ^2On");
		self iPrintln("^1Fire RPG, ^3You can ^4Fly.");
		doRocketTeleport();
	}
	else
	{
		self.rocketTeleOn = 0;
		self iPrintlnbold("^5Rocket Teleporter: ^1Off");
		self notify("stop_rocketTele");
		self disableInvulnerability();
	}
}
doRocketTeleport()
{
	self endon("disconnect");
	self endon("stop_rocketTele");
	self enableInvulnerability();
	initGiveWeap("usrpg_mp", "", 0);
	for (;;)
	{
		self waittill("missile_fire", weapon, weapname);
		if (weapname == "usrpg_mp")
		{
			self PlayerLinkTo(weapon);
			weapon waittill("death");
			self detachAll();
		}              
		wait 0.05;
	}
}

//===< SpecNade >===

initSpecNade()
{
	if(self.sNadeOn == 0)
	{
		self.sNadeOn = 1;
		self iPrintlnbold("^5SpecNade: ^2On");
		self iPrintln("^3Let's throw ^6a Grenade!");
		doSpecNade();
	}
	else
	{
		self.sNadeOn = 0;
		self iPrintlnbold("^5SpecNade: ^1Off");
		self notify("stop_specNade");
	}
}
doSpecNade()
{
	self endon("disconnect");
	self endon("stop_specNade");
	for(;;)
	{
		self waittill("grenade_fire", Grenade);
		self.maxhealth = 999999999;
		self.health = self.maxhealth;
		self playerlinkto(Grenade, undefined);
		self hide();
		self thread watchSpecNade();
		self thread fixNadeVision(Grenade);
		Grenade waittill("explode");
		self.maxhealth = 100;
		self.health = self.maxhealth;
		self notify("specnade");
		self unlink();
		self show();
	}
}
watchSpecNade()
{
	setDvar("cg_drawgun", 0);
	setDvar("cg_fov", 90);
	self waittill_any("death", "specnade");
	setDvar("cg_drawgun", 1);
	setDvar("cg_fov", 65);
}
fixNadeVision(grenade)
{
	self endon("disconnect");
	self endon("specnade");
	self endon("stop_specNade");
	for(;;)
	{
		self setPlayerAngles(VectorToAngles(grenade.origin - self.origin));
		wait .01;
	}
}

//===< Save/Load .Loc >===

saveandload()
{
	if (self.snl == 0)
	{
		self iprintlnbold("^5Save and Load: ^2On");
		self iprintln("Press [{+actionslot 3}] to Save!");
		self iprintln("Press [{+actionslot 4}] to Load!");
		self thread dosaveandload();
		self.snl = 1;
    	}
    	else
    	{
		self iprintlnbold("^5Save and Load: ^1Off");
		self.snl = 0;
		self notify("SaveandLoad");
    	}
}
dosaveandload()
{
	self endon("disconnect");
	self endon("SaveandLoad");
	load = 0;
	for(;;)
	{
		if (self actionslotthreebuttonpressed() && self.snl == 1)
		{
			self.o = self.origin;
			self.a = self.angles;
			load = 1;
			self iprintlnbold("^3Position ^2Saved");
			wait 0.1;
		}
		if (self actionslotfourbuttonpressed() && load == 1 && self.snl == 1)
		{
			self setplayerangles(self.a);
			self setorigin(self.o);
			self iprintlnbold("^3Position ^6Loaded");
			wait 0.1;
		}
		wait 0.05;
	}
}

//===< Multi Jump >===

Toggle_Multijump()
{
	if(self.MultiJump==0)
	{
		self thread onPlayerMultijump();
		self.MultiJump = 1;
		self iPrintlnbold("^5Multi Jump: ^2On");
	}
	else
	{
		self notify("EndMultiJump");
		self.MultiJump = 0;
		self iPrintlnbold("^5Multi Jump: ^1Off");
	}
}
landsOnGround()
{
	self endon("disconnect");
	self endon("EndMultiJump");
	loopResult = true;
	for(;;)
	{
		wait 0.05;
		newResult = self isOnGround();
		if(newResult != loopResult)
		{
			if(!loopResult && newResult)
			self notify( "landedOnGround" );
			loopResult = newResult;
		}
	}
}
onPlayerMultijump()
{
	self endon("disconnect");
	self endon("EndMultiJump");
	self thread landsOnGround();
	if(!isDefined(self.numOfMultijumps))
		self.numOfMultijumps = 999;
	for(;;)
	{
		currentNum = 0;
		while(!self jumpbuttonpressed()) wait 0.05;
		while(self jumpbuttonpressed()) wait 0.05;
		if(getDvarFloat("jump_height") > 250)
		continue;
		if ( !isAlive( self ) )
		{
			self waittill("spawned_player");
			continue;
		}
		if ( !self isOnGround() )
		{
			while( !self isOnGround() && isAlive( self ) && currentNum < self.numOfMultijumps)
			{
				waittillResult = self waittill_any_timeout( 0.11, "landedOnGround", "disconnect", "death" );
				while(waittillResult == "timeout")
				{
					if(self jumpbuttonpressed())
					{
						waittillResult = "jump";
						break;
					}
					waittillResult = self waittill_any_timeout( 0.05, "landedOnGround", "disconnect", "death" );
				}
				if(waittillResult == "jump" && !self isOnGround() && isAlive( self ))
				{
					playerAngles = self getplayerangles();
					playerVelocity = self getVelocity();
					self setvelocity( (playerVelocity[0], playerVelocity[1], playerVelocity[2]/2 ) + anglestoforward( (270, playerAngles[1], playerAngles[2]) ) * getDvarInt( "jump_height" ) * ( ( (-1/39) * getDvarInt( "jump_height" ) ) + (17/2) ) );
					currentNum++;
					while(self jumpbuttonpressed()) wait 0.05;
				}
				else
					break;
			}
			while(!self isOnGround())
			wait 0.05;
		}
	}
}

//===< Ninja Mode >===

doNinja()
{
	if (self.ninjaon == 0)
	{
		self thread Ninja();
		self iPrintlnbold("^5Ninja Mode: ^2On");
		self.ninjaon = 1;
	}
	else
    	{
		self iPrintlnbold("^5Ninja Mode: ^1Off");
		self.ninjaon = 0;
		self notify("stop_ninja");
	}
}
Ninja()
{
	self endon("disconnect");
	self endon("stop_ninja");
	for(;;)
	{
		self cloneplayer(1);
		wait 0.1;
	}
}

//-----[ Visions List ]-----

EMPv()
{
	if(self.empv == 0)
	{
		self setempjammed(1);
		self iPrintlnbold("^5EMP Vision: ^2On");
		self.empv = 1;
	}
	else
	{
		self setempjammed(0);
		self iPrintlnbold("^5EMP Vision: ^1Off");
		self.empv = 0;
	}
}

Thermalv()
{
	if(self.thermv == 0)
	{
		self setinfraredvision(1);
		self iPrintlnbold("^5Thermal Vision: ^2On");
		self.thermv = 1;
	}
	else
	{
		self setinfraredvision(0);
		self iPrintlnbold("^5Thermal Vision: ^1Off");
		self.thermv = 0;
	}
}

switchSetVision(enab, code, name)
{
	if(enab == 1)
	{
		self useServerVisionSet(true);
		self SetVisionSetforPlayer(code, 0);
		self iPrintlnbold("^5" + name + ": ^2On");
	}
	else
	{
		self useServerVisionSet(false);
		self iPrintlnbold("^5" + name + ": ^1Off");
	}
}

BWV()
{
	if(self.bw == 0)
	{
		self.bw = 1;
		self switchSetVision(1, "mpintro", "Black and White");
	}
	else
	{
		self.bw = 0;
		self switchSetVision(0, "", "Black and White");
	}
}

LVis()
{
	if(self.lv == 0)
	{
		self.lv = 1;
		self switchSetVision(1, "taser_mine_shock", "Light Vision");
	}
	else
	{
		self.lv = 0;
		self switchSetVision(0, "", "Light Vision");
	}
}

EV()
{
	if(self.ev == 0)
	{
		self.ev = 1;
		self switchSetVision(1, "remote_mortar_enhanced", "Enhanced Vision");
	}
	else
	{
		self.ev = 0;
		self switchSetVision(0, "", "Enhanced Vision");
	}
}

//-----[ Models List ]-----

setDefoModel()
{
	self [[game["set_player_model"][self.team]["default"]]]();
	self iPrintlnbold("^3Set Model to ^6Default");
}
switchModelChange(code, name)
{
	self setModel(code);
	self iPrintlnbold("^3Set Model to ^6" + name);
}
SetModelDefoact()
{
	self switchModelChange("defaultactor", "Debug");
}
SetModelDog()
{
	self switchModelChange("german_shepherd", "Dog");
}
SetModelHKiller()
{
	self switchModelChange("veh_t6_drone_hunterkiller", "Hunter Killer");
}
SetModelTrosys()
{
	self switchModelChange("t6_wpn_trophy_system_world", "Trophy System");
}
SetModelAssaDro()
{
	self switchModelChange("veh_t6_drone_tank", "Assault Drone");
}
SetModelAttackHeli()
{
	self switchModelChange("veh_t6_air_attack_heli_mp_light", "Attack Helicopter");
}
SetModelOspley()
{
	self switchModelChange("veh_t6_air_v78_vtol_killstreak", "Warthog");
}
SetModelOverwatch()
{
	self switchModelChange("veh_t6_drone_overwatch_dark", "Little Bird");
}
SetModelUAV()
{
	self switchModelChange("veh_t6_drone_uav", "UAV");
}
SetModelCareP()
{
	self switchModelChange("t6_wpn_supply_drop_ally", "Care Package");
}
SetModelTurret()
{
	self switchModelChange("t6_wpn_turret_sentry_gun", "Sentry Gun");
}
SetModelStealth()
{
	self switchModelChange("veh_t6_drone_pegasus_mp", "Stealth Bomber");
}
SetModelHarrier()
{
	self switchModelChange("veh_t6_air_fa38_killstreak", "Harrier");
}

//-----[ VIP Menu ]-----

alwaysVSAT()
{
	if(self.vsatOn == 0)
	{
		self.vsatOn = 1;
		self thread doVSATv2();
		self iPrintlnbold("^5Always VSAT: ^2On");
	}
	else
	{
		self.vsatOn = 0;
		self notify("stop_VSAT");
		self iPrintlnbold("^5Always VSAT: ^1Off");
		self iPrintln("^3This power will disappear in about ^645 sec after");
	}
}
doVSATv2()
{
	self endon("disconnect");
	self endon("stop_VSAT");
	for(;;)
	{
		self maps\mp\killstreaks\_spyplane::callsatellite("radardirection_mp");
		wait 40;
	}
}

doKillstreaks()
{
	if (self.Killstreaks == 0)
	{
		self.Killstreaks = 1;
		self thread KillstreaksOn();
		self iPrintlnbold("^5Unlimited Killstreaks: ^2On");
	}
	else
	{
		self.Killstreaks = 0;
		maps/mp/gametypes/_globallogic_score::_setplayermomentum(self, 0);
		self iPrintlnbold("^5Unlimited Killstreaks: ^1Off");
		self notify("stop_killstreaks");
	}
}
KillstreaksOn()
{
	self endon("disconnect");
	self endon("stop_killstreaks");
	for(;;)
	{
		maps/mp/gametypes/_globallogic_score::_setplayermomentum(self, 9999);
		wait 20;
	}
}

switchClientSpeed(num, scale, print, enab)
{
	self.clientsspeed = num;
	self setmovespeedscale(scale);
	self iPrintln("^3Speed Scale: ^6x" + print);
	if(enab == 1)
	{
		self iPrintlnbold("^5Client Speed: ^2On");
		self thread loopCSpeed();
	}
	else if(enab == 2)
	{
	
	}
	else if(enab == 0)
	{
		self iPrintlnbold("^5Client Speed: ^1Off");
		self notify("stop_loopCSpeed");
	}
}
doClientsSpeed()
{
	if(self.clientsspeed == 0)
	{
		self switchClientSpeed(1, 2, "2", 1);
	}
	else if(self.clientsspeed == 1)
	{
		self switchClientSpeed(2, 3, "3", 2);
	}
	else if(self.clientsspeed == 2)
	{
		self switchClientSpeed(3, 4, "4", 2);
	}
	else if(self.clientsspeed == 3)
	{
		self switchClientSpeed(4, 5, "5", 2);
	}
	else if(self.clientsspeed == 4)
	{
		self switchClientSpeed(0, 1, "1", 0);
	}
}
loopCSpeed()
{
	self endon("disconnect");
	self endon("stop_loopCSpeed");
	for(;;)
	{
		self waittill("spawned_player");
		if(self.clientsspeed == 0)
		{
			self setmovespeedscale(2);
		}
		else if(self.clientsspeed == 1)
		{
			self setmovespeedscale(3);
		}
		else if(self.clientsspeed == 2)
		{
			self setmovespeedscale(4);
		}
		else if(self.clientsspeed == 3)
		{
			self setmovespeedscale(5);
		}
	}
}

TeleportWithiPad()
{
	self beginLocationSelection( "map_mortar_selector" ); 
	self disableoffhandweapons();
	self giveWeapon("killstreak_remote_turret_mp", 0, false);
	self switchToWeapon("killstreak_remote_turret_mp");
	self.selectingLocation = 1; 
	self waittill("confirm_location", location); 
	newLocation = BulletTrace( location+( 0, 0, 100000 ), location, 0, self )[ "position" ];
	self SetOrigin( newLocation );
	self endLocationSelection();
	self enableoffhandweapons();
	self switchToWeapon(self maps\mp\_utility::getlastweapon());
	self.selectingLocation = undefined;
	self iPrintlnbold("^2Teleported!");
}

vector_scal(vec, scale)
{
	vec = (vec[0] * scale, vec[1] * scale, vec[2] * scale);
	return vec;
}

doJetPack()
{
	if(self.jetpack == 0)
	{
		self thread StartJetPack();
		self iPrintlnbold("^5JetPack: ^2On");
		self iPrintln("Press [{+gostand}] & [{+usereload}]");
		self.jetpack = 1;
	}
	else
	{
		self.jetpack = 0;
		self notify("jetpack_off");
		self iPrintlnbold("^5JetPack: ^1Off");
	}
}
StartJetPack()
{
	self endon("jetpack_off");
	self endon("death");
	self.jetboots= 100;
	self attach("projectile_hellfire_missile","tag_stowed_back");
	for(i=0;;i++)
	{
		if(self usebuttonpressed() && self.jetboots>0)
		{
		    self playsound( "veh_huey_chaff_explo_npc" );
			playFX( level._effect[ "flak20_fire_fx" ], self getTagOrigin( "J_Ankle_RI" ) );
			playFx( level._effect[ "flak20_fire_fx" ], self getTagOrigin( "J_Ankle_LE" ) );
			earthquake(.15,.2,self gettagorigin("j_spine4"),50);
			self.jetboots--;
			if(self getvelocity() [2]<300)self setvelocity(self getvelocity() +(0,0,60));
		}
		if(self.jetboots<100 &&!self usebuttonpressed() )self.jetboots++;
		wait .05;
	}
}

Earthquake_gun()
{
	self endon("disconnect");
	self endon("stop_EarthQGun");
	if(!isDefined(self.isEarthQuake))
	{
		self.isEarthQuake = true;
		self.Quake_Gun = self getCurrentWeapon();
	}
	else
	{
		self.isEarthQuake = undefined;
		self.Quake_Gun = undefined;
	}

	self iPrintln("Earthquake Gun "+boolTxt(self.isEarthQuake));

	while(isDefined(self.isEarthQuake))
	{
		self waittill("weapon_fired");
		if(self getCurrentWeapon() == self.Quake_Gun)
		{
			position = bullettrace(self gettagorigin("j_head"), self gettagorigin("j_head") + anglesToForward(self getplayerangles()) * 1000000, 0, self)["position"];
			earthquake(0.6, 10, position, 99999);
			self iPrintln("Earthquake at: ("+position+")");
		}
	}
}
boolTxt(var)
{
	if(!isDefined(var))
		return "Disabled";
	else
		return "Enabled";
}
doEarthQGun()
{
	if(self.EarthQGun == 0)
	{
		self.EarthQGun = 1;
		self thread Earthquake_gun();
		self iPrintlnbold("^5Earthquake Gun: ^2On");
	}
	else
	{
		self.EarthQGun = 0;
		self notify("stop_EarthQGun");
		self iPrintlnbold("^5Earthquake Gun: ^1Off");
	}
}

walkingLoadestar()
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_WLStar");
	self GiveKillstreak("killstreak_remote_mortar");
	self iPrintlnbold("^5Walking Loadstar: ^2On");
	self iPrintln("^3You will Death to ^6Stop Walking Loadstar");
	self.WLStarFly = 0;
	WLStarUFO = spawn("script_model", self.origin);
	for(;;)
	{
		if(self.WLStarFly == 1)
		{
			self playerLinkTo(WLStarUFO);
			self.WLStarFly = 1;
		}
		else
		{
			self unlink();
			self.WLStarFly = 0;
		}
		if(self.WLStarFly == 1)
		{
			WLStarFly = self.origin + vector_scal(anglesToForward(self getPlayerAngles()),20);
			WLStarUFO moveTo(WLStarFly, .01);
		}
		wait .001;
	}
}

initHTorch()
{
	if(self.torchOn == 0)
	{
		self.torchOn = 1;
		self thread humanTorch();
		self iPrintlnbold("^5Human Torch: ^2On");	
	}
	else
	{
		self.torchOn = 0;
		self notify("stop_torch");
		self disableInvulnerability();
		self iPrintlnbold("^5Human Torch: ^1Off");
	}
}
humanTorch()
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_torch");

	level._effect["torch"] = loadfx( "maps/mp_maps/fx_mp_exp_rc_bomb" );
	self enableInvulnerability();
	while(1)
	{
		PlayFX(level._effect["torch"],self.origin+(0,0,60));
		RadiusDamage(self.origin, 300, 300, 200, self);
		wait 0.1;
	}
}

initWFountain()
{
	if(self.WFountainOn == 0)
	{
		self.WFountainOn = 1;
		self thread doWFountain();
   		self iPrintlnbold("^5Water Fountain: ^2On");
   		self iPrintln("^1Can not be used in the map with no water.");
	}
	else
	{
		self.WFountainOn = 0;
		self notify("stop_WFountain");
		self disableInvulnerability();
   		self iPrintlnbold("^5Water Fountain: ^1Off");
	}
}
doWFountain()
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_WFountain");
	self enableInvulnerability();
	for(;;)
	{
		level._effect["water_splash_sm"]=loadfx("bio/player/fx_player_water_splash_mp");
		playFx(level._effect["water_splash_sm"],self getTagOrigin("j_spine4"));
		RadiusDamage(self.origin, 400, 400, 300, self);
		wait .001;
	}
}

initSmokeMonster()
{
	if(self.smokemonsterr == 0)
	{
		self.smokemonsterr = 1;
		self iPrintlnbold("^5Smoke Monster: ^2On");
		self thread doSmokeMonster();
	}
	else
	{
		self.smokemonsterr = 0;
		self iPrintlnbold("^5Smoke Monster: ^1Off");
		self notify("stop_smokemonster");
	}
}
doSmokeMonster()
{
	self endon( "disconnect" );
	self endon( "stop_smokemonster" );
	for(;;)
	{
		spawntimedfx(level.fx_smokegrenade_single, self getTagOrigin("j_spine4"), ( 0, 0, 1 ), 6 );
		wait 0.2;
	}
}

//-----[ Give Killstreaks Menu ]-----

GiveKillstreak(killstreak)
{
	self maps/mp/killstreaks/_killstreaks::givekillstreak(maps/mp/killstreaks/_killstreaks::getkillstreakbymenuname(killstreak) , 5594, true, 5594);
}
initGiveKS(code, name, patt)
{
	self iPrintlnbold("^3Give Killstreak ^6" + name);
	if(patt == 0)
	{
		self GiveKillstreak(code);
	}
	else if(patt == 1)
	{
		self GiveWeapon(code, 0, false);
		self switchToWeapon(code);
	}
}
KSGiveUAV()
{
	self initGiveKS("killstreak_spyplane", "UAV", 0);
}
KSGiveRC()
{
	self initGiveKS("killstreak_rcbomb", "RC-XD", 0);
}
KSGiveHunt()
{
	self initGiveKS("missile_drone_mp", "Hunter Killer", 1);
}
KSGiveCare()
{
	self initGiveKS("supplydrop_mp", "Care Package", 1);
}
KSGiveCUAV()
{
	self initGiveKS("killstreak_counteruav", "Counter UAV", 0);
}
KSGiveGaurd()
{
	self initGiveKS("microwaveturret_mp", "Gaurdian", 1);
}
KSGiveHell()
{
	self initGiveKS("killstreak_remote_missile", "Hellstorm Missle", 0);
}
KSGiveLS()
{
	self initGiveKS("killstreak_planemortar", "Lightning Strike", 0);
}
KSGiveSG()
{
	self initGiveKS("autoturret_mp", "Sentry Gun", 1);
}
KSGiveAG()
{
	self initGiveKS("ai_tank_drop_mp", "A.G.R", 1);
}
KSGiveSC()
{
	self initGiveKS("killstreak_helicopter_comlink", "Stealth Chopper", 0);
}
KSGiveVSAT()
{
	self initGiveKS("killstreak_spyplane_direction", "Orbital VSAT", 0);
}
KSGiveED()
{
	self initGiveKS("killstreak_helicopter_guard", "Escort Drone", 0);
}
KSGiveEMP()
{
	self initGiveKS("emp_mp", "EMP System", 1);
}
KSGiveWH()
{
	self initGiveKS("killstreak_straferun", "Warthog", 0);
}
KSGiveLST()
{
	self initGiveKS("killstreak_remote_mortar", "Loadestar", 0);
}
KSGiveVW()
{
	self initGiveKS("helicopter_player_gunner_mp", "VTOL Warship", 1);
}
KSGiveSwarm()
{
	self initGiveKS("killstreak_missile_swarm", "Swarm", 0);
}

//-----[ Account Menu ]-----

doMaster()
{
    self.pres[ "prestige" ] = self.maxprestige;
    self setdstat( "playerstatslist", "plevel", "StatValue", self.maxprestige );
    self setrank( self.maxprestige );
    self iPrintlnbold("^5Prestige 11th ^6Set!");
}
doRank()
{
    self.pers["rank"] = level.maxrank;
	self.pers["rankxp"] = maps/mp/gametypes/_rank::getrankinfominxp(level.maxrank);
    self setrank(level.maxrankrank);
	self maps/mp/gametypes/_rank::syncxpstat();
    self setdstat("playerstatslist", "rank", "StatValue", level.maxrank);
    self iPrintlnbold("^3Set ^6Level 55");
}
unlockAllCheevos()
{
	self thread maps\mp\gametypes\_hud_message::hintMessage("^1All Trophys Unlocking Now...\n^3Please wait some times ^4(^v^)", 10);

   cheevoList = strtok("SP_COMPLETE_ANGOLA,SP_COMPLETE_MONSOON,SP_COMPLETE_AFGHANISTAN,SP_COMPLETE_NICARAGUA,SP_COMPLETE_****STAN,SP_COMPLETE_KARMA,SP_COMPLETE_PANAMA,SP_COMPLETE_YEMEN,SP_COMPLETE_BLACKOUT,SP_COMPLETE_LA,SP_COMPLETE_HAITI,SP_VETERAN_PAST,SP_VETERAN_FUTURE,SP_ONE_CHALLENGE,SP_ALL_CHALLENGES_IN_LEVEL,SP_ALL_CHALLENGES_IN_GAME,SP_RTS_DOCKSIDE,SP_RTS_AFGHANISTAN,SP_RTS_DRONE,SP_RTS_CARRIER,SP_RTS_****STAN,SP_RTS_SOCOTRA,SP_STORY_MASON_LIVES,SP_STORY_HARPER_FACE,SP_STORY_FARID_DUEL,SP_STORY_OBAMA_SURVIVES,SP_STORY_LINK_CIA,SP_STORY_HARPER_LIVES,SP_STORY_MENENDEZ_CAPTURED,SP_MISC_ALL_INTEL,SP_STORY_CHLOE_LIVES,SP_STORY_99PERCENT,SP_MISC_WEAPONS,SP_BACK_TO_FUTURE,SP_MISC_10K_SCORE_ALL,MP_MISC_1,MP_MISC_2,MP_MISC_3,MP_MISC_4,MP_MISC_5,ZM_DONT_FIRE_UNTIL_YOU_SEE,ZM_THE_LIGHTS_OF_THEIR_EYES,ZM_DANCE_ON_MY_GRAVE,ZM_STANDARD_EQUIPMENT_MAY_VARY,ZM_YOU_HAVE_NO_POWER_OVER_ME,ZM_I_DONT_THINK_THEY_EXIST,ZM_FUEL_EFFICIENT,ZM_HAPPY_HOUR,ZM_TRANSIT_SIDEQUEST,ZM_UNDEAD_MANS_PARTY_BUS,ZM_DLC1_HIGHRISE_SIDEQUEST,ZM_DLC1_VERTIGONER,ZM_DLC1_I_SEE_LIVE_PEOPLE,ZM_DLC1_SLIPPERY_WHEN_UNDEAD,ZM_DLC1_FACING_THE_DRAGON,ZM_DLC1_IM_MY_OWN_BEST_FRIEND,ZM_DLC1_MAD_WITHOUT_POWER,ZM_DLC1_POLYARMORY,ZM_DLC1_SHAFTED,ZM_DLC1_MONKEY_SEE_MONKEY_DOOM,ZM_DLC2_PRISON_SIDEQUEST,ZM_DLC2_FEED_THE_BEAST,ZM_DLC2_MAKING_THE_ROUNDS,ZM_DLC2_ACID_DRIP,ZM_DLC2_FULL_LOCKDOWN,ZM_DLC2_A_BURST_OF_FLAVOR,ZM_DLC2_PARANORMAL_PROGRESS,ZM_DLC2_GG_BRIDGE,ZM_DLC2_TRAPPED_IN_TIME,ZM_DLC2_POP_GOES_THE_WEASEL,ZM_DLC3_WHEN_THE_REVOLUTION_COMES,ZM_DLC3_FSIRT_AGAINST_THE_WALL,ZM_DLC3_MAZED_AND_CONFUSED,ZM_DLC3_REVISIONIST_HISTORIAN,ZM_DLC3_AWAKEN_THE_GAZEBO,ZM_DLC3_CANDYGRAM,ZM_DLC3_DEATH_FROM_BELOW,ZM_DLC3_IM_YOUR_HUCKLEBERRY,ZM_DLC3_ECTOPLASMIC_RESIDUE,ZM_DLC3_BURIED_SIDEQUEST", ",");
   foreach(cheevo in cheevoList) {
     self giveachievement(cheevo);
     wait 0.25;
   }
}
doAllUnlockCamos()
{
	self thread unlockallcamos(i);
	self thread camonlock();
	self thread maps\mp\gametypes\_hud_message::hintMessage("^3Weapon's Camo ^1Unlocked!!", 5);
}
unlockallcamos(i)
{
	self addweaponstat(i, "headshots", 5000 );
	self addweaponstat(i, "kills", 5000 );
	self addweaponstat(i, "direct_hit_kills", 100 );
	self addweaponstat(i, "revenge_kill", 2500 );
	self addweaponstat(i, "noAttKills", 2500 );
	self addweaponstat(i, "noPerkKills", 2500 );
	self addweaponstat(i, "multikill_2", 2500 );
	self addweaponstat(i, "killstreak_5", 2500 );
	self addweaponstat(i, "challenges", 5000 );
	self addweaponstat(i, "multikill_2", 2500 );
	self addweaponstat(i, "killstreak_5", 2500 );
	self addweaponstat(i, "challenges", 5000 );
	self addweaponstat(i, "longshot_kill", 750 );
	self addweaponstat(i, "direct_hit_kills", 120);
	self addweaponstat(i, "destroyed_aircraft_under20s", 120);
	self addweaponstat(i, "destroyed_5_aircraft", 120);
	self addweaponstat(i, "destroyed_aircraft", 120);
	self addweaponstat(i, "kills_from_cars", 120);
	self addweaponstat(i, "destroyed_2aircraft_quickly", 120);
	self addweaponstat(i, "destroyed_controlled_killstreak", 120);
	self addweaponstat(i, "destroyed_qrdrone", 120);
	self addweaponstat(i, "destroyed_aitank", 120);
	self addweaponstat(i, "multikill_3", 120);
	self addweaponstat(i, "score_from_blocked_damage", 140);
	self addweaponstat(i, "shield_melee_while_enemy_shooting", 140);
	self addweaponstat(i, "hatchet_kill_with_shield_equiped", 140);
	self addweaponstat(i, "noLethalKills", 140);
	self addweaponstat(i, "ballistic_knife_kill",5000);
	self addweaponstat(i, "kill_retrieved_blade", 160);
	self addweaponstat(i, "ballistic_knife_melee", 160);
	self addweaponstat(i, "kills_from_cars", 170);
	self addweaponstat(i, "crossbow_kill_clip", 170);
	self addweaponstat(i, "backstabber_kill", 190);
	self addweaponstat(i, "kill_enemy_with_their_weapon", 190);
	self addweaponstat(i, "kill_enemy_when_injured", 190);
	self addweaponstat(i, "primary_mastery",10000);
	self addweaponstat(i, "secondary_mastery",10000);
	self addweaponstat(i, "weapons_mastery",10000);
	self addweaponstat(i, "kill_enemy_one_bullet_shotgun", 5000);
	self addweaponstat(i, "kill_enemy_one_bullet_sniper", 5000);
}
camonlock()
{
	self thread unlockallcamos("870mcs_mp");
	wait 2;
	self thread unlockallcamos("an94_mp");
	wait 2;
	self thread unlockallcamos("as50_mp");
	wait 2;
	self thread unlockallcamos("ballista_mp");
	wait 2;
	self thread unlockallcamos("beretta93r_dw_mp");
	wait 2;
	self thread unlockallcamos("beretta93r_lh_mp");
	wait 2;
	self thread unlockallcamos("beretta93r_mp");
	wait 2;
	self thread unlockallcamos("crossbow_mp");
	wait 2;
	self thread unlockallcamos("dsr50_mp");
	wait 2;
	self thread unlockallcamos("evoskorpion_mp");
	wait 2;
	self thread unlockallcamos("fiveseven_dw_mp");
	wait 2;
	self thread unlockallcamos("fiveseven_lh_mp");
	wait 2;
	self thread unlockallcamos("fiveseven_mp");
	wait 2;
	self thread unlockallcamos("fhj18_mp");
	wait 2;
	self thread unlockallcamos("fnp45_dw_mp");
	wait 2;
	self thread unlockallcamos("fnp45_lh_mp");
	wait 2;
	self thread unlockallcamos("fnp45_mp");
	wait 2;
	self thread unlockallcamos("hamr_mp");
	wait 2;
	self thread unlockallcamos("hk416_mp");
	wait 2;
	self thread unlockallcamos("insas_mp");
	wait 2;
	self thread unlockallcamos("judge_dw_mp");
	wait 2;
	self thread unlockallcamos("judge_lh_mp");
	wait 2;
	self thread unlockallcamos("judge_mp");
	wait 2;
	self thread unlockallcamos("kard_dw_mp");
	wait 2;
	self thread unlockallcamos("kard_lh_mp");
	wait 2;
	self thread unlockallcamos("kard_mp");
	wait 2;
	self thread unlockallcamos("kard_wager_mp");
	wait 2;
	self thread unlockallcamos("knife_ballistic_mp");
	wait 2;
	self thread unlockallcamos("knife_held_mp");
	wait 2;
	self thread unlockallcamos("knife_mp");
	wait 2;
	self thread unlockallcamos("ksg_mp");
	wait 2;
	self thread unlockallcamos("lsat_mp");
	wait 2;
	self thread unlockallcamos("mk48_mp");
	wait 2;
	self thread unlockallcamos("mp7_mp");
	wait 2;
	self thread unlockallcamos("pdw57_mp");
	wait 2;
	self thread unlockallcamos("peacekeeper_mp");
	wait 2;
	self thread unlockallcamos("qbb95_mp");
	wait 2;
	self thread unlockallcamos("qcw05_mp");
	wait 2;
	self thread unlockallcamos("riotshield_mp");
	wait 2;
	self thread unlockallcamos("sa58_mp");
	wait 2;
	self thread unlockallcamos("saiga12_mp");
	wait 2;
	self thread unlockallcamos("saritch_mp");
	wait 2;
	self thread unlockallcamos("scar_mp");
	wait 2;
	self thread unlockallcamos("sig556_mp");
	wait 2;
	self thread unlockallcamos("smaw_mp");
	wait 2;
	self thread unlockallcamos("srm1216_mp");
	wait 2;
	self thread unlockallcamos("svu_mp");
	wait 2;
	self thread unlockallcamos("tar21_mp");
	wait 2;
	self thread unlockallcamos("type95_mp");
	wait 2;
	self thread unlockallcamos("usrpg_mp");
	wait 2;
	self thread unlockallcamos("vector_mp");
	wait 2;
	self thread unlockallcamos("xm8_mp");
}
ColoredClass()
{
	self iPrintlnBold("^3Custom Class Color is ^1C^2o^3l^4o^5r^6f^7u^8l^9!!");
	level.classmap["^F^1Class 1"] = "CLASS_CUSTOM1";
	level.classmap["^F^3Class 2"] = "CLASS_CUSTOM2";
	level.classmap["^F^2Class 3"] = "CLASS_CUSTOM3";
	level.classmap["^F^5Class 4"] = "CLASS_CUSTOM4";
	level.classmap["^F^6Class 5"] = "CLASS_CUSTOM5";
	level.classmap["^F^9Class 6"] = "CLASS_CUSTOM6";
	level.classmap["^F^3Class 7"] = "CLASS_CUSTOM7";
	level.classmap["^F^4Class 8"] = "CLASS_CUSTOM8";
	level.classmap["^F^2Class 9"] = "CLASS_CUSTOM9";
	level.classmap["^F^5Class 10"] = "CLASS_CUSTOM10";
}
selfDerank()
{
	self.pres["prestige"] = self.minprestige;
	self setdstat("playerstatslist", "plevel", "StatValue", self.minprestige);
	self setrank(self.minprestige);
	self.pres["rank"] = self.minrank;
	self setdstat("playerstatslist", "rank", "StatValue", self.minrank);
	self setrank(self.minrank);

	self iPrintlnbold("^3You are ^6Deranked!!");
}

//-----[ Weapons Menu ]-----

ExpBultOn()
{
    if (self.ExpBult == 0)
    {
		self notify("stop_NonFXExpBult");
		self.NonFXExpBultOn = 0;
        self thread doExplosiveBullets();
        self iPrintlnbold("^5Explosive Bullets: ^2On");
        self.ExpBult = 1;
    }
    else
    {
        self notify("stop_ExpBult");
        self.ExpBult = 0;
		self iprintlnbold("^5Explosive Bullets: ^1Off");
    }
}
doExplosiveBullets()
{
	self endon("disconnect");
	self endon("stop_ExpBult");
	level.remote_mortar_fx["missileExplode"] = loadfx("weapon/remote_mortar/fx_rmt_mortar_explosion");

	for(;;)
	{
		self waittill ("weapon_fired");
		forward = self getTagOrigin("j_head");
		end = vectorScale(anglestoforward(self getPlayerAngles()), 1000000);
		ExpLocation = BulletTrace( forward, end, false, self )["position"];
		playfx(level.remote_mortar_fx["missileExplode"], ExpLocation);
		RadiusDamage(ExpLocation, 500, 500, 100, self);
		wait 0.05;
	}
}

initNonFXExpBult()
{
	if(self.NonFXExpBultOn == 0)
	{
        self notify("stop_ExpBult");
        self.ExpBult = 0;
		self thread doNonFXExpBult();
		self.NonFXExpBultOn = 1;
		self iPrintlnbold("^5Non Effects Explosive Bullets: ^2On");
	}
	else
	{
		self notify("stop_NonFXExpBult");
		self.NonFXExpBultOn = 0;
		self iPrintlnbold("^5Non Effects Explosive Bullets: ^1Off");
	}
}
doNonFXExpBult()
{
	self endon("stop_NonFXExpBult");
	for(;;)
	{
		self waittill ("weapon_fired");
		forward = self getTagOrigin("j_head");
		end = self thread vector_scal(anglestoforward(self getPlayerAngles()),2147483600);
		SPLOSIONlocation = BulletTrace( forward, end, 2147483600, self )[ "position" ];
		RadiusDamage( SPLOSIONlocation, 999999, 999999, 999999, self );
	}
}

initWGun()
{
	if(self.WGunOn == 0)
	{
		self.WGunOn = 1;
   		self iPrintlnbold("^5Water Gun: ^2On");
   		self iPrintln("^1Can not be used in the map with no water.");
		self thread doWGun();
	}
	else
	{
		self.WGunOn = 0;
   		self iPrintlnbold("^5Water Gun: ^1Off");
		self notify("stop_WGun");
	}
}
doWGun()
{
	self endon("disconnect");
	self endon("stop_WGun");
	for(;;)
	{
		self waittill ("weapon_fired");
		forward = self getTagOrigin("j_head");
		end = vectorScale(anglestoforward(self getPlayerAngles()), 1000000);
		ExpLocation = BulletTrace( forward, end, false, self )["position"];
		level._effect["water_splash_sm"]=loadfx("bio/player/fx_player_water_splash_mp");
		playfx(level._effect["water_splash_sm"], ExpLocation);
		RadiusDamage(ExpLocation, 200, 200, 100, self);
		wait 0.005;
	}
}

ToggleTeleportGun()
{
    if (self.TPG == true)
    {
        self thread TeleportGun();
        self iPrintlnbold("^5Teleport Gun: ^2On");
        self.TPG = false;
    }
    else
    {
        self notify("Stop_TP");
        self iprintlnbold("^5Teleport Gun: ^1Off");
        self.TPG = true;
    }
}
TeleportGun()
{
    self endon("disconnect");
    self endon("Stop_TP");
    for(;;)
    {
        self waittill("weapon_fired");
        self setorigin(bullettrace(self gettagorigin("j_head"), self gettagorigin("j_head") + anglesToForward(self getplayerangles()) * 1000000, 0, self)["position"]);
    }
}

TakeWeapon()
{
	self takeallweapons();
    self iPrintlnbold("^3Weapons ^6Taked!");
}

ThunGun()
{
    self endon("disconnect");
    self endon("death");
    level.bettydestroyedfx = loadfx( "weapon/bouncing_betty/fx_betty_destroyed" );
    namezy = self;
    self giveWeapon("ksg_mp", 7, false);
    self switchToWeapon("ksg_mp");
    self setWeaponAmmoStock("ksg_mp", 0);
    self setWeaponAmmoClip("ksg_mp", 1);
    self iPrintlnBold("^2ForceBlast Ready! ^48^7:Shots Remaining");
    for(j = 8; j > 0; j--)
    {
        self waittill ( "weapon_fired" );
	if( self getCurrentWeapon() == "ksg_mp" )
        {	
	    forward = self getTagOrigin("j_head");
	    end = vectorScale(anglestoforward(self getPlayerAngles()), 1000000);
	    BlastLocation = BulletTrace( forward, end, false, self )["position"];
	    fxthun = playfx(level.bettydestroyedfx, self getTagOrigin("tag_weapon_right"));
	    fxthun.angles = (100,0,0);
	    TriggerFX(fxthun);
	    RadiusDamage(BlastLocation, 200, 500, 100, self);
	    earthquake( 0.9, 0.9, self.origin, 600 );
	    PlayRumbleOnPosition( "grenade_rumble", self.origin );
	    foreach(player in level.players)
	    {
                if(player.team != self.team)
                {
                    if(Distance(self.origin, player.origin) < 600)
		    {
		        player thread ThunDamage();
		    }
                 }
             }
	     self switchToWeapon("ksg_mp");
	     wait 0.8;
	     wait .5;
	     bulletz = (j - 1);
	     self iPrintlnBold("^2ForceBlast Ready. ^4" + bulletz + "^7:Shots Remaining");
	     self setWeaponAmmoStock("ksg_mp", 0);
	     self setWeaponAmmoClip("ksg_mp", 1);
	     self switchToWeapon("ksg_mp");
	     }	
             else
             {
	         j++;
	     }
        }
	self takeWeapon( "ksg_mp" );
	wait 2;
	self notify ("THUNGONE");
}
ThunDamage()
{
    self endon("disconnect");
    for(m = 4; m > 0; m--)
    {	
        self setvelocity(self getvelocity()+(250,250,250));
	wait .1;
    }
    self setvelocity(0,0,0);
    wait 7;
}

initNukeBullets()
{
    if (self.NukeBulletsOn == 0)
    {
        self.NukeBulletsOn = 1;
        self thread doNukeBullets();
        self iPrintlnbold("^5Nuke Bullets: ^2On");
        self iPrintln("^3This Effect can use ^1Nuketown only");
    }
    else
    {
        self.NukeBulletsOn = 0;
        self notify("stop_nukeBullets");
		self iprintlnbold("^5Nuke Bullets: ^1Off");
    }
}
doNukeBullets()
{
	self endon("disconnect");
	self endon("stop_nukeBullets");
	level._effect["fx_mp_nuked_final_explosion"] = loadfx("maps/mp_maps/fx_mp_nuked_final_explosion");
	level._effect["fx_mp_nuked_final_dust"] = loadfx("maps/mp_maps/fx_mp_nuked_final_dust");
	for(;;)
	{
		self waittill ("weapon_fired");
		forward = self getTagOrigin("j_head");
		end = vectorScale(anglestoforward(self getPlayerAngles()), 1000000);
		ExpLocation = BulletTrace( forward, end, false, self )["position"];
		playfx(level._effect["fx_mp_nuked_final_explosion"], ExpLocation);
		playfx(level._effect["fx_mp_nuked_final_dust"], ExpLocation);
		earthquake(0.6, 8.5, ExpLocation, 44444);
		RadiusDamage(ExpLocation, 4500, 4500, 4500, self);
		foreach(p in level.players)
		{
			p playsound("amb_end_nuke");
		}
		wait 0.05;
	}
}

initEMPBullets()
{
    if (self.EMPBulletsOn == 0)
    {
        self.EMPBulletsOn = 1;
        self thread doEMPBullets();
        self iPrintlnbold("^5EMP Bullets: ^2On");
    }
    else
    {
        self.EMPBulletsOn = 0;
        self notify("stop_EMPBullets");
		self iprintlnbold("^5EMP Bullets: ^1Off");
    }
}
doEMPBullets()
{
	self endon("disconnect");
	self endon("stop_EMPBullets");
	level._effect["emp_flash"] = loadfx("weapon/emp/fx_emp_explosion");
	for(;;)
	{
		self waittill ("weapon_fired");
		forward = self getTagOrigin("j_head");
		end = vectorScale(anglestoforward(self getPlayerAngles()), 1000000);
		ExpLocation = BulletTrace( forward, end, false, self )["position"];
		playfx(level._effect["emp_flash"], ExpLocation);
		earthquake(0.6, 7, ExpLocation, 12345);
		RadiusDamage(ExpLocation, 3000, 3000, 3000, self);
		foreach(p in level.players)
		{
			p playsound("wpn_emp_bomb");
		}
		wait 0.05;
	}
}

//-----[ Weapons List ]-----

giveWdmachine()
{
	self initGiveWeap("minigun_mp", "Death Machine", 1);
}
giveWWMachine()
{
	self initGiveWeap("m32_mp", "War Machine", 1);
}
giveWan()
{
	self initGiveWeap("an94_mp", "AN-94", 1);
}
giveWlsat()
{
	self initGiveWeap("lsat_mp", "LSAT", 1);
}
giveWpkeep()
{
	self initGiveWeap("peacekeeper_mp", "Peacekeeper", 1);
}
giveWscar()
{
	self initGiveWeap("scar_mp", "SCAR-H", 1);
}
giveWbalista()
{
	self initGiveWeap("ballista_mp", "DBalista", 1);
}
giveWdsr()
{
	self initGiveWeap("dsr50_mp", "DSR 50", 1);
}
giveWmcs()
{
	self initGiveWeap("870mcs_mp", "R-870 MCS", 1);
}
giveWcrsb()
{
	self initGiveWeap("crossbow_mp", "Crossbow", 1);
}
giveWrpg()
{
	self initGiveWeap("usrpg_mp", "RPG", 1);
}
giveRWeapon()
{
	id = random(level.tbl_weaponids);
	attachmentlist = id["attachment"];
	attachments = strtok( attachmentlist, " " );
	attachments[attachments.size] = "";
	attachment = random(attachments);
	self GiveWeapon((id["reference"] + "_mp+") + attachment, 0, false);
	self iPrintlnbold("^3Give ^6Random Weapon!");
}
giveWdefowep()
{
	self initGiveWeap("defaultweapon_mp", "Default Weapon", 1);
}

//-----[ Bullets List ]-----

initMagicBullet()
{
	if(self.mBulletOn == 0)
	{
		self.mBulletOn = 1;
		if(self.MBcheck == 0)
		{
			self selectMBsmaw();
		}
		self thread doMagicBullet();
		self iPrintlnbold("^5Modded Bullet: ^2On");
	}
	else
	{
		self.mBulletOn = 0;
		self notify("stop_magicBullet");
		self iPrintlnbold("^5Modded Bullet: ^1Off");
		self iPrintln("^3Select Bullet: ^6Nomal");
	}
}
doMagicBullet()
{
	self endon("disconnect");
	self endon("stop_magicBullet");

	for(;;)
	{
		self waittill("weapon_fired");
		MagicBullet(self.selectModBullet, self getEye(), self traceBullet(), self);
	}
}
doChangeMBullet(weap, printweap)
{
	self.selectModBullet = weap;
	self iPrintln("^3Select Bullet: ^6" + printweap);
	self.MBcheck = 1;
}
selectMBsmaw()
{
	self doChangeMBullet("smaw_mp", "SMAW");
}
selectMBgrenade()
{
	self doChangeMBullet("m32_mp", "Grenade");
}
selectMBagr()
{
	self doChangeMBullet("ai_tank_drone_rocket_mp", "A.G.R Rocket");
}
selectMBwarthog()
{
	self doChangeMBullet("straferun_rockets_mp", "Warthog Rockets");
}
selectMBburner()
{
	self doChangeMBullet("remote_missile_bomblet_mp", "Mortar Missile Burner");
}
selectMBhgr()
{
	self doChangeMBullet("heli_gunner_rockets_mp", "Heli Gunner Missile");
}
selectMBswarm()
{
	self doChangeMBullet("missile_swarm_projectile_mp", "Swarm");
}
selectMBhkill()
{
	self doChangeMBullet("missile_drone_projectile_mp", "Hanter Killer");
}
selectMBrmmm()
{
	self doChangeMBullet("remote_missile_missile_mp", "Remote Mortar Missile");
}
selectMBmcs()
{
	self doChangeMBullet("870mcs_mp", "R-870 MCS");
}
selectMBlstar()
{
	self doChangeMBullet("remote_mortar_missile_mp", "Loadstar");
}

//-----[ Special Bullets ]-----

initMagicGrenade()
{
	if(self.mLTOn == 0)
	{
		self.mLTOn = 1;
		if(self.MLTcheck == 0)
		{
			self selectMLTc4();
		}
		self thread doMagicLT();
		self iPrintlnbold("^5Lethal/Tactical Bullet: ^2On");
	}
	else
	{
		self.mLTOn = 0;
		self notify("stop_magicLT");
		self iPrintlnbold("^5Lethal/Tactical Bullet: ^1Off");
		self iPrintln("^3Select Bullet: ^6Nomal");
	}
}
doMagicLT()
{
	self endon("disconnect");
	self endon("stop_magicLT");

	for(;;)
	{
		self waittill("weapon_fired");
		GrenadeDirection = VectorNormalize(anglesToForward(self getPlayerAngles()));
		Velocity = VectorScale(GrenadeDirection, 5000);
		self MagicGrenadeType(self.selectMLT, self getEye(), Velocity, 2);
	}
}
doChangeMLT(weap, printweap)
{
	self.selectMLT = weap;
	self iPrintln("^3Select Bullet: ^6" + printweap);
	self.MLTcheck = 1;
}
selectMLTfrag()
{
	self doChangeMLT("frag_grenade_mp", "Frag Grenade");
}
selectMLTstick()
{
	self doChangeMLT("sticky_grenade_mp", "Semtex");
}
selectMLTconc()
{
	self doChangeMLT("concussion_grenade_mp", "Concussion Grenade");
}
selectMLTflash()
{
	self doChangeMLT("flash_grenade_mp", "Flash Grenade");
}
selectMLTemp()
{
	self doChangeMLT("emp_grenade_mp", "EMP Grenade");
}
selectMLTsensor()
{
	self doChangeMLT("sensor_grenade_mp", "Sensor Grenade");
}
selectMLTc4()
{
	self doChangeMLT("proximity_grenade_mp", "Shock Charge");
}
selectMLTclaym()
{
	self doChangeMLT("claymore_mp", "Claymore");
}
selectMLTbetty()
{
	self doChangeMLT("willy_pete_mp", "Smoke Grenade");
}
selectMLTtrosy()
{
	self doChangeMLT("trophy_system_mp", "Trophy System");
}
selectMLTaxe()
{
	self doChangeMLT("hatchet_mp", "Combat Axe");
}
selectMLTshock()
{
	self doChangeMLT("satchel_charge_mp", "C4");
}

//-----[ Admin Menu ]-----

giveGod()
{
	if(self.God == 0)
	{
		self enableInvulnerability();
		self thread loopGod();
		self thread fastGod();
		self iPrintlnbold("^5God Mode: ^2On");
		self.God = 1;
	}
	else
	{
		self notify("stop_loopGod");
		self disableInvulnerability();
		self iPrintlnbold("^5God Mode: ^1Off");
		self.God = 0;
	}
}
fastGod()
{
	self endon("stop_loopGod");
	for(;;)
	{
		self enableInvulnerability();
		wait 0.01;
	}
}
loopGod()
{
	self endon("stop_loopGod");
	for(;;)
	{
		self waittill("spawned_player");
		self enableInvulnerability();
	}
}

doInfAmmo()
{
	self endon("disconnect");

	if(self.UAOn == 0)
	{
		self iPrintlnbold("^5Infinity Ammo: ^2On");
		self thread InfAmmo();
		self.UAOn = 1;
	}
	else
	{
		self iPrintlnbold("^5Infinity Ammo: ^1Off");
		self.UAOn = 0;
		self notify("stop_InfAmmo");
	}
}
InfAmmo()
{
	self endon("disconnect");
	self endon("stop_InfAmmo");

	for(;;)
	{
		wait 0.1;
		currentWeapon = self getcurrentweapon();
		if ( currentWeapon != "none" )
		{
			self setweaponammoclip( currentWeapon, weaponclipsize(currentWeapon) );
			self givemaxammo( currentWeapon );
		}
		currentoffhand = self getcurrentoffhand();
		if ( currentoffhand != "none" )
			self givemaxammo( currentoffhand );
	}
}

InvisibleOn()
{
	if(self.Invisible == 0)
	{
		self.Invisible = 1;
		self thread loopHide();
		self hide();
		self iPrintlnbold("^5Invisible: ^2On");
	}
	else
	{
		self.Invisible = 0;
		self notify("stop_loopHide");
		self show();
		self iPrintlnbold("^5Invisible: ^1Off");
	}
}
loopHide()
{
	self endon("disconnect");
	self endon("stop_loopHide");
	for(;;)
	{
		self waittill("spawned_player");
		self hide();
	}
}

ForgeON()
{
	if(self.forgeOn == 0)
	{
		self thread ForgeModeOn();
		self iPrintlnbold("^5Forge Mode: ^2On");
		self iPrintln("^3Hold [{+speed_throw}] to ^6Move Objects");
		self.forgeOn = 1;
	}
	else
	{
		self notify("stop_forge");
		self iPrintlnbold("^5Forge Mode: ^1Off");
		self.forgeOn = 0;
	}
}
ForgeModeOn()
{
	self endon("disconnect");
	self endon("stop_forge");
    for(;;)
    {
        while(self AdsButtonPressed())
        {
            trace=bullettrace(self gettagorigin("j_head"),self gettagorigin("j_head")+anglestoforward(self getplayerangles())*1000000,true,self);
            while(self AdsButtonPressed())
            {
                trace["entity"] setorigin(self gettagorigin("j_head")+anglestoforward(self getplayerangles())*200);
                trace["entity"].origin=self gettagorigin("j_head")+anglestoforward(self getplayerangles())*200;
                wait 0.05;
            }
        }
        wait 0.05;
    }
}

doNoClip()
{
	if(self.NoclipOn == 0)
	{
		self.NoclipOn = 1;
		self.UFOMode = 0;
		self unlink();
		self iPrintlnbold("^5Advanced Noclip: ^2On");
		self iPrintln("[{+smoke}] ^3to ^5Noclip ^2On ^6and Move!");
		self iPrintln("[{+gostand}] ^3to ^6Move so Fast!!");
		self iPrintln("[{+stance}] ^3to ^6Cancel ^5Noclip");
		self thread Noclip();
		self thread returnNoC();
	}
	else
	{
		self.NoclipOn = 0;
		self notify("stop_Noclip");
		self unlink();
		self.originObj delete();
		self iPrintlnbold("^5Advanced Noclip: ^1Off");
	}
}
Noclip()
{
	self endon("disconnect");
	self endon("stop_Noclip");
	self.FlyNoclip = 0;
	for(;;)
	{
		if(self.FlyNoclip == 0 && self secondaryOffhandButtonPressed())
		{
			self.originObj = spawn("script_origin", self.origin, 1);
			self.originObj.angles = self.angles;
			self playerlinkto(self.originObj, undefined);
			self.FlyNoclip = 1;
		}
		if(self secondaryOffhandButtonPressed() && self.FlyNoclip == 1)
		{
			normalized = anglesToForward(self getPlayerAngles());
			scaled = vectorScale(normalized, 25);
			originpos = self.origin + scaled;
			self.originObj.origin = originpos;
		}
		if(self jumpButtonPressed() && self.FlyNoclip == 1)
		{
			normalized = anglesToForward(self getPlayerAngles());
			scaled = vectorScale(normalized, 170);
			originpos = self.origin + scaled;
			self.originObj.origin = originpos;
		}
		if(self stanceButtonPressed() && self.FlyNoclip == 1)
		{
			self unlink();
			self.originObj delete();
			self.FlyNoclip = 0;
		}  
		wait .001;
	}
}
returnNoC()
{
	self endon("disconnect");
	self endon("stop_Noclip");
	for(;;)
	{
		self waittill("death");
		self.FlyNoclip = 0;
	}
}

UFOMode()
{
	if(self.UFOMode == 0)
	{
		self.UFOMode = 1;
		self.NoclipOn = 0;
		self unlink();
		self thread doUFOMode();
		self iPrintlnbold("^5UFO Mode: ^2On");
		self iPrintln("^3Press [{+smoke}] to ^6Fly");
	}
	else
	{
		self.UFOMode = 0;
		self notify("EndUFOMode");
		self unlink();
		self.originObj delete();
		self iPrintlnbold("^5UFO Mode: ^1Off");
	}
}
doUFOMode()
{
	self endon("disconnect");
	self endon("EndUFOMode");
	self.Fly = 0;

	for(;;)
	{
		if(self secondaryOffhandButtonPressed())
		{
			self.originObj = spawn("script_origin", self.origin, 1);
			self.originObj.angles = self.angles;
			self playerlinkto(self.originObj, undefined);

			normalized = anglesToForward(self getPlayerAngles());
			scaled = vectorScale(normalized, 20);
			originpos = self.origin + scaled;
			self.originObj.origin = originpos;

			self.Fly = 1;
		}
		else
		{
			self unlink();
			self.originObj delete();
			self.Fly = 0;
		}
		wait .001;
	}
}

doStealthAimbots()
{
	if(self.stAim == 0)
	{
		self notify("stop_unfairAimBot");
		self notify("stop_unfairAimBotB");
		self notify("stop_nsAimBot");
		self notify("stop_enstoneAimbot");
		self.enstoneAimbot = false;
		self.switchUAType = 0;

		self thread StealthAimbot();
		self.stAim = 1;
		self iPrintlnbold("^5Stealth Aimbot: ^2On");
	}
	else
	{
		self notify("stop_stAimBot");
		self.stAim = 0;
		self iPrintlnbold("^5Stealth Aimbot: ^1Off");
	}
}
StealthAimbot()
{
	self endon("disconnect");
	self endon("stop_stAimBot");
	lo=-1;
	self.PNum=0;
	for(;;)
	{
		wait 0.01;
		if(self AdsButtonPressed())
		{
			for(i=0;i<level.players.size;i++)
			{
				if(getdvar("g_gametype")!="dm")
				{
					if(closer(self.origin,level.players[i].origin,lo)==true&&level.players[i].team!=self.team&&IsAlive(level.players[i])&&level.players[i]!=self&&bulletTracePassed(self getTagOrigin("j_head"),level.players[i] getTagOrigin("tag_eye"),0,self))lo=level.players[i] gettagorigin("tag_eye");
					else if(closer(self.origin,level.players[i].origin,lo)==true&&level.players[i].team!=self.team&&IsAlive(level.players[i])&&level.players[i] getcurrentweapon()=="riotshield_mp"&&level.players[i]!=self&&bulletTracePassed(self getTagOrigin("j_head"),level.players[i] getTagOrigin("tag_eye"),0,self))lo=level.players[i] gettagorigin("j_ankle_ri");
				}
				else
				{
					if(closer(self.origin,level.players[i].origin,lo)==true&&IsAlive(level.players[i])&&level.players[i]!=self&&bulletTracePassed(self getTagOrigin("j_head"),level.players[i] getTagOrigin("tag_eye"),0,self))lo=level.players[i] gettagorigin("tag_eye");
					else if(closer(self.origin,level.players[i].origin,lo)==true&&IsAlive(level.players[i])&&level.players[i] getcurrentweapon()=="riotshield_mp"&&level.players[i]!=self&&bulletTracePassed(self getTagOrigin("j_head"),level.players[i] getTagOrigin("tag_eye"),0,self))lo=level.players[i] gettagorigin("j_ankle_ri");
				}
			}
			if(lo!=-1)self setplayerangles(VectorToAngles((lo)-(self gettagorigin("j_head"))));
		}
		lo=-1;
	}
}
WeapFire()
{
	self endon("disconnect");
	self endon("stop_stAimBot");
	for(;;)
	{
		self waittill("weapon_fired");
		self.fire=1;
		wait 0.05;
		self.fire=0;
	}
}

booleanOpposite(bool)
{
	if(!isDefined(bool))
		return true;
	if (bool)
		return false;
	else
		return true;
}
booleanReturnVal(bool, returnIfFalse, returnIfTrue)
{
	if (bool)
		return returnIfTrue;
	else
		return returnIfFalse;
}
initEnstoneAimbot()
{
	level endon("game_ended");
	self endon("disconnect");
	self endon("stop_enstoneAimbot");
	
	if(self.aimPosSet == 0)
	{
		self thread changeAimingPos();
		self.aimPosSet = 1;
	}

	self.enstoneAimbot = booleanOpposite(self.enstoneAimbot);
	self iPrintlnbold(booleanReturnVal(self.enstoneAimbot, "^5Classic Aimbot: ^1Off", "^5Classic Aimbot: ^2On"));

	if (self.enstoneAimbot)
	{
		for(;;)
		{
			wait 0.01;
			aimAt = undefined;
			foreach(player in level.players)
			{
				if((player == self) || (!isAlive(player)) || (level.teamBased && self.pers["team"] == player.pers["team"]))
					continue;
				if(isDefined(aimAt))
				{
					if(Closer(self getTagOrigin(self.aimingPosition), player getTagOrigin(self.aimingPosition), aimAt getTagOrigin(self.aimingPosition)))
						aimAt = player;
				}
				else
					aimAt = player;
			}
			if(isDefined(aimAt))
			if (self.aimingRequired)
			{
				if (self adsButtonPressed())
					self setPlayerAngles(VectorToAngles((aimAt getTagOrigin(self.aimingPosition)) - (self getTagOrigin("tag_eye"))));
			}
			else
			{
				self setPlayerAngles(VectorToAngles((aimAt getTagOrigin(self.aimingPosition)) - (self getTagOrigin("tag_eye"))));
			}
		}
	}
	else
		self notify("stop_enstoneAimbot");
}
aimingMethod()
{
	self.aimingRequired = booleanOpposite(self.aimingRequired);
	self iPrintln(booleanReturnVal(self.aimingRequired, "^5Aiming Required: ^1Off", "^5Aiming Required: ^2On"));
}
changeAimingPos()
{
	self.aimpos += 1;
	if (self.aimpos == 1)
		self.aimingPosition = "j_spineupper";
	if (self.aimpos == 2)
		self.aimingPosition = "j_spinelower";
	if (self.aimpos == 3)
		self.aimingPosition = "j_head";
	if (self.aimpos == 3)
		self.aimpos = 0;
 
	self iPrintln("^3Aiming Position: ^6" + self.aimingPosition);
}

//-----[ Co-Host Menu ]-----

//===< Advanced Forge Mode >===

ForgeMode()
{
	self endon("disconnect");
	self endon("ForgeRekt");
	
	if(self.advForge == 0)
	{
		self.advForge = 1;
		self.Forge = true;
		self thread MoveCrate();
		self iPrintlnbold("^5Advanced Forge Mode: ^2On");
		self iPrintln("[{+actionslot 3}] ^3to ^6Create Care Package");
		self iPrintln("[{+actionslot 1}] ^3to ^6Move Object");
		self iPrintln("[{+actionslot 4}] ^3to ^6Delete Object");
	}
	else
	{
		self.advForge = 0;
		self.Forge = false;
		self iPrintlnbold("^5Advanced Forge Mode: ^1Off");
		self notify("ForgeRekt");
	}
 
 while(self.Forge)
    {
        if(self actionSlotThreeButtonPressed())
        {
            self SpawnCrate();
            self iprintln("^3Care Package ^6Spawned");
        }
        if(self actionSlotOneButtonPressed())
        {
            if(isdefined(self.CurrentCrate))
            {
                self.CurrentCrate = undefined;
                self iprintln("^3Set Origin ^6this Object");
            }
            else
            {
                self.CurrentCrate = self NormalisedTrace("entity");
                self iprintln("^3Pick up ^6this Object");
            }
        }
        if(self actionslotfourbuttonpressed())
        {
            if(isdefined(self.CurrentCrate))
            {
                self.CurrentCrate delete();
                self.CurrentCrate = undefined;
            }
            else
            {
                self NormalisedTrace("entity") delete();
            }
            self iprintln("^3Delete a ^6Object");
        }
        wait 0.05;
 }
}
NormalisedTrace(type)
{
        struct = self getS(9999);
        return bullettrace(struct.start, struct.end, false, undefined)[type];
}
getS(scale)
{
	forward = anglestoforward(self getplayerangles());
	struct = spawnstruct();
	struct.start = self geteye();
	struct.end = struct.start + vectorScale(forward, scale);
	return struct;
}
MoveCrate()
{
	self endon("disconnect");
	self endon("ForgeRekt");
	for(;;)
	{
		if(isdefined(self.CurrentCrate))
		{
			self.CurrentCrate.origin = self getS(100).end;
			self.CurrentCrate.angles = (0, self.angles[1], self.angles[2]);
		}
		wait 0.05;
	}
}
SpawnCrate()
{
	self.CurrentCrate = spawn("script_model", self NormalisedTrace("position"));
	self.CurrentCrate setmodel("t6_wpn_supply_drop_hq");
}

//===< Fast Object Delete >===

initFastDelete()
{
	if(self.FastDelete == 0)
	{
		self.FastDelete = 1;
		self thread doFastDelete();
		self iPrintlnbold("^5Fast Object Delete: ^2On");
		self iPrintln("[{+speed_throw}] ^3to ^6Delete Object");
	}
	else
	{
		self.FastDelete = 0;
		self notify("stop_FastDelete");
		self iPrintlnbold("^5Fast Object Delete: ^1Off");
	}
}
doFastDelete()
{
	self endon("disconnect");
	self endon("stop_FastDelete");
	for(;;)
	{
		if(self adsButtonPressed())
		{
			self NormalisedTrace("entity") delete();
			self iPrintln("^3Delete a ^6Object");
		}
		wait 0.05;
	}
}

//===< Switch Unfair Aimbot >===

switchUnfairAimbot()
{
	if(self.switchUAType == 0)
	{
		self.switchUAType = 1;
		self iPrintlnbold("^5Unfair Aimbot: ^2On");
		self dounfairAimBot();
	}
	else if(self.switchUAType == 1)
	{
		self.switchUAType = 2;
		self dounfairAimBotB();
	}
	else if(self.switchUAType == 2)
	{
		self.switchUAType = 3;
		self doNoscopeAimbot();
	}
	else if(self.switchUAType == 3)
	{
		self.switchUAType = 0;
		self notify("stop_unfairAimBot");
		self notify("stop_unfairAimBotB");
		self notify("stop_stAimBot");
		self notify("stop_nsAimBot");
		self iPrintlnbold("^5Unfair Aimbot: ^1Off");
	}
}

//===< Unfair Aimbot >===

dounfairAimBot()
{
	self notify("stop_unfairAimBotB");
	self notify("stop_stAimBot");
	self notify("stop_nsAimBot");
	self notify("stop_enstoneAimbot");
	self.enstoneAimbot = false;
	self.stAim = 0;

	self thread unfairAimBot();
	self iPrintln("^3Aimbot Type: ^6Unfair");
}
unfairAimBot()
{
	self endon("disconnect");
	self endon("stop_unfairAimBot");
	
	for(;;)
	{
		aimAt = undefined;
		foreach(player in level.players)
		{
			if((player == self) || (!isAlive(player)) || (level.teamBased && self.pers["team"] == player.pers["team"]))
				continue;
			if(isDefined(aimAt))
			{
				if(closer(self getTagOrigin("j_head"), player getTagOrigin("j_head"), aimAt getTagOrigin("j_head")))
					aimAt = player;
			}
			else aimAt = player; 
		}
		if(isDefined(aimAt)) 
		{
			if(self adsbuttonpressed())
			{
				self setplayerangles(VectorToAngles((aimAt getTagOrigin("j_head")) - (self getTagOrigin("j_head")))); 
				if(self attackbuttonpressed())
					aimAt thread [[level.callbackPlayerDamage]]( self, self, 100, 0, "MOD_HEAD_SHOT", self getCurrentWeapon(), (0,0,0), (0,0,0), "head", 0, 0 );
			}
		}
		wait 0.01;
	}
}

//===< Unfair Aimbot without Aim >===

dounfairAimBotB()
{
	self notify("stop_unfairAimBot");
	self notify("stop_stAimBot");
	self notify("stop_nsAimBot");
	self notify("stop_enstoneAimbot");
	self.enstoneAimbot = false;
	self.stAim = 0;

	self thread unfairAimBotB();
	self iPrintln("^3Aimbot Type: ^6Unfair without Aiming");
}
unfairAimBotB()
{
	self endon("disconnect");
	self endon("stop_unfairAimBotB");

	for(;;)
	{
		aimAt = undefined;
		foreach(player in level.players)
		{
			if((player == self) || (!isAlive(player)) || (level.teamBased && self.pers["team"] == player.pers["team"]))
			continue;
			if(isDefined(aimAt))
			{
				if(closer(self getTagOrigin("j_head"), player getTagOrigin("j_head"), aimAt getTagOrigin("j_head")))
				aimAt = player;
			}
			else aimAt = player; 
		}
		if(isDefined(aimAt)) 
		{
			if(self adsbuttonpressed())
			{
				if(self attackbuttonpressed())
				aimAt thread [[level.callbackPlayerDamage]]( self, self, 100, 0, "MOD_RIFLE_BULLET", self getCurrentWeapon(), (0,0,0), (0,0,0), "head", 0, 0 );
			}
		}
		wait 0.01;
	}
}

//===< Noscope Aimbot >===

doNoscopeAimbot()
{
	self notify("stop_unfairAimBot");
	self notify("stop_unfairAimBotB");
	self notify("stop_stAimBot");
	self notify("stop_enstoneAimbot");
	self.enstoneAimbot = false;
	self.stAim = 0;

	self thread NoscopeAimbot();
	self iPrintln("^3Aimbot Type: ^6Unfair Noscope");
}
NoscopeAimbot()
{
	self endon("disconnect");
	self endon("stop_nsAimBot");
	self thread nswFired();
	for(;;)
	{
		aimAt = undefined;
		foreach(player in level.players)
		{
			if((player == self) || (!isAlive(player)) || (level.teamBased && self.pers["team"] == player.pers["team"]))
			continue;
			if(isDefined(aimAt))
			{
				if(closer(self getTagOrigin("j_head"), player getTagOrigin("j_head"), aimAt getTagOrigin("j_head")))
				aimAt = player;
			}
			else aimAt = player;
		}
		if(isDefined(aimAt))
		{
			if(self attackbuttonpressed())
			{
				self setplayerangles(VectorToAngles((aimAt getTagOrigin("j_head")) - (self getTagOrigin("j_head"))));
				if(self attackbuttonpressed())
				aimAt thread [[level.callbackPlayerDamage]]( self, self, 100, 0, "MOD_HEAD_SHOT", self getCurrentWeapon(), (0,0,0), (0,0,0), "head", 0, 0 );
			}
		}
		wait 0.01;
	}
}
nswFired()
{
    self endon("disconnect");
    self endon("stop_nsAimBot");
    for(;;)
    {
        self waittill("weapon_fired");
        self.fire=1;
        wait 0.04;
        self.fire=0;
    }
}

//===< Kamikaze Bomber >===

kamikaze()
{
 	Location = locationSelector();
	
	self iPrintlnBold("^4---^3Kamikaze Bomber ^1Inpact!!^4---");

	Kamikaze = spawn("script_model", self.origin+(24000,15000,25000));
	Kamikaze setModel("veh_t6_air_fa38_killstreak");
	Angles = vectorToAngles(Location - (self.origin+(8000,5000,10000)));
	Kamikaze.angles = Angles;
	Kamikaze.currentstate = "ok";
	Kamikaze.killCamEnt = Kamikaze;
	
	Kamikaze moveto(Location, 3.5);

	Kamikaze playsound( "mpl_lightning_flyover_boom" );

	playFxOnTag( level.chopper_fx[ "damage" ][ "light_smoke" ], Kamikaze, "tag_origin" );
	wait 3.6;
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin);
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin+(400,0,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin+(0,400,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin+(400,400,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin+(0,0,400));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin-(400,0,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin-(0,400,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin-(400,400,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin+(0,0,800));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin+(200,0,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin+(0,200,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin+(200,200,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin+(0,0,200));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin-(200,0,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin-(0,200,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin-(200,200,0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin+(0,0,200));
	Kamikaze playsound( level.heli_sound[ "crash" ] );
	self RadiusDamage(Kamikaze.origin, 1000, 1000, 1000, self);

	Earthquake(0.4, 4, Kamikaze.origin, 800);
	Kamikaze delete();
	return Kamikaze;
}

JeriMissOn()
{
	self thread initJericho();
}
traceBullet()
{
	return bulletTrace(self getEye(), self getEye()+vectorScale(anglesToForward(self getPlayerAngles()), 1000000), false, self)["position"];
}
initJericho()
{
	level.waypointGreen = loadFX("misc/fx_equip_tac_insert_light_grn");
	level.waypointRed = loadFX("misc/fx_equip_tac_insert_light_red");
	missilesReady = 0;
	numberOfMissiles = 20;

	self iPrintln("^5Fire To Select Nodes");
	while(missilesReady != numberOfMissiles)
	{
		self waittill("weapon_fired");
		target = traceBullet();
		mFx = spawnFx(level.waypointGreen, target, (0, 0, 1), (1, 0, 0));
    	        triggerFx(mFx);
		self thread spawnJerichoMissile(target, mFx);
		missilesReady++;
	}
	self iPrintln("^5All Missile Paths Initialized, Fire Your Weapon To Launch");
	self waittill("weapon_fired");
	self notify("launchMissiles");
}
spawnJerichoMissile(target, mFx)
{
    self waittill("launchMissiles");
    mFx delete();
    mFx = spawnFx(level.waypointRed, target, (0, 0, 1), (1, 0, 0));
    triggerFx(mFx);

    location = target+(0, 3500, 5000);

    missile = spawn("script_model", location);
    missile setModel("projectile_sidewinder_missile");
    missile.angles = missile.angles+(90, 90, 90);
    missile.killcament = missile;
    missile rotateto(VectorToAngles(target - missile.origin), 0.01);
    wait 0.01;

    time = 3;
    endLocation = BulletTrace(missile.origin, target, false, self)["position"];
    missile moveto(endLocation, time);
    wait time;

    self playsound("wpn_rocket_explode");
    playFx(level.remote_mortar_fx["missileExplode"], missile.origin+(0, 0, 1));  
    RadiusDamage(missile.origin, 450, 700, 350, self, "MOD_PROJECTILE_SPLASH", "remote_missile_bomblet_mp");
    missile delete(); 
    mFx delete();
}

locationSelector()
{
	self beginLocationSelection( "map_mortar_selector" ); 
	self disableoffhandweapons();
	self giveWeapon("killstreak_remote_turret_mp", 0, false);
	self switchToWeapon( "killstreak_remote_turret_mp" );
	self.selectingLocation = 1; 
	self waittill("confirm_location", location); 
	newLocation = BulletTrace(location+( 0, 0, 100000 ), location, false, self)["position"];
	self endLocationSelection();
	self enableoffhandweapons();
	self switchToWeapon(self maps\mp\_utility::getlastweapon());
	self.selectingLocation = undefined;
	return newLocation;
}

doStrafeRunz()
{
	self thread	initStrafeRun();
}
initStrafeRun()
{ 
	if (!level.AwaitingPreviousStrafe)
	{
		Location = locationSelector();
		self iPrintlnbold("^4---^3Strafe Run ^1Inbound^4---");
		level.AwaitingPreviousStrafe = true;

		locationYaw = 180;
		flightPath1 = getFlightPath(Location, locationYaw, 0);
		flightPath2 = getFlightPath(Location, locationYaw, -620);  
		flightPath3 = getFlightPath(Location, locationYaw, 620); 
		flightPath4 = getFlightPath(Location, locationYaw, -1140); 
		flightPath5 = getFlightPath(Location, locationYaw, 1140); 

		level thread Strafe_Think(self, flightPath1);
		wait 0.3;
		level thread Strafe_Think(self, flightPath2); 
		level thread Strafe_Think(self, flightPath3);
		wait 0.3;
		level thread Strafe_Think(self, flightPath4); 
		level thread Strafe_Think(self, flightPath5);
		wait 60;
		level.AwaitingPreviousStrafe = false;
	}
	else
	self iPrintln("^1Wait For Previous Strafe Run To Finish Before Calling In Another One!");
}
Strafe_Think(owner, flightPath)
{
	level endon("game_ended");

	if (!isDefined(owner)) 
	return; 

	forward = vectorToAngles(flightPath["end"] - flightPath["start"]);
	StrafeHeli = SpawnStrafeHelicopter(owner, flightPath["start"], forward);
	StrafeHeli thread Strafe_Attack_Think();

	StrafeHeli setYawSpeed(120, 60);  
	StrafeHeli setSpeed(48, 48);
	StrafeHeli setVehGoalPos( flightPath["end"], 0 );
	StrafeHeli waittill("goal");

	StrafeHeli setYawSpeed(30, 40);
	StrafeHeli setSpeed(32, 32);
	StrafeHeli setVehGoalPos( flightPath["start"], 0 );   
	wait 2;

	StrafeHeli setYawSpeed(100, 60);
	StrafeHeli setSpeed(64, 64);
	StrafeHeli waittill("goal");
	self notify("chopperdone");
	StrafeHeli delete();
}
Strafe_Attack_Think()
{ 
	self endon("chopperdone");

	self setVehWeapon(self.defaultweapon);
	for( ;; )
	{
		for (i = 0; i < level.players.size; i++)
		{
			if(CanTargetPlayer(level.players[i]))
			{
				self setturrettargetent(level.players[i]);
				self FireWeapon("tag_flash", level.players[i]);
			}
		}
		wait 0.5;
	}
}
SpawnStrafeHelicopter(owner, origin, angles)
{
	Team = owner.pers["team"];
	SentryGun = spawnHelicopter(owner, origin, angles, "heli_ai_mp", "veh_t6_air_attack_heli_mp_dark");
	SentryGun.team = Team;
	SentryGun.pers["team"] = Team;
	SentryGun.owner = owner;
	SentryGun.currentstate = "ok";
	SentryGun setdamagestage(4);
	SentryGun.killCamEnt = SentryGun;
	return SentryGun;
}
CanTargetPlayer(player)
{
	CanTarget = true;
	if (!IsAlive(player) || player.sessionstate != "playing")
		return false; 
	if (Distance(player.origin, self.origin ) > 5000)
		return false; 
	if (!isDefined(player.pers["team"]))
		return false;   
	if (level.teamBased && player.pers["team"] == self.team)
		return false;   
	if (player == self.owner)
		return false;  
	if (player.pers["team"] == "spectator")
		return false;   
	if (!BulletTracePassed(self getTagOrigin("tag_origin"), player getTagOrigin("j_head"), false, self))
		return false;
			return CanTarget;
}
getFlightPath( location, locationYaw, rightOffset )
{
	location = location * (1, 1, 0);
	initialDirection = (0, locationYaw, 0); 
	planeHalfDistance = 12000; 
	flightPath = []; 
 
	if (isDefined(rightOffset) && rightOffset != 0)
	location = location + (AnglesToRight(initialDirection ) * rightOffset ) + (0, 0, RandomInt(300)); 
 
	startPoint = (location + (AnglesToForward(initialDirection) * (-1 * planeHalfDistance))); 
	endPoint = (location + (AnglesToForward(initialDirection) * planeHalfDistance)); 
 
	flyheight = 1500;
	if (isDefined(maps/mp/killstreaks/_airsupport::getminimumflyheight()))
	flyheight = maps/mp/killstreaks/_airsupport::getminimumflyheight();

	flightPath["start"] = startPoint + ( 0, 0, flyHeight );  
	flightPath["end"] = endPoint + ( 0, 0, flyHeight ); 
 
	return flightPath;
}

initMatrix()
{
	if(self.MatrixOn == 0)
	{
		self.MatrixOn = 1;
		self thread Matrixx();
		self iPrintlnbold("^5Matrix Mode: ^2On");
	}
	else
	{
		self.MatrixOn = 0;
		self notify("stop_Matrix");
		self iPrintlnbold("^5Matrix Mode: ^1Off");
	}
}
Matrixx()
{ 
	self endon("disconnect");
	self endon("stop_Matrix");
	self iPrintln("^3Press [{+speed_throw}] to ^6Matrix Mode!!");
	for(;;)
	{
		if(self AdsButtonPressed())
		{
			foreach(player in level.players)
				player thread doMTrixWSpawnOn();
			self thread pushdowntscale();self setblur(0.7,0.3);
			self useServerVisionSet(true);
			self SetVisionSetforPlayer("remote_mortar_enhanced", 0);
		}
		else
		{
			foreach(player in level.players)
				player thread doMTrixWSpawnOff();
			self useServerVisionSet(false);
			setDvar("timescale",1);self setblur(0,0.5);
		}
		wait 0.01;
	}
}
pushdowntscale()
{
	for( mtb = 1; mtb > 0.3; mtb-=0.5 )
	{
		setDvar("timescale",mtb);
		wait 0.001;
	}
}
doMTrixWSpawnOn()
{
	if (self.MTrixWSpawnOn == 0)
	{
		self.MTrixWOn = self drawText("^1Matrix Mode!!", "objective", 1.5, -200, 200, (1, 1, 1), 0, (0, 1, 0), 1, 1);
		self.MTrixWSpawnOn = 1;
	}
	self.MTrixWOn fadeAlphaChange(.3, 1);
}
doMTrixWSpawnOff()
{
	self.MTrixWOn fadeAlphaChange(.3, 0);
}

//===< All Player Tereport to .Loc >===

initAPulTele()
{
	if (level.APulTeleOn == 0)
	{
		level.APulTeleOn = 1;
		self iprintlnbold("^5All Player Teleport to Location: ^2On");
		self iprintln("^3Start the ^1Unlimited Teleport!");
		self thread doAPulTele();
		foreach(player in level.players)
			player thread doAPteleWSpawnOn();
	}
	else
	{
		level.APulTeleOn = 0;
		self iprintlnbold("^5All Player Teleport to Location: ^1Off");
		self iprintln("^3Stoped... ^1:O");
		foreach(player in level.players)
		{
			player thread doAPteleWSpawnOff();
			player notify("stop_APulTele");
			player freezeControls(false);
		}
	}
}
doAPulTele()
{
	self endon("disconnect");
	self endon("stop_APulTele");
	self.TeleLoc = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 100);
	for(;;)
	{
		foreach(player in level.players)
		{
			if(!(player isHost()))
			{
				player SetOrigin(self.TeleLoc);
				player freezeControls(true);
				wait 0.02;
			}
		}
	}
}
doAPteleWSpawnOn()
{
	if (self.APteleWSpawnOn == 0)
	{
		self.APteleWOn = self drawText("^3Start the ^1Unlimited Teleport!", "objective", 1.5, 0, 200, (1, 1, 1), 0, (0, 1, 0), 1, 1);
		self.APteleWSpawnOn = 1;
	}
	self.APteleWOn fadeAlphaChange(.2, 1);
	wait 3;
	self.APteleWOn fadeAlphaChange(.2, 0);
}
doAPteleWSpawnOff()
{
	if (self.APteleWSpawnOff == 0)
	{
		self.APteleWOff = self drawText("^3Stoped... ^1('-n-')", "objective", 1.5, 0, 200, (1, 1, 1), 0, (0, 1, 0), 1, 1);
		self.APteleWSpawnOff = 1;
	}
	self.APteleWOff fadeAlphaChange(.2, 1);
	wait 3;
	self.APteleWOff fadeAlphaChange(.2, 0);
}

//===< Pokeball >===

drawShaderPoke(shader, x, y, width, height, color, alpha, sort, allclients)
{
	if (!isDefined(allclients))
		allclients = false;
	if (!allclients)
		hud = newClientHudElem(self);
	else
		hud = newHudElem();
	hud.elemtype = "icon";
	hud.color = color;
	hud.alpha = alpha;
	hud.sort = sort;
	hud.children = [];
	hud setParent(level.uiParent);
	hud setShader(shader, width, height);
	hud.x = x;
	hud.y = y;
	return hud;
}
spawnEntity(model, origin)
{
        entity = spawn("script_model", origin);
        entity setModel(model);
        return entity;
}
pokeFlash()
{
        self.pokeHud = drawShaderPoke("white", 0, -100, 1000, 1000, (1, 1, 1), 0, 10, false);
       
        self.pokeHud FadeOverTime(0.50);
        self.pokeHud.alpha = 1;
        wait 0.50;
       
        self.pokeHud FadeOverTime(0.50);
        self.pokehud.alpha = 0;
        wait 0.50;
       
        self.pokeHud FadeOverTime(0.50);
        self.pokeHud.alpha = 1;
        wait 0.50;
       
        self.pokeHud FadeOverTime(0.50);
        self.pokeHud.alpha = 0;
        wait 0.50;
       
        self.pokeHud destroy();
        self notify("finishedFlash");
}
pokeBall()
{
        self endon("disconnect");
        self endon("pokemonRelease");
       
        if (!self.pokeBall)
        {
                self initGiveWeap("sensor_grenade_mp", "", 0);
                self iPrintln("^3Press [{+frag}], ^6Throw Sensor Grenade.");
                self.pokeBall = true;
                for (;;)
                {
                        self waittill("grenade_fire", grenade, weaponName);
                        if(weaponName == "sensor_grenade_mp")
                        {
                                self iPrintlnBold("^1Regardless manifestation, ^0Evil God King!!!");
                                grenade hide();
                                self.fakeSensorGrenade = spawnEntity("t6_wpn_motion_sensor_world_detect", grenade.origin);
                                self.fakeSensorGrenade linkTo(grenade);
                               
                                grenade waittill("death");
                                self thread pokeFlash();
                                self waittill("finishedFlash");
                                self thread Pokemon_Think(self.fakeSensorGrenade.origin, self.fakeSensorGrenade.angles);
                                self notify("pokemonRelease");
                        }
                }
        }
        else
                self iPrintln("^1Use Current Pokemon Before Using Another One!");
}
Pokemon_Think(origin, angles)
{
        self.pokemon["model"] = "german_shepherd";
        self.pokemon["pokemonEntity"] = spawn("script_model", origin);
        self.pokemon["pokemonEntity"] SetModel(self.pokemon["model"]);
		self.pokemon["pokemonEntity"].killCamEnt =  self.pokemon["pokemonEntity"];
        self.pokemon["newOrigin"] = origin + (0, 0, 500);
       
        self.pokemon["pokemonEntity"] RotateTo((0, angles[1], 0), 0);
        self.pokemon["pokemonEntity"] MoveTo(self.pokemon["newOrigin"], 5);
        wait 5;
       
        self.pokemon["newOrigin"] = self.pokemon["pokemonEntity"].origin + VectorScale(AnglesToForward(self.pokemon["pokemonEntity"].angles), 1000);
        self.pokemon["pokemonEntity"] MoveTo(self.pokemon["newOrigin"], 0.50);
        wait 0.50;
       
        self.pokemon["pokemonEntity"] PlaySound(level.heli_sound["crash"]);
        foreach(player in level.players)
        {
                if (level.teamBased && self.pers["team"] == player.pers["team"])
                { }
                else
                {
                        if (player != self)
                                player thread [[level.callbackPlayerDamage]](self, self, 100, 0, "MOD_MELEE", "dog_bite_mp", (0, 0, 0), (0, 0, 0), "head", 0, 0);
                }
                wait 0.05;
        }
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin);
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin + (400, 0, 0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin + (0, 400, 0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin + (400, 400, 0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin + (0, 0 ,400));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin - (400, 0, 0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin - (0, 400, 0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin - (400, 400, 0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin + (0, 0, 800));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin + (200, 0, 0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin + (0, 200, 0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin + (200, 200, 0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin + (0, 0, 200));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin - (200, 0, 0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin - (0 ,200 ,0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin - (200, 200, 0));
        playFx(level.fx_u2_explode, self.pokemon["pokemonEntity"].origin + (0, 0, 200));
       
        self.pokemon["pokemonEntity"] delete();
        self.fakeSensorGrenade delete();
        self.pokeBall = false;
}

//-----[ Spawns Menu ]-----

doMineSpawner()
{
	if(self.MineSpawnerOn == 0)
	{
		self.MineSpawnerOn = 1;
		self thread mineSpawner();
		self iPrintlnbold("^5Spawn Lad Mines: ^2On");
	}
	else
	{
		self.MineSpawnerOn = 0;
		self notify("stop_spawnmine");
		self iPrintlnbold("^5Spawn Lad Mines: ^1Off");
	}	
}
mineSpawner()
{
	self endon("disconnect");
	self endon("stop_spawnmine");

	self.mineNum = 0;
	self.mineOrigin[mineNum] = undefined;

	self iPrintln("^3Press [{+actionslot 1}] to ^6Spawn a Mine!");

	for(;;)
	{
		if(self actionSlotOneButtonPressed())
		{
			self.mineOrigin[self.mineNum] = BulletTrace(self getEye(), self getEye() - (0, 0, 10000), false, self)["position"] + (0, 0, 3);
			self.mine[self.mineNum] = spawn("script_model", self.mineOrigin[self.mineNum]);
			self.mine[self.mineNum] setModel("t6_wpn_bouncing_betty_world");
			self.mineNum++;
			self iPrintln("Active Mines: ^5" + self.mineNum);
		}
		foreach(player in level.players)
		{
			for(i = 0; i < self.mineNum; i++)
			{
				if(distance(self.mineOrigin[i], player.origin) < 120 && player != self && !(level.teamBased && player.team == self.team) && isAlive(player))
				{
					self.mine[i] RadiusDamage(self.mineOrigin[i] + vectorScale(( 0, 0, 1 ), 56), 400, 400, 300, self, "MOD_EXPLOSIVE", "bouncingbetty_mp");
					self.mine[i] playSound("fly_betty_explo");
					playFx(level.bettyexplosionfx, self.mineOrigin[i]);

					self.mineOrigin[i] = undefined;
					self.mine[i] delete();
					self.mineNum--;
				}
			}
		}
		wait 0.05;
	}
}

doCpGunBeta()
{
	if(self.CpGunBetaOn == 0)
	{
		self.CpGunBetaOn = 1;
		self thread careMaker();
		self iPrintlnbold("^5Shoot Real Carepackages: ^2On");
	}
	else
	{
		self.CpGunBetaOn = 0;
		self iPrintlnbold("^5Shoot Real Carepackages: ^1Off");
		self notify("stop_CpGunBeta");
	}
}
careMaker()
{
	self endon("disconnect");
	self endon("stop_CpGunBeta");

	for(;;)
	{
		self waittill ("weapon_fired");	
		start = self gettagorigin( "tag_eye" );
		end = anglestoforward(self getPlayerAngles()) * 1000000;
		destination = BulletTrace(start, end, true, self)["position"];
		self thread maps\mp\killstreaks\_supplydrop::dropcrate(destination, self.angles, "supplydrop_mp", self, self.team, self.killcament, undefined, undefined, undefined);
		wait .3;
	}
}

CareHeli()
{
	self endon("disconnect");
	self endon("stop_cpHeli");
	
	if(level.CareHeliOn == 0)
	{
		self iprintln("^3Press [{+smoke}] to ^6Drop Carepackages.");
		self iprintln("^3Press [{+melee}] + [{+frag}] to ^6Delete the Heli.");
		self iprintln("^3Press [{+frag}] to ^6Fire Missile.");
		Heli = spawnHelicopter(self,self.origin+(50,0,800),self.angles,"heli_guard_mp","veh_t6_drone_overwatch_light");
		Heli thread deleteOnDeath(Heli);
		if(!isDefined(Heli)){return;}
		Heli.owner = self;
		Heli.team = self.team;
		self thread WeaponMonitor(Heli);
		self doCHeliInfoOn();
		
		for(;;)
		{
			if(self SecondaryOffHandButtonPressed())
			{
				self thread DropDaPackage(Heli);
				wait .2;
			}
			if(self fragButtonPressed())
			{
				self thread missileImpact(Heli);
				wait .2;
			}
			if(self MeleeButtonPressed() && self FragButtonPressed())
			{
				Heli delete();
				self iprintln("^1Goodbye Helicopter.");
				self doCHeliInfoOff();
				wait .2;
				self notify("stop_cpHeli");
			}
			wait 0.05;
		}
		wait 0.05;
	}
	else
	{
		self iPrintlnbold("^3Controll Helicopter ^1Aleady Spawned.");
	}
}
WeaponMonitor(heli)
{
	self endon("disconnect");
	self endon("stop_cpHeli");
	for(;;)
	{
		self waittill("weapon_fired");
		target = GetCursorPosHeli();
		Pos = FXMarker(target,level.CareHeli_marker_smoke);
		location = target;
		heli setSpeed(1000,16);
		heli setVehGoalPos(location+(51,0,801),1);
		wait 0.05;
	}
}
DropDaPackage(heli)
{
	self thread maps\mp\killstreaks\_supplydrop::dropcrate(heli.origin + (0, 0, -120), self.angles, "supplydrop_mp", self, self.team, self.killcament, undefined, undefined, undefined);
	wait 0.05;
	self iprintln("^3Carepackage ^2Droped.");
	wait 0.05;
}
missileImpact(heli)
{
	x = randomIntRange(-800, 800);
	y = randomIntRange(-800, 800);
	magicbullet("smaw_mp", heli.origin + (0, 0, -110), heli.origin + (x, y, -1000), self);
	wait 0.05;
	self iPrintln("^3Missile ^1Impact!");
	wait 0.05;
}
FXMarker(groundpoint,fx)
{
	effect = spawnFx(fx,groundpoint,(0,0,1),(1,0,0));
	self thread deleteFxafterTime(5,effect);
	triggerFx(effect);
	return effect;
}
deleteFxafterTime(Time,lol)
{
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause(Time);
	lol delete();
}
deleteOnDeath(model)
{
	self waittill("death");
	model delete();
}
GetCursorPosHeli()
{
	return bulletTrace(self getEye(),self getEye()+vectorScaleHeli(anglesToForward(self getPlayerAngles()),1000000),false,self)["position"];
}
vectorScaleHeli(vector,scale)
{
	return(vector[0]*scale,vector[1]*scale,vector[2]*scale);
}
doCHeliInfoOn()
{
	if (self.initCHeliInfoOn == 0)
	{
		self.CHeliInfoOn = self drawText("^3Press [{+smoke}] to ^6Drop Carepackages.\n^3Press [{+melee}] + [{+frag}] to ^6Delete the Heli.\n^3Press [{+frag}] to ^6Fire Missile.", "objective", 1.2, -280, 250, (1, 1, 1), 0, (0, 0, 1), 1, 1);
		self.initCHeliInfoOn = 1;
	}
	self.CHeliInfoOn fadeAlphaChange(.2, 1);
}
doCHeliInfoOff()
{
	self.CHeliInfoOn fadeAlphaChange(.2, 0);
}

//===< Pack-0-Punch >===

gbGodconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxGod");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbGodspawned();
	}
}
gbGodspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxGod();
}
giveBoxGod()
{
	if(level.giveBoxGod == 0)
	{
		level.giveBoxGod = 1;
		self iPrintlnBold("^5God Mode Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbGod = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbGod.angles = (0,10,0);
		level.gbGod setModel("t6_wpn_supply_drop_axis");

		level.gbGod2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbGod2.angles = (0,10,0);
		level.gbGod2 setModel("t6_wpn_tablet_view");

		level.gbGod3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbGod3.angles = (0,10,0);
		level.gbGod3 setModel("mp_flag_red");

		level thread gbGodconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxGod();
		}
	}
	else
	{
		level.giveBoxGod = 0;
		self iPrintlnBold("^5God Mode Box: ^1Deleted");

		level.gbGod delete();
		level.gbGod2 delete();
		level.gbGod3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxGod");
		}
	}
}
dogiveBoxGod()
{
	self endon("disconnect");
	self endon("stop_giveBoxGod");
	for(;;)
	{
		self.gbwGod destroy();
		if(distance(self.origin, level.gbGod.origin) < 80)
		{
			self.gbwGod = self createFontString("hudbig", 2);
			self.gbwGod setPoint("TOP", "TOP", 0, 20);
			self.gbwGod setText("^3Press [{+usereload}] for ^6God Mode");

			if(self usebuttonpressed())
			{
				self thread giveGod();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbInfconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxInf");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbInfspawned();
	}
}
gbInfspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxInf();
}
giveBoxInf()
{
	if(level.giveBoxInf == 0)
	{
		level.giveBoxInf = 1;
		self iPrintlnBold("^5Inf.Ammo Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbInf = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbInf.angles = (0,10,0);
		level.gbInf setModel("t6_wpn_supply_drop_axis");

		level.gbInf2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbInf2.angles = (0,10,0);
		level.gbInf2 setModel("t6_wpn_tablet_view");

		level.gbInf3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbInf3.angles = (0,10,0);
		level.gbInf3 setModel("mp_flag_red");

		level thread gbInfconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxInf();
		}
	}
	else
	{
		level.giveBoxInf = 0;
		self iPrintlnBold("^5Inf.Ammo Box: ^1Deleted");

		level.gbInf delete();
		level.gbInf2 delete();
		level.gbInf3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxInf");
		}
	}
}
dogiveBoxInf()
{
	self endon("disconnect");
	self endon("stop_giveBoxInf");
	for(;;)
	{
		self.gbwInf destroy();
		if(distance(self.origin, level.gbInf.origin) < 80)
		{
			self.gbwInf = self createFontString("hudbig", 2);
			self.gbwInf setPoint("TOP", "TOP", 0, 20);
			self.gbwInf setText("^3Press [{+usereload}] for ^6Infinity Ammo");

			if(self usebuttonpressed())
			{
				self thread doInfAmmo();
			}
		}
		wait 0.3;
	}
}

//--------------------

gb3rdconnect()
{
	level endon("disconnect");
	level endon("stop_giveBox3rd");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gb3rdspawned();
	}
}
gb3rdspawned()
{
	self waittill("spawned_player");
	self thread dogiveBox3rd();
}
giveBox3rd()
{
	if(level.giveBox3rd == 0)
	{
		level.giveBox3rd = 1;
		self iPrintlnBold("^53rd Person Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gb3rd = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gb3rd.angles = (0,10,0);
		level.gb3rd setModel("t6_wpn_supply_drop_axis");

		level.gb3rd2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gb3rd2.angles = (0,10,0);
		level.gb3rd2 setModel("t6_wpn_tablet_view");

		level.gb3rd3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gb3rd3.angles = (0,10,0);
		level.gb3rd3 setModel("mp_flag_red");

		level thread gb3rdconnect();
		foreach(p in level.players)
		{
			p thread dogiveBox3rd();
		}
	}
	else
	{
		level.giveBox3rd = 0;
		self iPrintlnBold("^53rd Person Box: ^1Deleted");

		level.gb3rd delete();
		level.gb3rd2 delete();
		level.gb3rd3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBox3rd");
		}
	}
}
dogiveBox3rd()
{
	self endon("disconnect");
	self endon("stop_giveBox3rd");
	for(;;)
	{
		self.gbw3rd destroy();
		if(distance(self.origin, level.gb3rd.origin) < 80)
		{
			self.gbw3rd = self createFontString("hudbig", 2);
			self.gbw3rd setPoint("TOP", "TOP", 0, 20);
			self.gbw3rd setText("^3Press [{+usereload}] for ^63rd Person");

			if(self usebuttonpressed())
			{
				self thread giveTP();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbNVconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxNV");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbNVspawned();
	}
}
gbNVspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxNV();
}
giveBoxNV()
{
	if(level.giveBoxNV == 0)
	{
		level.giveBoxNV = 1;
		self iPrintlnBold("^5Night Vision Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbNV = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbNV.angles = (0,10,0);
		level.gbNV setModel("t6_wpn_supply_drop_axis");

		level.gbNV2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbNV2.angles = (0,10,0);
		level.gbNV2 setModel("t6_wpn_tablet_view");

		level.gbNV3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbNV3.angles = (0,10,0);
		level.gbNV3 setModel("mp_flag_red");

		level thread gbNVconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxNV();
		}
	}
	else
	{
		level.giveBoxNV = 0;
		self iPrintlnBold("^5Night Vision Box: ^1Deleted");

		level.gbNV delete();
		level.gbNV2 delete();
		level.gbNV3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxNV");
		}
	}
}
dogiveBoxNV()
{
	self endon("disconnect");
	self endon("stop_giveBoxNV");
	for(;;)
	{
		self.gbwNV destroy();
		if(distance(self.origin, level.gbNV.origin) < 80)
		{
			self.gbwNV = self createFontString("hudbig", 2);
			self.gbwNV setPoint("TOP", "TOP", 0, 20);
			self.gbwNV setText("^3Press [{+usereload}] for ^6Night Vision");

			if(self usebuttonpressed())
			{
				self thread Thermalv();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbWalkconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxWalk");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbWalkspawned();
	}
}
gbWalkspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxWalk();
}
giveBoxWalk()
{
	if(level.giveBoxWalk == 0)
	{
		level.giveBoxWalk = 1;
		self iPrintlnBold("^5Walk Speed Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbWalk = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbWalk.angles = (0,10,0);
		level.gbWalk setModel("t6_wpn_supply_drop_axis");

		level.gbWalk2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbWalk2.angles = (0,10,0);
		level.gbWalk2 setModel("t6_wpn_tablet_view");

		level.gbWalk3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbWalk3.angles = (0,10,0);
		level.gbWalk3 setModel("mp_flag_red");

		level thread gbWalkconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxWalk();
		}
	}
	else
	{
		level.giveBoxWalk = 0;
		self iPrintlnBold("^5Walk Speed Box: ^1Deleted");

		level.gbWalk delete();
		level.gbWalk2 delete();
		level.gbWalk3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxWalk");
		}
	}
}
dogiveBoxWalk()
{
	self endon("disconnect");
	self endon("stop_giveBoxWalk");
	for(;;)
	{
		self.gbwWalk destroy();
		if(distance(self.origin, level.gbWalk.origin) < 80)
		{
			self.gbwWalk = self createFontString("hudbig", 2);
			self.gbwWalk setPoint("TOP", "TOP", 0, 20);
			self.gbwWalk setText("^3Press [{+usereload}] for ^6Walk Speed Change");

			if(self usebuttonpressed())
			{
				self thread doClientsSpeed();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbRWepconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxRWep");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbRWepspawned();
	}
}
gbRWepspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxRWep();
}
giveBoxRWep()
{
	if(level.giveBoxRWep == 0)
	{
		level.giveBoxRWep = 1;
		self iPrintlnBold("^5Random Weapons Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbRWep = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbRWep.angles = (0,10,0);
		level.gbRWep setModel("t6_wpn_supply_drop_axis");

		level.gbRWep2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbRWep2.angles = (0,10,0);
		level.gbRWep2 setModel("t6_wpn_tablet_view");

		level.gbRWep3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbRWep3.angles = (0,10,0);
		level.gbRWep3 setModel("mp_flag_red");

		level thread gbRWepconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxRWep();
		}
	}
	else
	{
		level.giveBoxRWep = 0;
		self iPrintlnBold("^5Random Weapons Box: ^1Deleted");

		level.gbRWep delete();
		level.gbRWep2 delete();
		level.gbRWep3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxRWep");
		}
	}
}
dogiveBoxRWep()
{
	self endon("disconnect");
	self endon("stop_giveBoxRWep");
	for(;;)
	{
		self.gbwRWep destroy();
		if(distance(self.origin, level.gbRWep.origin) < 80)
		{
			self.gbwRWep = self createFontString("hudbig", 2);
			self.gbwRWep setPoint("TOP", "TOP", 0, 20);
			self.gbwRWep setText("^3Press [{+usereload}] for ^6Random Weapons");

			if(self usebuttonpressed())
			{
				self thread giveRWeapon();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbDHPconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxDHP");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbDHPspawned();
	}
}
gbDHPspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxDHP();
}
giveBoxDHP()
{
	if(level.giveBoxDHP == 0)
	{
		level.giveBoxDHP = 1;
		self iPrintlnBold("^5Display HP Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbDHP = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbDHP.angles = (0,10,0);
		level.gbDHP setModel("t6_wpn_supply_drop_axis");

		level.gbDHP2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbDHP2.angles = (0,10,0);
		level.gbDHP2 setModel("t6_wpn_tablet_view");

		level.gbDHP3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbDHP3.angles = (0,10,0);
		level.gbDHP3 setModel("mp_flag_red");

		level thread gbDHPconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxDHP();
		}
	}
	else
	{
		level.giveBoxDHP = 0;
		self iPrintlnBold("^5Display HP Box: ^1Deleted");

		level.gbDHP delete();
		level.gbDHP2 delete();
		level.gbDHP3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxDHP");
		}
	}
}
dogiveBoxDHP()
{
	self endon("disconnect");
	self endon("stop_giveBoxDHP");
	for(;;)
	{
		self.gbwDHP destroy();
		if(distance(self.origin, level.gbDHP.origin) < 80)
		{
			self.gbwDHP = self createFontString("hudbig", 2);
			self.gbwDHP setPoint("TOP", "TOP", 0, 20);
			self.gbwDHP setText("^3Press [{+usereload}] for ^6Display HP");

			if(self usebuttonpressed())
			{
				self thread initHealthBar();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbNocconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxNoc");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbNocspawned();
	}
}
gbNocspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxNoc();
}
giveBoxNoc()
{
	if(level.giveBoxNoc == 0)
	{
		level.giveBoxNoc = 1;
		self iPrintlnBold("^5Advanced No Clip Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbNoc = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbNoc.angles = (0,10,0);
		level.gbNoc setModel("t6_wpn_supply_drop_axis");

		level.gbNoc2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbNoc2.angles = (0,10,0);
		level.gbNoc2 setModel("t6_wpn_tablet_view");

		level.gbNoc3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbNoc3.angles = (0,10,0);
		level.gbNoc3 setModel("mp_flag_red");

		level thread gbNocconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxNoc();
		}
	}
	else
	{
		level.giveBoxNoc = 0;
		self iPrintlnBold("^5Advanced No Clip Box: ^1Deleted");

		level.gbNoc delete();
		level.gbNoc2 delete();
		level.gbNoc3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxNoc");
		}
	}
}
dogiveBoxNoc()
{
	self endon("disconnect");
	self endon("stop_giveBoxNoc");
	for(;;)
	{
		self.gbwNoc destroy();
		if(distance(self.origin, level.gbNoc.origin) < 80)
		{
			self.gbwNoc = self createFontString("hudbig", 2);
			self.gbwNoc setPoint("TOP", "TOP", 0, 20);
			self.gbwNoc setText("^3Press [{+usereload}] for ^6Advanced No Clip");

			if(self usebuttonpressed())
			{
				self thread doNoClip();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbForgconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxForg");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbForgspawned();
	}
}
gbForgspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxForg();
}
giveBoxForg()
{
	if(level.giveBoxForg == 0)
	{
		level.giveBoxForg = 1;
		self iPrintlnBold("^5Advanced Forge Mode Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbForg = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbForg.angles = (0,10,0);
		level.gbForg setModel("t6_wpn_supply_drop_axis");

		level.gbForg2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbForg2.angles = (0,10,0);
		level.gbForg2 setModel("t6_wpn_tablet_view");

		level.gbForg3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbForg3.angles = (0,10,0);
		level.gbForg3 setModel("mp_flag_red");

		level thread gbForgconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxForg();
		}
	}
	else
	{
		level.giveBoxForg = 0;
		self iPrintlnBold("^5Advanced Forge Mode Box: ^1Deleted");

		level.gbForg delete();
		level.gbForg2 delete();
		level.gbForg3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxForg");
		}
	}
}
dogiveBoxForg()
{
	self endon("disconnect");
	self endon("stop_giveBoxForg");
	for(;;)
	{
		self.gbwForg destroy();
		if(distance(self.origin, level.gbForg.origin) < 80)
		{
			self.gbwForg = self createFontString("hudbig", 2);
			self.gbwForg setPoint("TOP", "TOP", 0, 20);
			self.gbwForg setText("^3Press [{+usereload}] for ^6Advanced Forge Mode");

			if(self usebuttonpressed())
			{
				self thread ForgeMode();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbJumpconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxJump");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbJumpspawned();
	}
}
gbJumpspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxJump();
}
giveBoxJump()
{
	if(level.giveBoxJump == 0)
	{
		level.giveBoxJump = 1;
		self iPrintlnBold("^5Mulit Jump Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbJump = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbJump.angles = (0,10,0);
		level.gbJump setModel("t6_wpn_supply_drop_axis");

		level.gbJump2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbJump2.angles = (0,10,0);
		level.gbJump2 setModel("t6_wpn_tablet_view");

		level.gbJump3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbJump3.angles = (0,10,0);
		level.gbJump3 setModel("mp_flag_red");

		level thread gbJumpconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxJump();
		}
	}
	else
	{
		level.giveBoxJump = 0;
		self iPrintlnBold("^5Mulit Jump Box: ^1Deleted");

		level.gbJump delete();
		level.gbJump2 delete();
		level.gbJump3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxJump");
		}
	}
}
dogiveBoxJump()
{
	self endon("disconnect");
	self endon("stop_giveBoxJump");
	for(;;)
	{
		self.gbwJump destroy();
		if(distance(self.origin, level.gbJump.origin) < 80)
		{
			self.gbwJump = self createFontString("hudbig", 2);
			self.gbwJump setPoint("TOP", "TOP", 0, 20);
			self.gbwJump setText("^3Press [{+usereload}] for ^6Mulit Jump");

			if(self usebuttonpressed())
			{
				self thread Toggle_Multijump();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbNinjconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxNinj");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbNinjspawned();
	}
}
gbNinjspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxNinj();
}
giveBoxNinj()
{
	if(level.giveBoxNinj == 0)
	{
		level.giveBoxNinj = 1;
		self iPrintlnBold("^5Ninja Mode Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbNinj = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbNinj.angles = (0,10,0);
		level.gbNinj setModel("t6_wpn_supply_drop_axis");

		level.gbNinj2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbNinj2.angles = (0,10,0);
		level.gbNinj2 setModel("t6_wpn_tablet_view");

		level.gbNinj3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbNinj3.angles = (0,10,0);
		level.gbNinj3 setModel("mp_flag_red");

		level thread gbNinjconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxNinj();
		}
	}
	else
	{
		level.giveBoxNinj = 0;
		self iPrintlnBold("^5Ninja Mode Box: ^1Deleted");

		level.gbNinj delete();
		level.gbNinj2 delete();
		level.gbNinj3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxNinj");
		}
	}
}
dogiveBoxNinj()
{
	self endon("disconnect");
	self endon("stop_giveBoxNinj");
	for(;;)
	{
		self.gbwNinj destroy();
		if(distance(self.origin, level.gbNinj.origin) < 80)
		{
			self.gbwNinj = self createFontString("hudbig", 2);
			self.gbwNinj setPoint("TOP", "TOP", 0, 20);
			self.gbwNinj setText("^3Press [{+usereload}] for ^6Ninja Mode");

			if(self usebuttonpressed())
			{
				self thread doNinja();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbFireconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxFire");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbFirespawned();
	}
}
gbFirespawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxNinj();
}
giveBoxFire()
{
	if(level.giveBoxFire == 0)
	{
		level.giveBoxFire = 1;
		self iPrintlnBold("^5Human Torch Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbFire = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbFire.angles = (0,10,0);
		level.gbFire setModel("t6_wpn_supply_drop_axis");

		level.gbFire2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbFire2.angles = (0,10,0);
		level.gbFire2 setModel("t6_wpn_tablet_view");

		level.gbFire3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbFire3.angles = (0,10,0);
		level.gbFire3 setModel("mp_flag_red");

		level thread gbFireconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxFire();
		}
	}
	else
	{
		level.giveBoxFire = 0;
		self iPrintlnBold("^5Human Torch Box: ^1Deleted");

		level.gbFire delete();
		level.gbFire2 delete();
		level.gbFire3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxFire");
		}
	}
}
dogiveBoxFire()
{
	self endon("disconnect");
	self endon("stop_giveBoxFire");
	for(;;)
	{
		self.gbwFire destroy();
		if(distance(self.origin, level.gbFire.origin) < 80)
		{
			self.gbwFire = self createFontString("hudbig", 2);
			self.gbwFire setPoint("TOP", "TOP", 0, 20);
			self.gbwFire setText("^3Press [{+usereload}] for ^6Human Torch");

			if(self usebuttonpressed())
			{
				self thread initHTorch();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbExBuconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxExBu");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbExBuspawned();
	}
}
gbExBuspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxExBu();
}
giveBoxExBu()
{
	if(level.giveBoxExBu == 0)
	{
		level.giveBoxExBu = 1;
		self iPrintlnBold("^5Explosive Bullets Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbExBu = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbExBu.angles = (0,10,0);
		level.gbExBu setModel("t6_wpn_supply_drop_axis");

		level.gbExBu2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbExBu2.angles = (0,10,0);
		level.gbExBu2 setModel("t6_wpn_tablet_view");

		level.gbExBu3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbExBu3.angles = (0,10,0);
		level.gbExBu3 setModel("mp_flag_red");

		level thread gbExBuconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxExBu();
		}
	}
	else
	{
		level.giveBoxExBu = 0;
		self iPrintlnBold("^5Explosive Bullets Box: ^1Deleted");

		level.gbExBu delete();
		level.gbExBu2 delete();
		level.gbExBu3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxExBu");
		}
	}
}
dogiveBoxExBu()
{
	self endon("disconnect");
	self endon("stop_giveBoxExBu");
	for(;;)
	{
		self.gbwExBu destroy();
		if(distance(self.origin, level.gbExBu.origin) < 80)
		{
			self.gbwExBu = self createFontString("hudbig", 2);
			self.gbwExBu setPoint("TOP", "TOP", 0, 20);
			self.gbwExBu setText("^3Press [{+usereload}] for ^6Explosive Bullets");

			if(self usebuttonpressed())
			{
				self thread ExpBultOn();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbEMPconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxEMP");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbEMPspawned();
	}
}
gbEMPspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxEMP();
}
giveBoxEMP()
{
	if(level.giveBoxEMP == 0)
	{
		level.giveBoxEMP = 1;
		self iPrintlnBold("^5EMP Bullets Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbEMP = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbEMP.angles = (0,10,0);
		level.gbEMP setModel("t6_wpn_supply_drop_axis");

		level.gbEMP2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbEMP2.angles = (0,10,0);
		level.gbEMP2 setModel("t6_wpn_tablet_view");

		level.gbEMP3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbEMP3.angles = (0,10,0);
		level.gbEMP3 setModel("mp_flag_red");

		level thread gbEMPconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxEMP();
		}
	}
	else
	{
		level.giveBoxEMP = 0;
		self iPrintlnBold("^5EMP Bullets Box: ^1Deleted");

		level.gbEMP delete();
		level.gbEMP2 delete();
		level.gbEMP3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxEMP");
		}
	}
}
dogiveBoxEMP()
{
	self endon("disconnect");
	self endon("stop_giveBoxEMP");
	for(;;)
	{
		self.gbwEMP destroy();
		if(distance(self.origin, level.gbEMP.origin) < 80)
		{
			self.gbwEMP = self createFontString("hudbig", 2);
			self.gbwEMP setPoint("TOP", "TOP", 0, 20);
			self.gbwEMP setText("^3Press [{+usereload}] for ^6EMP Bullets");

			if(self usebuttonpressed())
			{
				self thread initEMPBullets();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbMgBlconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxMgBl");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbMgBlspawned();
	}
}
gbMgBlspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxMgBl();
}
giveBoxMgBl()
{
	if(level.giveBoxMgBl == 0)
	{
		level.giveBoxMgBl = 1;
		self iPrintlnBold("^5Modded Bullets Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbMgBl = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbMgBl.angles = (0,10,0);
		level.gbMgBl setModel("t6_wpn_supply_drop_axis");

		level.gbMgBl2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbMgBl2.angles = (0,10,0);
		level.gbMgBl2 setModel("t6_wpn_tablet_view");

		level.gbMgBl3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbMgBl3.angles = (0,10,0);
		level.gbMgBl3 setModel("mp_flag_red");

		level thread gbMgBlconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxMgBl();
		}
	}
	else
	{
		level.giveBoxMgBl = 0;
		self iPrintlnBold("^5Modded Bullets Box: ^1Deleted");

		level.gbMgBl delete();
		level.gbMgBl2 delete();
		level.gbMgBl3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxMgBl");
		}
	}
}
dogiveBoxMgBl()
{
	self endon("disconnect");
	self endon("stop_giveBoxMgBl");
	for(;;)
	{
		self.gbwMgBl destroy();
		if(distance(self.origin, level.gbMgBl.origin) < 80)
		{
			self.gbwMgBl = self createFontString("hudbig", 2);
			self.gbwMgBl setPoint("TOP", "TOP", 0, 20);
			self.gbwMgBl setText("^3Press [{+usereload}] for ^6Modded Bullets");

			if(self usebuttonpressed())
			{
				self thread initMagicBullet();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbRPGconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxRPG");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbRPGspawned();
	}
}
gbRPGspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxRPG();
}
giveBoxRPG()
{
	if(level.giveBoxRPG == 0)
	{
		level.giveBoxRPG = 1;
		self iPrintlnBold("^5Rocket Teleporter Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbRPG = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbRPG.angles = (0,10,0);
		level.gbRPG setModel("t6_wpn_supply_drop_axis");

		level.gbRPG2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbRPG2.angles = (0,10,0);
		level.gbRPG2 setModel("t6_wpn_tablet_view");

		level.gbRPG3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbRPG3.angles = (0,10,0);
		level.gbRPG3 setModel("mp_flag_red");

		level thread gbRPGconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxRPG();
		}
	}
	else
	{
		level.giveBoxRPG = 0;
		self iPrintlnBold("^5Rocket Teleporter Box: ^1Deleted");

		level.gbRPG delete();
		level.gbRPG2 delete();
		level.gbRPG3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxRPG");
		}
	}
}
dogiveBoxRPG()
{
	self endon("disconnect");
	self endon("stop_giveBoxRPG");
	for(;;)
	{
		self.gbwRPG destroy();
		if(distance(self.origin, level.gbRPG.origin) < 80)
		{
			self.gbwRPG = self createFontString("hudbig", 2);
			self.gbwRPG setPoint("TOP", "TOP", 0, 20);
			self.gbwRPG setText("^3Press [{+usereload}] for ^6Rocket Teleporter");

			if(self usebuttonpressed())
			{
				self thread initRocketTeleport();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbJMisconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxJMis");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbJMisspawned();
	}
}
gbJMisspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxJMis();
}
giveBoxJMis()
{
	if(level.giveBoxJMis == 0)
	{
		level.giveBoxJMis = 1;
		self iPrintlnBold("^5Jericho Missiles Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbJMis = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbJMis.angles = (0,10,0);
		level.gbJMis setModel("t6_wpn_supply_drop_axis");

		level.gbJMis2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbJMis2.angles = (0,10,0);
		level.gbJMis2 setModel("t6_wpn_tablet_view");

		level.gbJMis3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbJMis3.angles = (0,10,0);
		level.gbJMis3 setModel("mp_flag_red");

		level thread gbJMisconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxJMis();
		}
	}
	else
	{
		level.giveBoxJMis = 0;
		self iPrintlnBold("^5Jericho Missiles Box: ^1Deleted");

		level.gbJMis delete();
		level.gbJMis2 delete();
		level.gbJMis3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxJMis");
		}
	}
}
dogiveBoxJMis()
{
	self endon("disconnect");
	self endon("stop_giveBoxJMis");
	for(;;)
	{
		self.gbwJMis destroy();
		if(distance(self.origin, level.gbJMis.origin) < 80)
		{
			self.gbwJMis = self createFontString("hudbig", 2);
			self.gbwJMis setPoint("TOP", "TOP", 0, 20);
			self.gbwJMis setText("^3Press [{+usereload}] for ^6Jericho Missiles");

			if(self usebuttonpressed())
			{
				self thread JeriMissOn();
			}
		}
		wait 0.3;
	}
}

//--------------------

gbCarconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxCar");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbCarspawned();
	}
}
gbCarspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxJMis();
}
giveBoxCar()
{
	if(level.giveBoxCar == 0)
	{
		level.giveBoxCar = 1;
		self iPrintlnBold("^5Drivable Car Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbCar = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbCar.angles = (0,10,0);
		level.gbCar setModel("t6_wpn_supply_drop_axis");

		level.gbCar2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbCar2.angles = (0,10,0);
		level.gbCar2 setModel("t6_wpn_tablet_view");

		level.gbCar3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbCar3.angles = (0,10,0);
		level.gbCar3 setModel("mp_flag_red");

		level thread gbCarconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxCar();
		}
	}
	else
	{
		level.giveBoxCar = 0;
		self iPrintlnBold("^5Drivable Car Box: ^1Deleted");

		level.gbCar delete();
		level.gbCar2 delete();
		level.gbCar3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxCar");
		}
	}
}
dogiveBoxCar()
{
	self endon("disconnect");
	self endon("stop_giveBoxCar");
	for(;;)
	{
		self.gbwCar destroy();
		if(distance(self.origin, level.gbCar.origin) < 80)
		{
			self.gbwCar = self createFontString("hudbig", 2);
			self.gbwCar setPoint("TOP", "TOP", 0, 20);
			self.gbwCar setText("^3Press [{+usereload}] for ^6Drivable Car\n^2and [{+attack}] for ^6Call Car");

			if(self usebuttonpressed())
			{
				if(self.gbCarUsed == 0)
				{
					self.gbCarUsed = 1;
					self thread initgiveBoxCar();
				}
			}
		}
		wait 0.3;
	}
}
initgiveBoxCar()
{
	self endon("disconnect");
	self endon("stop_initgiveBoxCar");
	for(;;)
	{
		self waittill("weapon_fired");
		self thread spawnDrivableCar();
		self notify("stop_initgiveBoxCar");
	}
}

//--------------------

gbACconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxAC");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbACspawned();
	}
}
gbACspawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxAC();
}
giveBoxAC()
{
	if(level.giveBoxAC == 0)
	{
		level.giveBoxAC = 1;
		self iPrintlnBold("^5Ace Combat Box: ^2Spawned");

		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);

		level.gbAC = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbAC.angles = (0,10,0);
		level.gbAC setModel("t6_wpn_supply_drop_axis");

		level.gbAC2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbAC2.angles = (0,10,0);
		level.gbAC2 setModel("t6_wpn_tablet_view");

		level.gbAC3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbAC3.angles = (0,10,0);
		level.gbAC3 setModel("mp_flag_red");

		level thread gbACconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxAC();
		}
	}
	else
	{
		level.giveBoxAC = 0;
		self iPrintlnBold("^5Ace Combat Box: ^1Deleted");

		level.gbAC delete();
		level.gbAC2 delete();
		level.gbAC3 delete();

		foreach(p in level.players)
		{
			p notify("stop_giveBoxAC");
		}
	}
}
dogiveBoxAC()
{
	self endon("disconnect");
	self endon("stop_giveBoxAC");
	for(;;)
	{
		self.gbwAC destroy();
		if(distance(self.origin, level.gbAC.origin) < 80)
		{
			self.gbwAC = self createFontString("hudbig", 2);
			self.gbwAC setPoint("TOP", "TOP", 0, 20);
			self.gbwAC setText("^3Press [{+usereload}] for ^6Ace Combat\n^2and [{+attack}] for ^6Call Jet");

			if(self usebuttonpressed())
			{
				if(self.gbACUsed == 0)
				{
					self.gbACUsed = 1;
					self thread initgiveBoxAC();
				}
			}
		}
		wait 0.3;
	}
}
initgiveBoxAC()
{
	self endon("disconnect");
	self endon("stop_initgiveBoxAC");
	for(;;)
	{
		self waittill("weapon_fired");
		self thread initFlyableJetMe();
		self notify("stop_initgiveBoxAC");
	}
}

//--------------------

gbHeliconnect()
{
	level endon("disconnect");
	level endon("stop_giveBoxHeli");
	for(;;)
	{
		level waittill("connecting", p);
		p thread gbHelispawned();
	}
}
gbHelispawned()
{
	self waittill("spawned_player");
	self thread dogiveBoxHeli();
}
giveBoxHeli()
{
	if(level.giveBoxHeli == 0)
	{
		level.giveBoxHeli = 1;
		self iPrintlnBold("^5Pilot Aircraft Box: ^2Spawned");
		self.giveBoxOrigin = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 165);
		level.gbHeli = spawn("script_model", self.giveBoxOrigin + (10, 0, 15));
		level.gbHeli.angles = (0,10,0);
		level.gbHeli setModel("t6_wpn_supply_drop_axis");
		level.gbHeli2 = spawn("script_model", self.giveBoxOrigin + (2, 0, 31));
		level.gbHeli2.angles = (0,10,0);
		level.gbHeli2 setModel("t6_wpn_tablet_view");
		level.gbHeli3 = spawn("script_model", self.giveBoxOrigin + (13, 0, 15));
		level.gbHeli3.angles = (0,10,0);
		level.gbHeli3 setModel("mp_flag_red");
		level thread gbHeliconnect();
		foreach(p in level.players)
		{
			p thread dogiveBoxHeli();
		}
	}
	else
	{
		level.giveBoxHeli = 0;
		foreach(p in level.players)
		{
			p notify("stop_giveBoxHeli");
		}
		level.gbHeli delete();
		level.gbHeli2 delete();
		level.gbHeli3 delete();
		self iPrintlnBold("^5Pilot Aircraft Box: ^1Deleted");
	}
}
dogiveBoxHeli()
{
	self endon("disconnect");
	self endon("stop_giveBoxHeli");
	for(;;)
	{
		self.gbwHeli destroy();
		if(distance(self.origin, level.gbHeli.origin) < 80)
		{
			self.gbwHeli = self createFontString("hudbig", 2);
			self.gbwHeli setPoint("TOP", "TOP", 0, 20);
			self.gbwHeli setText("^3Press [{+usereload}] for ^6Pilot Aircraft");

			if(self usebuttonpressed())
			{
				self thread initPilotHeliMe();
			}
		}
		wait 0.3;
	}
}

//===< Spawn Turrets >===

switchSpawnTurret(weap, spawntype)
{
    turret.angles = self.angles;
    turret.weaponinfoname = "auto_gun_turret_mp";
	
	if(spawntype == 0)
	{
		turret = spawnTurret("misc_turret", self.origin, weap);
		turret setModel("t6_wpn_turret_sentry_gun");
	}
	else if(spawntype == 1)
	{
		turret = spawnTurret("auto_turret", self.origin, weap);
		turret.turrettype = "sentry";
		turret setturrettype(turret.turrettype);
		turret setmodel(level.auto_turret_settings[turret.turrettype].modelgoodplacement);
	}
	else if(spawntype == 2)
	{
		turret = spawnTurret("auto_turret", self.origin, weap);
		turret.turrettype = "sentry";
		turret setturrettype(turret.turrettype);
		turret setmodel(level.auto_turret_settings[turret.turrettype].modelbadplacement);
	}
}
spawnturret1()
{
	switchSpawnTurret("auto_gun_turret_mp", 0);
}
spawnturret2()
{
	switchSpawnTurret("remote_missile_bomblet_mp", 1);
}
spawnturret3()
{
	switchSpawnTurret("straferun_rockets_mp", 2);
}
spawnturret4()
{
	switchSpawnTurret("chopper_minigun_mp", 0);
}

//===< Drivable Car >===

spawnDrivableCar()
{
    if(!isDefined(self.car["spawned"]))
    {
        setDvar("cg_thirdPersonRange", "300");
        self.car["carModel"] = "veh_t6_drone_rcxd";
        self.car["spawned"] = true;
        self.car["runCar"] = true;
        self.car["spawnPosition"] = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 100);
        self.car["spawnAngles"] = (0, self getPlayerAngles()[1], self getPlayerAngles()[2]);

        self.car["carEntity"] = spawn("script_model", self.car["spawnPosition"]);
        self.car["carEntity"].angles = self.car["spawnAngles"];
        self.car["carEntity"] setModel(self.car["carModel"]);

        wait .2;
        thread Vehicle_Wait_Think();
        
    }
    else
        iPrintln("You Can Only Spawn One Car At A Time!");
}
Vehicle_Wait_Think()
{
    self endon("disconnect");
    self endon("end_car");

    while(self.car["runCar"])
    {
        if(distance(self.origin, self.car["carEntity"].origin) < 120)
        {
            if(self useButtonPressed())
            {
                if(!self.car["inCar"])
                {
                    self iPrintln("Press [{+attack}] To Accelerate");
                    self iPrintln("Press [{+speed_throw}] To Reverse/Break");
                    self iPrintln("Press [{+reload}] To Exit Car");

                    self.car["speed"] = 0;
                    self.car["inCar"] = true;

                    self disableWeapons();
                    self detachAll();
                    self setOrigin(((self.car["carEntity"].origin) + (AnglesToForward(self.car["carEntity"].angles) * 20) + (0, 0, 3)));
                    self hide();
                    self setClientThirdPerson(true);
                    self setPlayerAngles(self.car["carEntity"].angles + (0, 0, 0));
                    self PlayerLinkTo(self.car["carEntity"]);

                    thread Vehicle_Physics_Think();
                    thread Vehicle_Death_Think();

                    wait 1;
                }
                else
                    thread Vehicle_Exit_Think();
            }
        }
        wait .05;
    }
}
Vehicle_Physics_Think()
{
    self endon("disconnect");
    self endon("end_car");

    self.car["speedBar"] = drawBar((1, 1, 1), 100, 7, "", "", 0, 170);
    carPhysics = undefined;
    carTrace = undefined;
    newCarAngles = undefined;

    while(self.car["runCar"])
    {
        carPhysics = ((self.car["carEntity"].origin) + ((AnglesToForward(self.car["carEntity"].angles) * (self.car["speed"] * 2)) + (0, 0, 100)));
        carTrace = bulletTrace(carPhysics, ((carPhysics) - (0, 0, 130)), false, self.car["carEntity"])["position"];
        if(self attackButtonPressed())
        {
            if(self.car["speed"] < 0)
                self.car["speed"] = 0;

            if(self.car["speed"] < 50)
                self.car["speed"] += 0.4;
                
            newCarAngles = vectorToAngles(carTrace - self.car["carEntity"].origin);
            self.car["carEntity"] moveTo(carTrace, 0.2);
            self.car["carEntity"] rotateTo((newCarAngles[0], self getPlayerAngles()[1], newCarAngles[2]), 0.2);
        }
        else
        {
            if(self.car["speed"] > 0)
            {
                newCarAngles = vectorToAngles(carTrace - self.car["carEntity"].origin);
                self.car["speed"] -= 0.7;
                self.car["carEntity"] moveTo(carTrace, 0.2);
                self.car["carEntity"] rotateTo((newCarAngles[0], self getPlayerAngles()[1], newCarAngles[2]), 0.2);
            }
        }
        if(self adsButtonPressed())
        {
            if(self.car["speed"] > -20)
            {
                if(self.car["speed"] < 0)
                    newCarAngles = vectorToAngles(self.car["carEntity"].origin - carTrace);
                    
                self.car["speed"] -= 0.5;
                self.car["carEntity"] moveTo(carTrace, 0.2);
            }
            else
                self.car["speed"] += 0.5;
                
            self.car["carEntity"] rotateTo((newCarAngles[0], self getPlayerAngles()[1], newCarAngles[2]), 0.2);
        }
        else
        {
            if(self.car["speed"] < -1)
            {
                if(self.car["speed"] < 0)
                    newCarAngles = vectorToAngles(self.car["carEntity"].origin - carTrace);
                    
                self.car["speed"] += 0.8;
                self.car["carEntity"] moveTo(carTrace, 0.2);
                self.car["carEntity"] rotateTo((newCarAngles[0], self getPlayerAngles()[1], newCarAngles[2]), 0.2);
            }
        }
        self.car["speedBar"] updateBar(self.car["speed"]/50);
        wait 0.05;
    }
}
Vehicle_Death_Think()
{
    self endon("disconnect");
    self endon("end_car");

    self waittill("death");
    if(self.car["inCar"])
        thread Vehicle_Exit_Think();
    else
        self.car["carEntity"] delete();
    wait 0.2;
}
Vehicle_Exit_Think()
{
	self.gbCarUsed = 0;
    self.car["speed"] = 0;
    self.car["inCar"] = false;
    self.car["runCar"] = false;
    self.car["spawned"] = undefined;
    self.car["speedBar"] destroy();
    self.car["carEntity"] delete();

    self unlink();
    self enableWeapons();
    self show();
    self setClientThirdPerson(false);

    wait 0.3;
    self notify("end_car");
}
traceBullet(distance)
{
    if (!isDefined(distance))
        distance = 10000000;
    return bulletTrace(self getEye(), self getEye() + vectorScale(AnglesToForward(self getPlayerAngles()), distance), false, self)["position"];
}
drawBar(color, width, height, align, relative, x, y)
{
    bar = createBar(color, width, height, self);
    bar setPoint(align, relative, x, y);
    bar.hideWhenInMenu = true;
    return bar;
}

//===< Ace Combat >===

playerAnglesToForward(player, distance)
{
	return player.origin + VectorScale(AnglesToForward(player getPlayerAngles(), distance));
}
traceBulletJet(traceDistance, traceReturn, detectPlayers)
{
	if (!isDefined(traceDistance))
		traceDistance = 10000000;

	if (!isDefined(traceReturn))
		traceReturn = "position";

	if (!isDefined(detectPlayers))
		detectPlayers = false;

	return bulletTrace(self getEye(), self getEye() + VectorScale(AnglesToForward(self getPlayerAngles()), traceDistance), detectPlayers, self)[traceReturn];
}
switchFJetModel(code, name)
{
	level.FJetModel = code;
	self iPrintln("^3Set Jet's Model to ^6" + name);
	level.FJetMCheck = 1;
	self changeFJetTPR();
}
changeFJetTPR()
{
	if(level.FJetModel == "veh_t6_air_a10f_alt" || level.FJetModel == "veh_t6_air_v78_vtol_killstreak")
	{
		setDvar("cg_thirdPersonRange", "700");
	}
	else if(level.FJetModel == "veh_t6_air_fa38_killstreak" || level.FJetModel == "veh_t6_drone_pegasus_mp")
	{
		setDvar("cg_thirdPersonRange", "500");
	}
	else if(level.FJetModel == "veh_t6_drone_uav")
	{
		setDvar("cg_thirdPersonRange", "400");
	}
}
setFJetMatb()
{
	self switchFJetModel("veh_t6_air_a10f_alt", "A10 Thunderbolt");
}
setFJetMharr()
{
	self switchFJetModel("veh_t6_air_fa38_killstreak", "Harrier");
}
setFJetMuav()
{
	self switchFJetModel("veh_t6_drone_uav", "UAV");
}
setFJetMstb()
{
	self switchFJetModel("veh_t6_drone_pegasus_mp", "Stealth Bomber");
}
setFJetMvtol()
{
	self switchFJetModel("veh_t6_air_v78_vtol_killstreak", "VTOL Warship");
}
initFlyableJet()
{
	if(level.JetSpawned == 0)
	{
		level.JetSpawned = 1;
		if(level.FJetMCheck == 0)
		{
			self setFJetMatb();
		}

		self.FJet["setOrigin"] = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 260);
		level.FJetEntity = spawn("script_model", self.FJet["setOrigin"] + (0, 0, 70));
		level.FJetEntity.angles = (0, 10, 0);
		level.FJetEntity setModel(level.FJetModel);

		self iPrintlnbold("^3Flyable Jet ^2Spawned");
		foreach(p in level.players)
		{
			p thread doFlyableJet();
		}
	}
	else
	{
		self iPrintlnbold("^3Flyable Jet is ^1already Spawned");
	}
}
doFlyableJet()
{
	self endon("disconnect");
	self endon("stop_doFJet");
	self endon("stop_threeFJet");

	for(;;)
	{
		self.FJetRaidInfo destroy();

		if(distance(self.origin, level.FJetEntity.origin) < 170)
		{
			self.FJetRaidInfo = self createFontString("hudbig", 1.8);
			self.FJetRaidInfo setPoint("TOP", "TOP", 0, 50);
			self.FJetRaidInfo setText("^3Press [{+usereload}] to ^1Ride on Jet");

			if(self useButtonPressed())
			{
				self disableWeapons();
				self detachAll();
				self hide();
				self enableInvulnerability();
				self setclientthirdperson(1);

				self thread moveFlyableJet();
				self thread doWeapFJet();
				self thread stopFlyableJet();
				self thread exitFlyableJet();
				self thread doFJCInfoOn();
			}
		}
		wait 0.05;
	}
}
doFJCInfoOn()
{
	if (self.initFJCInfoOn == 0)
	{
		self.FJCInfoOn = self drawText("[{+attack}] ^2Accel\n[{+smoke}] Drop Carepackage\n[{+switchseat}] ^5Change Weapon\n[{+speed_throw}] Fire Weapon\n[{+frag}] Bomblet to Under\n[{+stance}] ^1Exit\n[{+melee}] Delete Jet", "objective", 1.5, -280, 250, (1, 1, 1), 0, (0, 0, 1), 1, 1);
		self.initFJCInfoOn = 1;
	}
	self.FJCInfoOn fadeAlphaChange(.2, 1);

	foreach(p in level.players)
	{
		p notify("stop_doFJet");
		p.FJetRaidInfo destroy();
	}
}
doFJCInfoOff()
{
	self.FJCInfoOn fadeAlphaChange(.2, 0);
	wait 0.2;
	self.FJCInfoOn destroy();
}
moveFlyableJet()
{
	self endon("disconnect");
	self endon("stop_driveFJet");

	self changeFJetTPR();

	self setOrigin(((level.FJetEntity.origin + (0, -500, 300)) + (AnglesToForward(level.FJetEntity.angles) * 20) + ((0, 0, 3))));
	self setPlayerAngles(level.FJetEntity.angles + (0, 0, 0));
	self PlayerLinkTo(level.FJetEntity);

	self.FJetSBar = drawBar((1, 1, 1), 250, 7, "", "", 0, 170);
	level.FJetSpeed = 0;
	jetTrace = undefined;
	newJetAngles = undefined;

	for(;;)
	{
		jetTrace = playerAnglesToForward(self, 150 + level.FJetSpeed);
		level.FJetEntity rotateTo(self getPlayerAngles(), 0.2);

		if (self attackButtonPressed())
		{
			if(level.FJetSpeed < 0)
				level.FJetSpeed = 0;

			if(level.FJetSpeed < 250)
				level.FJetSpeed += 0.5;

			level.FJetEntity moveTo(jetTrace, 0.15);
		}
		else
		{
			if(level.FJetSpeed > 0)
			{
				newJetAngles = self getPlayerAngles();
				level.FJetSpeed -= 2;
				level.FJetEntity moveTo(jetTrace, 0.3);
			}
		}

		self.FJetSBar updateBar(level.FJetSpeed / 250);
		wait 0.05;
	}
}
doWeapFJet()
{
	self endon("disconnect");
	self endon("stop_weapSFJet");

	self changeFJetweap();

	self.FJetNowWeap = self drawText("^3Armament: ^5" + level.FJetWeapName, "objective", 2, 0, 330, (1, 1, 1), 0, (1, 0, 0), 1, 1);
	self.FJetNowWeap fadeAlphaChange(.2, 1);

	for(;;)
	{
		if(self changeSeatButtonPressed())
		{
			self changeFJetweap();
			self.FJetNowWeap destroy();
			self.FJetNowWeap = self drawText("^3Armament: ^5" + level.FJetWeapName, "objective", 2, 0, 330, (1, 1, 1), 0, (1, 0, 0), 1, 1);
			self.FJetNowWeap fadeAlphaChange(.2, 1);
			wait 0.2;
		}
		if(self adsButtonPressed())
		{
			MagicBullet(level.FJetWeapType, level.FJetEntity getTagOrigin("tag_origin") + (-180, 250, -100), self traceBulletJet(), self);
			MagicBullet(level.FJetWeapType, level.FJetEntity getTagOrigin("tag_origin") + (180, 250, -100), self traceBulletJet(), self);
			wait 0.2;
		}
		if(self fragButtonPressed())
		{
			MagicBullet(level.FJetWeapType, level.FJetEntity.origin + (0, 0, -90), level.FJetEntity.origin + (0, 0, -10000), self);
			wait 0.2;
		}
		if(self secondaryOffhandButtonPressed())
		{
			self thread maps\mp\killstreaks\_supplydrop::dropcrate(level.FJetEntity.origin + (0, 0, -20), self.angles, "supplydrop_mp", self, self.team, self.killcament, undefined, undefined, undefined);
			self iPrintln("^3Carepackage ^2Droped.");
			wait 0.5;
		}
		wait 0.05;
	}
}
changeFJetweap()
{
	if(level.FJetWeapon == 0)
	{
		level.FJetWeapon = 1;
		level.FJetWeapType = "smaw_mp";
		level.FJetWeapName = "SMAW";
	}
	else if(level.FJetWeapon == 1)
	{
		level.FJetWeapon = 2;
		level.FJetWeapType = "ai_tank_drone_rocket_mp";
		level.FJetWeapName = "A.G.R Rocket";
	}
	else if(level.FJetWeapon == 2)
	{
		level.FJetWeapon = 3;
		level.FJetWeapType = "straferun_rockets_mp";
		level.FJetWeapName = "Warthog Rockets";
	}
	else if(level.FJetWeapon == 3)
	{
		level.FJetWeapon = 4;
		level.FJetWeapType = "remote_missile_bomblet_mp";
		level.FJetWeapName = "Mortar Missile Burner";
	}
	else if(level.FJetWeapon == 4)
	{
		level.FJetWeapon = 5;
		level.FJetWeapType = "missile_swarm_projectile_mp";
		level.FJetWeapName = "Swarm";
	}
	else if(level.FJetWeapon == 5)
	{
		level.FJetWeapon = 0;
		level.FJetWeapType = "remote_mortar_missile_mp";
		level.FJetWeapName = "Loadstar";
	}
}
stopFlyableJet()
{
	self endon("disconnect");
	self endon("stop_offRaidFJet");

	for(;;)
	{
		if(self stanceButtonPressed())
		{
			self notify("stop_driveFJet");
			self notify("stop_weapSFJet");
			self notify("stop_oneExitFJet");

			level.FJetSpeed = 0;
			setDvar("cg_thirdPersonRange", "100");

			self.FJetSBar destroy();
			self.FJetNowWeap destroy();
			self unlink();
			self enableWeapons();
			self show();
			self setClientThirdPerson(0);
			self disableInvulnerability();
			self thread doFJCInfoOff();

			foreach(p in level.players)
			{
				p thread doFlyableJet();
			}
			self notify("stop_offRaidFJet");
		}
		wait 0.05;
	}
}
exitFlyableJet()
{
	self endon("disconnect");
	self endon("stop_oneExitFJet");

	for(;;)
	{
		if(self meleeButtonPressed())
		{
			self notify("stop_driveFJet");
			self notify("stop_weapSFJet");
			self notify("stop_offRaidFJet");

			level.FJetEntity delete();
			level.JetSpawned = 0;
			level.FJetSpeed = 0;
			setDvar("cg_thirdPersonRange", "100");

			self.FJetSBar destroy();
			self.FJetNowWeap destroy();
			self unlink();
			self enableWeapons();
			self show();
			self setClientThirdPerson(0);
			self disableInvulnerability();
			self thread doFJCInfoOff();

			foreach(p in level.players)
			{
				p notify("stop_threeFJet");
			}
			self notify("stop_oneExitFJet");
		}
		wait 0.05;
	}
}

switchFJetModelMe(code, name)
{
	self.FJetModel = code;
	self iPrintln("^3Set Jet's Model to ^6" + name);
	self.FJetMCheck = 1;
	self changeFJetTPRMe();
}
changeFJetTPRMe()
{
	if(self.FJetModel == "veh_t6_air_a10f_alt" || self.FJetModel == "veh_t6_air_v78_vtol_killstreak")
	{
		setDvar("cg_thirdPersonRange", "700");
	}
	else if(self.FJetModel == "veh_t6_air_fa38_killstreak" || self.FJetModel == "veh_t6_drone_pegasus_mp")
	{
		setDvar("cg_thirdPersonRange", "500");
	}
	else if(self.FJetModel == "veh_t6_drone_uav" || self.FJetModel == "veh_t6_drone_cuav")
	{
		setDvar("cg_thirdPersonRange", "400");
	}
}
setFJetMatbMe()
{
	self switchFJetModelMe("veh_t6_air_a10f_alt", "A10 Thunderbolt");
}
setFJetMharrMe()
{
	self switchFJetModelMe("veh_t6_air_fa38_killstreak", "Harrier");
}
setFJetMstbMe()
{
	self switchFJetModelMe("veh_t6_drone_pegasus_mp", "Stealth Bomber");
}
setFJetMcuav()
{
	self switchFJetModelMe("veh_t6_drone_cuav", "Counter UAV");
}
initFlyableJetMe()
{
	self endon("stop_threeFJetMe");

	if(self.JetSpawned == 0)
	{
		self.JetSpawned = 1;
		if(self.FJetMCheck == 0)
		{
			self setFJetMatbMe();
		}

		self.FJet["setOrigin"] = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 260);
		self.FJetEntity = spawn("script_model", self.FJet["setOrigin"] + (0, 0, 70));
		self.FJetEntity.angles = (0, 10, 0);
		self.FJetEntity setModel(self.FJetModel);

		self iPrintlnbold("^3Flyable Jet ^2Spawned");
		self thread doFlyableJetMe();
	}
	else
	{
		self iPrintlnbold("^3Flyable Jet is ^1already Spawned");
	}
}
doFlyableJetMe()
{
	self endon("disconnect");
	self endon("stop_doFJetMe");
	self endon("stop_threeFJetMe");

	for(;;)
	{
		self.FJetRaidInfoMe destroy();

		if(distance(self.origin, self.FJetEntity.origin) < 170)
		{
			self.FJetRaidInfoMe = self createFontString("hudbig", 1.8);
			self.FJetRaidInfoMe setPoint("TOP", "TOP", 0, 50);
			self.FJetRaidInfoMe setText("^3Press [{+usereload}] to ^1Ride on Jet");

			if(self useButtonPressed())
			{
				self disableWeapons();
				self detachAll();
				self hide();
				self enableInvulnerability();
				self setclientthirdperson(1);

				self thread moveFlyableJetMe();
				self thread doWeapFJetMe();
				self thread stopFlyableJetMe();
				self thread exitFlyableJetMe();
				self thread doFJCInfoOnMe();
			}
		}
		wait 0.05;
	}
}
doFJCInfoOnMe()
{
	if (self.initFJCInfoOnMe == 0)
	{
		self.FJCInfoOnMe = self drawText("[{+attack}] ^2Accel\n[{+smoke}] Drop Carepackage\n[{+switchseat}] ^5Change Weapon\n[{+speed_throw}] Fire Weapon\n[{+frag}] Bomblet to Under\n[{+stance}] ^1Exit\n[{+melee}] Delete Jet", "objective", 1.5, -280, 250, (1, 1, 1), 0, (0, 0, 1), 1, 1);
		self.initFJCInfoOnMe = 1;
	}
	self.FJCInfoOnMe fadeAlphaChange(.2, 1);

	self notify("stop_doFJetMe");
}
doFJCInfoOffMe()
{
	self.FJCInfoOnMe fadeAlphaChange(.2, 0);
}
moveFlyableJetMe()
{
	self endon("disconnect");
	self endon("stop_driveFJetMe");

	self.FJetRaidInfoMe destroy();
	self changeFJetTPRMe();

	self setOrigin(((self.FJetEntity.origin) + (AnglesToForward(self.FJetEntity.angles) * 20) + (0, 0, 3)));
	self setPlayerAngles(self.FJetEntity.angles + (0, 0, 0));
	self PlayerLinkTo(self.FJetEntity);

	self.FJetSBarMe = drawBar((1, 1, 1), 250, 7, "", "", 0, 170);
	self.FJetSpeed = 0;
	jetTrace = undefined;
	newJetAngles = undefined;

	for(;;)
	{
		jetTrace = playerAnglesToForward(self, 150 + self.FJetSpeed);
		self.FJetEntity rotateTo(self getPlayerAngles(), 0.2);

		if (self attackButtonPressed())
		{
			if(self.FJetSpeed < 0)
				self.FJetSpeed = 0;

			if(self.FJetSpeed < 250)
				self.FJetSpeed += 0.5;

			self.FJetEntity moveTo(jetTrace, 0.15);
		}
		else
		{
			if(self.FJetSpeed > 0)
			{
				newJetAngles = self getPlayerAngles();
				self.FJetSpeed -= 2;
				self.FJetEntity moveTo(jetTrace, 0.3);
			}
		}

		self.FJetSBarMe updateBar(self.FJetSpeed / 250);
		wait 0.05;
	}
}
doWeapFJetMe()
{
	self endon("disconnect");
	self endon("stop_weapSFJetMe");

	self changeFJetweapMe();

	self.FJetNowWeapMe = self drawText("^3Armament: ^5" + self.FJetWeapName, "objective", 2, 0, 330, (1, 1, 1), 0, (1, 0, 0), 1, 1);
	self.FJetNowWeapMe fadeAlphaChange(.2, 1);

	for(;;)
	{
		if(self changeSeatButtonPressed())
		{
			self changeFJetweapMe();
			self.FJetNowWeapMe destroy();
			self.FJetNowWeapMe = self drawText("^3Armament: ^5" + self.FJetWeapName, "objective", 2, 0, 330, (1, 1, 1), 0, (1, 0, 0), 1, 1);
			self.FJetNowWeapMe fadeAlphaChange(.2, 1);
			wait 0.2;
		}
		if(self adsButtonPressed())
		{
			MagicBullet(self.FJetWeapType, self.FJetEntity getTagOrigin("tag_origin") + (-180, 250, -100), self traceBulletJet(), self);
			MagicBullet(self.FJetWeapType, self.FJetEntity getTagOrigin("tag_origin") + (180, 250, -100), self traceBulletJet(), self);
			wait 0.1;
		}
		if(self fragButtonPressed())
		{
			MagicBullet(self.FJetWeapType, self.FJetEntity.origin + (0, 0, -90), self.FJetEntity.origin + (0, 0, -10000), self);
			wait 0.1;
		}
		if(self secondaryOffhandButtonPressed())
		{
			self thread maps\mp\killstreaks\_supplydrop::dropcrate(self.FJetEntity.origin + (0, 0, -20), self.angles, "supplydrop_mp", self, self.team, self.killcament, undefined, undefined, undefined);
			self iPrintln("^3Carepackage ^2Droped.");
			wait 0.5;
		}
		wait 0.05;
	}
}
changeFJetweapMe()
{
	if(self.FJetWeapon == 0)
	{
		self.FJetWeapon = 1;
		self.FJetWeapType = "smaw_mp";
		self.FJetWeapName = "SMAW";
	}
	else if(self.FJetWeapon == 1)
	{
		self.FJetWeapon = 2;
		self.FJetWeapType = "ai_tank_drone_rocket_mp";
		self.FJetWeapName = "A.G.R Rocket";
	}
	else if(self.FJetWeapon == 2)
	{
		self.FJetWeapon = 3;
		self.FJetWeapType = "straferun_rockets_mp";
		self.FJetWeapName = "Warthog Rockets";
	}
	else if(self.FJetWeapon == 3)
	{
		self.FJetWeapon = 4;
		self.FJetWeapType = "remote_missile_bomblet_mp";
		self.FJetWeapName = "Mortar Missile Burner";
	}
	else if(self.FJetWeapon == 4)
	{
		self.FJetWeapon = 5;
		self.FJetWeapType = "missile_swarm_projectile_mp";
		self.FJetWeapName = "Swarm";
	}
	else if(self.FJetWeapon == 5)
	{
		self.FJetWeapon = 6;
		self.FJetWeapType = "remote_mortar_missile_mp";
		self.FJetWeapName = "Loadstar";
	}
	else if(self.FJetWeapon == 6)
	{
		self.FJetWeapon = 0;
		self.FJetWeapType = "remote_missile_missile_mp";
		self.FJetWeapName = "Remote Mortar Missile";
	}
}
stopFlyableJetMe()
{
	self endon("disconnect");
	self endon("stop_offRaidFJetMe");

	for(;;)
	{
		if(self stanceButtonPressed())
		{
			self notify("stop_driveFJetMe");
			self notify("stop_weapSFJetMe");
			self notify("stop_oneExitFJetMe");

			self.FJetSpeed = 0;
			setDvar("cg_thirdPersonRange", "100");

			self.FJetSBarMe destroy();
			self.FJetNowWeapMe destroy();
			self unlink();
			self enableWeapons();
			self show();
			self setClientThirdPerson(0);
			self disableInvulnerability();
			self thread doFJCInfoOffMe();

			self thread doFlyableJetMe();
			self notify("stop_offRaidFJetMe");
		}
		wait 0.05;
	}
}
exitFlyableJetMe()
{
	self endon("disconnect");
	self endon("stop_oneExitFJetMe");

	for(;;)
	{
		if(self meleeButtonPressed())
		{
			self notify("stop_driveFJetMe");
			self notify("stop_weapSFJetMe");
			self notify("stop_offRaidFJetMe");

			self.FJetEntity delete();
			self.JetSpawned = 0;
			self.FJetSpeed = 0;
			self.gbACUsed = 0;
			setDvar("cg_thirdPersonRange", "100");

			self.FJetSBarMe destroy();
			self.FJetNowWeapMe destroy();
			self unlink();
			self enableWeapons();
			self show();
			self setClientThirdPerson(0);
			self disableInvulnerability();
			self thread doFJCInfoOffMe();
			self notify("stop_threeFJetMe");
			self notify("stop_oneExitFJetMe");
		}
		wait 0.05;
	}
}

//===< Pilot Helicopter >===

changePHeliType(code, code2, print)
{
	level.PHeliCheck = 1;
	level.PHeliModel = code;
	level.PHeliModel2 = code2;
	self iPrintln("^3Set Helicopter Model to ^2" + print);
	self changePHeliFov();
}
changePHeliFov()
{	
	if(level.PHeliModel2 == "veh_t6_drone_overwatch_light")
	{
		setDvar("cg_thirdPersonRange", "400");
	}
	else if(level.PHeliModel2 == "veh_t6_air_attack_heli_mp_dark")
	{
		setDvar("cg_thirdPersonRange", "550");
	}
	else if(level.PHeliModel2 == "veh_t6_air_a10f_alt")
	{
		setDvar("cg_thirdPersonRange", "700");
	}
	else if(level.PHeliModel2 == "veh_t6_drone_pegasus_mp")
	{
		setDvar("cg_thirdPersonRange", "600");
	}
}
PHeliModellb()
{
	changePHeliType("heli_guard_mp", "veh_t6_drone_overwatch_light", "Little Bird");
}
PHeliModelah()
{
	changePHeliType("heli_ai_mp", "veh_t6_air_attack_heli_mp_dark", "Attack Helicopter");
}
PHeliModela10()
{
	changePHeliType("heli_ai_mp", "veh_t6_air_a10f_alt", "A10 Thunderbolt");
}
PHeliModelstlh()
{
	changePHeliType("heli_ai_mp", "veh_t6_drone_pegasus_mp", "Stealth Bomber");
}

initPilotHeli()
{
	if(level.pilotHeliOn == 0)
	{
		level.pilotHeliOn = 1;
		if(level.PHeliCheck == 0)
		{
			level.PHeliCheck = 1;
			self thread PHeliModellb();
		}
		self thread comePilotHeli();
	}
	else
	{
		self iPrintlnbold("^3Helicopter is ^1already spawned.");
	}
}
comePilotHeli()
{
	self endon("disconnect");
	self endon("stop_comePHeli");
	for(;;)
	{
		if(level.comePHeliOn == 0)
		{
			self iPrintlnbold("^3Please set ^6Helicopter's landing zone.");
			wait 1;
			Location = locationSelector();
			level.comePHeliOn = 1;
		}
		if(level.comePHeliOn == 1)
		{
			level.PHeli = spawnHelicopter(self, self.origin + (12000, 0, 1500), self.angles, level.PHeliModel, level.PHeliModel2);
			level.PHeli.owner = self;
			level.PHeli.team = self.team;
			self iPrintlnbold("^3Landing zone ^2pointed.");
			self iPrintln("^1Helicopter will arrive soon...");
			level.comePHeliOn = 2;
		}
		if(level.comePHeliOn == 2)
		{
			level.PHeli setSpeed(1000, 25);
			level.PHeli setVehGoalPos(Location + (0, 0, 1500), 1);
			wait 14;
			level.PHeli setSpeed(200, 20);
			level.PHeli setVehGoalPos(Location + (0, 0, 65), 1);
			level.comePHeliOn = 0;
			foreach(p in level.players)
			{
				p thread ridePilotHeli();
			}
			self notify("stop_comePHeli");
		}
		wait 0.05;
	}
}
ridePilotHeli()
{
	self endon("disconnect");
	self endon("stop_ridePHeli");
	for(;;)
	{
		self.ridePHeliInfo destroy();
		if(distance(self.origin, level.PHeli.origin) < 150)
		{
			self.ridePHeliInfo = self createFontString("hudbig", 1.8);
			self.ridePHeliInfo setPoint( "TOP", "TOP", 0, 50 );
			self.ridePHeliInfo setText("^3Press [{+usereload}] to ^1Ride on Helicopter");

			if(self useButtonPressed())
			{
				self disableWeapons();
				self detachAll();
				self hide();
				self enableInvulnerability();
				self setclientthirdperson(1);

				self thread movePilotHeli();
				self thread attackPHeli();
				self thread stopPilotHeli();
				self thread exitPilotHeli();
				self thread infoPHeliOn();
			}
		}
		wait 0.05;
	}
}
infoPHeliOn()
{
	self.PHeliInfoOn = self drawText("^0R1 ^2Accel\n^0R2 ^2Rise\n^0L2 ^2Fall\n[{+switchseat}] ^5Change Weapon\n^0L1 ^5Fire Weapon\n^0<-- ^6Change Action\n[{+actionslot 2}] do Action\n[{+stance}] ^3Exit\n^0R3 ^3Delete", "objective", 1.2, -280, 225, (1, 1, 1), 0, (0, 0, 1), 1, 1);
	self.PHeliInfoOn fadeAlphaChange(.2, 1);

	foreach(p in level.players)
	{
		p notify("stop_ridePHeli");
		p.ridePHeliInfo destroy();
	}
}
infoPHeliOff()
{
	self.PHeliInfoOn fadeAlphaChange(.2, 0);
	wait 0.2;
	self.PHeliInfoOn destroy();
}
movePilotHeli()
{
	self endon("disconnect");
	self endon("stop_movePHeli");
	
	self changePHeliFov();
	self PlayerLinkTo(level.PHeli);
	self setPlayerAngles(level.PHeli.angles + (0, 0, 0));
	self setOrigin(((level.PHeli.origin + (-200, 0, 150)) + (AnglesToForward(level.PHeli.angles) * 30) + (0, 0, 3)));
	level.PHeliSpeed = 0;
	PHeliTrace = undefined;
	newPHeliAngles = undefined;

	for(;;)
	{
		PHeliTrace = playerAnglesToForward(self, 200 + level.PHeliSpeed);
		if(self attackButtonPressed())
		{
			if(level.PHeliSpeed < 0)
			{
				level.PHeliSpeed = 0;
			}
			if(level.PHeliSpeed < 500)
			{
				level.PHeliSpeed += 5;
				level.PHeli setYawSpeed(150, 80);
				level.PHeli setSpeed(270, 90);
				level.PHeli setVehGoalPos(PHeliTrace, 1);
			}
		}
		if(self fragButtonPressed())
		{
			if(level.PHeliSpeed < 0)
			{
				level.PHeliSpeed = 0;
			}
			if(level.PHeliSpeed < 500)
			{
				level.PHeliSpeed += 5;
				level.PHeli setYawSpeed(150, 80);
				level.PHeli setSpeed(270, 90);
				level.PHeli setVehGoalPos(level.PHeli.origin + (0, 0, level.PHeliSpeed), 1);
			}
		}
		if(self secondaryOffhandButtonPressed())
		{
			if(level.PHeliSpeed > 0)
			{
				level.PHeliSpeed = 0;
			}
			if(level.PHeliSpeed > -500)
			{
				level.PHeliSpeed -= 5;
				level.PHeli setYawSpeed(150, 80);
				level.PHeli setSpeed(270, 90);
				level.PHeli setVehGoalPos(level.PHeli.origin + (0, 0, level.PHeliSpeed), 1);
			}
		}
		if(level.PHeliSpeed == 500)
		{
				level.PHeliSpeed = 400;
		}
		if(level.PHeliSpeed == -500)
		{
				level.PHeliSpeed = -400;
		}
		wait 0.05;
	}
}
attackPHeli()
{
	self endon("disconnect");
	self endon("stop_attackPHeli");

	if(level.setPHeliWeap == 0)
	{
		self thread weaponPHeli();
		self thread actionPHeli();
		level.setPHeliWeap = 1;
	}

	self.PHeliNowWeap = self drawText("^3Armament: ^1" + level.PHeliWeapName, "objective", 2, 0, 330, (1, 1, 1), 0, (1, 0, 1), 1, 1);
	self.PHeliNowWeap fadeAlphaChange(.2, 1);
	self.PHeliNowAction = self drawText("^3Action: ^4" + level.PHeliactionName, "objective", 2, 0, 360, (1, 1, 1), 0, (0, 1, 1), 1, 1);
	self.PHeliNowAction fadeAlphaChange(.2, 1);

	for(;;)
	{
		if(self changeSeatButtonPressed())
		{
			self thread weaponPHeli();
			self.PHeliNowWeap destroy();
			self.PHeliNowWeap = self drawText("^3Armament: ^1" + level.PHeliWeapName, "objective", 2, 0, 330, (1, 1, 1), 0, (1, 0, 1), 1, 1);
			self.PHeliNowWeap fadeAlphaChange(.2, 1);
			wait 0.2;
		}
		if(self adsButtonPressed())
		{
			if(level.PHeliWeapType == "cobra_20mm_mp" || level.PHeliWeapType == "helicopter_player_gunner_mp")
			{
				MagicBullet(level.PHeliWeapType, level.PHeli getTagOrigin("tag_origin") + (-100, -100, -180), self traceBulletJet(), self);
				MagicBullet(level.PHeliWeapType, level.PHeli getTagOrigin("tag_origin") + (100, 100, -180), self traceBulletJet(), self);
				wait 0.01;
			}
			else
			{
				MagicBullet(level.PHeliWeapType, level.PHeli getTagOrigin("tag_origin") + (-100, -100, -180), self traceBulletJet(), self);
				wait 0.15;
				MagicBullet(level.PHeliWeapType, level.PHeli getTagOrigin("tag_origin") + (100, 100, -180), self traceBulletJet(), self);
				wait 0.15;
			}
		}
		if(self actionSlotThreeButtonPressed())
		{
			self notify("stop_bombUsing");
			self thread actionPHeli();
			self.PHeliNowAction destroy();
			self.PHeliNowAction = self drawText("^3Action: ^4" + level.PHeliactionName, "objective", 2, 0, 360, (1, 1, 1), 0, (0, 1, 1), 1, 1);
			self.PHeliNowAction fadeAlphaChange(.2, 1);
			wait 0.2;
		}
		if(self actionSlotTwoButtonPressed())
		{
			if(level.PHeliactionType == "dropCP")
			{
				self thread initPHeliCP();
			}
			else if(level.PHeliactionType == "empBomb")
			{
				self thread initPHeliNuke();
			}
			else if(level.PHeliactionType == "bomblet")
			{
				self thread initPHeliBomb();
			}
		}
		wait 0.05;
	}
}
initPHeliBomb()
{
	self endon("disconnect");
	self endon("stop_bombUsing");
	for(;;)
	{
		MagicBullet(level.PHeliWeapType, level.PHeli.origin + (0, 0, -220), level.PHeli.origin + (0, 0, -10000), self);
		wait 0.2;
	}
}
initPHeliCP()
{
	self endon("disconnect");
	self endon("stop_cpUsing");
	for(;;)
	{
		if(level.PHeliDroped == 0)
		{
			self thread maps\mp\killstreaks\_supplydrop::dropcrate(level.PHeli.origin + (0, 0, -20), self.angles, "supplydrop_mp", self, self.team, self.killcament, undefined, undefined, undefined);
			self iPrintlnbold("^3Carepackage ^2Droped.");
			self iPrintln("^3Next you can drop for ^1wait 5 sec.");
			level.PHeliDroped = 1;
		}
		if(level.PHeliDroped == 1)
		{
			wait 5;
			self iPrintln("^5Carepackage Drop ^2charged.");
			level.PHeliDroped = 0;
			self notify("stop_cpUsing");
		}
		wait 0.05;
	}
}
initPHeliNuke()
{
	self endon("disconnect");
	self endon("stop_nukeUsing");

	for(;;)
	{
		if(level.nukeUsed == 0)
		{
			foreach(p in level.players)
			{
				p thread maps\mp\gametypes\_hud_message::hintMessage("^3---^1Nuke Bomblet Warning^3---", 7);
			}

			PHeliNuke = spawn("script_model", level.PHeli.origin + (0, 0, -100));
			PHeliNuke setModel("projectile_sa6_missile_desert_mp");
			PHeliNuke.angles = (90, 90, 90);
			self thread nukeFireEffect(PHeliNuke);

			PHeliNuke moveto(PHeliNuke.origin + (0, 0, -750), 9);
			wait 9.1;
			self notify("stop_PHeliNuke");
		
			if(GetDvar("mapname") == "mp_nuketown_2020")
			{
				level._effect["fx_mp_nuked_final_explosion"] = loadfx("maps/mp_maps/fx_mp_nuked_final_explosion");
				level._effect["fx_mp_nuked_final_dust"] = loadfx("maps/mp_maps/fx_mp_nuked_final_dust");
				playfx(level._effect["fx_mp_nuked_final_explosion"], PHeliNuke.origin);
				playfx(level._effect["fx_mp_nuked_final_dust"], PHeliNuke.origin);
			}
			else
			{
				level._effect["emp_flash"] = loadfx("weapon/emp/fx_emp_explosion");
				playfx(level._effect["emp_flash"], PHeliNuke.origin);
			}

			foreach(p in level.players)
			{
				p playsound("wpn_emp_bomb");
			}
			earthquake(0.6, 7, PHeliNuke.origin, 12345);

			foreach(p in level.players)
			{
				if (level.teamBased && self.pers["team"] == p.pers["team"])
				{

				}
				else
				{
					if (p != self)
						p thread [[level.callbackPlayerDamage]](self, self, 1000, 0, "MOD_MELEE", "remote_missile_missile_mp", (0, 0, 0), (0, 0, 0), "head", 0, 0);
				}
			}

			wait 0.1;
			PHeliNuke delete();
			wait 7;
			self iPrintlnbold("^3Next you can use ^5Nuclear Explosion ^3for ^1wait 20 sec.");
			level.PHelinukePrint = 1;
			level.nukeUsed = 1;
		}
		if(level.nukeUsed == 1)
		{
			wait 13;
			self iPrintln("^5Nuclear Explosion ^2charged.");
			level.nukeUsed = 0;
			self notify("stop_nukeUsing");
		}
		wait 0.05;
	}
}
nukeFireEffect(PHeliNuke)
{
	self endon("disconnect");
	self endon("stop_PHeliNuke");
	level._effect["torch"] = loadfx( "maps/mp_maps/fx_mp_exp_rc_bomb" );
	for(;;)
	{
		PlayFX(level._effect["torch"], PHeliNuke.origin + (0, 0, 120));
		wait 0.1;
	}
}
weaponPHeli()
{
	if(level.PHeliWeapon == 0)
	{
		level.PHeliWeapon = 1;
		level.PHeliWeapType = "smaw_mp";
		level.PHeliWeapName = "SMAW";
	}
	else if(level.PHeliWeapon == 1)
	{
		level.PHeliWeapon = 2;
		level.PHeliWeapType = "ai_tank_drone_rocket_mp";
		level.PHeliWeapName = "A.G.R Rocket";
	}
	else if(level.PHeliWeapon == 2)
	{
		level.PHeliWeapon = 3;
		level.PHeliWeapType = "straferun_rockets_mp";
		level.PHeliWeapName = "Warthog Rockets";
	}
	else if(level.PHeliWeapon == 3)
	{
		level.PHeliWeapon = 4;
		level.PHeliWeapType = "remote_missile_bomblet_mp";
		level.PHeliWeapName = "Mortar Missile Burner";
	}
	else if(level.PHeliWeapon == 4)
	{
		level.PHeliWeapon = 5;
		level.PHeliWeapType = "missile_swarm_projectile_mp";
		level.PHeliWeapName = "Swarm";
	}
	else if(level.PHeliWeapon == 5)
	{
		level.PHeliWeapon = 6;
		level.PHeliWeapType = "remote_mortar_missile_mp";
		level.PHeliWeapName = "Loadstar";
	}
	else if(level.PHeliWeapon == 6)
	{
		level.PHeliWeapon = 7;
		level.PHeliWeapType = "remote_missile_missile_mp";
		level.PHeliWeapName = "Remote Mortar Missile";
	}
	else if(level.PHeliWeapon == 7)
	{
		level.PHeliWeapon = 0;
		level.PHeliWeapType = "cobra_20mm_mp";
		level.PHeliWeapName = "Cobra 20mm Bullet";
	}
}
actionPHeli()
{
	if(level.PHeliaction == 0)
	{
		level.PHeliaction = 1;
		level.PHeliactionType = "dropCP";
		level.PHeliactionName = "Drop CarePackage";
	}
	else if(level.PHeliaction == 1)
	{
		level.PHeliaction = 2;
		level.PHeliactionType = "empBomb";
		level.PHeliactionName = "Nuclear Explosion";
	}
	else if(level.PHeliaction == 2)
	{
		level.PHeliaction = 0;
		level.PHeliactionType = "bomblet";
		level.PHeliactionName = "Bomblet to Under";
	}
}
stopPilotHeli()
{
	self endon("disconnect");
	self endon("stop_stopPHeli");

	for(;;)
	{
		if(self stanceButtonPressed())
		{
			self notify("stop_movePHeli");
			self notify("stop_attackPHeli");
			self notify("stop_exitPHeli");
			self notify("stop_bombUsing");

			level.PHeliSpeed = 0;
			setDvar("cg_thirdPersonRange", "100");

			self.PHeliNowWeap destroy();
			self.PHeliNowAction destroy();
			self thread infoPHeliOff();
			self unlink();
			self enableWeapons();
			self show();
			self setClientThirdPerson(0);
			self disableInvulnerability();
			
			foreach(p in level.players)
			{
				p thread ridePilotHeli();
			}
			self notify("stop_stopPHeli");
		}
		wait 0.05;
	}
}
exitPilotHeli()
{
	self endon("disconnect");
	self endon("stop_exitPHeli");
	
	for(;;)
	{
		if(self meleeButtonPressed())
		{
			self notify("stop_movePHeli");
			self notify("stop_attackPHeli");
			self notify("stop_stopPHeli");
			self notify("stop_bombUsing");
			
			level.PHeliSpeed = 0;
			setDvar("cg_thirdPersonRange", "100");

			self.PHeliNowWeap destroy();
			self.PHeliNowAction destroy();
			self thread infoPHeliOff();
			self unlink();
			self enableWeapons();
			self show();
			self setClientThirdPerson(0);
			self disableInvulnerability();

			level.PHeli delete();
			level.pilotHeliOn = 0;
			self notify("stop_exitPHeli");
		}
		wait 0.05;
	}
}

//~~~< Self Type >~~~

changePHeliTypeMe(code, code2, print)
{
	self.PHeliCheck = 1;
	self.PHeliModel = code;
	self.PHeliModel2 = code2;
	self iPrintln("^3Set Helicopter Model to ^2" + print);
	self changePHeliFovMe();
}
changePHeliFovMe()
{	
	if(self.PHeliModel2 == "veh_t6_drone_overwatch_light" || self.PHeliModel2 == "veh_t6_drone_cuav")
	{
		setDvar("cg_thirdPersonRange", "450");
	}
	else if(self.PHeliModel2 == "veh_t6_air_attack_heli_mp_dark")
	{
		setDvar("cg_thirdPersonRange", "550");
	}
	else if(self.PHeliModel2 == "veh_t6_drone_pegasus_mp" || self.PHeliModel2 == "veh_t6_air_fa38_killstreak")
	{
		setDvar("cg_thirdPersonRange", "600");
	}
	else if(self.PHeliModel2 == "veh_t6_air_a10f_alt")
	{
		setDvar("cg_thirdPersonRange", "700");
	}
	else if(self.PHeliModel2 == "veh_t6_air_v78_vtol_killstreak")
	{
		setDvar("cg_thirdPersonRange", "800");
	}
}
PHeliModellbMe()
{
	changePHeliTypeMe("heli_guard_mp", "veh_t6_drone_overwatch_light", "Little Bird");
}
PHeliModelahMe()
{
	changePHeliTypeMe("heli_guard_mp", "veh_t6_air_attack_heli_mp_dark", "Attack Helicopter");
}
PHeliModela10Me()
{
	changePHeliTypeMe("heli_guard_mp", "veh_t6_air_a10f_alt", "A10 Thunderbolt");
}
PHeliModelstlhMe()
{
	changePHeliTypeMe("heli_guard_mp", "veh_t6_drone_pegasus_mp", "Stealth Bomber");
}
PHeliModelvtolMe()
{
	changePHeliTypeMe("heli_guard_mp", "veh_t6_air_v78_vtol_killstreak", "VTOL Warship");
}
PHeliModelfaMe()
{
	changePHeliTypeMe("heli_guard_mp", "veh_t6_air_fa38_killstreak", "FA38 Harrier");
}
PHeliModelcuavMe()
{
	changePHeliTypeMe("heli_guard_mp", "veh_t6_drone_cuav", "Counter UAV");
}
initPilotHeliMe()
{
	if(self.pilotHeliOn == 0)
	{
		self.pilotHeliOn = 1;
		if(self.PHeliCheck == 0)
		{
			self.PHeliCheck = 1;
			self PHeliModellbMe();
		}
		self thread comePilotHeliMe();
	}
	else
	{
		self iPrintlnbold("^3Helicopter is ^1already spawned.");
	}
}
comePilotHeliMe()
{
	self endon("disconnect");
	self endon("stop_comePHeliMe");
	for(;;)
	{
		if(self.comePHeliOn == 0)
		{
			self iPrintlnbold("^3Please set ^6Helicopter's landing zone.");
			wait 1;
			Location = locationSelector();
			self.comePHeliOn = 1;
		}
		if(self.comePHeliOn == 1)
		{
			self.PHeli = spawnHelicopter(self, self.origin + (12000, 0, 1500), self.angles, self.PHeliModel, self.PHeliModel2);
			self.PHeli.owner = self;
			self.PHeli.team = self.team;
			self iPrintlnbold("^3Landing zone ^2pointed.");
			self iPrintln("^1Helicopter will arrive soon...");
			self.comePHeliOn = 2;
		}
		if(self.comePHeliOn == 2)
		{
			self.PHeli setSpeed(1000, 25);
			self.PHeli setVehGoalPos(Location + (0, 0, 1500), 1);
			wait 14;
			self.PHeli setSpeed(200, 20);
			self.PHeli setVehGoalPos(Location + (0, 0, 65), 1);
			self.comePHeliOn = 0;
			self thread ridePilotHeliMe();
			self notify("stop_comePHeliMe");
		}
		wait 0.05;
	}
}
ridePilotHeliMe()
{
	self endon("disconnect");
	self endon("stop_ridePHeliMe");
	for(;;)
	{
		self.ridePHeliInfoMe destroy();
		if(distance(self.origin, self.PHeli.origin) < 150)
		{
			self.ridePHeliInfoMe = self createFontString("hudbig", 1.8);
			self.ridePHeliInfoMe setPoint( "TOP", "TOP", 0, 50 );
			self.ridePHeliInfoMe setText("^3Press [{+usereload}] to ^1Ride on Helicopter");

			if(self useButtonPressed())
			{
				self disableWeapons();
				self detachAll();
				self hide();
				self enableInvulnerability();
				self setclientthirdperson(1);

				self thread movePilotHeliMe();
				self thread attackPHeliMe();
				self thread stopPilotHeliMe();
				self thread exitPilotHeliMe();
				self thread infoPHeliOnMe();
			}
		}
		wait 0.05;
	}
}
infoPHeliOnMe()
{
	self.PHeliInfoOnMe = self drawText("^0R1 ^2Accel\n^0R2 ^2Rise\n^0L2 ^2Fall\n[{+switchseat}] ^5Change Weapon\n^0L1 ^5Fire Weapon\n^0<-- ^6Change Action\n[{+actionslot 2}] do Action\n[{+stance}] ^3Exit\n^0R3 ^3Delete", "objective", 1.2, -280, 225, (1, 1, 1), 0, (0, 0, 1), 1, 1);
	self.PHeliInfoOnMe fadeAlphaChange(.2, 1);

	self notify("stop_ridePHeliMe");
	self.ridePHeliInfoMe destroy();
}
infoPHeliOffMe()
{
	self.PHeliInfoOnMe fadeAlphaChange(.2, 0);
	wait 0.2;
	self.PHeliInfoOnMe destroy();
}
movePilotHeliMe()
{
	self endon("disconnect");
	self endon("stop_movePHeliMe");
	
	self changePHeliFovMe();
	self PlayerLinkTo(self.PHeli);
	self setPlayerAngles(self.PHeli.angles + (0, 0, 0));
	self setOrigin(((self.PHeli.origin + (-200, 0, 150)) + (AnglesToForward(self.PHeli.angles) * 30) + (0, 0, 3)));
	self.PHeliSpeed = 0;
	PHeliTrace = undefined;
	newPHeliAngles = undefined;

	for(;;)
	{
		PHeliTrace = playerAnglesToForward(self, 200 + self.PHeliSpeed);
		if(self attackButtonPressed())
		{
			if(self.PHeliSpeed < 0)
			{
				self.PHeliSpeed = 0;
			}
			if(self.PHeliSpeed < 1000)
			{
				self.PHeliSpeed += 5;
				self.PHeli setYawSpeed(200, 120);
				self.PHeli setSpeed(335, 130);
				self.PHeli setVehGoalPos(PHeliTrace, 1);
			}
		}
		if(self fragButtonPressed())
		{
			if(self.PHeliSpeed < 0)
			{
				self.PHeliSpeed = 0;
			}
			if(self.PHeliSpeed < 1000)
			{
				self.PHeliSpeed += 5;
				self.PHeli setYawSpeed(200, 120);
				self.PHeli setSpeed(335, 130);
				self.PHeli setVehGoalPos(self.PHeli.origin + (0, 0, self.PHeliSpeed), 1);
			}
		}
		if(self secondaryOffhandButtonPressed())
		{
			if(self.PHeliSpeed > 0)
			{
				self.PHeliSpeed = 0;
			}
			if(self.PHeliSpeed > -1000)
			{
				self.PHeliSpeed -= 5;
				self.PHeli setYawSpeed(200, 120);
				self.PHeli setSpeed(335, 130);
				self.PHeli setVehGoalPos(self.PHeli.origin + (0, 0, self.PHeliSpeed), 1);
			}
		}
		if(self.PHeliSpeed == 1000)
		{
				self.PHeliSpeed = 900;
		}
		if(self.PHeliSpeed == -1000)
		{
				self.PHeliSpeed = -900;
		}
		wait 0.05;
	}
}
attackPHeliMe()
{
	self endon("disconnect");
	self endon("stop_attackPHeliMe");

	if(self.setPHeliWeap == 0)
	{
		self thread weaponPHeliMe();
		self thread actionPHeliMe();
		self.setPHeliWeap = 1;
	}

	self.PHeliNowWeapMe = self drawText("^3Armament: ^1" + self.PHeliWeapName, "objective", 2, 0, 330, (1, 1, 1), 0, (1, 0, 1), 1, 1);
	self.PHeliNowWeapMe fadeAlphaChange(.2, 1);
	self.PHeliNowActionMe = self drawText("^3Action: ^4" + self.PHeliactionName, "objective", 2, 0, 360, (1, 1, 1), 0, (0, 1, 1), 1, 1);
	self.PHeliNowActionMe fadeAlphaChange(.2, 1);

	for(;;)
	{
		if(self changeSeatButtonPressed())
		{
			self thread weaponPHeliMe();
			self.PHeliNowWeapMe destroy();
			self.PHeliNowWeapMe = self drawText("^3Armament: ^1" + self.PHeliWeapName, "objective", 2, 0, 330, (1, 1, 1), 0, (1, 0, 1), 1, 1);
			self.PHeliNowWeapMe fadeAlphaChange(.2, 1);
			wait 0.2;
		}
		if(self adsButtonPressed())
		{
			if(self.PHeliWeapType == "cobra_20mm_mp" || self.PHeliWeapType == "helicopter_player_gunner_mp")
			{
				MagicBullet(self.PHeliWeapType, self.PHeli getTagOrigin("tag_origin") + (-100, -100, -200), self traceBulletJet(), self);
				MagicBullet(self.PHeliWeapType, self.PHeli getTagOrigin("tag_origin") + (100, 100, -200), self traceBulletJet(), self);
				wait 0.01;
			}
			else
			{
				MagicBullet(self.PHeliWeapType, self.PHeli getTagOrigin("tag_origin") + (-130, -130, -220), self traceBulletJet(), self);
				wait 0.15;
				MagicBullet(self.PHeliWeapType, self.PHeli getTagOrigin("tag_origin") + (130, 130, -220), self traceBulletJet(), self);
				wait 0.15;
			}
		}
		if(self actionSlotThreeButtonPressed())
		{
			self notify("stop_bombUsingMe");
			self.PHeliBombOn = 0;
			self thread actionPHeliMe();
			self.PHeliNowActionMe destroy();
			self.PHeliNowActionMe = self drawText("^3Action: ^4" + self.PHeliactionName, "objective", 2, 0, 360, (1, 1, 1), 0, (0, 1, 1), 1, 1);
			self.PHeliNowActionMe fadeAlphaChange(.2, 1);
			wait 0.2;
		}
		if(self actionSlotTwoButtonPressed())
		{
			if(self.PHeliactionType == "dropCP")
			{
				self thread initPHeliCPMe();
			}
			else if(self.PHeliactionType == "empBomb")
			{
				self thread initPHeliNukeMe();
			}
			else if(self.PHeliactionType == "bomblet")
			{
				if(self.PHeliBombOn == 0)
				{
					self.PHeliBombOn = 1;
					self thread initPHeliBombMe();
				}
			}
		}
		wait 0.05;
	}
}
initPHeliBombMe()
{
	self endon("disconnect");
	self endon("stop_bombUsingMe");
	for(;;)
	{
		MagicBullet(self.PHeliWeapType, self.PHeli.origin + (0, 0, -220), self.PHeli.origin + (0, 0, -10000), self);
		wait 0.2;
	}
}
initPHeliCPMe()
{
	self endon("disconnect");
	self endon("stop_cpUsingMe");
	for(;;)
	{
		if(self.PHeliDroped == 0)
		{
			self thread maps\mp\killstreaks\_supplydrop::dropcrate(self.PHeli.origin + (0, 0, -20), self.angles, "supplydrop_mp", self, self.team, self.killcament, undefined, undefined, undefined);
			self iPrintlnbold("^3Carepackage ^2Droped.");
			self iPrintln("^3Next you can drop for ^1wait 5 sec.");
			self.PHeliDroped = 1;
		}
		if(self.PHeliDroped == 1)
		{
			wait 5;
			self iPrintln("^5Carepackage Drop ^2charged.");
			self.PHeliDroped = 0;
			self notify("stop_cpUsingMe");
		}
		wait 0.05;
	}
}
initPHeliNukeMe()
{
	self endon("disconnect");
	self endon("stop_nukeUsingMe");

	for(;;)
	{
		if(self.nukeUsed == 0)
		{
			foreach(p in level.players)
			{
				p thread maps\mp\gametypes\_hud_message::hintMessage("^3---^1Nuke Bomblet Warning^3---", 7);
			}

			PHeliNukeMe = spawn("script_model", self.PHeli.origin + (0, 0, -100));
			PHeliNukeMe setModel("projectile_sa6_missile_desert_mp");
			PHeliNukeMe.angles = (90, 90, 90);
			self thread nukeFireEffectMe(PHeliNukeMe);

			PHeliNukeMe moveto(PHeliNukeMe.origin + (0, 0, -750), 9);
			wait 9.1;
			self notify("stop_PHeliNukeMe");
		
			if(GetDvar("mapname") == "mp_nuketown_2020")
			{
				level._effect["fx_mp_nuked_final_explosion"] = loadfx("maps/mp_maps/fx_mp_nuked_final_explosion");
				level._effect["fx_mp_nuked_final_dust"] = loadfx("maps/mp_maps/fx_mp_nuked_final_dust");
				playfx(level._effect["fx_mp_nuked_final_explosion"], PHeliNukeMe.origin);
				playfx(level._effect["fx_mp_nuked_final_dust"], PHeliNukeMe.origin);
			}
			else
			{
				level._effect["emp_flash"] = loadfx("weapon/emp/fx_emp_explosion");
				playfx(level._effect["emp_flash"], PHeliNukeMe.origin);
			}

			foreach(p in level.players)
			{
				p playsound("wpn_emp_bomb");
			}
			earthquake(0.6, 7, PHeliNukeMe.origin, 12345);

			foreach(p in level.players)
			{
				if (level.teamBased && self.pers["team"] == p.pers["team"])
				{

				}
				else
				{
					if (p != self)
						p thread [[level.callbackPlayerDamage]](self, self, 1000, 0, "MOD_MELEE", "remote_missile_missile_mp", (0, 0, 0), (0, 0, 0), "head", 0, 0);
				}
			}

			wait 0.1;
			PHeliNukeMe delete();
			wait 7;
			self iPrintlnbold("^3Next you can use ^5Nuclear Explosion ^3for ^1wait 20 sec.");
			self.PHelinukePrint = 1;
			self.nukeUsed = 1;
		}
		if(self.nukeUsed == 1)
		{
			wait 13;
			self iPrintln("^5Nuclear Explosion ^2charged.");
			self.nukeUsed = 0;
			self notify("stop_nukeUsingMe");
		}
		wait 0.05;
	}
}
nukeFireEffectMe(PHeliNukeMe)
{
	self endon("disconnect");
	self endon("stop_PHeliNukeMe");
	level._effect["torch"] = loadfx( "maps/mp_maps/fx_mp_exp_rc_bomb" );
	for(;;)
	{
		PlayFX(level._effect["torch"], PHeliNukeMe.origin + (0, 0, 120));
		wait 0.1;
	}
}
weaponPHeliMe()
{
	if(self.PHeliWeapon == 0)
	{
		self.PHeliWeapon = 1;
		self.PHeliWeapType = "smaw_mp";
		self.PHeliWeapName = "SMAW";
	}
	else if(self.PHeliWeapon == 1)
	{
		self.PHeliWeapon = 2;
		self.PHeliWeapType = "ai_tank_drone_rocket_mp";
		self.PHeliWeapName = "A.G.R Rocket";
	}
	else if(self.PHeliWeapon == 2)
	{
		self.PHeliWeapon = 3;
		self.PHeliWeapType = "straferun_rockets_mp";
		self.PHeliWeapName = "Warthog Rockets";
	}
	else if(self.PHeliWeapon == 3)
	{
		self.PHeliWeapon = 4;
		self.PHeliWeapType = "remote_missile_bomblet_mp";
		self.PHeliWeapName = "Mortar Missile Burner";
	}
	else if(self.PHeliWeapon == 4)
	{
		self.PHeliWeapon = 5;
		self.PHeliWeapType = "missile_swarm_projectile_mp";
		self.PHeliWeapName = "Swarm";
	}
	else if(self.PHeliWeapon == 5)
	{
		self.PHeliWeapon = 6;
		self.PHeliWeapType = "remote_mortar_missile_mp";
		self.PHeliWeapName = "Loadstar";
	}
	else if(self.PHeliWeapon == 6)
	{
		self.PHeliWeapon = 7;
		self.PHeliWeapType = "remote_missile_missile_mp";
		self.PHeliWeapName = "Remote Mortar Missile";
	}
	else if(self.PHeliWeapon == 7)
	{
		self.PHeliWeapon = 0;
		self.PHeliWeapType = "cobra_20mm_mp";
		self.PHeliWeapName = "Cobra 20mm Bullet";
	}
}
actionPHeliMe()
{
	if(self.PHeliaction == 0)
	{
		self.PHeliaction = 1;
		self.PHeliactionType = "dropCP";
		self.PHeliactionName = "Drop CarePackage";
	}
	else if(self.PHeliaction == 1)
	{
		self.PHeliaction = 2;
		self.PHeliactionType = "empBomb";
		self.PHeliactionName = "Nuclear Explosion";
	}
	else if(self.PHeliaction == 2)
	{
		self.PHeliaction = 0;
		self.PHeliactionType = "bomblet";
		self.PHeliactionName = "Bomblet to Under";
	}
}
stopPilotHeliMe()
{
	self endon("disconnect");
	self endon("stop_stopPHeliMe");

	for(;;)
	{
		if(self stanceButtonPressed())
		{
			self notify("stop_movePHeliMe");
			self notify("stop_attackPHeliMe");
			self notify("stop_exitPHeliMe");
			self notify("stop_bombUsingMe");

			self.PHeliSpeed = 0;
			setDvar("cg_thirdPersonRange", "100");

			self.PHeliNowWeapMe destroy();
			self.PHeliNowActionMe destroy();
			self thread infoPHeliOffMe();
			self unlink();
			self enableWeapons();
			self show();
			self setClientThirdPerson(0);
			self disableInvulnerability();

			self thread ridePilotHeliMe();
			self notify("stop_stopPHeliMe");
		}
		wait 0.05;
	}
}
exitPilotHeliMe()
{
	self endon("disconnect");
	self endon("stop_exitPHeliMe");
	
	for(;;)
	{
		if(self meleeButtonPressed())
		{
			self notify("stop_movePHeliMe");
			self notify("stop_attackPHeliMe");
			self notify("stop_stopPHeliMe");
			self notify("stop_bombUsingMe");
			
			self.PHeliSpeed = 0;
			setDvar("cg_thirdPersonRange", "100");

			self.PHeliNowWeapMe destroy();
			self.PHeliNowActionMe destroy();
			self thread infoPHeliOffMe();
			self unlink();
			self enableWeapons();
			self show();
			self setClientThirdPerson(0);
			self disableInvulnerability();

			self.PHeli delete();
			self.pilotHeliOn = 0;
			self notify("stop_exitPHeliMe");
		}
		wait 0.05;
	}
}

//===< IMS >===

IMSMW3()
{
	self endon("disconnect");
	self endon("noims");
	if(self.imcSpawned == 0)
	{
		self.imcSpawned = 1;
		self iPrintlnbold("^3This Turret's working time to ^1180 sec");
		o = self;
		ims = spawn("script_model", self.origin + (50, 0, 40));
		ims setModel("t6_wpn_turret_sentry_gun_red");
		s = "fhj18_mp";
		self thread imsDelete(ims);
		for(;;)
		{
			foreach(p in level.players)
			{
				d = distance(ims.origin, p.origin);
				if (level.teambased)
				{
					if ((p!=o)&&(p.pers["team"]!= self.pers["team"]))
					if(d < 450)
					if (isAlive(p))
						p thread imsxpl(ims, o, p, s);
				}
				else
				{
					if(p!=o)
					if(d < 450)
					if (isAlive(p))
						p thread imsxpl(ims, o, p, s);
				}
				wait 0.3;
			}
		}
		wait 180;
		self notify("noims");
		self.imcSpawned = 0;
	}
	else
	{
		self iPrintlnbold("^1Turret is still active.");
	}
} 
imsxpl(obj, me, noob, bullet)
{
	me endon("noims");
	while(1)
	{
		MagicBullet(bullet,obj.origin,noob.origin,me);
		wait 2;
			break;
	}
}
imsDelete(ims)
{
	self waittill("noims");
	ims delete();
}

//===< Spawn Bullets >===

initSpawnBullet()
{
	if(self.SpawnBulletOn == 0)
	{
		self.SpawnBulletOn = 1;
		if(self.SBcheck == 0)
		{
			self carepBullets();
		}
		self thread doSpawnBullet();
		self iPrintlnbold("^5Spawn Bullets: ^2On");
	}
	else
	{
		self.SpawnBulletOn = 0;
		self notify("stop_spawnBullet");
		self iPrintlnbold("^5Spawn Bullets: ^1Off");
		self iPrintln("^3Spawn Bullets Type: ^6Nomal");
	}
}
doSpawnBullet()
{
	self endon("disconnect");
	self endon("stop_spawnBullet");
	while(1)
	{
		self waittill ("weapon_fired");
		forward = self getTagOrigin("j_head");
		end = self thread vector_Scal(anglestoforward(self getPlayerAngles()),1000000);
		SPLOSIONlocation = BulletTrace(forward, end, 0, self)["position"];
		M = spawn("script_model",SPLOSIONlocation);
		M setModel(self.spawnBulletType);
	}
}
switchSpawnBType(code, name)
{
	self.spawnBulletType = code;
	self iPrintln("^3Spawn Bullets Type: ^6" + name);
	self.SBcheck = 1;
}
carepBullets()
{
	self switchSpawnBType("t6_wpn_supply_drop_ally", "Frendly Carepackage");
}
redcareBullets()
{
	self switchSpawnBType("t6_wpn_supply_drop_axis", "Enemy Carepackage");
}
detcareBullets()
{
	self switchSpawnBType("t6_wpn_supply_drop_detect", "Detect Carepackage");
}
hqcareBullets()
{
	self switchSpawnBType("t6_wpn_supply_drop_hq", "HQ Carepackage");
}
agrBullets()
{
	self switchSpawnBType("veh_t6_drone_tank", "A.G.R");
}
droneBullets()
{
	self switchSpawnBType("t6_wpn_drop_box", "Drone Package");
}
defacBullets()
{
	self switchSpawnBType("defaultactor", "Debug Model");
}
dogBullets()
{
	self switchSpawnBType("german_shepherd", "Dog");
}
turretBullets()
{
	self switchSpawnBType("t6_wpn_turret_sentry_gun", "Sentry Gun");
}
lbirdBullets()
{
	self switchSpawnBType("veh_t6_drone_overwatch_dark", "Little Bird");
}
sbombBullets()
{
	self switchSpawnBType("veh_t6_drone_pegasus_mp", "Stealth Bomber");
}
vtolBullets()
{
	self switchSpawnBType("veh_t6_air_v78_vtol_killstreak", "VTOL Warship");
}

//===< Spawn Bunker >===

initSpawnBunker()
{
	if(level.BunkerSpwaunOn == 0)
	{    
		level.BunkerSpwaunOn = 1;
		self iPrintlnbold("^5Bunker: ^2Spawned");
		self thread Sneakerbunker();
	}
	else
	{
		self iprintlnbold("^3Bunker is ^1already Spawned");
	}
}
WP(D, Z, P)
{
	L = strTok(D, ",");
	for(i = 0 ; i < L.size; i += 2)
	{
		B = spawn("script_model", self.origin + (int(L[i]), int(L[i+1]), Z));
		if(!P)
			B.angles = (90, 0, 0);
		B setModel("t6_wpn_supply_drop_ally");
	}
}
Sneakerbunker()
{
	WP("0,0,25,0,50,0,75,0,100,0,125,0,150,0,175,0,200,0,225,0,250,0,275,0,0,30,25,30,50,30,75,30,100,30,125,30,150,30,175,30,200,30,225,30,250,30,275,30,0,60,25,60,50,60,75,60,100,60,125,60,150,60,175,60,200,60,225,60,250,60,275,60,0,90,25,90,50,90,75,90,100,90,125,90,150,90,175,90,200,90,225,90,250,90,275,90,0,120,25,120,50,120,75,120,100,120,125,120,150,120,175,120,200,120,225,120,250,120,275,120,0,150,25,150,50,150,75,150,100,150,125,150,150,150,175,150,200,150,225,150,250,150,275,150,0,180,25,180,50,180,75,180,100,180,125,180,150,180,175,180,200,180,225,180,250,180,275,180,0,210,25,210,50,210,75,210,100,210,125,210,150,210,175,210,200,210,225,210,250,210,275,210,0,240,25,240,50,240,75,240,100,240,125,240,150,240,175,240,200,240,225,240,250,240,275,240,0,270,25,270,50,270,75,270,100,270,125,270,150,270,175,270,200,270,225,270,250,270,275,270",0,0);
	WP("0,0,25,0,50,0,75,0,100,0,125,0,150,0,175,0,200,0,225,0,250,0,275,0,0,30,275,30,0,60,275,60,0,90,275,90,0,120,275,120,0,150,275,150,0,180,275,180,0,210,275,210,0,240,275,240,0,270,25,270,50,270,75,270,200,270,225,270,250,270,275,270",23,0);
	WP("0,0,25,0,50,0,75,0,100,0,125,0,150,0,175,0,200,0,225,0,250,0,275,0,0,30,275,30,0,60,275,60,0,90,275,90,0,120,275,120,0,150,275,150,0,180,275,180,0,210,275,210,0,240,275,240,0,270,25,270,50,270,75,270,200,270,225,270,250,270,275,270",56,0);
	WP("0,0,25,0,50,0,75,0,200,0,225,0,250,0,275,0,0,30,275,30,0,60,275,60,0,210,275,210,0,240,275,240,0,270,25,270,50,270,75,270,100,270,125,270,150,270,175,270,200,270,225,270,250,270,275,270",90,0);
	WP("0,0,25,0,50,0,75,0,100,0,125,0,150,0,175,0,200,0,225,0,250,0,275,0,0,30,275,30,0,60,275,60,0,90,275,90,0,120,275,120,0,150,275,150,0,180,275,180,0,210,275,210,0,240,275,240,0,270,25,270,50,270,75,270,100,270,125,270,150,270,175,270,200,270,225,270,250,270,275,270",120,0);
	WP("0,0,25,0,50,0,75,0,100,0,125,0,150,0,175,0,200,0,225,0,250,0,275,0,0,30,25,30,50,30,75,30,100,30,125,30,150,30,175,30,200,30,225,30,250,30,275,30,0,60,25,60,50,60,75,60,100,60,125,60,150,60,175,60,200,60,225,60,250,60,275,60,0,90,25,90,50,90,75,90,100,90,125,90,150,90,175,90,200,90,225,90,250,90,275,90,0,120,25,120,50,120,75,120,100,120,125,120,150,120,175,120,200,120,225,120,250,120,275,120,0,150,25,150,50,150,75,150,100,150,125,150,150,150,175,150,200,150,225,150,250,150,275,150,0,180,25,180,50,180,75,180,100,180,125,180,150,180,175,180,200,180,225,180,250,180,275,180,0,210,25,210,50,210,75,210,100,210,125,210,150,210,175,210,200,210,225,210,250,210,275,210,0,240,25,240,50,240,75,240,100,240,125,240,150,240,175,240,200,240,225,240,250,240,275,240,0,270,25,270,50,270,75,270,100,270,125,270,150,270,175,270,200,270,225,270,250,270,275,270",147,0);
}

//===< Sky Plaza >===

initSkyPlaza()
{
	if(level.skyPOn == 0)
	{
		level.skyPOn = 1;
		self thread doSkyPlaza();
		self iPrintlnbold("^5Sky Plaza ^2Spawned");
	}
	else
	{
		self iPrintlnbold("^5Sky Plaza ^1already Spawned");
	}
}
doSkyPlaza()
{
		WP("0,0,55,0,110,0,0,30,110,30,55,60,0,90,110,90,55,120,0,150,110,150,55,180,0,210,110,210,55,240,0,270,110,270,55,300,0,330,110,330,55,360,0,390,110,390,55,420,0,450,110,450,55,480,0,510,110,510,55,540,0,570,110,570,55,600,0,630,110,630,55,660,0,690,110,690,55,720,1155,720,1210,720,1265,720,1320,720,1375,720,0,750,110,750,1155,750,1210,750,1265,750,1320,750,1375,750,55,780,1100,780,1155,780,1210,780,1265,780,1320,780,1375,780,0,810,110,810,1100,810,1155,810,1210,810,1265,810,1320,810,1375,810,55,840,1100,840,1155,840,1210,840,1265,840,1320,840,1375,840,0,870,110,870,1100,870,1155,870,1210,870,1265,870,1320,870,1375,870,55,900,0,930,110,930,55,960,0,990,110,990,55,1020,0,1050,110,1050,55,1080,0,1110,110,1110,55,1140,0,1170,110,1170,165,1170,55,1200,165,1200,0,1230,110,1230,55,1260,0,1290,110,1290,55,1320,0,1350,110,1350,55,1380,0,1410,110,1410,0,1440,55,1440,110,1440,0,1470,55,1470,110,1470",0,1);
		WP("0,0,55,0,110,0,1155,720,1210,720,1265,720,1320,720,1375,720,1155,750,1375,750,1100,780,1155,780,1375,780,1100,810,1375,810,1100,840,1375,840,1100,870,1155,870,1210,870,1265,870,1320,870,1375,870,110,1050,110,1080,0,1470,55,1470,110,1470",25,1);
		WP("0,0,55,0,110,0,1155,720,1210,720,1265,720,1320,720,1375,720,1155,750,1375,750,1100,780,1155,780,1375,780,1100,810,1375,810,1100,840,1375,840,1100,870,1155,870,1210,870,1265,870,1320,870,1375,870,110,900,110,930,0,1470,55,1470,110,1470",50,1);
		WP("0,0,55,0,110,0,1155,720,1210,720,1265,720,1320,720,1375,720,1155,750,1375,750,110,780,1100,780,1155,780,1375,780,110,810,1100,810,1375,810,1100,840,1375,840,1100,870,1155,870,1210,870,1265,870,1320,870,1375,870,0,1470,55,1470,110,1470",75,1);
		WP("0,0,55,0,110,0,110,690,110,720,1155,720,1210,720,1265,720,1320,720,1375,720,1155,750,1375,750,1100,780,1155,780,1375,780,1100,810,1375,810,1100,840,1375,840,1100,870,1155,870,1210,870,1265,870,1320,870,1375,870,0,1470,55,1470,110,1470",100,1);
		WP("0,0,55,0,110,0,110,600,110,630,110,660,1155,720,1210,720,1265,720,1320,720,1375,720,1155,750,1375,750,1100,780,1155,780,1375,780,1100,810,1375,810,1100,840,1375,840,1100,870,1155,870,1210,870,1265,870,1320,870,1375,870,0,1470,55,1470,110,1470",125,1);
		WP("0,0,55,0,110,0,0,30,55,30,110,30,165,30,220,30,0,60,55,60,110,60,220,60,275,60,330,60,0,90,55,90,110,90,330,90,55,120,330,120,55,150,330,150,55,180,330,180,55,210,330,210,330,240,385,240,440,240,495,240,550,240,550,270,605,270,330,300,605,300,605,330,605,360,330,390,605,390,605,420,660,420,715,420,770,420,770,450,825,450,880,450,935,450,330,480,935,480,880,510,935,510,880,540,935,540,990,540,1045,540,1100,540,1155,540,165,570,220,570,275,570,330,570,495,570,1155,570,1210,570,330,600,495,600,1210,600,330,630,495,630,1210,630,165,660,220,660,275,660,330,660,385,660,440,660,495,660,1210,660,165,690,330,690,1210,690,165,720,330,720,1100,720,1155,720,1210,720,1265,720,1320,720,1375,720,165,750,330,750,385,750,440,750,495,750,1100,750,1155,750,1375,750,935,780,990,780,1045,780,1100,780,1155,780,1375,780,935,810,1100,810,1375,810,935,840,1100,840,1375,840,935,870,1100,870,1155,870,1210,870,1265,870,1320,870,1375,870,935,900,935,930,825,960,880,960,935,960,825,990,825,1020,825,1050,825,1080,825,1110,770,1140,825,1140,770,1170,770,1200,770,1230,770,1260,770,1290,770,1320,55,1350,110,1350,165,1350,220,1350,275,1350,330,1350,385,1350,440,1350,495,1350,550,1350,605,1350,660,1350,715,1350,770,1350,55,1380,0,1410,55,1410,110,1410,0,1440,55,1440,110,1440,0,1470,55,1470,110,1470",150,1);
}

//===< Prison Break >===

initPrison()
{
	if(level.PrisonBreak == 0)
	{
		level.PrisonBreak = 1;
		self iPrintlnbold("^5Prison Break: ^2Spawned");
		self thread PrisonBreak();
	}
	else
	{
		self iprintln("^3Prison Break ^1already spawned");
	}
}
PrisonBreak()
{
	WP("0,0,25,0,50,0,75,0,100,0,125,0,150,0,175,0,200 ,0,225,0,250,0,275,0,300,0,325,0,350,0,375,0,400,0 ,425,0,450,0,475,0,500,0,525,0,550,0,575,0,0,30,25 ,30,50,30,75,30,100,30,125,30,150,30,175,30,200,30 ,225,30,250,30,275,30,300,30,325,30,350,30,375,30, 400,30,425,30,450,30,475,30,500,30,525,30,550,30,5 75,30,0,60,25,60,50,60,75,60,100,60,125,60,150,60, 175,60,200,60,225,60,250,60,275,60,300,60,325,60,3 50,60,375,60,400,60,425,60,450,60,475,60,500,60,52 5,60,550,60,575,60,0,90,25,90,50,90,75,90,100,90,1 25,90,150,90,175,90,200,90,225,90,250,90,275,90,30 0,90,325,90,350,90,375,90,400,90,425,90,450,90,475 ,90,500,90,525,90,550,90,575,90,0,120,25,120,50,12 0,75,120,100,120,125,120,150,120,175,120,200,120,2 25,120,250,120,275,120,300,120,325,120,350,120,375 ,120,400,120,425,120,450,120,475,120,500,120,525,1 20,550,120,575,120,0,150,25,150,50,150,75,150,100, 150,125,150,150,150,175,150,200,150,225,150,250,15 0,275,150,300,150,325,150,350,150,375,150,400,150, 425,150,450,150,475,150,500,150,525,150,550,150,57 5,150,0,180,25,180,50,180,75,180,100,180,125,180,1 50,180,175,180,200,180,225,180,250,180,275,180,300 ,180,325,180,350,180,375,180,400,180,425,180,450,1 80,475,180,500,180,525,180,550,180,575,180,0,210,2 5,210,50,210,75,210,100,210,125,210,150,210,175,21 0,200,210,225,210,250,210,275,210,300,210,325,210, 350,210,375,210,400,210,425,210,450,210,475,210,50 0,210,525,210,550,210,575,210,0,240,25,240,50,240, 75,240,100,240,125,240,150,240,175,240,200,240,225 ,240,250,240,275,240,300,240,325,240,350,240,375,2 40,400,240,425,240,450,240,475,240,500,240,525,240 ,550,240,575,240,0,270,25,270,50,270,75,270,100,27 0,125,270,150,270,175,270,200,270,225,270,250,270, 275,270,300,270,325,270,350,270,375,270,400,270,42 5,270,450,270,475,270,500,270,525,270,550,270,575, 270",0,0);
	WP("0,0,25,0,50,0,75,0,100,0,125,0,150,0,175,0,200 ,0,225,0,250,0,275,0,300,0,325,0,350,0,375,0,400,0 ,425,0,450,0,475,0,500,0,525,0,550,0,575,0,0,30,57 5,30,0,60,575,60,0,90,575,90,0,120,575,120,0,150,5 75,150,0,180,575,180,0,210,575,210,0,240,575,240,0 ,270,25,270,50,270,75,270,100,270,125,270,150,270, 175,270,200,270,225,270,250,270,275,270,300,270,32 5,270,350,270,375,270,400,270,425,270,450,270,475, 270,500,270,525,270,550,270,575,270",40,0);
	WP("0,0,25,0,50,0,75,0,100,0,125,0,150,0,175,0,200 ,0,225,0,250,0,275,0,300,0,325,0,350,0,375,0,400,0 ,425,0,450,0,475,0,500,0,525,0,550,0,575,0,0,30,57 5,30,0,60,575,60,0,90,575,90,0,120,575,120,0,150,5 75,150,0,180,575,180,0,210,575,210,0,240,575,240,0 ,270,25,270,50,270,75,270,100,270,125,270,150,270, 175,270,200,270,225,270,250,270,275,270,300,270,32 5,270,350,270,375,270,400,270,425,270,450,270,475, 270,500,270,525,270,550,270,575,270",80,0);
	WP("0,0,25,0,50,0,75,0,100,0,125,0,150,0,175,0,200 ,0,225,0,250,0,275,0,300,0,325,0,350,0,375,0,400,0 ,425,0,450,0,475,0,500,0,525,0,550,0,575,0,0,30,57 5,30,0,60,575,60,0,90,575,90,0,120,575,120,0,150,5 75,150,0,180,575,180,0,210,575,210,0,240,575,240,0 ,270,25,270,50,270,75,270,100,270,125,270,150,270, 175,270,200,270,225,270,250,270,275,270,300,270,32 5,270,350,270,375,270,400,270,425,270,450,270,475, 270,500,270,525,270,550,270,575,270",120,0);
}

//===< Escalator >===

Escalatore()
{
	if(self.DoEscalator == 0)
	{
		self.DoEscalator = 1;
		self iPrintlnbold("^5Pwnd DoEscalator: ^2Spawned");
		self thread DoEscalator();
	}
	else
	{
		self iPrintlnbold("^3Pwnd DoEscalator ^1already Spawned");
	}
}
DoEscalator()
{
	WP("0,0,0,30,0,60,0,90,0,120,0,150,0,180,0,210,0,2 40,0,270",0,0);
	WP("25,0,25,30,25,60,25,90,25,120,25,150,25,180,25 ,210,25,240,25,270",40,0);
	WP("50,0,50,30,50,60,50,90,50,120,50,150,50,180,50 ,210,50,240,50,270",80,0);
	WP("75,0,75,30,75,60,75,90,75,120,75,150,75,180,75 ,210,75,240,75,270",120,0);
	WP("100,0,100,30,100,60,100,90,100,120,100,150,100 ,180,100,210,100,240,100,270",160,0);
}

//-----[ Forge Menu ]-----


//===< Spawn Warpzone >===

initTeletoFlag()
{
	self endon("disconnect");
	self endon("stop_TeletoFlag");

	for(;;)
	{
		self.TtF["setOrigin"] = self.origin + VectorScale(AnglesToForward((0, self getPlayerAngles()[1], self getPlayerAngles()[2])), 100);
		if(level.setTele1Ori == 0)
		{
			level.setTele1Ori = 1;
			self iPrintlnbold("^3Please set ^61st Teleport Start Flag.");
			self iPrintln("^3Press [{+actionslot 3}] to ^6Set.");
			wait 0.5;
		}
		if(level.setTele1Ori == 1)
		{
			if(self actionSlotThreeButtonPressed())
			{
				level.setTele1Ori = 2;
				level.TtF = spawn("script_model", self.TtF["setOrigin"]);
				level.TtF.angles = (0,10,0);
				level.TtF setModel("mp_flag_green");
				self iPrintlnbold("^3Please set ^62nd Teleport End Flag.");
				self iPrintln("^3Press [{+actionslot 4}] to ^6Set.");
				wait 0.5;
			}
		}
		if(level.setTele1Ori == 2)
		{
			if(self actionSlotFourButtonPressed())
			{
				level.setTele1Ori = 3;
				level.TtF2 = spawn("script_model", self.TtF["setOrigin"]);
				level.TtF2.angles = (0,10,0);
				level.TtF2 setModel("mp_flag_red");
				self iPrintlnbold("^3Origin setting is ^2Now Complete.");
				self iPrintln("^3Start ^2Warpzone^3...");
				wait 0.5;
				level thread ttfConnect();
				foreach(p in level.players)
				{
					p thread doTeletoFlag();
				}
				self notify("stop_TeletoFlag");
			}
		}
		if(level.setTele1Ori == 3)
		{
			level.setTele1Ori = 0;
			foreach(p in level.players)
			{
				p notify("stop_warpzone");
			}
			level.TtF delete();
			level.TtF2 delete();
			self iPrintlnbold("^3Flag Object ^1deleted.");
			self iPrintln("^3Warpzone setting is ^2Restart.");
			wait 0.5;
		}
		wait 0.05;
	}
}
doTeletoFlag()
{
	self endon("disconnect");
	self endon("stop_warpzone");

	for(;;)
	{
		self.TtFGInfoOn destroy();
		self.TtFRInfoOn destroy();

		if(distance(self.origin, level.TtF.origin) < 95)
		{
			self.TtFGInfoOn = self createFontString("hudbig", 2.2);
			self.TtFGInfoOn setPoint("TOP", "TOP", 0, 50);
			self.TtFGInfoOn setText("^3Press [{+usereload}] to Teleport to ^1Red Flag");
			if(self useButtonPressed())
			{
				self setorigin(level.TtF2.origin);
				wait 1;
			}
		}

		if(distance(self.origin, level.TtF2.origin) < 95)
		{
			self.TtFRInfoOn = self createFontString("hudbig", 2.2);
			self.TtFRInfoOn setPoint("TOP", "TOP", 0, 50);
			self.TtFRInfoOn setText("^3Press [{+usereload}] to Teleport to ^2Green Flag");
			if(self useButtonPressed())
			{
				self setorigin(level.TtF.origin);
				wait 1;
			}
		}
		wait 0.05;
	}
}
ttfConnect()
{
	level endon("disconnect");
	level endon("stop_warpzone");
	for(;;)
	{
		level waittill("connecting", p);
		p thread ttfspawned();
	}
}
ttfspawned()
{
	self waittill("spawned_player");
	self thread doTeletoFlag();
}

xxroundUp(floatVal)
{
	if(int(floatVal)!= floatVal)return int(floatVal+1);
	else return int(floatVal);
}
ForgeRamp()
{
	self endon("disconnect");
	self endon("stop_ramp");
	for(;;)
	{
		if(self.RampStart == 0)
		{
			self.RampStart = 1;
			self iPrintlnbold("^3Please set ^6Start Ramp Origin.");
			self iPrintln("^3Press [{+actionslot 3}] to ^6Set.");
			wait 0.5;
		}
		if(self.RampStart == 1)
		{
			if(self actionSlotThreeButtonPressed())
			{
				self.RampStart = 2;
				pos1 = self.origin;
				self iPrintln("^3Position ^2Marked.");
				wait 1;
				self iPrintlnbold("^3Please set ^6End Ramp Origin.");
				self iPrintln("^3Press [{+actionslot 4}] to ^6Set.");
				wait 0.5;
			}
		}
		if(self.RampStart == 2)
		{
			if(self actionSlotFourButtonPressed())
			{
				self.RampStart = 0;
				pos2 = self.origin;
				self iPrintln("^3Position ^2Marked.");
				wait 1;
				self iPrintlnbold("^3Creating ^2Ramp...");
				wait 0.5;
				level thread CreateRamp(pos1,pos2);
				self notify("stop_ramp");
			}
		}
		wait 0.05;
	}
}
CreateRamp(top,bottom)
{
	D=Distance(top,bottom);
	blocks=xxroundUp(D / 30);
	CX=top[0] - bottom[0];
	CY=top[1] - bottom[1];
	CZ=top[2] - bottom[2];
	XA=CX / blocks;
	YA=CY / blocks;
	ZA=CZ / blocks;
	CXY=Distance((top[0],top[1],0),(bottom[0],bottom[1],0));
	Temp=VectorToAngles(top - bottom);
	BA =(Temp[2],Temp[1] + 90,Temp[0]);
	for(b=0;b < blocks;b++)
	{
		block=spawn("script_model",(bottom +((XA,YA,ZA)* B)));
		block setModel("t6_wpn_supply_drop_ally");
		block.angles=BA;
		blockb=spawn("trigger_radius",(0,0,0),0,65,30);
		blockb.origin=block.origin+(0,0,5);
		blockb.angles=BA;
		blockb setContents(1);
		wait 0.01;
	}
	block=spawn("script_model",(bottom +((XA,YA,ZA)* blocks)-(0,0,5)));
	block setModel("t6_wpn_supply_drop_ally");
	block.angles =(BA[0],BA[1],0);
	blockb=spawn("trigger_radius",(0,0,0),0,65,30);
	blockb.origin=block.origin+(0,0,5);
	blockb.angles =(BA[0],BA[1],0);
	blockb setContents(1);
	wait 0.01;
}

ForgeWall()
{
	self endon("disconnect");
	self endon("stop_wall");
	for(;;)
	{
		if(self.WallStart == 0)
		{
			self.WallStart = 1;
			self iPrintlnbold("^3Please set ^6Start Wall Origin.");
			self iPrintln("^3Press [{+actionslot 3}] to ^6Set.");
			wait 0.5;
		}
		if(self.WallStart == 1)
		{
			if(self actionSlotThreeButtonPressed())
			{
				self.WallStart = 2;
				pos1 = self.origin;
				self iPrintln("^3Position ^2Marked.");
				wait 1;
				self iPrintlnbold("^3Please set ^6End Wall Origin.");
				self iPrintln("^3Press [{+actionslot 4}] to ^6Set.");
				wait 0.5;
			}
		}
		if(self.WallStart == 2)
		{
			if(self actionSlotFourButtonPressed())
			{
				self.WallStart = 0;
				pos2 = self.origin;
				self iPrintln("^3Position ^2Marked.");
				wait 1;
				self iPrintlnbold("^3Creating ^2Wall...");
				wait 0.5;
				level thread CreateWall(pos1,pos2);
				self notify("stop_wall");
			}
		}
		wait 0.05;
	}
}
CreateWall(top,bottom)
{
    blockb=[];
	blockc=[];
	D=Distance((top[0],top[1],0),(bottom[0],bottom[1],0));
	H=Distance((0,0,top[2]),(0,0,bottom[2]));
	blocks=xxroundUp(D / 40);
	height=xxroundUp(H / 40);
	CX=bottom[0] - top[0];
	CY=bottom[1] - top[1];
	CZ=bottom[2] - top[2];
	XA=CX / blocks;
	YA=CY / blocks;
	ZA=CZ / height;
	TXA=(XA / 4);
	TYA=(YA / 4);
	Temp=VectorToAngles(bottom - top);
	BA =(0,Temp[1],90);
	for(h=0;h < height;h++)
	{
		fstpos=(top+(TXA,TYA,10)+((0,0,ZA)* h));
		block=spawn("script_model",fstpos);
		block setModel("t6_wpn_supply_drop_ally");
		block.angles=BA;
		blockb[h]=spawn("trigger_radius",(0,0,0),0,75,40);
		blockb[h].origin=fstpos;
		blockb[h].angles=BA;
		blockb[h] setContents(1);
		wait 0.001;
		for(i=0;i < blocks;i++)
		{
			secpos=(top +((XA,YA,0)* i)+(0,0,10)+((0,0,ZA)* h));
			block=spawn("script_model",secpos);
			block setModel("t6_wpn_supply_drop_ally");
			block.angles =BA;
			blockc[i]=spawn("trigger_radius",(0,0,0),0,75,40);
			blockc[i].origin=secpos;
			blockc[i].angles=BA;
			blockc[i] setContents(1);
			wait 0.001;
		}
	}
}

ForgeGrids()
{
	self endon("disconnect");
	self endon("stop_floor");
	for(;;)
	{
		if(self.FloorStart == 0)
		{
			self.FloorStart = 1;
			self iPrintlnbold("^3Please set ^6Start Floor Origin.");
			self iPrintln("^3Press [{+actionslot 3}] to ^6Set.");
			wait 0.5;
		}
		if(self.FloorStart == 1)
		{
			if(self actionSlotThreeButtonPressed())
			{
				self.FloorStart = 2;
				pos1 = self.origin;
				self iPrintln("^3Position ^2Marked.");
				wait 1;
				self iPrintlnbold("^3Please set ^6End Floor Origin.");
				self iPrintln("^3Press [{+actionslot 4}] to ^6Set.");
				wait 0.5;
			}
		}
		if(self.FloorStart == 2)
		{
			if(self actionSlotFourButtonPressed())
			{
				self.FloorStart = 0;
				pos2 = self.origin;
				self iPrintln("^3Position ^2Marked.");
				wait 1;
				self iPrintlnbold("^3Creating ^2Floor...");
				wait 0.5;
				level thread CreateGrids(pos1,pos2);
				self notify("stop_floor");
			}
		}
		wait 0.05;
	}
}
CreateGrids(corner1,corner2,angle)
{
	blockfloor=[];
	W=Distance((corner1[0],0,0),(corner2[0],0,0));
	L=Distance((0,corner1[1],0),(0,corner2[1],0));
	H=Distance((0,0,corner1[2]),(0,0,corner2[2]));
	CX=corner2[0] - corner1[0];
	CY=corner2[1] - corner1[1];
	CZ=corner2[2] - corner1[2];
	ROWS=xxroundUp(W / 40);
	COLUMNS=xxroundUp(L / 55);
	HEIGHT=xxroundUp(H / 20);
	XA=CX / ROWS;
	YA=CY / COLUMNS;
	ZA=CZ / HEIGHT;
	center=spawn("script_model",corner1);
	for(r=0;r<=ROWS;r++)
	{
		for(c=0;c<=COLUMNS;c++)
		{
			for(h=0;h<=HEIGHT;h++)
			{
				floor=(corner1 +(XA * r, YA * c, ZA * h));
				block=spawn("script_model",floor);
				block setModel("t6_wpn_supply_drop_ally");
				block.angles =(0,0,0);
				block LinkTo(center);
	            blockfloor[h]=spawn("trigger_radius",(0,0,0),0,65,30);
	            blockfloor[h].origin=floor;
	            blockfloor[h].angles=(0,90,0);
	            blockfloor[h] setContents(1);
			}
		}
	}
	center.angles=angle;
}

//-----[ Players Menu ]-----

doTeleportToMe()
{
    player = level.players[self.Menu.System["ClientIndex"]];
    if (player ishost())
    {
        self iprintln("You can't teleport the Host!");
    }
    else
    {
        player setorigin(self.origin);
        player iprintln("Teleported to ^1" + player.name);
    }
    self iPrintln("^1" + player.name + " ^7Teleported to Me");
}
doTeleportToHim()
{
    player = level.players[self.Menu.System["ClientIndex"]];
    if (player ishost())
    {
        self iprintln("You can't teleport to the host!");
    }
    else
    {
        self setorigin(player.origin);
        self iprintln("Teleported to ^1" + player.name);
    }
    player iPrintln("^1" + self.name + " ^7Teleported to Me");
}
doKickPlayer()
{
	player = level.players[self.Menu.System["ClientIndex"]];
	if (player ishost())
	{
		self iPrintln("^1Good bye ^4:D");
		kick(self getentitynumber());
	}
	else
	{
		self iPrintln("^1 " + player.name + " ^7Has Been ^1Kicked ^7!");
		kick(player getentitynumber());
	}
}

//===< Basic Cheats >===

playerGod()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.God == 0)
		{
			self iPrintln("^3" + p.name + " ^5God Mode: ^2On");
			p giveGod();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5God Mode: ^1Off");
			p giveGod();
		}
	}
}
playerInfa()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.UAOn == 0)
		{
			self iPrintln("^3" + p.name + " ^5Infinity Ammo: ^2On");
			p doInfAmmo();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Infinity Ammo: ^1Off");
			p doInfAmmo();
		}
	}
}
playerHide()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.Invisible == 0)
		{
			self iPrintln("^3" + p.name + " ^5Invisible: ^2On");
			p InvisibleOn();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Invisible: ^1Off");
			p InvisibleOn();
		}
	}
}
playerSpeed()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.clientsspeed == 0)
		{
			self iPrintln("^3" + p.name + " ^3Walk Speed: ^6x2");
			p doClientsSpeed();
		}
		else if(p.clientsspeed == 1)
		{
			self iPrintln("^3" + p.name + " ^3Walk Speed: ^6x3");
			p doClientsSpeed();
		}
		else if(p.clientsspeed == 2)
		{
			self iPrintln("^3" + p.name + " ^3Walk Speed: ^6x4");
			p doClientsSpeed();
		}
		else if(p.clientsspeed == 3)
		{
			self iPrintln("^3" + p.name + " ^3Walk Speed: ^6x5");
			p doClientsSpeed();
		}
		else if(p.clientsspeed == 4)
		{
			self iPrintln("^3" + p.name + " ^3Walk Speed: ^6x1");
			p doClientsSpeed();
		}
	}
}
playerPerk()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
			self iPrintln("^3" + p.name + " ^3Set ^6All Perks");
			p givespPerk();
			p iPrintlnbold("^3Set ^6All Perks");
	}
}
playerDeath()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
			self iPrintln("^3" + p.name + " ^1Died");
			p doSuicide();
	}
}
playerUAV()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.uav == 0)
		{
			self iPrintln("^3" + p.name + " ^5Always UAV: ^2On");
			p doUAV();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Always UAV: ^1Off");
			p doUAV();
		}
	}
}
playerDMachi()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
			self iPrintln("^3" + p.name + " ^3Give ^6Death Machine");
			p giveWdmachine();
	}
}
playerRWeap()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
			self iPrintln("^3" + p.name + " ^3Give ^6Random Weapons");
			p giveRWeapon();
	}
}
playerNoclip()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.NoclipOn == 0)
		{
			self iPrintln("^3" + p.name + " ^5Advanced No Clip: ^2On");
			p doNoClip();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Advanced No Clip: ^1Off");
			p doNoClip();
		}
	}
}
playerExBul()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.ExpBult == 0)
		{
			self iPrintln("^3" + p.name + " ^5Explosive Bullets: ^2On");
			p ExpBultOn();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Explosive Bullets: ^1Off");
			p ExpBultOn();
		}
	}
}

playerMGB()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.mBulletOn == 0)
		{
			self iPrintln("^3" + p.name + " ^5Modded Bullets: ^2On");
			p initMagicBullet();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Modded Bullets: ^1Off");
			p initMagicBullet();
		}
	}
}

playerTChange()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.TeamPattern == 0)
		{
			self iPrintln("^3" + p.name + " ^5Team changed to ^2axis");
			p initTeamChange();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Team changed to ^2allies");
			p initTeamChange();
		}
	}
}

playerMJump()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.MultiJump == 0)
		{
			self iPrintln("^3" + p.name + " ^5Mulit Jump: ^2On");
			p Toggle_Multijump();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Mulit Jump: ^1Off");
			p Toggle_Multijump();
		}
	}
}

playerNinja()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.ninjaon == 0)
		{
			self iPrintln("^3" + p.name + " ^5Ninja Mode: ^2On");
			p doNinja();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Ninja Mode: ^1Off");
			p doNinja();
		}
	}
}

playerSmokeM()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.smokemonsterr == 0)
		{
			self iPrintln("^3" + p.name + " ^5Smoke Monster: ^2On");
			p initSmokeMonster();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Smoke Monster: ^1Off");
			p initSmokeMonster();
		}
	}
}

playerForge()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.forgeOn == 0)
		{
			self iPrintln("^3" + p.name + " ^5Forge Mode: ^2On");
			p ForgeON();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Forge Mode: ^1Off");
			p ForgeON();
		}
	}
}

playerAdvFor()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		if(p.advForge == 0)
		{
			self iPrintln("^3" + p.name + " ^5Advanced Forge Mode: ^2On");
			p ForgeMode();
		}
		else
		{
			self iPrintln("^3" + p.name + " ^5Advanced Forge Mode: ^1Off");
			p ForgeMode();
		}
	}
}

playerDCar()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		self iPrintln("^3" + p.name + " ^3Give ^6Drivable Car");
		p spawnDrivableCar();
	}
}
playerJet()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		self iPrintln("^3" + p.name + " ^3Give ^6Flyable Jet");
		p setFJetMcuav();
		p initFlyableJetMe();
	}
}
playerHeli()
{
	p = level.players[self.Menu.System["ClientIndex"]];
	if (p isHost())
	{
		self iPrintln("^1Cannot using for Host!");
	}
	else
	{
		self iPrintln("^3" + p.name + " ^3Give ^6Pilot Aircraft");
		p initPilotHeliMe();
	}
}

//-----[ All Players Menu ]-----

doGodAllPlayer()
{
	if(level.apGod == 0)
	{
		level.apGod = 1;
		self iPrintlnbold("^3All Players ^5God Mode: ^2On");
		foreach(p in level.players)
		{
			if(!p isHost())
			{
				p thread giveGod();
			}
			p thread callOnText(self.apGodWordOn, "^3All Players ^5God Mode", "", (1, 1, 1), (1, 0, 1));
		}
	}
	else if(level.apGod == 1)
	{
		level.apGod = 0;
		self iPrintlnbold("^3All Players ^5God Mode: ^1Off");
		foreach(p in level.players)
		{
			if(!p isHost())
			{
				p thread giveGod();
			}
			p thread callOffText(self.apGodWordOff, "^3All Players ^5God Mode", "", (1, 1, 1), (1, 0, 1));
		}
	}
}
doNocAllPlayer()
{
	if(level.apNoc == 0)
	{
		level.apNoc = 1;
		self iPrintlnbold("^3All Player ^5Noclip: ^2On");
		foreach(p in level.players)
		{
			p thread callOnText(self.apNocOnWord, "^3All Player ^5Noclip", "", (1, 1, 1), (1, 0, 1));
			if(!(p isHost()))
			{
				p thread doNoClip();
			}
		}
	}
	else
	{
		level.apNoc = 0;
		self iPrintlnbold("^3All Player ^5Noclip: ^1Off");
		foreach(p in level.players)
		{
			p thread callOffText(self.apNocOffWord, "^3All Player ^5Noclip", "", (1, 1, 1), (1, 0, 1));
			if(!(p isHost()))
			{
				p thread doNoClip();
			}
		}
	}
}
doInfAmmAllPlayer()
{
	if(level.apInAm == 0)
	{
		level.apInAm = 1;
		self iPrintlnbold("^3All Player ^5Infinity Ammo: ^2On");
		foreach(p in level.players)
		{
			p thread callOnText(self.apInAmOn2, "^3All Player ^5Infinity Ammo", "", (1, 1, 1), (1, 0, 1));
			if(!(p isHost()))
			{
				p thread doInfAmmo();
			}
		}
	}
	else
	{
		level.apInAm = 0;
		self iPrintlnbold("^3All Player ^5Infinity Ammo: ^1Off");
		foreach(p in level.players)
		{
			p thread callOffText(self.apInAmOff2, "^3All Player ^5Infinity Ammo", "", (1, 1, 1), (1, 0, 1));
			if(!(p isHost()))
			{
				p thread doInfAmmo();
			}
		}
	}
}
doExpBulAllPlayer()
{
	if(level.apExpB == 0)
	{
		level.apExpB = 1;
		self iPrintlnbold("^3All Player ^5Infinity Ammo: ^2On");
		foreach(p in level.players)
		{
			p thread callOnText(self.apExpBOn2, "^3All Player ^5Explosive Bullets", "", (1, 1, 1), (1, 0, 1));
			if(!(p isHost()))
			{
				p thread ExpBultOn();
			}
		}
	}
	else
	{
		level.apExpB = 0;
		self iPrintlnbold("^3All Player ^5Explosive Bullets: ^1Off");
		foreach(p in level.players)
		{
			p thread callOffText(self.apExpBOff2, "^3All Player ^5Explosive Bullets", "", (1, 1, 1), (1, 0, 1));
			if(!(p isHost()))
			{
				p thread ExpBultOn();
			}
		}
	}
}
APadvForge()
{
	if(level.apForge == 0)
	{
		level.apForge = 1;
		self iPrintlnbold("^3All Player ^5Advanced Forge Mode: ^2On");
		foreach(p in level.players)
		{
			p thread callOnText(self.apForgeOn2, "^3All Player ^5Advanced Forge Mode", "", (1, 1, 1), (1, 0, 1));
			if(!(p isHost()))
			{
				p thread ForgeMode();
			}
		}
	}
	else
	{
		level.apForge = 0;
		self iPrintlnbold("^3All Player ^5Advanced Forge Mode: ^1Off");
		foreach(p in level.players)
		{
			p thread callOffText(self.apForgeOff2, "^3All Player ^5Advanced Forge Mode", "", (1, 1, 1), (1, 0, 1));
			if(!(p isHost()))
			{
				p thread ForgeMode();
			}
		}
	}
}
doFreezeAllPlayer()
{
	if(level.AllPfreeze == 0)
	{
		level.AllPfreeze = 1;
		self iPrintlnbold("^3All Player ^5Freeze: ^2On");
		foreach(p in level.players)
		{
			p thread callOnText(self.apFreezeOn2, "^3All Player ^5Freeze", "", (1, 1, 1), (1, 0, 1));
			if(!(p isHost()))
			{
				p thread freezePlayer();
			}
		}
	}
	else
	{
		level.AllPfreeze = 0;
		self iPrintlnbold("^3All Player ^5Freeze: ^1Off");
		foreach(p in level.players)
		{
			p thread callOffText(self.apFreezeOff2, "^3All Player ^5Freeze", "", (1, 1, 1), (1, 0, 1));
			if(!(p isHost()))
			{
				p notify("stop_FreezeAllP");
				p freezecontrols(0);
			}
		}
	}
}
freezePlayer()
{
	self endon("disconnect");
	self endon("stop_FreezeAllP");
	for(;;)
	{
		self freezecontrols(1);
		wait 0.1;
	}
}

allPlayerGive(print, callon)
{
	self iPrintlnbold(print);
	foreach(p in level.players)
	{
		p callInfoText(callon, print, "", (1, 1, 1), (1, 0, 1));
	}
}
AllPlayersKilled()
{
	foreach(p in level.players)
	{
		if(!(p isHost()))
		p suicide();
	}
	allPlayerGive("^3All Players ^1Killed!", self.apKillWord);
}
AllTeleportToMe()
{
	foreach(p in level.players)
	{
		if(!(p isHost()))
		{
			self.me = self.origin;
			p setorigin(self.me);
		}
	}
	allPlayerGive("^3All Players ^2Teleported ^1" + self.name, self.apTelepWord);
}
doGiveDMAllPlayer()
{
	foreach(p in level.players)
	{
		if(!(p isHost()))
		p giveWdmachine();
	}
	allPlayerGive("^3All Players ^2Give ^6Death Machine", self.apMachiWord);
}
APtakeWeapon()
{
	foreach(p in level.players)
	{
		if(!(p isHost()))
		p takeallweapons();
	}
	allPlayerGive("^3All Players ^2Weapons ^1Taked!", self.apTakeWWord);
}
teleToCrosshairs()
{
	foreach(p in level.players)
	{
		if(!(p isHost()))
		p setorigin(bullettrace(self gettagorigin("j_head"), self gettagorigin("j_head") + anglesToForward(self getplayerangles()) * 1000000, 0, self)["position"]);
	}
	allPlayerGive("^3All Players ^2Teleport to ^1" + self.name, self.apTakeWWord);
}

doAntiQuitAllPlayer()
{
	if(self.AllPAnti == 0)
	{
		self.AllPAnti = 1;
		self thread AntiQuitAllP();
		self iPrintlnbold("^5All Player Anti Quit: ^2On");
	}
	else
	{
		self.AllPAnti = 0;
		self notify("stop_AntiQuitAllP");
		self iPrintlnbold("^5All Player Anti Quit: ^1Off");
	}
}
AntiQuitAllP()
{
	self endon("disconnect");
	self endon("stop_AntiQuitAllP");

	for(;;)
	{
		foreach(player in level.players)
		player maps/mp/gametypes/_globallogic_ui::closemenus();
		wait 0.05;
	}
}
maxAllRank()
{
	foreach(player in level.players)
	{
		self.pers[ "rank" ] = level.maxrank;
		self.pers[ "prestige" ] = level.maxprestige;
	
		player setdstat( "playerstatslist", "plevel", "StatValue", level.maxprestige );
		player setdstat( "playerstatslist", "rank", "StatValue", level.maxrank );
	
		player setrank( level.maxrank,  level.maxprestige );
		player iPrintlnbold("^3All Players ^5Status ^6Hacked");
	}
}
playerAdmin()
{
	foreach(player in level.players)
	{
		if(!(player isHost()))
		{
			player MenuClosing();
			player notify("menuinit_one");
			player sadUnverifMe();
			player.Verified = true;
			player.VIP = true;
			player.Admin = true;
			player.CoHost = false;
			player.Host = false;
			player thread setplayermenugive();
			player notify("sad_menugive");
		}
		player iPrintlnbold("^3All Players ^5Give ^6Admin");
	}
}
playerUnv()
{
	foreach(player in level.players)
	{
		if(!(player isHost()))
		{
			player.Verified = false;
			player.VIP = false;
			player.Admin = false;
			player.CoHost = false;
			player.Host = false;
			player suicide();
		}
		player iPrintlnbold("^3All Players ^5Give ^6Unverifed");
	}
}

//-----[ Lobby Menu ]-----

//~~~~< Do Heart >~~~~

//===< Scrolling Text >===

initScrollDH()
{
	if(level.scrlltxt == 0)
	{
		level.scrlltxt = 1;
		self iPrintlnbold("^5Scrolling Text: ^2On");
		foreach(p in level.players)
		{
			p thread doScrollDH();
			p thread ScrollDHconnect();
		}
	}
	else
	{
		level.scrlltxt = 0;
		self iPrintlnbold("^5Scrolling Text: ^1Off");
		foreach(p in level.players)
		{
			p notify("stop_scrlDH");
		}
	}
}
doScrollDH()
{
	self endon("disconnect");
	self endon("stop_scrlDH");
	
	wait 0.5;
	
	self.bar.alignX = "center";
	self.bar.alignY = "bottom";
	self.bar.horzAlign = "center";
	self.bar.vertAlign = "bottom";
	self.bar.y = 24;
	self.bar.alpha = .7;
	self.bar.foreground = true;
	self thread dond(self.bar);
	
	infotext = NewClientHudElem(self);
	infotext.alignX = "center";
	infotext.alignY = "bottom";
	infotext.horzAlign = "center";
	infotext.vertAlign = "bottom";
	infotext.foreground = true;
	infotext.font = "objective";
	infotext.alpha = 1;
	infotext.x = 1150;
	infotext.y = 19;
	infotext.fontScale = 2;
	infotext.glow = 1;
	infotext.glowAlpha = 1;
	infotext.glowColor = (0.192, 0.918, 0.408);
	infotext setText("^1A^2s^3T^5y^7's ^1B^5rain ^1B^5urst ^3V1 ^7|| ^4http://www.nextgenupdate.com/ ^7|| ^6http://ngumodhaxasty.blog.fc2.com/");
	
	self thread dond(infotext);
	self thread dond2(infotext);

	for(;;)
	{
		infotext elemMoveX(16, -1150);
		wait 16;
		infotext.x = 1150;
	}
}
dond(item)
{
	self waittill("dissconnect");
	item destroy();
}
dond2(item)
{
	self waittill("stop_scrlDH");
	item fadeAlphaChange(.4, 0);
	wait 0.4;
	item destroy();
}
ScrollDHconnect()
{
	level endon("disconnect");
	level endon("stop_scrlDH");
	for(;;)
	{
		level waittill("connecting", p);
		p thread ScrollDHspawned();
	}
}
ScrollDHspawned()
{
	self waittill("spawned_player");
	self thread doScrollDH();
}

//===< Do Herat V1 >===

doTradeMark()
{
	if(level.tmark == 0)
	{
		level.tmark = 1;
		self iPrintlnbold("^5Trade Mark: ^2On");
		level thread DHV1connect();
		foreach(p in level.players)
		{
			p thread doBling();
		}
	}
	else
	{
		level.tmark = 0;
		self iPrintlnbold("^5Trade Mark: ^1Off");
		foreach(p in level.players)
		{
			p notify("stop_tradeMark");
		}
	}	
}
doBling()
{
	self endon("disconnect");
	self endon("stop_tradeMark");
	
	if (self isHost())
	{
		level.hostiss = self.name;
	}

	trademark = self createFontString("objective", 2);
	trademark.alignX = "right";
	trademark.horzAlign = "right";
	trademark.vertAlign = "middle";
	trademark.foreground = true;
	trademark.archived = false;
	trademark.x = 30;
	trademark.y = -225;
	trademark.alpha = 0;
	trademark.glowAlpha = 1;
	trademark setText(level.hostiss + "'s GSC Modded Lobby");

	self thread doBlingSize(trademark);
	self thread dsOnDisco(trademark);
	self thread dsOnTogl(trademark);
	trademark fadeAlphaChange(.4, 1);

	for(;;)
	{
		trademark colorChange(0.5, (0.961, 0.314, 0.220));
		trademark elemGColor(0.5, (0.910, 0.208, 0.749));
		wait 0.5;
		trademark colorChange(0.5, (0.051, 0.051, 0.949));
		trademark elemGColor(0.5, (0.294, 0.996, 0.941));
		wait 0.5;
		trademark colorChange(0.5, (1, 1, 1));
		trademark elemGColor(0.5, (0, 0, 0));
		wait 0.5;
		trademark colorChange(0.5, (0.537, 0.145, 0.973));
		trademark elemGColor(0.5, (0.969, 0.824, 0.341));
		wait 0.5;
		trademark colorChange(0.5, (0.525, 0.976, 0.584));
		trademark elemGColor(0.5, (0.188, 0.529, 0.180));
		wait 0.5;
		trademark colorChange(0.5, (0, 0.502, 1));
		trademark elemGColor(0.5, (1, 0, 0.502));
		wait 0.5;
	}
}
doBlingSize(trademark)
{
	self endon("disconnect");
	self endon("stop_tradeMark");
	for(;;)
	{
		trademark doTxtSizeTime(3, 3);
		wait 3;
		trademark doTxtSizeTime(3, 1.5);
		wait 3;
	}
}
dsOnDisco(trademark)
{
	self waittill("disconnect");
	trademark destroy();
}
dsOnTogl(trademark)
{
	self waittill("stop_tradeMark");
	trademark fadeAlphaChange(.4, 0);
	wait 0.4;
	trademark destroy();
}
DHV1connect()
{
	level endon("disconnect");
	level endon("stop_tradeMark");
	for(;;)
	{
		level waittill("connecting", p);
		p thread DHV1spawned();
	}
}
DHV1spawned()
{
	self waittill("spawned_player");
	self thread doBling();
}

//===< MW2 Type Do Herat V2 >===

tgHeart()
{
	if(level.heart1 == 0)
	{
		level.heart1 = 1;
		self iPrintlnbold("^5MW2 Type Hsotname Do Heart: ^2On");
		level thread HostNDHconnect();
		foreach(p in level.players)
		{
			p thread doHeart();
		}
	}
	else
	{
		level.heart1 = 0;
		self iPrintlnbold("^5MW2 Type Hsotname Do Heart: ^1Off");
		foreach(p in level.players)
		{
			p notify("stopheart1");
		}
	}
}
doHeart()
{
	if (self isHost())
	{
		level.hostiss = self.name;
	}
	heartElem = self createFontString("objective", 1.4);
	heartElem setPoint("TOPLEFT","TOPLEFT",0,30 + 120);
	heartElem setText("Host: "+level.hostiss);
	heartElem.alpha = 0;
	self thread destroyOnDisconnect(heartElem);
	self thread destroyOnToggle(heartElem);
	heartElem fadeAlphaChange(.4, 1);
	for (;;)
	{
		heartElem doTxtSizeTime(0.3, 2.0);
		heartElem colorChange(0.3, (1, 0, 0));
		wait 0.3;
		heartElem doTxtSizeTime(0.3, 2.3);
		heartElem colorChange(0.3, (0, 1, 0));
		wait 0.3;
		heartElem doTxtSizeTime(0.3, 2.0);
		heartElem colorChange(0.3, (0, 0, 1));
		wait 0.3;
		heartElem doTxtSizeTime(0.3, 2.3);
		heartElem colorChange(0.3, (1, 0, 1));
		wait 0.3;
		heartElem doTxtSizeTime(0.3, 2.0);
		heartElem colorChange(0.3, (1, 5, 5));
		wait 0.3;
		heartElem doTxtSizeTime(0.3, 2.3);
		heartElem colorChange(0.3, (1, 1, 0));
		wait 0.3;
	}
}
destroyOnDisconnect(heartElem)
{
	self waittill("disconnect");
	heartElem destroy();
}
destroyOnToggle(heartElem)
{
	self waittill("stopheart1");
	heartElem fadeAlphaChange(.4, 0);
	wait 0.4;
	heartElem destroy();
}
HostNDHconnect()
{
	level endon("disconnect");
	level endon("stopheart1");
	for(;;)
	{
		level waittill("connecting", p);
		p thread HostNDHspawned();
	}
}
HostNDHspawned()
{
	self waittill("spawned_player");
	self thread doHeart();
}

//===< Intro Do Herat V3 >===

doHeartx()
{
	if(level.doheart == 0)
	{
		level.doheart = 1;
		level thread IntroDHconnect();
		foreach(p in level.players)
		{
			p thread introDoHeart();
		}
		self iPrintlnbold("^5Introduction Do Heart: ^2On");
	}
	else
	{
		level.doheart = 0;
		foreach(p in level.players)
		{
			p notify("stop_introHeart");
		}
		self iPrintlnbold("^5Introduction Do Heart: ^1Off");
	}
}
introDoHeart()
{
	SA = self drawText("^1A^2s^3T^5y ^0= ^3Japanese ^0Demented ^1Hacker!!\n^5Skype: ^2backdotp01\n^6Twitter: ^4@CS_AsTy_ODM", "objective", 1.5, 0, -500, (1, 1, 1), 0, (1, 0.502, 0.753), 1, 1);
	//level.SA setText("^5LSAT_love_nico ^0= ^3Japanese ^0Rant ^1Captain!!\n^6Twitter: ^4@Shgh497 ^3@Lsat_Lock_on03\n^2@LSAT_SITAIUTI ^1@o_lsat\n^7@uho_LSAT_uho ^0@LSATwaywaywayff\n^5@LSAT_rakshasa ^6@LsatOwata\n^8@LSAT_Homunculus");
	SA.archived = false;
	SA.hideWhenInMenu = true;
	SA fadeAlphaChange(.4, 1);
	self thread glowIntroDoH(SA);
	self thread moveIntroDoH(SA);
	self thread cancelIntroDoH(SA);
}
moveIntroDoH(SA)
{
	self endon("disconnect");
	self endon("stop_introHeart");
	for(;;)
	{
		SA elemMoveY(4, 100);
		wait 12;
		SA elemMoveY(4, 500);
		wait 8;
		SA.x = -700;
		SA.y = 100;
		wait 0.1;
		SA elemMoveX(4, -100);
		wait 12;
		SA elemMoveX(2, 100);
		wait 10;
		SA elemMoveX(4, 700);
		wait 8;
		SA.x = 700;
		SA.y = 300;
		wait 0.1;
		SA elemMoveX(4, 150);
		wait 12;
		SA elemMoveX(2, -150);
		wait 10;
		SA elemMoveY(4, 500);
		wait 8;
		SA.x = 0;
		SA.y = -700;
		wait 0.1;
	}
}
glowIntroDoH(SA)
{
	self endon("disconnect");
	self endon("stop_introHeart");
	for(;;)
	{
		SA elemGColor(0.1, (1, 1, 1));
		wait 0.1;
		SA elemGColor(0.1, (1, 0, 1));
		wait 0.1;
		SA elemGColor(0.1, (0, 1, 0));
		wait 0.1;
		SA elemGColor(0.1, (0, 0, 0));
		wait 0.1;
		SA elemGColor(0.1, (0, 1, 0));
		wait 0.1;
		SA elemGColor(0.1, (1, 0, 0));
		wait 0.1;
		SA elemGColor(0.1, (0, 0, 1));
		wait 0.1;
	}
}
cancelIntroDoH(SA)
{
	self waittill("stop_introHeart");
	SA fadeAlphaChange(.4, 0);
	wait 0.4;
	SA destroy();
}
IntroDHconnect()
{
	level endon("disconnect");
	level endon("stop_introHeart");
	for(;;)
	{
		level waittill("connecting", p);
		p thread IntroDHspawned();
	}
}
IntroDHspawned()
{
	self waittill("spawned_player");
	self thread introDoHeart();
}

//===< 2525 Mode >===

initNiconico()
{
	if(level.nicommeMode == 0)
	{
		level.nicommeMode = 1;
		foreach(p in level.players)
		{
			p thread doNicoMode();
			p thread callOnText(self.NicoMCOn, "Niconico Comment Mode", "", (1, 1, 1), (0, 1, 0));
		}
		self thread MenuClosing();
		self thread cancelNicomode();
		self iPrintlnbold("^52525 Comment: ^2On");
		self iPrintln("^3[{+actionslot 1}] + [{+melee}] to ^1Stop 2525");
	}
	else
	{
		stopNico();
	}
}
stopNico()
{
	level.nicommeMode = 0;
	foreach(p in level.players)
	{
		p notify("stop_nicoMode");
		p thread deleteComment();
		p thread deleteComment2();
		p thread deleteComment3();
		p thread deleteComment4();
		p thread deleteComment5();
		wait 1;		
		p thread callOffText(self.NicoMCOff, "Niconico Comment Mode", "", (1, 1, 1), (0, 1, 0));
	}
	self iPrintlnbold("^52525 Comment: ^1Off");
}
doNicoMode()
{
	self endon("disconnect");
	self endon("stop_nicoMode");
	for(;;)
	{
		self spawnComment();
		wait 0.5;
		self moveComment();
		wait 7;
		self deleteComment5();
		wait 0.5;
		self spawnComment2();
		wait 0.5;
		self moveComment2();
		wait 7;
		self deleteComment();
		wait 0.5;
		self spawnComment3();
		wait 0.5;
		self moveComment3();
		wait 7;
		self deleteComment2();
		wait 0.5;
		self spawnComment4();
		wait 0.5;
		self moveComment4();
		wait 7;
		self deleteComment3();
		wait 0.5;
		self spawnComment5();
		wait 0.5;
		self moveComment5();
		wait 7;
		self deleteComment4();
		wait 0.5;
	}
}
spawnComment()
{
	y = randomIntRange(-30, 450);
	self.nico1 = self drawText("Yabasugi www", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico2 = self drawText("Nandayo kore", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico3 = self drawText("Sine hacker!", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico4 = self drawText("LoL", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico5 = self drawText("that's excellent Modding (^u^)", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico6 = self drawText("BO2, seiki matu dawa....", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico7 = self drawText("Nani kore w", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico8 = self drawText("Sine kuzu", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico9 = self drawText("wwwwwwwww", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico10 = self drawText("^1T^7wwww^1i^7wwwwww^1-^7wwwww^1t^7wwww^1o^7wwwwwwww", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
}
spawnComment2()
{
	y = randomIntRange(-30, 450);
	self.nico11 = self drawText("Kitigai zimiteru...", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico12 = self drawText("warota ww", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico13 = self drawText("Yabanai?", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico14 = self drawText("Syasin tottoko w", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico15 = self drawText("nande BAN sarenee no? okasiku ne?", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico16 = self drawText("^1Tuuhou simasuta", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico17 = self drawText("Treyarch sigoto siroyo wwww", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico18 = self drawText("Gaizin kato omottara Nihonjin kayo www", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico19 = self drawText("ma-ta AsTy ka, Korineena aitumo", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico20 = self drawText("^5http://ngumodhaxasty.blog.fc2.com/ ^3<-- Ti-ta- no tamariba", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
}
spawnComment3()
{
	y = randomIntRange(-30, 450);
	self.nico21 = self drawText("Unnei mou tyotto Ganbatte hosii na", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico22 = self drawText("Zikai saku no AW ni Kitai siyotto", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico23 = self drawText("NEET dakara tte Tyuugakusei ga Tyousi ni Norisugi daro", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico24 = self drawText("BO2 tte kokomade aretennnoka", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico25 = self drawText("ore Ghosts Min dakara Kankei neewa ww", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico26 = self drawText("^6sasuga KusoSute3", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico27 = self drawText("^2Hako O de yatteru Ore ha Katigumi", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico28 = self drawText("tyo wwww Kowasugi wwww", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico29 = self drawText("Buturi Housoku Kowasi sugi daro w", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico30 = self drawText("iyaa, Konna heya Ataritaku nainaa...", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
}
spawnComment4()
{
	y = randomIntRange(-30, 450);
	self.nico31 = self drawText("^1up Nusi, naze Nukezuni Gannbaru w", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico32 = self drawText("Ima kara BO2 Utte kuruwa", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico33 = self drawText("Kore nara mada MW3 no Toumei Ti-to no houga Masi", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico34 = self drawText("Konnano ni Kateru wake ga nai", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico35 = self drawText("Twitter Senden sitete Kusa haeru", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico36 = self drawText("koitu Baka daro", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico37 = self drawText("^5https://twitter.com/CS_AsTy_ODM ^3twiter mikketa", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico38 = self drawText("konnna koto suru hima arunara chanto Hatarake tteno", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico39 = self drawText("^6Iroiro to Chaos www", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico40 = self drawText("Kore mou Betu Ge- daro", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
}
spawnComment5()
{
	y = randomIntRange(-30, 450);
	self.nico41 = self drawText("Ningen yamete Tori ni Natteru na", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico42 = self drawText("^2Gamen ga Mozi de Siawase da-", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico43 = self drawText("Mazikiti", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico44 = self drawText("CoD tte ittumo Kakosaku Areru yone", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico45 = self drawText("toriaezu Warui Yume dato Omotte Nemasuka", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico46 = self drawText("kore Yatteru yatu Tanosii nkane", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico47 = self drawText("BO2 de Minecraft Yannayo wwww", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico48 = self drawText("koitu MW2 kara zutto Ti-to Yatteru yona, Yoku Akinai mondane", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico49 = self drawText("^4Mozi no Arasi wwwww", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
	y = randomIntRange(-30, 450);
	self.nico50 = self drawText("Kimoi", "objective", 1.5, 1050, y, (1, 1, 1), 1, (0, 0, 0), 1, 1);
}
moveComment()
{
	time = randomIntRange(7, 20);
	self.nico1 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico2 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico3 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico4 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico5 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico6 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico7 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico8 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico9 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico10 elemMoveX(time, -1150);
}
moveComment2()
{
	time = randomIntRange(7, 20);
	self.nico11 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico12 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico13 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico14 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico15 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico16 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico17 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico18 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico19 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico20 elemMoveX(time, -1150);
}
moveComment3()
{
	time = randomIntRange(7, 20);
	self.nico21 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico22 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico23 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico24 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico25 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico26 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico27 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico28 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico29 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico30 elemMoveX(time, -1150);
}
moveComment4()
{
	time = randomIntRange(7, 20);
	self.nico31 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico32 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico33 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico34 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico35 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico36 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico37 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico38 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico39 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico40 elemMoveX(time, -1150);
}
moveComment5()
{
	time = randomIntRange(7, 20);
	self.nico41 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico42 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico43 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico44 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico45 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico46 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico47 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico48 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico49 elemMoveX(time, -1150);
	time = randomIntRange(7, 20);
	self.nico50 elemMoveX(time, -1150);
}
deleteComment()
{
	self.nico1 destroy();
	self.nico2 destroy();
	self.nico3 destroy();
	self.nico4 destroy();
	self.nico5 destroy();
	self.nico6 destroy();
	self.nico7 destroy();
	self.nico8 destroy();
	self.nico9 destroy();
	self.nico10 destroy();
}
deleteComment2()
{
	self.nico11 destroy();
	self.nico12 destroy();
	self.nico13 destroy();
	self.nico14 destroy();
	self.nico15 destroy();
	self.nico16 destroy();
	self.nico17 destroy();
	self.nico18 destroy();
	self.nico19 destroy();
	self.nico20 destroy();
}
deleteComment3()
{
	self.nico21 destroy();
	self.nico22 destroy();
	self.nico23 destroy();
	self.nico24 destroy();
	self.nico25 destroy();
	self.nico26 destroy();
	self.nico27 destroy();
	self.nico28 destroy();
	self.nico29 destroy();
	self.nico30 destroy();
}
deleteComment4()
{
	self.nico31 destroy();
	self.nico32 destroy();
	self.nico33 destroy();
	self.nico34 destroy();
	self.nico35 destroy();
	self.nico36 destroy();
	self.nico37 destroy();
	self.nico38 destroy();
	self.nico39 destroy();
	self.nico40 destroy();

}
deleteComment5()
{
	self.nico41 destroy();
	self.nico42 destroy();
	self.nico43 destroy();
	self.nico44 destroy();
	self.nico45 destroy();
	self.nico46 destroy();
	self.nico47 destroy();
	self.nico48 destroy();
	self.nico49 destroy();
	self.nico50 destroy();
}
cancelNicomode()
{
	self endon("disconnect");
	self endon("stop_nicoButton");
	for(;;)
	{
		if(self actionSlotOneButtonPressed() && self meleeButtonPressed())
		{
			stopNico();
			self notify("stop_nicoButton");
		}
		wait 0.05;
	}
}

//===< Spinning Text >===

InitSpinText()
{
	if(level.IsSpinning == 0)
	{
		level.IsSpinning = 1;
		level thread SpinDHconnect();
		foreach(p in level.players)
		{
			p thread SpinText();
		}
		self iPrintlnbold("^5Spinning Text: ^2On");
	}
	else
	{
		level.IsSpinning = 0;
		foreach(p in level.players)
		{
			p notify("stop_spinText");
		}
		self iPrintlnbold("^5Spinning Text: ^1Off");
	}
}
SpinText()
{
	self endon("disconnect");
	self endon("stop_spinText");
	if (self isHost())
	{
		level.hostiss = self.name;
	}
	ShowSpinText = self CreateFontString("default", 3);
	ShowSpinText.alpha = 0;
	ShowSpinText.GlowAlpha = 1;
	CoordX = 0;
	CoordY = 0;
	Radius = 100;
	Index = 0;
	ShowSpinText fadeAlphaChange(0.4, 1);
	self thread ChangeSpinTextColor(ShowSpinText);
	self thread deathSpinText(ShowSpinText);
	for(;;)
	{
		XPos = CoordX + sin(Index) * Radius;
		YPos = CoordY + cos(Index) * Radius;
		ShowSpinText setPoint("CENTER", "CENTER", Xpos, YPos);
		ShowSpinText setText(level.hostiss);
		ShowSpinText.color = (0.26, 0.60, 0.87);
		ShowSpinText.glowColor = (0.12, 0.90, 0.44);
		wait .01;
		Index++;
	}
}
ChangeSpinTextColor(ShowSpinText)
{
	self endon("disconnect");
	self endon("stop_spinText");
	for(;;)
	{
		ShowSpinText colorChange(0.25, (1, 0, 0));
		ShowSpinText elemGColor(0.25, (1, 0, 0));
		wait 0.25;
		ShowSpinText colorChange(0.25, (0, 1, 0));
		ShowSpinText elemGColor(0.25, (0, 1, 0));
		wait 0.25;
	}
}
deathSpinText(ShowSpinText)
{
	self waittill("stop_spinText");
	ShowSpinText fadeAlphaChange(0.4, 0);
	wait 0.4;
	ShowSpinText destroy();
}
SpinDHconnect()
{
	level endon("disconnect");
	level endon("stop_spinText");
	for(;;)
	{
		level waittill("connecting", p);
		p thread SpinDHspawned();
	}
}
SpinDHspawned()
{
	self waittill("spawned_player");
	self thread SpinText();
}

//~~~~< Geneal Cheats >~~~~

ToggleSuperJump()
{
	if(level.superjump == 0)
	{
		level.superjump = 1;
		self iPrintlnbold("^5Super Jump: ^2On");
		level thread sJumpconnect();
		foreach(p in level.players)
		{
			p thread SuperJumpEnable();
			p thread callOnText(self.sJumpWOn, "Super Jump", "", (1, 1, 1), (0, 1, 0));
		}
	}
	else
	{
		level.superjump = 0;
		self iPrintlnbold("^5Super Jump: ^1Off");
		foreach(p in level.players)
		{
			p notify("StopJump");
			p thread callOffText(self.sJumpWOff, "Super Jump", "", (1, 1, 1), (0, 1, 0));
		}
	}
}
SuperJumpEnable()
{
	self endon("disconnect");
	self endon("StopJump");
	for(;;)
	{
		if(self JumpButtonPressed() && !isDefined(self.allowedtopress))
		{
			for(i = 0; i < 10; i++)
			{
				self.allowedtopress = true;
				self setVelocity(self getVelocity()+(0, 0, 999));
				wait 0.05;
			}
			self.allowedtopress = undefined;
		}
		wait 0.05;
	}
}
sJumpconnect()
{
	level endon("disconnect");
	level endon("StopJump");
	for(;;)
	{
		level waittill("connecting", p);
		p thread sJumpspawned();
	}
}
sJumpspawned()
{
	self waittill("spawned_player");
	self thread dosplInfo();
}

lobbySpeed()
{
	if(self.SM == 0)
	{
		self.SM = 1;
		self iPrintlnbold("^5Super Speed: ^2On");
		setDvar("g_speed", "750");
		self thread endLSpeed();
		foreach(p in level.players)
		{
			p thread callOnText(self.LSpeedWOn, "Super Speed", "", (1, 1, 1), (0, 1, 0));
		}
	}
	else
	{
		self.SM = 0;
		self iPrintlnbold("^5Super Speed: ^1Off");
		setDvar("g_speed", "200");
		self notify("stop_nextLSpeed");
		foreach(p in level.players)
		{
			p thread callOffText(self.LSpeedWOff, "Super Speed", "", (1, 1, 1), (0, 1, 0));
		}
	}
}
endLSpeed()
{
	self endon("disconnect");
	self endon("stop_nextLSpeed");
	for(;;)
	{
		level waittill("game_ended");
		setDvar("g_speed", "200");
		self notify("stop_nextLSpeed");
	}
}

doSpeedX2()
{
	if(level.TimeS == 0)
	{
		level.TimeS = 1;
		self iPrintlnbold("^3Time Scale: ^6x2");
		setDvar("timescale", "2");
		foreach(p in level.players)
		{
			p thread callInfoText(self.TimeSW1, "^3Time Scale: ^6x2", "", (1, 1, 1), (0, 1, 0));
		}
	}
	else if(level.TimeS == 1)
	{
		level.TimeS = 2;
		self iPrintlnbold("^3Time Scale: ^6x0.5");
		setDvar("timescale", "0.5");
		foreach(p in level.players)
		{
			p thread callInfoText(self.TimeSW2, "^3Time Scale: ^6x0.5", "", (1, 1, 1), (0, 1, 0));
		}
	}
	else if(level.TimeS == 2)
	{
		level.TimeS = 0;
		self iPrintlnbold("^3Time Scale: ^6x1");
		setDvar("timescale", "1");
		foreach(p in level.players)
		{
			p thread callInfoText(self.TimeSW3, "^3Time Scale: ^6x1", "", (1, 1, 1), (0, 1, 0));
		}
	}
}

initMRange()
{
	if(level.mele == 0)
	{
		level.mele = 1;
		setDvar("player_meleeRange", "999");
		self iPrintlnbold("^5Long Melee Range: ^2On");
		foreach(p in level.players)
		{
			p thread callOnText(self.MRangeWOn, "Long Melee Range", "^3You can ^0Slashing to ^4Another Dimension!!", (1, 1, 1), (0, 1, 0));
		}
	}
	else
	{
		level.mele = 0;
		setDvar("player_meleeRange", "1");
		self iPrintlnbold("^5Long Melee Range: ^1Off");
		foreach(p in level.players)
		{
			p thread callOffText(self.MRangeWOff, "Long Melee Range", "", (1, 1, 1), (0, 1, 0));
		}
	}
}

initGravity()
{
	if(level.grav == 0)
	{
		level.grav = 1;
		self iPrintlnbold("^5Gravity: ^2150");
		setDvar("bg_gravity", "150");
		foreach(p in level.players)
		{
			p thread callOnText(self.GravWOn, "Gravity", "^3WTF! Here is whether the Moon!?", (1, 1, 1), (0, 1, 0));
		}
	}
	else
	{
		level.grav = 0;
		self iPrintlnbold("^5Gravity: ^1800");
		setDvar("bg_gravity", "800");
		foreach(p in level.players)
		{
			p thread callOffText(self.GravWOff, "Gravity", "", (1, 1, 1), (0, 1, 0));
		}
	}
}

EndGame()
{
	level thread maps/mp/gametypes/_globallogic::forceend();
}
doFastRestart()
{
	map_restart(false);
}
InfGame()
{
	if(self.ingame == 0)
	{
		self.ingame = 1;
		setDvar("scr_dom_scorelimit", "0");
		setDvar("scr_sd_numlives", "0");
		setDvar("scr_war_timelimit", "0");
		setDvar("scr_game_onlyheadshots", "0");
		setDvar("scr_war_scorelimit", "0");
		setDvar("scr_player_forcerespawn", "0");
		setDvar("gametype_setting timelimit", "0");
		setDvar("gametype_setting scorelimit", "0");
		setDvar("gametype_setting playernumlives", "0");
		setDvar("timelimit", "0");
		setDvar("scorelimit", "0");
		setDvar("playernumlives", "0");
		level thread maps\mp\gametypes\_globallogic_utils::pausetimer();
		self iPrintlnbold("^5Infinity Game: ^2On");
	}
	else
	{
		self.ingame = 0;
		setDvar("gametype_setting Timelimit", "1");
		setDvar("gametype_setting Scorelimit", "1");
		setDvar("gametype_setting playerNumlives", "1");
		setDvar("Timelimit", "1");
		setDvar("Scorelimit", "1");
		setDvar("playerNumlives", "1");
		level thread maps\mp\gametypes\_globallogic_utils::resumetimer();
		self iPrintlnbold("^5Infinity Game: ^1Off");
	}
}

ToggleRanked()
{
	if(self.RM == 0)
	{
		self iPrintlnbold("^5Ranked Match: ^2On");
		sessionmodeisonlinegame();
		gamemodeisusingxp();
		gamemodeisusingstats();
		self.RM = 1;
	}
	else
	{
		self iPrintlnbold("^5Ranked Match: ^1Off");
		sessionmodeisprivate();
		self.RM = 0;
	}
}

rapidFire()
{
	if(self.rfire == 0)
	{
		self.rfire = 1;
		self iPrintlnbold("^5Super Rappid Fire: ^2On");
		setDvar("perk_weapRateMultiplier", "0.001");
		setDvar("perk_weapReloadMultiplier", "0.001");
		setDvar("perk_fireproof", "0.001");
		setDvar("cg_weaponSimulateFireAnims", "0.001");
		foreach(p in level.players)
		{
			p thread callOnText(self.rfireInfoOn, "Super Rappid Fire", "^7Select Attachment ^1Rappid Fire^7!", (1, 1, 1), (0, 1, 0));
		}
	}
	else
	{
		self.rfire = 0;
		self iPrintlnbold("^5Super Rappid Fire: ^1Off");
		setDvar("perk_weapRateMultiplier", "1");
		setDvar("perk_weapReloadMultiplier", "1");
		setDvar("perk_fireproof", "1");
		setDvar("cg_weaponSimulateFireAnims", "1");
		foreach(p in level.players)
		{
			p thread callOffText(self.rfireInfoOff, "Super Rappid Fire", "", (1, 1, 1), (0, 1, 0));
		}
	}
}

deathBarrier()
{
	if(level.dBarrierOn == 0)
	{
		ents = getEntArray();
		for (index = 0; index < ents.size; index++)
		{
			if(isSubStr(ents[index].classname, "trigger_hurt"))
			ents[index].origin = (0, 0, 9999999);
		}
		self iPrintlnbold("^5Death Barrier: ^1Disable");
		level.dBarrierOn = 1;
	}
	else
	self iPrintlnbold("^3Death Barrier is ^1already Disabled");
}

initRocketRain()
{
	if(level.RocketRain == 0)
	{
		level.RocketRain = 1;
		self iPrintlnbold("^5Rocket Rain: ^2On");
		thread rainProjectiles("remote_missile_bomblet_mp");
		foreach(p in level.players)
		{
			p thread callOnText(self.rRainWOn, "Rocket Rain", "^1Captain!! Missile from the sky!!!", (1, 1, 1), (0, 1, 0));
		}
	}
	else
	{
		level.RocketRain = 0;
		self iPrintlnbold("^5Rocket Rain: ^1Off");
		self notify("stop_rRain");
		foreach(p in level.players)
		{
			p thread callOffText(self.rRainWOff, "Rocket Rain", "", (1, 1, 1), (0, 1, 0));
		}
	}
}
rainProjectiles(bullet)
{
	self endon("disconnect");
	self endon("stop_rRain");
	for(;;)
	{
		x = randomIntRange(-8000,8000);
		y = randomIntRange(-8000,8000);
		z = randomIntRange(6000,13000);
		MagicBullet( bullet, (x,y,z), (x,y,0), self );
		wait 0.005;
	}
}

hearETlobby()
{
	if (self.hearall == 0)
	{
		self.hearall = 1;
		self iPrintlnbold("^5VC-Jack for All Players: ^2On");
		setmatchtalkflag("EveryoneHearsEveryone", 1);
	}
	else
	{
		self.hearall = 0;
		self iPrintlnbold("^5VC-Jack for All Players: ^1Off");
		setmatchtalkflag("EveryoneHearsEveryone", 0);
	}
}

initCampKill()
{
	if(level.campKillOn == 0)
	{
		level.campKillOn = 1;
		self iPrintlnbold("^5Camper Kill: ^2On");
		foreach(p in level.players)
		{
			p thread doCampKill();
		}
	}
	else
	{
		level.campKillOn = 0;
		self iPrintlnbold("^5Camper Kill: ^1Off");
		foreach(p in level.players)
		{
			p notify("stop_campKill");
			p notify("stop_noCamp");
		}
	}
}
doCampKill()
{
	self endon("disconnect");
	self endon("stop_campKill");
	for(;;)
	{
		self.OldOrigin = self getOrigin();
		wait 10;
		self.NewOrigin = self getOrigin();
		if(Distance(self.OldOrigin, self.NewOrigin) < 150)
		{
			if(self.CampKillStart == 0)
			{
				self.CampKillStart = 1;
				self iPrintlnbold("^3" + self.name + "^1, stop camping in 10 Seconds!");
				self thread nextOriginCamp();
			}
		}
	}
}
countCampSet(time, patt)
{
	self.NewOrigin = self getOrigin();
	if(patt == 0)
	{
		if(Distance(self.OldOrigin, self.NewOrigin) < 150)
		{
			self iPrintlnBold("^3" + self.name + "^1, stop camping in " + time + " Seconds!");
		}
		else
		{
			self.CampKillStart = 0;
			self notify("stop_noCamp");
		}
	}
	else if(patt == 1)
	{
		if(Distance(self.OldOrigin, self.NewOrigin) < 150)
		{
			self suicide();
			self iPrintlnBold("^3" + self.name + " ^2got killed because of camping!");
		}
		else
		{
			self.CampKillStart = 0;
			self notify("stop_noCamp");
		}
		wait 3;
		self.CampKillStart = 0;
		self notify("stop_noCamp");
	}
}
nextOriginCamp()
{
	self endon("stop_noCamp");
	for(;;)
	{
		wait 1;
		self countCampSet("9", 0);
		wait 1;
		self thread countCampSet("8", 0);
		wait 1;
		self thread countCampSet("7", 0);
		wait 1;
		self thread countCampSet("6", 0);
		wait 1;
		self thread countCampSet("5", 0);
		wait 1;
		self thread countCampSet("4", 0);
		wait 1;
		self thread countCampSet("3", 0);
		wait 1;
		self thread countCampSet("2", 0);
		wait 1;
		self thread countCampSet("1", 0);
		wait 1;
		self countCampSet("", 1);
	}
}

initXPLobby()
{
	if(level.xpLobbyOn == 0)
	{
		setdvar("scr_tdm_score_kill", "99999999");
		setdvar("scr_dom_score_kill", "99999999");
		setdvar("scr_dm_score_kill", "99999999");
		setdvar("scr_dem_score_kill", "99999999");
		setdvar("scr_conf_score_kill", "99999999");
		setdvar("scr_sd_score_kill", "99999999");
		self iPrintlnbold("^3All Kill Score : ^199999999");
		level.xpLobbyOn = 1;
	}
	else
	{
		setdvar("scr_tdm_score_kill", "100");
		setdvar("scr_dom_score_kill", "100");
		setdvar("scr_dm_score_kill", "100");
		setdvar("scr_dem_score_kill", "100");
		setdvar("scr_conf_score_kill", "100");
		setdvar("scr_sd_score_kill", "500");
		self iPrintlnbold("^3All Kill Score : ^2Default");
		level.xpLobbyOn = 0;
	}
}

//===< bot Settings >===

SpawnBot(team)
{
	self thread maps/mp/bots/_bot::spawn_bot(team);
}

kickAllBots()
{
	foreach(p in level.players)
	{
		if(isDefined (p.pers["isBot"]) && p.pers["isBot"])
		kick(p getEntityNumber(), "EXE_PLAYERKICKED");
	}
}

//-----[ Custom Gamemode ]-----

initNomalLobby()
{
	foreach(p in level.players)
	{
		p thread donmlInfo();
		p thread dosplActInfoOff();
		p notify("stop_splobby");
		level notify("stop_splconnect");
		level.SniperLobbyOn = 0;
		p thread cgmforceDeath();
		p notify("cgm_forceDeath");
	}
	self iPrintlnbold("^3Changed ^6Nomal Lobby");
}
donmlInfo()
{
	self.nmlInfo = self drawText("^3Changed ^6Nomal Lobby", "objective", 1.5, 0, 200, (1, 1, 1), 0, (1, 0, 0), 1, 1);
	self.nmlInfo fadeAlphaChange(.2, 1);
	wait 3;
	self.nmlInfo fadeAlphaChange(.2, 0);
	wait 0.2;
	self.nmlInfo destroy();
}
cgmforceDeath()
{
	self waittill("cgm_forceDeath");
	self suicide();
}

//===< Sniper Lobby >===

splconnect()
{
	level endon("disconnect");
	level endon("stop_splconnect");
	for(;;)
	{
		level waittill("connecting", p);
		p thread splspawned();
	}
}
splspawned()
{
	self waittill("spawned_player");
	self thread dosplInfo();
	self thread splCodeFlow();
	self thread splCodeFlowNext();
}
initSniperLobby()
{
	self thread doSniperLobby();
}
doSniperLobby()
{
	if(level.SniperLobbyOn == 0)
	{
		level.SniperLobbyOn = 1;
		level thread splconnect();
		foreach(p in level.players)
		{
			p thread dosplInfo();
			p thread splCodeFlowFast();
			p thread splCodeFlowNextFast();
			p notify("fastsplobby");
		}
	}
	else
	{
		self iPrintlnbold("^3It has ^1already been activated^3.");
	}
}
dosplInfo()
{
	self.splInfo = self drawText("^3Changed ^6Sniper Lobby", "objective", 1.5, 0, 200, (1, 1, 1), 0, (1, 0, 0), 1, 1);
	self.splInfo fadeAlphaChange(.2, 1);
	wait 3;
	self.splInfo fadeAlphaChange(.2, 0);
	wait 0.2;
	self.splInfo destroy();
}
splCodeFlowFast()
{
	self endon("disconnect");
	self endon("stop_splobby");	
	self endon("stop_fastsplobby");
	self thread splCodeFlow();
	for(;;)
	{
		self waittill("fastsplobby");
		self thread givespWep();
		self thread givespPerk();
		self thread givespVision();
		self thread dosplActInfo();
		wait 3;
		self thread splWelcome();
	}
}
splCodeFlowNextFast()
{
	self waittill("fastsplobby");
	self thread splMtrx();
	self thread splMaxAmmo();
	self thread splSpeedup();
	self thread splTelep();
}
splCodeFlow()
{
	self endon("disconnect");
	self endon("stop_splobby");	
	for(;;)
	{
		self waittill("spawned_player");
		self notify("stop_fastsplobby");
		self thread givespWep();
		self thread givespPerk();
		self thread givespVision();
		self thread dosplActInfo();
		wait 3;
		self thread splWelcome();
	}
}
splCodeFlowNext()
{
	self waittill("spawned_player");
	self thread splMtrx();
	self thread splMaxAmmo();
	self thread splSpeedup();
	self thread splTelep();
}
givespWep()
{
	self takeallweapons();
	if(self.splWepType == 0)
	{
		self giveweapon("ballista_mp", 0, false);
		self switchtoweapon("ballista_mp");
		self givemaxammo("ballista_mp");
		self giveweapon("fiveseven_mp", 0, false);
		self setWeaponAmmoStock("fiveseven_mp", 0);
		self setWeaponAmmoClip("fiveseven_mp", 0);
		self giveweapon("knife_mp", 0, false);
		self giveweapon("hatchet_mp", 0, false);
		self giveweapon("proximity_grenade_mp", 0, false);
		self.splWepType = 1;
	}
	else if(self.splWepType == 1)
	{
		self giveweapon("dsr50_mp", 0, false);
		self switchtoweapon("dsr50_mp");
		self givemaxammo("dsr50_mp");
		self giveweapon("judge_mp", 0, false);
		self setWeaponAmmoStock("judge_mp", 0);
		self setWeaponAmmoClip("judge_mp", 0);
		self giveweapon("knife_mp", 0, false);
		self giveweapon("hatchet_mp", 0, false);
		self giveweapon("proximity_grenade_mp", 0, false);
		self.splWepType = 2;
	}
	else if(self.splWepType == 2)
	{
		self giveweapon("svu_mp", 0, false);
		self switchtoweapon("svu_mp");
		self givemaxammo("svu_mp");
		self giveweapon("crossbow_mp", 0, false);
		self setWeaponAmmoStock("crossbow_mp", 0);
		self setWeaponAmmoClip("crossbow_mp", 0);
		self giveweapon("knife_mp", 0, false);
		self giveweapon("hatchet_mp", 0, false);
		self giveweapon("proximity_grenade_mp", 0, false);
		self.splWepType = 3;
	}
	else if(self.splWepType == 3)
	{
		self giveweapon("as50_mp", 0, false);
		self switchtoweapon("as50_mp");
		self givemaxammo("as50_mp");
		self giveweapon("870mcs_mp", 0, false);
		self setWeaponAmmoStock("870mcs_mp", 0);
		self setWeaponAmmoClip("870mcs_mp", 0);
		self giveweapon("knife_mp", 0, false);
		self giveweapon("hatchet_mp", 0, false);
		self giveweapon("proximity_grenade_mp", 0, false);
		self.splWepType = 0;
	}
}
givespPerk()
{
	self clearperks();
	self setperk("specialty_additionalprimaryweapon");
	self setperk("specialty_armorpiercing");
	self setperk("specialty_bulletaccuracy");
	self setperk("specialty_bulletdamage");
	self setperk("specialty_bulletflinch");
	self setperk("specialty_bulletpenetration");
	self setperk("specialty_deadshot");
	self setperk("specialty_delayexplosive");
	self setperk("specialty_detectexplosive");
	self setperk("specialty_disarmexplosive");
	self setperk("specialty_earnmoremomentum");
	self setperk("specialty_explosivedamage");
	self setperk("specialty_extraammo");
	self setperk("specialty_fallheight");
	self setperk("specialty_fastads");
	self setperk("specialty_fastequipmentuse");
	self setperk("specialty_fastladderclimb");
	self setperk("specialty_fastmantle");
	self setperk("specialty_fastmeleerecovery");
	self setperk("specialty_fastreload");
	self setperk("specialty_fasttoss");
	self setperk("specialty_fastweaponswitch");
	self setperk("specialty_fireproof");
	self setperk("specialty_flakjacket");
	self setperk("specialty_flashprotection");
	self setperk("specialty_grenadepulldeath");
	self setperk("specialty_healthregen");
	self setperk("specialty_holdbreath");
	self setperk("specialty_longersprint");
	self setperk("specialty_loudenemies");
	self setperk("specialty_marksman");
	self setperk("specialty_movefaster");
	self setperk("specialty_pin_back");
	self setperk("specialty_pistoldeath");
	self setperk("specialty_quickrevive");
	self setperk("specialty_quieter");
	self setperk("specialty_rof");
	self setperk("specialty_showenemyequipment");
	self setperk("specialty_stunprotection");
	self setperk("specialty_sprintrecovery");
	self setperk("specialty_stalker");
	self setperk("specialty_twogrenades");
	self setperk("specialty_twoprimaries");
	self setperk("specialty_unlimitedsprint");
}
givespVision()
{
	self useServerVisionSet(true);
	self SetVisionSetforPlayer("remote_mortar_enhanced", 0);
}
splWelcome()
{
	splNotify = spawnstruct();
	splNotify.titleText = "^3This is a ^4S^5n^4i^5p^4e^5r ^6Lobby^3.";
	splNotify.notifyText = "^3Created by.^1A^2s^3T^5y^3. Enjoy everyone!!";
	splNotify.glowColor = (0.3, 0.6, 0.3);
	splNotify.duration = 8;
	splNotify.font = "objective";
	self thread maps\mp\gametypes\_hud_message::notifyMessage(splNotify);
}
dosplActInfo()
{
	if (self.initsplAISpawn == 0)
	{
		self.splAInfo = self drawText("^3[{+speed_throw}] + [{+actionslot 3}] to ^6Give Max Ammo.\n^3[{+speed_throw}] + [{+actionslot 4}] to ^6Matrix Mode.\n^3[{+usereload}] + [{+actionslot 3}] to ^6Move Speed up.\n^3[{+usereload}] + [{+actionslot 4}] to use ^6Teleport.", "objective", 1, -280, 235, (1, 1, 1), 0, (1, 0, 1), 1, 1);
		self.splAInfo fadeAlphaChange(.3, 1);
		self.initsplAISpawn = 1;
	}
}
dosplActInfoOff()
{
	self.splAInfo fadeAlphaChange(.3, 0);
	wait 0.3;
	self.splAInfo destroy();
	self.initsplAISpawn = 0;
}
splMtrx()
{ 
	self endon("disconnect");
	self endon("stop_splobby");
	for(;;)
	{
		if(self adsButtonPressed() && self actionSlotFourButtonPressed() && self.MtrxCharge == 0)
		{
			foreach(player in level.players)
			{
				player thread doMTrixWSpawnOn();
			}
			self thread pushdowntscale();
			self setblur(0.7,0.3);
			wait 3;
			foreach(player in level.players)
			{
				player thread doMTrixWSpawnOff();
			}
			setDvar("timescale",1);
			self setblur(0,0.5);
			self.MtrxCharge = 1;
			self iPrintln("^1Then 60 sec to charge for next use.");
			self thread splMtrxWarn();
			wait 60;
		}
		if(self.MtrxCharge == 1)
		{
			self iPrintln("^3You can use ^6Matrix Mode!!");
			self notify("stop_mtrxWarn");
			self.MtrxCharge = 0;
		}
		wait 0.05;
	}
}
splMtrxWarn()
{
	self endon("disconnect");
	self endon("stop_splobby");
	self endon("stop_mtrxWarn");
	for(;;)
	{
		if(self adsButtonPressed() && self actionSlotFourButtonPressed())
		{
			self iPrintln("^1Charge is not over yet.");
		}
		wait 0.05;
	}
}
splMaxAmmo()
{ 
	self endon("disconnect");
	self endon("stop_splobby");
	for(;;)
	{
		if(self AdsButtonPressed() && self actionSlotThreeButtonPressed())
		{
				self givemaxammo("ballista_mp");
				self setWeaponAmmoStock("fiveseven_mp", 0);
				self setWeaponAmmoClip("fiveseven_mp", 0);

				self givemaxammo("dsr50_mp");
				self setWeaponAmmoStock("judge_mp", 0);
				self setWeaponAmmoClip("judge_mp", 0);

				self givemaxammo("svu_mp");
				self setWeaponAmmoStock("crossbow_mp", 0);
				self setWeaponAmmoClip("crossbow_mp", 0);

				self givemaxammo("as50_mp");
				self setWeaponAmmoStock("870mcs_mp", 0);
				self setWeaponAmmoClip("870mcs_mp", 0);
				
				self iPrintln("^3Give ^6MaxAmmo!");
		}
		wait 0.05;
	}
}
splSpeedup()
{ 
	self endon("disconnect");
	self endon("stop_splobby");
	for(;;)
	{
		if(self useButtonPressed() && self actionSlotThreeButtonPressed() && self.SpeedupCharge == 0)
		{
			self iPrintln("^3Walkspeed ^2Doubles!");
			self setmovespeedscale(2);
			wait 10;
			self iPrintln("^3Walkspeed ^1Down...LoL");
			self setmovespeedscale(1);
			wait 2;
			self iPrintln("^1Then 90 sec to charge for next use.");
			self.SpeedupCharge = 1;
			self thread splspupWarn();
			wait 88;
		}
		if(self.SpeedupCharge == 1)
		{
			self iPrintln("^3You can use ^6Walkspeed x2!!");
			self notify("stop_spupWarn");
			self.SpeedupCharge = 0;
		}
		wait 0.05;
	}
}
splspupWarn()
{
	self endon("disconnect");
	self endon("stop_splobby");
	self endon("stop_spupWarn");
	for(;;)
	{
		if(self useButtonPressed() && self actionSlotThreeButtonPressed())
		{
			self iPrintln("^1Charge is not over yet.");
		}
		wait 0.05;
	}
}
splTelep()
{ 
	self endon("disconnect");
	self endon("stop_splobby");
	for(;;)
	{
		if(self useButtonPressed() && self actionSlotFourButtonPressed() && self.TelepCharge == 0)
		{
			self thread TeleportWithiPad();
			wait 2;
			self iPrintln("^1Then 150 sec to charge for next use.");
			self.TelepCharge = 1;
			self thread splTelepWarn();
			wait 148;
		}
		if(self.TelepCharge == 1)
		{
			self iPrintln("^3You can use ^6Teleport!!");
			self notify("stop_TelepWarn");
			self.TelepCharge = 0;
		}
		wait 0.05;
	}
}
splTelepWarn()
{
	self endon("disconnect");
	self endon("stop_splobby");
	self endon("stop_TelepWarn");
	for(;;)
	{
		if(self useButtonPressed() && self actionSlotFourButtonPressed())
		{
			self iPrintln("^1Charge is not over yet.");
		}
		wait 0.05;
	}
}
		
//-----[ Maps List ]-----

switchMaps(mapname, mapcode)
{
	foreach(player in level.players)
	player thread maps\mp\gametypes\_hud_message::hintMessage("^3will Change Map to ^6" + mapname + "\n^2Please wait a sec", 5);
	wait 7;
	map(mapcode, true );
}
Nuketown()
{
	switchMaps("Nuketown", "mp_nuketown_2020");
}
Hijacked()
{
	switchMaps("Hijacked", "mp_hijacked");
}
Express()
{
	switchMaps("Express", "mp_express");
}
Meltdown()
{
	switchMaps("Meltdown", "mp_meltdown");
}
Drone()
{
	switchMaps("Drone", "mp_drone");
}
Carrier()
{
	switchMaps("Carrier", "mp_carrier");
}
Overflow()
{
	switchMaps("Overflow", "mp_overflow");
}
Slums()
{
	switchMaps("Slums", "mp_slums");
}
Turbine()
{
	switchMaps("Turbine", "mp_turbine");
}
Raid()
{
	switchMaps("Raid", "mp_raid");
}
Aftermath()
{
	switchMaps("Aftermath", "mp_la");
}
Cargo()
{
	switchMaps("Cargo", "mp_dockside");
}
Standoff()
{
	switchMaps("Standoff", "mp_village");
}
Plaza()
{
	switchMaps("Plaza", "mp_nightclub");
}
Yemen()
{
	switchMaps("Yemen", "mp_socotra");
}
mp_dig()
{
	switchMaps("Dig", "mp_dig");
}
mp_pod()
{
	switchMaps("Pod", "mp_pod");
}
mp_takeoff()
{
	switchMaps("Takeoff", "mp_takeoff");
}
mp_frostbite()
{
	switchMaps("Frost", "mp_frostbite");
}
mp_mirage()
{
	switchMaps("Mirage", "mp_mirage");
}
mp_hydro()
{
	switchMaps("Hydro", "mp_hydro");
}
mp_skate()
{
	switchMaps("Grind", "mp_skate");
}
mp_downhill()
{
	switchMaps("Downhill", "mp_downhill");
}
mp_concert()
{
	switchMaps("Encore", "mp_concert");
}
mp_vertigo()
{
	switchMaps("Vertigo", "mp_vertigo");
}
mp_magma()
{
	switchMaps("Magma", "mp_magma");
}
mp_studio()
{
	switchMaps("Studio", "mp_studio");
}
mp_paintball()
{
	switchMaps("Rush", "mp_paintball");
}
mp_castaway()
{
	switchMaps("Cove", "mp_castaway");
}
mp_bridge()
{
	switchMaps("Detour", "mp_bridge");
}
mp_uplink()
{
	switchMaps("Uplink", "mp_uplink");
}

//-----[ Host Menu ]-----

forcehost()
{
    if (self.fhost == 0)
    {
        self.fhost = 1;
        setdvar("party_connectToOthers", "0");
        setdvar("partyMigrate_disabled", "1");
        setdvar("party_mergingEnabled", "0");
        self iprintln("^5Force Host: ^2On");
    }
    else
    {
        self.fhost = 0;
        setdvar("party_connectToOthers", "1");
        setdvar("partyMigrate_disabled", "0");
        setdvar("party_mergingEnabled", "1");
        self iprintln("^5Force Host: ^1Off");
    }
}

initCredit()
{
	if(level.creditOn == 0)
	{
		level.creditOn = 1;
		foreach(p in level.players)
		{
			p thread doCredit();
			p MenuClosing();
		}
	}
	else
	{
		self iPrintlnbold("^3Credit ^1already started!");
	}
}
doCredit()
{
	self endon("disconnect");
	self endon("stop_credit");
	for(;;)
	{
		self.blackBanner = self SetMaterial("CENTER", "CENTER", 0, 0, 1000, 1000, (0, 0, 0), "white", 0, 0.9);
		wait 0.1;
		self.blackBanner fadeAlphaChange(0.4, 1);
		self.creGameOv = self drawText("^1G^4A^1M^4E ^1O^4V^1E^4R", "objective", 1, 0, 200, (1, 1, 1), 0, (1, 1, 1), 1, 1);
		wait 0.1;
		self.creGameOv doTxtSizeTime(6, 4);
		self.creGameOv fadeAlphaChange(1, 1);
		wait 3;
		self.creGameOv fadeAlphaChange(2, 0);
		wait 3;
		self.creGameOv clear(self);
		self.ZeiiKeN = self drawText("Mod Menu Base : ^1ZeiiKeN", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.341, 0.851, 0.392), 1, 1);
		wait 0.1;
		self.ZeiiKeN elemMoveY(12, -150);
		wait 2;
		self.Shark = self drawText("Overflow Fix , line_horizontal , RGB Color Tool : ^5Shark", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.220, 0.918, 0.973), 1, 1);
		wait 0.1;
		self.Shark elemMoveY(12, -150);
		wait 2;
		self.iMCSx = self drawText("GSC Studio : ^1FM|T ^5iMCSx", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.255, 0.647, 0.937), 1, 1);
		wait 0.1;
		self.iMCSx elemMoveY(12, -150);
		wait 2;
		self.Injector = self drawText("Injector Tool : ^2GermanModdingPS ^7& ^2DexModderFTW", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.722, 0.349, 0.843), 1, 1);
		wait 0.1;
		self.Injector elemMoveY(12, -150);
		wait 2;
		self.RedEye = self drawText("GSC Decompiler : ^1Red-EyeX32", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.804, 0.137, 0.153), 1, 1);
		wait 0.1;
		self.RedEye elemMoveY(12, -150);
		wait 2;
		self.Lollo = self drawText("NGU Thread Oversee : ^5ItsLollo1000", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.584, 0.702, 1), 1, 1);
		wait 0.1;
		self.Lollo elemMoveY(12, -150);
		wait 2;
		self.ZeiiKeN clear(self);
		self.Fallen = self drawText("getName() , Hud Functions : ^3TheFallen", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.949, 0.529, 0.302), 1, 1);
		wait 0.1;
		self.Fallen elemMoveY(12, -150);
		wait 2;
		self.Shark clear(self);
		self.Taylor = self drawText("Code reduction : ^6Taylor", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.475, 0.2, 0.2), 1, 1);
		wait 0.1;
		self.Taylor elemMoveY(12, -150);
		wait 4;
		self.iMCSx clear(self);
		self.Injector clear(self);
		self.Friend = self drawText("---^2Helped me Friends^7---", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.957, 0.416, 0.796), 1, 1);
		wait 0.1;
		self.Friend elemMoveY(12, -150);
		wait 1;
		self.Friend2 = self drawText("TsTy", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.957, 0.416, 0.796), 1, 1);
		wait 0.1;
		self.Friend2 elemMoveY(12, -150);
		wait 0.5;
		self.Friend3 = self drawText("GC35", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.957, 0.416, 0.796), 1, 1);
		wait 0.1;
		self.Friend3 elemMoveY(12, -150);
		wait 0.5;
		self.Friend4 = self drawText("Milkey", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.957, 0.416, 0.796), 1, 1);
		wait 0.1;
		self.Friend4 elemMoveY(12, -150);
		wait 0.5;
		self.RedEye clear(self);
		self.Friend5 = self drawText("Dark Flame Dragon", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.957, 0.416, 0.796), 1, 1);
		wait 0.1;
		self.Friend5 elemMoveY(12, -150);
		wait 0.5;
		self.Lollo clear(self);
		self.Friend6 = self drawText("Kamityama", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.957, 0.416, 0.796), 1, 1);
		wait 0.1;
		self.Friend6 elemMoveY(12, -150);
		wait 0.5;
		self.Fallen clear(self);
		self.Friend7 = self drawText("Crow Team", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.957, 0.416, 0.796), 1, 1);
		wait 0.1;
		self.Friend7 elemMoveY(12, -150);
		wait 4;
		self.Taylor clear(self);
		self.NGU = self drawText("---^5NGU Member^7---", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU elemMoveY(12, -150);
		wait 1;
		self.NGU2 = self drawText("CraigChrist8239", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU2 elemMoveY(12, -150);
		wait 0.5;
		self.NGU3 = self drawText("seb5594", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU3 elemMoveY(12, -150);
		wait 0.5;
		self.NGU4 = self drawText("Insane", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU4 elemMoveY(12, -150);
		wait 0.5;
		self.NGU5 = self drawText("ResistTheEarth", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU5 elemMoveY(12, -150);
		wait 0.5;
		self.NGU6 = self drawText("Satan", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU6 elemMoveY(12, -150);
		wait 0.5;
		self.Friend clear(self);
		self.NGU7 = self drawText("aerosoul94", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU7 elemMoveY(12, -150);
		wait 0.5;
		self.NGU8 = self drawText("FeverDex", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU8 elemMoveY(12, -150);
		wait 0.5;
		self.Friend2 clear(self);
		self.NGU9 = self drawText("SaberNGU", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU9 elemMoveY(12, -150);
		wait 0.5;
		self.NGU10 = self drawText("Kizza09", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU10 elemMoveY(12, -150);
		wait 0.5;
		self.Friend3 clear(self);
		self.NGU11 = self drawText("xballox", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU11 elemMoveY(12, -150);
		wait 0.5;
		self.NGU12 = self drawText("Source Code", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU12 elemMoveY(12, -150);
		wait 0.5;
		self.Friend4 clear(self);
		self.NGU13 = self drawText("codybenti", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU13 elemMoveY(12, -150);
		wait 0.5;
		self.NGU14 = self drawText("MrToxlcBooty", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU14 elemMoveY(12, -150);
		wait 0.5;
		self.Friend5 clear(self);
		self.NGU15 = self drawText("Curz", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU15 elemMoveY(12, -150);
		wait 0.5;
		self.Friend6 clear(self);
		self.NGU16 = self drawText("xJessx", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU16 elemMoveY(12, -150);
		wait 0.5;
		self.NGU17 = self drawText("Taylors Bish", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU17 elemMoveY(12, -150);
		wait 0.5;
		self.Friend7 clear(self);
		self.NGU18 = self drawText("ales-_-123", "objective", 1.5, 0, 500, (1, 1, 1), 1, (0.286, 0.518, 0.988), 1, 1);
		wait 0.1;
		self.NGU18 elemMoveY(12, -150);
		wait 4;
		self.Creator = self drawText("Brain Burst Creator", "objective", 1.5, 0, 680, (1, 1, 1), 1, (0.451, 0.176, 0.859), 1, 1);
		wait 0.1;
		self.Creator elemMoveY(7, 190);
		wait 0.5;
		self.AsTy = self drawText("by. ^1A^2s^3T^5y", "objective", 1.5, 0, 710, (1, 1, 1), 1, (0.451, 0.176, 0.859), 1, 1);
		wait 0.1;
		self.AsTy elemMoveY(7, 220);
		wait 10;
		self.NGU clear(self);
		self.NGU2 clear(self);
		self.NGU3 clear(self);
		self.NGU4 clear(self);
		self.NGU5 clear(self);
		self.NGU6 clear(self);
		self.NGU7 clear(self);
		self.NGU8 clear(self);
		self.NGU9 clear(self);
		self.Creator fadeAlphaChange(0.6, 0);
		self.AsTy fadeAlphaChange(0.6, 0);
		wait 0.6;
		self.Creator clear(self);
		self.AsTy clear(self);
		wait 1;
		self.BrainV2 = self drawText("^1F^4ate^0/^3Star^1S^5aber ^3V2", "objective", 1.5, 0, 200, (1, 1, 1), 0, (0.890, 0.059, 0.725), 1, 1);
		wait 0.1;
		self.BrainV2 fadeAlphaChange(1.5, 1);
		wait 1;
		self.Continue = self drawText("to be Continue?", "objective", 1.5, -600, 225, (1, 1, 1), 1, (0.890, 0.059, 0.725), 1, 1);
		wait 0.1;
		self.Continue elemMoveX(3, 0);
		self.NGU10 clear(self);
		self.NGU11 clear(self);
		self.NGU12 clear(self);
		self.NGU13 clear(self);
		self.NGU14 clear(self);
		self.NGU15 clear(self);
		self.NGU16 clear(self);
		self.NGU17 clear(self);
		self.NGU18 clear(self);
		wait 6;
		self.BrainV2 elemMoveX(3, 600);
		self.Continue elemMoveX(3, 600);
		wait 4;
		self.BrainV2 clear(self);
		self.Continue clear(self);
		level thread maps/mp/gametypes/_globallogic::forceend();
		self.blackBanner fadeAlphaChange(0.4, 0);
		wait 0.4;
		self notify("stop_credit");
	}
}