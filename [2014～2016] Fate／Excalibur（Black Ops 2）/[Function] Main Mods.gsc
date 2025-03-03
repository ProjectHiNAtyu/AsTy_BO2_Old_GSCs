GodMode()
{
	self thread init_GodMode(1);
}

//-----< 本体 >-----

init_GodMode(Notice)
{
	if(self.isGodMode == 0)
	{
		self thread Fast_GodMode();
		if(Notice == 1)
		{
			self iPrintln("^6God Mode ^7: [^2On^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6God Mode ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isGodMode = 1;
	}
	else
	{
		self notify("stop_GodMode");
		self disableInvulnerability();
		if(Notice == 1)
		{
			self iPrintln("^6God Mode ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6God Mode ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isGodMode = 0;
	}
}

//-----< 処理 >-----

Fast_GodMode()
{
	self endon("disconnect");
	self endon("stop_GodMode");
	for(;;)
	{
		self enableInvulnerability();
		wait 0.01;
	}
}

InfinityAmmo()
{
	self thread init_InfinityAmmo(1);
}

init_InfinityAmmo(Notice)
{
	if(self.isInfinityAmmo == 0)
	{
		self thread do_InfinityAmmo();
		if(Notice == 1)
		{
			self iPrintln("^6Infinity Ammo ^7: [^2On^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Infinity Ammo ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isInfinityAmmo = 1;
	}
	else
	{
		self notify("stop_InfinityAmmo");
		if(Notice == 1)
		{
			self iPrintln("^6Infinity Ammo ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Infinity Ammo ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isInfinityAmmo = 0;
	}
}

//-----< 本体 >-----

do_InfinityAmmo()
{
	self endon("disconnect");
	self endon("stop_InfinityAmmo");
	for(;;)
	{
		wait 0.01;
		
		currentWeapon = self getcurrentweapon();
		if(currentWeapon != "none")
		{
			self setweaponammoclip(currentWeapon, weaponclipsize(currentWeapon));
			self givemaxammo(currentWeapon);
		}
		currentoffhand = self getcurrentoffhand();
		if(currentoffhand != "none")
			self givemaxammo(currentoffhand);
	}
}

ESPWallHack()
{
	self thread init_ESPWallHack(1);
}
init_ESPWallHack(Notice)
{
	if(self.isWallHack == 0)
	{
		self thread GetTargets_ESPWallHack();
		if(Notice == 1)
		{
			self iPrintln("^6ESP Wall Hack ^7: [^2On^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6ESP Wall Hack ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isWallHack = 1;
	}
	else
	{
		self notify("stop_ESPWallHack");
		for(i = 0; i < self.esp.targets.size; i++)
			self.esp.targets[i].hudbox destroy();
		if(Notice == 1)
		{
			self iPrintln("^6ESP Wall Hack ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6ESP Wall Hack ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isWallHack = 0;
	}
} 
GetTargets_ESPWallHack()
{
	self endon("stop_ESPWallHack");
	for(;;)
	{
		self.esp = spawnStruct();
		self.esp.targets = [];
		a = 0;
		for(i = 0; i < level.players.size; i++)
		{
			if(self != level.players[i])
			{
				self.esp.targets[a] = spawnStruct();
				self.esp.targets[a].player = level.players[i];
				self.esp.targets[a].hudbox = self CreateBox_ESPWallHack(self.esp.targets[a].player.origin, 1);
				self thread MonitorTarget_ESPWallHack(self.esp.targets[a]);
				self thread WaitDestroy_ESPBox(self.esp.targets[a]);
				a++;
			}
		}
		level waittill("connected", player);
		self notify("UpdateTarget_ESPWallHack");
	}
}
MonitorTarget_ESPWallHack(target)
{
	self endon("UpdateTarget_ESPWallHack");
	self endon("stop_ESPWallHack");
	for(;;)
	{
		target.hudbox destroy();
		h_pos = target.player.origin;
		t_pos = target.player.origin;
		if(bulletTracePassed(self getTagOrigin("j_spine4"), target.player getTagOrigin("j_spine4"), false, self))
		{
			if(distance(self.origin,target.player.origin) <= 1800)
			{
				if(level.teamBased && target.player.pers["team"] != self.pers["team"])
				{
					target.hudbox = self CreateBox_ESPWallHack(h_pos, 900);
					target.hudbox.color = (0, 1, 0);
				}
				if(!level.teamBased)
				{
					target.hudbox = self CreateBox_ESPWallHack(h_pos, 900);
				       	target.hudbox.color = (0, 1, 0);
				}
			}
			else
				target.hudbox = self CreateBox_ESPWallHack(t_pos, 900);
		}
		else
			target.hudbox = self CreateBox_ESPWallHack(t_pos, 100);
	       
		if(!isAlive(target.player))
		{
			target.hudbox destroy();
			if(level.teamBased && target.player.pers["team"] != self.pers["team"])
			{
				target.hudbox = self CreateBox_ESPWallHack(t_pos, 900);
				target.hudbox setShader(level.deads, 6, 6);
			}
			else if(!level.teamBased)
			{
				target.hudbox = self CreateBox_ESPWallHack(t_pos, 900);
				target.hudbox setShader(level.deads, 6, 6);
			}
		}
	       
		if(self.pers["team"] == target.player.pers["team"] && level.teamBased)
		{
			target.hudbox destroy();
			if(distance(target.player.origin, self.origin) < 3)
				target.hudbox = self CreateBox_ESPWallHack(t_pos, 900);
 
		}
		wait 0.001;
	}
}
WaitDestroy_ESPBox(target)
{
		self waittill("UpdateTarget_ESPWallHack");
		target.hudbox destroy();
}
CreateBox_ESPWallHack(pos, type)
{
	shader = newClientHudElem(self);
	shader.sort = 0;
	shader.archived = false;
	shader.x = pos[0];
	shader.y = pos[1];
	shader.z = pos[2] + 30;
	shader setShader(level.esps, 6, 6);
	shader setWaypoint(true, true);
	shader.alpha = 0.80;
	shader.color = (1, 0, 0);
	return shader;
}

AdvancedNoclip()
{
	self thread init_AdvancedNoclip(1, 20, 200);
}

//-----< On / Off >-----

init_AdvancedNoclip(Notice, Slow, Fast)
{
	if(self.isAdvancedNoclip == 0)
	{
		self notify("stop_UFOMode");
		self unlink();
		self.isUFOMode = 0;
		self thread do_AdvancedNoclip(Slow, Fast);
		if(Notice == 1)
		{
			self iPrintln("^6Advanced Noclip ^7: [^2On^7]");
			if(self.NoticeTextMode == 0)
				self thread optionCalledMesage("[{+speed_throw}] + [{+smoke}] : ^2Fly start", 1, "^7[{+gostand}] + ^3 Fast move ^7| [{+stance}] : ^1Cancel fly", (0, 1, 0), 6, 0);
			else
				self thread init_NotifySetText(0, 2, "^6Advanced Noclip ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 4, 1, "[{+speed_throw}] + [{+smoke}] : ^2Fly start ^7| [{+gostand}] + ^3 Fast move ^7| [{+stance}] : ^1Cancel fly", (1, 1, 1), 1, (1, 1, 1));
		}
		self.isAdvancedNoclip = 1;
	}
	else
	{
		self notify("stop_AdvancedNoclip");
		self unlink();
		self.Object_AdvancedNoclip delete();
		if(Notice == 1)
		{
			self iPrintln("^6Advanced Noclip ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Advanced Noclip ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isAdvancedNoclip = 0;
	}
}
do_AdvancedNoclip(Slow, Fast)
{
	self endon("disconnect");
	self endon("stop_AdvancedNoclip");
	self.Flying_AdvancedNoclip = 0;
	for(;;)
	{
		if(self.Flying_AdvancedNoclip == 0 && self adsButtonPressed() && self secondaryOffhandButtonPressed())
		{
			self.Object_AdvancedNoclip = spawn("script_origin", self.origin, 1);
			self.Object_AdvancedNoclip.angles = self.angles;
			self playerlinkto(self.Object_AdvancedNoclip, undefined);
			self.Flying_AdvancedNoclip = 1;
		}
		if(self.Flying_AdvancedNoclip == 1 && self secondaryOffhandButtonPressed())
		{
			normalized = anglesToForward(self getPlayerAngles());
			scaled = vectorScale(normalized, Slow);
			originpos = self.origin + scaled;
			self.Object_AdvancedNoclip.origin = originpos;
		}
		if(self.Flying_AdvancedNoclip == 1 && self jumpButtonPressed())
		{
			normalized = anglesToForward(self getPlayerAngles());
			scaled = vectorScale(normalized, Fast);
			originpos = self.origin + scaled;
			self.Object_AdvancedNoclip.origin = originpos;
		}
		if(self.Flying_AdvancedNoclip == 1 && self stanceButtonPressed())
		{
			self unlink();
			self.Object_AdvancedNoclip delete();
			self.Flying_AdvancedNoclip = 0;
		}  
		wait 0.001;
	}
}

Invisible()
{
	self thread init_Invisible(1);
}
init_Invisible(Notice)
{
	if(self.isInvisible == 0)
	{
		self thread do_Invisible();
		if(Notice == 1)
		{
			self iPrintln("^6Invisible ^7: [^2On^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Invisible ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isInvisible = 1;
	}
	else
	{
		self notify("stop_Invisible");
		self show();
		if(Notice == 1)
		{
			self iPrintln("^6Invisible ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Invisible ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isInvisible = 0;
	}
}
do_Invisible()
{
	self endon("disconnect");
	self endon("stop_Invisible");
	for(;;)
	{
		self hide();
		wait 0.1;
	}
}

ClientSpeed()
{
	if(self.isClientSpeed < 10)
		self thread Change_ClientSpeed(1);
	else if(self.isClientSpeed == 10)
	{
		self.isClientSpeed = 19;
		self thread Change_ClientSpeed(1);
	}
	else if(self.isClientSpeed == 20)
	{
		self.isClientSpeed = 29;
		self thread Change_ClientSpeed(1);
	}
	else if(self.isClientSpeed == 30)
	{
		self.isClientSpeed = 39;
		self thread Change_ClientSpeed(1);
	}
	else if(self.isClientSpeed == 40)
	{
		self.isClientSpeed = 49;
		self thread Change_ClientSpeed(1);
	}
	else if(self.isClientSpeed == 50)
	{
		self.isClientSpeed = 99;
		self thread Change_ClientSpeed(1);
	}
	else if(self.isClientSpeed == 100)
	{
		self.isClientSpeed = 0;
		self thread Change_ClientSpeed(1);
		self notify("stop_ClientSpeed");
	}
}
Change_ClientSpeed(Notice)
{
	self.isClientSpeed++;
	Scale = self.isClientSpeed;
	self setMoveSpeedScale(self.isClientSpeed);
	if(Notice == 1)
	{
		self iPrintln("^6Client Speed Scale ^7: [^5x" + Scale + "^7]");
		if(self.NoticeTextMode == 1)
			self thread init_NotifySetText(0, 2, "^6Change Client Speed ^7to ^5" + Scale, (1, 1, 1), 1, (0, 0, 1), 2, 0);
	}
	self notify("stop_ClientSpeed");
	self thread do_ClientSpeed();
}
do_ClientSpeed()
{
	self endon("disconnect");
	self endon("stop_ClientSpeed");
	for(;;)
	{
		self setMoveSpeedScale(self.isClientSpeed);
		wait 0.05;
	}
}

ProMod()
{
	self thread init_ProMod(1);
}

//-----< 本体 >-----

init_ProMod(Notice)
{
	if(self.isProMod == 0)
	{
		self thread do_ProMod();
		if(Notice == 1)
		{
			self iPrintln("^6Pro Mod ^7: [^2On^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Pro Mod ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isProMod = 1;
	}
	else
	{
		self notify("stop_ProMod");
		self setClientFOV(65);
		self thread ChangeVision(-1, 0, 0, 0);
		if(Notice == 1)
		{
			self iPrintln("^6Pro Mod ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Pro Mod ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isProMod = 0;
	}
}
do_ProMod()
{
	self endon("disconnect");
	self endon("stop_ProMod");
	self setClientFOV(90);
	self thread ChangeVision(1, "remote_mortar_enhanced", 0, 0);
	for(;;)
	{
		self waittill("spawned_player");
		wait 0.1;
		self setClientFOV(90);
		self thread ChangeVision(1, "remote_mortar_enhanced", 0, 0);
	}
}


















