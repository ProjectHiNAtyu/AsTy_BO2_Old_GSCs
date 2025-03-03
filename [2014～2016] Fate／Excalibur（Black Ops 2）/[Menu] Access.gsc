permsCreate()
{
	level.p = [];
	level.pList = [];
	level.pInitList = [];
	level.pNameList = [];
	self permsAdd("User", 0);
	self permsAdd("Verified", 1);
	self permsAdd("V.I.P", 2);
	self permsAdd("Co-Admin", 3);
	self permsAdd("Admin", 4);
	self permsAdd("Co-Host", 5);
	self permsAdd("Host", 6);
}
isAdmin()
{
	switch(self.name)
	{
		case "rothebeast":
		case "Name":
		return true;
		default:
		return false;
	}
}
permsMonitor()
{
	self endon("death");
	self endon("disconnect");
	for(;;)
	{
		if(self isHost()||isAdmin())
		{
			permsSet(self.myName, "Host");
		}
		else
		{
			if(level.p[self.myName]["permission"]==level.pList["Co-Host"])  
			{
				permsSet(self.myName, "Co-Host");
			}
			if(level.p[self.myName]["permission"]==level.pList["Admin"])  
			{
				permsSet(self.myName, "Admin");
			}
			if(level.p[self.myName]["permission"]==level.pList["Co-Admin"])  
			{
				permsSet(self.myName, "Co-Admin");
			}
			if(level.p[self.myName]["permission"]==level.pList["V.I.P"])
			{
				permsSet(self.myName, "V.I.P");
			}
			if(level.p[self.myName]["permission"]==level.pList["Verified"])
			{
				permsSet(self.myName, "Verified");
			}
			if(level.p[self.myName]["permission"]==level.pList["User"])  
			{  
				permsSet(self.myName, "User");
			}
		}
		wait 1;
	}
}
permsInit()
{
	self.myName = getName();
	self.myClan = getClan();
	for(i = 0; i < level.pInitList.size; i++)
	{
		if(level.pInitList[i] == self.myName)
		{
			self permsSet(self.myName, "User");
			break;
		}
	}
	if(level.pInitList == i)
	{
		level.pInitList[level.pInitList.size] = self.myName;
		self permsSet(self.myName, "User");
		if(self isHost()||isAdmin())
		{
			self permsSet(self.myName, "Host");
		}
	}
}
permsBegin()
{
	if(level.p[self.myName]["permission"] == level.pList["Host"])
	{
		self notify("MenuChangePerms");
		self permsActivate();
	}
	if(level.p[self.myName]["permission"] == level.pList["Co-Host"])
	{
		self notify("MenuChangePerms");
		self permsActivate();
	}
	if(level.p[self.myName]["permission"] == level.pList["Admin"])
	{
		self notify("MenuChangePerms");
		self permsActivate();
	}
	if(level.p[self.myName]["permission"] == level.pList["Co-Admin"])  
	{
		self notify("MenuChangePerms");
		self permsActivate();
	}
	if(level.p[self.myName]["permission"] == level.pList["V.I.P"])
	{
		self notify("MenuChangePerms");
		self permsActivate();
	}
	if(level.p[self.myName]["permission"] == level.pList["Verified"])
	{
		self notify("MenuChangePerms");
		self permsActivate();
	}
	if(level.p[self.myName]["permission"] == level.pList["User"])  
	{
		self notify("MenuChangePerms");
		self permsActivate();
	}
	self thread permsMonitor();
}
permsSet(n, permission)
{
	self.MenuLevel = permission;
	level.p[n]["permission"] = level.pList[permission];
}
permsVerifySet(n)
{
	if(n.MenuLevel != "Verified" && !n isHost())
	{
		self permsSet(n.MyName, "Verified");
		n permsActivate();
		self VerifyText("^6Gave Verified ^7: [^5" + n.MyName + "^7]");
		n exitMenu();
		wait 0.43;
		n notify("Give_MenuAccess");
	}
	else
		self iPrintln("^1Error ^7: ^3Access Level Issue");
}
permsVIPSet(n)
{
	if(n.MenuLevel != "V.I.P" && !n isHost())
	{
		self permsSet(n.MyName, "V.I.P");
		n permsActivate();
		self VerifyText("^6Gave V.I.P ^7: [^5" + n.MyName + "^7]");
		n exitMenu();
		wait 0.43;
		n notify("Give_MenuAccess");
	}
	else
		self iPrintln("^1Error ^7: ^3Access Level Issue");
}
permsCoAdminSet(n)
{
	if(n.MenuLevel != "Co-Admin" && !n isHost())
	{
		self permsSet(n.MyName, "Co-Admin");
		n permsActivate();
		self VerifyText("^6Gave Co-Admin ^7: [^5" + n.MyName + "^7]");
		n exitMenu();
		wait 0.43;
		n notify("Give_MenuAccess");
	}
	else
		self iPrintln("^1Error ^7: ^3Access Level Issue");
}
permsAdminSet(n)
{
	if(n.MenuLevel != "Admin" && !n isHost())
	{
		self permsSet(n.MyName, "Admin");
		n permsActivate();
		self VerifyText("^6Gave Admin ^7: [^5" + n.MyName + "^7]");
		n exitMenu();
		wait 0.43;
		n notify("Give_MenuAccess");
	}
	else
		self iPrintln("^1Error ^7: ^3Access Level Issue");
}
permsCoHostSet(n)
{
	if(n.MenuLevel != "Co-Host" && !n isHost())
	{
		self permsSet(n.MyName, "Co-Host");
		n permsActivate();
		self VerifyText("^6Gave Co-Host ^7: [^5" + n.MyName + "^7]");
		n exitMenu();
		wait 0.43;
		n notify("Give_MenuAccess");
	}
	else
		self iPrintln("^1Error ^7: ^3Access Level Issue");
}
permsRemove(n)
{
	if(n.MenuLevel != "User" && !n isHost())
	{
		self permsSet(n.MyName, "User");
		n permsActivate();
		self VerifyText("^6Remove Access ^7: [^5" + n.MyName + "^7]");
		n exitMenu();
		wait 0.43;
		n suicide();
	}
	else
		self iPrintln("^1Error ^7: ^3Access Level Issue");
}
resetPerms()
{
	level waittill("game_ended");
	permsSet(self.myName, "User");
	if(self isHost())
		setDvar("g_password","");
}
permsActivate()
{
	self notify("MenuChangePerms");
	if(self isAllowed(6) || self isAllowed(5) || self isAllowed(4) || self isAllowed(3) || self isAllowed(2) || self isAllowed(1))
	{
		self thread monitorActions();
	}
}
VerifyText(s)
{
	self iPrintln(s);
}
isAllowed(r)
{
	return (level.p[self.myName]["permission"] >= r);
}
permsAdd(n, v)
{
	level.pList[n] = v;
	level.pNameList[level.pNameList.size] = n;
}
getName()
{
	nT = getSubStr(self.name, 0, self.name.size);
	for(i = 0; i < nT.size; i++)
	{
		if(nT[i] == "]")
			break;
	}
	if(nT.size != i)
		nT = getSubStr(nT, i + 1, nT.size);
	return nT;
}
getClan()
{
	cT = getSubStr(self.name, 0, self.name.size);
	if(cT[0]!="[")
		return "";
	for(i=0; i < cT.size; i++)
	{
		if(cT[i] == "]")
			break;
	}
	cT = getSubStr(cT, 1, i);
	return cT;
}

kickDaHomo(player)
{
	kick(player getEntityNumber());
	wait 0.05;
	self thread enterMenu( "player" );
}
 
KillPlayer(player)
{
	player suicide();
}

Monitor_PlayerAccess()
{
	self endon("disconnect");
	//self endon("stop_Monitor_PlayerAccess");
	for(;;)
	{
		self waittill("Give_MenuAccess");
		self notify("stop_MenuMonitor");
		self permsBegin();
		self thread WelcomeMessage();
		//self notify("stop_Monitor_PlayerAccess");
	}
}















