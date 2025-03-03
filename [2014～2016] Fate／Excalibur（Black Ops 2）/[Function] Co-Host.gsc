init_UnfairAimbot()
{
	if(self.isUnfairAimbot == 0)
		self thread Change_UnfairAimbot(0, "with Aiming", 1);
	else if(self.isUnfairAimbot == 1)
		self thread Change_UnfairAimbot(0, "without Aiming", 1);
	else if(self.isUnfairAimbot == 2)
		self thread Change_UnfairAimbot(0, "No Scope", 1);
	else if(self.isUnfairAimbot == 3)
		self thread Change_UnfairAimbot(1, "", 1);
}

//-----< 変更処理 >-----

Change_UnfairAimbot(Stop, Type, Notice)
{
	if(Stop == 0)
	{
		self notify("stop_UnfairAimbot");
		self thread do_UnfairAimbot(Type);
		if(Notice == 1)
		{
			if(self.isUnfairAimbot == 0)
				self iPrintln("^6Unfair Aimbot ^7: [^2On^7]");
			self iPrintln("^6Aimbot Type ^7: [^5" + Type + "^7]");
		}
		self.isUnfairAimbot++;
	}
	else
	{
		self notify("stop_UnfairAimbot");
		if(Notice == 1)
			self iPrintln("^6Unfair Aimbot ^7: [^1Off^7]");
		self.isUnfairAimbot = 0;
	}
}

//-----< 本体 >-----

do_UnfairAimbot(Type)
{
	self endon("disconnect");
	self endon("stop_UnfairAimbot");
	for(;;)
	{
		Target = undefined;
		foreach(player in level.players)
		{
			if((player == self) || (!isAlive(player)) || (level.teamBased && self.pers["team"] == player.pers["team"]))
				continue;
			if(isDefined(Target))
			{
				if(closer(self getTagOrigin("j_head"), player getTagOrigin("j_head"), Target getTagOrigin("j_head")))
					Target = player;
			}
			else
				Target = player; 
		}
		if(isDefined(Target)) 
		{
			if(Type == "with Aiming")
			{
				if(self adsButtonPressed())
				{
					self setPlayerAngles(VectorToAngles((Target getTagOrigin("j_head")) - (self getTagOrigin("j_head")))); 
					if(self attackButtonPressed())
						Target thread [[level.callbackPlayerDamage]](self, self, 100, 0, "MOD_HEAD_SHOT", self getCurrentWeapon(), (0, 0, 0), (0, 0, 0), "head", 0, 0);
				}
			}
			else if(Type == "without Aiming")
			{
				if(self adsButtonPressed())
				{
					if(self attackButtonPressed())
						Target thread [[level.callbackPlayerDamage]](self, self, 100, 0, "MOD_RIFLE_BULLET", self getCurrentWeapon(), (0, 0, 0), (0, 0, 0), "head", 0, 0);
				}
			}
			else if(Type == "No Scope")
			{
				if(self attackButtonPressed())
				{
					self setPlayerAngles(VectorToAngles((Target getTagOrigin("j_head")) - (self getTagOrigin("j_head"))));
					Target thread [[level.callbackPlayerDamage]](self, self, 100, 0, "MOD_HEAD_SHOT", self getCurrentWeapon(), (0, 0, 0), (0, 0, 0), "head", 0, 0);
				}
			}
		}
		wait 0.01;
	}
}















