#include maps/mp/_utility;
#include common_scripts/utility;
#include maps/mp/_scoreevents;
#include maps/mp/gametypes/_globallogic;
#include maps/mp/gametypes/_hud;
#include maps/mp/gametypes/_hud_util;
#include maps/mp/gametypes/_hud_message;
#include maps/mp/gametypes/_weapons;
#include maps/mp/teams/_teams;
#include maps/mp/gametypes/_spawnlogic;
#include maps/mp/killstreaks/_ai_tank;
//#insert raw/maps/mp/_scoreevents.gsh;
//#include maps/mp/gametypes/_rank;


init()
{
	level.scoreinfo = [];
	level.xpscale = getDvarFloat("scr_xpscale");
	level.codpointsxpscale = getDvarFloat("scr_codpointsxpscale");
	level.codpointsmatchscale = getDvarFloat("scr_codpointsmatchscale");
	level.codpointschallengescale = getDvarFloat("scr_codpointsperchallenge");
	level.rankxpcap = getDvarInt("scr_rankXpCap");
	level.codpointscap = getDvarInt("scr_codPointsCap");
	level.usingmomentum = 1;
	level.usingscorestreaks = getDvarInt("scr_scorestreaks") != 0;
	level.scorestreaksmaxstacking = getDvarInt("scr_scorestreaks_maxstacking");
	level.maxinventoryscorestreaks = getdvarintdefault("scr_maxinventory_scorestreaks", 3);
	if(isDefined(level.usingscorestreaks))
	{
		level.usingrampage = !level.usingscorestreaks;
	}
	level.rampagebonusscale = getDvarFloat("scr_rampagebonusscale");
	level.ranktable = [];
	precacheshader("white");
	/*precachestring(&"RANK_PLAYER_WAS_PROMOTED_N");
	precachestring(&"RANK_PLAYER_WAS_PROMOTED");
	precachestring(&"RANK_PROMOTED");
	precachestring(&"MP_PLUS");
	precachestring(&"RANK_ROMANI");
	precachestring(&"RANK_ROMANII");
	precachestring(&"MP_SCORE_KILL");*/
	if(!sessionmodeiszombiesgame())
	{
		initscoreinfo();
	}
	level.maxrank = int(tablelookup("mp/rankTable.csv", 0, "maxrank", 1));
	level.maxprestige = int(tablelookup("mp/rankIconTable.csv", 0, "maxprestige", 1));
	pid = 0;
	rid = 0;
	pid = 0;
	while(pid <= level.maxprestige)
	{
		rid = 0;
		while(rid <= level.maxrank)
		{
			precacheshader(tablelookup("mp/rankIconTable.csv", 0, rid, pid + 1));
			rid++;
		}
		pid++;
	}
	rankid = 0;
	rankname = tablelookup("mp/ranktable.csv", 0, rankid, 1);
       
	while(isDefined(rankname) && rankname != "")
	{
		level.ranktable[ rankid ][ 1 ] = tablelookup("mp/ranktable.csv", 0, rankid, 1);
		level.ranktable[ rankid ][ 2 ] = tablelookup("mp/ranktable.csv", 0, rankid, 2);
		level.ranktable[ rankid ][ 3 ] = tablelookup("mp/ranktable.csv", 0, rankid, 3);
		level.ranktable[ rankid ][ 7 ] = tablelookup("mp/ranktable.csv", 0, rankid, 7);
		level.ranktable[ rankid ][ 14 ] = tablelookup("mp/ranktable.csv", 0, rankid, 14);
		//precachestring(tablelookupistring("mp/ranktable.csv", 0, rankid, 16));
		rankid++;
		rankname = tablelookup("mp/ranktable.csv", 0, rankid, 1);
	}

	level.AllNoticeTextMode = 0; //オールプレイヤー通知モード
	level.NoticeMode = 0; //Self通知モード
	level.clientid = 0; //プレイヤー接続フリーズ回避
	//Menu上部アイコン
	precacheshader("faction_seals");
	precacheshader("faction_pmc");
	 //MW2 Nuke
	precacheshader("mp_hud_cluster_status");
	precacheshader("emblem_bg_bo2_nuclear_killer");
    precacheShader("line_horizontal"); //デザインの柔軟透過表現素材
    //スモークエフェクトの使用
    level.fx_smokegrenade_single = "smoke_center_mp";
	precacheitem(level.fx_smokegrenade_single);
    //オブジェクト記憶
	precacheModel("veh_t6_drone_pegasus_mp"); //Suicide LodeStar
	precacheModel("defaultactor"); //Change Model
	precacheModel("german_shepherd"); //Change Model
	//ESP Wall Hack
	precacheShader("hud_remote_missile_target");
	precacheShader("headicon_dead");
	level.deads = "headicon_dead";
	level.esps = "hud_remote_missile_target";

	level thread onPlayerConnect();
	if(!isDefined(level.pList)) 
	{
		level permsCreate();
	}
}
 
