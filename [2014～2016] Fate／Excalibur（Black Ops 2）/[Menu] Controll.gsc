monitorActions()
{
	self endon("disconnect");
	self endon("death");
	self endon("stop_MenuMonitor");
       
	self.MenuOpen = false;
	self.Info["Cursor"] = 0;
       
	for(;;)
	{
	if(self.isCtrlTut == 0)
	{
		if(self.MenuOpen == false)
		{
			if(self adsButtonPressed() && self meleeButtonPressed() || self adsButtonPressed() && self actionSlotOneButtonPressed())
			{
				self initMenu();
			}
		}
		else if(self.MenuOpen == true)
		{
			if(self actionslotonebuttonpressed())
			{
				self doScrolling(-1);
				wait 0.1;
			}
			if(self actionSlotTwoButtonPressed())
			{
				self doScrolling(1);
				wait 0.1;
			}
			if(self UseButtonPressed())
			{
				self thread [[self.Menu[self.Menu["Current"]][self.Menu["Scroller"][self.Menu["Current"]]].action]](self.Menu[self.Menu["Current"]][self.Menu["Scroller"][self.Menu["Current"]]].arg);
				self notify("Option_Enabled");
				wait 0.15;
			}
			if(self adsButtonPressed() && self stanceButtonPressed())
			{
				self exitMenu();
			}
			if(self adsButtonPressed() && self actionSlotThreeButtonPressed())
			{
				if(isDefined(self.Menu["Parents"][self.Menu["Current"]]))
				{
					self enterMenu(self.Menu["Parents"][self.Menu["Current"]]);
					wait 0.1;
				}
				else
				{
					self exitMenu();
				}
			}
		}
	}
		wait 0.05;
	}
}

initMenu()
{
	self.result = 226;
	self notify("textset");
	wait 0.01;
	if(self.isMenuEffectType == 0)
		Time = 0.12;
	else if(self.isMenuEffectType == 1)
		Time = 0.42;
	self freezeControls(0);
	self enterMenu("Main");
	self thread createMenuBG();
	self thread WaitDeath_MenuClose();
	wait Time;
	//self thread ReCreateMenuOpen();
	self.MenuOpen = true;
}
exitMenu()
{
	self freezecontrols(0);
	self notify("Menu_Closed");
	self thread CloseMenuDesign();
	if(self.isMenuEffectType == 0)
		Time = 0.12;
	else if(self.isMenuEffectType == 1)
		Time = 0.42;
	wait Time;
	self.MenuOpen = false;
}
//Scrolling Function
doScrolling(num)
{
	self endon("disconnect");
	self endon("death");

	if(num == 0)
		self.Menu["Scroller"][self.Menu["Current"]] = 0;
	else if(num == self.Menu[self.Menu["Current"]].size - 1)
		self.Menu["Scroller"][self.Menu["Current"]] = self.Menu[self.Menu["Current"]].size - 1;
	else
		self.Menu["Scroller"][self.Menu["Current"]] += num;

	if(self.Menu["Scroller"][self.Menu["Current"]] < 0)
		self.Menu["Scroller"][self.Menu["Current"]] = self.Menu[self.Menu["Current"]].size - 1;
	else if(self.Menu["Scroller"][self.Menu["Current"]] > self.Menu[self.Menu["Current"]].size - 1)
		self.Menu["Scroller"][self.Menu["Current"]] = 0;

	self updateMenuScrollbar();
}


















