
UnlimitedKillstreaks()
{
	self thread init_UnlimitedKillstreaks(1);
}
init_UnlimitedKillstreaks(Notice)
{
	if(self.isUnlimitedKillstreaks == 0)
	{
		self thread do_UnlimitedKillstreaks();
		if(Notice == 1)
		{
			self iPrintln("^6Unlimited Killstreaks ^7: [^2On^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Unlimited Killstreaks ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isUnlimitedKillstreaks = 1;
	}
	else
	{
		self notify("stop_UnlimitedKillstreaks");
		if(Notice == 1)
		{
			self iPrintln("^6Unlimited Killstreaks ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Unlimited Killstreaks ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isUnlimitedKillstreaks = 0;
	}
}
do_UnlimitedKillstreaks()
{
	self endon("disconnect");
	self endon("stop_UnlimitedKillstreaks");
	for(;;)
	{
		maps/mp/gametypes/_globallogic_score::_setplayermomentum(self, 9999);
		wait 10;
	}
}

KamikazeBomber()
{
	self thread init_KamikazeBomber(1);
}
init_KamikazeBomber(Notice)
{	
 	Location = init_LocationSelector(0, 1, 0, 0, 0);
	if(Notice == 1)
	{
		if(level.NoticeMode == 0)
			self iPrintln("^6Kamikaze Bomber ^7: [^2Request^7]");
		else
		{
			if(level.AllNoticeTextMode == 0)
				self thread optionCalledMesage("Kamikaze Bomber is Incoming!", 0, "", (1, 0, 0), 7, 1);
			else
				self thread init_NotifySetText(1, 1, "Kamikaze Bomber is Incoming!", (1, 1, 1), 1, (1, 0, 0), 2, 0);
		}
	}

	x = randomIntRange(-30000, 30000);
	y = randomIntRange(-20000, 20000);
	z = randomIntRange(25000, 30000);
	Kamikaze = spawn("script_model", self.origin + (x, y, z));
	Kamikaze setModel("veh_t6_air_fa38_killstreak");
	Kamikaze.angles = vectorToAngles(Location - (self.origin + (x, y, z)));
	Kamikaze.currentstate = "ok";
	Kamikaze.killCamEnt = Kamikaze;
	Kamikaze moveto(Location, 3.5);
	Kamikaze playsound("mpl_lightning_flyover_boom");

	playFxOnTag(level.chopper_fx["damage"]["light_smoke"], Kamikaze, "tag_origin");
	wait 3.6;
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin);
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin + (400, 0, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin + (0, 400, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin + (400, 400, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin + (0, 0, 400));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin - (400, 0, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin - (0, 400, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin - (400, 400, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin + (0, 0, 800));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin + (200, 0, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin + (0, 200, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin + (200, 200, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin + (0, 0, 200));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin - (200, 0, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin - (0, 200, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin - (200, 200, 0));
	playFX(level.chopper_fx["explode"]["large"], Kamikaze.origin + (0, 0, 200));
	Kamikaze playsound(level.heli_sound["crash"]);
	Kamikaze RadiusDamage(Kamikaze.origin, 1000, 1000, 1000, self);
	Earthquake(0.4, 5, Kamikaze.origin, 1000);
	Kamikaze delete();
	return Kamikaze;
}

StrafeRun()
{
	self thread init_StrafeRun(1);
}
init_StrafeRun(Notice)
{ 
	if(level.isStrafeRun == 0)
	{
		level.isStrafeRun = 1;
		Location = init_LocationSelector(0, 1, 0, 0, 0);
		if(Notice == 1)
		{
			if(level.NoticeMode == 0)
				self iPrintln("^6Starfe Run ^7: [^2Request^7]");
			else
			{
				if(level.AllNoticeTextMode == 0)
					self thread optionCalledMesage("Starfe Run is Incoming!", 0, "", (1, 0, 0), 7, 1);
				else
					self thread init_NotifySetText(1, 1, "Starfe Run is Incoming!", (1, 1, 1), 1, (1, 0, 0), 2, 0);
			}
		}

		locationYaw = 180;
		flightPath1 = init_FlightPath(Location, locationYaw, 0, 12000, 300, 1500);
		flightPath2 = init_FlightPath(Location, locationYaw, -620, 12000, 300, 1500);  
		flightPath3 = init_FlightPath(Location, locationYaw, 620, 12000, 300, 1500); 
		flightPath4 = init_FlightPath(Location, locationYaw, -1140, 12000, 300, 1500); 
		flightPath5 = init_FlightPath(Location, locationYaw, 1140, 12000, 300, 1500); 

		level thread Think_StrafeRun(self, flightPath1);
		wait 0.3;
		level thread Think_StrafeRun(self, flightPath2); 
		level thread Think_StrafeRun(self, flightPath3);
		wait 0.3;
		level thread Think_StrafeRun(self, flightPath4); 
		level thread Think_StrafeRun(self, flightPath5);
		wait 60;
		level.isStrafeRun = 0;
	}
	else
		self iPrintln("^1Caution ^7: ^3Strafe Run is still active.");
}
Think_StrafeRun(owner, flightPath)
{
	level endon("game_ended");

	if (!isDefined(owner)) 
	return; 

	forward = vectorToAngles(flightPath["end"] - flightPath["start"]);
	StrafeHeli = Spawn_StrafeRun(owner, flightPath["start"], forward);
	StrafeHeli thread Attack_StrafeRun();

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
Attack_StrafeRun()
{ 
	self endon("chopperdone");
	self setVehWeapon(self.defaultweapon);
	for(;;)
	{
		for (i = 0; i < level.players.size; i++)
		{
			if(Target_StrafeRun(level.players[i]))
			{
				self setturrettargetent(level.players[i]);
				self FireWeapon("tag_flash", level.players[i]);
			}
		}
		wait 0.5;
	}
}
Spawn_StrafeRun(owner, origin, angles)
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
Target_StrafeRun(player)
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

SuicideLodeStar()
{
	self thread init_SuicideLodeStar(1);
}
init_SuicideLodeStar(Notice)
{
	Location = init_LocationSelector(0, 1, 0, 0, 0);
	self thread do_SuicideLodeStar(self, Location);
	if(Notice == 1)
	{
		if(level.NoticeMode == 0)
			self iPrintln("^6Suicide LodeStar ^7: [^2Request^7]");
		else
		{
			if(level.AllNoticeTextMode == 0)
				self thread optionCalledMesage("Suicide LodeStar is Incoming!", 0, "", (1, 0, 0), 7, 1);
			else
				self thread init_NotifySetText(1, 1, "Suicide LodeStar is Incoming!", (1, 1, 1), 1, (1, 0, 0), 2, 0);
		}
	}
}
do_SuicideLodeStar(owner, start1)
{
	start = start1 + (0, 0, 10000);
	end = start1;
	spinToEnd = Vectortoangles(end - start);
	LodeStar = SpawnPlane(owner, "script_model", start);
	LodeStar setModel("veh_t6_drone_pegasus_mp");
	LodeStar.angles = spinToend;
	LodeStar init_PlaySound(2, "mpl_lightning_flyover_boom", 0);
	LodeStar endon("death");
	LodeStar thread Origin_PlayFX(1, "maps/mp_maps/fx_mp_exp_rc_bomb", 0, 0, 0.1, (0, 0, 60));
	LodeStar thread init_RotateRall(10, 360, 2);

	time = init_MoveSpeed(4000, end, start);
	LodeStar moveTo(end, time);
	wait time - 0.05;
	LodeStar.angles = spinToend;
	Earthquake(1, 5, end, 8000);
	wait 0.5;
	LodeStar thread Origin_PlayFX(1, "weapon/emp/fx_emp_explosion", 1, 0, 0, (0, 0, 0));
	wait 0.5;
	LodeStar RadiusDamage(end, 1000000, 1000000, 999999, owner);
	self thread init_PlaySound(3, "wpn_c4_activate_plr", 0);
	self thread init_PlaySound(3, "evt_helicopter_spin_start", 0);
	self thread init_PlaySound(3, "wpn_a10_drop_chaff", 0);
	LodeStar notify("stop_Origin_PlayFX");
	wait 0.1;
	LodeStar delete();
}

SuperFlyingBomber()
{
	self thread init_SuperFlyingBomber(1);
}
init_SuperFlyingBomber(Notice)
{
	if(self.isSuperFlyingBomber == 0)
	{
		self thread do_SuperFlyingBomber();
		if(Notice == 1)
		{
			if(level.NoticeMode == 0)
				self iPrintln("^6Super Flying Bomber ^7: [^2Request^7]");
			else
			{
				if(level.AllNoticeTextMode == 0)
					self thread optionCalledMesage("Super Flying Bomber is Incoming!", 0, "", (1, 0, 0), 7, 1);
				else
					self thread init_NotifySetText(1, 1, "Super Flying Bomber is Incoming!", (1, 1, 1), 1, (1, 0, 0), 2, 0);
			}
		}
		self.isSuperFlyingBomber = 1;
	}
	else
		self iPrintln("^1Caution ^7: ^3Super Flying Bomber is still active.");
}
do_SuperFlyingBomber()
{
	Center = maps\mp\gametypes\_spawnlogic::findBoxCenter(level.spawnMins, level.spawnMaxs);

	Object_SuperFlyingBomber = Spawn("script_model", Center);
	Object_SuperFlyingBomber SetModel("veh_t6_air_fa38_killstreak");
	Object_SuperFlyingBomber.angles =(0, 115, 0);
	Object_SuperFlyingBomber Hide();

	self thread move_SuperFlyingBomber(Object_SuperFlyingBomber);
}
move_SuperFlyingBomber(Object)
{
	self endon("disconnect");
	self endon("stop_SuperFlyingBomber");

	Plane_Object = Spawn("script_model", Object getTagOrigin("tag_origin"));
	Plane_Object SetModel("veh_t6_air_fa38_killstreak");
	Angle = RandomInt(360);
	RadiusOffset = RandomInt(2000) + 5000;
	xOffset = cos(Angle) * RadiusOffset;
	yOffset = sin(Angle) * RadiusOffset;
	zOffset = RandomIntRange(3000, 5000);
	AngleVector = VectorNormalize((xOffset, yOffset, zOffset));
	AngleVector2 = Vector_Multiply(AngleVector, RandomIntRange(6000, 7000));
	Plane_Object LinkTo(Object, "tag_origin", AngleVector2, (0, Angle - 90, 0));

	self thread attack_SuperFlyingBomber(Plane_Object);

	for(;;)
	{
		Object RotateYaw(-360, 30);
		wait(30);
	}
}
attack_SuperFlyingBomber(Object)
{
	self endon("disconnect");
	self endon("stop_SuperFlyingBomber");

	Bullet = "remote_missile_bomblet_mp";
	TimeOut = 30;

	self thread timeLimit_SuperFlyingBomber(Object, TimeOut);

	for(;;)
	{
		foreach(player in level.players)
		{
			if(level.teambased)
			{
				if((player != self) && (player.pers["team"] != self.pers["team"]))
					if(isAlive(player))
						MagicBullet(Bullet, Object.origin, player.origin, self);
			}
			else
			{
				if(player!= self)
					if(isAlive(player))
						MagicBullet(Bullet, Object.origin, player.origin, self);
			}
			wait 0.3;
		}
	}
}
timeLimit_SuperFlyingBomber(Object, Time)
{
	wait Time;
	self notify("stop_SuperFlyingBomber");
	Object delete();
	self iPrintln("^6Super Flying Bomber ^7: [^1Ended^7]");
	self.isSuperFlyingBomber = 0;
}

AGRArmy()
{
	self thread init_AGRArmy(1);
}
init_AGRArmy(Notice)
{
	if(level.isAGRArmy == 0)
	{
		level.isAGRArmy = 1;

		for(i = 0; i < 6; i++)
		{
			drone = spawnvehicle("veh_t6_drone_tank", "talon", "ai_tank_drone_mp", self.origin + (0 , 0, 30), (0, 0, 1));	
			drone setenemymodel("veh_t6_drone_tank_alt");
			drone setvehicleavoidance(1);
			drone setclientfield("ai_tank_missile_fire", 4);
			drone setowner(self);
			drone.owner = self;
			drone.team = self.team;
			drone.aiteam = self.team;
			drone.type = "tank_drone";
			drone setteam(self.team);
			drone maps/mp/_entityheadicons::setentityheadicon(drone.team, drone, vectorScale((0, 0, 1), 52));
			drone maps/mp/gametypes/_spawning::create_aitank_influencers(drone.team);
			drone.controlled = 0;
			drone makevehicleunusable();
			drone.numberrockets = 99;
			drone.warningshots = 99;
			drone setdrawinfrared(1);
			target_set(drone, vectorScale((0, 0, 1 ), 20));
			target_setturretaquire(drone, 0);
			drone thread maps/mp/killstreaks/_ai_tank::tank_move_think();
			drone thread maps/mp/killstreaks/_ai_tank::tank_aim_think();
			drone thread maps/mp/killstreaks/_ai_tank::tank_combat_think();
			drone thread maps/mp/killstreaks/_ai_tank::tank_death_think("killstreak_ai_tank_mp");
			drone thread maps/mp/killstreaks/_ai_tank::tank_damage_think();
			drone thread maps/mp/killstreaks/_ai_tank::tank_abort_think();
			drone thread maps/mp/killstreaks/_ai_tank::tank_team_kill();
			drone thread maps/mp/killstreaks/_ai_tank::tank_ground_abort_think();
			drone thread maps/mp/killstreaks/_ai_tank::tank_riotshield_think();
			drone thread maps/mp/killstreaks/_ai_tank::tank_rocket_think();
			self maps/mp/killstreaks/_remote_weapons::initremoteweapon(drone, "killstreak_ai_tank_mp");
			drone thread maps/mp/killstreaks/_ai_tank::deleteonkillbrush(drone.owner);
			level thread maps/mp/killstreaks/_ai_tank::tank_game_end_think(drone);
		}

		if(Notice == 1)
		{
			if(level.NoticeMode == 0)
				self iPrintln("^6AGR Army ^7: [^2Active^7]");
			else
			{
				if(level.AllNoticeTextMode == 0)
					self thread optionCalledMesage("AGR Army is Incoming!", 0, "", (0, 1, 0), 6, Target);
				else
					self thread init_NotifySetText(1, 1, "AGR Army is Incoming!", (1, 1, 1), 1, (1, 0, 0), 2, 0);
			}
		}
		wait 120;
		level.isAGRArmy = 0;
	}
	else
		self iPrintln("^1Caution ^7: ^3AGR Army is still active.");
}

StuntPlane()
{
	self thread init_StuntPlane(1);
}
init_StuntPlane(Notice)
{
	if(self.isStuntPlane == 0)
	{
		Location = init_LocationSelector(0, 1, 0, 0, 0);
		if(Notice == 1)
		{
			if(level.NoticeMode == 0)
				self iPrintln("^6Stunt Plane ^7: [^2Request^7]");
			else
			{
				if(level.AllNoticeTextMode == 0)
					self thread optionCalledMesage("Stunt Plane is Holding!", 0, "", (1, 0, 0), 7, 1);
				else
					self thread init_NotifySetText(1, 1, "Stunt Plane is Holding!", (1, 1, 1), 1, (1, 0, 0), 2, 0);
			}
		}
		locationYaw = init_GetBestDirection(Location);
		flightPath = init_FlightPath(Location, locationYaw, 0, 12000, 300, 3500);
		self thread do_StuntPlane(self, flightPath, Location);
		self.isStuntPlane = 1;
	}
	else
		self iPrintln("^1Caution ^7: ^3Stunt Plane is still active.");
}
do_StuntPlane(owner, flightPath, location)
{
	if(!isDefined(owner))
		return;
	start = flightpath["start"];
	end = flightpath["end"];
	middle = location + (0, 0, 3500);

	spinTostart = VectorToAngles(flightPath["start"] - flightPath["end"]);
	spinToEnd = VectorToAngles(flightPath["end"] - flightPath["start"]);

	lb = SpawnPlane(owner, "script_model", start);
	lb setModel("veh_t6_drone_pegasus_mp");
	lb.angles = spinToend;
	lb playLoopSound("mpl_lightning_flyover_boom");
	lb endon("death");
	lb thread Tag_PlayFX(0, level.fx_cuav_afterburner, 0, "tag_turret", 0.1, 0, 0, 25);
	lb thread init_RotateRall(10, 360, 2);

	time = init_MoveSpeed(1500, end, start);
	lb moveTo(end, time);
	wait time;
	lb.angles = spinToStart;
	lb thread Origin_PlayFX(1, "maps/mp_maps/fx_mp_exp_rc_bomb", 20, 1, 0, 0, -5000, -5000, 1000, 5000, 5000, 2000);
	lb init_PlaySound(0, "fly_betty_explo", 0);
	wait 3;

	time = init_MoveSpeed(1500, lb.origin, middle);
	lb moveTo(middle, time);
	wait time;
	lb thread Origin_PlayFX(1, "maps/mp_maps/fx_mp_exp_rc_bomb", 20, 1, 0, 0, -5000, -5000, 1000, 5000, 5000, 2000);
	lb init_PlaySound(0, "fly_betty_explo", 0);

	lb thread Yaw_StuntPlane();
	lb waittill("stop_Yaw_StuntPlane");

	wait 0.05;

	lb.angles = spinToStart;
	time = init_MoveSpeed(1500, lb.origin, start);
	lb moveTo(start, time);
	wait time;
	lb thread Origin_PlayFX(1, "maps/mp_maps/fx_mp_exp_rc_bomb", 20, 1, 0, 0, -5000, -5000, 1000, 5000, 5000, 2000);
	lb init_PlaySound(0, "fly_betty_explo", 0);
	lb.angles = spinToEnd;
	wait 3;

	time = init_MoveSpeed(1500, lb.origin, middle);
	lb moveTo(middle, time);
	wait time;

	lb thread Pitch_StuntPlane();
	lb waittill("stop_Pitch_StuntPlane");

	wait 0.03;
	lb.angles = spinToEnd;
	time = init_MoveSpeed(1500, lb.origin, end);
	lb thread init_RotateRall(10, 360, 2);
	lb moveTo(end, time);
	wait time;
	lb thread Origin_PlayFX(1, "maps/mp_maps/fx_mp_exp_rc_bomb", 20, 1, 0, 0, -5000, -5000, 1000, 5000, 5000, 2000);
	lb init_PlaySound(0, "fly_betty_explo", 0);

	lb.angles = spinTostart;
	wait 3;

	time = init_MoveSpeed(1500, lb.origin, middle);
	lb moveTo(middle, time);
	wait time;
	wait 0.05;
	lb thread Bomb_StuntPlane(owner);
	wait 0.05;
	lb moveTo(start, time);
	wait time;
	lb notify("stop_Tag_PlayFX");
	self.isStuntPlane = 0;
	lb delete();
}
Yaw_StuntPlane()
{
	move = 80;
	for(i = 0; i < 60; i++)
	{
	       vec = anglesToForward(self.angles);
	       speed = (vec[0] * move, vec[1] * move, vec[2] * move);
	       self moveTo(self.origin + speed, 0.05);
	       self rotateYaw(6, 0.05);
	       wait 0.05;
	}
	for(i = 0;i < 60;i++)
	{
	       vec = anglesToForward(self.angles);
	       speed = (vec[0] * move, vec[1] * move, vec[2] * move);
	       self moveTo(self.origin + speed, 0.05);
	       self rotateYaw(6, 0.05);
	       wait 0.05;
	}
	self notify("stop_Yaw_StuntPlane");
}
Pitch_StuntPlane()
{
	move = 60;
	for(i = 0; i < 60; i++)
	{
	       vec = anglesToForward(self.angles);
	       speed = (vec[0] * move, vec[1] * move, vec[2] * move);
	       self moveTo(self.origin + speed, 0.05);
	       self rotatePitch(-6, 0.05);
	       wait 0.05;
	}
	self notify("stop_Pitch_StuntPlane");
}
Bomb_StuntPlane(owner)
{
	target = GetGround();
	wait 0.05;
	bomb = Spawn("script_model", self.origin - (0, 0, 80));
	bomb SetModel("projectile_sa6_missile_desert_mp");
	bomb.angles = self.angles;
	bomb.KillCamEnt = bomb;

	wait 0.01;
	bomb MoveTo(target, 2);
	bomb RotatePitch(90, 1.8);
	bomb init_PlaySound(0, "wpn_remote_missile_inc", 0);
	bomb thread Origin_PlayFX(1, "maps/mp_maps/fx_mp_exp_rc_bomb", 0, 0, 0.1, (0, 0, 120));
	wait 2;
	EarthQuake(2, 2, target, 2500);
	bomb thread Origin_PlayFX(1, "weapon/emp/fx_emp_explosion", 1, 0, 0, (0, 0, 0));
	foreach(player in level.players)
		player thread init_PlaySound(0, "wpn_emp_bomb", 0);
	bomb RadiusDamage(self.origin, 100000, 100000, 99999, owner);
	bomb notify("stop_Origin_PlayFX");
	wait 0.01;
	bomb delete();
}

init_MW2Nuke()
{
	if(self.isMW2Nuke == 0)
	{
		self thread do_MW2Nuke();
		self iPrintln("^6MW2 Nuke ^7: [^2Request^7]");
		self.isMW2Nuke = 1;
	}
	else
		self iPrintln("^3Nuclear warhead missile ^1is already requested.");
}

//=====[ Nukeの流れ呼び出し ]=====

do_MW2Nuke()
{
	self thread init_NotifySetText(0, 0, "MW2 Nuke Kill Streak!", (1, 1, 1), 1, (0, 1, 0), 6, 1, "Press [{+frag}] for Tactical Nuke.", (1, 1, 1), 1, (1, 1, 1));
	self thread WaitPress_MW2Nuke();
}

//=====[ 入力待機 ]=====

WaitPress_MW2Nuke()
{
	self endon("disconnect");
	self endon("stop_WaitPress_MW2Nuke");
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter(level.spawnMins, level.spawnMaxs);
	self takeallweapons();
	self giveWeapon("satchel_charge_mp", 0, false);
	self setWeaponAmmoStock("satchel_charge_mp", 0);
	self setWeaponAmmoClip("satchel_charge_mp", 0);
	self enableInvulnerability();

	for(;;)
	{
		if(self FragButtonPressed())
		{
			wait 0.7;
			self thread Missile_MW2Nuke(level.mapCenter);
			foreach(player in level.players)
				player thread Countdown_MW2Nuke();
			self notify("stop_WaitPress_MW2Nuke");
		}
		wait 0.05;
	}
}

//=====[ カウントダウン ]=====

Countdown_MW2Nuke()
{
	self endon("disconnect");
	self endon("stop_Countdown_MW2Nuke");
	
	self thread optionCalledMesage("^3Nuclear Missile ^1Incoming!!", 1, "^0Anymore us of fate was exhausted...", (1, 0, 0.502), 7, 0);

	for(num = 10; num > 0; num--)
	{
		self PlaySoundToPlayer("wpn_semtex_alert", self);
		NukeCountdown = self createText("hudbig", 10, num, "CENTER", "CENTER", 0, 0, 1, true, 0, (1, 1, 1), 1, (1, 0.5, 0.2));
		NukeCountdown fontIn(0.1, 1, 0.3, 2.5);
		self thread Delete_NotifySetText(NukeCountdown);
		wait 1;
		if(num > 1)
			NukeCountdown destroy();
	}
	
	wait 0.7;
	NukeCountdown elemFade(0.3, 0);
	wait 0.3;
	NukeCountdown destroy();
	self thread init_PlaySound(0, "wpn_c4_activate_plr", 0);
	self thread init_PlaySound(0, "evt_helicopter_spin_start", 0);
	self thread init_PlaySound(0, "wpn_a10_drop_chaff", 0);
	self notify("stop_Countdown_MW2Nuke");
}

Missile_MW2Nuke(Location)
{
	self endon("disconnect");
	self endon("stop_Missile_MW2Nuke");
	
	MissileLocation = Location;
	for(;;)
	{
		for(i = 0; i <= 6; i++)
		{
			x = randomIntRange(-1000, 1000);
			y = randomIntRange(-1000, 1000);
			z = randomIntRange(20000, 25000);

			level.nukeMissile[i] = spawn("script_model", MissileLocation + (x, y, z));
			level.nukeMissile[i] setModel("projectile_sa6_missile_desert_mp");
			level.nukeMissile[i].angles = (90, 90, 90);
			level.nukeMissile[i] thread Origin_PlayFX(1, "maps/mp_maps/fx_mp_exp_rc_bomb", 0, 0, 0.1, (0, 0, 120));
		}
		wait 0.05;
		for(i = 0; i <= 6; i++)
		{
			level.nukeMissile[i] moveto(level.nukeMissile[i].origin + (0, 0, -20000), 10);
		}
		wait 10.01;
		foreach(nukeMissiles in level.nukeMissile)
		{
			nukeMissiles thread Origin_PlayFX(1, "weapon/emp/fx_emp_explosion", 1, 0, 0, (0, 0, 0));
			Earthquake(0.6, 7, nukeMissiles.origin, 12345);
		}
		foreach(player in level.players)
		{
			player thread init_PlaySound(0, "wpn_emp_bomb", 0);
		}
		wait 0.5;
		setDvar("timescale", "0.9");
		wait 0.6;
		setDvar("timescale", "0.8");
		foreach(player in level.players)
		{
			player thread ChangeVision(2, "remote_mortar_infrared", 0, "");
		}
		wait 0.7;
		setDvar("timescale", "0.7");
		wait 0.8;
		setDvar("timescale", "0.6");
		for(i = 3; i <= 6; i++)
		{
			level.nukeMissile[i] RadiusDamage(level.nukeMissile[i].origin, 20000, 20000, 20000, self);
		}
		foreach(nukeMissiles in level.nukeMissile)
		{
			nukeMissiles notify("stop_Origin_PlayFX");
			nukeMissiles delete();
		}
		wait 0.9;
		setDvar("timescale", "0.5");
		foreach(player in level.players)
			player suicide();
		wait 0.1;
		setDvar("timescale", "0.6");
		wait 0.1;
		setDvar("timescale", "0.7");
		wait 0.1;
		setDvar("timescale", "0.8");
		wait 0.1;
		setDvar("timescale", "0.9");
		wait 0.1;
		setDvar("timescale", "1");
		level thread maps/mp/gametypes/_globallogic::forceend();
		self notify("stop_Missile_MW2Nuke");
	}
}

MOAB()
{
	if(self.isMOAB == 0)
	{
		if(self.NoticeTextMode == 0)
			self thread optionCalledMesage("MW3 M.O.A.B Kill Streak!", 1, "Press [{+frag}] + [{+actionslot 3}] for M.O.A.B.", (0, 1, 0), 8, 0);
		else
			self thread init_NotifySetText(0, 0, "MW3 M.O.A.B Kill Streak!", (1, 1, 1), 1, (0, 1, 0), 6, 1, "Press [{+frag}] + [{+actionslot 3}] for M.O.A.B.", (1, 1, 1), 1, (1, 1, 1));
		self thread Monitor_MOAB();
		self.isMOAB = 1;
	}
	else
		self iPrintln("^1Caution ^7: ^3M.O.A.B is still unused.");
}
Monitor_MOAB()
{
	self endon("disconnect");
	self endon("Start_MOAB");
	for(;;)
	{
		if(self fragButtonPressed() && self actionSlotThreeButtonPressed())
		{
			self thread init_MOAB(1);
			self notify("Start_MOAB");
		}
		wait 0.05;
	}
}
init_MOAB(Notice)
{
	Location = init_LocationSelector(0, 1, 0, 0, 0);
	if(Notice == 1)
	{
		if(level.NoticeMode == 0)
			self iPrintln("^6M.O.A.B ^7: [^2Requested^7]");
		else
		{
			if(level.AllNoticeTextMode == 0)
				self thread optionCalledMesage("M.O.A.B is Incoming!", 0, "", (0, 1, 0), 6, 1);
			else
				self thread init_NotifySetText(1, 1, "M.O.A.B is Incoming!", (1, 1, 1), 1, (1, 0, 0), 2, 0);
		}
	}
	
	self.isMOAB = 0;
	flightPath = init_FlightPath(Location, 0, 0, 17500, 0, 7000);
	Start = flightPath["start"];
	End = flightPath["end"];
	Position = Location + (0, 0, 6920);
	MOABAngle = VectorToAngles(flightPath["end"] - flightPath["start"]);
	
	MOAB = SpawnPlane(self, "script_model", Start);
	MOAB setModel("veh_t6_air_v78_vtol_killstreak");
	MOAB.angles = MOABAngle;
	MOAB playLoopSound("mpl_lightning_flyover_boom");
	MOAB endon("death");
	MOAB thread Tag_PlayFX(0, level.fx_cuav_afterburner, 0, "tag_turret", 0.1, 0, 0, 25);
	
	Time = init_MoveSpeed(1000, Position, Start);
	MOAB moveTo(Position, Time);
	wait Time;
	MOAB thread Bomb_MOAB(self);
	MOAB moveTo(End, Time);
	wait Time;
	MOAB notify("stop_Tag_PlayFX");
	MOAB delete();
}
Bomb_MOAB(Owner)
{
	Ground = GetGround();
	Missile = Spawn("script_model", self.origin - (0, 0, 80));
	Missile SetModel("projectile_sa6_missile_desert_mp");
	Missile.angles = self.angles;
	Missile.KillCamEnt = Missile;
	Missile thread Origin_PlayFX(1, "maps/mp_maps/fx_mp_exp_rc_bomb", 0, 0, 0.1, (0, 0, 120));
	
	Target = Ground + (0, 0, 4000);
	Time = init_MoveSpeed(800, Target, self.origin);
	Missile MoveTo(Target, Time);
	Missile RotatePitch(90, Time);
	Missile init_PlaySound(0, "wpn_remote_missile_inc", 0);
	wait Time;
	
	FinalTarget = Ground + (0, 0, 2000);
	Time = init_MoveSpeed(800, FinalTarget, Missile.origin);
	Missile MoveTo(FinalTarget, Time);
	for(i = 0; i < 20; i++)
	{
		x = randomIntRange(-1500, 1500);
		y = randomIntRange(-1500, 1500);
		RocketTarget = Ground + (x, y, 0);
		Missile thread DiffusionBomb_MOAB(RocketTarget, Time, Owner);	
	}
	wait Time;
	
	EarthQuake(0.6, 5, FinalTarget, 5000);
	Missile thread Origin_PlayFX(1, "weapon/emp/fx_emp_explosion", 1, 0, 0, (0, 0, 0));
	foreach(player in level.players)
		player thread init_PlaySound(0, "wpn_emp_bomb", 0);
	Missile RadiusDamage(Missile.origin, 100000, 100000, 100000, Owner);
	Missile notify("stop_Origin_PlayFX");
	wait 0.2;
	Missile delete();
}
DiffusionBomb_MOAB(Target, Time, Owner)
{
	Rocket = Spawn("script_model", self.origin - (0, 0, 45));
	Rocket SetModel("projectile_sidewinder_missile");
	Rocket.angles = vectorToAngles(Target - Rocket.origin);
	Rocket.KillCamEnt = Rocket;
	
	playFxOnTag(level.chopper_fx["damage"]["light_smoke"], Rocket, "tag_origin");
	Rocket moveTo(Target, Time);
	Rocket RotatePitch(30, Time);
	wait Time;
	
	EarthQuake(0.4, 3, Rocket.origin, 400);
	Rocket thread Origin_PlayFX(0, level.fx_u2_explode, 1, 0, 0, (0, 0, 0));
	Rocket PlaySound(level.heli_sound["crash"]);
	Rocket RadiusDamage(Rocket.origin, 350, 350, 350, Owner);
	wait 0.4;
	Rocket delete();
}

AC130()
{
	if(self.isAC130 == 0)
	{
		if(self.NoticeTextMode == 0)
			self thread optionCalledMesage("MW2 AC-130 Kill Streak!", 1, "Press [{+actionslot 3}] for AC-130.", (0, 1, 0), 8, 0);
		else
			self thread init_NotifySetText(0, 0, "MW2 AC-130 Kill Streak!", (1, 1, 1), 1, (0, 1, 0), 6, 1, "Press [{+actionslot 3}] for AC-130.", (1, 1, 1), 1, (1, 1, 1));
		self thread Monitor_AC130();
		self.isAC130 = 1;
	}
	else
		self iPrintln("^1Caution ^7: ^3AC-130 is still unused.");
}
Monitor_AC130()
{
	self endon("disconnect");
	self endon("stop_Monitor_AC130");
	for(;;)
	{
		if(self actionSlotThreeButtonPressed())
		{
			self.LastLocation_AC130 = self.origin;
			self.LastWeapon_AC130 = self getCurrentWeapon();
			self takeWeapon(self.LastWeapon_AC130);
			wait 0.1;
			self.LastWeapon2_AC130 = self getCurrentWeapon();
			self takeWeapon(self.LastWeapon2_AC130);
			self giveWeapon("killstreak_remote_turret_mp", 0, false);
			self switchToWeapon("killstreak_remote_turret_mp");
			wait 1;
			self.BlackScreen elemFade(0.2, 1);
			wait 0.2;
			self disableOffHandWeapons();
			self takeAllWeapons();
			self Hide();
			self enableInvulnerability();
			self thread init_AC130(1);
			self notify("stop_Monitor_AC130");
		}
		wait 0.05;
	}
}
init_AC130(Notice)
{
	if(Notice == 1)
	{
		if(level.NoticeMode == 0)
			self iPrintln("^6AC-130 ^7: [^2Requested^7]");
		else
		{
			if(level.AllNoticeTextMode == 0)
				self thread optionCalledMesage("AC-130 is Incoming!", 0, "", (0, 1, 0), 6, 1);
			else
				self thread init_NotifySetText(1, 1, "AC-130 is Incoming!", (1, 1, 1), 1, (1, 0, 0), 2, 0);
		}
	}
	
	Center = maps\mp\gametypes\_spawnlogic::findBoxCenter(level.spawnMins, level.spawnMaxs);
	Object_AC130 = Spawn("script_model", Center);
	Object_AC130 SetModel("veh_t6_air_v78_vtol_killstreak");
	Object_AC130.angles = (0, 115, 0);
	Object_AC130 Hide();
	Player_AC130 = Spawn("script_model", Center);
	Player_AC130 SetModel("tag_origin");
	Player_AC130.angles = (0, 115, 0);
	Player_AC130 Hide();
	self thread Move_AC130(Object_AC130);
	self thread MovePlayer_AC130(Player_AC130);
	self waittill("end_AC130");
	Object_AC130 delete();
	Player_AC130 delete();
}
Move_AC130(Object)
{
	self endon("disconnect");
	self endon("stop_AC130");
	Plane_AC130 = Spawn("script_model", Object getTagOrigin("tag_origin"));
	Plane_AC130 SetModel("veh_t6_air_v78_vtol_killstreak");
	Plane_AC130 thread Tag_PlayFX(0, level.fx_cuav_afterburner, 0, "tag_turret", 0.1, 0, 0, 25);
	Angle = 360; //RandomInt(360)
	RadiusOffset = 8000; //RandomInt(4000) + 7000
	xOffset = cos(Angle) * RadiusOffset;
	yOffset = sin(Angle) * RadiusOffset;
	zOffset = 5200; //RandomIntRange(5000, 7000)
	AngleVector = VectorNormalize((xOffset, yOffset, zOffset));
	AngleVector2 = Vector_Multiply(AngleVector, 7500); //RandomIntRange(8000, 9000)
	Plane_AC130 LinkTo(Object, "tag_origin", AngleVector2, (0, Angle - 90, 0));
	for(;;)
	{
		Object RotateYaw(-360, 60);
		wait 60;
		self notify("end_AC130");
		Plane_AC130 notify("stop_Tag_PlayFX");
		Plane_AC130 delete();
		self notify("stop_AC130");
	}
}
MovePlayer_AC130(Object)
{
	self endon("disconnect");
	self endon("stop_Player_AC130");
	HidePlayer = Spawn("script_model", Object getTagOrigin("tag_origin"));
	HidePlayer SetModel("tag_origin");
	Angle = 360; //RandomInt(360)
	RadiusOffset = 8100; //RandomInt(4000) + 7000
	xOffset = cos(Angle) * RadiusOffset;
	yOffset = sin(Angle) * RadiusOffset;
	zOffset = 5150; //RandomIntRange(5000, 7000)
	AngleVector = VectorNormalize((xOffset, yOffset, zOffset));
	AngleVector2 = Vector_Multiply(AngleVector, 7360); //RandomIntRange(8000, 9000)
	HidePlayer LinkTo(Object, "tag_origin", AngleVector2, (0, Angle - 90, 0));
	self.BlackScreen elemFade(0.5, 0);
	self PlayerLinkTo(HidePlayer, undefined);
	self thread Weapon_AC130();
	for(;;)
	{
		Object RotateYaw(-360, 60);
		wait 60;
		self thread Delete_AC130TargetDesign();
		HidePlayer delete();
		self unlink();
		self.BlackScreen elemFade(0.2, 1);
		wait 0.2;
		self.BlackScreen elemFade(0.2, 0);
		self setOrigin(self.LastLocation_AC130);
		self enableOffHandWeapons();
		self thread ProvideWeapon(self.LastWeapon_AC130, 0, 1, 0, "");
		self thread ProvideWeapon(self.LastWeapon2_AC130, 0, 0, 0, "");
		self thread ProvideWeapon("knife_mp", 0, 0, 0, "");
		self Show();
		self setClientFOV(65);
		self.isAC130 = 0;
		self notify("stop_Player_AC130");
	}
}

Weapon_AC130()
{
	self endon("disconnect");
	self endon("end_AC130");
	self.isWeapon_AC130 = 0;
	self.Max_WeaponAC130 = 70;
	self.Count_WeaponAC130 = 0;
	self.Charge_WeaponAC130 = 0;
	self.SelectWeapon_AC130 = "straferun_gun_mp";
	self.WaitTime_AC130 = 0.05;
	self setClientFOV(20);
	self thread Design25mm_AC130();
	for(;;)
	{
		if(self changeSeatButtonPressed())
		{
			self thread Delete_AC130TargetDesign();
			if(self.isWeapon_AC130 == 0)
			{
				self thread Design40mm_AC130();
				self.SelectWeapon_AC130 = "ai_tank_drone_rocket_mp";
				self.WaitTime_AC130 = 0.5;
				self.Max_WeaponAC130 = 10;
				self.Count_WeaponAC130 = 0;
				self.Charge_WeaponAC130 = 0;
				self setClientFOV(35);
				self.isWeapon_AC130++;
				wait 0.5;
			}
			else if(self.isWeapon_AC130 == 1)
			{
				self thread Design105mm_AC130();
				self.SelectWeapon_AC130 = "remote_missile_bomblet_mp";
				self.WaitTime_AC130 = 3;
				self.Max_WeaponAC130 = 1;
				self.Count_WeaponAC130 = 0;
				self.Charge_WeaponAC130 = 0;
				self setClientFOV(50);
				self.isWeapon_AC130++;
				wait 0.5;
			}
			else if(self.isWeapon_AC130 == 2)
			{
				self thread Design105mm_AC130();
				self.SelectWeapon_AC130 = "remote_missile_bomblet_mp";
				self.WaitTime_AC130 = 0.05;
				self.Max_WeaponAC130 = 99999999;
				self.Count_WeaponAC130 = 0;
				self.Charge_WeaponAC130 = 0;
				self setClientFOV(50);
				self.isWeapon_AC130++;
				wait 0.5;
			}
			else if(self.isWeapon_AC130 == 3)
			{
				self thread Design25mm_AC130();
				self.SelectWeapon_AC130 = "straferun_gun_mp";
				self.WaitTime_AC130 = 0.05;
				self.Max_WeaponAC130 = 70;
				self.Count_WeaponAC130 = 0;
				self.Charge_WeaponAC130 = 0;
				self setClientFOV(20);
				self.isWeapon_AC130 = 0;
				wait 0.5;
			}
		}
		if(self attackButtonPressed())
		{
			if(self.Max_WeaponAC130 >= self.Count_WeaponAC130 && self.Charge_WeaponAC130 == 0)
			{
				MagicBullet(self.SelectWeapon_AC130, self getEye(), self TraceBullet(1000000), self);
				self.Count_WeaponAC130++;
				wait self.WaitTime_AC130;
				if(self.Max_WeaponAC130 == self.Count_WeaponAC130)
					self.Charge_WeaponAC130 = 1;
			}
			else
			{
				self.Count_WeaponAC130--;
				wait self.WaitTime_AC130;
				if(self.Count_WeaponAC130 == 0)
					self.Charge_WeaponAC130 = 0;
			}
		}
		wait 0.05;
	}
}

Delete_AC130TargetDesign()
{
	self.AC130_25mm destroy();
	self.AC130_25mm_2 destroy();
	self.AC130_25mm_3 destroy();
	self.AC130_25mm_4 destroy();
	self.AC130_25mm_5 destroy();
	self.AC130_25mm_6 destroy();
	self.AC130_25mm_7 destroy();
	self.AC130_25mm_8 destroy();
	self.AC130_25mm_9 destroy();
	self.AC130_25mm_10 destroy();
	self.AC130_25mm_11 destroy();
	self.AC130_45mm destroy();
	self.AC130_45mm_1 destroy();
	self.AC130_45mm_2 destroy();
	self.AC130_45mm_3 destroy();
	self.AC130_45mm_4 destroy();
	self.AC130_45mm_5 destroy();
	self.AC130_45mm_6 destroy();
	self.AC130_45mm_7 destroy();
	self.AC130_45mm_8 destroy();
	self.AC130_45mm_9 destroy();
	self.AC130_45mm_10 destroy();
	self.AC130_45mm_11 destroy();
	self.AC130_45mm_12 destroy();
	self.AC130_45mm_13 destroy();
	self.AC130_45mm_14 destroy();
	self.AC130_45mm_15 destroy();
	self.AC130_45mm_16 destroy();
	self.AC130_45mm_17 destroy();
	self.AC130_45mm_18 destroy();
	self.AC130_45mm_19 destroy();
	self.AC130_105mm destroy();
	self.AC130_105mm_1 destroy();
	self.AC130_105mm_2 destroy();
	self.AC130_105mm_3 destroy();
	self.AC130_105mm_4 destroy();
	self.AC130_105mm_5 destroy();
	self.AC130_105mm_6 destroy();
	self.AC130_105mm_7 destroy();
	self.AC130_105mm_8 destroy();
	self.AC130_105mm_9 destroy();
	self.AC130_105mm_10 destroy();
	self.AC130_105mm_11 destroy();
	self.AC130_105mm_12 destroy();
	self.AC130_105mm_13 destroy();
	self.AC130_105mm_14 destroy();
	self.AC130_105mm_15 destroy();
}
Design25mm_AC130()
{
	self.AC130_25mm = self createRectangle("CENTER", "CENTER", -35, -50, "white", 30, 1, (1, 1, 1), 1, 1);
	self.AC130_25mm_2 = self createRectangle("CENTER", "CENTER", -50, -35, "white", 1, 30, (1, 1, 1), 1, 1);
	self.AC130_25mm_3 = self createRectangle("CENTER", "CENTER", 35, -50, "white", 30, 1, (1, 1, 1), 1, 1);
	self.AC130_25mm_4 = self createRectangle("CENTER", "CENTER", 50, -35, "white", 1, 30, (1, 1, 1), 1, 1);
	self.AC130_25mm_5 = self createRectangle("CENTER", "CENTER", -35, 50, "white", 30, 1, (1, 1, 1), 1, 1);
	self.AC130_25mm_6 = self createRectangle("CENTER", "CENTER", -50, 35, "white", 1, 30, (1, 1, 1), 1, 1);
	self.AC130_25mm_7 = self createRectangle("CENTER", "CENTER", 35, 50, "white", 30, 1, (1, 1, 1), 1, 1);
	self.AC130_25mm_8 = self createRectangle("CENTER", "CENTER", 50, 35, "white", 1, 30, (1, 1, 1), 1, 1);
	self.AC130_25mm_9 = self createRectangle("CENTER", "CENTER", -10, 0, "white", 15, 1, (1, 1, 1), 1, 1);
	self.AC130_25mm_10 = self createRectangle("CENTER", "CENTER", 10, 0, "white", 15, 1, (1, 1, 1), 1, 1);
	self.AC130_25mm_11 = self createRectangle("CENTER", "CENTER", 0, 20, "white", 1, 35, (1, 1, 1), 1, 1);
}
Design40mm_AC130()
{
	self.AC130_45mm = self createRectangle("CENTER", "CENTER", -75, 0,"white", 120, 1, (1, 1, 1), 1, 1);
	self.AC130_45mm_1 = self createRectangle("CENTER", "CENTER", 75, 0, "white", 120, 1, (1, 1, 1), 1, 1);
	self.AC130_45mm_2 = self createRectangle("CENTER", "CENTER", 0, -75, "white", 1, 120, (1, 1, 1), 1, 1);
	self.AC130_45mm_3 = self createRectangle("CENTER", "CENTER", 0, 75,"white", 1, 120, (1, 1, 1), 1, 1);
	self.AC130_45mm_4 = self createRectangle("CENTER", "CENTER", -135, 0,"white", 2, 20, (1, 1, 1), 1, 1);
	self.AC130_45mm_5 = self createRectangle("CENTER", "CENTER", 135, 0,"white", 2, 20, (1, 1, 1), 1, 1);
	self.AC130_45mm_6 = self createRectangle("CENTER", "CENTER", 0, -135,"white", 20, 2, (1, 1, 1), 1, 1);
	self.AC130_45mm_7 = self createRectangle("CENTER", "CENTER", 0, 135,"white", 20, 2, (1, 1, 1), 1, 1);
	self.AC130_45mm_8 = self createRectangle("CENTER", "CENTER", -35, 0,"white", 1, 10, (1, 1, 1), 1, 1);
	self.AC130_45mm_9 = self createRectangle("CENTER", "CENTER", 35, 0,"white", 1, 10, (1, 1, 1), 1, 1);
	self.AC130_45mm_10 = self createRectangle("CENTER", "CENTER", 0, -35,"white", 10, 1, (1, 1, 1), 1, 1);
	self.AC130_45mm_11 = self createRectangle("CENTER", "CENTER", 0, 35,"white", 10, 1, (1, 1, 1), 1, 1);
	self.AC130_45mm_12 = self createRectangle("CENTER", "CENTER", -68, 0,"white", 1, 10, (1, 1, 1), 1, 1);
	self.AC130_45mm_13 = self createRectangle("CENTER", "CENTER", 68, 0,"white", 1, 10, (1, 1, 1), 1, 1);
	self.AC130_45mm_14 = self createRectangle("CENTER", "CENTER", 0, -68,"white", 10, 1, (1, 1, 1), 1, 1);
	self.AC130_45mm_15 = self createRectangle("CENTER", "CENTER", 0, 68,"white", 10, 1, (1, 1, 1), 1, 1);
	self.AC130_45mm_16 = self createRectangle("CENTER", "CENTER", -101, 0,"white", 1, 10, (1, 1, 1), 1, 1);
	self.AC130_45mm_17 = self createRectangle("CENTER", "CENTER", 101, 0,"white", 1, 10, (1, 1, 1), 1, 1);
	self.AC130_45mm_18 = self createRectangle("CENTER", "CENTER", 0, -101,"white", 10, 1, (1, 1, 1), 1, 1);
	self.AC130_45mm_19 = self createRectangle("CENTER", "CENTER", 0, 101,"white", 10, 1, (1, 1, 1), 1, 1);
}
Design105mm_AC130()
{
	self.AC130_105mm = self createRectangle("CENTER", "CENTER", 25, 0,"white", 2, 33, (1, 1, 1), 1, 1); 
	self.AC130_105mm_1 = self createRectangle("CENTER", "CENTER", -25, 0,"white", 2, 33, (1, 1, 1), 1, 1); 
	self.AC130_105mm_2 = self createRectangle("CENTER", "CENTER", 0, -16,"white", 50, 2, (1, 1, 1), 1, 1);
	self.AC130_105mm_3 = self createRectangle("CENTER", "CENTER", 0, 16,"white", 50, 2, (1, 1, 1), 1, 1);
	self.AC130_105mm_4 = self createRectangle("CENTER", "CENTER", 0, -44,"white", 2, 57, (1, 1, 1), 1, 1);
	self.AC130_105mm_5 = self createRectangle("CENTER", "CENTER", 0, 44,"white", 2, 57, (1, 1, 1), 1, 1);
	self.AC130_105mm_6 = self createRectangle("CENTER", "CENTER", -53, 0,"white", 57, 2, (1, 1, 1), 1, 1);
	self.AC130_105mm_7 = self createRectangle("CENTER", "CENTER", 53, 0,"white", 57, 2, (1, 1, 1), 1, 1);
	self.AC130_105mm_8 = self createRectangle("CENTER", "CENTER", -155, -122,"white", 2, 21, (1, 1, 1), 1, 1);
	self.AC130_105mm_9 = self createRectangle("CENTER", "CENTER", -155, 122,"white", 2, 21, (1, 1, 1), 1, 1);
	self.AC130_105mm_10 = self createRectangle("CENTER", "CENTER", 155, 122,"white", 2, 21, (1, 1, 1), 1, 1);
	self.AC130_105mm_11 = self createRectangle("CENTER", "CENTER", 155, -122,"white", 2, 21, (1, 1, 1), 1, 1);
	self.AC130_105mm_12 = self createRectangle("CENTER", "CENTER", -145, -132,"white", 21, 2, (1, 1, 1), 1, 1);
	self.AC130_105mm_13 = self createRectangle("CENTER", "CENTER", 145, -132,"white", 21, 2, (1, 1, 1), 1, 1);
	self.AC130_105mm_14 = self createRectangle("CENTER", "CENTER", -145, 132,"white", 21, 2, (1, 1, 1), 1, 1);
	self.AC130_105mm_15 = self createRectangle("CENTER", "CENTER", 145, 132,"white", 21, 2, (1, 1, 1), 1, 1);
}












