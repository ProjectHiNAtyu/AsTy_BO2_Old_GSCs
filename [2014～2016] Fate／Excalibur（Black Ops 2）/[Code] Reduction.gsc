init_NotifySetText(Target, Mode, Word, Color, isGlow, Glow, Time, Use, WordII, ColorII, isGlowII, GlowII)
{
	if(Target == 0)
		self thread do_NotifySetText(Mode, Word, Color, isGlow, Glow, Use, WordII, ColorII, isGlowII, GlowII, Time);
	else
	{
		foreach(player in level.players)
			player thread do_NotifySetText(Mode, Word, Color, isGlow, Glow, Use, WordII, ColorII, isGlowII, GlowII, Time);
	}
}
do_NotifySetText(Mode, Word, Color, isGlow, Glow, Use, WordII, ColorII, isGlowII, GlowII, Time)
{
	if(Mode == 0)
	{
		Font = 2;
		FontII = 1.3;
		Alpha = 1;
		x = -700;
		yI = -150;
		yII = -130;
	}
	else if(Mode == 1)
	{
		Font = 1.5;
		FontII = 0.8;
		Alpha = 0;
		x = 0;
		yI = -20;
		yII = 20;
	}
	else
	{
		Font = 6;
		FontII = 5.5;
		Alpha = 0;
		x = 0;
		yI = -20;
		yII = 20;
	}
	NotifySetText = self createText("default", Font, Word, "CENTER", "CENTER", x, yI, 1000, true, Alpha, Color, isGlow, Glow);
	if(Use == 1)
		NotifySetTextII = self createText("default", FontII, WordII, "CENTER", "CENTER", x, yII, 1000, true, Alpha, ColorII, isGlowII, GlowII);
	wait 0.01;
	
	if(Mode == 0)
	{
		self init_PlaySound(0, "wpn_remote_missile_inc", 0);
		NotifySetText elemMoveX(0.3, 0);
		if(Use == 1)
			NotifySetTextII elemMoveX(0.3, 0);
		wait 1;
		self init_PlaySound(0, "wpn_remote_missile_fire_boost", 0);
	}
	else if(Mode == 1)
	{
		self init_PlaySound(0, "wpn_remote_missile_inc", 0);
		NewTime = Time + 1.6;
		NotifySetText fontIn(1, 1, NewTime, 4);
		if(Use == 1)
			NotifySetTextII fontIn(1, 1, NewTime, 3.3);
		wait 1;
		self init_PlaySound(0, "wpn_remote_missile_fire_boost", 0);
	}
	else
	{
		self init_PlaySound(0, level.heli_sound["crash"], 0);
		NotifySetText fontIn(0.2, 1, 0.2, 2);
		if(Use == 1)
			NotifySetTextII fontIn(0.2, 1, 0.2, 1.5);
		wait 1;
	}
	wait Time;
	if(Mode == 0)
	{
		NotifySetText elemMoveX(0.3, 700);
		if(Use == 1)
			NotifySetTextII elemMoveX(0.3, 700);
	}
	else
	{
		NotifySetText elemFade(0.3, 0);
		if(Use == 1)
			NotifySetTextII elemFade(0.3, 0);
	}
	wait 0.3;
	
	NotifySetText destroy();
	if(Use == 1)
		NotifySetTextII destroy();
	self thread Delete_NotifySetText(NotifySetText);
	if(Use == 1)
		self thread Delete_NotifySetText(NotifySetTextII);
}
Delete_NotifySetText(Text)
{
	self waittill("textset");
	if(self.result >= 225)
	{
		Text ClearAllTextAfterHudElem();
	}
}

optionCalledMesage(titleWord, isNotify, notifyWord, color, time, type)
{
	optionMessage = spawnstruct();
	optionMessage.titleText = titleWord;
	if(isNotify == 1)
		optionMessage.notifyText = notifyWord;
	optionMessage.glowColor = color;
	optionMessage.duration = time;
	optionMessage.font = "objective";
	optionMessage.hideWhenInMenu = false;
	if(type == 0)
		self thread maps\mp\gametypes\_hud_message::notifyMessage(optionMessage);
	else
	{
		foreach(player in level.players)
			player thread maps\mp\gametypes\_hud_message::notifyMessage(optionMessage);
	}
}

