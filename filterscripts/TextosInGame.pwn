/****************** [FS] Creador de Textos In-Game by HERMES ******************/

#include <a_samp>

// Defines

#define ARCHIVO_LABEL 				"Textos/%d.ini" // Nombre del Archivo
#define MAX_LABELS 					1000 	// Cambiar a gusto (Límite: 1024)
#define DIALOG_CREARLABEL_TXT       30000
#define DIALOG_CREARLABEL_POS       30001
#define DIALOG_CREARLABEL_POS_2     30002
#define DIALOG_CREARLABEL_CLR       30003
#define DIALOG_CREARLABEL_CLR_2     30004
#define DIALOG_CREARLABEL_CLR_3     30005
#define DIALOG_CREARLABEL_RNG       30006
#define DIALOG_CREARLABEL_VWD       30007
#define DIALOG_CREARLABEL_VWD_2     30008
#define DIALOG_CREARLABEL_LOS       30009
#define DIALOG_EDITARLABEL 			30010
#define DIALOG_EDITARLABEL_TXT 		30011
#define DIALOG_EDITARLABEL_POS      30012
#define DIALOG_EDITARLABEL_POS_2    30013
#define DIALOG_EDITARLABEL_CLR 		30014
#define DIALOG_EDITARLABEL_CLR_2	30015
#define DIALOG_EDITARLABEL_CLR_3	30016
#define DIALOG_EDITARLABEL_RNG      30017
#define DIALOG_EDITARLABEL_VWD      30018
#define DIALOG_EDITARLABEL_VWD_2    30019
#define DIALOG_EDITARLABEL_LOS      30020

#define SOLO_RCON // Borrar si quieres que los usuarios normales puedan crear textos.

// Colores
#define Amarillo	0xFFFF00AA
#define Rojo		0xFF0000AA

// Variables
enum LabelInfo
{
	bool:LabelCreado,   // Variable
	LabelTexto[128],    // Texto
	LabelColor,			// Color del Texto
	Float:LabelX,		// Coordenada X
	Float:LabelY,		// Coordenada Y
	Float:LabelZ,		// Coordenada Z
	Float:LabelRange,	// Distancia desde la cual es visible
	LabelVW,			// VirtualWorld
	LabelLOS,           // 0 = No atraviesa objetos | 1 = Atraviesa objetos
	Text3D:Label		// 3DTextLabel
}

new TextLabel[MAX_LABELS][LabelInfo];
new CreandoLabel[MAX_PLAYERS];
new EditandoLabel[MAX_PLAYERS];

public OnFilterScriptInit()
{
    print("  -------------------------------------------------");
	print("  | Creador de Textos In-Game by HERMES | Cargado |");
	print("  -------------------------------------------------");
	for(new l = 0; l < MAX_LABELS; l++)
	{
	    TextLabel[l][LabelCreado] = false;
		TextLabel[l][LabelColor] = -255;
		TextLabel[l][LabelX] = 0.0;
		TextLabel[l][LabelY] = 0.0;
		TextLabel[l][LabelZ] = 0.0;
		TextLabel[l][LabelRange] = 0.0;
		TextLabel[l][LabelVW] = -255;
		TextLabel[l][LabelLOS] = -255;
		strdel(TextLabel[l][LabelTexto], 0, strlen(TextLabel[l][LabelTexto]));
	}
	CargarLabels();
	return 1;
}

public OnFilterScriptExit()
{
	for(new l = 0; l < MAX_LABELS; l++)
	{
	    TextLabel[l][LabelCreado] = false;
		TextLabel[l][LabelColor] = -255;
		TextLabel[l][LabelX] = 0.0;
		TextLabel[l][LabelY] = 0.0;
		TextLabel[l][LabelZ] = 0.0;
		TextLabel[l][LabelRange] = 0.0;
		TextLabel[l][LabelVW] = -255;
		TextLabel[l][LabelLOS] = -255;
		strdel(TextLabel[l][LabelTexto], 0, strlen(TextLabel[l][LabelTexto]));
		Delete3DTextLabel(TextLabel[l][Label]);
	}
    return 1;
}

