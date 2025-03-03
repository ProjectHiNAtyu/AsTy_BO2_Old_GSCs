FastRestart()
{
	map_restart(0);
}

VCJack()
{
	if(level.isVCJack == 0)
	{
		setmatchtalkflag("EveryoneHearsEveryone", 1);
		self iPrintln("^6VC Jack ^7: [^2On^7]");
		level.isVCJack = 1;
	}
	else
	{
		setmatchtalkflag("EveryoneHearsEveryone", 0);
		self iPrintln("^6VC Jack ^7: [^1Off^7]");
		level.isVCJack = 0;
	}
}

SpawnBot()
{
	self thread init_SpawnBot("autoassign", 1);
}
init_SpawnBot(Team, Notice)
{
	self thread maps/mp/bots/_bot::spawn_bot(Team);
	if(Notice == 1)
		self iPrintln("^6Bot ^7: [^2Spawned^7]");
}

KickAllBots()
{
	self thread init_KickAllBots(1);
}
init_KickAllBots(Notice)
{
	foreach(player in level.players)
	{
		if(isDefined(player.pers["isBot"]) && player.pers["isBot"])
			kick(player getEntityNumber(), "EXE_PLAYERKICKED");
	}
	if(Notice == 1)
		self iPrintln("^6All Bots ^7: [^1Kicked^7]");
}

HomefrontSpawn()
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_HomefrontSpawn");
	for(;;)
	{
		wait 0.2;
		if(self.isHomefrontSpawn == 1)
		{
			self enableInvulnerability();
			weapon = self getCurrentWeapon();
			self takeWeapon(weapon);
			wait 0.1;
			secweapon = self getCurrentWeapon();
			self takeWeapon(secweapon);
			self takeWeapon("knife_mp");
			self hide();
			self freezeControls(1);
			zoomHeight = 5000;
			zoomBack = 4000;
			yaw = 55;
			origin = self.origin;
			self.origin = origin + vector_scale(anglesToForward(self.angles + (0, -180, 0)), zoomBack) + (0, 0, zoomHeight);
			ent = Spawn("script_model", (0, 0, 0));
			ent.angles = self.angles + (yaw, 0, 0);
			ent.origin = self.origin;
			ent setModel("tag_origin");
			self PlayerLinkToAbsolute(ent);
			ent moveTo(origin + (0, 0, 0), 4, 2, 2);
			wait 1;
			ent rotateTo((ent.angles[0] - yaw, ent.angles[1], 0), 3, 1, 1);
			wait 3.5;
			self unlink();
			wait 0.2;
			ent delete();
			self Show();
			self freezeControls(0);
			Camo = RandomIntRange(0, 45);
			self giveWeapon(weapon, 0, true(Camo, 0, 0, 0, 0));
			wait 0.1;
			Camo = RandomIntRange(0, 45);
			self giveWeapon(secweapon, 0, true(Camo, 0, 0, 0, 0));
			self giveWeapon("knife_mp", 0, false);
			self switchToWeapon(weapon);
			self disableInvulnerability();
			wait 0.4;
		}
		self notify("stop_HomefrontSpawn");
	}
}















