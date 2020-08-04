CMD:tickets(playerid)
{
    new sql[144];
    format(sql, sizeof(sql), "SELECT * FROM `fines` WHERE `account_id` = '%d' ORDER BY `fine_id` ASC limit 10", PlayerInfo[playerid][pID]);
    mysql_tquery(connects, sql, "ShowFines", "i", playerid);
}

publics ShowFines(playerid)
{
	new rows[2], fine_id, date_fine[30], fine, reason[40];
	cache_get_data(rows[0], rows[1]);
	if(rows[0])
	{
        SCM(playerid, red, "________________________________________________________");
        SCM(playerid, red, "");
        for(new i = 0; i < rows[0]; i++)
		{
            fine_id = cache_get_field_content_int(i, "fine_id");
            fine = cache_get_field_content_int(i, "fine");
            cache_get_field_content(i, "date", date_fine, sizeof date_fine);
			cache_get_field_content(i, "reason", reason, sizeof reason);
			
			static const fmt_msg[] = "Штраф №%d. %d рублей. Дата %s. Причина: %s";
			new string[sizeof(fmt_msg)+100];
			format(string, sizeof(string), fmt_msg, fine_id, fine, date_fine, reason);
			SCM(playerid, red, string);
		}
		SCM(playerid, red, "________________________________________________________");
		SCM(playerid, red, "");
		SCM(playerid, red, "Показаны 10 последних штрафов");
	}
	else SCM(playerid, red, "У вас нет неоплаченных штрафов");
	return 1;
}