public OnPlayerConnect(playerid)
{
    CreandoLabel[playerid] = -1;
	EditandoLabel[playerid] = -1;
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(CreandoLabel[playerid] >= 0)
	{
	    BorrarLabel(CreandoLabel[playerid]);
	}
	CreandoLabel[playerid] = -1;
	EditandoLabel[playerid] = -1;
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128], idx;
    cmd = strtok(cmdtext, idx);

	if(strcmp(cmdtext, "/creartexto", true) == 0 || strcmp(cmdtext, "/crearlabel", true) == 0)
	{
	    #if defined SOLO_RCON
	    if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, Rojo, "<!> No eres Administrador RCON."), PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	    #endif
	    new ID = SiguienteLabelLibre();
	    if(ID > MAX_LABELS || ID < 0) return SendClientMessage(playerid, Rojo, "La cantidad de 3DTextLabels ha llegado a su límite! Cambiar: #define MAX_LABELS");
	    ShowPlayerDialog(playerid, DIALOG_CREARLABEL_TXT, DIALOG_STYLE_INPUT, "Crear Texto", "Introduce el Texto que quieres que tenga:", "Siguiente", "Cancelar");
	    return 1;
	}

	if(strcmp(cmd, "/editartexto", true) == 0 || strcmp(cmd, "/editarlabel", true) == 0)
	{
	    #if defined SOLO_RCON
	    if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, Rojo, "<!> No eres Administrador RCON."), PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	    #endif
	    new ID;
	    cmd = strtok(cmdtext, idx);
		if(!strlen(cmd)) return SendClientMessage(playerid, Amarillo, "USO: /editartexto [ID]");
		if(!IsNumeric(cmd)) return SendClientMessage(playerid, Rojo, "<!> El ID debe ser un número."), PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		ID = strval(cmd);
		if(ID >= 0 && ID < MAX_LABELS && TextLabel[ID][LabelCreado] == true)
		{
		    ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
		    EditandoLabel[playerid] = ID;
		} else {
		    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			SendClientMessage(playerid, Rojo, "<!> ID Inválido.");
		}
		return 1;
	}

	if(strcmp(cmd, "/borrartexto", true) == 0 || strcmp(cmd, "/borrarlabel", true) == 0)
	{
	    #if defined SOLO_RCON
	    if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, Rojo, "<!> No eres Administrador RCON."), PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	    #endif
	    new ID;
	    cmd = strtok(cmdtext, idx);
		if(!strlen(cmd)) return SendClientMessage(playerid, Amarillo, "USO: /borrartexto [ID]");
		if(!IsNumeric(cmd)) return SendClientMessage(playerid, Rojo, "<!> El ID debe ser un número."), PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		ID = strval(cmd);
		if(ID >= 0 && ID < MAX_LABELS && TextLabel[ID][LabelCreado] == true)
		{
		    new Mensaje[128];
		    format(Mensaje, sizeof(Mensaje), "> Texto ID: %d Borrado.", ID);
		    BorrarLabel(ID);
		    SendClientMessage(playerid, Rojo, Mensaje);
		    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
		    for(new i = 0; i < MAX_PLAYERS; i++) if(IsPlayerConnected(i) && EditandoLabel[i] == ID) EditandoLabel[i] = -1;
		} else {
		    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			SendClientMessage(playerid, Rojo, "<!> ID Inválido.");
		}
		return 1;
	}
	
	return 0;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
 	switch(dialogid)
	{
	    case DIALOG_CREARLABEL_TXT:
	    {
	        if(response)
	        {
	            if(!strlen(inputtext))
	            {
	                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	                SendClientMessage(playerid, Rojo, "<!> No has introducido el texto.");
	                return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_TXT, DIALOG_STYLE_INPUT, "Crear Texto", "Introduce el Texto que quieres que tenga:", "Siguiente", "Cancelar");
	            }
				new ID = SiguienteLabelLibre();
	            strmid(TextLabel[ID][LabelTexto], inputtext, 0, strlen(inputtext), 128);
				CreandoLabel[playerid] = ID;
				GuardarLabel(ID);
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
				return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_POS, DIALOG_STYLE_LIST, "Crear Texto (Posición)", "Introducir coordenadas (X, Y, Z)\nPosición actual", "Seleccionar", "Atrás");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return CreandoLabel[playerid] = -1;
			}
		}
		case DIALOG_CREARLABEL_POS:
		{
		    if(CreandoLabel[playerid] == -1) return 0;
		    if(response)
			{
			    PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
			    if(listitem == 0) return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_POS_2, DIALOG_STYLE_INPUT, "Crear Texto (Posición)", "Introduce las coordenadas (X, Y, Z) en la que quieres que aparezca el Texto:", "Siguiente", "Atrás");
			    else if(listitem == 1)
				{
				    new ID = CreandoLabel[playerid];
	            	GetPlayerPos(playerid, TextLabel[ID][LabelX], TextLabel[ID][LabelY], TextLabel[ID][LabelZ]);
	            	return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_CLR, DIALOG_STYLE_LIST, "Crear Texto (Color)", "Introducir color hexadecimal\nElegir color prehecho", "Seleccionar", "Atrás");
				}
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
       			return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_TXT, DIALOG_STYLE_INPUT, "Crear Texto", "Introduce el Texto que quieres que tenga:", "Siguiente", "Cancelar");
			}
		}
		case DIALOG_CREARLABEL_POS_2:
		{
		    if(CreandoLabel[playerid] == -1) return 0;
		    if(response)
			{
			    if(!strlen(inputtext))
	            {
	                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	                SendClientMessage(playerid, Rojo, "<!> No has introducido las coordenadas.");
	                return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_POS_2, DIALOG_STYLE_INPUT, "Crear Texto (Posición)", "Introduce las coordenadas (X, Y, Z) en la que quieres que aparezca el Texto:", "Siguiente", "Atrás");
	            }
	            new ID = CreandoLabel[playerid];
                new len = strlen(inputtext);
                new Linea[128], idx;
				for(new l = 0; l < len; l++) if(inputtext[l] == '|' || inputtext[l] == ',') inputtext[l] = ' ';
			    PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
			    Linea = strtok(inputtext, idx);
			    TextLabel[ID][LabelX] = floatstr(Linea);
			    Linea = strtok(inputtext, idx);
			    if(!strlen(Linea))
	            {
	                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	                SendClientMessage(playerid, Rojo, "<!> Coordenadas Inválidas.");
	                return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_POS_2, DIALOG_STYLE_INPUT, "Crear Texto (Posición)", "Introduce las coordenadas (X, Y, Z) en la que quieres que aparezca el Texto:", "Siguiente", "Atrás");
	            }
			    TextLabel[ID][LabelY] = floatstr(Linea);
			    Linea = strtok(inputtext, idx);
			    if(!strlen(Linea))
	            {
	                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	                SendClientMessage(playerid, Rojo, "<!> Coordenadas Inválidas.");
	                return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_POS_2, DIALOG_STYLE_INPUT, "Crear Texto (Posición)", "Introduce las coordenadas (X, Y, Z) en la que quieres que aparezca el Texto:", "Siguiente", "Atrás");
	            }
			    TextLabel[ID][LabelZ] = floatstr(Linea);
	            return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_CLR, DIALOG_STYLE_LIST, "Crear Texto (Color)", "Introducir color hexadecimal\nElegir color prehecho", "Seleccionar", "Atrás");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
      			return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_POS, DIALOG_STYLE_LIST, "Crear Texto (Posición)", "Introducir coordenadas (X, Y, Z)\nPosición actual", "Seleccionar", "Atrás");
			}
		}
		case DIALOG_CREARLABEL_CLR:
		{
		    if(CreandoLabel[playerid] == -1) return 0;
		    if(response)
			{
			    PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
			    if(listitem == 0) return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_CLR_2, DIALOG_STYLE_INPUT, "Crear Texto (Color)", "Introduce el color hexadecimal que quieres que tenga:\n\nFormatos válidos: 0xFFFFFFFF | #FFFFFF | FFFFFF", "Siguiente", "Atrás");
			    else if(listitem == 1) return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_CLR_3, DIALOG_STYLE_LIST, "Crear Texto (Color)", "{FFFFFF}Blanco\n{000000}Negro\n{FF0000}Rojo\n{0000FF}Azul\n{FFFF00}Amarillo\n{00FF00}Verde\n{FF8000}Naranja\n{8000FF}Violeta\n{FF80FF}Rosado\n{00FFFF}Celeste", "Seleccionar", "Atrás");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_POS, DIALOG_STYLE_LIST, "Crear Texto (Posición)", "Introducir coordenadas (X, Y, Z)\nPosición actual", "Seleccionar", "Atrás");
			}
		}
		case DIALOG_CREARLABEL_CLR_2:
		{
		    if(CreandoLabel[playerid] == -1) return 0;
		    if(response)
		    {
		        if(!strlen(inputtext))
	            {
	                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	                SendClientMessage(playerid, Rojo, "<!> No has introducido el color.");
	                return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_CLR_2, DIALOG_STYLE_INPUT, "Crear Texto (Color)", "Introduce el color hexadecimal que quieres que tenga:\n\nFormatos válidos: 0xFFFFFFFF | #FFFFFF | FFFFFF", "Siguiente", "Atrás");
	            }
	            new ID = CreandoLabel[playerid];
	            // Por Zamaroth:
	            new red[3], green[3], blue[3], alpha[3];
                if(inputtext[0] == '0' && inputtext[1] == 'x') // Esta usando el formato 0xFFFFFF
                {
                    if(strlen(inputtext) != 8 && strlen(inputtext) != 10) return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_CLR_2, DIALOG_STYLE_INPUT, "Crear Texto (Color)", "Introduce el color hexadecimal que quieres que tenga:\n\nFormatos válidos: 0xFFFFFFFF | #FFFFFF | FFFFFF", "Siguiente", "Atrás");
                    else
                    {
	                    format(red, sizeof(red), "%c%c", inputtext[2], inputtext[3]);
	                    format(green, sizeof(green), "%c%c", inputtext[4], inputtext[5]);
	                    format(blue, sizeof(blue), "%c%c", inputtext[6], inputtext[7]);
	                    if(inputtext[8] != '\0')
	                        format(alpha, sizeof(alpha), "%c%c", inputtext[8], inputtext[9]);
						else
						    alpha = "FF";
					}
                }
                else if(inputtext[0] == '#') // Esta usando el formato #FFFFFF
                {
                    if(strlen(inputtext) != 7 && strlen(inputtext) != 9) return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_CLR_2, DIALOG_STYLE_INPUT, "Crear Texto (Color)", "Introduce el color hexadecimal que quieres que tenga:\n\nFormatos válidos: 0xFFFFFFFF | #FFFFFF | FFFFFF", "Siguiente", "Atrás");
                    else
                    {
	                    format(red, sizeof(red), "%c%c", inputtext[1], inputtext[2]);
	                    format(green, sizeof(green), "%c%c", inputtext[3], inputtext[4]);
	                    format(blue, sizeof(blue), "%c%c", inputtext[5], inputtext[6]);
	                    if(inputtext[7] != '\0')
	                        format(alpha, sizeof(alpha), "%c%c", inputtext[7], inputtext[8]);
						else
						    alpha = "FF";
					}
                }
                else // Esta usando el formato FFFFFF
                {
                    if(strlen(inputtext) != 6 && strlen(inputtext) != 8) return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_CLR_2, DIALOG_STYLE_INPUT, "Crear Texto (Color)", "Introduce el color hexadecimal que quieres que tenga:\n\nFormatos válidos: 0xFFFFFFFF | #FFFFFF | FFFFFF", "Siguiente", "Atrás");
                    else
                    {
	                    format(red, sizeof(red), "%c%c", inputtext[0], inputtext[1]);
	                    format(green, sizeof(green), "%c%c", inputtext[2], inputtext[3]);
	                    format(blue, sizeof(blue), "%c%c", inputtext[4], inputtext[5]);
	                    if(inputtext[6] != '\0')
	                        format(alpha, sizeof(alpha), "%c%c", inputtext[6], inputtext[7]);
						else
						    alpha = "FF";
					}
                }
                TextLabel[ID][LabelColor] = RGB(HexToInt(red), HexToInt(green), HexToInt(blue), HexToInt(alpha));
                PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
                return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_RNG, DIALOG_STYLE_INPUT, "Crear Texto (Rango)", "Introduce el rango en el que quieres que se pueda ver el texto:\n\nEjemplo: 100.0", "Siguiente", "Atrás");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_CLR, DIALOG_STYLE_LIST, "Crear Texto (Color)", "Introducir color hexadecimal\nElegir color prehecho", "Seleccionar", "Atrás");
			}
		}
		case DIALOG_CREARLABEL_CLR_3:
		{
		    if(CreandoLabel[playerid] == -1) return 0;
		    if(response)
		    {
		        new ID = CreandoLabel[playerid];
                switch(listitem)
                {
                    case 0: TextLabel[ID][LabelColor] = 0xFFFFFFFF; // Blanco
                    case 1: TextLabel[ID][LabelColor] = 0x000000FF; // Negro
                    case 2: TextLabel[ID][LabelColor] = 0xFF0000FF; // Rojo
                    case 3: TextLabel[ID][LabelColor] = 0x0000FFFF; // Azul
                    case 4: TextLabel[ID][LabelColor] = 0xFFFF00FF; // Amarillo
                    case 5: TextLabel[ID][LabelColor] = 0x00FF00FF; // Verde
                    case 6: TextLabel[ID][LabelColor] = 0xFF8000FF; // Naranja
                    case 7: TextLabel[ID][LabelColor] = 0x8000FFFF; // Violeta
                    case 8: TextLabel[ID][LabelColor] = 0xFF80FFFF; // Rosado
                    case 9: TextLabel[ID][LabelColor] = 0x00FFFFFF; // Celeste
                }
                PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
                return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_RNG, DIALOG_STYLE_INPUT, "Crear Texto (Rango)", "Introduce el rango en el que quieres que se pueda ver el texto:\n\nEjemplo: 100.0", "Siguiente", "Atrás");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_CLR, DIALOG_STYLE_LIST, "Crear Texto (Color)", "Introducir color hexadecimal\nElegir color prehecho", "Seleccionar", "Atrás");
			}
		}
		case DIALOG_CREARLABEL_RNG:
		{
		    if(CreandoLabel[playerid] == -1) return 0;
			if(response)
			{
			    if(!strlen(inputtext))
			    {
					PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid, Rojo, "<!> No has introducido el rango.");
			    	return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_RNG, DIALOG_STYLE_INPUT, "Crear Texto (Rango)", "Introduce el rango en el que quieres que se pueda ver el texto:\n\nEjemplo: 100.0", "Siguiente", "Atrás");
				}
				if(floatstr(inputtext) < 1)
				{
				    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				    SendClientMessage(playerid, Rojo, "<!> Rango Inválido.");
			    	return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_RNG, DIALOG_STYLE_INPUT, "Crear Texto (Rango)", "Introduce el rango en el que quieres que se pueda ver el texto:\n\nEjemplo: 100.0", "Siguiente", "Atrás");
				}
				new ID = CreandoLabel[playerid];
				TextLabel[ID][LabelRange] = floatstr(inputtext);
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
				return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_VWD, DIALOG_STYLE_LIST, "Crear Texto (VirtualWorld)", "Introducir VirtualWorld ID\nVirtualWorld actual", "Seleccionar", "Atrás");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_CLR, DIALOG_STYLE_LIST, "Crear Texto (Color)", "Introducir color hexadecimal\nElegir color prehecho", "Seleccionar", "Atrás");
			}
		}
  		case DIALOG_CREARLABEL_VWD:
		{
		    if(CreandoLabel[playerid] == -1) return 0;
			if(response)
			{
			    PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
			    if(listitem == 0) return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_VWD_2, DIALOG_STYLE_INPUT, "Crear Texto (VirtualWorld)", "Introduce el VirtualWorld (Mundo) en el que quieres que se vea el texto:\n\nEjemplo: 0", "Siguiente", "Atrás");
			    else if(listitem == 1)
			    {
					new ID = CreandoLabel[playerid];
					TextLabel[ID][LabelVW] = GetPlayerVirtualWorld(playerid);
					return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_LOS, DIALOG_STYLE_MSGBOX, "Crear Texto (LOS)", "¿Deseas que el texto sea visible a través de los objetos?", "Sí", "No");
				}
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_RNG, DIALOG_STYLE_INPUT, "Crear Texto (Rango)", "Introduce el rango en el que quieres que se pueda ver el texto:\n\nEjemplo: 100.0", "Siguiente", "Atrás");
			}
		}
		case DIALOG_CREARLABEL_VWD_2:
		{
		    if(CreandoLabel[playerid] == -1) return 0;
			if(response)
			{
			    if(!strlen(inputtext))
			    {
					PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid, Rojo, "<!> No has introducido el VirtualWorld.");
			    	return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_VWD_2, DIALOG_STYLE_INPUT, "Crear Texto (VirtualWorld)", "Introduce el VirtualWorld (Mundo) en el que quieres que se vea el texto:\n\nEjemplo: 0", "Siguiente", "Atrás");
				}
				if(!IsNumeric(inputtext))
				{
				    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				    SendClientMessage(playerid, Rojo, "<!> El VirtualWorld debe ser un número.");
			    	return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_VWD_2, DIALOG_STYLE_INPUT, "Crear Texto (VirtualWorld)", "Introduce el VirtualWorld (Mundo) en el que quieres que se vea el texto:\n\nEjemplo: 0", "Siguiente", "Atrás");
				}
				if(strval(inputtext) < 0 || strval(inputtext) > 2000000)
				{
				    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				    SendClientMessage(playerid, Rojo, "<!> VirtualWorld Inválido.");
			    	return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_VWD_2, DIALOG_STYLE_INPUT, "Crear Texto (VirtualWorld)", "Introduce el VirtualWorld (Mundo) en el que quieres que se vea el texto:\n\nEjemplo: 0", "Siguiente", "Atrás");
				}
				new ID = CreandoLabel[playerid];
				TextLabel[ID][LabelVW] = strval(inputtext);
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
				return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_LOS, DIALOG_STYLE_MSGBOX, "Crear Texto (LOS)", "¿Deseas que el texto sea visible a través de los objetos?", "Sí", "No");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_CREARLABEL_VWD, DIALOG_STYLE_LIST, "Crear Texto (VirtualWorld)", "Introducir VirtualWorld ID\nVirtualWorld actual", "Seleccionar", "Atrás");
			}
		}
		case DIALOG_CREARLABEL_LOS:
		{
		    if(CreandoLabel[playerid] == -1) return 0;
		    new ID = SiguienteLabelLibre();
      		if(ID > MAX_LABELS || ID < 0) return SendClientMessage(playerid, Rojo, "La cantidad de 3DTextLabels ha llegado a su límite! Cambiar: #define MAX_LABELS");
        	else ID = CreandoLabel[playerid];
			if(response)
			{
				TextLabel[ID][LabelLOS] = 0;
			} else {
                TextLabel[ID][LabelLOS] = 1;
			}
			new Mensaje[36];
			format(Mensaje, sizeof(Mensaje), "> Texto creado con éxito! ID: %d.", ID);
			TextLabel[ID][LabelCreado] = true;
		    TextLabel[ID][Label] = Create3DTextLabel(TextLabel[ID][LabelTexto], TextLabel[ID][LabelColor], TextLabel[ID][LabelX], TextLabel[ID][LabelY], TextLabel[ID][LabelZ], TextLabel[ID][LabelRange], TextLabel[ID][LabelVW], TextLabel[ID][LabelLOS]);
			GuardarLabel(ID);
			SendClientMessage(playerid, Rojo, Mensaje);
			PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
			return CreandoLabel[playerid] = -1;
		}
		case DIALOG_EDITARLABEL:
		{
		    if(response)
		    {
		        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
		        switch(listitem)
				{
				    case 0: return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_TXT, DIALOG_STYLE_INPUT, "Editar Texto", "Introduce el Texto que quieres que tenga:", "Aceptar", "Atrás");
				    case 1: return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_POS, DIALOG_STYLE_LIST, "Editar Texto (Posición)", "Introducir coordenadas (X, Y, Z)\nPosición actual", "Seleccionar", "Atrás");
				    case 2: return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_CLR, DIALOG_STYLE_LIST, "Editar Texto (Color)", "Introducir color hexadecimal\nElegir color prehecho", "Seleccionar", "Atrás");
				    case 3: return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_RNG, DIALOG_STYLE_INPUT, "Editar Texto (Rango)", "Introduce el rango en el que quieres que se pueda ver el texto:\n\nEjemplo: 100.0", "Aceptar", "Atrás");
				    case 4: return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_VWD, DIALOG_STYLE_LIST, "Editar Texto (VirtualWorld)", "Introducir VirtualWorld ID\nVirtualWorld actual", "Seleccionar", "Atrás");
				    case 5: return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_LOS, DIALOG_STYLE_MSGBOX, "Editar Texto (LOS)", "¿Deseas que el texto sea visible a través de los objetos?", "Sí", "No");
				}
		    } else {
		        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		        return EditandoLabel[playerid] = -1;
		    }
		}
		case DIALOG_EDITARLABEL_TXT:
		{
		    if(EditandoLabel[playerid] == -1 || TextLabel[EditandoLabel[playerid]][LabelCreado] == false) return 0;
		    if(response)
	        {
	            if(!strlen(inputtext))
	            {
	                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	                SendClientMessage(playerid, Rojo, "<!> No has introducido el texto.");
	                return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_TXT, DIALOG_STYLE_INPUT, "Editar Texto", "Introduce el Texto que quieres que tenga:", "Aceptar", "Atrás");
	            }
	            new ID = EditandoLabel[playerid];
	            new Mensaje[36];
				format(Mensaje, sizeof(Mensaje), "> Texto editado con éxito! ID: %d.", ID);
	            strmid(TextLabel[ID][LabelTexto], inputtext, 0, strlen(inputtext), 128);
	            Update3DTextLabelText(TextLabel[ID][Label], TextLabel[ID][LabelColor], TextLabel[ID][LabelTexto]);
	            GuardarLabel(ID);
	            SendClientMessage(playerid, Rojo, Mensaje);
	            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
				return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
			}
		}
		case DIALOG_EDITARLABEL_POS:
		{
		    if(EditandoLabel[playerid] == -1 || TextLabel[EditandoLabel[playerid]][LabelCreado] == false) return 0;
		    if(response)
			{
			    if(listitem == 0) return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_POS_2, DIALOG_STYLE_INPUT, "Editar Texto (Posición)", "Introduce las coordenadas (X, Y, Z) en la que quieres que aparezca el Texto:", "Aceptar", "Atrás");
			    else if(listitem == 1)
				{
				    new ID = EditandoLabel[playerid];
				    new Mensaje[36];
					format(Mensaje, sizeof(Mensaje), "> Texto editado con éxito! ID: %d.", ID);
	            	GetPlayerPos(playerid, TextLabel[ID][LabelX], TextLabel[ID][LabelY], TextLabel[ID][LabelZ]);
	            	Delete3DTextLabel(TextLabel[ID][Label]);
	            	TextLabel[ID][Label] = Create3DTextLabel(TextLabel[ID][LabelTexto], TextLabel[ID][LabelColor], TextLabel[ID][LabelX], TextLabel[ID][LabelY], TextLabel[ID][LabelZ], TextLabel[ID][LabelRange], TextLabel[ID][LabelVW], TextLabel[ID][LabelLOS]);
					GuardarLabel(ID);
					SendClientMessage(playerid, Rojo, Mensaje);
					PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
	            	return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
				}
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
       			return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
			}
		}
		case DIALOG_EDITARLABEL_POS_2:
		{
		    if(EditandoLabel[playerid] == -1 || TextLabel[EditandoLabel[playerid]][LabelCreado] == false) return 0;
		    if(response)
			{
			    if(!strlen(inputtext))
	            {
	                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	                SendClientMessage(playerid, Rojo, "<!> No has introducido las coordenadas.");
	                return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_POS_2, DIALOG_STYLE_INPUT, "Editar Texto (Posición)", "Introduce las coordenadas (X, Y, Z) en la que quieres que aparezca el Texto:", "Aceptar", "Atrás");
	            }
	            new ID = EditandoLabel[playerid];
                new len = strlen(inputtext);
                new Linea[128], idx;
				for(new l = 0; l < len; l++) if(inputtext[l] == '|' || inputtext[l] == ',') inputtext[l] = ' ';
			    Linea = strtok(inputtext, idx);
			    if(!strlen(Linea))
	            {
	                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	                SendClientMessage(playerid, Rojo, "<!> Coordenadas Inválidas.");
	                return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_POS_2, DIALOG_STYLE_INPUT, "Editar Texto (Posición)", "Introduce las coordenadas (X, Y, Z) en la que quieres que aparezca el Texto:", "Aceptar", "Atrás");
	            }
			    TextLabel[ID][LabelX] = floatstr(Linea);
			    Linea = strtok(inputtext, idx);
			    if(!strlen(Linea))
	            {
	                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	                SendClientMessage(playerid, Rojo, "<!> Coordenadas Inválidas.");
	                return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_POS_2, DIALOG_STYLE_INPUT, "Editar Texto (Posición)", "Introduce las coordenadas (X, Y, Z) en la que quieres que aparezca el Texto:", "Aceptar", "Atrás");
	            }
			    TextLabel[ID][LabelY] = floatstr(Linea);
			    Linea = strtok(inputtext, idx);
			    if(!strlen(Linea))
	            {
	                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	                SendClientMessage(playerid, Rojo, "<!> Coordenadas Inválidas.");
	                return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_POS_2, DIALOG_STYLE_INPUT, "Editar Texto (Posición)", "Introduce las coordenadas (X, Y, Z) en la que quieres que aparezca el Texto:", "Aceptar", "Atrás");
	            }
	            new Mensaje[36];
				format(Mensaje, sizeof(Mensaje), "> Texto editado con éxito! ID: %d.", ID);
			    TextLabel[ID][LabelZ] = floatstr(Linea);
			    Delete3DTextLabel(TextLabel[ID][Label]);
			    TextLabel[ID][Label] = Create3DTextLabel(TextLabel[ID][LabelTexto], TextLabel[ID][LabelColor], TextLabel[ID][LabelX], TextLabel[ID][LabelY], TextLabel[ID][LabelZ], TextLabel[ID][LabelRange], TextLabel[ID][LabelVW], TextLabel[ID][LabelLOS]);
				GuardarLabel(ID);
				SendClientMessage(playerid, Rojo, Mensaje);
				PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
	            return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
      			return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_POS, DIALOG_STYLE_LIST, "Editar Texto (Posición)", "Introducir coordenadas (X, Y, Z)\nPosición actual", "Seleccionar", "Atrás");
			}
		}
		case DIALOG_EDITARLABEL_CLR:
		{
		    if(EditandoLabel[playerid] == -1 || TextLabel[EditandoLabel[playerid]][LabelCreado] == false) return 0;
		    if(response)
		    {
		        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
			    if(listitem == 0) return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_CLR_2, DIALOG_STYLE_INPUT, "Editar Texto (Color)", "Introduce el color hexadecimal que quieres que tenga:\n\nFormatos válidos: 0xFFFFFFFF | #FFFFFF | FFFFFF", "Aceptar", "Atrás");
			    else if(listitem == 1) return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_CLR_3, DIALOG_STYLE_LIST, "Editar Texto (Color)", "{FFFFFF}Blanco\n{000000}Negro\n{FF0000}Rojo\n{0000FF}Azul\n{FFFF00}Amarillo\n{00FF00}Verde\n{FF8000}Naranja\n{8000FF}Violeta\n{FF80FF}Rosado\n{00FFFF}Celeste", "Seleccionar", "Atrás");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
			}
		}
		case DIALOG_EDITARLABEL_CLR_2:
		{
		    if(EditandoLabel[playerid] == -1 || TextLabel[EditandoLabel[playerid]][LabelCreado] == false) return 0;
		    if(response)
		    {
		        if(!strlen(inputtext))
	            {
	                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	                SendClientMessage(playerid, Rojo, "<!> No has introducido el color.");
	                return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_CLR_2, DIALOG_STYLE_INPUT, "Editar Texto (Color)", "Introduce el color hexadecimal que quieres que tenga:\n\nFormatos válidos: 0xFFFFFFFF | #FFFFFF | FFFFFF", "Aceptar", "Atrás");
	            }
	            new ID = EditandoLabel[playerid];
	            // Por Zamaroth:
	            new red[3], green[3], blue[3], alpha[3];
                if(inputtext[0] == '0' && inputtext[1] == 'x') // Esta usando el formato 0xFFFFFF
                {
                    if(strlen(inputtext) != 8 && strlen(inputtext) != 10) return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_CLR_2, DIALOG_STYLE_INPUT, "Editar Texto (Color)", "Introduce el color hexadecimal que quieres que tenga:\n\nFormatos válidos: 0xFFFFFFFF | #FFFFFF | FFFFFF", "Aceptar", "Atrás");
                    else
                    {
	                    format(red, sizeof(red), "%c%c", inputtext[2], inputtext[3]);
	                    format(green, sizeof(green), "%c%c", inputtext[4], inputtext[5]);
	                    format(blue, sizeof(blue), "%c%c", inputtext[6], inputtext[7]);
	                    if(inputtext[8] != '\0')
	                        format(alpha, sizeof(alpha), "%c%c", inputtext[8], inputtext[9]);
						else
						    alpha = "FF";
					}
                }
                else if(inputtext[0] == '#') // Esta usando el formato #FFFFFF
                {
                    if(strlen(inputtext) != 7 && strlen(inputtext) != 9) return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_CLR_2, DIALOG_STYLE_INPUT, "Editar Texto (Color)", "Introduce el color hexadecimal que quieres que tenga:\n\nFormatos válidos: 0xFFFFFFFF | #FFFFFF | FFFFFF", "Aceptar", "Atrás");
                    else
                    {
	                    format(red, sizeof(red), "%c%c", inputtext[1], inputtext[2]);
	                    format(green, sizeof(green), "%c%c", inputtext[3], inputtext[4]);
	                    format(blue, sizeof(blue), "%c%c", inputtext[5], inputtext[6]);
	                    if(inputtext[7] != '\0')
	                        format(alpha, sizeof(alpha), "%c%c", inputtext[7], inputtext[8]);
						else
						    alpha = "FF";
					}
                }
                else // Esta usando el formato FFFFFF
                {
                    if(strlen(inputtext) != 6 && strlen(inputtext) != 8) return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_CLR_2, DIALOG_STYLE_INPUT, "Crear Texto (Color)", "Introduce el color hexadecimal que quieres que tenga:\n\nFormatos válidos: 0xFFFFFFFF | #FFFFFF | FFFFFF", "Aceptar", "Atrás");
                    else
                    {
	                    format(red, sizeof(red), "%c%c", inputtext[0], inputtext[1]);
	                    format(green, sizeof(green), "%c%c", inputtext[2], inputtext[3]);
	                    format(blue, sizeof(blue), "%c%c", inputtext[4], inputtext[5]);
	                    if(inputtext[6] != '\0')
	                        format(alpha, sizeof(alpha), "%c%c", inputtext[6], inputtext[7]);
						else
						    alpha = "FF";
					}
                }
                new Mensaje[36];
				format(Mensaje, sizeof(Mensaje), "> Texto editado con éxito! ID: %d.", ID);
                TextLabel[ID][LabelColor] = RGB(HexToInt(red), HexToInt(green), HexToInt(blue), HexToInt(alpha));
                Update3DTextLabelText(TextLabel[ID][Label], TextLabel[ID][LabelColor], TextLabel[ID][LabelTexto]);
	            GuardarLabel(ID);
	            SendClientMessage(playerid, Rojo, Mensaje);
	            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
    			return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_CLR, DIALOG_STYLE_LIST, "Editar Texto (Color)", "Introducir color hexadecimal\nElegir color prehecho", "Seleccionar", "Atrás");
			}
		}
		case DIALOG_EDITARLABEL_CLR_3:
		{
		    if(EditandoLabel[playerid] == -1 || TextLabel[EditandoLabel[playerid]][LabelCreado] == false) return 0;
		    if(response)
		    {
		        new ID = EditandoLabel[playerid];
                switch(listitem)
                {
                    case 0: TextLabel[ID][LabelColor] = 0xFFFFFFFF; // Blanco
                    case 1: TextLabel[ID][LabelColor] = 0x000000FF; // Negro
                    case 2: TextLabel[ID][LabelColor] = 0xFF0000FF; // Rojo
                    case 3: TextLabel[ID][LabelColor] = 0x0000FFFF; // Azul
                    case 4: TextLabel[ID][LabelColor] = 0xFFFF00FF; // Amarillo
                    case 5: TextLabel[ID][LabelColor] = 0x00FF00FF; // Verde
                    case 6: TextLabel[ID][LabelColor] = 0xFF8000FF; // Naranja
                    case 7: TextLabel[ID][LabelColor] = 0x8000FFFF; // Violeta
                    case 8: TextLabel[ID][LabelColor] = 0xFF80FFFF; // Rosado
                    case 9: TextLabel[ID][LabelColor] = 0x00FFFFFF; // Celeste
                }
                new Mensaje[36];
				format(Mensaje, sizeof(Mensaje), "> Texto editado con éxito! ID: %d.", ID);
                Update3DTextLabelText(TextLabel[ID][Label], TextLabel[ID][LabelColor], TextLabel[ID][LabelTexto]);
	            GuardarLabel(ID);
	            SendClientMessage(playerid, Rojo, Mensaje);
	            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
    			return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_CLR, DIALOG_STYLE_LIST, "Editar Texto (Color)", "Introducir color hexadecimal\nElegir color prehecho", "Seleccionar", "Atrás");
			}
		}
		case DIALOG_EDITARLABEL_RNG:
		{
		    if(EditandoLabel[playerid] == -1 || TextLabel[EditandoLabel[playerid]][LabelCreado] == false) return 0;
		    if(response)
			{
			    if(!strlen(inputtext))
			    {
					PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid, Rojo, "<!> No has introducido el rango.");
			    	return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_RNG, DIALOG_STYLE_INPUT, "Editar Texto (Rango)", "Introduce el rango en el que quieres que se pueda ver el texto:\n\nEjemplo: 100.0", "Aceptar", "Atrás");
				}
				if(floatstr(inputtext) < 1)
				{
				    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				    SendClientMessage(playerid, Rojo, "<!> Rango Inválido.");
			    	return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_RNG, DIALOG_STYLE_INPUT, "Editar Texto (Rango)", "Introduce el rango en el que quieres que se pueda ver el texto:\n\nEjemplo: 100.0", "Aceptar", "Atrás");
				}
				new ID = EditandoLabel[playerid];
				new Mensaje[36];
				format(Mensaje, sizeof(Mensaje), "> Texto editado con éxito! ID: %d.", ID);
				TextLabel[ID][LabelRange] = floatstr(inputtext);
				Delete3DTextLabel(TextLabel[ID][Label]);
			    TextLabel[ID][Label] = Create3DTextLabel(TextLabel[ID][LabelTexto], TextLabel[ID][LabelColor], TextLabel[ID][LabelX], TextLabel[ID][LabelY], TextLabel[ID][LabelZ], TextLabel[ID][LabelRange], TextLabel[ID][LabelVW], TextLabel[ID][LabelLOS]);
				GuardarLabel(ID);
				SendClientMessage(playerid, Rojo, Mensaje);
				PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
				return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
			}
		}
		case DIALOG_EDITARLABEL_VWD:
		{
		    if(EditandoLabel[playerid] == -1 || TextLabel[EditandoLabel[playerid]][LabelCreado] == false) return 0;
		    if(response)
			{
			    if(listitem == 0) return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_VWD_2, DIALOG_STYLE_INPUT, "Editar Texto (VirtualWorld)", "Introduce el VirtualWorld (Mundo) en el que quieres que se vea el texto:\n\nEjemplo: 0", "Aceptar", "Atrás");
			    else if(listitem == 1)
			    {
					new ID = EditandoLabel[playerid];
					new Mensaje[36];
					format(Mensaje, sizeof(Mensaje), "> Texto editado con éxito! ID: %d.", ID);
					TextLabel[ID][LabelVW] = GetPlayerVirtualWorld(playerid);
					Delete3DTextLabel(TextLabel[ID][Label]);
				    TextLabel[ID][Label] = Create3DTextLabel(TextLabel[ID][LabelTexto], TextLabel[ID][LabelColor], TextLabel[ID][LabelX], TextLabel[ID][LabelY], TextLabel[ID][LabelZ], TextLabel[ID][LabelRange], TextLabel[ID][LabelVW], TextLabel[ID][LabelLOS]);
					GuardarLabel(ID);
					SendClientMessage(playerid, Rojo, Mensaje);
					PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
					return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
				}
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
			}
		}
		case DIALOG_EDITARLABEL_VWD_2:
		{
		    if(EditandoLabel[playerid] == -1 || TextLabel[EditandoLabel[playerid]][LabelCreado] == false) return 0;
		    if(response)
			{
			    if(!strlen(inputtext))
			    {
					PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid, Rojo, "<!> No has introducido el VirtualWorld.");
			    	return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_VWD_2, DIALOG_STYLE_INPUT, "Editar Texto (VirtualWorld)", "Introduce el VirtualWorld (Mundo) en el que quieres que se vea el texto:\n\nEjemplo: 0", "Aceptar", "Atrás");
				}
				if(!IsNumeric(inputtext))
				{
				    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				    SendClientMessage(playerid, Rojo, "<!> El VirtualWorld debe ser un número.");
			    	return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_VWD_2, DIALOG_STYLE_INPUT, "Editar Texto (VirtualWorld)", "Introduce el VirtualWorld (Mundo) en el que quieres que se vea el texto:\n\nEjemplo: 0", "Aceptar", "Atrás");
				}
				if(strval(inputtext) < 0 || strval(inputtext) > 2000000)
				{
				    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				    SendClientMessage(playerid, Rojo, "<!> VirtualWorld Inválido.");
			    	return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_VWD_2, DIALOG_STYLE_INPUT, "Editar Texto (VirtualWorld)", "Introduce el VirtualWorld (Mundo) en el que quieres que se vea el texto:\n\nEjemplo: 0", "Aceptar", "Atrás");
				}
				new ID = EditandoLabel[playerid];
				new Mensaje[36];
				format(Mensaje, sizeof(Mensaje), "> Texto editado con éxito! ID: %d.", ID);
				TextLabel[ID][LabelVW] = strval(inputtext);
				Delete3DTextLabel(TextLabel[ID][Label]);
			    TextLabel[ID][Label] = Create3DTextLabel(TextLabel[ID][LabelTexto], TextLabel[ID][LabelColor], TextLabel[ID][LabelX], TextLabel[ID][LabelY], TextLabel[ID][LabelZ], TextLabel[ID][LabelRange], TextLabel[ID][LabelVW], TextLabel[ID][LabelLOS]);
				GuardarLabel(ID);
				SendClientMessage(playerid, Rojo, Mensaje);
				PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
				return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
			} else {
			    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			    return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL_VWD, DIALOG_STYLE_LIST, "Editar Texto (VirtualWorld)", "Introducir VirtualWorld ID\nVirtualWorld actual", "Seleccionar", "Atrás");
			}
		}
		case DIALOG_EDITARLABEL_LOS:
		{
		    if(EditandoLabel[playerid] == -1 || TextLabel[EditandoLabel[playerid]][LabelCreado] == false) return 0;
		    new ID = EditandoLabel[playerid];
		    new Mensaje[36];
			format(Mensaje, sizeof(Mensaje), "> Texto editado con éxito! ID: %d.", ID);
		    if(response)
			{
				TextLabel[ID][LabelLOS] = 0;
			} else {
                TextLabel[ID][LabelLOS] = 1;
			}
			Delete3DTextLabel(TextLabel[ID][Label]);
		    TextLabel[ID][Label] = Create3DTextLabel(TextLabel[ID][LabelTexto], TextLabel[ID][LabelColor], TextLabel[ID][LabelX], TextLabel[ID][LabelY], TextLabel[ID][LabelZ], TextLabel[ID][LabelRange], TextLabel[ID][LabelVW], TextLabel[ID][LabelLOS]);
			GuardarLabel(ID);
			SendClientMessage(playerid, Rojo, Mensaje);
			PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
			return ShowPlayerDialog(playerid, DIALOG_EDITARLABEL, DIALOG_STYLE_LIST, "Editar Texto", "Cambiar Texto\nCambiar Posición\nCambiar Color\nCambiar Rango\nCambiar VirtualWorld (Mundo)\nCambiar Visibilidad", "Seleccionar", "Cancelar");
		}
	}
	return 0;
}

