//******************************
//=====[ Menu制作に欠かせない、解析用コードページ ]=====
//******************************

Check_Weapon()
{
	Weapon = self GetCurrentWeapon();
	self iPrintln("^6This Weapon ^7: [^5" + Weapon + "^7]");
}
Check_DesignPos()
{
	Time = 3;
	/*self iPrintln(self.MenuPanelx);
	wait Time;
	self iPrintln(self.MenuSwordx);
	wait Time;
	self iPrintln(self.MenuLinex);
	wait Time;
	self iPrintln(self.MenuLineIIx);
	wait Time;
	self iPrintln(self.MenuLineIIIx);
	wait Time;
	self iPrintln(self.RootTextBGx);
	wait Time;
	self iPrintln(self.MenuUpIconx);
	wait Time;
	self iPrintln(self.MenuUpIconIIx);
	wait Time;
	self iPrintln("^2ControllBG");
	wait Time;
	self iPrintln(self.ControllBGx);
	wait Time;
	self iPrintln(self.ControllBGy);
	wait Time;
	/*self iPrintln(self.MenuScrollbarx);
	wait Time;
	self iPrintln(self.MenuLogox);
	wait Time;
	self iPrintln(self.MenuCreatorx);
	wait Time;
	self iPrintln("^2MenuControllText");
	wait Time;
	self iPrintln(self.MenuControllTextx);
	wait Time;
	self iPrintln(self.MenuControllTexty);
	wait Time;
	/*self iPrintln(self.TitleTextx);
	wait Time;
	self iPrintln(self.MenuTextx);
	wait Time;*/
	self iPrintln("^2----------");
	wait Time;
	self iPrintln("^5BGx_TutBoarder");
	self iPrintln(self.BGx_TutBoarder);
	wait Time;
	self iPrintln("^5BGy_TutBoarder");
	self iPrintln(self.BGy_TutBoarder);
	wait Time;
	self iPrintln("^5Txtx_TutBoarder");
	self iPrintln(self.Txtx_TutBoarder);
	wait Time;
	self iPrintln("^5Txty_TutBoarder");
	self iPrintln(self.Txty_TutBoarder);
}


















