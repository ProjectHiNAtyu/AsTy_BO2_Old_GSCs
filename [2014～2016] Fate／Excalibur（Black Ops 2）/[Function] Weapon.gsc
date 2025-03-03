EffectBullets()
{
	if(self.isEffectBullets == 0)
	{
		self Change_EffectBullets(1, "Remote Mortat Explosion", 0);
		self thread init_EffectBullets(1, 0, "weapon/remote_mortar/fx_rmt_mortar_explosion", 1000000, 500, 0.5, 3, 600, 0, "");
	}
	else if(self.isEffectBullets == 1)
	{
		self Change_EffectBullets(1, "Proximiry Shock Grenade");
		self thread init_EffectBullets(0, 0, level._effect["prox_grenade_player_shock"], 1000000, 50, 0.1, 1, 70, 0, "");
	}
	else if(self.isEffectBullets == 2)
	{
		self Change_EffectBullets(1, "Smoke Flare", 0);
		self thread init_EffectBullets(1, 0, "env/smoke/fx_smoke_supply_drop_blue_mp", 1000000, 80, 0.1, 1, 100, 0, "");
	}
	else if(self.isEffectBullets == 3)
	{
		self Change_EffectBullets(1, "Bouncing Betty Destroyed", 0);
		self thread init_EffectBullets(1, 0, "weapon/bouncing_betty/fx_betty_destroyed", 1000000, 150, 0.3, 2, 190, 1, "fly_betty_explo");
	}
	else if(self.isEffectBullets == 4)
	{
		self Change_EffectBullets(1, "Green Light", 0);
		self thread init_EffectBullets(1, 1, "misc/fx_equip_tac_insert_light_grn", 1000000, 50, 0.1, 1, 80, 1, "wpn_flash_grenade_explode");
	}
	else if(self.isEffectBullets == 5)
	{
		self Change_EffectBullets(1, "Red Light", 0);
		self thread init_EffectBullets(1, 1, "misc/fx_equip_tac_insert_light_red", 1000000, 50, 0.1, 1, 80, 1, "wpn_flash_grenade_explode");
	}
	else if(self.isEffectBullets == 6)
	{
		self Change_EffectBullets(1, "Equipment LG Explosion", 0);
		self thread init_EffectBullets(1, 0, "explosions/fx_exp_equipment_lg", 1000000, 70, 0.1, 1, 100, 0, "");
	}
	else if(self.isEffectBullets == 7)
	{
		self Change_EffectBullets(1, "EMP Equipment Explosion", 0);
		self thread init_EffectBullets(1, 0, "weapon/emp/fx_emp_explosion_equip", 1000000, 70, 0.1, 1, 100, 0, "");
	}
	else if(self.isEffectBullets == 8)
	{
		self Change_EffectBullets(1, "Chopper Smoke Trail", 0);
		self thread init_EffectBullets(0, 1, level.chopper_fx["smoke"]["trail"], 1000000, 140, 0.3, 3, 190, 0, "");
	}
	else if(self.isEffectBullets == 9)
	{
		self Change_EffectBullets(1, "Chopper Damage Heavy Smoke");
		self thread init_EffectBullets(0, 1, level.chopper_fx["damage"]["heavy_smoke"], 1000000, 120, 0.2, 2, 150, 0, "");
	}
	else if(self.isEffectBullets == 10)
	{
		self Change_EffectBullets(1, "Chopper Large Explode", 0);
		self thread init_EffectBullets(0, 0, level.chopper_fx["explode"]["large"], 1000000, 550, 0.4, 5, 600, 0, "");
	}
	else if(self.isEffectBullets == 11)
	{
		self Change_EffectBullets(1, "Counter UAV Afterburner");
		self thread init_EffectBullets(0, 1, level.fx_cuav_afterburner, 1000000, 350, 0.3, 4, 400, 0, "");
	}
	else if(self.isEffectBullets == 12)
	{
		self Change_EffectBullets(1, "EMP Explosion", 0);
		self thread init_EffectBullets(1, 0, "weapon/emp/fx_emp_explosion", 1000000, 2500, 1, 7, 2700, 1, "wpn_emp_bomb");
	}
	else if(self.isEffectBullets == 13)
	{
		self Change_EffectBullets(1, "RC-XD Bomb Explosion", 0);
		self thread init_EffectBullets(1, 0, "maps/mp_maps/fx_mp_exp_rc_bomb", 1000000, 450, 0.5, 2, 500, 0, "");
	}
	else if(self.isEffectBullets == 14)
	{
		self Change_EffectBullets(1, "U2 Explode", 0);
		self thread init_EffectBullets(0, 0, level.fx_u2_explode, 1000000, 500, 0.4, 3, 550, 2, level.heli_sound["crash"]);
	}
	else if(self.isEffectBullets == 15)
	{
		self Change_EffectBullets(1, "Nuked Final Explosion", 0);
		self thread init_EffectBullets(1, 0, "maps/mp_maps/fx_mp_nuked_final_explosion", 1000000, 8000, 1, 7, 8500, 1, "amb_end_nuke");
	}
	else if(self.isEffectBullets == 16)
	{
		self Change_EffectBullets(1, "Nuked Final Dust", 0);
		self thread init_EffectBullets(1, 0, "maps/mp_maps/fx_mp_nuked_final_dust", 1000000, 2000, 1, 6, 2200, 1, "amb_end_nuke");
	}
	else if(self.isEffectBullets == 17)
	{
		self Change_EffectBullets(1, "Water Splash", 0);
		self thread init_EffectBullets(1, 0, "bio/player/fx_player_water_splash_mp", 1000000, 350, 0.5, 2, 390, 1, "wpn_satchel_plant_water");
	}
	else if(self.isEffectBullets == 18)
	{
		self Change_EffectBullets(1, "No Effect & Damage", 0);
		self thread init_EffectBullets(0, 0, "Damage", 1000000, 5000, 0, 0, 0, 0, "");
	}
	else
	{
		self Change_EffectBullets(1, "", 1);
	}
}