stock GuardarLabel(ID)
{
	new PATH[20], Linea[135];
	format(PATH, sizeof(PATH), ARCHIVO_LABEL, ID);
	new File: Archivo = fopen(PATH, io_write);
	format(Linea, sizeof(Linea), "Texto=%s\n", TextLabel[ID][LabelTexto]); fwrite(Archivo, Linea);
	format(Linea, sizeof(Linea), "Color=%d\n", TextLabel[ID][LabelColor]); fwrite(Archivo, Linea);
	format(Linea, sizeof(Linea), "PosX=%f\n", TextLabel[ID][LabelX]); fwrite(Archivo, Linea);
	format(Linea, sizeof(Linea), "PosY=%f\n", TextLabel[ID][LabelY]); fwrite(Archivo, Linea);
	format(Linea, sizeof(Linea), "PosZ=%f\n", TextLabel[ID][LabelZ]); fwrite(Archivo, Linea);
	format(Linea, sizeof(Linea), "Rango=%f\n", TextLabel[ID][LabelRange]); fwrite(Archivo, Linea);
	format(Linea, sizeof(Linea), "VWorld=%d\n", TextLabel[ID][LabelVW]); fwrite(Archivo, Linea);
	format(Linea, sizeof(Linea), "LOS=%d", TextLabel[ID][LabelLOS]); fwrite(Archivo, Linea);
	fclose(Archivo);
	return 1;
}

