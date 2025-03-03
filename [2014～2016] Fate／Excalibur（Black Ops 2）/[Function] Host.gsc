ForceHost()
{
	if(level.isForceHost == 0)
	{
		setdvar("party_connectToOthers", "0");
		setdvar("partyMigrate_disabled", "1");
		setdvar("party_mergingEnabled", "0");
		self iPrintln("^6Force Host ^7: [^2On^7]");
		level.isForceHost = 1;
	}
	else
	{
		setdvar("party_connectToOthers", "1");
		setdvar("partyMigrate_disabled", "0");
		setdvar("party_mergingEnabled", "1");
		self iPrintln("^6Force Host ^7: [^1Off^7]");
		level.isForceHost = 0;
	}
}

















