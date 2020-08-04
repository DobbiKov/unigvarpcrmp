ALT:w:whisper;
CMD:w(playerid,params[])
{
    if(sscanf(params,"s[100]",params[0])) return SCM(playerid, white, "{"cblue"}• [Подсказка]{"cwhite"}: /w(hisper) [сообщение]");
    if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, green, !"В данный момент у вас мут. Время до сняти мута: /time");
    stringer[0] = EOS;
	format(stringer, 144, "%s[%d] шепчет: %s", PlayerInfo[playerid][pName],playerid, params[0]);
 	ProxDetector(30.0, playerid, stringer, 0x6E6E6E6E, 0x6E6E6E6E, 0x6E6E6E6E, 0x6E6E6E6E, 0x6E6E6E6E);
	return 1;
}