init_WelcomeMessage(titleWord, isNotify, notifyWord, color, time, type)
{
	optionMessage = spawnstruct();
	optionMessage.titleText = titleWord;
	if(isNotify == 1)
		optionMessage.notifyText = notifyWord;
	optionMessage.glowColor = color;
	optionMessage.duration = time;
	optionMessage.font = "objective";
	optionMessage.hideWhenInMenu = false;
	if(type == 0)
		self thread maps\mp\gametypes\_hud_message::notifyMessage(optionMessage);
	else
	{
		foreach(player in level.players)
			player thread maps\mp\gametypes\_hud_message::notifyMessage(optionMessage);
	}
}

init_FlightPath(Location, LocationYaw, RightOffset, HalfDistance, RandomHeight, FlyHeight)
{
	Location = Location * (1, 1, 0);
	initialDirection = (0, LocationYaw, 0);
	FlightPath = [];

	if(isDefined(RightOffset) && RightOffset != 0)
		Location = Location + (AnglesToRight(initialDirection) * RightOffset) + (0, 0, RandomInt(RandomHeight));
	startPoint = (Location + (AnglesToForward(initialDirection) * (-1 * HalfDistance)));
	endPoint = (Location + (AnglesToForward(initialDirection) * HalfDistance));
	//if(isDefined(maps/mp/killstreaks/_airsupport::getminimumflyheight()))
		//FlyHeight = maps/mp/killstreaks/_airsupport::getminimumflyheight();
	FlightPath["start"] = startPoint + (0, 0, FlyHeight);
	FlightPath["end"] = endPoint + (0, 0, FlyHeight);

	return FlightPath;
}

init_LocationSelector(Icon, Pad, Teleport, Notice, Word)
{
	if(Icon == 0)
		self beginLocationSelection("map_mortar_selector"); 
	else
		self beginLocationSelection(Icon); 
	self disableOffHandWeapons();
	if(Pad == 1)
	{
		self giveWeapon("killstreak_remote_turret_mp", 0, false);
		self switchToWeapon("killstreak_remote_turret_mp");
	}
	self.selectingLocation = 1; 
	self waittill("confirm_location", location); 
	newLocation = bulletTrace(location + (0, 0, 100000), location, false, self)["position"];
	if(Teleport == 1)
		self setOrigin(newLocation);
	self endLocationSelection();
	self enableOffHandWeapons();
	self switchToWeapon(self maps\mp\_utility::getlastweapon());
	self.selectingLocation = undefined;
	if(Notice == 1)
	{
		if(Teleport != 1 && Word != 0)
			self iPrintln(Word);
		else if(Teleport != 1 && Word == 0)
			self iPrintln("^6Location ^7: [^2Selected ^7| ^5" + newLocation + "^7]");
		else
			self iPrintln("^6Teleport ^7: [^2Clear ^7| ^5" + newLocation + "^7]");
	}
	return newLocation;
}

Vector_Multiply(vec, dif)
{
	vec =(vec[ 0 ] * dif, vec[ 1 ] * dif, vec[ 2 ] * dif);
	return vec;
}

init_GetBestDirection(Location)
{
	checkPitch = -25;
	numChecks = 15;
	startpos = Location + (0, 0, 64);
	bestangle = randomfloat(360);
	bestanglefrac = 0;
	fullTraceResults = [];
	for (i = 0; i < numChecks; i++)
	{
		yaw = ((i * 1.0 + randomfloat(1)) / numChecks) * 360.0;
		angle = (checkPitch, yaw + 180, 0);
		dir = anglesToForward(angle);
		endpos = startpos + dir * 1500;
		trace = bullettrace(startpos, endpos, false, undefined);
		if(trace["fraction"] > bestanglefrac)
		{
			bestanglefrac = trace["fraction"];
			bestangle = yaw;
			if(trace["fraction"] >= 1)
				fullTraceResults[fullTraceResults.size] = yaw;
		}
		if(i % 3 == 0)
			wait .05;
	}
	if(fullTraceResults.size > 0)
		return fullTraceResults[randomint(fullTraceResults.size)];
	return bestangle;
}

init_MoveSpeed(Speed, Origin, MoveTo)
{
        return (Distance(Origin, MoveTo) / Speed);
}

Tag_PlayFX(Type, Effect, Position, Tag, Time, x, y, z, xII, yII, zII)
{
	self endon("disconnect");
	self endon("stop_Tag_PlayFX");
	if(Type != 0)
		FX = LoadFX(Effect);
	else
		FX = Effect;
	FXEntity = Spawn("script_model", self.origin);
	FXEntity SetModel("tag_origin");
	if(Position == 0)
		FXEntity LinkTo(self, Tag, (x, y, z));
	else
		FXEntity LinkTo(self, Tag, (RandomIntRange(x ,xII), RandomIntRange(y, yII),RandomIntRange(z, zII)));
	for(;;)
	{
		PlayFXonTag(FX, self, "tag_origin");
		wait Time;
	}
}

