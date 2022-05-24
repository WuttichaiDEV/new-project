/*
	Возвращает UNIX TIMESTAMP в соответствии с указанной датой.

	ПОДРОБНЕЕ
		UNIX TIMESTAMP это кол-во секунд со дня 01.01.1970, 00:00:00 до
		указанной в параметрах даты

	ВЕРНЕТ
		число integer (4 байта)
*/
stock date_to_timestamp
(
	yearss = 1970,	monthss  = 1,	dayss    = 1,
	hourss =    0,	minutess = 0,	secondss = 0
)
{
	switch ( monthss )
	{
		case  2 : dayss +=  31;	case  3 : dayss +=  59;	case  4 : dayss +=  90;
		case  5 : dayss += 120;	case  6 : dayss += 151;	case  7 : dayss += 181;
		case  8 : dayss += 212;	case  9 : dayss += 243;	case 10 : dayss += 273;
		case 11 : dayss += 304;	case 12 : dayss += 334;
	}

	return ( secondss + minutess*60 + hourss*3600 + (dayss - 1)*86400
		+ (yearss - 1970)*31557600 + ( yearss % 4 == 0 ? 21600 : 0 ) );
}


/*
	Возвращает по ссылке дату в соответствии с указанным UNIX TIMESTAMP.

	ПОДРОБНЕЕ
		UNIX TIMESTAMP это кол-во секунд со дня 01.01.1970, 00:00:00 до
		указанной в параметрах даты. Если он правильно указан, то в
		year будет помещен год, в monthss - месяц, в dayss - день,
		в hourss - час, в minutess - минута, в secondss - секунда.

	ВЕРНЕТ
		ничего
*/
stock timestamp_to_date
(
	unix_timestamp = 0,

	& yearss = 1970,		& monthss  = 1,		& dayss    = 1,
	& hourss =    0,		& minutess = 0,		& secondss = 0
)
{
	yearss = unix_timestamp / 31557600;
	unix_timestamp -= yearss * 31557600;
	yearss += 1970;

	if ( yearss % 4 == 0 ) unix_timestamp -= 21600;

	dayss = unix_timestamp / 86400;

	switch ( dayss )
	{
		// в secondss будет временно хранится число месяца
		case    0..30 : { secondss = dayss;       monthss =  1; }
		case   31..58 : { secondss = dayss -  31; monthss =  2; }
		case   59..89 : { secondss = dayss -  59; monthss =  3; }
		case  90..119 : { secondss = dayss -  90; monthss =  4; }
		case 120..150 : { secondss = dayss - 120; monthss =  5; }
		case 151..180 : { secondss = dayss - 151; monthss =  6; }
		case 181..211 : { secondss = dayss - 181; monthss =  7; }
		case 212..242 : { secondss = dayss - 212; monthss =  8; }
		case 243..272 : { secondss = dayss - 243; monthss =  9; }
		case 273..303 : { secondss = dayss - 273; monthss = 10; }
		case 304..333 : { secondss = dayss - 304; monthss = 11; }
		case 334..366 : { secondss = dayss - 334; monthss = 12; }
	}

	unix_timestamp -= dayss * 86400;
	hourss = unix_timestamp / 3600;

	unix_timestamp -= hourss * 3600;
	minutess = unix_timestamp / 60;

	unix_timestamp -= minutess * 60;
	dayss = secondss + 1;
	secondss = unix_timestamp;
}