onPlayerConnect()
{
	for(;;)
	{
		level waittill("connected", player);
		
		player.pers["rankxp"] = player getrankxpstat();
		player.pers["codpoints"] = player getcodpointsstat();
		player.pers["currencyspent"] = player getdstat("playerstatslist", "currencyspent", "StatValue");
		rankid = player getrankforxp(player getrankxp());
		player.pers["rank"] = rankid;
		player.pers["plevel"] = player getdstat("playerstatslist", "PLEVEL", "StatValue");
		if(player shouldkickbyrank())
		{
			kick(player getentitynumber());
			continue;
		}
		else
		{
			if(!isDefined(player.pers["participation"]) || level.gametype == "twar" && game["roundsplayed"] >= 0 && player.pers["participation"] >= 0)
			{
				player.pers["participation"] = 0;
			}
			player.rankupdatetotal = 0;
			player.cur_ranknum = rankid;
 
			prestige = player getdstat("playerstatslist", "plevel", "StatValue");
			player setrank(rankid, prestige);
			player.pers["prestige"] = prestige;
			if(!isDefined(player.pers["summary"]))
			{
				player.pers["summary"] = [];
				player.pers["summary"]["xp"] = 0;
				player.pers["summary"]["score"] = 0;
				player.pers["summary"]["challenge"] = 0;
				player.pers["summary"]["match"] = 0;
				player.pers["summary"]["misc"] = 0;
				player.pers["summary"]["codpoints"] = 0;
			}
			if(!level.rankedmatch || level.wagermatch && level.leaguematch)
			{
				player setdstat("AfterActionReportStats", "lobbyPopup", "none");
			}
			if(level.rankedmatch)
			{
				player setdstat("playerstatslist", "rank", "StatValue", rankid);
				player setdstat("playerstatslist", "minxp", "StatValue", getrankinfominxp(rankid));
				player setdstat("playerstatslist", "maxxp", "StatValue", getrankinfomaxxp(rankid));
				player setdstat("playerstatslist", "lastxp", "StatValue", getrankxpcapped(player.pers["rankxp"]));
			}
			player.explosivekills[0] = 0;
			player thread onPlayerSpawned();
			player thread onjoinedteam();
			player thread onjoinedspectators();
		}
		
		player.clientid = level.clientid; //プレイヤー接続フリーズ回避
		level.clientid++; //プレイヤー接続フリーズ回避
		if(player isHost())
		{
			level.hostyis = player;
		}
	}
}
 
onPlayerSpawned()
{
	self endon("disconnect");
	self permsInit();
	self thread init_SetDesignPosition(0, 0, -140, 140, 0, 0, -90, 90, -245, -70, -200, 0, 0, -370, -100, 0, 0, -220, 100, -389, 58);
	self thread NoNotice_StealthBinds(); //黙ってESP Wall Hack
	self thread Wait_Suicide_Return();
	self thread MethodDesigns();
	self thread OverflowFix(); //Overflow Fix
	self thread Monitor_PlayerAccess();
	self.NoticeTextMode = 0; //Self Notice Mode
	self.isEffectBullets = 0; //Effect Bullets
	self.isSelect_ModdedBullets = 0; //Modded Bullets
	//self.isClientFOV = 0; //Client FOV
	self.Scale_ClientFOV = 65; //Client FOV Scale
	self.isClientSpeed = 1; //Client Speed
	self.isCtrlTut = 0; //Menu開口時の左側説明文の使用状況
	//Mod Menuの初期エフェクトモード指定。
	self.isMenuEffectType = 1;
	self.isMenuTitleEffect = 1;
	self.isCreatorTextEffect = 1;
	self.isOptionTextEffect = 1;
	self.isBackGroundEffect = 1;
	self.isHomefrontSpawn = 0; //Homefront Spawn
	self.isWelcomeMessage = 1; //Welcome Message
	self.isUnfairAimbot = 0; //Unfair Aimbot
	self.isTutorialBoarder = 0;
	self.MenuOpen = false;
	for(;;)
	{
		self waittill("spawned_player");
		
		if(!isDefined(self.hud_rankscroreupdate))
		{
			self.hud_rankscroreupdate = newscorehudelem(self);
			self.hud_rankscroreupdate.horzalign = "center";
			self.hud_rankscroreupdate.vertalign = "middle";
			self.hud_rankscroreupdate.alignx = "center";
			self.hud_rankscroreupdate.aligny = "middle";
			self.hud_rankscroreupdate.x = 0;
			if(self issplitscreen())
			{
				self.hud_rankscroreupdate.y = -15;
			}
			else
			{
				self.hud_rankscroreupdate.y = -60;
			}
			self.hud_rankscroreupdate.font = "default";
			self.hud_rankscroreupdate.fontscale = 2;
			self.hud_rankscroreupdate.archived = 0;
			self.hud_rankscroreupdate.color =(1, 1, 0.5);
			self.hud_rankscroreupdate.alpha = 0;
			self.hud_rankscroreupdate.sort = 50;
			self.hud_rankscroreupdate maps/mp/gametypes/_hud::fontpulseinit();
		}
		
		if(self ishost() || self isAllowed(4) || self isAllowed(3) || self isAllowed(2) || self isAllowed(1))
		{
			if(self.isWelcomeMessage == 1)
				self thread WelcomeMessage();
			self thread HomefrontSpawn();
		}
		self permsBegin();
	}
}















