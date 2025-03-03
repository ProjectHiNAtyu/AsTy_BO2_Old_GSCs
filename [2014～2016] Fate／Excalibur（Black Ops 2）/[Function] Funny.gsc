TeleportToLocationSelector()
{
	self thread init_LocationSelector(0, 1, 1, 1, 0);
}

PickupPlayer()
{
	self thread init_PickupPlayer(1, 200);
}

//-----< On / Off >-----

init_PickupPlayer(Notice, Range)
{
	if(self.isPickupPlayer == 0)
	{
		self thread do_PickupPlayer(Range);
		if(Notice == 1)
		{
			self iPrintln("^6Pickup Player ^7: [^2On^7]");
			if(self.NoticeTextMode == 0)
				self thread optionCalledMesage("You can Move the Player.", 1, "[{+speed_throw}] : ^2Pickup Player", (0, 1, 0), 6, 0);
			else
				self thread init_NotifySetText(0, 2, "^6Pickup Player ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 3, 1, "[{+speed_throw}] : ^2Pickup Player", (1, 1, 1), 1, (1, 1, 1));
		}
		self.isPickupPlayer = 1;
	}
	else
	{
		self notify("stop_PickupPlayer");
		if(Notice == 1)
		{
			self iPrintln("^6Pickup Player ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Pickup Player ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isPickupPlayer = 0;
	}
}
do_PickupPlayer(Range)
{
	self endon("disconnect");
	self endon("stop_PickupPlayer");
	for(;;)
	{
		while(self AdsButtonPressed())
		{
			Trace = bulletTrace(self getTagOrigin("j_head"), self getTagOrigin("j_head") + anglesToForward(self getplayerangles()) * 1000000, true, self);
			while(self AdsButtonPressed())
			{
				Location = self TraceBullet(Range);
				Trace["entity"] setOrigin(Location);
				Trace["entity"].origin = Location;
				wait 0.01;
			}
		}
		wait 0.01;
	}
}

ThirdPerson()
{
	self thread init_3rdPerson(1);
}
init_3rdPerson(Notice)
{
	if(self.is3rdPerson == 0)
	{
		self thread do_3rdPerson();
		if(Notice == 1)
		{
			self iPrintln("^63rd Person ^7: [^2On^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^63rd Person ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.is3rdPerson = 1;
	}
	else
	{
		self notify("stop_3rdPerson");
		self setClientThirdPerson(0);
		if(Notice == 1)
		{
			self iPrintln("^63rd Person ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^63rd Person ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.is3rdPerson = 0;
	}
}
do_3rdPerson()
{
	self endon("disconnect");
	self endon("stop_3rdPerson");
	for(;;)
	{
		self setClientThirdPerson(1);
		wait 0.1;
	}
}

ClientFOV()
{
	if(self.Scale_ClientFOV == 64)
	{
		self thread Change_ClientFOV(1);
		self notify("stop_ClientFOV");
	}
	else if(self.Scale_ClientFOV < 150)
	{
		self thread Change_ClientFOV(1);
	}
	else if(self.Scale_ClientFOV == 150)
	{
		self.Scale_ClientFOV = 29;
		self thread Change_ClientFOV(1);
	}
}
Change_ClientFOV(Notice)
{
	self.Scale_ClientFOV++;
	Scale = self.Scale_ClientFOV;
	self setClientFOV(self.Scale_ClientFOV);
	self notify("stop_ClientFOV");
	self thread do_ClientFOV();
	if(Notice == 1)
	{
		self iPrintln("^6Client FOV Scale ^7: [^5" + Scale + "^7]");
		if(self.NoticeTextMode == 1)
			self thread init_NotifySetText(0, 2, "^6Change Client FOV ^7to ^5" + Scale, (1, 1, 1), 1, (0, 0, 1), 2, 0);
	}
}
do_ClientFOV()
{
	self endon("disconnect");
	self endon("stop_ClientFOV");
	for(;;)
	{
		self setClientFOV(self.Scale_ClientFOV);
		wait 0.05;
	}
}

Set_Model_Debug()
{
	self thread Process_Change_Model("defaultactor", 1, 1, "Debug");
}
Set_Model_Dog()
{
	self thread Process_Change_Model("german_shepherd", 1, 1, "Dog");
}
Set_Model_Default()
{
	self thread Change_Model("Default", 0, 1, 0);
}

//-----< 本体 >-----

Process_Change_Model(Code, TP, Notice, Word)
{
	self thread Change_Model("Default", 0, 0, 0);
	wait 0.1;
	self thread Change_Model(Code, TP, Notice, Word);
}
Change_Model(Code, TP, Notice, Word)
{
	if(Code != "Default")
	{
		self notify("stop_Change_Model");
		self setModel(Code);
		self thread Spawned_Change_Model(Code);
	}
	else
	{
		self notify("stop_Change_Model");
		self [[game["set_player_model"][self.team]["default"]]]();
	}
	if(TP == 1)
		self setClientThirdPerson(1);
	else
		self setClientThirdPerson(0);
	if(Notice == 1)
	{
		if(Word != 0)
			self iPrintln("^6Set Model ^7: [^5" + Word + "^7]");
		else
			self iPrintln("^6Set Model ^7: [^5" + Code + "^7]");
	}
}
Spawned_Change_Model(Code)
{
	self endon("disconnect");
	self endon("stop_Change_Model");
	for(;;)
	{
		self waittill("spawned_player");
		wait 1;
		self setModel(Code);
	}
}

LinkTo_Model_HunterKiller()
{
	self thread Process_LinkTo_Model("veh_t6_drone_hunterkiller", 1, 0, 1, 1, "Hunter Killer");
}
LinkTo_Model_TrophySystem()
{
	self thread Process_LinkTo_Model("t6_wpn_trophy_system_world", 1, 0, 1, 1, "Trophy System");
}
LinkTo_Model_AssaultDrone()
{
	self thread Process_LinkTo_Model("veh_t6_drone_tank", 1, 0, 1, 1, "Assault Drone");
}
LinkTo_Model_AttackHelicopter()
{
	self thread Process_LinkTo_Model("veh_t6_air_attack_heli_mp_light", 1, 150, 1, 1, "Attack Helicopter");
}
LinkTo_Model_VTOLWarship()
{
	self thread Process_LinkTo_Model("veh_t6_air_v78_vtol_killstreak", 1, 160, 1, 1, "VTOL Warship");
}
LinkTo_Model_OverWatch()
{
	self thread Process_LinkTo_Model("veh_t6_drone_overwatch_dark", 1, 130, 1, 1, "Over Watch");
}
LinkTo_Model_UAV()
{
	self thread Process_LinkTo_Model("veh_t6_drone_uav", 1, 120, 1, 1, "UAV");
}
LinkTo_Model_CarePackage()
{
	self thread Process_LinkTo_Model("t6_wpn_supply_drop_ally", 1, 0, 1, 1, "Care Package");
}
LinkTo_Model_SentryGun()
{
	self thread Process_LinkTo_Model("t6_wpn_turret_sentry_gun", 1, 0, 1, 1, "Sentry Gun");
}
LinkTo_Model_StealthBomber()
{
	self thread Process_LinkTo_Model("veh_t6_drone_pegasus_mp", 1, 140, 1, 1, "Stealth Bomber");
}
LinkTo_Model_FA38()
{
	self thread Process_LinkTo_Model("veh_t6_air_fa38_killstreak", 1, 140, 1, 1, "FA38");
}
LinkTo_Model_Delete()
{
	self thread LinkTo_Model("Delete", 0, 0, 0, 1, "");
}

//-----< 内部処理 >-----

Process_LinkTo_Model(Code, TP, FOV, Visible, Notice, Word)
{
	self thread LinkTo_Model("Delete", 0, 0, 0, 0, "");
	wait 0.1;
	self thread LinkTo_Model(Code, TP, FOV, Visible, Notice, Word);
}

//-----< 本体 >-----

LinkTo_Model(Code, TP, FOV, Visible, Notice, Word)
{
	if(Code != "Delete")
	{
		self.LinkTo_Model_Object = spawn("script_model", self.origin);
		self.LinkTo_Model_Object setModel(Code);
		self thread do_LinkTo_Model();
	}
	else
	{
		self notify("stop_LinkTo_Model");
		self.LinkTo_Model_Object delete();
	}
	if(TP == 1)
		self setClientThirdPerson(1);
	else
		self setClientThirdPerson(0);
	if(FOV != 0)
		self setClientFOV(FOV);
	else
		self setClientFOV(65);
	if(Visible == 1)
		self hide();
	else
		self show();
	if(Notice == 1)
	{
		if(Code != "Delete" && Word != "")
			self iPrintln("^6Link to Model ^7: [^5" + Word + "^7]");
		else if(Code != "Delete" && Word == "")
			self iPrintln("^6Link to Model ^7: [^5" + Code + "^7]");
		else if(Code == "Delete" && Word == "")
			self iPrintln("^6Link to Model ^7: [^1Delete Object^7]");
	}
}
do_LinkTo_Model()
{
	self endon("disconnect");
	self endon("stop_LinkTo_Model");
	for(;;)
	{
		self.LinkTo_Model_Object MoveTo(self.origin, 0.1);
		self.LinkTo_Model_Object RotateTo(self.angles, 0.1);
		wait 0.01;
	}
}


