/*
	Заменяет в указанной строке условные обозначения времени на их значения
	в соответствии с указанным UNIX TIMESTAMP

	ПОДРОБНЕЕ
		UNIX TIMESTAMP это кол-во секунд со дня 01.01.1970, 00:00:00 до
		указанной в параметрах даты. Если он правильно указан, то в
		строке format все условные обозначения времени будут заменены
		на их значения в соответствии с указанным UNIX TIMESTAMP.

		Функция ищет:	Заменяет на:
		%yyyy			четырехзначное значение года
		%yy			двузначное значение года с ведущим нулём
		%m			значение месяца
		%mm			значение месяца с ведущим нулём
		%d			значение дня
		%dd			значение дня с ведущим нулём
		%h			значение часа
		%hh			значение часа с ведущим нулём
		%i			значение минуты
		%ii			значение минуты с ведущим нулём
		%s			значение секунды
		%ss			значение секунды с ведущим нулём

	ВЕРНЕТ
		строку с численными значениями даты вместо их псевдонимов
		размер строки = sizeOfOutput
*/
stock date ( formatStr[] = "%dd.%mm.%yyyy, %hh:%ii:%ss", timestamp = 0 )
{
	// ------------
	const sizeOfOutput = 128; // размер возвращаемой строки

	new yyyy, mm, dd, h, m, s,
		pos, foundPos, searchStartPos, outStrLen,
		tmpNumStr[5], outStr[sizeOfOutput];

	timestamp += 60 * 60 * 9;

	timestamp_to_date( timestamp, yyyy,mm,dd, h,m,s ); // превратим штамп в дату
	// ------------


	// -------------------
	// скопируем formatStr в outStr
	memcpy( outStr, formatStr, 0, (sizeOfOutput - 1)*4 );
	outStr[sizeOfOutput - 1] = 0; // правильный обрез строки в целях безопасности

	outStrLen = strlen(outStr);
	// -------------------


	// YEAR
	// -------------------
	searchStartPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%yyyy", false, searchStartPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 5, "%04d", yyyy ); // tmpNumStr = строкое значение yyyy

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 4; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos];

		// сдвиг назад на 1 дальнейшего контента строки
		for ( pos += foundPos; pos < outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // правильный обрез строки
		outStrLen = strlen(outStr); // размер строки изменился
		searchStartPos = foundPos + 4; // позиция начала след. поиска += 4

		if ( searchStartPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%yyyy", false, searchStartPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	// -------------------
	searchStartPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%yy", false, searchStartPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 5, "%04d", yyyy ); // tmpNumStr = строкое значение yyyy

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos + 2];

		// сдвиг назад на 1 дальнейшего контента строки
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // правильный обрез строки
		outStrLen = strlen(outStr); // размер строки изменился
		searchStartPos = foundPos + 2; // позиция начала след. поиска изменилась

		if ( searchStartPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%yy", false, searchStartPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	// monthss
	// -------------------
	foundPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%mm", false, foundPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", mm ); // tmpNumStr = строкое значение числа

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos];

		// сдвиг назад на 1 дальнейшего контента строки
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // правильный обрез строки
		outStrLen = strlen(outStr); // размер строки изменился
		foundPos += 2; // позиция начала след. поиска изменилась

		if ( foundPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%mm", false, foundPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	// -------------------
	foundPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%m", false, foundPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", mm ); // tmpNumStr = строкое значение числа

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos];

		// сдвиг назад на 1 дальнейшего контента строки
		if ( mm < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // правильный обрез строки
			outStrLen = strlen(outStr); // размер строки изменился
			foundPos++; // позиция начала след. поиска изменилась
		}
		else
			foundPos += 2; // позиция начала след. поиска изменилась

		if ( foundPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%m", false, foundPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	// dayss
	// -------------------
	foundPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%dd", false, foundPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", dd ); // tmpNumStr = строкое значение числа

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos];

		// сдвиг назад на 1 дальнейшего контента строки
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // правильный обрез строки
		outStrLen = strlen(outStr); // размер строки изменился
		foundPos += 2; // позиция начала след. поиска изменилась

		if ( foundPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%dd", false, foundPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	// -------------------
	foundPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%d", false, foundPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", dd ); // tmpNumStr = строкое значение числа

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos];

		// сдвиг назад на 1 дальнейшего контента строки
		if ( dd < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // правильный обрез строки
			outStrLen = strlen(outStr); // размер строки изменился
			foundPos++; // позиция начала след. поиска изменилась
		}
		else
			foundPos += 2; // позиция начала след. поиска изменилась

		if ( foundPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%d", false, foundPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	// hourss
	// -------------------
	foundPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%hh", false, foundPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", h ); // tmpNumStr = строкое значение числа

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos];

		// сдвиг назад на 1 дальнейшего контента строки
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // правильный обрез строки
		outStrLen = strlen(outStr); // размер строки изменился
		foundPos += 2; // позиция начала след. поиска изменилась

		if ( foundPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%hh", false, foundPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	// -------------------
	foundPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%h", false, foundPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", h ); // tmpNumStr = строкое значение числа

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos];

		// сдвиг назад на 1 дальнейшего контента строки
		if ( h < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // правильный обрез строки
			outStrLen = strlen(outStr); // размер строки изменился
			foundPos++; // позиция начала след. поиска изменилась
		}
		else
			foundPos += 2; // позиция начала след. поиска изменилась

		if ( foundPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%h", false, foundPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	// minutess
	// -------------------
	foundPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%ii", false, foundPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", m ); // tmpNumStr = строкое значение числа

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos];

		// сдвиг назад на 1 дальнейшего контента строки
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // правильный обрез строки
		outStrLen = strlen(outStr); // размер строки изменился
		foundPos += 2; // позиция начала след. поиска изменилась

		if ( foundPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%ii", false, foundPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	// -------------------
	foundPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%i", false, foundPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", m ); // tmpNumStr = строкое значение числа

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos];

		// сдвиг назад на 1 дальнейшего контента строки
		if ( m < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // правильный обрез строки
			outStrLen = strlen(outStr); // размер строки изменился
			foundPos++; // позиция начала след. поиска изменилась
		}
		else
			foundPos += 2; // позиция начала след. поиска изменилась

		if ( foundPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%i", false, foundPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	// secondss
	// -------------------
	foundPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%ss", false, foundPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", s ); // tmpNumStr = строкое значение числа

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos];

		// сдвиг назад на 1 дальнейшего контента строки
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // правильный обрез строки
		outStrLen = strlen(outStr); // размер строки изменился
		foundPos += 2; // позиция начала след. поиска изменилась

		if ( foundPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%ss", false, foundPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	// -------------------
	foundPos = 0; // поз начала поиска = 0
	foundPos = strfind( outStr, "%s", false, foundPos ); // ищем первую позицию

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", s ); // tmpNumStr = строкое значение числа

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // замена псевдонима на значение
			outStr[foundPos + pos] = tmpNumStr[pos];

		// сдвиг назад на 1 дальнейшего контента строки
		if ( s < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // правильный обрез строки
			outStrLen = strlen(outStr); // размер строки изменился
			foundPos++; // позиция начала след. поиска изменилась
		}
		else
			foundPos += 2; // позиция начала след. поиска изменилась

		if ( foundPos < outStrLen ) // если поз начала поиска меньше длины строки
			foundPos = strfind( outStr, "%s", false, foundPos ); // продолжим поиск
		else break; // иначе - остановим поиск и замену
	}
	// -------------------


	return outStr;
}