stock CargarLabels()
{
    new LabelCount = 0;
    for(new l = 0; l < MAX_LABELS; l++)
	{
	    new PATH[20];
	    format(PATH, sizeof(PATH), ARCHIVO_LABEL, l);
	    if(fexist(PATH))
	    {
	        new File: Archivo = fopen(PATH, io_read);
	        if(Archivo)
	        {
	        	new Arg[256], Valor[256], Linea[256];
				while(fread(Archivo, Linea, sizeof(Linea)))
				{
				    if(strlen(Linea))
					Arg = ini_GetKey(Linea);
					if(strcmp(Arg, "Texto", true) == 0)
					{
						Valor = ini_GetValue( Linea );
						strmid(TextLabel[l][LabelTexto], Valor, 0, strlen(Valor), 128);
					}
					if(strcmp(Arg, "Color", true) == 0)
					{
						Valor = ini_GetValue( Linea );
						TextLabel[l][LabelColor] = strval(Valor);
					}
					if(strcmp(Arg, "PosX", true) == 0)
					{
						Valor = ini_GetValue( Linea );
						TextLabel[l][LabelX] = floatstr(Valor);
					}
					if(strcmp(Arg, "PosY", true) == 0)
					{
						Valor = ini_GetValue( Linea );
						TextLabel[l][LabelY] = floatstr(Valor);
					}
					if(strcmp(Arg, "PosZ", true) == 0)
					{
						Valor = ini_GetValue( Linea );
						TextLabel[l][LabelZ] = floatstr(Valor);
					}
					if(strcmp(Arg, "Rango", true) == 0)
					{
						Valor = ini_GetValue( Linea );
						TextLabel[l][LabelRange] = floatstr(Valor);
					}
					if(strcmp(Arg, "VWorld", true) == 0)
					{
						Valor = ini_GetValue( Linea );
						TextLabel[l][LabelVW] = strval(Valor);
					}
					if(strcmp(Arg, "LOS", true) == 0)
					{
						Valor = ini_GetValue( Linea );
						TextLabel[l][LabelLOS] = strval(Valor);
					}
				}
				TextLabel[l][LabelCreado] = true;
				TextLabel[l][Label] = Create3DTextLabel(TextLabel[l][LabelTexto], TextLabel[l][LabelColor], TextLabel[l][LabelX], TextLabel[l][LabelY], TextLabel[l][LabelZ], TextLabel[l][LabelRange], TextLabel[l][LabelVW], TextLabel[l][LabelLOS]);
				LabelCount++;
				fclose(Archivo);
			}
		}
	}
	printf("  Textos Creados: %d.", LabelCount);
	return 1;
}

