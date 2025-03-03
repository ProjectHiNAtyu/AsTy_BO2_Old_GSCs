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

SomePerks()
{
	self thread init_SomePerks(1);
}

init_SomePerks(Notice)
{
	self thread Set_SomePerks();
	if(Notice == 1)
	{
		self iPrintln("^6Some Perks ^7: [^2Set^7]");
		if(self.NoticeTextMode == 1)
			self thread init_NotifySetText(0, 2, "^6Some Perks ^7is ^2Setted.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
	}
}

//-----< 本体 >-----

Set_SomePerks(Notice)
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

AlwaysUAV()
{
	self thread init_AlwaysUAV(1);
}

//-----< 本体 >-----

init_AlwaysUAV(Notice)
{
	if (self.isAlwaysUAV == 0)
	{
		self setClientUIVisibilityFlag("g_compassShowEnemies", 1);
		if(Notice == 1)
		{
			self iPrintln("^6Always UAV ^7: [^2On^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Always UAV ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isAlwaysUAV = 1;
	}
	else
	{
		self setClientUIVisibilityFlag("g_compassShowEnemies", 0);
		if(Notice == 1)
		{
			self iPrintln("^6Always UAV ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Always UAV ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isAlwaysUAV = 0;
	}
}

AlwaysVSAT()
{
	self thread init_AlwaysVSAT(1);
}

init_AlwaysVSAT(Notice)
{
	if(self.isAlwaysVSAT == 0)
	{
		self thread do_AlwaysVSAT();
		if(Notice == 1)
		{
			self iPrintln("^6Always VSAT ^7: [^2On^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Always VSAT ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isAlwaysVSAT = 1;
	}
	else
	{
		self notify("stop_AlwaysVSAT");
		if(Notice == 1)
		{
			self iPrintln("^6Always VSAT ^7: [^1Off^7]");
			self iPrintln("^1Caution ^7: ^3This power will disappear in about 45sec after.");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Always VSAT ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 1, "This power will disappear in about 45sec after.", (1, 1, 1), 0, (0, 0, 0));
		}
		self.isAlwaysVSAT = 0;
	}
}

//-----< 本体 >-----

do_AlwaysVSAT()
{
	self endon("disconnect");
	self endon("stop_AlwaysVSAT");
	for(;;)
	{
		self maps\mp\killstreaks\_spyplane::callsatellite("radardirection_mp");
		wait 40;
	}
}


















