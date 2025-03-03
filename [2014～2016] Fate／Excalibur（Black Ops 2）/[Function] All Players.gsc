
//-----< 呼び出し >-----

AntiQuit()
{
	self thread init_AntiQuit(0, 1);
}
AllPlayers_AntiQuit()
{
	self thread init_AntiQuit(1, 1);
}

//-----< 本体 >-----

init_AntiQuit(Target, Notice)
{
	if(self.isAntiQuit == 0)
	{
		if(Target == 0)
			self thread do_AntiQuit();
		else
		{
			foreach(player in level.players)
				player thread do_AntiQuit();
		}
		if(Notice == 1)
		{
			self iPrintln("^6Anti Quit ^7: [^2On^7]");
			if(level.NoticeMode == 0)
				self thread init_NotifySetText(0, 2, "^6Anti Quit ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
			else
				self thread init_NotifySetText(1, 2, "^6Anti Quit ^7is ^2Enabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isAntiQuit = 1;
	}
	else
	{
		if(Target == 0)
			self notify("stop_AntiQuit");
		else
		{
			foreach(player in level.players)
				player notify("stop_AntiQuit");
		}
		if(Notice == 1)
		{
			self iPrintln("^6Anti Quit ^7: [^2Off^7]");
			if(self.NoticeTextMode == 1)
				self thread init_NotifySetText(0, 2, "^6Anti Quit ^7is ^1Disabled.", (1, 1, 1), 1, (0, 0, 1), 2, 0);
		}
		self.isAntiQuit = 0;
	}
}
do_AntiQuit()
{
	self endon("disconnect");
	self endon("stop_AntiQuit");
	for(;;)
	{
		self maps/mp/gametypes/_globallogic_ui::closemenus();
		wait 0.05;
	}
}