stock BorrarLabel(ID)
{
	new PATH[20];
	TextLabel[ID][LabelCreado] = false;
	TextLabel[ID][LabelColor] = -255;
	TextLabel[ID][LabelX] = 0.0;
	TextLabel[ID][LabelY] = 0.0;
	TextLabel[ID][LabelZ] = 0.0;
	TextLabel[ID][LabelRange] = 0.0;
	TextLabel[ID][LabelVW] = -255;
	TextLabel[ID][LabelLOS] = -255;
	strdel(TextLabel[ID][LabelTexto], 0, strlen(TextLabel[ID][LabelTexto]));
	Delete3DTextLabel(TextLabel[ID][Label]);
	format(PATH, sizeof(PATH), ARCHIVO_LABEL, ID);
	if(fexist(PATH)) fremove(PATH);
}

stock SiguienteLabelLibre()
{
	new PATH[20];
    for(new l = 0; l < MAX_LABELS; l++)
	{
	    format(PATH, sizeof(PATH), ARCHIVO_LABEL, l);
		if(!fexist(PATH)) return l;
	}
	return -1;
}

stock ini_GetKey( line[] )
{
    new keyRes[256];
    keyRes[0] = 0;
    if( strfind( line , "=" , true ) == -1 ) return keyRes;
    strmid( keyRes , line , 0 , strfind( line , "=" , true ) , sizeof( keyRes) );
    return keyRes;
}

