stock GetPlayerID(const pname[])
{
	if(isnull(pname)) return -1;

	foreach(new i : logged_players) 
	{
		if(!strcmp(p_info[i][name], pname, false)) return i;
	}
	return -1;
}