init_EffectBullets(Type, Mode, Effect, Range, Damage, Scale, Time, Offset, SoundType, Sound)
{
	self endon("disconnect");
	self endon("stop_EffectBullets");
	if(Type != 0)
		FX = LoadFX(Effect);
	else
		FX = Effect;
	for(;;)
	{
		self waittill("weapon_fired");
		Location = self TraceBullet(Range);
		if(Mode == 0)
		{
			if(Effect != "Damage")
				PlayFX(FX, Location);
		}
		else
		{
			SpecialFX = SpawnFX(FX, Location, (0, 0, 1), (1, 0, 0));
			TriggerFX(SpecialFX);
			wait 0.05;
			SpecialFX delete();
		}
		if(Damage != 0)
			RadiusDamage(Location, Damage, Damage, Damage, self);
		if(Scale != 0)
			Earthquake(Scale, Time, Location, Offset);
		if(SoundType != 0)
		{
			if(SoundType == 2)
				Soundcode = Sound;
			foreach(player in level.players)
			{
				if(SoundType == 1)
					player playsound(Sound);
				else
				{
					player playsound(Soundcode);
				}
			}
		}
	}
}
Change_EffectBullets(Notice, iPrint, Stop)
{
	if(Stop == 0)
	{
		if(self.isEffectBullets > 0)
			self notify("stop_EffectBullets");
		if(Notice == 1)
		{
			if(self.isEffectBullets == 0)
				self iPrintln("^6Effect Bullets ^7: [^2On^7]");
			self iPrintln("^6Select ^7: [^5" + iPrint + "^7]");
			if(self.NoticeTextMode == 1)
			{
				if(self.isEffectBullets == 0)
					self thread init_NotifySetText(0, 2, "^6Effect Bullets ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 3, 1, "^6Select Bullet ^7is ^5" + iPrint, (1, 1, 1), 1, (1, 1, 1));
				else
					self thread init_NotifySetText(0, 2, "^6Select Bullet ^7is ^5" + iPrint, (1, 1, 1), 1, (0, 0, 1), 2, 0);
			}
		}
		self.isEffectBullets++;
	}
	else
	{
		self notify("stop_EffectBullets");
		if(Notice == 1)
		{
			self iPrintln("^6Effect Bullets ^7: [^1Off^7]");
			self iPrintln("^6Select ^7: [^5Nomal^7]");
			if(self.NoticeTextMode == 1)
			{
					self thread init_NotifySetText(0, 2, "^6Effect Bullets ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 3, 1, "^6Select Bullet ^7is ^5Nomal", (1, 1, 1), 1, (1, 1, 1));
			}
		}
		self.isEffectBullets = 0;
	}
}

RayGun()
{
	self thread initRaygun(1);
}

initRaygun(Notice)
{
	if(self.isRaygun == 0)
	{
		self thread doRaygun();
		if(Notice == 1)
		{
			self iPrintln("^6Ray Gun ^7: [^2Given^7]");
			if(self.NoticeTextMode == 0)
				self thread optionCalledMesage("You get ^2Ray Gun^7!!", 1, "^7Is this a ^0Zombie?", (0.243, 0.957, 0.545), 8, 0);
			else
				self thread init_NotifySetText(0, 0, "^6Ray Gun ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 3, 1, "Is this a ^0Zombie?", (1, 1, 1), 0, (0, 0, 0));
		}
		self.isRaygun = 1;
	}
	else
	{
		self notify("stop_Raygun");
		self notify("stop_RaygunFX");
		self takeWeapon("judge_mp+reflex");
		//self takeWeapon("kard_mp+reflex");
		if(Notice == 1)
		{
			self iPrintln("^6Ray Gun ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Ray Gun ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isRaygun = 0;
	}
}

//=====[ 本体 ]=====

//発砲→メインFnction呼び出し

doRaygun()
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_Raygun");
	self ProvideWeapon("judge_mp+reflex", 43, 1, 0, "");
	//self ProvideWeapon("kard_mp+reflex", 43, 1, 0, "");
	for(;;)
	{
		self waittill("weapon_fired");
		if(self getCurrentWeapon() == "judge_mp+reflex" || self getCurrentWeapon() == "kard_mp+reflex")
		{
			self thread mainRaygun();
		}
	}
}

//メイン動作
		
mainRaygun()
{
	raygunExplode = loadfx("weapon/emp/fx_emp_explosion_equip");
	raygunExplode2 = loadfx("explosions/fx_exp_equipment_lg");

	weapOrigin = self getTagOrigin("tag_weapon_right");
	target = self TraceBullet(1000000);

	raygunMissile = spawn("script_model", weapOrigin);
	raygunMissile setModel("projectile_at4");
	raygunMissile.killcament = raygunMissile;
	endLocation = BulletTrace(raygunMissile.origin, target, false, self)["position"];
	raygunMissile.angles = VectorToAngles(endLocation - raygunMissile.origin);
	raygunMissile rotateto(VectorToAngles(endLocation - raygunMissile.origin), 0.001);

	raygunMissile moveto(endLocation, 0.55);
	self thread raygunEffect(raygunMissile, endLocation);
	wait 0.556;
	self notify("stop_RaygunFX");
	playfx(raygunExplode, raygunMissile.origin);
	playfx(raygunExplode2, raygunMissile.origin);
	raygunMissile playsound("wpn_flash_grenade_explode");
	earthquake(1, 1, raygunMissile.origin, 300);
	raygunMissile RadiusDamage(raygunMissile.origin, 200, 200, 200, self);
	raygunMissile delete();
}

//緑のトーチEffect移動コード

raygunEffect(object, target)
{
	self endon("disconnect");
	self endon("stop_RaygunFX_Final");
	raygunLaser = loadFX("misc/fx_equip_tac_insert_light_grn");
	for(;;)
	{
		raygunGreen = spawnFx(raygunLaser, object.origin, VectorToAngles(target - object.origin));
		triggerFx(raygunGreen);
		wait 0.001;
		raygunGreen delete();
	}
	
	for(;;)
	{
		self waittill("stop_RaygunFX");
		raygunGreen delete();
		self notify("stop_RaygunFX_Final");
	}
}

RayGunMarkII()
{
	self thread initRaygunM2(1);
}

initRaygunM2(Notice)
{
	if(self.isRaygunM2 == 0)
	{
		self thread doRaygunM2();
		if(Notice == 1)
		{
			self iPrintln("^6Ray Gun Mark II ^7: [^2Given^7]");
			if(self.NoticeTextMode == 0)
				self thread optionCalledMesage("WoW!! ^1Red Color...?", 1, "^7Upgraded Weapon LoL", (1, 0.502, 0.251), 8, 0);
			else
				self thread init_NotifySetText(0, 0, "^6Ray Gun Mark II ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 3, 1, "WoW!! ^1Red Color...? ^7Upgraded Weapon LoL", (1, 1, 1), 0, (0, 0, 0));
		}
		self.isRaygunM2 = 1;
	}
	else
	{
		self notify("stop_RaygunM2");
		self notify("stop_RaygunM2FX");
		self takeWeapon("beretta93r_mp+reflex");
		if(Notice == 1)
		{
			self iPrintln("^6Ray Gun Mark II ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Ray Gun Mark II ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isRaygunM2 = 0;
	}
}

//=====[ 本体 ]=====

//発砲→メインFnction呼び出し

doRaygunM2()
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_RaygunM2");
	self ProvideWeapon("beretta93r_mp+reflex", 38, 1, 0, "");
	for(;;)
	{
		self waittill("weapon_fired");
		if(self getCurrentWeapon() == "beretta93r_mp+reflex")
		{
			self thread mainRaygunM2();
		}
	}
}

//メイン動作
		
mainRaygunM2()
{
	raygunM2Explode = loadfx("weapon/bouncing_betty/fx_betty_destroyed");
	raygunM2Explode2 = loadfx("weapon/tracer/fx_tracer_flak_single_noExp");
	weapOrigin = self getTagOrigin("tag_weapon_right");
	target = self TraceBullet(1000000);

	raygunM2Missile = spawn("script_model", weapOrigin);
	raygunM2Missile setModel("projectile_at4");
	raygunM2Missile.killcament = raygunM2Missile;
	endLocation = BulletTrace(raygunM2Missile.origin, target, false, self)["position"];
	raygunM2Missile.angles = VectorToAngles(endLocation - raygunM2Missile.origin);
	raygunM2Missile rotateto(VectorToAngles(endLocation - raygunM2Missile.origin), 0.001);

	raygunM2Missile moveto(endLocation, 0.3);
	self thread raygunM2Effect(raygunM2Missile, endLocation);
	wait 0.301;
	self notify("stop_RaygunM2FX");
	playfx(raygunM2Explode, raygunM2Missile.origin);
	playfx(raygunM2Explode2, raygunM2Missile.origin); //level.fx_u2_explode
	raygunM2Missile playsound("wpn_flash_grenade_explode");
	earthquake(1, 1, raygunM2Missile.origin, 300);
	raygunM2Missile RadiusDamage(raygunM2Missile.origin, 270, 270, 270, self);
	raygunM2Missile delete();
}

//赤のトーチEffect移動コード

raygunM2Effect(object, target)
{
	self endon("disconnect");
	self endon("stop_RaygunM2FX_Final");
	raygunM2Laser = loadFX("misc/fx_equip_tac_insert_light_red");
	for(;;)
	{
		raygunM2Red = spawnFx(raygunM2Laser, object.origin, VectorToAngles(target - object.origin));
		triggerFx(raygunM2Red);
		wait 0.001;
		raygunM2Red delete();
	}
	for(;;)
	{
		self waittill("stop_RaygunM2FX");
		raygunM2Red delete();
		self notify("stop_RaygunM2FX_Final");
	}
}

LightningThunder()
{
	self thread init_LightningThunder(1);
}

init_LightningThunder(Notice)
{
	if(self.isLightningThunder == 0)
	{
		self thread ProvideWeapon("saiga12_mp+reflex", 39, 1, 0, "");
		self thread do_LightningThunder();
		if(Notice == 1)
		{
			self iPrintln("^6Lightning Thunder ^7: [^2Given^7]");
			if(self.NoticeTextMode == 0)
				self thread optionCalledMesage("^3b, Biteeeeeee!!!!", 1, "^7This is either ^3Biribiri-Tyuugakusei!?", (1, 1, 0.502), 8, 0);
			else
				self thread init_NotifySetText(0, 0, "^6Lightning Thunder ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 3, 1, "^3b, Biteeeeeee!!!! ^7This is either ^3Biribiri-Tyuugakusei!?", (1, 1, 1), 0, (0, 0, 0));
		}
		self.isLightningThunder = 1;
	}
	else
	{
		self notify("stop_LightningThunder");
		self takeWeapon("saiga12_mp+reflex");
		if(Notice == 1)
		{
			self iPrintln("^6Lightning Thunder ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Lightning Thunder ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isLightningThunder = 0;
	}
}

//==========[ 本体 ]==========

//発砲→メインFnction呼び出し

do_LightningThunder()
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_LightningThunder");
	for(;;)
	{
		self waittill("weapon_fired");
		if(self getCurrentWeapon() == "saiga12_mp+reflex")
		{
			self thread main_LightningThunder(1);
		}
	}
}

//メイン動作

main_LightningThunder(DamageType)
{
	LightningThunder_Explode = loadfx("weapon/emp/fx_emp_explosion_equip");
	LightningThunder_Explode2 = loadfx("explosions/fx_exp_equipment_lg");
	WeaponOrigin = self getTagOrigin("tag_weapon_right");
	Target = self TraceBullet(1000000);

	LightningThunder_Missile = spawn("script_model", WeaponOrigin + VectorScale(AnglesToForward(self GetPlayerAngles()), 70));
	LightningThunder_Missile setModel("projectile_at4");
	LightningThunder_Missile.killcament = LightningThunder_Missile;
	EndLocation = BulletTrace(LightningThunder_Missile.origin, Target, false, self)["position"];
	LightningThunder_Missile.angles = VectorToAngles(EndLocation - LightningThunder_Missile.origin);
	LightningThunder_Missile rotateto(VectorToAngles(EndLocation - LightningThunder_Missile.origin), 0.001);

	if(DamageType == 0)
		self thread effect_LightningThunder(LightningThunder_Missile, 0);
	else
		self thread effect_LightningThunder(LightningThunder_Missile, 1);
	
	LightningThunder_Missile moveto(EndLocation, 0.4);
	wait 0.401;
	self notify("stop_LightningThunder_FX");
	PlayFX(LightningThunder_Explode, LightningThunder_Missile.origin);
	PlayFX(LightningThunder_Explode2, LightningThunder_Missile.origin);
	//PlayFX(level.chopper_fx["explode"]["large"], LightningThunder_Missile.origin);
	LightningThunder_Missile PlaySound(level.heli_sound["crash"]);
	Earthquake(1, 1, LightningThunder_Missile.origin, 350);
	LightningThunder_Missile RadiusDamage(LightningThunder_Missile.origin, 220, 220, 220, self);
	LightningThunder_Missile delete();
}

//エフェクト追尾

effect_LightningThunder(object, DamageType)
{
	self endon("disconnect");
	self endon("stop_LightningThunder_FX");
	for(;;)
	{
		PlayFX(level._effect["prox_grenade_player_shock"], object.origin);
		PlayFX(level._effect["prox_grenade_player_shock"], object.origin + (5, 5, 5));
		PlayFX(level._effect["prox_grenade_player_shock"], object.origin + (-5, -5, -5));
		PlayFX(level._effect["prox_grenade_player_shock"], object.origin + (5, -5, -5));
		PlayFX(level._effect["prox_grenade_player_shock"], object.origin + (-5, -5, 5));
		PlayFX(level._effect["prox_grenade_player_shock"], object.origin + (5, 5, -5));
		PlayFX(level._effect["prox_grenade_player_shock"], object.origin + (-5, 5, 5));
		PlayFX(level._effect["prox_grenade_player_shock"], object.origin + (5, -5, 5));
		PlayFX(level._effect["prox_grenade_player_shock"], object.origin + (-5, 5, -5));
		object PlaySound("mpl_lightning_flyover_boom");
		if(DamageType == 1)
		{
			Earthquake(1, 1, object.origin, 100);
			object RadiusDamage(object.origin, 90, 90, 90, self);
		}
		wait 0.01;
	}
}

HydroCombinator()
{
	self thread init_HydroCombinator(1);
}

//-----< On / Off >-----

init_HydroCombinator(Notice)
{
	if(self.isHydroCombinator == 0)
	{
		self thread do_HydroCombinator();
		if(Notice == 1)
		{
			self iPrintln("^6Hydro Combinator ^7: [^2Given^7]");
			self iPrintln("^1Caution ^7: ^3Water Effect is working but only map with water.");
			if(self.NoticeTextMode == 0)
				self thread optionCalledMesage("^4Flood's!!", 1, "^7It ^5drowning ^7a dying...", (0, 0, 1), 8, 0);
			else
				self thread init_NotifySetText(0, 0, "^6Hydro Combinator ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 3, 1, "^4Flood's!! ^7It ^5drowning ^7a dying...", (1, 1, 1), 0, (0, 0, 0));
		}
		self.isHydroCombinator = 1;
	}
	else
	{
		self notify("stop_HydroCombinator");
		self takeWeapon("pdw57_mp+mms");
		if(Notice == 1)
		{
			self iPrintln("^6Hydro Combinator ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Hydro Combinator ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isHydroCombinator = 0;
	}
}

//==========[ 本体 ]==========

//発砲→メインFnction呼び出し

do_HydroCombinator()
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_HydroCombinator");
	self thread ProvideWeapon("pdw57_mp+mms", 39, 1, 0, "");
	for(;;)
	{
		self waittill("weapon_fired");
		if(self getCurrentWeapon() == "pdw57_mp+mms")
		{
			self thread main_HydroCombinator(1);
		}
	}
}

//メイン動作
	
main_HydroCombinator(DamageType)
{
	level._effect["water_splash_sm"] = LoadFX("bio/player/fx_player_water_splash_mp");
	WeaponOrigin = self getTagOrigin("tag_weapon_right");
	Target = self TraceBullet(1000000);

	HydroCombinator_Missile = spawn("script_model", WeaponOrigin + VectorScale(AnglesToForward(self GetPlayerAngles()), 70));
	HydroCombinator_Missile setModel("projectile_at4");
	HydroCombinator_Missile.killcament = HydroCombinator_Missile;
	EndLocation = BulletTrace(HydroCombinator_Missile.origin, Target, false, self)["position"];
	HydroCombinator_Missile.angles = VectorToAngles(EndLocation - HydroCombinator_Missile.origin);
	HydroCombinator_Missile rotateto(VectorToAngles(EndLocation - HydroCombinator_Missile.origin), 0.001);

	if(DamageType == 0)
		self thread effect_HydroCombinator(HydroCombinator_Missile, 0);
	else
		self thread effect_HydroCombinator(HydroCombinator_Missile, 1);
		
	HydroCombinator_Missile moveto(EndLocation, 0.25);
	wait 0.251;
	self notify("stop_HydroCombinator_FX");

	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin);
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (50, 50, 50));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (-50, -50, -50));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (50, -50, 50));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (-50, 50, -50));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (50, -50, -50));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (-50, -50, 50));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (50, 50, -50));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (-50, 50, 50));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (100, 100, 100));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (-100, -100, -100));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (100, -100, 100));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (-100, 100, -100));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (100, -100, -100));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (-100, -100, 100));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (100, 100, -100));
	PlayFX(level._effect["water_splash_sm"], HydroCombinator_Missile.origin + (-100, 100, 100));
	
	HydroCombinator_Missile PlaySound("fly_betty_explo");
	Earthquake(1, 1, HydroCombinator_Missile.origin, 420);
	HydroCombinator_Missile RadiusDamage(HydroCombinator_Missile.origin, 320, 320, 320, self);
	HydroCombinator_Missile delete();
}

