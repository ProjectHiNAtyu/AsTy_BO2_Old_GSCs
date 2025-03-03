JerichoMissiles()
{
	self thread init_JerichoMissiles(30, 1);
}
init_JerichoMissiles(Round, Notice)
{
	self endon("Launch_JerichoMissiles");
	if(Notice == 1)
	{
		self iPrintln("^6Jericho Missiles ^7: [^2Ready^7]");
		self iPrintln("^4Fire [{+attack}] ^7: ^3Pointing the Missile Location.");
		if(self.NoticeTextMode == 1)
			self thread init_NotifySetText(0, 2, "^6Jericho Missiles ^7is ^2Loaded.", (1, 1, 1), 1, (0, 0, 1), 2, 1, "Fire [{+attack}] to ^3Pointing the Missile Location. ^7| Count =" + Round, (1, 1, 1), 0, (1, 1, 1));
	}
	FX = LoadFX("misc/fx_equip_tac_insert_light_grn");
	Fired = 0;
	Count = Round;
	while(Fired != Count)
	{
		self waittill("weapon_fired");
		Target = self TraceBullet(1000000);
		Green = SpawnFX(FX, Target, (0, 0, 1), (1, 0, 0));
		triggerFx(Green);
		self thread do_JerichoMissiles(Target, Green);
		Fired++;
		Rest = Count - Fired;
		if(Notice == 1)
			self iPrintln("^4Jericho Missiles Counter ^7: [^3" + Rest + "^7]");
	}
	if(Notice == 1)
	{
		self iPrintln("^4Announce ^7: ^3All missile paths initialized.");
		self iPrintln("^4Fire [{+attack}] ^7: ^3Launch the Missiles.");
		if(self.NoticeTextMode == 1)
			self thread init_NotifySetText(0, 2, "All missile paths initialized.", (1, 1, 1), 1, (0, 0, 1), 2, 1, "Fire [{+attack}] to ^3Launch the Missiles.", (1, 1, 1), 0, (1, 1, 1));
	}
	self waittill("weapon_fired");
	if(level.NoticeMode == 1)
	{
		if(level.AllNoticeTextMode == 0)
			self thread optionCalledMesage("Jericho Missiles is Incoming!", 0, "", (0, 1, 0), 6, 1);
		else
			self thread init_NotifySetText(1, 1, "Jericho Missiles is Incoming!", (1, 1, 1), 1, (1, 0, 0), 2, 0);
	}
	self notify("Launch_JerichoMissiles");
}
do_JerichoMissiles(Target, Green)
{
	self endon("stop_JerichoMissiles");
	FX = LoadFX("misc/fx_equip_tac_insert_light_red");
	self waittill("Launch_JerichoMissiles");
	Green delete();
	Red = SpawnFX(FX, Target, (0, 0, 1), (1, 0, 0));
	triggerFx(Red);

	xy = RandomIntRange(-3500, 3500);
	SpawnPos = Target + (xy, xy, 5000);
	Missile = Spawn("script_model", SpawnPos);
	Missile SetModel("projectile_sidewinder_missile");
	Missile.angles = Missile.angles + (90, 90, 90);
	Missile.killcament = Missile;
	Missile RotateTo(VectorToAngles(Target - Missile.origin), 0.01);
	wait 0.01;
	EndPos = BulletTrace(Missile.origin, Target, false, self)["position"];
	Missile MoveTo(EndPos, 3);
	wait 3;
	Missile PlaySound("wpn_rocket_explode");
	PlayFX(level.remote_mortar_fx["missileExplode"], Missile.origin + (0, 0, 1));  
	Missile RadiusDamage(Missile.origin, 450, 700, 350, self, "MOD_PROJECTILE_SPLASH", "remote_missile_bomblet_mp");
	wait 0.05;
	Missile delete(); 
	Red delete();
	wait 0.05;
	self notify("stop_JerichoMissiles");
}















