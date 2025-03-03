//******************************
//=====[ Menuシステム調整系 ]=====
//******************************

//===============[ メッセージ設定 ]===============

Change_NoticeMode()
{
	if(level.NoticeMode == 0)
	{
		self iPrintln("^6Notice Mode ^7 : [^5All Players^7]");
		level.NoticeMode = 1;
	}
	else
	{
		self iPrintln("^6Notice Mode ^7 : [^5Self Only^7]");
		level.NoticeMode = 0;
	}
}
Change_NoticeTextMode_Host()
{
	if(level.AllNoticeTextMode == 0)
	{
		self iPrintln("^6Notice Text Mode ^7 : [^5Set Text^7]");
		level.AllNoticeTextMode = 1;
	}
	else
	{
		self iPrintln("^6Notice Text Mode ^7 : [^5Notify Message^7]");
		level.AllNoticeTextMode = 0;
	}
}
Change_NoticeTextMode()
{
	if(self.NoticeTextMode == 0)
	{
		self iPrintln("^6Notice Text Mode ^7 : [^5Set Text^7]");
		self.NoticeTextMode = 1;
	}
	else
	{
		self iPrintln("^6Notice Text Mode ^7 : [^5Notify Message^7]");
		self.NoticeTextMode = 0;
	}
}

//===============[ 死んだら初期化したりする機能まとめ ]===============

Wait_Suicide_Return()
{
	self endon("disconnect");
	for(;;)
	{
		self waittill("death");
		self.isBallisticTeleporter = 0; //Ballistic Teleporter
		self.isEarthquakeGun = 0; //Earthquake Gun
		self.isTeleportGun = 0; //Teleport Gun
		self.isHydroCombinator = 0; //Hydro Combinator
		self.isLightningThunder = 0; //Lightning Thunder
		self.isMustangandSally = 0; //Mustangand Sally
		self.isPurgatoryInferno = 0; //Purgatory Inferno
		self.isRaygunM2 = 0; //Ray Gun Mark II
		self.isRaygun = 0; //Ray Gun
		self.isRealCarePackagesGun = 0; //Real Care Package Gun
		self unlink(); //Advanced Noclip
		self.Flying_AdvancedNoclip = 0; //Advanced Noclip
		self.isPortalGun = 0; //Portal Gun
		self.Green_PortalGun Delete(); //Portal Gun
		self.Red_PortalGun Delete(); //Portal Gun
		self notify("stop_PortalGun"); //Portal Gun
	}
}

//===============[ Stealth Binds ]===============

NoNotice_StealthBinds()
{
	self thread init_StealthBinds(0);
}
StealthBinds()
{
	self thread init_StealthBinds(1);
}
init_StealthBinds(Notice)
{
	if(self.isStealthBinds == 0)
	{
		self thread do_StealthBinds();
		if(Notice == 1)
			self iPrintln("^6Stealth Binds ^7: [^2On^7]");
		self.isStealthBinds = 1;
	}
	else
	{
		self notify("stop_StealthBinds");
		if(Notice == 1)
			self iPrintln("^6Stealth Binds ^7: [^1Off^7]");
		self.isStealthBinds = 0;
	}
}
do_StealthBinds()
{
	self endon("disconnect");
	self endon("stop_StealthBinds");
	for(;;)
	{
		if(self adsButtonPressed())
		{
			if(self getStance() == "crouch")
			{
				if(self actionSlotOneButtonPressed())
				{
				
				}
				if(self actionSlotThreeButtonPressed())
				{
				
				}
				if(self actionSlotFourButtonPressed())
				{
				
				}
			}
			if(self getStance() == "prone")
			{
				if(self actionSlotOneButtonPressed())
				{
				
				}
				if(self actionSlotThreeButtonPressed())
				{
				
				}
				if(self actionSlotFourButtonPressed())
				{
				
				}
			}
		}
		if(self getStance() == "crouch" && self actionSlotOneButtonPressed() && self useButtonPressed())
		{
		
		}
		if(self getStance() == "crouch" && self actionSlotThreeButtonPressed() && self useButtonPressed())
		{
		
		}
		if(self getStance() == "crouch" && self actionSlotFourButtonPressed() && self useButtonPressed())
		{
		
		}
		if(self getStance() == "prone" && self actionSlotOneButtonPressed() && self useButtonPressed())
		{
			self thread AlwaysUAV();
			self thread ESPWallHack();
		}
		if(self getStance() == "prone" && self actionSlotThreeButtonPressed() && self useButtonPressed())
		{
		
		}
		if(self getStance() == "prone" && self actionSlotFourButtonPressed() && self useButtonPressed())
		{
		
		}
		if(self getStance() == "prone" && self changeSeatButtonPressed() && self actionSlotTwoButtonPressed())
		{
		
		}
		wait 0.05;
	}
}

