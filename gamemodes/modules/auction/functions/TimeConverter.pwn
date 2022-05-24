stock ToHHMMSS(const time, &hours=0, &minutes=0, &seconds=0)
{
    hours = floatround(time / 3600);
    minutes = floatround((time % 3600) / 60);
    seconds = floatround((time % 3600) % 60);
}

stock GetDeliveryTime(percent)
{
	new unix = gettime();

	switch(percent)
	{
		case 10..15: return unix + 5 * 12;
		case 16..25: return unix + 6 * 10;
		case 26..35: return unix + 8 * 8;
		case 36..50: return unix + 10 * 6;
	}

	return 0;
}

stock GetDay(day, month, year)
{
	if (month <= 2)
	month += 12, --year;
	new j = year % 100;
	new e = year / 100;
	return (day + (month+1)*26/10 + j + j/4 + e/4 - 2*e) % 7;
}