Origin_PlayFX(Type, Effect, Count, Position, Time, Origin, x, y, z, xII, yII, zII)
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_Loop_Origin_PlayFX");

	if(Type == 1)
		FX = LoadFX(Effect);
	else
		FX = Effect;

	if(Count == 0)
	{
		for(;;)
		{
			if(Position == 0)
				PlayFX(FX, self.origin + Origin);
			else
				PlayFX(FX, self.origin + (RandomIntRange(x ,xII), RandomIntRange(y, yII),RandomIntRange(z, zII)));
			wait Time;
		}
	}
	else
	{
		for(i = 0; i < Count; i++)
		{
			if(Position == 0)
				PlayFX(FX, self.origin + Origin);
			else
				PlayFX(FX, self.origin + (RandomIntRange(x ,xII), RandomIntRange(y, yII),RandomIntRange(z, zII)));
		}
	}
}

init_PlaySound(Type, Code, Notice)
{
	self endon("death");
	if(Type == 0)
		self playsound(Code);
	else if(Type == 1)
		self playLocalSound(Code);
	else if(Type == 2)
		self playLoopSound(Code);
	else
	{
		foreach(player in level.players)
			player PlaySoundToPlayer(Code, player);
	}
	if(Notice == 1)
		self iPrintln("^6Play Sound ^7: [^5" + Code + "^7]");
}

GetGround()
{
	return bulletTrace(self.origin, self.origin - (0, 0, 100000), false, self)["position"];
}

init_RotateRall(Count, View, Time)
{
	for(i = 0; i < Count; i++)
	{
	       self rotateRoll(View, Time);
	       wait Time;
	}
	self notify("stop_RotateRall");
}
ChangeVision(Type, VisionName, Notice, Word)
{
	if(Type == 0)
	{
		if(VisionName == "Thermal")
			self SetEMPJammed(1);
		else if(VisionName == "EMP")
			self SetInfraredVision(1);
	}
	else if(Type == 1)
	{
		self UseServerVisionSet(true);
		self SetVisionSetforPlayer(VisionName, 0);
	}
	else if(Type == 2)
	{
		VisionSetNaked(VisionName, 1);
		wait 0.01;
	}
	else if(Type == -1)
	{
		self SetEMPJammed(0);
		self SetInfraredVision(0);
		self UseServerVisionSet(0);
		VisionSetNaked("default", 1);
		wait 0.01;
	}

	if(Notice == 1)
		self iPrintln("^6Set Vision ^7: [^5" + Word + "^7]");
}

TraceBullet(Range)
{
	return BulletTrace(self GetEye(), self GetEye() + VectorScale(AnglesToForward(self GetPlayerAngles()), Range), false, self)["position"];
}

ProvideWeapon(WeaponID, Camo, Toggle, Print, Word)
{
	if(Camo == 0)
		self GiveWeapon(WeaponID, 0, false);
	else
		self GiveWeapon(WeaponID, 0, true(Camo, 0, 0, 0, 0));

	if(Toggle == 1)
		self SwitchToWeapon(WeaponID);

	self GiveMaxAmmo(WeaponID);
	self SetWeaponAmmoClip(WeaponID, weaponClipSize(self getCurrentWeapon()));

	if(Print == 1)
	{
		if(Word != "")
		{
			self iPrintln("^6Give Weapon ^7: [^2" + Word + "^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Give Weapon ^7to ^5" + Word, (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		else
		{
			self iPrintln("^6Give Weapon ^7: [^2" + WeaponID + "^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Give Weapon ^7to ^5" + WeaponID, (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
	}
}

init_InvisibleDamageObject(Position, Location, Time, Damage, Owner)
{
	if(Position == 0)
		Position = Owner.origin;
	else if(Position == 1)
		Position = Owner getTagOrigin("tag_weapon_right");

	Object = Spawn("script_model", Position);
	Object.angles = vectorToAngles(Location - Position);
	Object SetModel("tag_origin");
	Object MoveTo(Location, Time);
	wait Time;
	Object RadiusDamage(Object.origin, Damage, Damage, Damage, Owner);
}

vector_scale(vec, scale)
{
	vec = (vec[0] * scale, vec[1] * scale, vec[2] * scale);
	return vec;
}