stock ini_GetValue( line[] )
{
    new valRes[256];
    valRes[0] = 0;
    if( strfind( line , "=" , true ) == -1 ) return valRes;
    strmid( valRes , line , strfind( line , "=" , true )+1 , strlen( line ) , sizeof( valRes ) );
    return valRes;
}

stock strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}
	new offset = index;
	new result[64];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

stock IsNumeric(const string[])
{
    new length = strlen(string);
    if(length == 0) return 0;
    for(new i = 0; i < length; i++)
    {
        if((string[i] > '9' || string[i] < '0' && string[i] != '-' && string[i] != '+') || (string[i] == '-' && i != 0) || (string[i] == '+' && i != 0)) return 0;
    }
    if(length == 1 && (string[0] == '-' || string[0] == '+')) return 0;
    return 1;
}

// Por Zamaroth:
stock RGB( red, green, blue, alpha )
{
	return (red * 16777216) + (green * 65536) + (blue * 256) + alpha;
}

// Por Dracoblue:
stock HexToInt(string[])
{
	if(string[0] == 0) return 0;
	new i;
  	new cur = 1;
  	new res = 0;
  	for(i = strlen(string); i > 0; i--)
  	{
    	if (string[i-1] < 58) res = res + cur * (string[i-1] - 48); else res = res + cur * (string[i-1] - 65 + 10);
    	cur = cur * 16;
  	}
  	return res;
}
