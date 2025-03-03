//******************************
//=====[ Menuデザイン表示関係 ]=====
//******************************

enterMenu(menu)
{
	self.Menu["Current"] = menu;
	self notify("Menu_Opened");
	self playLocalSound("oldschool_pickup");

	if(!isDefined(self.Menu["Scroller"][self.Menu["Current"]]))
		self.Menu["Scroller"][self.Menu["Current"]] = 0;
	else
		self.Menu["Scroller"][self.Menu["Current"]] = self.Menu["Scroller"][self.Menu["Current"]];

	self thread updateMenuStructure();
	self thread createMenuText();
}
updateMenuScrollbar()
{
	self.MenuMenuScrollbar.y = (self.Menu["Scroller"][self.Menu["Current"]] * 20) + 70;
}

//******************************
//=====[ 文字表示～文字エフェクト ]=====
//******************************

createMenuText()
{
	if(self.isMenuEffectType == 0)
		Time = 0.1;
	else if(self.isMenuEffectType == 1)
		Time = 0.4;
		
	if(self.MenuOpen == false)
	{
		self.MenuLogo = self createText("default", 1.8, "^1F^0a^1t^0e^3/^1E^0x^1c^0a^1l^0i^1b^0u^1r", "CENTER", "TOP", self.MenuLogox, -10, 10000, true, 0, (1, 1, 1), 1, (1, 1, 1));
		self.MenuLogo elemFade(Time, 1);
		if(self.isCreatorTextEffect == 0)
			self.MenuCreator = self createText("default", 1.2, "by. ^1A^2s^3T^5y", "CENTER", "TOP", self.MenuCreatorx, 30, 10000, true, 0, (1, 1, 1), 1, (1, 1, 0));
		else
			self.MenuCreator = self createText("default", 1.2, "by. ^F^1A^2s^3T^5y", "CENTER", "TOP", self.MenuCreatorx, 30, 10000, true, 0, (1, 1, 1), 1, (1, 1, 0));
		self.MenuCreator elemFade(Time, 1);
		self.MenuControllText = self createText("default", 1, "[{+actionslot 1}] / [{+actionslot 2}] : ^5Scroll", "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty, 10000, true, 0, (1, 1, 1), 1, (1, 1, 0));
		self.MenuControllText elemFade(Time, 1);
		self.MenuControllTextII = self createText("default", 1, "[{+usereload}] : ^5Select", "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 20, 10000, true, 0, (1, 1, 1), 1, (1, 1, 0));
		self.MenuControllTextII elemFade(Time, 1);
		self.MenuControllTextIII = self createText("default", 1, "[{+speed_throw}] + [{+actionslot 3}] : ^5Back", "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 40, 10000, true, 0, (1, 1, 1), 1, (1, 1, 0));
		self.MenuControllTextIII elemFade(Time, 1);
		self.MenuControllTextIIII = self createText("default", 1, "[{+speed_throw}] + [{+stance}] : ^5Close Menu", "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 60, 10000, true, 0, (1, 1, 1), 1, (1, 1, 0));
		self.MenuControllTextIIII elemFade(Time, 1);
	}
	else
	{
		self.MenuLogo = self createText("default", 1.8, "Test Release Menu", "CENTER", "TOP", self.MenuLogox, -10, 10000, true, 1, (1, 1, 1), 1, (1, 1, 1));
		if(self.isCreatorTextEffect == 0)
			self.MenuCreator = self createText("default", 1.2, "by. ^1A^2s^3T^5y", "CENTER", "TOP", self.MenuCreatorx, 30, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
		else
			self.MenuCreator = self createText("default", 1.2, "by. ^F^1A^2s^3T^5y", "CENTER", "TOP", self.MenuCreatorx, 30, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
		if(self.isCtrlTut == 0)
		{
			self.MenuControllText = self createText("default", 1, "[{+actionslot 1}] / [{+actionslot 2}] : ^5Scroll", "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
			self.MenuControllTextII = self createText("default", 1, "[{+usereload}] : ^5Select", "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 20, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
			self.MenuControllTextIII = self createText("default", 1, "[{+speed_throw}] + [{+actionslot 3}] : ^5Back", "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 40, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
			self.MenuControllTextIIII = self createText("default", 1, "[{+speed_throw}] + [{+stance}] : ^5Close Menu", "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 60, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
		}
		else
		{
			self.MenuControllText = self createText("default", 1, self.isCtrlTutText, "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
			self.MenuControllTextII = self createText("default", 1, self.isCtrlTutText2, "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 20, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
			self.MenuControllTextIII = self createText("default", 1, self.isCtrlTutText3, "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 40, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
			self.MenuControllTextIIII = self createText("default", 1, self.isCtrlTutText4, "LEFT", "CENTER", self.MenuControllTextx, self.MenuControllTexty + 60, 10000, true, 1, (1, 1, 1), 1, (1, 1, 0));
		}
	}
	self.TitleText = self createText("default", 1, self.Menu["Title"][self.Menu["Current"]], "CENTER", "TOP", self.TitleTextx, 50, 10000, true, 0, (1, 1, 1), 1, (0, 1, 1));
	self.TitleText elemFade(Time, 1);
	
	self thread destroyOnAny(self.MenuLogo, "Menu_Opened", "Menu_Closed");
	self thread destroyOnAny(self.MenuCreator, "Menu_Opened", "Menu_Closed");
	self thread destroyOnAny(self.TitleText, "Menu_Opened", "Menu_Closed");
	self thread destroyOnAny(self.MenuControllText, "Menu_Opened", "Menu_Closed");
	self thread destroyOnAny(self.MenuControllTextII, "Menu_Opened", "Menu_Closed");
	self thread destroyOnAny(self.MenuControllTextIII, "Menu_Opened", "Menu_Closed");
	self thread destroyOnAny(self.MenuControllTextIIII, "Menu_Opened", "Menu_Closed");

	if(self.isMenuTitleEffect == 1)
		self thread MenuTitleEffect();
	if(self.isOptionTextEffect == 1)
		self thread MenuTextEffect();
	self thread ScrollbarEffect();
	self thread MenuTextEnabled();
	for(i = 0; i < self.Menu[self.Menu["Current"]].size; i++)
	{
		self.string = (self.Menu[self.Menu["Current"]][i].label);
		if(self.MenuOpen == false)
			WSize = 2.4;
		else
			WSize = 1;
		self.MenuText[i] = self createText("hudbig", WSize, self.string, "CENTER", "TOP", self.MenuTextx, 80 + (i * 20), 10000, true, 0, (1, 1, 1));
		self.MenuText[i] elemFade(Time, 1);
		self.MenuText[i].archived = false;
		self thread destroyOnAny(self.MenuText[i], "Menu_Opened", "Menu_Closed");
	}
}
MenuTitleEffect()
{
	self endon("disconnect");
	self endon("Menu_Opened");
	self endon("Menu_Closed");
	self endon("stop_MenuTitleEffect");
	for(;;)
	{
		self.MenuLogo elemGlow(0.05, (1, 0.149, 0.149), 1);
		wait 0.05;
		self.MenuLogo elemGlow(0.05, (1, 0.341, 0.149), 1);
		wait 0.05; //0.1
		self.MenuLogo elemGlow(0.05, (1, 0.553, 0.149), 1);
		wait 0.05;
		self.MenuLogo elemGlow(0.05, (1, 0.788, 0.149), 1);
		wait 0.05; //0.2
		self.MenuLogo elemGlow(0.05, (0.980, 1, 0.149), 1);
		wait 0.05;
		self.MenuLogo elemGlow(0.05, (0.745, 1, 0.149), 1);
		wait 0.05; //0.3
		self.MenuLogo elemGlow(0.05, (0.149, 1, 0.212), 1);
		wait 0.05;
		self.MenuLogo elemGlow(0.05, (0.149, 1, 0.706), 1);
		wait 0.05; //0.4
		self.MenuLogo elemGlow(0.05, (0.149, 1, 0.980), 1);
		wait 0.05;
		self.MenuLogo elemGlow(0.05, (0.149, 0.745, 1), 1);
		wait 0.05; //0.5
		self.MenuLogo elemGlow(0.05, (0.149, 0.404, 1), 1);
		wait 0.05;
		self.MenuLogo elemGlow(0.05, (0.302, 0.149, 1), 1);
		wait 0.05; //0.6
		self.MenuLogo elemGlow(0.05, (0.576, 0.149, 1), 1);
		wait 0.05;
		self.MenuLogo elemGlow(0.05, (0.788, 0.149, 1), 1);
		wait 0.05; //0.7
		self.MenuLogo elemGlow(0.05, (1, 0.149, 1), 1);
		wait 0.05;
		self.MenuLogo elemGlow(0.05, (1, 0.149, 0.788), 1);
		wait 0.05; //0.8
		self.MenuLogo elemGlow(0.05, (1, 0.149, 0.490), 1);
		wait 0.05;
		self.MenuLogo elemGlow(0.05, (1, 0.149, 0.384), 1);
		wait 0.05; //0.9
		self.MenuLogo elemGlow(0.05, (0.992, 0.157, 0.180), 1);
		wait 0.05;
	}
}
ScrollbarEffect()
{
	self endon("disconnect");
	self endon("Menu_Opened");
	self endon("Menu_Closed");
	self endon("Option_Enabled");
	for(;;)
	{
		for(i = 0; i < self.Menu[self.Menu["Current"]].size; i++)
		{
			if(i == self.Menu["Scroller"][self.Menu["Current"]])
			{
				self.MenuText[i] scaleFont(0.1, 1.4);
				self.MenuText[i] elemGlow(0.01, (1, 0, 0), 1);
			}
			else
			{
				self.MenuText[i] scaleFont(0.1, 1);
				self.MenuText[i] elemGlow(0.01, (0, 0, 0), 0);
			}
		}
		wait 0.05;
	}
}
MenuTextEffect()
{
	self endon("disconnect");
	self endon("Menu_Opened");
	self endon("Menu_Closed");
	self endon("Option_Enabled");
	self endon("stop_OptionTextEffect");
	for(;;)
	{
		for(i = 0; i < self.Menu[self.Menu["Current"]].size; i++)
		{
			if(i == self.Menu["Scroller"][self.Menu["Current"]])
			{
				self.MenuText[i] elemGlow(0.01, (0.980, 0.682, 0.129), 1);
				wait 0.01;
				self.MenuText[i] elemGlow(0.01, (0.780, 0.969, 0.141), 1);
				wait 0.01;
				self.MenuText[i] elemGlow(0.01, (0.133, 0.976, 0.533), 1);
				wait 0.01;
				self.MenuText[i] elemGlow(0.01, (0.133, 0.976, 0.533), 1);
				wait 0.01;
				self.MenuText[i] elemGlow(0.01, (0.129, 0.322, 0.980), 1);
				wait 0.01;
			}
		}
		wait 0.05;
	}
}
MenuTextEnabled()
{
	self waittill("Option_Enabled");
	for(i = 0; i < self.Menu[self.Menu["Current"]].size; i++)
	{
		if(i == self.Menu["Scroller"][self.Menu["Current"]])
		{
			self.MenuText[i] elemGlow(0.15, (1, 1, 0), 1);
		}
	}
	wait 0.15;
	if(self.isOptionTextEffect == 1)
		self thread MenuTextEffect();
	self thread ScrollbarEffect();
	self thread MenuTextEnabled();
}


//******************************
//=====[ BG(背景) 生成～削除 ]=====
//******************************

createMenuBG()
{
	if(self.isMenuEffectType == 0)
	{
		self.MenuPanel = self createRectangle("CENTER", "CENTER", self.MenuPanelx, 0, "white", 280, 800, (0.039, 0.157, 0.471), 0, 1);
		self.MenuPanel elemFade(0.1, 0.6);
		//self.MenuSword = self createRectangle("CENTER", "CENTER", self.MenuSwordx, 89, "line_horizontal", 180, 450, (0.910, 0.929, 0.122), 0, 2);
		//self.MenuSword elemFade(0.4, 0.6);
		self.MenuLine = self createRectangle("CENTER", "CENTER", self.MenuLinex, 0, "white", 5, 800, (0.910, 0.929, 0.122), 0, 2);
		self.MenuLine elemFade(0.1, 0.9);
		self.MenuLineII = self createRectangle("CENTER", "CENTER", self.MenuLineIIx, 0, "white", 5, 800, (0.910, 0.929, 0.122), 0, 2);
		self.MenuLineII elemFade(0.1, 0.9);
		self.MenuLineIII = self createRectangle("CENTER", "TOP", self.MenuLineIIIx, 65, "white", 278, 5, (1, 1, 1), 0, 2);
		self.MenuLineIII elemFade(0.1, 0.9);
		self.RootTextBG = self createRectangle("CENTER", "TOP", self.RootTextBGx, 50, "white", 210, 15, (0, 0, 0), 0, 2);
		self.RootTextBG elemFade(0.1, 0.7);
		/*self.MenuUpIcon = self createRectangle("CENTER", "TOP", self.MenuUpIconx, 20, "faction_seals", 35, 35, (1, 1, 1), 0, 2);
		self.MenuUpIcon elemFade(0.4, 0.9);
		self.MenuUpIconII = self createRectangle("CENTER", "TOP", self.MenuUpIconIIx, 20, "faction_pmc", 35, 35, (1, 1, 1), 0, 2);
		self.MenuUpIconII elemFade(0.4, 0.9);*/
		self.ControllBG = self createRectangle("RIGHT", "CENTER", self.ControllBGx, self.ControllBGy, "white", 127, 85, (0.039, 0.157, 0.471), 0, 1);
		self.ControllBG elemFade(0.1, 0.6);
		self.MenuScrollbar = self createRectangle("RIGHT", "TOP", self.MenuScrollbarx, (self.Menu["Scroller"][self.Menu["Current"]] * 20) + 70, "white", 300, 18, (0, 0, 0), 0, 2);
		wait 0.1;
	}
	else if(self.isMenuEffectType == 1)
	{
		self.MenuPanel = self createRectangle("CENTER", "CENTER", self.MenuPanelx, 0, "white", 280, 0, (0.039, 0.157, 0.471), 0, 1);
		self.MenuPanel elemFade(0.4, 0.6);
		self.MenuPanel scaleOverTime(0.4, 280, 800);
		self.MenuSword = self createRectangle("CENTER", "CENTER", self.MenuSwordx, 89, "line_horizontal", 0, 450, (0.910, 0.929, 0.122), 0, 2);
		self.MenuSword elemFade(0.4, 0.6);
		self.MenuSword scaleOverTime(0.4, 180, 450);
		self.MenuLine = self createRectangle("CENTER", "CENTER", -250, 0, "white", 100, 800, (0.910, 0.929, 0.122), 0, 2);
		self.MenuLine elemFade(0.4, 0.9);
		self.MenuLine elemMoveX(0.4, self.MenuLinex);
		self.MenuLine scaleOverTime(0.4, 5, 800);
		self.MenuLineII = self createRectangle("CENTER", "CENTER", 250, 0, "white", 100, 800, (0.910, 0.929, 0.122), 0, 2);
		self.MenuLineII elemFade(0.4, 0.9);
		self.MenuLineII elemMoveX(0.4, self.MenuLineIIx);
		self.MenuLineII scaleOverTime(0.4, 5, 800);
		self.MenuLineIII = self createRectangle("CENTER", "TOP", self.MenuLineIIIx, 65, "white", 600, 25, (1, 1, 1), 0, 2);
		self.MenuLineIII elemFade(0.4, 0.9);
		self.MenuLineIII scaleOverTime(0.4, 278, 5);
		self.RootTextBG = self createRectangle("CENTER", "TOP", self.RootTextBGx, -1000, "white", 210, 15, (0, 0, 0), 0, 2);
		self.RootTextBG elemFade(0.4, 0.7);
		self.RootTextBG elemMoveY(0.3, 50);
		self.MenuUpIcon = self createRectangle("CENTER", "TOP", self.MenuUpIconx, 20, "faction_seals", 0, 0, (1, 1, 1), 0, 2);
		self.MenuUpIcon elemFade(0.4, 0.9);
		self.MenuUpIcon scaleOverTime(0.4, 35, 35);
		self.MenuUpIconII = self createRectangle("CENTER", "TOP", self.MenuUpIconIIx, 20, "faction_pmc", 0, 0, (1, 1, 1), 0, 2);
		self.MenuUpIconII elemFade(0.4, 0.9);
		self.MenuUpIconII scaleOverTime(0.4, 35, 35);
		self.ControllBG = self createRectangle("RIGHT", "CENTER", -1000, self.ControllBGy, "white", 127, 0, (0.039, 0.157, 0.471), 0, 1);
		self.ControllBG elemFade(0.4, 0.6);
		self.ControllBG elemMoveX(0.4, self.ControllBGx);
		self.ControllBG scaleOverTime(0.4, 127, 85);
		self.MenuScrollbar = self createRectangle("RIGHT", "TOP", self.MenuScrollbarx, (self.Menu["Scroller"][self.Menu["Current"]] * 20) + 70, "white", 300, 18, (0, 0, 0), 0, 2);
		wait 0.4;
	}
	if(self.isBackGroundEffect == 1)
		self thread MenuBGEffect();
}
MenuBGEffect()
{
	self endon("disconnect");
	self endon("Menu_Closed");
	self endon("stop_BackGroundEffect");
	for(;;)
	{
		self.MenuPanel elemColor(0.5, (0.071, 0.055, 0.722));
		self.ControllBG elemColor(0.5, (0.071, 0.055, 0.722));
		self.MenuSword elemColor(0.5, (0.792, 0.894, 0.047));
		self.MenuLine elemColor(0.5, (0.792, 0.808, 0.176));
		self.MenuLineII elemColor(0.5, (0.792, 0.808, 0.176));
		self.MenuLineIII elemColor(0.5, (0.835, 0.835, 0.835));
		wait 0.5;
		self.MenuPanel elemColor(0.5, (0.039, 0.157, 0.471));
		self.ControllBG elemColor(0.5, (0.039, 0.157, 0.471));
		self.MenuSword elemColor(0.5, (0.910, 0.929, 0.122));
		self.MenuLine elemColor(0.5, (0.910, 0.929, 0.122));
		self.MenuLineII elemColor(0.5, (0.910, 0.929, 0.122));
		self.MenuLineIII elemColor(0.5, (1, 1, 1));
		wait 0.5;
	}
}
CloseMenuDesign()
{
	if(self.isMenuEffectType == 0)
	{
		Time = 0.15;
		self.MenuPanel elemFade(Time, 0);
		self.MenuLine elemFade(Time, 0);
		self.MenuLineII elemFade(Time, 0);
		self.MenuLineIII elemFade(Time, 0);
		self.RootTextBG elemFade(Time, 0);
		self.ControllBG elemFade(Time, 0);
		wait Time;
		self.MenuPanel destroy();
		self.MenuLine destroy();
		self.MenuLineII destroy();
		self.MenuLineIII destroy();
		self.RootTextBG destroy();
		self.ControllBG destroy();
		self.MenuScrollbar destroy();
	}
	else if(self.isMenuEffectType == 1)
	{
		Time = 0.4;
		self.MenuPanel elemFade(Time, 0);
		self.MenuPanel scaleOverTime(Time, 0, 800);
		self.MenuPanel elemMoveY(Time, -1000);
		self.MenuSword elemFade(Time, 0);
		self.MenuSword scaleOverTime(Time, 0, 450);
		self.MenuSword elemMoveY(Time, 1000);
		self.MenuLine elemFade(Time, 0);
		self.MenuLine elemMove(Time, -1000, 1000);
		self.MenuLine scaleOverTime(0.4, 100, 100);
		self.MenuLineII elemFade(Time, 0);
		self.MenuLineII elemMove(Time, 1000, 1000);
		self.MenuLineII scaleOverTime(Time, 100, 100);
		self.MenuLineIII elemFade(Time, 0);
		self.MenuLineIII scaleOverTime(Time, 1000, 1000);
		self.RootTextBG elemFade(Time, 0);
		self.RootTextBG scaleOverTime(Time, 0, 15);
		self.MenuUpIcon elemFade(Time, 0);
		self.MenuUpIcon scaleOverTime(Time, 0, 0);
		self.MenuUpIconII elemFade(Time, 0);
		self.MenuUpIconII scaleOverTime(Time, 0, 0);
		self.ControllBG elemFade(Time, 0);
		self.ControllBG elemMoveX(Time, -800);
		wait Time;
		self.MenuPanel destroy();
		self.MenuSword destroy();
		self.MenuLine destroy();
		self.MenuLineII destroy();
		self.MenuLineIII destroy();
		self.RootTextBG destroy();
		self.MenuUpIcon destroy();
		self.MenuUpIconII destroy();
		self.ControllBG destroy();
		self.MenuScrollbar destroy();
	}
}
WaitDeath_MenuClose()
{
	self waittill("death");
	self exitMenu();
}