//エフェクト追尾

effect_HydroCombinator(object, DamageType)
{
	self endon("disconnect");
	self endon("stop_HydroCombinator_FX");
	level._effect["water_splash_sm"] = LoadFX("bio/player/fx_player_water_splash_mp");
	for(;;)
	{
		PlayFX(level._effect["water_splash_sm"], object.origin);
		object PlaySound("mpl_lightning_flyover_boom");
		if(DamageType == 1)
		{
			Earthquake(1, 1, object.origin, 100);
			object RadiusDamage(object.origin, 90, 90, 90, self);
		}
		wait 0.05;
	}
}

PurgatoryInferno()
{
	self thread init_PurgatoryInferno(0, 1);
}
PurgatoryInfernoV2()
{
	self thread init_PurgatoryInferno(1, 1);
}

init_PurgatoryInferno(Mode, Notice)
{
	if(self.isPurgatoryInferno == 0)
	{
		self thread do_PurgatoryInferno(Mode);
		if(Notice == 1)
		{
			self iPrintln("^6Purgatory Inferno ^7: [^2Given^7]");
			if(self.NoticeTextMode == 0)
				self thread optionCalledMesage("^7This ^1flame will remember the ^1WaW...", 1, "^1However, it is incredibly ^1hot!", (1, 0, 0), 8, 0);
			else
				self thread init_NotifySetText(0, 0, "^6Purgatory Inferno ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 3, 1, "^7This ^1flame will remember the ^1WaW... ^1However, it is incredibly ^1hot!", (1, 1, 1), 0, (0, 0, 0));
		}
		self.isPurgatoryInferno = 1;
	}
	else
	{
		self notify("stop_PurgatoryInferno");
		self takeWeapon("fhj18_mp");
		if(Notice == 1)
		{
			self iPrintln("^6Purgatory Inferno ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Purgatory Inferno ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isPurgatoryInferno = 0;
	}
}

//==========[ 本体 ]==========

//発砲→メインFnction呼び出し

do_PurgatoryInferno(Mode)
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_PurgatoryInferno");
	self thread ProvideWeapon("fhj18_mp", 39, 1, 0, "");
	for(;;)
	{
		if(self attackButtonPressed() && self getCurrentWeapon() == "fhj18_mp")
		{
			self thread main_PurgatoryInferno(Mode);
		}
		wait 0.05;
	}
}

//メイン動作

main_PurgatoryInferno(DamageType)
{
	WeaponOrigin = self getTagOrigin("tag_weapon_right");
	
	if(DamageType == 0)
		EndLocation = TraceBullet(600);
	else
		EndLocation = TraceBullet(1000000);

	PurgatoryInferno_Missile = spawn("script_model", WeaponOrigin + VectorScale(AnglesToForward(self GetPlayerAngles()), 70));
	PurgatoryInferno_Missile setModel("tag_origin");
	PurgatoryInferno_Missile.killcament = PurgatoryInferno_Missile;
	PurgatoryInferno_Missile.angles = VectorToAngles(EndLocation - PurgatoryInferno_Missile.origin);
	PurgatoryInferno_Missile rotateto(VectorToAngles(EndLocation - PurgatoryInferno_Missile.origin), 0.001);
            
	if(DamageType == 0)
		self thread effect_PurgatoryInferno(PurgatoryInferno_Missile, EndLocation, 0);
	else
		self thread effect_PurgatoryInferno(PurgatoryInferno_Missile, EndLocation, 1);

	PurgatoryInferno_Missile moveto(EndLocation, 0.3);
	wait 0.301;
	self notify("stop_PurgatoryInferno_FX");

	if(DamageType == 1)
	{
		PlayFX(level.chopper_fx["explode"]["large"], PurgatoryInferno_Missile.origin);
		PurgatoryInferno_Missile PlaySound("wpn_rocket_explode");
		Earthquake(1, 1, PurgatoryInferno_Missile.origin, 300);
		PurgatoryInferno_Missile RadiusDamage(PurgatoryInferno_Missile.origin, 300, 300, 300, self);
	}

	PurgatoryInferno_Missile delete();
}

//エフェクト追尾

effect_PurgatoryInferno(object, target, DamageType)
{
	self endon("disconnect");
	self endon("stop_PurgatoryInferno_FX_Final");
	for(;;)
	{
		if(DamageType == 0)
			Fire_PurgatoryInferno = spawnFx(level.chopper_fx["smoke"]["trail"], object.origin, VectorToAngles(target - object.origin));
		else
			Fire_PurgatoryInferno = spawnFx(level.chopper_fx["damage"]["heavy_smoke"], object.origin, VectorToAngles(target - object.origin));
		
		triggerFx(Fire_PurgatoryInferno);
		wait 0.025;
		Fire_PurgatoryInferno delete();
		object PlaySound("mpl_lightning_flyover_boom");


			Earthquake(1, 1, object.origin, 100);
			object RadiusDamage(object.origin, 70, 70, 70, self);

		wait 0.025;
	}

	for(;;)
	{
		self waittill("stop_PurgatoryInferno_FX_Final");
		Fire_PurgatoryInferno delete();
		self notify("stop_PurgatoryInferno_FX");
	}
}

MustangandSally()
{
	self thread init_MustangandSally(1);
}
init_MustangandSally(Notice)
{
	if(self.isMustangandSally == 0)
	{
		self thread do_MustangandSally();
		if(Notice == 1)
		{
			self iPrintln("^6Mustang and Sally ^7: [^2Given^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Mustang and Sally ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isMustangandSally = 1;
	}
	else
	{
		self notify("stop_MustangandSally");
		self TakeWeapon("fnp45_dw_mp");
		if(Notice == 1)
		{
			self iPrintln("^6Mustang and Sally ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Mustang and Sally ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isMustangandSally = 0;
	}
}
do_MustangandSally()
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_MustangandSally");
	self thread ProvideWeapon("fnp45_dw_mp", 39, 1, 0, "");
	for(;;)
	{
		self waittill("weapon_fired");
		if(self GetCurrentWeapon() == "fnp45_dw_mp")
			MagicBullet("m32_mp", self GetEye(), self TraceBullet(1000000), self);
	}
}

ThunderGun()
{
	self thread init_ThunderGun(550, 1);
}
init_ThunderGun(Range, Notice)
{
	if(self.isThunderGun == 0)
	{
		self thread do_ThunderGun(Range);
		if(Notice == 1)
		{
			self iPrintln("^6Thunder Gun ^7: [^2Given^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Thunder Gun ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isThunderGun = 1;
	}
	else
	{
		self notify("stop_ThunderGun");
		self TakeWeapon("ksg_mp+extbarrel+fastads");
		if(Notice == 1)
		{
			self iPrintln("^6Thunder Gun ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Thunder Gun ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isThunderGun = 0;
	}
}
do_ThunderGun(Range)
{
	self endon("disconnect");
	self endon("stop_ThunderGun");
	self thread ProvideWeapon("ksg_mp+extbarrel+fastads", 29, 1, 0, "");
	for(;;)
	{
		self waittill("weapon_fired");
		if(self getCurrentWeapon() == "ksg_mp+extbarrel+fastads")
		{	
			KillPos = self getTagOrigin("tag_weapon_right") + (0, 0, 50);
			KillLoc = self TraceBullet(400);
			self thread init_InvisibleDamageObject(KillPos, KillLoc, 0.7, 380, self);
			Location = self TraceBullet(Range);
			Position = self getTagOrigin("tag_weapon_right");
			Object = Spawn("script_model", Position);
	 		Object.angles = vectorToAngles(Location - Position);
	  		Object SetModel("tag_origin");
			Object thread Origin_PlayFX(1, "weapon/bouncing_betty/fx_betty_destroyed", 0, 0, 0.05, (0, 0, 0));
			foreach(player in level.players)
			{
				if(player != self)
					player thread Judge_ThunderGun(Object);
			}
			Object MoveTo(Location, 0.7);
			wait 0.7;
			Object notify("stop_Origin_PlayFX");
			Object thread Origin_PlayFX(1, "explosions/fx_exp_equipment_lg", 1, 0, 0, (0, 0, 0));
			//Object RadiusDamage(Object.origin, 350, 350, 350, self);
			Earthquake(0.9, 0.9, Object.origin, 600);
			foreach(player in level.players)
			{
				if(player != self)
					player notify("Judge_ThunderGun");
			}
			Object delete();
		}	
	}
	for(;;)
	{
		self waittill("death");
		foreach(player in level.players)
			player notify("Judge_ThunderGun");
		self.isThunderGun = 0;
		self notify("stop_ThunderGun");
	}
}
Judge_ThunderGun(Object)
{
	self endon("disconnect");
	self endon("death");
	self endon("Judge_ThunderGun");
	for(;;)
	{
		if(Distance(Object.origin, self.origin) < 600)
			self thread Damage_ThunderGun();
		wait 0.05;
	}
}
Damage_ThunderGun()
{
	self endon("disconnect");
	for(m = 4; m > 0; m--)
	{	
		self SetVelocity(self GetVelocity() + (250, 250, 250));
		wait 0.1;
	}
	self SetVelocity(0, 0, 0);
	wait 7;
}

ModdedBullets()
{
	self thread init_ModdedBullets(1);
}

//-----< On / Off >-----

init_ModdedBullets(Notice)
{
	if(self.isModdedBullets == 0)
	{
		self thread do_ModdedBullets();
		if(Notice == 1)
		{
			self iPrintln("^6Modded Bullets ^7: [^2On^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Modded Bullets ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isModdedBullets = 1;
	}
	else
	{
		self notify("stop_ModdedBullets");
		if(Notice == 1)
		{
			self iPrintln("^6Modded Bullets ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Modded Bullets ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isModdedBullets = 0;
	}
}

//-----< 本体 >-----

do_ModdedBullets()
{
	self endon("disconnect");
	self endon("stop_ModdedBullets");
	if(self.Check_ModdedBullets == 0)
	{
		wait 3;
		self thread Change_ModdedBullets("smaw_mp", 1, "SMAW");
	}
	for(;;)
	{
		self waittill("weapon_fired");
		MagicBullet(self.Select_ModdedBullets, self getEye(), self TraceBullet(1000000), self);
	}
}

//++++++++++< Modded Bulletsの弾切り替え >++++++++++

//-----< 呼び出し >-----

Select_ModdedBullets()
{
	if(self.isSelect_ModdedBullets == 0)
		self thread Change_ModdedBullets("smaw_mp", 1, "SMAW");
	else if(self.isSelect_ModdedBullets == 1)
		self thread Change_ModdedBullets("m32_mp", 1, "Grenade");
	else if(self.isSelect_ModdedBullets == 2)
		self thread Change_ModdedBullets("ai_tank_drone_rocket_mp", 1, "A.G.R Rocket");
	else if(self.isSelect_ModdedBullets == 3)
		self thread Change_ModdedBullets("straferun_rockets_mp", 1, "Warthog Rockets");
	else if(self.isSelect_ModdedBullets == 4)
		self thread Change_ModdedBullets("remote_missile_bomblet_mp", 1, "Mortar Missile Burner");
	else if(self.isSelect_ModdedBullets == 5)
		self thread Change_ModdedBullets("heli_gunner_rockets_mp", 1, "Heli Gunner Missile");
	else if(self.isSelect_ModdedBullets == 6)
		self thread Change_ModdedBullets("missile_swarm_projectile_mp", 1, "Swarm");
	else if(self.isSelect_ModdedBullets == 7)
		self thread Change_ModdedBullets("missile_drone_projectile_mp", 1, "Hanter Killer");
	else if(self.isSelect_ModdedBullets == 8)
		self thread Change_ModdedBullets("remote_missile_missile_mp", 1, "Remote Mortar Missile");
	else if(self.isSelect_ModdedBullets == 9)
		self thread Change_ModdedBullets("870mcs_mp", 1, "R-870 MCS");
	else if(self.isSelect_ModdedBullets == 10)
		self thread Change_ModdedBullets("straferun_gun_mp", 1, 0);
	else if(self.isSelect_ModdedBullets == 11)
		self thread Change_ModdedBullets("littlebird_guard_minigun_mp", 1, 0);
	else if(self.isSelect_ModdedBullets == 12)
		self thread Change_ModdedBullets("killstreak_qrdrone_mp", 1, 0);
	else if(self.isSelect_ModdedBullets == 13)
		self thread Change_ModdedBullets("helicopter_guard_mp", 1, 0);
	else if(self.isSelect_ModdedBullets == 14)
		self thread Change_ModdedBullets("helicopter_player_gunner_mp", 1, 0);
	else if(self.isSelect_ModdedBullets == 15)
		self thread Change_ModdedBullets("chopper_minigun_mp", 1, 0);
	else if(self.isSelect_ModdedBullets == 16)
		self thread Change_ModdedBullets("missile_drone_projectile_mp", 1, 0);
	else if(self.isSelect_ModdedBullets == 17)
		self thread Change_ModdedBullets("cobra_20mm_mp", 1, 0);
	else if(self.isSelect_ModdedBullets == 18)
	{
		self thread Change_ModdedBullets("remote_mortar_missile_mp", 1, "Loadstar");
		self.isSelect_ModdedBullets = 0;
	}
}

//-----< 本体 >-----

Change_ModdedBullets(Weapon, Notice, Word)
{
	self.Select_ModdedBullets = Weapon;
	if(Notice == 1)
	{
		if(Word != 0)
		{
			self iPrintln("^6Select Bullet ^7: [^5" + Word + "^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Select Bullet ^7is ^5" + Word, (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		else
		{
			self iPrintln("^6Select Bullet ^7: [^5" + Weapon + "^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Select Bullet ^7is ^5" + Weapon, (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
	}
	self.Check_ModdedBullets = 1;
	self.isSelect_ModdedBullets++;
}

TakeAllWeapons()
{
	self thread init_TakeAllWeapons(1);
}
init_TakeAllWeapons(Notice)
{
	self takeAllWeapons();
	if(Notice == 1)
	{
		self iPrintln("^6All Weapons ^7: [^1Taked^7]");
		if(self.NoticeTextMode == 1)
			self thread init_NotifySetText(0, 2, "^6All Weapons ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
	}
}

GiveRandomWeapon()
{
	self thread init_GiveRandomWeapon(1, 1, 1);
}

//-----< 本体 >-----

init_GiveRandomWeapon(Toggle, Print, Type)
{
	id = random(level.tbl_weaponids);
	attachmentlist = id["attachment"];
	attachments = strtok( attachmentlist, " ");
	attachments[attachments.size] = "";
	attachment = random(attachments);
	Camo = RandomIntRange(0, 45);
	self GiveWeapon((id["reference"] + "_mp+") + attachment, 0, true(Camo, 0, 0, 0, 0));
	if(Toggle == 1)
		self SwitchToWeapon((id["reference"] + "_mp+") + attachment);
	if(Print == 1)
	{
		if(Type == 0)
		{
			self iPrintln("^6Random Weapon ^7: [^2Given^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Random Weapon ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		else
		{
			self iPrintln("^6Give Weapon ^7: [^5" + (id["reference"] + "_mp+") + attachment + "^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Random Weapon ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 3, 1, "^6Give Weapon ^7to ^5" + (id["reference"] + "_mp+") + attachment, (1, 1, 1), 0, (1, 1, 1));
		}
	}
}

ChangeCamo_NomalRandom()
{
	self thread ChangeCamo(0, -1, 1);
}
ChangeCamo_DLCRandom()
{
	self thread ChangeCamo(1, -1, 1);
}
ChangeCamo_Default()
{
	self thread ChangeCamo(2, 0, 1);
}
ChangeCamo_Gold()
{
	self thread ChangeCamo(2, 15, 1);
}
ChangeCamo_Ghosts()
{
	self thread ChangeCamo(2, 29, 1);
}
ChangeCamo_Dragon()
{
	self thread ChangeCamo(2, 32, 1);
}
ChangeCamo_PackaPunch()
{
	self thread ChangeCamo(2, 39, 1);
}
ChangeCamo_Weaponized115()
{
	self thread ChangeCamo(2, 43, 1);
}
ChangeCamo_Afterlife()
{
	self thread ChangeCamo(2, 44, 1);
}

//-----< 本体 >-----

ChangeCamo(Type, Camo, Print)
{
	Weapon = self getCurrentWeapon();
	if(Type == 0)
		Random = RandomIntRange(0, 45);
	else if(Type == 1)
		Random = RandomIntRange(17, 45);
	else
		Random = RandomIntRange(0, 45);

	self TakeWeapon(self getCurrentWeapon());
	if(Camo == 0)
		self GiveWeapon(Weapon, 0, false);
	else if(Camo == -1)
		self GiveWeapon(Weapon, 0, true(Random, 0, 0, 0, 0));
	else
		self GiveWeapon(Weapon, 0, true(Camo, 0, 0, 0, 0));
	self GiveMaxAmmo(Weapon);
	self SwitchToWeapon(Weapon);

	if(Print == 1)
	{
		if(Camo == -1)
		{
			self iPrintln("^6Changed Camo ^7: [^5#" + Random + "^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Changed Camo ^7to ^5#" + Random, (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		else
		{
			self iPrintln("^6Changed Camo ^7: [^5#" + Camo + "^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Changed Camo ^7to ^5#" + Camo, (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
	}
}

BallisticTeleporter()
{
	self thread init_BallisticTeleporter(1);
}

init_BallisticTeleporter(Notice)
{
	if(self.isBallisticTeleporter == 0)
	{
		self thread do_BallisticTeleporter();
		self thread ProvideWeapon("knife_ballistic_mp", 16, 1, 0, "");
		if(Notice == 1)
		{
			self iPrintln("^6Ballistic Teleporter ^7: [^2Given^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Ballistic Teleporter ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isBallisticTeleporter = 1;
	}
	else
	{
		self notify("stop_BallisticTeleporter");
		self TakeWeapon("knife_ballistic_mp");
		if(Notice == 1)
		{
			self iPrintln("^6Ballistic Teleporter ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Ballistic Teleporter ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isBallisticTeleporter = 0;
	}
}

//===============[ 本体 ]===============

do_BallisticTeleporter()
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_BallisticTeleporter");
	for(;;)
	{
		self waittill("missile_fire", Weapon, WeaponName);
		if(WeaponName == "knife_ballistic_mp")
		{
			self DetachAll();
			self PlayerLinkTo(Weapon);
			Weapon waittill("death");
			self DetachAll();
		}
	}
}

EarthquakeGun()
{
	self thread init_EarthquakeGun(0.6, 10, 5000, 1, 1);
}

init_EarthquakeGun(Scale, Time, Offset, LocNotice, Notice)
{
	if(self.isEarthquakeGun == 0)
	{
		self thread do_EarthquakeGun(Scale, Time, Offset, LocNotice);
		if(Notice == 1)
		{
			self iPrintln("^6Earthquake Gun ^7: [^2Given^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Earthquake Gun ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isEarthquakeGun = 1;
	}
	else
	{
		self notify("stop_EarthquakeGun");
		self takeWeapon("judge_mp+extbarrel+steadyaim");
		if(Notice == 1)
		{
			self iPrintln("^6Earthquake Gun ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Earthquake Gun ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isEarthquakeGun = 0;
	}
}

//===============[ 本体 ]===============

do_EarthquakeGun(Scale, Time, Offset, LocNotice)
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_EarthquakeGun");
	self thread ProvideWeapon("judge_mp+extbarrel+steadyaim", 41, 1, 0, "");
	for(;;)
	{
		self waittill("weapon_fired");
		if(self GetCurrentWeapon() == "judge_mp+extbarrel+steadyaim")
		{
			Location = self TraceBullet(1000000);
			EarthQuake(Scale, Time, Location, Offset);
			if(LocNotice == 1)
				self iPrintln("^6Hit Location ^7: [^5" + Location + "^7]");
		}
	}
}

PortalGun()
{
	self thread init_PortalGun(1);
}
init_PortalGun(Notice)
{
	if(self.isPortalGun == 0)
	{
		self thread do_PortalGun();
		if(Notice == 1)
		{
			self iPrintln("^6Portal Gun ^7: [^2Given^7]");
			if(self.NoticeTextMode == 0)
				self thread optionCalledMesage("[{+attack}] : Spawn ^2Green teleporter", 1, "^7& Spawn ^1Red teleporter", (0, 1, 0), 6, 0);
			else
				self thread init_NotifySetText(0, 0, "^6Portal Gun ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 4, 1, "[{+attack}] : Spawn ^2Green teleporter ^7& Spawn ^1Red teleporter", (1, 1, 1), 1, (1, 1, 1));
		}
		self.isPortalGun = 1;
	}
	else
	{
		self notify("stop_PortalGun");
		self takeweapon("fiveseven_mp+silencer+steadyaim");
		self.Green_PortalGun Delete();
		self.Red_PortalGun Delete();
		if(Notice == 1)
		{
			self iPrintln("^6Portal Gun ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Portal Gun ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isPortalGun = 0;
	}
}
do_PortalGun()
{
	self endon("disconnect");
	self endon("stop_PortalGun");
	self thread ProvideWeapon("fiveseven_mp+silencer+steadyaim", 30, 1, 0, "");
	level.waypointGreen = loadFX("misc/fx_equip_tac_insert_light_grn");
	level.waypointRed = loadFX("misc/fx_equip_tac_insert_light_red");
	self.Check_PortalGun = 0;
	for(;;)
	{
		self waittill("weapon_fired");
		if(self GetCurrentWeapon() == "fiveseven_mp+silencer+steadyaim")
		{
			Location = self TraceBullet(1000000);
			if(self.Check_PortalGun == 0)
			{
				self notify("stop_Monitor_PortalGun");
				self.Green_PortalGun Delete();
				self.Red_PortalGun Delete();
				self.Green_PortalGun = SpawnFx(level.waypointGreen, Location);
				TriggerFx(self.Green_PortalGun);
				self iPrintln("^2Green Portal ^7: [^2Created^7]");
				wait 0.5;
				self.Check_PortalGun++;
			}
			else if(self.Check_PortalGun == 1)
			{
				self.Red_PortalGun Delete();
				self.Red_PortalGun = SpawnFx(level.waypointRed, Location);
				TriggerFx(self.Red_PortalGun);
				self iPrintln("^1Red Portal ^7: [^2Created^7]");
				wait 0.5;
				self.Check_PortalGun--;
				self thread Monitor_PortalGun();
			}
		}
	}
}
Monitor_PortalGun()
{
	self endon("disconnect");
	self endon("stop_PortalGun");
	self endon("stop_Monitor_PortalGun");
	for(;;)
	{
		foreach(player in level.players)
		{
			if(Distance(self.Green_PortalGun.origin, player.origin) < 50)
			{
				player SetOrigin(self.Red_PortalGun.origin);
				wait 2;
			}
			if(Distance(self.Red_PortalGun.origin, player.origin) < 50)
			{
				player SetOrigin(self.Green_PortalGun.origin);
				wait 2;
			}
			wait 0.05;
		}
		wait 0.05;
	}
}

RealCarePackagesGun()
{
	self thread init_RealCarePackagesGun(300, 1);
}
init_RealCarePackagesGun(Range, Notice)
{
	if(self.isRealCarePackagesGun == 0)
	{
		self thread do_RealCarePackagesGun(Range);
		if(Notice == 1)
		{
			self iPrintln("^6Real Carepackages Gun ^7: [^2Given^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Real Carepackages Gun ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isRealCarePackagesGun = 1;
	}
	else
	{
		self notify("stop_RealCarePackagesGun");
		self takeWeapon("sa58_mp+sf+steadyaim");
		if(Notice == 1)
		{
			self iPrintln("^6Real Carepackages Gun ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Real Carepackages Gun ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isRealCarePackagesGun = 0;
	}
}
do_RealCarePackagesGun(Range)
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_RealCarePackagesGun");
	self thread ProvideWeapon("sa58_mp+sf+steadyaim", 34, 1, 0, "");
	for(;;)
	{
		self waittill("weapon_fired");
		if(self GetCurrentWeapon() == "sa58_mp+sf+steadyaim" || self GetCurrentWeapon() == "sf_sa58_mp+sf+steadyaim")
			self thread maps\mp\killstreaks\_supplydrop::dropcrate(self TraceBullet(Range), self.angles, "supplydrop_mp", self, self.team, self.killcament, undefined, undefined, undefined);
		wait 0.05;
	}
}

TeleportGun()
{
	self thread init_TeleportGun(1000000, 1, 1);
}
init_TeleportGun(Range, LocNotice, Notice)
{
	if(self.isTeleportGun == 0)
	{
		self thread do_TeleportGun(Range, LocNotice);
		if(Notice == 1)
		{
			self iPrintln("^6Teleport Gun ^7: [^2Given^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Teleport Gun ^7is ^2Given.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isTeleportGun = 1;
	}
	else
	{
		self notify("stop_TeleportGun");
		self takeWeapon("870mcs_mp+mms+steadyaim");
		if(Notice == 1)
		{
			self iPrintln("^6Teleport Gun ^7: [^1Taked^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Teleport Gun ^7is ^1Taked.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isTeleportGun = 0;
	}
}
do_TeleportGun(Range, LocNotice)
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_TeleportGun");
	self thread ProvideWeapon("870mcs_mp+mms+steadyaim", 44, 1, 0, "");
	for(;;)
	{
		self waittill("weapon_fired");
		if(self GetCurrentWeapon() == "870mcs_mp+mms+steadyaim")
		{
			Location = self TraceBullet(Range);
			self SetOrigin(Location);
			if(LocNotice == 1)
				self iPrintln("^6Teleported to ^7: [^5" + Location + "^7]");
		}
	}
}


