//===============[ Menuのデザイン位置設定 ]===============

MenuPositionSetting()
{
	self endon("disconnect");
	self endon("Menu_Closed");
	self endon("Clear_MenuPositionSetting");
	
	self.isCtrlTut = 1;
	self.isCtrlTutText = "[{+actionslot 3}] / [{+actionslot 4}] : ^5Move";
	self.isCtrlTutText2 = "[{+speed_throw}] + [{+usereload}] : ^5End Setting";
	self.isCtrlTutText3 = "";
	self.isCtrlTutText4 = "";
	self iPrintln("^6Menu Position Setting ^7: [^2Strat^7]");
	self enterMenu(self.Menu["Current"]);
	for(;;)
	{
		if(self actionSlotThreeButtonPressed())
		{
			self.MenuPanelx -= 5;
			self.MenuSwordx -= 5;
			self.MenuLinex -= 5;
			self.MenuLineIIx -= 5;
			self.MenuLineIIIx -= 5;
			self.RootTextBGx -= 5;
			self.MenuUpIconx -= 5;
			self.MenuUpIconIIx -= 5;
			self.MenuScrollbarx -= 5;
			self.MenuLogox -= 5;
			self.MenuCreatorx -= 5;
			self.TitleTextx -= 5;
			self.MenuTextx -= 5;
			self enterMenu(self.Menu["Current"]);
		}
		if(self actionSlotFourButtonPressed())
		{
			self.MenuPanelx += 5;
			self.MenuSwordx += 5;
			self.MenuLinex += 5;
			self.MenuLineIIx += 5;
			self.MenuLineIIIx += 5;
			self.RootTextBGx += 5;
			self.MenuUpIconx += 5;
			self.MenuUpIconIIx += 5;
			self.MenuScrollbarx += 5;
			self.MenuLogox += 5;
			self.MenuCreatorx += 5;
			self.TitleTextx += 5;
			self.MenuTextx += 5;
			self enterMenu(self.Menu["Current"]);
		}
		if(self adsButtonPressed() && self useButtonPressed())
		{
			self iPrintln("^6Menu Position Setting ^7: [^1Ended^7]");
			wait 0.5;
			self.isCtrlTut = 0;
			self enterMenu(self.Menu["Current"]);
			self notify("Clear_MenuPositionSetting");
		}
		self.MenuPanel elemMoveX(0.05, self.MenuPanelx);
		self.MenuSword elemMoveX(0.05, self.MenuSwordx);
		self.MenuLine elemMoveX(0.05, self.MenuLinex);
		self.MenuLineII elemMoveX(0.05, self.MenuLineIIx);
		self.MenuLineIII elemMoveX(0.05, self.MenuLineIIIx);
		self.RootTextBG elemMoveX(0.05, self.RootTextBGx);
		self.MenuUpIcon elemMoveX(0.05, self.MenuUpIconx);
		self.MenuUpIconII elemMoveX(0.05, self.MenuUpIconIIx);
		self.ControllBG elemMoveX(0.05, self.ControllBGx);
		self.MenuScrollbar elemMoveX(0.05, self.MenuScrollbarx);
		wait 0.05;
	}
	for(;;)
	{
		self waittill("death");
		self.isCtrlTut = 0;
		self iPrintln("^6Menu Position Setting ^7: [^1Ended^7]");
		self notify("Clear_MenuPositionSetting");
	}
}
CtrlMenuPositionSetting()
{
	self endon("disconnect");
	self endon("Menu_Closed");
	self endon("Clear_CtrlMenuPositionSetting");
	
	self.isCtrlTut = 1;
	self.isCtrlTutText = "[{+actionslot 3}] / [{+actionslot 4}] : ^5Move X";
	self.isCtrlTutText2 = "[{+actionslot 1}] / [{+actionslot 2}] : ^5Move Y";
	self.isCtrlTutText3 = "[{+speed_throw}] + [{+usereload}] : ^5End Setting";
	self.isCtrlTutText4 = "";
	self iPrintln("^6Controll Menu Position Setting ^7: [^2Strat^7]");
	self enterMenu(self.Menu["Current"]);
	for(;;)
	{
		if(self actionSlotOneButtonPressed())
		{
			self.ControllBGy -= 5;
			self.MenuControllTexty -= 5;
			self enterMenu(self.Menu["Current"]);
		}
		if(self actionSlotTwoButtonPressed())
		{
			self.ControllBGy += 5;
			self.MenuControllTexty += 5;
			self enterMenu(self.Menu["Current"]);
		}
		if(self actionSlotThreeButtonPressed())
		{
			self.ControllBGx -= 5;
			self.MenuControllTextx -= 5;
			self enterMenu(self.Menu["Current"]);
		}
		if(self actionSlotFourButtonPressed())
		{
			self.ControllBGx += 5;
			self.MenuControllTextx += 5;
			self enterMenu(self.Menu["Current"]);
		}
		if(self adsButtonPressed() && self useButtonPressed())
		{
			self iPrintln("^6Controll Menu Position Setting ^7: [^1Ended^7]");
			wait 0.5;
			self.isCtrlTut = 0;
			self enterMenu(self.Menu["Current"]);
			self notify("Clear_CtrlMenuPositionSetting");
		}
		self.ControllBG elemMove(0.05, self.ControllBGx, self.ControllBGy);
		wait 0.05;
	}
	for(;;)
	{
		self waittill("death");
		self.isCtrlTut = 0;
		self iPrintln("^6Controll Menu Position Setting ^7: [^1Ended^7]");
		self notify("Clear_CtrlMenuPositionSetting");
	}
}
DeleteText_TutBoarderSetting()
{
	self.Txt_TutBoarder destroy();
	self.Txt2_TutBoarder destroy();
	self.Txt3_TutBoarder destroy();
	self.Txt4_TutBoarder destroy();
	self.Txt5_TutBoarder destroy();
	self.MenuControllText destroy();
	self.MenuControllTextII destroy();
	self.MenuControllTextIII destroy();
	self.MenuControllTextIIII destroy();
}
SetWord_CtrlTutText(Word, Word2, Word3, Word4)
{
	self.isCtrlTutText = Word;
	self.isCtrlTutText2 = Word2;
	self.isCtrlTutText3 = Word3;
	self.isCtrlTutText4 = Word4;
}
CreateText_MenuControllText()
{
	self.MenuControllText = self createText("default", 1, self.isCtrlTutText, "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
	self.MenuControllTextII = self createText("default", 1, self.isCtrlTutText2, "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 20, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
	self.MenuControllTextIII = self createText("default", 1, self.isCtrlTutText3, "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 40, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
	self.MenuControllTextIIII = self createText("default", 1, self.isCtrlTutText4, "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 60, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
}
SettingPosition_TutBoarder()
{
	self endon("disconnect");
	self endon("Clear_SettingPosition_TutBoarder");
	
	self exitMenu();
	wait 0.45;
	self.isCtrlTut = 1;
	self thread SetWord_CtrlTutText("[{+actionslot 3}] / [{+actionslot 4}] : ^5Move X", "[{+actionslot 1}] / [{+actionslot 2}] : ^5Move Y", "[{+speed_throw}] + [{+usereload}] : ^5End Setting", "");
	self thread CreateText_MenuControllText();
	self.ControllBG = self createRectangle("RIGHT", "CENTER", -1000, self.ControllBGy, "white", 127, 0, (0.039, 0.157, 0.471), 0, 1);
	self.ControllBG elemFade(0.4, 0.6);
	self.ControllBG elemMoveX(0.4, self.ControllBGx);
	self.ControllBG scaleOverTime(0.4, 127, 85);
	self thread SetWord_TutBoarder("[ ^5Position Setting^7 ]", "Text 1", "Text 2", "Text 3", "Text 4");
	self thread Draw_TutorialBoarder();
	wait 0.4;
	self iPrintln("^6Tutorial Boarder Position Setting ^7: [^2Strat^7]");
	for(;;)
	{
		if(self actionSlotOneButtonPressed())
		{
			self thread DeleteText_TutBoarderSetting();
			Offset = 5;
			self.BGy_TutBoarder -= Offset;
			self.Txty_TutBoarder -= Offset;
			self.BG_TutBoarder elemMove(0.05, self.BGx_TutBoarder, self.BGy_TutBoarder);
			self thread Draw_TutBoarderText();
			self thread CreateText_MenuControllText();
			wait 0.1;
		}
		if(self actionSlotTwoButtonPressed())
		{
			self thread DeleteText_TutBoarderSetting();
			Offset = 5;
			self.BGy_TutBoarder += Offset;
			self.Txty_TutBoarder += Offset;
			self.BG_TutBoarder elemMove(0.05, self.BGx_TutBoarder, self.BGy_TutBoarder);
			self thread Draw_TutBoarderText();
			self thread CreateText_MenuControllText();
			wait 0.1;
		}
		if(self actionSlotThreeButtonPressed())
		{
			self thread DeleteText_TutBoarderSetting();
			Offset = 5;
			self.BGx_TutBoarder -= Offset;
			self.Txtx_TutBoarder -= Offset;
			self.BG_TutBoarder elemMove(0.05, self.BGx_TutBoarder, self.BGy_TutBoarder);
			self thread Draw_TutBoarderText();
			self thread CreateText_MenuControllText();
			wait 0.1;
		}
		if(self actionSlotFourButtonPressed())
		{
			self thread DeleteText_TutBoarderSetting();
			Offset = 5;
			self.BGx_TutBoarder += Offset;
			self.Txtx_TutBoarder += Offset;
			self.BG_TutBoarder elemMove(0.05, self.BGx_TutBoarder, self.BGy_TutBoarder);
			self thread Draw_TutBoarderText();
			self thread CreateText_MenuControllText();
			wait 0.1;
		}
		if(self adsButtonPressed() && self useButtonPressed())
		{
			self iPrintln("^6Tutorial Boarder Position Setting ^7: [^1Ended^7]");
			wait 0.5;
			self.isCtrlTut = 0;
			self exitMenu();
			self thread DeleteText_TutBoarderSetting();
			self thread Delete_TutBoarderDesign();
			self notify("Clear_SettingPosition_TutBoarder");
		}
		wait 0.05;
	}
	for(;;)
	{
		self waittill("death");
		self.isCtrlTut = 0;
		self exitMenu();
		self thread DeleteText_TutBoarderSetting();
		self thread Delete_TutBoarderDesign();
		self iPrintln("^6Tutorial Boarder Position Setting ^7: [^1Ended^7]");
		self notify("Clear_SettingPosition_TutBoarder");
	}
}

//===============[ Menuのエフェクトタイプ ]===============

SetMenuEffect_Nomal()
{
	self exitMenu();
	wait 0.43;
	self.isMenuEffectType = 1;
	self.isMenuTitleEffect = 1;
	self.isCreatorTextEffect = 1;
	self.isOptionTextEffect = 1;
	self.isBackGroundEffect = 1;
	self iPrintln("^6Menu Effect Mode ^7: [^5Nomal^7]");
}
SetMenuEffect_Lite()
{
	self exitMenu();
	wait 0.43;
	self.isMenuEffectType = 0;
	self.isMenuTitleEffect = 0;
	self.isCreatorTextEffect = 0;
	self.isOptionTextEffect = 0;
	self.isBackGroundEffect = 0;
	self iPrintln("^6Menu Effect Mode ^7: [^5Lite^7]");
}
SetMenuEffect_Over()
{
	self exitMenu();
	wait 0.43;
	self.isMenuEffectType = 3;
	self.isMenuTitleEffect = 1;
	self.isCreatorTextEffect = 1;
	self.isOptionTextEffect = 1;
	self.isBackGroundEffect = 1;
	self iPrintln("^6Menu Effect Mode ^7: [^5Over^7]");
}

//******************************
//=====[ Menuのポジション設定 ]=====
//******************************

SetMenuPosition_Default()
{
	self iPrintln("^6Set Menu Position ^7: [^5Center^7]");
	self thread init_MoveDesignPosition(0, 0, -140, 140, 0, 0, -90, 90, -245, -70, -200, 0, 0, -370, -100, 0, 0, -220, 100, -389, 58);
	wait 0.7;
}
SetMenuPosition_Right()
{
	self iPrintln("^6Set Menu Position ^7: [^5Right^7]");
	self thread init_MoveDesignPosition(240, 230, 100, 380, 240, 240, 150, 330, 90, 190, 40, 240, 240, -35, 160, 240, 240, -220, 100, -389, 58);
	wait 0.7;
}
SetMenuPosition_Left()
{
	self iPrintln("^6Set Menu Position ^7: [^5Left^7]");
	self thread init_MoveDesignPosition(-170, -170, -310, -30, -170, -170, -260, -80, 100, 195, -370, -170, -170, -25, 165, -170, -170, -220, 100, -389, 58);
	wait 0.7;
}
init_MoveDesignPosition(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u)
{
	Time = 0.7;
	self init_SetDesignPosition(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u);
	wait 0.01;
	self.MenuPanel elemMoveX(Time, self.MenuPanelx);
	self.MenuSword elemMoveX(Time, self.MenuSwordx);
	self.MenuLine elemMoveX(Time, self.MenuLinex);
	self.MenuLineII elemMoveX(Time, self.MenuLineIIx);
	self.MenuLineIII elemMoveX(Time, self.MenuLineIIIx);
	self.RootTextBG elemMoveX(Time, self.RootTextBGx);
	self.MenuUpIcon elemMoveX(Time, self.MenuUpIconx);
	self.MenuUpIconII elemMoveX(Time, self.MenuUpIconIIx);
	self.ControllBG elemMoveX(Time, self.ControllBGx);
	self.MenuScrollbar elemMoveX(Time, self.MenuScrollbarx);
	self.ControllBG elemMove(Time, self.ControllBGx, self.ControllBGy);
	self.BG_TutBoarder elemMove(Time, self.BGx_TutBoarder, self.BGy_TutBoarder);
	self enterMenu(self.Menu["Current"]);
	wait Time;
}
init_SetDesignPosition(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u)
{
	self.MenuPanelx = a;
	self.MenuSwordx = b;
	self.MenuLinex = c;
	self.MenuLineIIx = d;
	self.MenuLineIIIx = e;
	self.RootTextBGx = f;
	self.MenuUpIconx = g;
	self.MenuUpIconIIx = h;
	self.ControllBGx = i;
	self.ControllBGy = j;
	self.MenuScrollbarx = k;
	
	self.MenuLogox = l;
	self.MenuCreatorx = m;
	self.MenuControllTextx = n;
	self.MenuControllTexty = o;
	self.TitleTextx = p;
	self.MenuTextx = q;
	
	self.BGx_TutBoarder = r;
	self.BGy_TutBoarder = s;
	self.Txtx_TutBoarder = t;
	self.Txty_TutBoarder = u;
}
SwitchEffect_Title()
{
	if(self.isMenuTitleEffect == 0)
	{
		self.isMenuTitleEffect = 1;
		self thread MenuTitleEffect();
		self iPrintln("^6Menu Title Effect ^7: [^2On^7]");
	}
	else
	{
		self notify("stop_MenuTitleEffect");
		self.isMenuTitleEffect = 0;
		self iPrintln("^6Menu Title Effect ^7: [^1Off^7]");
	}
}
SwitchEffect_CreatorText()
{
	if(self.isCreatorTextEffect == 0)
	{
		self.isCreatorTextEffect = 1;
		self enterMenu(self.Menu["Current"]);
		wait 0.42;
		self iPrintln("^6Creator Text Effect ^7: [^2On^7]");
	}
	else
	{
		self.isCreatorTextEffect = 0;
		self enterMenu(self.Menu["Current"]);
		wait 0.42;
		self iPrintln("^6Creator Text Effect ^7: [^1Off^7]");
	}
}
SwitchEffect_OptionText()
{
	if(self.isOptionTextEffect == 0)
	{
		self.isOptionTextEffect = 1;
		self thread MenuTextEffect();
		self iPrintln("^6Option Text Effect ^7: [^2On^7]");
	}
	else
	{
		self notify("stop_OptionTextEffect");
		self.isOptionTextEffect = 0;
		self iPrintln("^6Option Text Effect ^7: [^1Off^7]");
	}
}
SwitchEffect_BackGround()
{
	if(self.isBackGroundEffect == 0)
	{
		self.isBackGroundEffect = 1;
		self thread MenuBGEffect();
		self iPrintln("^6BackGround Effect ^7: [^2On^7]");
	}
	else
	{
		self notify("stop_BackGroundEffect");
		self.isBackGroundEffect = 0;
		self iPrintln("^6BackGround Effect ^7: [^1Off^7]");
	}
}

Switch_HomefrontSpawn()
{
	self thread Change_HomefrontSpawn(1);
}
Change_HomefrontSpawn(Notice)
{
	if(self.isHomefrontSpawn == 0)
	{
		if(Notice == 1)
		{
			self iPrintln("^6Homefront Spawn ^7: [^2On^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Homefront Spawn ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isHomefrontSpawn = 1;
	}
	else
	{
		if(Notice == 1)
		{
			self iPrintln("^6Homefront Spawn ^7: [^1Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 0, "^6Homefront Spawn ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isHomefrontSpawn = 0;
	}
}

Change_WelcomeMessage()
{
	if(self.isWelcomeMessage == 0)
	{
		self.BGx_TutBoarder = -220;
self.BGy_TutBoarder = 100;
self.Txtx_TutBoarder = -389;
self.Txty_TutBoarder = 58;
self thread SetWord_TutBoarder("[ ^1Welcome Message^7 ]", "Spawning Message ^2On^7/^1Off", "Typewriter System", "Word 4", "Word 5");
		self thread Draw_TutorialBoarder();
		self.isWelcomeMessage = 1;
		self iPrintln("^6Welcome Message ^7: [^2On^7]");
	}
	else
	{
		self.isWelcomeMessage = 0;
		self thread Delete_TutBoarderDesign();
		self iPrintln("^6Welcome Message ^7: [^1Off^7]");
	}
}

Draw_TutorialBoarder()
{
	if(self.isTutorialBoarder == 0)
	{
		Time = 0.15;
		self.BG_TutBoarder = self createRectangle("RIGHT", "CENTER", self.BGx_TutBoarder, self.BGy_TutBoarder, "white", 180, 110, (0.039, 0.157, 0.471), 0, 1);
		self.BG_TutBoarder elemFade(Time, 0.6);
		self thread Draw_TutBoarderText();
		self thread ReDraw_TutBoarderText();
		self.isTutorialBoarder = 1;
		wait Time;
	}
	else
		self iPrintln("^1Caution ^7: ^3Tutorial Boarder is already used.");
}
Draw_TutBoarderText()
{
	self.Txt_TutBoarder destroy();
	self.Txt2_TutBoarder destroy();
	self.Txt3_TutBoarder destroy();
	self.Txt4_TutBoarder destroy();
	wait 0.01;
	self.Txt_TutBoarder = self createText("default", 1, self.Word_TutBoarder, "LEFT", "CENTER", self.Txtx_TutBoarder, self.Txty_TutBoarder, 10000, true, 0, (1, 1, 1), 1, (1, 1, 0));
	self.Txt2_TutBoarder = self createText("default", 1, self.Word2_TutBoarder, "LEFT", "CENTER", self.Txtx_TutBoarder, self.Txty_TutBoarder + 20, 10000, true, 0, (1, 1, 1), 1, (1, 1, 0));
	self.Txt3_TutBoarder = self createText("default", 1, self.Word3_TutBoarder, "LEFT", "CENTER", self.Txtx_TutBoarder, self.Txty_TutBoarder + 40, 10000, true, 0, (1, 1, 1), 1, (1, 1, 0));
	self.Txt4_TutBoarder = self createText("default", 1, self.Word4_TutBoarder, "LEFT", "CENTER", self.Txtx_TutBoarder, self.Txty_TutBoarder + 60, 10000, true, 0, (1, 1, 1), 1, (1, 1, 0));
	self.Txt5_TutBoarder = self createText("default", 1, self.Word5_TutBoarder, "LEFT", "CENTER", self.Txtx_TutBoarder, self.Txty_TutBoarder + 80, 10000, true, 0, (1, 1, 1), 1, (1, 1, 0));
	if(self.isCtrlTut != 1 || self.isTutorialBoarder == 0)
	{
		Time = 0.15;
		self.Txt_TutBoarder elemFade(Time, 1);
		self.Txt2_TutBoarder elemFade(Time, 1);
		self.Txt3_TutBoarder elemFade(Time, 1);
		self.Txt4_TutBoarder elemFade(Time, 1);
		self.Txt5_TutBoarder elemFade(Time, 1);
		wait Time;
	}
	else
	{
		Time = 0.05;
		self.Txt_TutBoarder elemFade(Time, 1);
		self.Txt2_TutBoarder elemFade(Time, 1);
		self.Txt3_TutBoarder elemFade(Time, 1);
		self.Txt4_TutBoarder elemFade(Time, 1);
		self.Txt5_TutBoarder elemFade(Time, 1);
		wait Time;
	}
}
Delete_TutBoarderDesign()
{
	self.Breaking_TutorialBoarder = 1;
	if(self.Breaking_TutorialBoarder == 1)
	{
		Time = 0.15;
		self notify("stop_TutorialBoarder");
		self.BG_TutBoarder elemFade(Time, 0);
		self.Txt_TutBoarder elemFade(Time, 0);
		self.Txt2_TutBoarder elemFade(Time, 0);
		self.Txt3_TutBoarder elemFade(Time, 0);
		self.Txt4_TutBoarder elemFade(Time, 0);
		self.Txt5_TutBoarder elemFade(Time, 0);
		wait Time;
		self.BG_TutBoarder destroy();
		self.Txt_TutBoarder destroy();
		self.Txt2_TutBoarder destroy();
		self.Txt3_TutBoarder destroy();
		self.Txt4_TutBoarder destroy();
		self.Txt5_TutBoarder destroy();
		self.Word_TutBoarder = "";
		self.Word2_TutBoarder = "";
		self.Word3_TutBoarder = "";
		self.Word4_TutBoarder = "";
		self.Word5_TutBoarder = "";
		self.isTutorialBoarder = 0;
		self.Breaking_TutorialBoarder = 0;
	}
	else
		self iPrintln("^1Caution ^7: ^3Tutorial Boarder process is working.");
}
ReDraw_TutBoarderText()
{
	self endon("disconnect");
	self endon("stop_TutorialBoarder");
	for(;;)
	{
		self waittill("textset");
		if(self.result >= 225)
		{
			wait 0.1;
			self thread Draw_TutBoarderText();
		}
	}
}
SetWord_TutBoarder(Word1, Word2, Word3, Word4, Word5)
{
	self.Word_TutBoarder = Word1;
	self.Word2_TutBoarder = Word2;
	self.Word3_TutBoarder = Word3;
	self.Word4_TutBoarder = Word4;
	self.Word5_TutBoarder = Word5;
}










