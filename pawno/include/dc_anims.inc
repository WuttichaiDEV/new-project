/*==============================================================================
		Animations System v1.3
			by Daniel_Cortez

http://pro-pawn.ru/showthread.php?9482-dc_anims

Copyright (c) 2014-2017 Stanislav Gromov (Daniel_Cortez)
This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the
use of this software. Permission is granted to anyone to use this software for
any purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:
	1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software in
		a product, an acknowledgment in the product documentation would be
		appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source distribution.
==============================================================================*/


#if defined DC__ANIMS
	#endinput
#endif
#define	DC__ANIMS


#include <a_samp>

#if defined CMD
	#define dc_anims__command:%0(%1) CMD:%0(%1)
#else
	#define dc_anims__command:%0(%1) dc_anims__command_%0(%1)
	#if	!defined	isnull
		#define isnull(%0) \
			(((%0)[0]) == '\0')
	#endif
#endif


#if	!defined	SPECIAL_ACTION_PISSING
	#define	SPECIAL_ACTION_PISSING	68
#endif

#if	!defined	DC_ANIMS_COLOR
	#define	DC_ANIMS_COLOR	"{70A0E0}"
#endif
#if	!defined	DC_ANIMS_ERROR_COLOR
	#define	DC_ANIMS_ERROR_COLOR	"{A0A0A0}"
#endif

#if	!defined	MAX_ACTION_NAME
	#define MAX_ACTION_NAME 7
#endif
#if	!defined	MAX_ANIM_LIB_NAME
	#define	MAX_ANIM_LIB_NAME 12
#endif
#if	!defined MAX_ANIM_NAME
	#define	MAX_ANIM_NAME 22
#endif

#define	_AnimLib(%0)	{{!#%0}, -1, -1}
#define	_Anim(%0,%1)	{ANIMLIB_%0, {!#%1}}

enum e_ANIM_LIB_INFO
{
	eAnimLib_Name[(MAX_ANIM_LIB_NAME+1) char],
	eAnimLib_FirstAnim,
	eAnimLib_LastAnim
};

enum e_ANIM_INFO
{
	eAnim_LibID,
	eAnim_Name[(MAX_ANIM_NAME+1) char]
};


enum
{
	DC_ANIMS__INVALID_ANIMLIB_ID = -1,
#if !defined DC_ANIMS_DISABLE__AIRPORT
	ANIMLIB_AIRPORT,
#endif
#if !defined DC_ANIMS_DISABLE__ATTRACTORS
	ANIMLIB_Attractors,
#endif
#if !defined DC_ANIMS_DISABLE__BAR
	ANIMLIB_BAR,
#endif
#if !defined DC_ANIMS_DISABLE__BASEBALL
	ANIMLIB_BASEBALL,
#endif
#if !defined DC_ANIMS_DISABLE__BD_FIRE
	ANIMLIB_BD_FIRE,
#endif
#if !defined DC_ANIMS_DISABLE__BEACH
	ANIMLIB_BEACH,
#endif
#if !defined DC_ANIMS_DISABLE__BENCHPRESS
	ANIMLIB_benchpress,
#endif
#if !defined DC_ANIMS_DISABLE__BF_INJECTION
	ANIMLIB_BF_injection,
#endif
#if !defined DC_ANIMS_DISABLE__BIKED
	ANIMLIB_BIKED,
#endif
#if !defined DC_ANIMS_DISABLE__BIKEH
	ANIMLIB_BIKEH,
#endif
#if !defined DC_ANIMS_DISABLE__BIKELEAP
	ANIMLIB_BIKELEAP,
#endif
#if !defined DC_ANIMS_DISABLE__BIKES
	ANIMLIB_BIKES,
#endif
#if !defined DC_ANIMS_DISABLE__BIKEV
	ANIMLIB_BIKEV,
#endif
#if !defined DC_ANIMS_DISABLE__BIKE_DBZ
	ANIMLIB_BIKE_DBZ,
#endif
#if !defined DC_ANIMS_DISABLE__BLOWJOBZ
	ANIMLIB_BLOWJOBZ,
#endif
#if !defined DC_ANIMS_DISABLE__BMX
	ANIMLIB_BMX,
#endif
#if !defined DC_ANIMS_DISABLE__BOMBER
	ANIMLIB_BOMBER,
#endif
#if !defined DC_ANIMS_DISABLE__BOX
	ANIMLIB_BOX,
#endif
#if !defined DC_ANIMS_DISABLE__BSKTBALL
	ANIMLIB_BSKTBALL,
#endif
#if !defined DC_ANIMS_DISABLE__BUDDY
	ANIMLIB_BUDDY,
#endif
#if !defined DC_ANIMS_DISABLE__BUS
	ANIMLIB_BUS,
#endif
#if !defined DC_ANIMS_DISABLE__CAMERA
	ANIMLIB_CAMERA,
#endif
#if !defined DC_ANIMS_DISABLE__CAR
	ANIMLIB_CAR,
#endif
#if !defined DC_ANIMS_DISABLE__CARRY
	ANIMLIB_CARRY,
#endif
#if !defined DC_ANIMS_DISABLE__CAR_CHAT
	ANIMLIB_CAR_CHAT,
#endif
#if !defined DC_ANIMS_DISABLE__CASINO
	ANIMLIB_CASINO,
#endif
#if !defined DC_ANIMS_DISABLE__CHAINSAW
	ANIMLIB_CHAINSAW,
#endif
#if !defined DC_ANIMS_DISABLE__CHOPPA
	ANIMLIB_CHOPPA,
#endif
#if !defined DC_ANIMS_DISABLE__CLOTHES
	ANIMLIB_CLOTHES,
#endif
#if !defined DC_ANIMS_DISABLE__COACH
	ANIMLIB_COACH,
#endif
#if !defined DC_ANIMS_DISABLE__COLT45
	ANIMLIB_COLT45,
#endif
#if !defined DC_ANIMS_DISABLE__COP_AMBIENT
	ANIMLIB_COP_AMBIENT,
#endif
#if !defined DC_ANIMS_DISABLE__COP_DVBYZ
	ANIMLIB_COP_DVBYZ,
#endif
#if !defined DC_ANIMS_DISABLE__CRACK
	ANIMLIB_CRACK,
#endif
#if !defined DC_ANIMS_DISABLE__CRIB
	ANIMLIB_CRIB,
#endif
#if !defined DC_ANIMS_DISABLE__DAM_JUMP
	ANIMLIB_DAM_JUMP,
#endif
#if !defined DC_ANIMS_DISABLE__DANCING
	ANIMLIB_DANCING,
#endif
#if !defined DC_ANIMS_DISABLE__DEALER
	ANIMLIB_DEALER,
#endif
#if !defined DC_ANIMS_DISABLE__DILDO
	ANIMLIB_DILDO,
#endif
#if !defined DC_ANIMS_DISABLE__DODGE
	ANIMLIB_DODGE,
#endif
#if !defined DC_ANIMS_DISABLE__DOZER
	ANIMLIB_DOZER,
#endif
#if !defined DC_ANIMS_DISABLE__DRIVEBYS
	ANIMLIB_DRIVEBYS,
#endif
#if !defined DC_ANIMS_DISABLE__FAT
	ANIMLIB_FAT,
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_B
	ANIMLIB_FIGHT_B,
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_C
	ANIMLIB_FIGHT_C,
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_D
	ANIMLIB_FIGHT_D,
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_E
	ANIMLIB_FIGHT_E,
#endif
#if !defined DC_ANIMS_DISABLE__FINALE
	ANIMLIB_FINALE,
#endif
#if !defined DC_ANIMS_DISABLE__FINALE2
	ANIMLIB_FINALE2,
#endif
#if !defined DC_ANIMS_DISABLE__FLAME
	ANIMLIB_FLAME,
#endif
#if !defined DC_ANIMS_DISABLE__FLOWERS
	ANIMLIB_Flowers,
#endif
#if !defined DC_ANIMS_DISABLE__FOOD
	ANIMLIB_FOOD,
#endif
#if !defined DC_ANIMS_DISABLE__FREEWEIGHTS
	ANIMLIB_Freeweights,
#endif
#if !defined DC_ANIMS_DISABLE__GANGS
	ANIMLIB_GANGS,
#endif
#if !defined DC_ANIMS_DISABLE__GFUNK
	ANIMLIB_GFUNK,
#endif
#if !defined DC_ANIMS_DISABLE__GHANDS
	ANIMLIB_GHANDS,
#endif
#if !defined DC_ANIMS_DISABLE__GHETTO_DB
	ANIMLIB_GHETTO_DB,
#endif
#if !defined DC_ANIMS_DISABLE__GOGGLES
	ANIMLIB_goggles,
#endif
#if !defined DC_ANIMS_DISABLE__GRAFFITI
	ANIMLIB_GRAFFITI,
#endif
#if !defined DC_ANIMS_DISABLE__GRAVEYARD
	ANIMLIB_GRAVEYARD,
#endif
#if !defined DC_ANIMS_DISABLE__GRENADE
	ANIMLIB_GRENADE,
#endif
#if !defined DC_ANIMS_DISABLE__GYMNASIUM
	ANIMLIB_GYMNASIUM,
#endif
#if !defined DC_ANIMS_DISABLE__HAIRCUTS
	ANIMLIB_HAIRCUTS,
#endif
#if !defined DC_ANIMS_DISABLE__HEIST9
	ANIMLIB_HEIST9,
#endif
#if !defined DC_ANIMS_DISABLE__INT_HOUSE
	ANIMLIB_INT_HOUSE,
#endif
#if !defined DC_ANIMS_DISABLE__INT_OFFICE
	ANIMLIB_INT_OFFICE,
#endif
#if !defined DC_ANIMS_DISABLE__INT_SHOP
	ANIMLIB_INT_SHOP,
#endif
#if !defined DC_ANIMS_DISABLE__JST_BUISNESS
	ANIMLIB_JST_BUISNESS,
#endif
#if !defined DC_ANIMS_DISABLE__KART
	ANIMLIB_KART,
#endif
#if !defined DC_ANIMS_DISABLE__KISSING
	ANIMLIB_KISSING,
#endif
#if !defined DC_ANIMS_DISABLE__KNIFE
	ANIMLIB_KNIFE,
#endif
#if !defined DC_ANIMS_DISABLE__LAPDAN1
	ANIMLIB_LAPDAN1,
#endif
#if !defined DC_ANIMS_DISABLE__LAPDAN2
	ANIMLIB_LAPDAN2,
#endif
#if !defined DC_ANIMS_DISABLE__LAPDAN3
	ANIMLIB_LAPDAN3,
#endif
#if !defined DC_ANIMS_DISABLE__LOWRIDER
	ANIMLIB_LOWRIDER,
#endif
#if !defined DC_ANIMS_DISABLE__MD_CHASE
	ANIMLIB_MD_CHASE,
#endif
#if !defined DC_ANIMS_DISABLE__MD_END
	ANIMLIB_MD_END,
#endif
#if !defined DC_ANIMS_DISABLE__MEDIC
	ANIMLIB_MEDIC,
#endif
#if !defined DC_ANIMS_DISABLE__MISC
	ANIMLIB_MISC,
#endif
#if !defined DC_ANIMS_DISABLE__MTB
	ANIMLIB_MTB,
#endif
#if !defined DC_ANIMS_DISABLE__MUSCULAR
	ANIMLIB_MUSCULAR,
#endif
#if !defined DC_ANIMS_DISABLE__NEVADA
	ANIMLIB_NEVADA,
#endif
#if !defined DC_ANIMS_DISABLE__ON_LOOKERS
	ANIMLIB_ON_LOOKERS,
#endif
#if !defined DC_ANIMS_DISABLE__OTB
	ANIMLIB_OTB,
#endif
#if !defined DC_ANIMS_DISABLE__PARACHUTE
	ANIMLIB_PARACHUTE,
#endif
#if !defined DC_ANIMS_DISABLE__PARK
	ANIMLIB_PARK,
#endif
#if !defined DC_ANIMS_DISABLE__PAULNMAC
	ANIMLIB_PAULNMAC,
#endif
#if !defined DC_ANIMS_DISABLE__PED
	ANIMLIB_ped,
#endif
#if !defined DC_ANIMS_DISABLE__PLAYER_DVBYS
	ANIMLIB_PLAYER_DVBYS,
#endif
#if !defined DC_ANIMS_DISABLE__PLAYIDLES
	ANIMLIB_PLAYIDLES,
#endif
#if !defined DC_ANIMS_DISABLE__POLICE
	ANIMLIB_POLICE,
#endif
#if !defined DC_ANIMS_DISABLE__POOL
	ANIMLIB_POOL,
#endif
#if !defined DC_ANIMS_DISABLE__POOR
	ANIMLIB_POOR,
#endif
#if !defined DC_ANIMS_DISABLE__PYTHON
	ANIMLIB_PYTHON,
#endif
#if !defined DC_ANIMS_DISABLE__QUAD
	ANIMLIB_QUAD,
#endif
#if !defined DC_ANIMS_DISABLE__QUAD_DBZ
	ANIMLIB_QUAD_DBZ,
#endif
#if !defined DC_ANIMS_DISABLE__RAPPING
	ANIMLIB_RAPPING,
#endif
#if !defined DC_ANIMS_DISABLE__RIFLE
	ANIMLIB_RIFLE,
#endif
#if !defined DC_ANIMS_DISABLE__RIOT
	ANIMLIB_RIOT,
#endif
#if !defined DC_ANIMS_DISABLE__ROB_BANK
	ANIMLIB_ROB_BANK,
#endif
#if !defined DC_ANIMS_DISABLE__ROCKET
	ANIMLIB_ROCKET,
#endif
#if !defined DC_ANIMS_DISABLE__RUNNINGMAN
	ANIMLIB_RUNNINGMAN,
#endif
#if !defined DC_ANIMS_DISABLE__RUSTLER
	ANIMLIB_RUSTLER,
#endif
#if !defined DC_ANIMS_DISABLE__RYDER
	ANIMLIB_RYDER,
#endif
#if !defined DC_ANIMS_DISABLE__SCRATCHING
	ANIMLIB_SCRATCHING,
#endif
#if !defined DC_ANIMS_DISABLE__SEX
	ANIMLIB_SEX,
#endif
#if !defined DC_ANIMS_DISABLE__SHAMAL
	ANIMLIB_SHAMAL,
#endif
#if !defined DC_ANIMS_DISABLE__SHOP
	ANIMLIB_SHOP,
#endif
#if !defined DC_ANIMS_DISABLE__SHOTGUN
	ANIMLIB_SHOTGUN,
#endif
#if !defined DC_ANIMS_DISABLE__SILENCED
	ANIMLIB_SILENCED,
#endif
#if !defined DC_ANIMS_DISABLE__SKATE
	ANIMLIB_SKATE,
#endif
#if !defined DC_ANIMS_DISABLE__SMOKING
	ANIMLIB_SMOKING,
#endif
#if !defined DC_ANIMS_DISABLE__SNIPER
	ANIMLIB_SNIPER,
#endif
#if !defined DC_ANIMS_DISABLE__SNM
	ANIMLIB_SnM,
#endif
#if !defined DC_ANIMS_DISABLE__SPRAYCAN
	ANIMLIB_SPRAYCAN,
#endif
#if !defined DC_ANIMS_DISABLE__STRIP
	ANIMLIB_STRIP,
#endif
#if !defined DC_ANIMS_DISABLE__SUNBATHE
	ANIMLIB_SUNBATHE,
#endif
#if !defined DC_ANIMS_DISABLE__SWAT
	ANIMLIB_SWAT,
#endif
#if !defined DC_ANIMS_DISABLE__SWEET
	ANIMLIB_SWEET,
#endif
#if !defined DC_ANIMS_DISABLE__SWIM
	ANIMLIB_SWIM,
#endif
#if !defined DC_ANIMS_DISABLE__SWORD
	ANIMLIB_SWORD,
#endif
#if !defined DC_ANIMS_DISABLE__TANK
	ANIMLIB_TANK,
#endif
#if !defined DC_ANIMS_DISABLE__TATTOOS
	ANIMLIB_TATTOOS,
#endif
#if !defined DC_ANIMS_DISABLE__TEC
	ANIMLIB_TEC,
#endif
#if !defined DC_ANIMS_DISABLE__TRAIN
	ANIMLIB_TRAIN,
#endif
#if !defined DC_ANIMS_DISABLE__TRUCK
	ANIMLIB_TRUCK,
#endif
#if !defined DC_ANIMS_DISABLE__UZI
	ANIMLIB_UZI,
#endif
#if !defined DC_ANIMS_DISABLE__VAN
	ANIMLIB_VAN,
#endif
#if !defined DC_ANIMS_DISABLE__VENDING
	ANIMLIB_VENDING,
#endif
#if !defined DC_ANIMS_DISABLE__VORTEX
	ANIMLIB_VORTEX,
#endif
#if !defined DC_ANIMS_DISABLE__WAYFARER
	ANIMLIB_WAYFARER,
#endif
#if !defined DC_ANIMS_DISABLE__WEAPONS
	ANIMLIB_WEAPONS,
#endif
#if !defined DC_ANIMS_DISABLE__WOP
	ANIMLIB_WOP,
#endif
#if !defined DC_ANIMS_DISABLE__WUZI
	ANIMLIB_WUZI,
#endif
#if !defined DC_ANIMS_DISABLE__SAMP
	ANIMLIB_SAMP,
#endif
	DC_ANIMS__LAST_ANIMLIB_ID
};

static const dc_anims__libs[][e_ANIM_LIB_INFO] =
{
#if !defined DC_ANIMS_DISABLE__AIRPORT
	_AnimLib(AIRPORT),
#endif
#if !defined DC_ANIMS_DISABLE__ATTRACTORS
	_AnimLib(Attractors),
#endif
#if !defined DC_ANIMS_DISABLE__BAR
	_AnimLib(BAR),
#endif
#if !defined DC_ANIMS_DISABLE__BASEBALL
	_AnimLib(BASEBALL),
#endif
#if !defined DC_ANIMS_DISABLE__BD_FIRE
	_AnimLib(BD_FIRE),
#endif
#if !defined DC_ANIMS_DISABLE__BEACH
	_AnimLib(BEACH),
#endif
#if !defined DC_ANIMS_DISABLE__BENCHPRESS
	_AnimLib(benchpress),
#endif
#if !defined DC_ANIMS_DISABLE__BF_INJECTION
	_AnimLib(BF_injection),
#endif
#if !defined DC_ANIMS_DISABLE__BIKED
	_AnimLib(BIKED),
#endif
#if !defined DC_ANIMS_DISABLE__BIKEH
	_AnimLib(BIKEH),
#endif
#if !defined DC_ANIMS_DISABLE__BIKELEAP
	_AnimLib(BIKELEAP),
#endif
#if !defined DC_ANIMS_DISABLE__BIKES
	_AnimLib(BIKES),
#endif
#if !defined DC_ANIMS_DISABLE__BIKEV
	_AnimLib(BIKEV),
#endif
#if !defined DC_ANIMS_DISABLE__BIKE_DBZ
	_AnimLib(BIKE_DBZ),
#endif
#if !defined DC_ANIMS_DISABLE__BLOWJOBZ
	_AnimLib(BLOWJOBZ),
#endif
#if !defined DC_ANIMS_DISABLE__BMX
	_AnimLib(BMX),
#endif
#if !defined DC_ANIMS_DISABLE__BOMBER
	_AnimLib(BOMBER),
#endif
#if !defined DC_ANIMS_DISABLE__BOX
	_AnimLib(BOX),
#endif
#if !defined DC_ANIMS_DISABLE__BSKTBALL
	_AnimLib(BSKTBALL),
#endif
#if !defined DC_ANIMS_DISABLE__BUDDY
	_AnimLib(BUDDY),
#endif
#if !defined DC_ANIMS_DISABLE__BUS
	_AnimLib(BUS),
#endif
#if !defined DC_ANIMS_DISABLE__CAMERA
	_AnimLib(CAMERA),
#endif
#if !defined DC_ANIMS_DISABLE__CAR
	_AnimLib(CAR),
#endif
#if !defined DC_ANIMS_DISABLE__CARRY
	_AnimLib(CARRY),
#endif
#if !defined DC_ANIMS_DISABLE__CAR_CHAT
	_AnimLib(CAR_CHAT),
#endif
#if !defined DC_ANIMS_DISABLE__CASINO
	_AnimLib(CASINO),
#endif
#if !defined DC_ANIMS_DISABLE__CHAINSAW
	_AnimLib(CHAINSAW),
#endif
#if !defined DC_ANIMS_DISABLE__CHOPPA
	_AnimLib(CHOPPA),
#endif
#if !defined DC_ANIMS_DISABLE__CLOTHES
	_AnimLib(CLOTHES),
#endif
#if !defined DC_ANIMS_DISABLE__COACH
	_AnimLib(COACH),
#endif
#if !defined DC_ANIMS_DISABLE__COLT45
	_AnimLib(COLT45),
#endif
#if !defined DC_ANIMS_DISABLE__COP_AMBIENT
	_AnimLib(COP_AMBIENT),
#endif
#if !defined DC_ANIMS_DISABLE__COP_DVBYZ
	_AnimLib(COP_DVBYZ),
#endif
#if !defined DC_ANIMS_DISABLE__CRACK
	_AnimLib(CRACK),
#endif
#if !defined DC_ANIMS_DISABLE__CRIB
	_AnimLib(CRIB),
#endif
#if !defined DC_ANIMS_DISABLE__DAM_JUMP
	_AnimLib(DAM_JUMP),
#endif
#if !defined DC_ANIMS_DISABLE__DANCING
	_AnimLib(DANCING),
#endif
#if !defined DC_ANIMS_DISABLE__DEALER
	_AnimLib(DEALER),
#endif
#if !defined DC_ANIMS_DISABLE__DILDO
	_AnimLib(DILDO),
#endif
#if !defined DC_ANIMS_DISABLE__DODGE
	_AnimLib(DODGE),
#endif
#if !defined DC_ANIMS_DISABLE__DOZER
	_AnimLib(DOZER),
#endif
#if !defined DC_ANIMS_DISABLE__DRIVEBYS
	_AnimLib(DRIVEBYS),
#endif
#if !defined DC_ANIMS_DISABLE__FAT
	_AnimLib(FAT),
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_B
	_AnimLib(FIGHT_B),
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_C
	_AnimLib(FIGHT_C),
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_D
	_AnimLib(FIGHT_D),
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_E
	_AnimLib(FIGHT_E),
#endif
#if !defined DC_ANIMS_DISABLE__FINALE
	_AnimLib(FINALE),
#endif
#if !defined DC_ANIMS_DISABLE__FINALE2
	_AnimLib(FINALE2),
#endif
#if !defined DC_ANIMS_DISABLE__FLAME
	_AnimLib(FLAME),
#endif
#if !defined DC_ANIMS_DISABLE__FLOWERS
	_AnimLib(Flowers),
#endif
#if !defined DC_ANIMS_DISABLE__FOOD
	_AnimLib(FOOD),
#endif
#if !defined DC_ANIMS_DISABLE__FREEWEIGHTS
	_AnimLib(Freeweights),
#endif
#if !defined DC_ANIMS_DISABLE__GANGS
	_AnimLib(GANGS),
#endif
#if !defined DC_ANIMS_DISABLE__GFUNK
	_AnimLib(GFUNK),
#endif
#if !defined DC_ANIMS_DISABLE__GHANDS
	_AnimLib(GHANDS),
#endif
#if !defined DC_ANIMS_DISABLE__GHETTO_DB
	_AnimLib(GHETTO_DB),
#endif
#if !defined DC_ANIMS_DISABLE__GOGGLES
	_AnimLib(goggles),
#endif
#if !defined DC_ANIMS_DISABLE__GRAFFITI
	_AnimLib(GRAFFITI),
#endif
#if !defined DC_ANIMS_DISABLE__GRAVEYARD
	_AnimLib(GRAVEYARD),
#endif
#if !defined DC_ANIMS_DISABLE__GRENADE
	_AnimLib(GRENADE),
#endif
#if !defined DC_ANIMS_DISABLE__GYMNASIUM
	_AnimLib(GYMNASIUM),
#endif
#if !defined DC_ANIMS_DISABLE__HAIRCUTS
	_AnimLib(HAIRCUTS),
#endif
#if !defined DC_ANIMS_DISABLE__HEIST9
	_AnimLib(HEIST9),
#endif
#if !defined DC_ANIMS_DISABLE__INT_HOUSE
	_AnimLib(INT_HOUSE),
#endif
#if !defined DC_ANIMS_DISABLE__INT_OFFICE
	_AnimLib(INT_OFFICE),
#endif
#if !defined DC_ANIMS_DISABLE__INT_SHOP
	_AnimLib(INT_SHOP),
#endif
#if !defined DC_ANIMS_DISABLE__JST_BUISNESS
	_AnimLib(JST_BUISNESS),
#endif
#if !defined DC_ANIMS_DISABLE__KART
	_AnimLib(KART),
#endif
#if !defined DC_ANIMS_DISABLE__KISSING
	_AnimLib(KISSING),
#endif
#if !defined DC_ANIMS_DISABLE__KNIFE
	_AnimLib(KNIFE),
#endif
#if !defined DC_ANIMS_DISABLE__LAPDAN1
	_AnimLib(LAPDAN1),
#endif
#if !defined DC_ANIMS_DISABLE__LAPDAN2
	_AnimLib(LAPDAN2),
#endif
#if !defined DC_ANIMS_DISABLE__LAPDAN3
	_AnimLib(LAPDAN3),
#endif
#if !defined DC_ANIMS_DISABLE__LOWRIDER
	_AnimLib(LOWRIDER),
#endif
#if !defined DC_ANIMS_DISABLE__MD_CHASE
	_AnimLib(MD_CHASE),
#endif
#if !defined DC_ANIMS_DISABLE__MD_END
	_AnimLib(MD_END),
#endif
#if !defined DC_ANIMS_DISABLE__MEDIC
	_AnimLib(MEDIC),
#endif
#if !defined DC_ANIMS_DISABLE__MISC
	_AnimLib(MISC),
#endif
#if !defined DC_ANIMS_DISABLE__MTB
	_AnimLib(MTB),
#endif
#if !defined DC_ANIMS_DISABLE__MUSCULAR
	_AnimLib(MUSCULAR),
#endif
#if !defined DC_ANIMS_DISABLE__NEVADA
	_AnimLib(NEVADA),
#endif
#if !defined DC_ANIMS_DISABLE__ON_LOOKERS
	_AnimLib(ON_LOOKERS),
#endif
#if !defined DC_ANIMS_DISABLE__OTB
	_AnimLib(OTB),
#endif
#if !defined DC_ANIMS_DISABLE__PARACHUTE
	_AnimLib(PARACHUTE),
#endif
#if !defined DC_ANIMS_DISABLE__PARK
	_AnimLib(PARK),
#endif
#if !defined DC_ANIMS_DISABLE__PAULNMAC
	_AnimLib(PAULNMAC),
#endif
#if !defined DC_ANIMS_DISABLE__PED
	_AnimLib(ped),
#endif
#if !defined DC_ANIMS_DISABLE__PLAYER_DVBYS
	_AnimLib(PLAYER_DVBYS),
#endif
#if !defined DC_ANIMS_DISABLE__PLAYIDLES
	_AnimLib(PLAYIDLES),
#endif
#if !defined DC_ANIMS_DISABLE__POLICE
	_AnimLib(POLICE),
#endif
#if !defined DC_ANIMS_DISABLE__POOL
	_AnimLib(POOL),
#endif
#if !defined DC_ANIMS_DISABLE__POOR
	_AnimLib(POOR),
#endif
#if !defined DC_ANIMS_DISABLE__PYTHON
	_AnimLib(PYTHON),
#endif
#if !defined DC_ANIMS_DISABLE__QUAD
	_AnimLib(QUAD),
#endif
#if !defined DC_ANIMS_DISABLE__QUAD_DBZ
	_AnimLib(QUAD_DBZ),
#endif
#if !defined DC_ANIMS_DISABLE__RAPPING
	_AnimLib(RAPPING),
#endif
#if !defined DC_ANIMS_DISABLE__RIFLE
	_AnimLib(RIFLE),
#endif
#if !defined DC_ANIMS_DISABLE__RIOT
	_AnimLib(RIOT),
#endif
#if !defined DC_ANIMS_DISABLE__ROB_BANK
	_AnimLib(ROB_BANK),
#endif
#if !defined DC_ANIMS_DISABLE__ROCKET
	_AnimLib(ROCKET),
#endif
#if !defined DC_ANIMS_DISABLE__RUNNINGMAN
	_AnimLib(RUNNINGMAN),
#endif
#if !defined DC_ANIMS_DISABLE__RUSTLER
	_AnimLib(RUSTLER),
#endif
#if !defined DC_ANIMS_DISABLE__RYDER
	_AnimLib(RYDER),
#endif
#if !defined DC_ANIMS_DISABLE__SCRATCHING
	_AnimLib(SCRATCHING),
#endif
#if !defined DC_ANIMS_DISABLE__SEX
	_AnimLib(SEX),
#endif
#if !defined DC_ANIMS_DISABLE__SHAMAL
	_AnimLib(SHAMAL),
#endif
#if !defined DC_ANIMS_DISABLE__SHOP
	_AnimLib(SHOP),
#endif
#if !defined DC_ANIMS_DISABLE__SHOTGUN
	_AnimLib(SHOTGUN),
#endif
#if !defined DC_ANIMS_DISABLE__SILENCED
	_AnimLib(SILENCED),
#endif
#if !defined DC_ANIMS_DISABLE__SKATE
	_AnimLib(SKATE),
#endif
#if !defined DC_ANIMS_DISABLE__SMOKING
	_AnimLib(SMOKING),
#endif
#if !defined DC_ANIMS_DISABLE__SNIPER
	_AnimLib(SNIPER),
#endif
#if !defined DC_ANIMS_DISABLE__SNM
	_AnimLib(SnM),
#endif
#if !defined DC_ANIMS_DISABLE__SPRAYCAN
	_AnimLib(SPRAYCAN),
#endif
#if !defined DC_ANIMS_DISABLE__STRIP
	_AnimLib(STRIP),
#endif
#if !defined DC_ANIMS_DISABLE__SUNBATHE
	_AnimLib(SUNBATHE),
#endif
#if !defined DC_ANIMS_DISABLE__SWAT
	_AnimLib(SWAT),
#endif
#if !defined DC_ANIMS_DISABLE__SWEET
	_AnimLib(SWEET),
#endif
#if !defined DC_ANIMS_DISABLE__SWIM
	_AnimLib(SWIM),
#endif
#if !defined DC_ANIMS_DISABLE__SWORD
	_AnimLib(SWORD),
#endif
#if !defined DC_ANIMS_DISABLE__TANK
	_AnimLib(TANK),
#endif
#if !defined DC_ANIMS_DISABLE__TATTOOS
	_AnimLib(TATTOOS),
#endif
#if !defined DC_ANIMS_DISABLE__TEC
	_AnimLib(TEC),
#endif
#if !defined DC_ANIMS_DISABLE__TRAIN
	_AnimLib(TRAIN),
#endif
#if !defined DC_ANIMS_DISABLE__TRUCK
	_AnimLib(TRUCK),
#endif
#if !defined DC_ANIMS_DISABLE__UZI
	_AnimLib(UZI),
#endif
#if !defined DC_ANIMS_DISABLE__VAN
	_AnimLib(VAN),
#endif
#if !defined DC_ANIMS_DISABLE__VENDING
	_AnimLib(VENDING),
#endif
#if !defined DC_ANIMS_DISABLE__VORTEX
	_AnimLib(VORTEX),
#endif
#if !defined DC_ANIMS_DISABLE__WAYFARER
	_AnimLib(WAYFARER),
#endif
#if !defined DC_ANIMS_DISABLE__WEAPONS
	_AnimLib(WEAPONS),
#endif
#if !defined DC_ANIMS_DISABLE__WOP
	_AnimLib(WOP),
#endif
#if !defined DC_ANIMS_DISABLE__WUZI
	_AnimLib(WUZI),
#endif
#if !defined DC_ANIMS_DISABLE__SAMP
	_AnimLib(SAMP),
#endif
	{{""}, -1, -1}
};

static const dc_anims__info[][e_ANIM_INFO] =
{
#if !defined DC_ANIMS_DISABLE__AIRPORT
// Name: AIRPORT, animations count: 1
	_Anim(AIRPORT, thrw_barl_thrw),
#endif
#if !defined DC_ANIMS_DISABLE__ATTRACTORS
// Name: Attractors, animations count: 3
	_Anim(Attractors, Stepsit_in),
	_Anim(Attractors, Stepsit_loop),
	_Anim(Attractors, Stepsit_out),
#endif
#if !defined DC_ANIMS_DISABLE__BAR
// Name: BAR, animations count: 12
	_Anim(BAR, Barcustom_get),
	_Anim(BAR, Barcustom_loop),
	_Anim(BAR, Barcustom_order),
	_Anim(BAR, BARman_idle),
	_Anim(BAR, Barserve_bottle),
	_Anim(BAR, Barserve_give),
	_Anim(BAR, Barserve_glass),
	_Anim(BAR, Barserve_in),
	_Anim(BAR, Barserve_loop),
	_Anim(BAR, Barserve_order),
	_Anim(BAR, dnk_stndF_loop),
	_Anim(BAR, dnk_stndM_loop),
#endif
#if !defined DC_ANIMS_DISABLE__BASEBALL
// Name: BASEBALL, animations count: 11
	_Anim(BASEBALL, Bat_1),
	_Anim(BASEBALL, Bat_2),
	_Anim(BASEBALL, Bat_3),
	_Anim(BASEBALL, Bat_4),
	_Anim(BASEBALL, Bat_block),
	_Anim(BASEBALL, Bat_Hit_1),
	_Anim(BASEBALL, Bat_Hit_2),
	_Anim(BASEBALL, Bat_Hit_3),
	_Anim(BASEBALL, Bat_IDLE),
	_Anim(BASEBALL, Bat_M),
	_Anim(BASEBALL, BAT_PART),
#endif
#if !defined DC_ANIMS_DISABLE__BD_FIRE
// Name: BD_FIRE, animations count: 13
	_Anim(BD_FIRE, BD_Fire1),
	_Anim(BD_FIRE, BD_Fire2),
	_Anim(BD_FIRE, BD_Fire3),
	_Anim(BD_FIRE, BD_GF_Wave),
	_Anim(BD_FIRE, BD_Panic_01),
	_Anim(BD_FIRE, BD_Panic_02),
	_Anim(BD_FIRE, BD_Panic_03),
	_Anim(BD_FIRE, BD_Panic_04),
	_Anim(BD_FIRE, BD_Panic_Loop),
	_Anim(BD_FIRE, Grlfrd_Kiss_03),
	_Anim(BD_FIRE, M_smklean_loop),
	_Anim(BD_FIRE, Playa_Kiss_03),
	_Anim(BD_FIRE, wash_up),
#endif
#if !defined DC_ANIMS_DISABLE__BEACH
// Name: BEACH, animations count: 5
	_Anim(BEACH, bather),
	_Anim(BEACH, Lay_Bac_Loop),
	_Anim(BEACH, ParkSit_M_loop),
	_Anim(BEACH, ParkSit_W_loop),
	_Anim(BEACH, SitnWait_loop_W),
#endif
#if !defined DC_ANIMS_DISABLE__BENCHPRESS
// Name: benchpress, animations count: 7
	_Anim(benchpress, gym_bp_celebrate),
	_Anim(benchpress, gym_bp_down),
	_Anim(benchpress, gym_bp_getoff),
	_Anim(benchpress, gym_bp_geton),
	_Anim(benchpress, gym_bp_up_A),
	_Anim(benchpress, gym_bp_up_B),
	_Anim(benchpress, gym_bp_up_smooth),
#endif
#if !defined DC_ANIMS_DISABLE__BF_INJECTION
// Name: BF_injection, animations count: 4
	_Anim(BF_injection, BF_getin_LHS),
	_Anim(BF_injection, BF_getin_RHS),
	_Anim(BF_injection, BF_getout_LHS),
	_Anim(BF_injection, BF_getout_RHS),
#endif
#if !defined DC_ANIMS_DISABLE__BIKED
// Name: BIKED, animations count: 19
	_Anim(BIKED, BIKEd_Back),
	_Anim(BIKED, BIKEd_drivebyFT),
	_Anim(BIKED, BIKEd_drivebyLHS),
	_Anim(BIKED, BIKEd_drivebyRHS),
	_Anim(BIKED, BIKEd_Fwd),
	_Anim(BIKED, BIKEd_getoffBACK),
	_Anim(BIKED, BIKEd_getoffLHS),
	_Anim(BIKED, BIKEd_getoffRHS),
	_Anim(BIKED, BIKEd_hit),
	_Anim(BIKED, BIKEd_jumponL),
	_Anim(BIKED, BIKEd_jumponR),
	_Anim(BIKED, BIKEd_kick),
	_Anim(BIKED, BIKEd_Left),
	_Anim(BIKED, BIKEd_passenger),
	_Anim(BIKED, BIKEd_pushes),
	_Anim(BIKED, BIKEd_Ride),
	_Anim(BIKED, BIKEd_Right),
	_Anim(BIKED, BIKEd_shuffle),
	_Anim(BIKED, BIKEd_Still),
#endif
#if !defined DC_ANIMS_DISABLE__BIKEH
// Name: BIKEH, animations count: 18
	_Anim(BIKEH, BIKEh_Back),
	_Anim(BIKEH, BIKEh_drivebyFT),
	_Anim(BIKEH, BIKEh_drivebyLHS),
	_Anim(BIKEH, BIKEh_drivebyRHS),
	_Anim(BIKEH, BIKEh_Fwd),
	_Anim(BIKEH, BIKEh_getoffBACK),
	_Anim(BIKEH, BIKEh_getoffLHS),
	_Anim(BIKEH, BIKEh_getoffRHS),
	_Anim(BIKEH, BIKEh_hit),
	_Anim(BIKEH, BIKEh_jumponL),
	_Anim(BIKEH, BIKEh_jumponR),
	_Anim(BIKEH, BIKEh_kick),
	_Anim(BIKEH, BIKEh_Left),
	_Anim(BIKEH, BIKEh_passenger),
	_Anim(BIKEH, BIKEh_pushes),
	_Anim(BIKEH, BIKEh_Ride),
	_Anim(BIKEH, BIKEh_Right),
	_Anim(BIKEH, BIKEh_Still),
#endif
#if !defined DC_ANIMS_DISABLE__BIKELEAP
// Name: BIKELEAP, animations count: 9
	_Anim(BIKELEAP, bk_blnce_in),
	_Anim(BIKELEAP, bk_blnce_out),
	_Anim(BIKELEAP, bk_jmp),
	_Anim(BIKELEAP, bk_rdy_in),
	_Anim(BIKELEAP, bk_rdy_out),
	_Anim(BIKELEAP, struggle_cesar),
	_Anim(BIKELEAP, struggle_driver),
	_Anim(BIKELEAP, truck_driver),
	_Anim(BIKELEAP, truck_getin),
#endif
#if !defined DC_ANIMS_DISABLE__BIKES
// Name: BIKES, animations count: 20
	_Anim(BIKES, BIKEs_Back),
	_Anim(BIKES, BIKEs_drivebyFT),
	_Anim(BIKES, BIKEs_drivebyLHS),
	_Anim(BIKES, BIKEs_drivebyRHS),
	_Anim(BIKES, BIKEs_Fwd),
	_Anim(BIKES, BIKEs_getoffBACK),
	_Anim(BIKES, BIKEs_getoffLHS),
	_Anim(BIKES, BIKEs_getoffRHS),
	_Anim(BIKES, BIKEs_hit),
	_Anim(BIKES, BIKEs_jumponL),
	_Anim(BIKES, BIKEs_jumponR),
	_Anim(BIKES, BIKEs_kick),
	_Anim(BIKES, BIKEs_Left),
	_Anim(BIKES, BIKEs_passenger),
	_Anim(BIKES, BIKEs_pushes),
	_Anim(BIKES, BIKEs_Ride),
	_Anim(BIKES, BIKEs_Right),
	_Anim(BIKES, BIKEs_Snatch_L),
	_Anim(BIKES, BIKEs_Snatch_R),
	_Anim(BIKES, BIKEs_Still),
#endif
#if !defined DC_ANIMS_DISABLE__BIKEV
// Name: BIKEV, animations count: 18
	_Anim(BIKEV, BIKEv_Back),
	_Anim(BIKEV, BIKEv_drivebyFT),
	_Anim(BIKEV, BIKEv_drivebyLHS),
	_Anim(BIKEV, BIKEv_drivebyRHS),
	_Anim(BIKEV, BIKEv_Fwd),
	_Anim(BIKEV, BIKEv_getoffBACK),
	_Anim(BIKEV, BIKEv_getoffLHS),
	_Anim(BIKEV, BIKEv_getoffRHS),
	_Anim(BIKEV, BIKEv_hit),
	_Anim(BIKEV, BIKEv_jumponL),
	_Anim(BIKEV, BIKEv_jumponR),
	_Anim(BIKEV, BIKEv_kick),
	_Anim(BIKEV, BIKEv_Left),
	_Anim(BIKEV, BIKEv_passenger),
	_Anim(BIKEV, BIKEv_pushes),
	_Anim(BIKEV, BIKEv_Ride),
	_Anim(BIKEV, BIKEv_Right),
	_Anim(BIKEV, BIKEv_Still),
#endif
#if !defined DC_ANIMS_DISABLE__BIKE_DBZ
// Name: BIKE_DBZ, animations count: 4
	_Anim(BIKE_DBZ, Pass_Driveby_BWD),
	_Anim(BIKE_DBZ, Pass_Driveby_FWD),
	_Anim(BIKE_DBZ, Pass_Driveby_LHS),
	_Anim(BIKE_DBZ, Pass_Driveby_RHS),
#endif
#if !defined DC_ANIMS_DISABLE__BLOWJOBZ
// Name: BLOWJOBZ, animations count: 18
	_Anim(BLOWJOBZ, BJ_Car_End_P),
	_Anim(BLOWJOBZ, BJ_Car_End_W),
	_Anim(BLOWJOBZ, BJ_Car_Loop_P),
	_Anim(BLOWJOBZ, BJ_Car_Loop_W),
	_Anim(BLOWJOBZ, BJ_Car_Start_P),
	_Anim(BLOWJOBZ, BJ_Car_Start_W),
	_Anim(BLOWJOBZ, BJ_Couch_End_P),
	_Anim(BLOWJOBZ, BJ_Couch_End_W),
	_Anim(BLOWJOBZ, BJ_Couch_Loop_P),
	_Anim(BLOWJOBZ, BJ_Couch_Loop_W),
	_Anim(BLOWJOBZ, BJ_Couch_Start_P),
	_Anim(BLOWJOBZ, BJ_Couch_Start_W),
	_Anim(BLOWJOBZ, BJ_Stand_End_P),
	_Anim(BLOWJOBZ, BJ_Stand_End_W),
	_Anim(BLOWJOBZ, BJ_Stand_Loop_P),
	_Anim(BLOWJOBZ, BJ_Stand_Loop_W),
	_Anim(BLOWJOBZ, BJ_Stand_Start_P),
	_Anim(BLOWJOBZ, BJ_Stand_Start_W),
#endif
#if !defined DC_ANIMS_DISABLE__BMX
// Name: BMX, animations count: 18
	_Anim(BMX, BMX_back),
	_Anim(BMX, BMX_bunnyhop),
	_Anim(BMX, BMX_drivebyFT),
	_Anim(BMX, BMX_driveby_LHS),
	_Anim(BMX, BMX_driveby_RHS),
	_Anim(BMX, BMX_fwd),
	_Anim(BMX, BMX_getoffBACK),
	_Anim(BMX, BMX_getoffLHS),
	_Anim(BMX, BMX_getoffRHS),
	_Anim(BMX, BMX_jumponL),
	_Anim(BMX, BMX_jumponR),
	_Anim(BMX, BMX_Left),
	_Anim(BMX, BMX_pedal),
	_Anim(BMX, BMX_pushes),
	_Anim(BMX, BMX_Ride),
	_Anim(BMX, BMX_Right),
	_Anim(BMX, BMX_sprint),
	_Anim(BMX, BMX_still),
#endif
#if !defined DC_ANIMS_DISABLE__BOMBER
// Name: BOMBER, animations count: 6
	_Anim(BOMBER, BOM_Plant),
	_Anim(BOMBER, BOM_Plant_2Idle),
	_Anim(BOMBER, BOM_Plant_Crouch_In),
	_Anim(BOMBER, BOM_Plant_Crouch_Out),
	_Anim(BOMBER, BOM_Plant_In),
	_Anim(BOMBER, BOM_Plant_Loop),
#endif
#if !defined DC_ANIMS_DISABLE__BOX
// Name: BOX, animations count: 10
	_Anim(BOX, boxhipin),
	_Anim(BOX, boxhipup),
	_Anim(BOX, boxshdwn),
	_Anim(BOX, boxshup),
	_Anim(BOX, bxhipwlk),
	_Anim(BOX, bxhwlki),
	_Anim(BOX, bxshwlk),
	_Anim(BOX, bxshwlki),
	_Anim(BOX, bxwlko),
	_Anim(BOX, catch_box),
#endif
#if !defined DC_ANIMS_DISABLE__BSKTBALL
// Name: BSKTBALL, animations count: 41
	_Anim(BSKTBALL, BBALL_def_jump_shot),
	_Anim(BSKTBALL, BBALL_def_loop),
	_Anim(BSKTBALL, BBALL_def_stepL),
	_Anim(BSKTBALL, BBALL_def_stepR),
	_Anim(BSKTBALL, BBALL_Dnk),
	_Anim(BSKTBALL, BBALL_Dnk_Gli),
	_Anim(BSKTBALL, BBALL_Dnk_Gli_O),
	_Anim(BSKTBALL, BBALL_Dnk_Lnch),
	_Anim(BSKTBALL, BBALL_Dnk_Lnch_O),
	_Anim(BSKTBALL, BBALL_Dnk_Lnd),
	_Anim(BSKTBALL, BBALL_Dnk_O),
	_Anim(BSKTBALL, BBALL_idle),
	_Anim(BSKTBALL, BBALL_idle2),
	_Anim(BSKTBALL, BBALL_idle2_O),
	_Anim(BSKTBALL, BBALL_idleloop),
	_Anim(BSKTBALL, BBALL_idleloop_O),
	_Anim(BSKTBALL, BBALL_idle_O),
	_Anim(BSKTBALL, BBALL_Jump_Cancel),
	_Anim(BSKTBALL, BBALL_Jump_Cancel_O),
	_Anim(BSKTBALL, BBALL_Jump_End),
	_Anim(BSKTBALL, BBALL_Jump_Shot),
	_Anim(BSKTBALL, BBALL_Jump_Shot_O),
	_Anim(BSKTBALL, BBALL_Net_Dnk_O),
	_Anim(BSKTBALL, BBALL_pickup),
	_Anim(BSKTBALL, BBALL_pickup_O),
	_Anim(BSKTBALL, BBALL_react_miss),
	_Anim(BSKTBALL, BBALL_react_score),
	_Anim(BSKTBALL, BBALL_run),
	_Anim(BSKTBALL, BBALL_run_O),
	_Anim(BSKTBALL, BBALL_SkidStop_L),
	_Anim(BSKTBALL, BBALL_SkidStop_L_O),
	_Anim(BSKTBALL, BBALL_SkidStop_R),
	_Anim(BSKTBALL, BBALL_SkidStop_R_O),
	_Anim(BSKTBALL, BBALL_walk),
	_Anim(BSKTBALL, BBALL_WalkStop_L),
	_Anim(BSKTBALL, BBALL_WalkStop_L_O),
	_Anim(BSKTBALL, BBALL_WalkStop_R),
	_Anim(BSKTBALL, BBALL_WalkStop_R_O),
	_Anim(BSKTBALL, BBALL_walk_O),
	_Anim(BSKTBALL, BBALL_walk_start),
	_Anim(BSKTBALL, BBALL_walk_start_O),
#endif
#if !defined DC_ANIMS_DISABLE__BUDDY
// Name: BUDDY, animations count: 5
	_Anim(BUDDY, buddy_crouchfire),
	_Anim(BUDDY, buddy_crouchreload),
	_Anim(BUDDY, buddy_fire),
	_Anim(BUDDY, buddy_fire_poor),
	_Anim(BUDDY, buddy_reload),
#endif
#if !defined DC_ANIMS_DISABLE__BUS
// Name: BUS, animations count: 9
	_Anim(BUS, BUS_close),
	_Anim(BUS, BUS_getin_LHS),
	_Anim(BUS, BUS_getin_RHS),
	_Anim(BUS, BUS_getout_LHS),
	_Anim(BUS, BUS_getout_RHS),
	_Anim(BUS, BUS_jacked_LHS),
	_Anim(BUS, BUS_open),
	_Anim(BUS, BUS_open_RHS),
	_Anim(BUS, BUS_pullout_LHS),
#endif
#if !defined DC_ANIMS_DISABLE__CAMERA
// Name: CAMERA, animations count: 14
	_Anim(CAMERA, camcrch_cmon),
	_Anim(CAMERA, camcrch_idleloop),
	_Anim(CAMERA, camcrch_stay),
	_Anim(CAMERA, camcrch_to_camstnd),
	_Anim(CAMERA, camstnd_cmon),
	_Anim(CAMERA, camstnd_idleloop),
	_Anim(CAMERA, camstnd_lkabt),
	_Anim(CAMERA, camstnd_to_camcrch),
	_Anim(CAMERA, piccrch_in),
	_Anim(CAMERA, piccrch_out),
	_Anim(CAMERA, piccrch_take),
	_Anim(CAMERA, picstnd_in),
	_Anim(CAMERA, picstnd_out),
	_Anim(CAMERA, picstnd_take),
#endif
#if !defined DC_ANIMS_DISABLE__CAR
// Name: CAR, animations count: 11
	_Anim(CAR, Fixn_Car_Loop),
	_Anim(CAR, Fixn_Car_Out),
	_Anim(CAR, flag_drop),
	_Anim(CAR, Sit_relaxed),
	_Anim(CAR, Tap_hand),
	_Anim(CAR, Tyd2car_bump),
	_Anim(CAR, Tyd2car_high),
	_Anim(CAR, Tyd2car_low),
	_Anim(CAR, Tyd2car_med),
	_Anim(CAR, Tyd2car_TurnL),
	_Anim(CAR, Tyd2car_TurnR),
#endif
#if !defined DC_ANIMS_DISABLE__CARRY
// Name: CARRY, animations count: 7
	_Anim(CARRY, crry_prtial),
	_Anim(CARRY, liftup),
	_Anim(CARRY, liftup05),
	_Anim(CARRY, liftup105),
	_Anim(CARRY, putdwn),
	_Anim(CARRY, putdwn05),
	_Anim(CARRY, putdwn105),
#endif
#if !defined DC_ANIMS_DISABLE__CAR_CHAT
// Name: CAR_CHAT, animations count: 21
	_Anim(CAR_CHAT, carfone_in),
	_Anim(CAR_CHAT, carfone_loopA),
	_Anim(CAR_CHAT, carfone_loopA_to_B),
	_Anim(CAR_CHAT, carfone_loopB),
	_Anim(CAR_CHAT, carfone_loopB_to_A),
	_Anim(CAR_CHAT, carfone_out),
	_Anim(CAR_CHAT, CAR_Sc1_BL),
	_Anim(CAR_CHAT, CAR_Sc1_BR),
	_Anim(CAR_CHAT, CAR_Sc1_FL),
	_Anim(CAR_CHAT, CAR_Sc1_FR),
	_Anim(CAR_CHAT, CAR_Sc2_FL),
	_Anim(CAR_CHAT, CAR_Sc3_BR),
	_Anim(CAR_CHAT, CAR_Sc3_FL),
	_Anim(CAR_CHAT, CAR_Sc3_FR),
	_Anim(CAR_CHAT, CAR_Sc4_BL),
	_Anim(CAR_CHAT, CAR_Sc4_BR),
	_Anim(CAR_CHAT, CAR_Sc4_FL),
	_Anim(CAR_CHAT, CAR_Sc4_FR),
	_Anim(CAR_CHAT, car_talkm_in),
	_Anim(CAR_CHAT, car_talkm_loop),
	_Anim(CAR_CHAT, car_talkm_out),
#endif
#if !defined DC_ANIMS_DISABLE__CASINO
// Name: CASINO, animations count: 25
	_Anim(CASINO, cards_in),
	_Anim(CASINO, cards_loop),
	_Anim(CASINO, cards_lose),
	_Anim(CASINO, cards_out),
	_Anim(CASINO, cards_pick_01),
	_Anim(CASINO, cards_pick_02),
	_Anim(CASINO, cards_raise),
	_Anim(CASINO, cards_win),
	_Anim(CASINO, dealone),
	_Anim(CASINO, manwinb),
	_Anim(CASINO, manwind),
	_Anim(CASINO, Roulette_bet),
	_Anim(CASINO, Roulette_in),
	_Anim(CASINO, Roulette_loop),
	_Anim(CASINO, Roulette_lose),
	_Anim(CASINO, Roulette_out),
	_Anim(CASINO, Roulette_win),
	_Anim(CASINO, Slot_bet_01),
	_Anim(CASINO, Slot_bet_02),
	_Anim(CASINO, Slot_in),
	_Anim(CASINO, Slot_lose_out),
	_Anim(CASINO, Slot_Plyr),
	_Anim(CASINO, Slot_wait),
	_Anim(CASINO, Slot_win_out),
	_Anim(CASINO, wof),
#endif
#if !defined DC_ANIMS_DISABLE__CHAINSAW
// Name: CHAINSAW, animations count: 11
	_Anim(CHAINSAW, CSAW_1),
	_Anim(CHAINSAW, CSAW_2),
	_Anim(CHAINSAW, CSAW_3),
	_Anim(CHAINSAW, CSAW_G),
	_Anim(CHAINSAW, CSAW_Hit_1),
	_Anim(CHAINSAW, CSAW_Hit_2),
	_Anim(CHAINSAW, CSAW_Hit_3),
	_Anim(CHAINSAW, csaw_part),
	_Anim(CHAINSAW, IDLE_csaw),
	_Anim(CHAINSAW, WEAPON_csaw),
	_Anim(CHAINSAW, WEAPON_csawlo),
#endif
#if !defined DC_ANIMS_DISABLE__CHOPPA
// Name: CHOPPA, animations count: 18
	_Anim(CHOPPA, CHOPPA_back),
	_Anim(CHOPPA, CHOPPA_bunnyhop),
	_Anim(CHOPPA, CHOPPA_drivebyFT),
	_Anim(CHOPPA, CHOPPA_driveby_LHS),
	_Anim(CHOPPA, CHOPPA_driveby_RHS),
	_Anim(CHOPPA, CHOPPA_fwd),
	_Anim(CHOPPA, CHOPPA_getoffBACK),
	_Anim(CHOPPA, CHOPPA_getoffLHS),
	_Anim(CHOPPA, CHOPPA_getoffRHS),
	_Anim(CHOPPA, CHOPPA_jumponL),
	_Anim(CHOPPA, CHOPPA_jumponR),
	_Anim(CHOPPA, CHOPPA_Left),
	_Anim(CHOPPA, CHOPPA_pedal),
	_Anim(CHOPPA, CHOPPA_Pushes),
	_Anim(CHOPPA, CHOPPA_ride),
	_Anim(CHOPPA, CHOPPA_Right),
	_Anim(CHOPPA, CHOPPA_sprint),
	_Anim(CHOPPA, CHOPPA_Still),
#endif
#if !defined DC_ANIMS_DISABLE__CLOTHES
// Name: CLOTHES, animations count: 13
	_Anim(CLOTHES, CLO_Buy),
	_Anim(CLOTHES, CLO_In),
	_Anim(CLOTHES, CLO_Out),
	_Anim(CLOTHES, CLO_Pose_Hat),
	_Anim(CLOTHES, CLO_Pose_In),
	_Anim(CLOTHES, CLO_Pose_In_O),
	_Anim(CLOTHES, CLO_Pose_Legs),
	_Anim(CLOTHES, CLO_Pose_Loop),
	_Anim(CLOTHES, CLO_Pose_Out),
	_Anim(CLOTHES, CLO_Pose_Out_O),
	_Anim(CLOTHES, CLO_Pose_Shoes),
	_Anim(CLOTHES, CLO_Pose_Torso),
	_Anim(CLOTHES, CLO_Pose_Watch),
#endif
#if !defined DC_ANIMS_DISABLE__COACH
// Name: COACH, animations count: 6
	_Anim(COACH, COACH_inL),
	_Anim(COACH, COACH_inR),
	_Anim(COACH, COACH_opnL),
	_Anim(COACH, COACH_opnR),
	_Anim(COACH, COACH_outL),
	_Anim(COACH, COACH_outR),
#endif
#if !defined DC_ANIMS_DISABLE__COLT45
// Name: COLT45, animations count: 7
	_Anim(COLT45, 2guns_crouchfire),
	_Anim(COLT45, colt45_crouchfire),
	_Anim(COLT45, colt45_crouchreload),
	_Anim(COLT45, colt45_fire),
	_Anim(COLT45, colt45_fire_2hands),
	_Anim(COLT45, colt45_reload),
	_Anim(COLT45, sawnoff_reload),
#endif
#if !defined DC_ANIMS_DISABLE__COP_AMBIENT
// Name: COP_AMBIENT, animations count: 12
	_Anim(COP_AMBIENT, Copbrowse_in),
	_Anim(COP_AMBIENT, Copbrowse_loop),
	_Anim(COP_AMBIENT, Copbrowse_nod),
	_Anim(COP_AMBIENT, Copbrowse_out),
	_Anim(COP_AMBIENT, Copbrowse_shake),
	_Anim(COP_AMBIENT, Coplook_in),
	_Anim(COP_AMBIENT, Coplook_loop),
	_Anim(COP_AMBIENT, Coplook_nod),
	_Anim(COP_AMBIENT, Coplook_out),
	_Anim(COP_AMBIENT, Coplook_shake),
	_Anim(COP_AMBIENT, Coplook_think),
	_Anim(COP_AMBIENT, Coplook_watch),
#endif
#if !defined DC_ANIMS_DISABLE__COP_DVBYZ
// Name: COP_DVBYZ, animations count: 4
	_Anim(COP_DVBYZ, COP_Dvby_B),
	_Anim(COP_DVBYZ, COP_Dvby_FT),
	_Anim(COP_DVBYZ, COP_Dvby_L),
	_Anim(COP_DVBYZ, COP_Dvby_R),
#endif
#if !defined DC_ANIMS_DISABLE__CRACK
// Name: CRACK, animations count: 10
	_Anim(CRACK, Bbalbat_Idle_01),
	_Anim(CRACK, Bbalbat_Idle_02),
	_Anim(CRACK, crckdeth1),
	_Anim(CRACK, crckdeth2),
	_Anim(CRACK, crckdeth3),
	_Anim(CRACK, crckdeth4),
	_Anim(CRACK, crckidle1),
	_Anim(CRACK, crckidle2),
	_Anim(CRACK, crckidle3),
	_Anim(CRACK, crckidle4),
#endif
#if !defined DC_ANIMS_DISABLE__CRIB
// Name: CRIB, animations count: 5
	_Anim(CRIB, CRIB_Console_Loop),
	_Anim(CRIB, CRIB_Use_Switch),
	_Anim(CRIB, PED_Console_Loop),
	_Anim(CRIB, PED_Console_Loose),
	_Anim(CRIB, PED_Console_Win),
#endif
#if !defined DC_ANIMS_DISABLE__DAM_JUMP
// Name: DAM_JUMP, animations count: 5
	_Anim(DAM_JUMP, DAM_Dive_Loop),
	_Anim(DAM_JUMP, DAM_Land),
	_Anim(DAM_JUMP, DAM_Launch),
	_Anim(DAM_JUMP, Jump_Roll),
	_Anim(DAM_JUMP, SF_JumpWall),
#endif
#if !defined DC_ANIMS_DISABLE__DANCING
// Name: DANCING, animations count: 13
	_Anim(DANCING, bd_clap),
	_Anim(DANCING, bd_clap1),
	_Anim(DANCING, dance_loop),
	_Anim(DANCING, DAN_Down_A),
	_Anim(DANCING, DAN_Left_A),
	_Anim(DANCING, DAN_Loop_A),
	_Anim(DANCING, DAN_Right_A),
	_Anim(DANCING, DAN_Up_A),
	_Anim(DANCING, dnce_M_a),
	_Anim(DANCING, dnce_M_b),
	_Anim(DANCING, dnce_M_c),
	_Anim(DANCING, dnce_M_d),
	_Anim(DANCING, dnce_M_e),
#endif
#if !defined DC_ANIMS_DISABLE__DEALER
// Name: DEALER, animations count: 7
	_Anim(DEALER, DEALER_DEAL),
	_Anim(DEALER, DEALER_IDLE),
	_Anim(DEALER, DEALER_IDLE_01),
	_Anim(DEALER, DEALER_IDLE_02),
	_Anim(DEALER, DEALER_IDLE_03),
	_Anim(DEALER, DRUGS_BUY),
	_Anim(DEALER, shop_pay),
#endif
#if !defined DC_ANIMS_DISABLE__DILDO
// Name: DILDO, animations count: 9
	_Anim(DILDO, DILDO_1),
	_Anim(DILDO, DILDO_2),
	_Anim(DILDO, DILDO_3),
	_Anim(DILDO, DILDO_block),
	_Anim(DILDO, DILDO_G),
	_Anim(DILDO, DILDO_Hit_1),
	_Anim(DILDO, DILDO_Hit_2),
	_Anim(DILDO, DILDO_Hit_3),
	_Anim(DILDO, DILDO_IDLE),
#endif
#if !defined DC_ANIMS_DISABLE__DODGE
// Name: DODGE, animations count: 4
	_Anim(DODGE, Cover_Dive_01),
	_Anim(DODGE, Cover_Dive_02),
	_Anim(DODGE, Crushed),
	_Anim(DODGE, Crush_Jump),
#endif
#if !defined DC_ANIMS_DISABLE__DOZER
// Name: DOZER, animations count: 10
	_Anim(DOZER, DOZER_Align_LHS),
	_Anim(DOZER, DOZER_Align_RHS),
	_Anim(DOZER, DOZER_getin_LHS),
	_Anim(DOZER, DOZER_getin_RHS),
	_Anim(DOZER, DOZER_getout_LHS),
	_Anim(DOZER, DOZER_getout_RHS),
	_Anim(DOZER, DOZER_Jacked_LHS),
	_Anim(DOZER, DOZER_Jacked_RHS),
	_Anim(DOZER, DOZER_pullout_LHS),
	_Anim(DOZER, DOZER_pullout_RHS),
#endif
#if !defined DC_ANIMS_DISABLE__DRIVEBYS
// Name: DRIVEBYS, animations count: 8
	_Anim(DRIVEBYS, Gang_DrivebyLHS),
	_Anim(DRIVEBYS, Gang_DrivebyLHS_Bwd),
	_Anim(DRIVEBYS, Gang_DrivebyLHS_Fwd),
	_Anim(DRIVEBYS, Gang_DrivebyRHS),
	_Anim(DRIVEBYS, Gang_DrivebyRHS_Bwd),
	_Anim(DRIVEBYS, Gang_DrivebyRHS_Fwd),
	_Anim(DRIVEBYS, Gang_DrivebyTop_LHS),
	_Anim(DRIVEBYS, Gang_DrivebyTop_RHS),
#endif
#if !defined DC_ANIMS_DISABLE__FAT
// Name: FAT, animations count: 18
	_Anim(FAT, FatIdle),
	_Anim(FAT, FatIdle_armed),
	_Anim(FAT, FatIdle_Csaw),
	_Anim(FAT, FatIdle_Rocket),
	_Anim(FAT, FatRun),
	_Anim(FAT, FatRun_armed),
	_Anim(FAT, FatRun_Csaw),
	_Anim(FAT, FatRun_Rocket),
	_Anim(FAT, FatSprint),
	_Anim(FAT, FatWalk),
	_Anim(FAT, FatWalkstart),
	_Anim(FAT, FatWalkstart_Csaw),
	_Anim(FAT, FatWalkSt_armed),
	_Anim(FAT, FatWalkSt_Rocket),
	_Anim(FAT, FatWalk_armed),
	_Anim(FAT, FatWalk_Csaw),
	_Anim(FAT, FatWalk_Rocket),
	_Anim(FAT, IDLE_tired),
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_B
// Name: FIGHT_B, animations count: 10
	_Anim(FIGHT_B, FightB_1),
	_Anim(FIGHT_B, FightB_2),
	_Anim(FIGHT_B, FightB_3),
	_Anim(FIGHT_B, FightB_block),
	_Anim(FIGHT_B, FightB_G),
	_Anim(FIGHT_B, FightB_IDLE),
	_Anim(FIGHT_B, FightB_M),
	_Anim(FIGHT_B, HitB_1),
	_Anim(FIGHT_B, HitB_2),
	_Anim(FIGHT_B, HitB_3),
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_C
// Name: FIGHT_C, animations count: 12
	_Anim(FIGHT_C, FightC_1),
	_Anim(FIGHT_C, FightC_2),
	_Anim(FIGHT_C, FightC_3),
	_Anim(FIGHT_C, FightC_block),
	_Anim(FIGHT_C, FightC_blocking),
	_Anim(FIGHT_C, FightC_G),
	_Anim(FIGHT_C, FightC_IDLE),
	_Anim(FIGHT_C, FightC_M),
	_Anim(FIGHT_C, FightC_Spar),
	_Anim(FIGHT_C, HitC_1),
	_Anim(FIGHT_C, HitC_2),
	_Anim(FIGHT_C, HitC_3),
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_D
// Name: FIGHT_D, animations count: 10
	_Anim(FIGHT_D, FightD_1),
	_Anim(FIGHT_D, FightD_2),
	_Anim(FIGHT_D, FightD_3),
	_Anim(FIGHT_D, FightD_block),
	_Anim(FIGHT_D, FightD_G),
	_Anim(FIGHT_D, FightD_IDLE),
	_Anim(FIGHT_D, FightD_M),
	_Anim(FIGHT_D, HitD_1),
	_Anim(FIGHT_D, HitD_2),
	_Anim(FIGHT_D, HitD_3),
#endif
#if !defined DC_ANIMS_DISABLE__FIGHT_E
// Name: FIGHT_E, animations count: 4
	_Anim(FIGHT_E, FightKick),
	_Anim(FIGHT_E, FightKick_B),
	_Anim(FIGHT_E, Hit_fightkick),
	_Anim(FIGHT_E, Hit_fightkick_B),
#endif
#if !defined DC_ANIMS_DISABLE__FINALE
// Name: FINALE, animations count: 16
	_Anim(FINALE, FIN_Climb_In),
	_Anim(FINALE, FIN_Cop1_ClimbOut2),
	_Anim(FINALE, FIN_Cop1_Loop),
	_Anim(FINALE, FIN_Cop1_Stomp),
	_Anim(FINALE, FIN_Hang_L),
	_Anim(FINALE, FIN_Hang_Loop),
	_Anim(FINALE, FIN_Hang_R),
	_Anim(FINALE, FIN_Hang_Slip),
	_Anim(FINALE, FIN_Jump_On),
	_Anim(FINALE, FIN_Land_Car),
	_Anim(FINALE, FIN_Land_Die),
	_Anim(FINALE, FIN_LegsUp),
	_Anim(FINALE, FIN_LegsUp_L),
	_Anim(FINALE, FIN_LegsUp_Loop),
	_Anim(FINALE, FIN_LegsUp_R),
	_Anim(FINALE, FIN_Let_Go),
#endif
#if !defined DC_ANIMS_DISABLE__FINALE2
// Name: FINALE2, animations count: 8
	_Anim(FINALE2, FIN_Cop1_ClimbOut),
	_Anim(FINALE2, FIN_Cop1_Fall),
	_Anim(FINALE2, FIN_Cop1_Loop),
	_Anim(FINALE2, FIN_Cop1_Shot),
	_Anim(FINALE2, FIN_Cop1_Swing),
	_Anim(FINALE2, FIN_Cop2_ClimbOut),
	_Anim(FINALE2, FIN_Switch_P),
	_Anim(FINALE2, FIN_Switch_S),
#endif
#if !defined DC_ANIMS_DISABLE__FLAME
// Name: FLAME, animations count: 1
	_Anim(FLAME, FLAME_fire),
#endif
#if !defined DC_ANIMS_DISABLE__FLOWERS
// Name: Flowers, animations count: 3
	_Anim(Flowers, Flower_attack),
	_Anim(Flowers, Flower_attack_M),
	_Anim(Flowers, Flower_Hit),
#endif
#if !defined DC_ANIMS_DISABLE__FOOD
// Name: FOOD, animations count: 33
	_Anim(FOOD, EAT_Burger),
	_Anim(FOOD, EAT_Chicken),
	_Anim(FOOD, EAT_Pizza),
	_Anim(FOOD, EAT_Vomit_P),
	_Anim(FOOD, EAT_Vomit_SK),
	_Anim(FOOD, FF_Dam_Bkw),
	_Anim(FOOD, FF_Dam_Fwd),
	_Anim(FOOD, FF_Dam_Left),
	_Anim(FOOD, FF_Dam_Right),
	_Anim(FOOD, FF_Die_Bkw),
	_Anim(FOOD, FF_Die_Fwd),
	_Anim(FOOD, FF_Die_Left),
	_Anim(FOOD, FF_Die_Right),
	_Anim(FOOD, FF_Sit_Eat1),
	_Anim(FOOD, FF_Sit_Eat2),
	_Anim(FOOD, FF_Sit_Eat3),
	_Anim(FOOD, FF_Sit_In),
	_Anim(FOOD, FF_Sit_In_L),
	_Anim(FOOD, FF_Sit_In_R),
	_Anim(FOOD, FF_Sit_Look),
	_Anim(FOOD, FF_Sit_Loop),
	_Anim(FOOD, FF_Sit_Out_180),
	_Anim(FOOD, FF_Sit_Out_L_180),
	_Anim(FOOD, FF_Sit_Out_R_180),
	_Anim(FOOD, SHP_Thank),
	_Anim(FOOD, SHP_Tray_In),
	_Anim(FOOD, SHP_Tray_Lift),
	_Anim(FOOD, SHP_Tray_Lift_In),
	_Anim(FOOD, SHP_Tray_Lift_Loop),
	_Anim(FOOD, SHP_Tray_Lift_Out),
	_Anim(FOOD, SHP_Tray_Out),
	_Anim(FOOD, SHP_Tray_Pose),
	_Anim(FOOD, SHP_Tray_Return),
#endif
#if !defined DC_ANIMS_DISABLE__FREEWEIGHTS
// Name: Freeweights, animations count: 9
	_Anim(Freeweights, gym_barbell),
	_Anim(Freeweights, gym_free_A),
	_Anim(Freeweights, gym_free_B),
	_Anim(Freeweights, gym_free_celebrate),
	_Anim(Freeweights, gym_free_down),
	_Anim(Freeweights, gym_free_loop),
	_Anim(Freeweights, gym_free_pickup),
	_Anim(Freeweights, gym_free_putdown),
	_Anim(Freeweights, gym_free_up_smooth),
#endif
#if !defined DC_ANIMS_DISABLE__GANGS
// Name: GANGS, animations count: 33
	_Anim(GANGS, DEALER_DEAL),
	_Anim(GANGS, DEALER_IDLE),
	_Anim(GANGS, drnkbr_prtl),
	_Anim(GANGS, drnkbr_prtl_F),
	_Anim(GANGS, DRUGS_BUY),
	_Anim(GANGS, hndshkaa),
	_Anim(GANGS, hndshkba),
	_Anim(GANGS, hndshkca),
	_Anim(GANGS, hndshkcb),
	_Anim(GANGS, hndshkda),
	_Anim(GANGS, hndshkea),
	_Anim(GANGS, hndshkfa),
	_Anim(GANGS, hndshkfa_swt),
	_Anim(GANGS, Invite_No),
	_Anim(GANGS, Invite_Yes),
	_Anim(GANGS, leanIDLE),
	_Anim(GANGS, leanIN),
	_Anim(GANGS, leanOUT),
	_Anim(GANGS, prtial_gngtlkA),
	_Anim(GANGS, prtial_gngtlkB),
	_Anim(GANGS, prtial_gngtlkC),
	_Anim(GANGS, prtial_gngtlkD),
	_Anim(GANGS, prtial_gngtlkE),
	_Anim(GANGS, prtial_gngtlkF),
	_Anim(GANGS, prtial_gngtlkG),
	_Anim(GANGS, prtial_gngtlkH),
	_Anim(GANGS, prtial_hndshk_01),
	_Anim(GANGS, prtial_hndshk_biz_01),
	_Anim(GANGS, shake_cara),
	_Anim(GANGS, shake_carK),
	_Anim(GANGS, shake_carSH),
	_Anim(GANGS, smkcig_prtl),
	_Anim(GANGS, smkcig_prtl_F),
#endif
#if !defined DC_ANIMS_DISABLE__GFUNK
// Name: GFUNK, animations count: 33
	_Anim(GFUNK, Dance_B1),
	_Anim(GFUNK, Dance_B10),
	_Anim(GFUNK, Dance_B11),
	_Anim(GFUNK, Dance_B12),
	_Anim(GFUNK, Dance_B13),
	_Anim(GFUNK, Dance_B14),
	_Anim(GFUNK, Dance_B15),
	_Anim(GFUNK, Dance_B16),
	_Anim(GFUNK, Dance_B2),
	_Anim(GFUNK, Dance_B3),
	_Anim(GFUNK, Dance_B4),
	_Anim(GFUNK, Dance_B5),
	_Anim(GFUNK, Dance_B6),
	_Anim(GFUNK, Dance_B7),
	_Anim(GFUNK, Dance_B8),
	_Anim(GFUNK, Dance_B9),
	_Anim(GFUNK, Dance_G1),
	_Anim(GFUNK, Dance_G10),
	_Anim(GFUNK, Dance_G11),
	_Anim(GFUNK, Dance_G12),
	_Anim(GFUNK, Dance_G13),
	_Anim(GFUNK, Dance_G14),
	_Anim(GFUNK, Dance_G15),
	_Anim(GFUNK, Dance_G16),
	_Anim(GFUNK, Dance_G2),
	_Anim(GFUNK, Dance_G3),
	_Anim(GFUNK, Dance_G4),
	_Anim(GFUNK, Dance_G5),
	_Anim(GFUNK, Dance_G6),
	_Anim(GFUNK, Dance_G7),
	_Anim(GFUNK, Dance_G8),
	_Anim(GFUNK, Dance_G9),
	_Anim(GFUNK, dance_loop),
#endif
#if !defined DC_ANIMS_DISABLE__GHANDS
// Name: GHANDS, animations count: 20
	_Anim(GHANDS, gsign1),
	_Anim(GHANDS, gsign1LH),
	_Anim(GHANDS, gsign2),
	_Anim(GHANDS, gsign2LH),
	_Anim(GHANDS, gsign3),
	_Anim(GHANDS, gsign3LH),
	_Anim(GHANDS, gsign4),
	_Anim(GHANDS, gsign4LH),
	_Anim(GHANDS, gsign5),
	_Anim(GHANDS, gsign5LH),
	_Anim(GHANDS, LHGsign1),
	_Anim(GHANDS, LHGsign2),
	_Anim(GHANDS, LHGsign3),
	_Anim(GHANDS, LHGsign4),
	_Anim(GHANDS, LHGsign5),
	_Anim(GHANDS, RHGsign1),
	_Anim(GHANDS, RHGsign2),
	_Anim(GHANDS, RHGsign3),
	_Anim(GHANDS, RHGsign4),
	_Anim(GHANDS, RHGsign5),
#endif
#if !defined DC_ANIMS_DISABLE__GHETTO_DB
// Name: GHETTO_DB, animations count: 7
	_Anim(GHETTO_DB, GDB_Car2_PLY),
	_Anim(GHETTO_DB, GDB_Car2_SMO),
	_Anim(GHETTO_DB, GDB_Car2_SWE),
	_Anim(GHETTO_DB, GDB_Car_PLY),
	_Anim(GHETTO_DB, GDB_Car_RYD),
	_Anim(GHETTO_DB, GDB_Car_SMO),
	_Anim(GHETTO_DB, GDB_Car_SWE),
#endif
#if !defined DC_ANIMS_DISABLE__GOGGLES
// Name: goggles, animations count: 1
	_Anim(goggles, goggles_put_on),
#endif
#if !defined DC_ANIMS_DISABLE__GRAFFITI
// Name: GRAFFITI, animations count: 2
	_Anim(GRAFFITI, graffiti_Chkout),
	_Anim(GRAFFITI, spraycan_fire),
#endif
#if !defined DC_ANIMS_DISABLE__GRAVEYARD
// Name: GRAVEYARD, animations count: 3
	_Anim(GRAVEYARD, mrnF_loop),
	_Anim(GRAVEYARD, mrnM_loop),
	_Anim(GRAVEYARD, prst_loopa),
#endif
#if !defined DC_ANIMS_DISABLE__GRENADE
// Name: GRENADE, animations count: 3
	_Anim(GRENADE, WEAPON_start_throw),
	_Anim(GRENADE, WEAPON_throw),
	_Anim(GRENADE, WEAPON_throwu),
#endif
#if !defined DC_ANIMS_DISABLE__GYMNASIUM
// Name: GYMNASIUM, animations count: 24
	_Anim(GYMNASIUM, GYMshadowbox),
	_Anim(GYMNASIUM, gym_bike_celebrate),
	_Anim(GYMNASIUM, gym_bike_fast),
	_Anim(GYMNASIUM, gym_bike_faster),
	_Anim(GYMNASIUM, gym_bike_getoff),
	_Anim(GYMNASIUM, gym_bike_geton),
	_Anim(GYMNASIUM, gym_bike_pedal),
	_Anim(GYMNASIUM, gym_bike_slow),
	_Anim(GYMNASIUM, gym_bike_still),
	_Anim(GYMNASIUM, gym_jog_falloff),
	_Anim(GYMNASIUM, gym_shadowbox),
	_Anim(GYMNASIUM, gym_tread_celebrate),
	_Anim(GYMNASIUM, gym_tread_falloff),
	_Anim(GYMNASIUM, gym_tread_getoff),
	_Anim(GYMNASIUM, gym_tread_geton),
	_Anim(GYMNASIUM, gym_tread_jog),
	_Anim(GYMNASIUM, gym_tread_sprint),
	_Anim(GYMNASIUM, gym_tread_tired),
	_Anim(GYMNASIUM, gym_tread_walk),
	_Anim(GYMNASIUM, gym_walk_falloff),
	_Anim(GYMNASIUM, Pedals_fast),
	_Anim(GYMNASIUM, Pedals_med),
	_Anim(GYMNASIUM, Pedals_slow),
	_Anim(GYMNASIUM, Pedals_still),
#endif
#if !defined DC_ANIMS_DISABLE__HAIRCUTS
// Name: HAIRCUTS, animations count: 13
	_Anim(HAIRCUTS, BRB_Beard_01),
	_Anim(HAIRCUTS, BRB_Buy),
	_Anim(HAIRCUTS, BRB_Cut),
	_Anim(HAIRCUTS, BRB_Cut_In),
	_Anim(HAIRCUTS, BRB_Cut_Out),
	_Anim(HAIRCUTS, BRB_Hair_01),
	_Anim(HAIRCUTS, BRB_Hair_02),
	_Anim(HAIRCUTS, BRB_In),
	_Anim(HAIRCUTS, BRB_Loop),
	_Anim(HAIRCUTS, BRB_Out),
	_Anim(HAIRCUTS, BRB_Sit_In),
	_Anim(HAIRCUTS, BRB_Sit_Loop),
	_Anim(HAIRCUTS, BRB_Sit_Out),
#endif
#if !defined DC_ANIMS_DISABLE__HEIST9
// Name: HEIST9, animations count: 10
	_Anim(HEIST9, CAS_G2_GasKO),
	_Anim(HEIST9, swt_wllpk_L),
	_Anim(HEIST9, swt_wllpk_L_back),
	_Anim(HEIST9, swt_wllpk_R),
	_Anim(HEIST9, swt_wllpk_R_back),
	_Anim(HEIST9, swt_wllshoot_in_L),
	_Anim(HEIST9, swt_wllshoot_in_R),
	_Anim(HEIST9, swt_wllshoot_out_L),
	_Anim(HEIST9, swt_wllshoot_out_R),
	_Anim(HEIST9, Use_SwipeCard),
#endif
#if !defined DC_ANIMS_DISABLE__INT_HOUSE
// Name: INT_HOUSE, animations count: 10
	_Anim(INT_HOUSE, BED_In_L),
	_Anim(INT_HOUSE, BED_In_R),
	_Anim(INT_HOUSE, BED_Loop_L),
	_Anim(INT_HOUSE, BED_Loop_R),
	_Anim(INT_HOUSE, BED_Out_L),
	_Anim(INT_HOUSE, BED_Out_R),
	_Anim(INT_HOUSE, LOU_In),
	_Anim(INT_HOUSE, LOU_Loop),
	_Anim(INT_HOUSE, LOU_Out),
	_Anim(INT_HOUSE, wash_up),
#endif
#if !defined DC_ANIMS_DISABLE__INT_OFFICE
// Name: INT_OFFICE, animations count: 10
	_Anim(INT_OFFICE, FF_Dam_Fwd),
	_Anim(INT_OFFICE, OFF_Sit_2Idle_180),
	_Anim(INT_OFFICE, OFF_Sit_Bored_Loop),
	_Anim(INT_OFFICE, OFF_Sit_Crash),
	_Anim(INT_OFFICE, OFF_Sit_Drink),
	_Anim(INT_OFFICE, OFF_Sit_Idle_Loop),
	_Anim(INT_OFFICE, OFF_Sit_In),
	_Anim(INT_OFFICE, OFF_Sit_Read),
	_Anim(INT_OFFICE, OFF_Sit_Type_Loop),
	_Anim(INT_OFFICE, OFF_Sit_Watch),
#endif
#if !defined DC_ANIMS_DISABLE__INT_SHOP
// Name: INT_SHOP, animations count: 8
	_Anim(INT_SHOP, shop_cashier),
	_Anim(INT_SHOP, shop_in),
	_Anim(INT_SHOP, shop_lookA),
	_Anim(INT_SHOP, shop_lookB),
	_Anim(INT_SHOP, shop_loop),
	_Anim(INT_SHOP, shop_out),
	_Anim(INT_SHOP, shop_pay),
	_Anim(INT_SHOP, shop_shelf),
#endif
#if !defined DC_ANIMS_DISABLE__JST_BUISNESS
// Name: JST_BUISNESS, animations count: 4
	_Anim(JST_BUISNESS, girl_01),
	_Anim(JST_BUISNESS, girl_02),
	_Anim(JST_BUISNESS, player_01),
	_Anim(JST_BUISNESS, smoke_01),
#endif
#if !defined DC_ANIMS_DISABLE__KART
// Name: KART, animations count: 4
	_Anim(KART, KART_getin_LHS),
	_Anim(KART, KART_getin_RHS),
	_Anim(KART, KART_getout_LHS),
	_Anim(KART, KART_getout_RHS),
#endif
#if !defined DC_ANIMS_DISABLE__KISSING
// Name: KISSING, animations count: 15
	_Anim(KISSING, BD_GF_Wave),
	_Anim(KISSING, gfwave2),
	_Anim(KISSING, GF_CarArgue_01),
	_Anim(KISSING, GF_CarArgue_02),
	_Anim(KISSING, GF_CarSpot),
	_Anim(KISSING, GF_StreetArgue_01),
	_Anim(KISSING, GF_StreetArgue_02),
	_Anim(KISSING, gift_get),
	_Anim(KISSING, gift_give),
	_Anim(KISSING, Grlfrd_Kiss_01),
	_Anim(KISSING, Grlfrd_Kiss_02),
	_Anim(KISSING, Grlfrd_Kiss_03),
	_Anim(KISSING, Playa_Kiss_01),
	_Anim(KISSING, Playa_Kiss_02),
	_Anim(KISSING, Playa_Kiss_03),
#endif
#if !defined DC_ANIMS_DISABLE__KNIFE
// Name: KNIFE, animations count: 16
	_Anim(KNIFE, KILL_Knife_Ped_Damage),
	_Anim(KNIFE, KILL_Knife_Ped_Die),
	_Anim(KNIFE, KILL_Knife_Player),
	_Anim(KNIFE, KILL_Partial),
	_Anim(KNIFE, knife_1),
	_Anim(KNIFE, knife_2),
	_Anim(KNIFE, knife_3),
	_Anim(KNIFE, Knife_4),
	_Anim(KNIFE, knife_block),
	_Anim(KNIFE, Knife_G),
	_Anim(KNIFE, knife_hit_1),
	_Anim(KNIFE, knife_hit_2),
	_Anim(KNIFE, knife_hit_3),
	_Anim(KNIFE, knife_IDLE),
	_Anim(KNIFE, knife_part),
	_Anim(KNIFE, WEAPON_knifeidle),
#endif
#if !defined DC_ANIMS_DISABLE__LAPDAN1
// Name: LAPDAN1, animations count: 2
	_Anim(LAPDAN1, LAPDAN_D),
	_Anim(LAPDAN1, LAPDAN_P),
#endif
#if !defined DC_ANIMS_DISABLE__LAPDAN2
// Name: LAPDAN2, animations count: 2
	_Anim(LAPDAN2, LAPDAN_D),
	_Anim(LAPDAN2, LAPDAN_P),
#endif
#if !defined DC_ANIMS_DISABLE__LAPDAN3
// Name: LAPDAN3, animations count: 2
	_Anim(LAPDAN3, LAPDAN_D),
	_Anim(LAPDAN3, LAPDAN_P),
#endif
#if !defined DC_ANIMS_DISABLE__LOWRIDER
// Name: LOWRIDER, animations count: 39
	_Anim(LOWRIDER, F_smklean_loop),
	_Anim(LOWRIDER, lrgirl_bdbnce),
	_Anim(LOWRIDER, lrgirl_hair),
	_Anim(LOWRIDER, lrgirl_hurry),
	_Anim(LOWRIDER, lrgirl_idleloop),
	_Anim(LOWRIDER, lrgirl_idle_to_l0),
	_Anim(LOWRIDER, lrgirl_l0_bnce),
	_Anim(LOWRIDER, lrgirl_l0_loop),
	_Anim(LOWRIDER, lrgirl_l0_to_l1),
	_Anim(LOWRIDER, lrgirl_l12_to_l0),
	_Anim(LOWRIDER, lrgirl_l1_bnce),
	_Anim(LOWRIDER, lrgirl_l1_loop),
	_Anim(LOWRIDER, lrgirl_l1_to_l2),
	_Anim(LOWRIDER, lrgirl_l2_bnce),
	_Anim(LOWRIDER, lrgirl_l2_loop),
	_Anim(LOWRIDER, lrgirl_l2_to_l3),
	_Anim(LOWRIDER, lrgirl_l345_to_l1),
	_Anim(LOWRIDER, lrgirl_l3_bnce),
	_Anim(LOWRIDER, lrgirl_l3_loop),
	_Anim(LOWRIDER, lrgirl_l3_to_l4),
	_Anim(LOWRIDER, lrgirl_l4_bnce),
	_Anim(LOWRIDER, lrgirl_l4_loop),
	_Anim(LOWRIDER, lrgirl_l4_to_l5),
	_Anim(LOWRIDER, lrgirl_l5_bnce),
	_Anim(LOWRIDER, lrgirl_l5_loop),
	_Anim(LOWRIDER, M_smklean_loop),
	_Anim(LOWRIDER, M_smkstnd_loop),
	_Anim(LOWRIDER, prtial_gngtlkB),
	_Anim(LOWRIDER, prtial_gngtlkC),
	_Anim(LOWRIDER, prtial_gngtlkD),
	_Anim(LOWRIDER, prtial_gngtlkE),
	_Anim(LOWRIDER, prtial_gngtlkF),
	_Anim(LOWRIDER, prtial_gngtlkG),
	_Anim(LOWRIDER, prtial_gngtlkH),
	_Anim(LOWRIDER, RAP_A_Loop),
	_Anim(LOWRIDER, RAP_B_Loop),
	_Anim(LOWRIDER, RAP_C_Loop),
	_Anim(LOWRIDER, Sit_relaxed),
	_Anim(LOWRIDER, Tap_hand),
#endif
#if !defined DC_ANIMS_DISABLE__MD_CHASE
// Name: MD_CHASE, animations count: 25
	_Anim(MD_CHASE, Carhit_Hangon),
	_Anim(MD_CHASE, Carhit_Tumble),
	_Anim(MD_CHASE, donutdrop),
	_Anim(MD_CHASE, Fen_Choppa_L1),
	_Anim(MD_CHASE, Fen_Choppa_L2),
	_Anim(MD_CHASE, Fen_Choppa_L3),
	_Anim(MD_CHASE, Fen_Choppa_R1),
	_Anim(MD_CHASE, Fen_Choppa_R2),
	_Anim(MD_CHASE, Fen_Choppa_R3),
	_Anim(MD_CHASE, Hangon_Stun_loop),
	_Anim(MD_CHASE, Hangon_Stun_Turn),
	_Anim(MD_CHASE, MD_BIKE_2_HANG),
	_Anim(MD_CHASE, MD_BIKE_Jmp_BL),
	_Anim(MD_CHASE, MD_BIKE_Jmp_F),
	_Anim(MD_CHASE, MD_BIKE_Lnd_BL),
	_Anim(MD_CHASE, MD_BIKE_Lnd_Die_BL),
	_Anim(MD_CHASE, MD_BIKE_Lnd_Die_F),
	_Anim(MD_CHASE, MD_BIKE_Lnd_F),
	_Anim(MD_CHASE, MD_BIKE_Lnd_Roll),
	_Anim(MD_CHASE, MD_BIKE_Lnd_Roll_F),
	_Anim(MD_CHASE, MD_BIKE_Punch),
	_Anim(MD_CHASE, MD_BIKE_Punch_F),
	_Anim(MD_CHASE, MD_BIKE_Shot_F),
	_Anim(MD_CHASE, MD_HANG_Lnd_Roll),
	_Anim(MD_CHASE, MD_HANG_Loop),
#endif
#if !defined DC_ANIMS_DISABLE__MD_END
// Name: MD_END, animations count: 8
	_Anim(MD_END, END_SC1_PLY),
	_Anim(MD_END, END_SC1_RYD),
	_Anim(MD_END, END_SC1_SMO),
	_Anim(MD_END, END_SC1_SWE),
	_Anim(MD_END, END_SC2_PLY),
	_Anim(MD_END, END_SC2_RYD),
	_Anim(MD_END, END_SC2_SMO),
	_Anim(MD_END, END_SC2_SWE),
#endif
#if !defined DC_ANIMS_DISABLE__MEDIC
// Name: MEDIC, animations count: 1
	_Anim(MEDIC, CPR),
#endif
#if !defined DC_ANIMS_DISABLE__MISC
// Name: MISC, animations count: 41
	_Anim(MISC, bitchslap),
	_Anim(MISC, BMX_celebrate),
	_Anim(MISC, BMX_comeon),
	_Anim(MISC, bmx_idleloop_01),
	_Anim(MISC, bmx_idleloop_02),
	_Anim(MISC, bmx_talkleft_in),
	_Anim(MISC, bmx_talkleft_loop),
	_Anim(MISC, bmx_talkleft_out),
	_Anim(MISC, bmx_talkright_in),
	_Anim(MISC, bmx_talkright_loop),
	_Anim(MISC, bmx_talkright_out),
	_Anim(MISC, bng_wndw),
	_Anim(MISC, bng_wndw_02),
	_Anim(MISC, Case_pickup),
	_Anim(MISC, door_jet),
	_Anim(MISC, GRAB_L),
	_Anim(MISC, GRAB_R),
	_Anim(MISC, Hiker_Pose),
	_Anim(MISC, Hiker_Pose_L),
	_Anim(MISC, Idle_Chat_02),
	_Anim(MISC, KAT_Throw_K),
	_Anim(MISC, KAT_Throw_O),
	_Anim(MISC, KAT_Throw_P),
	_Anim(MISC, PASS_Rifle_O),
	_Anim(MISC, PASS_Rifle_Ped),
	_Anim(MISC, PASS_Rifle_Ply),
	_Anim(MISC, pickup_box),
	_Anim(MISC, Plane_door),
	_Anim(MISC, Plane_exit),
	_Anim(MISC, Plane_hijack),
	_Anim(MISC, Plunger_01),
	_Anim(MISC, Plyrlean_loop),
	_Anim(MISC, plyr_shkhead),
	_Anim(MISC, Run_Dive),
	_Anim(MISC, Scratchballs_01),
	_Anim(MISC, SEAT_LR),
	_Anim(MISC, Seat_talk_01),
	_Anim(MISC, Seat_talk_02),
	_Anim(MISC, SEAT_watch),
	_Anim(MISC, smalplane_door),
	_Anim(MISC, smlplane_door),
#endif
#if !defined DC_ANIMS_DISABLE__MTB
// Name: MTB, animations count: 18
	_Anim(MTB, MTB_back),
	_Anim(MTB, MTB_bunnyhop),
	_Anim(MTB, MTB_drivebyFT),
	_Anim(MTB, MTB_driveby_LHS),
	_Anim(MTB, MTB_driveby_RHS),
	_Anim(MTB, MTB_fwd),
	_Anim(MTB, MTB_getoffBACK),
	_Anim(MTB, MTB_getoffLHS),
	_Anim(MTB, MTB_getoffRHS),
	_Anim(MTB, MTB_jumponL),
	_Anim(MTB, MTB_jumponR),
	_Anim(MTB, MTB_Left),
	_Anim(MTB, MTB_pedal),
	_Anim(MTB, MTB_pushes),
	_Anim(MTB, MTB_Ride),
	_Anim(MTB, MTB_Right),
	_Anim(MTB, MTB_sprint),
	_Anim(MTB, MTB_still),
#endif
#if !defined DC_ANIMS_DISABLE__MUSCULAR
// Name: MUSCULAR, animations count: 17
	_Anim(MUSCULAR, MscleWalkst_armed),
	_Anim(MUSCULAR, MscleWalkst_Csaw),
	_Anim(MUSCULAR, Mscle_rckt_run),
	_Anim(MUSCULAR, Mscle_rckt_walkst),
	_Anim(MUSCULAR, Mscle_run_Csaw),
	_Anim(MUSCULAR, MuscleIdle),
	_Anim(MUSCULAR, MuscleIdle_armed),
	_Anim(MUSCULAR, MuscleIdle_Csaw),
	_Anim(MUSCULAR, MuscleIdle_rocket),
	_Anim(MUSCULAR, MuscleRun),
	_Anim(MUSCULAR, MuscleRun_armed),
	_Anim(MUSCULAR, MuscleSprint),
	_Anim(MUSCULAR, MuscleWalk),
	_Anim(MUSCULAR, MuscleWalkstart),
	_Anim(MUSCULAR, MuscleWalk_armed),
	_Anim(MUSCULAR, Musclewalk_Csaw),
	_Anim(MUSCULAR, Musclewalk_rocket),
#endif
#if !defined DC_ANIMS_DISABLE__NEVADA
// Name: NEVADA, animations count: 2
	_Anim(NEVADA, NEVADA_getin),
	_Anim(NEVADA, NEVADA_getout),
#endif
#if !defined DC_ANIMS_DISABLE__ON_LOOKERS
// Name: ON_LOOKERS, animations count: 29
	_Anim(ON_LOOKERS, lkaround_in),
	_Anim(ON_LOOKERS, lkaround_loop),
	_Anim(ON_LOOKERS, lkaround_out),
	_Anim(ON_LOOKERS, lkup_in),
	_Anim(ON_LOOKERS, lkup_loop),
	_Anim(ON_LOOKERS, lkup_out),
	_Anim(ON_LOOKERS, lkup_point),
	_Anim(ON_LOOKERS, panic_cower),
	_Anim(ON_LOOKERS, panic_hide),
	_Anim(ON_LOOKERS, panic_in),
	_Anim(ON_LOOKERS, panic_loop),
	_Anim(ON_LOOKERS, panic_out),
	_Anim(ON_LOOKERS, panic_point),
	_Anim(ON_LOOKERS, panic_shout),
	_Anim(ON_LOOKERS, Pointup_in),
	_Anim(ON_LOOKERS, Pointup_loop),
	_Anim(ON_LOOKERS, Pointup_out),
	_Anim(ON_LOOKERS, Pointup_shout),
	_Anim(ON_LOOKERS, point_in),
	_Anim(ON_LOOKERS, point_loop),
	_Anim(ON_LOOKERS, point_out),
	_Anim(ON_LOOKERS, shout_01),
	_Anim(ON_LOOKERS, shout_02),
	_Anim(ON_LOOKERS, shout_in),
	_Anim(ON_LOOKERS, shout_loop),
	_Anim(ON_LOOKERS, shout_out),
	_Anim(ON_LOOKERS, wave_in),
	_Anim(ON_LOOKERS, wave_loop),
	_Anim(ON_LOOKERS, wave_out),
#endif
#if !defined DC_ANIMS_DISABLE__OTB
// Name: OTB, animations count: 11
	_Anim(OTB, betslp_in),
	_Anim(OTB, betslp_lkabt),
	_Anim(OTB, betslp_loop),
	_Anim(OTB, betslp_out),
	_Anim(OTB, betslp_tnk),
	_Anim(OTB, wtchrace_cmon),
	_Anim(OTB, wtchrace_in),
	_Anim(OTB, wtchrace_loop),
	_Anim(OTB, wtchrace_lose),
	_Anim(OTB, wtchrace_out),
	_Anim(OTB, wtchrace_win),
#endif
#if !defined DC_ANIMS_DISABLE__PARACHUTE
// Name: PARACHUTE, animations count: 22
	_Anim(PARACHUTE, FALL_skyDive),
	_Anim(PARACHUTE, FALL_SkyDive_Accel),
	_Anim(PARACHUTE, FALL_skyDive_DIE),
	_Anim(PARACHUTE, FALL_SkyDive_L),
	_Anim(PARACHUTE, FALL_SkyDive_R),
	_Anim(PARACHUTE, PARA_decel),
	_Anim(PARACHUTE, PARA_decel_O),
	_Anim(PARACHUTE, PARA_float),
	_Anim(PARACHUTE, PARA_float_O),
	_Anim(PARACHUTE, PARA_Land),
	_Anim(PARACHUTE, PARA_Land_O),
	_Anim(PARACHUTE, PARA_Land_Water),
	_Anim(PARACHUTE, PARA_Land_Water_O),
	_Anim(PARACHUTE, PARA_open),
	_Anim(PARACHUTE, PARA_open_O),
	_Anim(PARACHUTE, PARA_Rip_Land_O),
	_Anim(PARACHUTE, PARA_Rip_Loop_O),
	_Anim(PARACHUTE, PARA_Rip_O),
	_Anim(PARACHUTE, PARA_steerL),
	_Anim(PARACHUTE, PARA_steerL_O),
	_Anim(PARACHUTE, PARA_steerR),
	_Anim(PARACHUTE, PARA_steerR_O),
#endif
#if !defined DC_ANIMS_DISABLE__PARK
// Name: PARK, animations count: 3
	_Anim(PARK, Tai_Chi_in),
	_Anim(PARK, Tai_Chi_Loop),
	_Anim(PARK, Tai_Chi_Out),
#endif
#if !defined DC_ANIMS_DISABLE__PAULNMAC
// Name: PAULNMAC, animations count: 12
	_Anim(PAULNMAC, Piss_in),
	_Anim(PAULNMAC, Piss_loop),
	_Anim(PAULNMAC, Piss_out),
	_Anim(PAULNMAC, PnM_Argue1_A),
	_Anim(PAULNMAC, PnM_Argue1_B),
	_Anim(PAULNMAC, PnM_Argue2_A),
	_Anim(PAULNMAC, PnM_Argue2_B),
	_Anim(PAULNMAC, PnM_Loop_A),
	_Anim(PAULNMAC, PnM_Loop_B),
	_Anim(PAULNMAC, wank_in),
	_Anim(PAULNMAC, wank_loop),
	_Anim(PAULNMAC, wank_out),
#endif
#if !defined DC_ANIMS_DISABLE__PED
// Name: ped, animations count: 294
	_Anim(ped, abseil),
	_Anim(ped, ARRESTgun),
	_Anim(ped, ATM),
	_Anim(ped, BIKE_elbowL),
	_Anim(ped, BIKE_elbowR),
	_Anim(ped, BIKE_fallR),
	_Anim(ped, BIKE_fall_off),
	_Anim(ped, BIKE_pickupL),
	_Anim(ped, BIKE_pickupR),
	_Anim(ped, BIKE_pullupL),
	_Anim(ped, BIKE_pullupR),
	_Anim(ped, bomber),
	_Anim(ped, CAR_alignHI_LHS),
	_Anim(ped, CAR_alignHI_RHS),
	_Anim(ped, CAR_align_LHS),
	_Anim(ped, CAR_align_RHS),
	_Anim(ped, CAR_closedoorL_LHS),
	_Anim(ped, CAR_closedoorL_RHS),
	_Anim(ped, CAR_closedoor_LHS),
	_Anim(ped, CAR_closedoor_RHS),
	_Anim(ped, CAR_close_LHS),
	_Anim(ped, CAR_close_RHS),
	_Anim(ped, CAR_crawloutRHS),
	_Anim(ped, CAR_dead_LHS),
	_Anim(ped, CAR_dead_RHS),
	_Anim(ped, CAR_doorlocked_LHS),
	_Anim(ped, CAR_doorlocked_RHS),
	_Anim(ped, CAR_fallout_LHS),
	_Anim(ped, CAR_fallout_RHS),
	_Anim(ped, CAR_getinL_LHS),
	_Anim(ped, CAR_getinL_RHS),
	_Anim(ped, CAR_getin_LHS),
	_Anim(ped, CAR_getin_RHS),
	_Anim(ped, CAR_getoutL_LHS),
	_Anim(ped, CAR_getoutL_RHS),
	_Anim(ped, CAR_getout_LHS),
	_Anim(ped, CAR_getout_RHS),
	_Anim(ped, car_hookertalk),
	_Anim(ped, CAR_jackedLHS),
	_Anim(ped, CAR_jackedRHS),
	_Anim(ped, CAR_jumpin_LHS),
	_Anim(ped, CAR_LB),
	_Anim(ped, CAR_LB_pro),
	_Anim(ped, CAR_LB_weak),
	_Anim(ped, CAR_LjackedLHS),
	_Anim(ped, CAR_LjackedRHS),
	_Anim(ped, CAR_Lshuffle_RHS),
	_Anim(ped, CAR_Lsit),
	_Anim(ped, CAR_open_LHS),
	_Anim(ped, CAR_open_RHS),
	_Anim(ped, CAR_pulloutL_LHS),
	_Anim(ped, CAR_pulloutL_RHS),
	_Anim(ped, CAR_pullout_LHS),
	_Anim(ped, CAR_pullout_RHS),
	_Anim(ped, CAR_Qjacked),
	_Anim(ped, CAR_rolldoor),
	_Anim(ped, CAR_rolldoorLO),
	_Anim(ped, CAR_rollout_LHS),
	_Anim(ped, CAR_rollout_RHS),
	_Anim(ped, CAR_shuffle_RHS),
	_Anim(ped, CAR_sit),
	_Anim(ped, CAR_sitp),
	_Anim(ped, CAR_sitpLO),
	_Anim(ped, CAR_sit_pro),
	_Anim(ped, CAR_sit_weak),
	_Anim(ped, CAR_tune_radio),
	_Anim(ped, CLIMB_idle),
	_Anim(ped, CLIMB_jump),
	_Anim(ped, CLIMB_jump2fall),
	_Anim(ped, CLIMB_jump_B),
	_Anim(ped, CLIMB_Pull),
	_Anim(ped, CLIMB_Stand),
	_Anim(ped, CLIMB_Stand_finish),
	_Anim(ped, cower),
	_Anim(ped, Crouch_Roll_L),
	_Anim(ped, Crouch_Roll_R),
	_Anim(ped, DAM_armL_frmBK),
	_Anim(ped, DAM_armL_frmFT),
	_Anim(ped, DAM_armL_frmLT),
	_Anim(ped, DAM_armR_frmBK),
	_Anim(ped, DAM_armR_frmFT),
	_Anim(ped, DAM_armR_frmRT),
	_Anim(ped, DAM_LegL_frmBK),
	_Anim(ped, DAM_LegL_frmFT),
	_Anim(ped, DAM_LegL_frmLT),
	_Anim(ped, DAM_LegR_frmBK),
	_Anim(ped, DAM_LegR_frmFT),
	_Anim(ped, DAM_LegR_frmRT),
	_Anim(ped, DAM_stomach_frmBK),
	_Anim(ped, DAM_stomach_frmFT),
	_Anim(ped, DAM_stomach_frmLT),
	_Anim(ped, DAM_stomach_frmRT),
	_Anim(ped, DOOR_LHinge_O),
	_Anim(ped, DOOR_RHinge_O),
	_Anim(ped, DrivebyL_L),
	_Anim(ped, DrivebyL_R),
	_Anim(ped, Driveby_L),
	_Anim(ped, Driveby_R),
	_Anim(ped, DRIVE_BOAT),
	_Anim(ped, DRIVE_BOAT_back),
	_Anim(ped, DRIVE_BOAT_L),
	_Anim(ped, DRIVE_BOAT_R),
	_Anim(ped, Drive_L),
	_Anim(ped, Drive_LO_l),
	_Anim(ped, Drive_LO_R),
	_Anim(ped, Drive_L_pro),
	_Anim(ped, Drive_L_pro_slow),
	_Anim(ped, Drive_L_slow),
	_Anim(ped, Drive_L_weak),
	_Anim(ped, Drive_L_weak_slow),
	_Anim(ped, Drive_R),
	_Anim(ped, Drive_R_pro),
	_Anim(ped, Drive_R_pro_slow),
	_Anim(ped, Drive_R_slow),
	_Anim(ped, Drive_R_weak),
	_Anim(ped, Drive_R_weak_slow),
	_Anim(ped, Drive_truck),
	_Anim(ped, DRIVE_truck_back),
	_Anim(ped, DRIVE_truck_L),
	_Anim(ped, DRIVE_truck_R),
	_Anim(ped, Drown),
	_Anim(ped, DUCK_cower),
	_Anim(ped, endchat_01),
	_Anim(ped, endchat_02),
	_Anim(ped, endchat_03),
	_Anim(ped, EV_dive),
	_Anim(ped, EV_step),
	_Anim(ped, facanger),
	_Anim(ped, facgum),
	_Anim(ped, facsurp),
	_Anim(ped, facsurpm),
	_Anim(ped, factalk),
	_Anim(ped, facurios),
	_Anim(ped, FALL_back),
	_Anim(ped, FALL_collapse),
	_Anim(ped, FALL_fall),
	_Anim(ped, FALL_front),
	_Anim(ped, FALL_glide),
	_Anim(ped, FALL_land),
	_Anim(ped, FALL_skyDive),
	_Anim(ped, Fight2Idle),
	_Anim(ped, FightA_1),
	_Anim(ped, FightA_2),
	_Anim(ped, FightA_3),
	_Anim(ped, FightA_block),
	_Anim(ped, FightA_G),
	_Anim(ped, FightA_M),
	_Anim(ped, FIGHTIDLE),
	_Anim(ped, FightShB),
	_Anim(ped, FightShF),
	_Anim(ped, FightSh_BWD),
	_Anim(ped, FightSh_FWD),
	_Anim(ped, FightSh_Left),
	_Anim(ped, FightSh_Right),
	_Anim(ped, flee_lkaround_01),
	_Anim(ped, FLOOR_hit),
	_Anim(ped, FLOOR_hit_f),
	_Anim(ped, fucku),
	_Anim(ped, gang_gunstand),
	_Anim(ped, gas_cwr),
	_Anim(ped, getup),
	_Anim(ped, getup_front),
	_Anim(ped, gum_eat),
	_Anim(ped, GunCrouchBwd),
	_Anim(ped, GunCrouchFwd),
	_Anim(ped, GunMove_BWD),
	_Anim(ped, GunMove_FWD),
	_Anim(ped, GunMove_L),
	_Anim(ped, GunMove_R),
	_Anim(ped, Gun_2_IDLE),
	_Anim(ped, GUN_BUTT),
	_Anim(ped, GUN_BUTT_crouch),
	_Anim(ped, Gun_stand),
	_Anim(ped, handscower),
	_Anim(ped, handsup),
	_Anim(ped, HitA_1),
	_Anim(ped, HitA_2),
	_Anim(ped, HitA_3),
	_Anim(ped, HIT_back),
	_Anim(ped, HIT_behind),
	_Anim(ped, HIT_front),
	_Anim(ped, HIT_GUN_BUTT),
	_Anim(ped, HIT_L),
	_Anim(ped, HIT_R),
	_Anim(ped, HIT_walk),
	_Anim(ped, HIT_wall),
	_Anim(ped, Idlestance_fat),
	_Anim(ped, idlestance_old),
	_Anim(ped, IDLE_armed),
	_Anim(ped, IDLE_chat),
	_Anim(ped, IDLE_csaw),
	_Anim(ped, Idle_Gang1),
	_Anim(ped, IDLE_HBHB),
	_Anim(ped, IDLE_ROCKET),
	_Anim(ped, IDLE_stance),
	_Anim(ped, IDLE_taxi),
	_Anim(ped, IDLE_tired),
	_Anim(ped, Jetpack_Idle),
	_Anim(ped, JOG_femaleA),
	_Anim(ped, JOG_maleA),
	_Anim(ped, JUMP_glide),
	_Anim(ped, JUMP_land),
	_Anim(ped, JUMP_launch),
	_Anim(ped, JUMP_launch_R),
	_Anim(ped, KART_drive),
	_Anim(ped, KART_L),
	_Anim(ped, KART_LB),
	_Anim(ped, KART_R),
	_Anim(ped, KD_left),
	_Anim(ped, KD_right),
	_Anim(ped, KO_shot_face),
	_Anim(ped, KO_shot_front),
	_Anim(ped, KO_shot_stom),
	_Anim(ped, KO_skid_back),
	_Anim(ped, KO_skid_front),
	_Anim(ped, KO_spin_L),
	_Anim(ped, KO_spin_R),
	_Anim(ped, pass_Smoke_in_car),
	_Anim(ped, phone_in),
	_Anim(ped, phone_out),
	_Anim(ped, phone_talk),
	_Anim(ped, Player_Sneak),
	_Anim(ped, Player_Sneak_walkstart),
	_Anim(ped, roadcross),
	_Anim(ped, roadcross_female),
	_Anim(ped, roadcross_gang),
	_Anim(ped, roadcross_old),
	_Anim(ped, run_1armed),
	_Anim(ped, run_armed),
	_Anim(ped, run_civi),
	_Anim(ped, run_csaw),
	_Anim(ped, run_fat),
	_Anim(ped, run_fatold),
	_Anim(ped, run_gang1),
	_Anim(ped, run_left),
	_Anim(ped, run_old),
	_Anim(ped, run_player),
	_Anim(ped, run_right),
	_Anim(ped, run_rocket),
	_Anim(ped, Run_stop),
	_Anim(ped, Run_stopR),
	_Anim(ped, Run_Wuzi),
	_Anim(ped, SEAT_down),
	_Anim(ped, SEAT_idle),
	_Anim(ped, SEAT_up),
	_Anim(ped, SHOT_leftP),
	_Anim(ped, SHOT_partial),
	_Anim(ped, SHOT_partial_B),
	_Anim(ped, SHOT_rightP),
	_Anim(ped, Shove_Partial),
	_Anim(ped, Smoke_in_car),
	_Anim(ped, sprint_civi),
	_Anim(ped, sprint_panic),
	_Anim(ped, Sprint_Wuzi),
	_Anim(ped, swat_run),
	_Anim(ped, Swim_Tread),
	_Anim(ped, Tap_hand),
	_Anim(ped, Tap_handP),
	_Anim(ped, turn_180),
	_Anim(ped, Turn_L),
	_Anim(ped, Turn_R),
	_Anim(ped, WALK_armed),
	_Anim(ped, WALK_civi),
	_Anim(ped, WALK_csaw),
	_Anim(ped, Walk_DoorPartial),
	_Anim(ped, WALK_drunk),
	_Anim(ped, WALK_fat),
	_Anim(ped, WALK_fatold),
	_Anim(ped, WALK_gang1),
	_Anim(ped, WALK_gang2),
	_Anim(ped, WALK_old),
	_Anim(ped, WALK_player),
	_Anim(ped, WALK_rocket),
	_Anim(ped, WALK_shuffle),
	_Anim(ped, WALK_start),
	_Anim(ped, WALK_start_armed),
	_Anim(ped, WALK_start_csaw),
	_Anim(ped, WALK_start_rocket),
	_Anim(ped, Walk_Wuzi),
	_Anim(ped, WEAPON_crouch),
	_Anim(ped, woman_idlestance),
	_Anim(ped, woman_run),
	_Anim(ped, WOMAN_runbusy),
	_Anim(ped, WOMAN_runfatold),
	_Anim(ped, woman_runpanic),
	_Anim(ped, WOMAN_runsexy),
	_Anim(ped, WOMAN_walkbusy),
	_Anim(ped, WOMAN_walkfatold),
	_Anim(ped, WOMAN_walknorm),
	_Anim(ped, WOMAN_walkold),
	_Anim(ped, WOMAN_walkpro),
	_Anim(ped, WOMAN_walksexy),
	_Anim(ped, WOMAN_walkshop),
	_Anim(ped, XPRESSscratch),
#endif
#if !defined DC_ANIMS_DISABLE__PLAYER_DVBYS
// Name: PLAYER_DVBYS, animations count: 4
	_Anim(PLAYER_DVBYS, Plyr_DrivebyBwd),
	_Anim(PLAYER_DVBYS, Plyr_DrivebyFwd),
	_Anim(PLAYER_DVBYS, Plyr_DrivebyLHS),
	_Anim(PLAYER_DVBYS, Plyr_DrivebyRHS),
#endif
#if !defined DC_ANIMS_DISABLE__PLAYIDLES
// Name: PLAYIDLES, animations count: 5
	_Anim(PLAYIDLES, shift),
	_Anim(PLAYIDLES, shldr),
	_Anim(PLAYIDLES, stretch),
	_Anim(PLAYIDLES, strleg),
	_Anim(PLAYIDLES, time),
#endif
#if !defined DC_ANIMS_DISABLE__POLICE
// Name: POLICE, animations count: 10
	_Anim(POLICE, CopTraf_Away),
	_Anim(POLICE, CopTraf_Come),
	_Anim(POLICE, CopTraf_Left),
	_Anim(POLICE, CopTraf_Stop),
	_Anim(POLICE, COP_getoutcar_LHS),
	_Anim(POLICE, Cop_move_FWD),
	_Anim(POLICE, crm_drgbst_01),
	_Anim(POLICE, Door_Kick),
	_Anim(POLICE, plc_drgbst_01),
	_Anim(POLICE, plc_drgbst_02),
#endif
#if !defined DC_ANIMS_DISABLE__POOL
// Name: POOL, animations count: 21
	_Anim(POOL, POOL_ChalkCue),
	_Anim(POOL, POOL_Idle_Stance),
	_Anim(POOL, POOL_Long_Shot),
	_Anim(POOL, POOL_Long_Shot_O),
	_Anim(POOL, POOL_Long_Start),
	_Anim(POOL, POOL_Long_Start_O),
	_Anim(POOL, POOL_Med_Shot),
	_Anim(POOL, POOL_Med_Shot_O),
	_Anim(POOL, POOL_Med_Start),
	_Anim(POOL, POOL_Med_Start_O),
	_Anim(POOL, POOL_Place_White),
	_Anim(POOL, POOL_Short_Shot),
	_Anim(POOL, POOL_Short_Shot_O),
	_Anim(POOL, POOL_Short_Start),
	_Anim(POOL, POOL_Short_Start_O),
	_Anim(POOL, POOL_Walk),
	_Anim(POOL, POOL_Walk_Start),
	_Anim(POOL, POOL_XLong_Shot),
	_Anim(POOL, POOL_XLong_Shot_O),
	_Anim(POOL, POOL_XLong_Start),
	_Anim(POOL, POOL_XLong_Start_O),
#endif
#if !defined DC_ANIMS_DISABLE__POOR
// Name: POOR, animations count: 2
	_Anim(POOR, WINWASH_Start),
	_Anim(POOR, WINWASH_Wash2Beg),
#endif
#if !defined DC_ANIMS_DISABLE__PYTHON
// Name: PYTHON, animations count: 5
	_Anim(PYTHON, python_crouchfire),
	_Anim(PYTHON, python_crouchreload),
	_Anim(PYTHON, python_fire),
	_Anim(PYTHON, python_fire_poor),
	_Anim(PYTHON, python_reload),
#endif
#if !defined DC_ANIMS_DISABLE__QUAD
// Name: QUAD, animations count: 17
	_Anim(QUAD, QUAD_back),
	_Anim(QUAD, QUAD_driveby_FT),
	_Anim(QUAD, QUAD_driveby_LHS),
	_Anim(QUAD, QUAD_driveby_RHS),
	_Anim(QUAD, QUAD_FWD),
	_Anim(QUAD, QUAD_getoff_B),
	_Anim(QUAD, QUAD_getoff_LHS),
	_Anim(QUAD, QUAD_getoff_RHS),
	_Anim(QUAD, QUAD_geton_LHS),
	_Anim(QUAD, QUAD_geton_RHS),
	_Anim(QUAD, QUAD_hit),
	_Anim(QUAD, QUAD_kick),
	_Anim(QUAD, QUAD_Left),
	_Anim(QUAD, QUAD_passenger),
	_Anim(QUAD, QUAD_reverse),
	_Anim(QUAD, QUAD_ride),
	_Anim(QUAD, QUAD_Right),
#endif
#if !defined DC_ANIMS_DISABLE__QUAD_DBZ
// Name: QUAD_DBZ, animations count: 4
	_Anim(QUAD_DBZ, Pass_Driveby_BWD),
	_Anim(QUAD_DBZ, Pass_Driveby_FWD),
	_Anim(QUAD_DBZ, Pass_Driveby_LHS),
	_Anim(QUAD_DBZ, Pass_Driveby_RHS),
#endif
#if !defined DC_ANIMS_DISABLE__RAPPING
// Name: RAPPING, animations count: 8
	_Anim(RAPPING, Laugh_01),
	_Anim(RAPPING, RAP_A_IN),
	_Anim(RAPPING, RAP_A_Loop),
	_Anim(RAPPING, RAP_A_OUT),
	_Anim(RAPPING, RAP_B_IN),
	_Anim(RAPPING, RAP_B_Loop),
	_Anim(RAPPING, RAP_B_OUT),
	_Anim(RAPPING, RAP_C_Loop),
#endif
#if !defined DC_ANIMS_DISABLE__RIFLE
// Name: RIFLE, animations count: 5
	_Anim(RIFLE, RIFLE_crouchfire),
	_Anim(RIFLE, RIFLE_crouchload),
	_Anim(RIFLE, RIFLE_fire),
	_Anim(RIFLE, RIFLE_fire_poor),
	_Anim(RIFLE, RIFLE_load),
#endif
#if !defined DC_ANIMS_DISABLE__RIOT
// Name: RIOT, animations count: 7
	_Anim(RIOT, RIOT_ANGRY),
	_Anim(RIOT, RIOT_ANGRY_B),
	_Anim(RIOT, RIOT_challenge),
	_Anim(RIOT, RIOT_CHANT),
	_Anim(RIOT, RIOT_FUKU),
	_Anim(RIOT, RIOT_PUNCHES),
	_Anim(RIOT, RIOT_shout),
#endif
#if !defined DC_ANIMS_DISABLE__ROB_BANK
// Name: ROB_BANK, animations count: 5
	_Anim(ROB_BANK, CAT_Safe_End),
	_Anim(ROB_BANK, CAT_Safe_Open),
	_Anim(ROB_BANK, CAT_Safe_Open_O),
	_Anim(ROB_BANK, CAT_Safe_Rob),
	_Anim(ROB_BANK, SHP_HandsUp_Scr),
#endif
#if !defined DC_ANIMS_DISABLE__ROCKET
// Name: ROCKET, animations count: 5
	_Anim(ROCKET, idle_rocket),
	_Anim(ROCKET, RocketFire),
	_Anim(ROCKET, run_rocket),
	_Anim(ROCKET, walk_rocket),
	_Anim(ROCKET, WALK_start_rocket),
#endif
#if !defined DC_ANIMS_DISABLE__RUNNINGMAN
// Name: RUNNINGMAN, animations count: 33
	_Anim(RUNNINGMAN, Dance_B1),
	_Anim(RUNNINGMAN, Dance_B10),
	_Anim(RUNNINGMAN, Dance_B11),
	_Anim(RUNNINGMAN, Dance_B12),
	_Anim(RUNNINGMAN, Dance_B13),
	_Anim(RUNNINGMAN, Dance_B14),
	_Anim(RUNNINGMAN, Dance_B15),
	_Anim(RUNNINGMAN, Dance_B16),
	_Anim(RUNNINGMAN, Dance_B2),
	_Anim(RUNNINGMAN, Dance_B3),
	_Anim(RUNNINGMAN, Dance_B4),
	_Anim(RUNNINGMAN, Dance_B5),
	_Anim(RUNNINGMAN, Dance_B6),
	_Anim(RUNNINGMAN, Dance_B7),
	_Anim(RUNNINGMAN, Dance_B8),
	_Anim(RUNNINGMAN, Dance_B9),
	_Anim(RUNNINGMAN, Dance_G1),
	_Anim(RUNNINGMAN, Dance_G10),
	_Anim(RUNNINGMAN, Dance_G11),
	_Anim(RUNNINGMAN, Dance_G12),
	_Anim(RUNNINGMAN, Dance_G13),
	_Anim(RUNNINGMAN, Dance_G14),
	_Anim(RUNNINGMAN, Dance_G15),
	_Anim(RUNNINGMAN, Dance_G16),
	_Anim(RUNNINGMAN, Dance_G2),
	_Anim(RUNNINGMAN, Dance_G3),
	_Anim(RUNNINGMAN, Dance_G4),
	_Anim(RUNNINGMAN, Dance_G5),
	_Anim(RUNNINGMAN, Dance_G6),
	_Anim(RUNNINGMAN, Dance_G7),
	_Anim(RUNNINGMAN, Dance_G8),
	_Anim(RUNNINGMAN, Dance_G9),
	_Anim(RUNNINGMAN, dance_loop),
#endif
#if !defined DC_ANIMS_DISABLE__RUSTLER
// Name: RUSTLER, animations count: 5
	_Anim(RUSTLER, Plane_align_LHS),
	_Anim(RUSTLER, Plane_close),
	_Anim(RUSTLER, Plane_getin),
	_Anim(RUSTLER, Plane_getout),
	_Anim(RUSTLER, Plane_open),
#endif
#if !defined DC_ANIMS_DISABLE__RYDER
// Name: RYDER, animations count: 16
	_Anim(RYDER, RYD_Beckon_01),
	_Anim(RYDER, RYD_Beckon_02),
	_Anim(RYDER, RYD_Beckon_03),
	_Anim(RYDER, RYD_Die_PT1),
	_Anim(RYDER, RYD_Die_PT2),
	_Anim(RYDER, Van_Crate_L),
	_Anim(RYDER, Van_Crate_R),
	_Anim(RYDER, Van_Fall_L),
	_Anim(RYDER, Van_Fall_R),
	_Anim(RYDER, Van_Lean_L),
	_Anim(RYDER, Van_Lean_R),
	_Anim(RYDER, VAN_PickUp_E),
	_Anim(RYDER, VAN_PickUp_S),
	_Anim(RYDER, Van_Stand),
	_Anim(RYDER, Van_Stand_Crate),
	_Anim(RYDER, Van_Throw),
#endif
#if !defined DC_ANIMS_DISABLE__SCRATCHING
// Name: SCRATCHING, animations count: 12
	_Anim(SCRATCHING, scdldlp),
	_Anim(SCRATCHING, scdlulp),
	_Anim(SCRATCHING, scdrdlp),
	_Anim(SCRATCHING, scdrulp),
	_Anim(SCRATCHING, sclng_l),
	_Anim(SCRATCHING, sclng_r),
	_Anim(SCRATCHING, scmid_l),
	_Anim(SCRATCHING, scmid_r),
	_Anim(SCRATCHING, scshrtl),
	_Anim(SCRATCHING, scshrtr),
	_Anim(SCRATCHING, sc_ltor),
	_Anim(SCRATCHING, sc_rtol),
#endif
#if !defined DC_ANIMS_DISABLE__SEX
// Name: SEX, animations count: 20
	_Anim(SEX, SEX_1to2_P),
	_Anim(SEX, SEX_1to2_W),
	_Anim(SEX, SEX_1_Cum_P),
	_Anim(SEX, SEX_1_Cum_W),
	_Anim(SEX, SEX_1_Fail_P),
	_Anim(SEX, SEX_1_Fail_W),
	_Anim(SEX, SEX_1_P),
	_Anim(SEX, SEX_1_W),
	_Anim(SEX, SEX_2to3_P),
	_Anim(SEX, SEX_2to3_W),
	_Anim(SEX, SEX_2_Fail_P),
	_Anim(SEX, SEX_2_Fail_W),
	_Anim(SEX, SEX_2_P),
	_Anim(SEX, SEX_2_W),
	_Anim(SEX, SEX_3to1_P),
	_Anim(SEX, SEX_3to1_W),
	_Anim(SEX, SEX_3_Fail_P),
	_Anim(SEX, SEX_3_Fail_W),
	_Anim(SEX, SEX_3_P),
	_Anim(SEX, SEX_3_W),
#endif
#if !defined DC_ANIMS_DISABLE__SHAMAL
// Name: SHAMAL, animations count: 4
	_Anim(SHAMAL, SHAMAL_align),
	_Anim(SHAMAL, SHAMAL_getin_LHS),
	_Anim(SHAMAL, SHAMAL_getout_LHS),
	_Anim(SHAMAL, SHAMAL_open),
#endif
#if !defined DC_ANIMS_DISABLE__SHOP
// Name: SHOP, animations count: 25
	_Anim(SHOP, ROB_2Idle),
	_Anim(SHOP, ROB_Loop),
	_Anim(SHOP, ROB_Loop_Threat),
	_Anim(SHOP, ROB_Shifty),
	_Anim(SHOP, ROB_StickUp_In),
	_Anim(SHOP, SHP_Duck),
	_Anim(SHOP, SHP_Duck_Aim),
	_Anim(SHOP, SHP_Duck_Fire),
	_Anim(SHOP, SHP_Gun_Aim),
	_Anim(SHOP, SHP_Gun_Duck),
	_Anim(SHOP, SHP_Gun_Fire),
	_Anim(SHOP, SHP_Gun_Grab),
	_Anim(SHOP, SHP_Gun_Threat),
	_Anim(SHOP, SHP_HandsUp_Scr),
	_Anim(SHOP, SHP_Jump_Glide),
	_Anim(SHOP, SHP_Jump_Land),
	_Anim(SHOP, SHP_Jump_Launch),
	_Anim(SHOP, SHP_Rob_GiveCash),
	_Anim(SHOP, SHP_Rob_HandsUp),
	_Anim(SHOP, SHP_Rob_React),
	_Anim(SHOP, SHP_Serve_End),
	_Anim(SHOP, SHP_Serve_Idle),
	_Anim(SHOP, SHP_Serve_Loop),
	_Anim(SHOP, SHP_Serve_Start),
	_Anim(SHOP, Smoke_RYD),
#endif
#if !defined DC_ANIMS_DISABLE__SHOTGUN
// Name: SHOTGUN, animations count: 3
	_Anim(SHOTGUN, shotgun_crouchfire),
	_Anim(SHOTGUN, shotgun_fire),
	_Anim(SHOTGUN, shotgun_fire_poor),
#endif
#if !defined DC_ANIMS_DISABLE__SILENCED
// Name: SILENCED, animations count: 4
	_Anim(SILENCED, CrouchReload),
	_Anim(SILENCED, SilenceCrouchfire),
	_Anim(SILENCED, Silence_fire),
	_Anim(SILENCED, Silence_reload),
#endif
#if !defined DC_ANIMS_DISABLE__SKATE
// Name: SKATE, animations count: 3
	_Anim(SKATE, skate_idle),
	_Anim(SKATE, skate_run),
	_Anim(SKATE, skate_sprint),
#endif
#if !defined DC_ANIMS_DISABLE__SMOKING
// Name: SMOKING, animations count: 8
	_Anim(SMOKING, F_smklean_loop),
	_Anim(SMOKING, M_smklean_loop),
	_Anim(SMOKING, M_smkstnd_loop),
	_Anim(SMOKING, M_smk_drag),
	_Anim(SMOKING, M_smk_in),
	_Anim(SMOKING, M_smk_loop),
	_Anim(SMOKING, M_smk_out),
	_Anim(SMOKING, M_smk_tap),
#endif
#if !defined DC_ANIMS_DISABLE__SNIPER
// Name: SNIPER, animations count: 1
	_Anim(SNIPER, WEAPON_sniper),
#endif
#if !defined DC_ANIMS_DISABLE__SNM
// Name: SnM, animations count: 22
	_Anim(SnM, SnM_Caned_Idle_P),
	_Anim(SnM, SnM_Caned_Idle_W),
	_Anim(SnM, SnM_Caned_P),
	_Anim(SnM, SnM_Caned_W),
	_Anim(SnM, SnM_Cane_Idle_P),
	_Anim(SnM, SnM_Cane_Idle_W),
	_Anim(SnM, SnM_Cane_P),
	_Anim(SnM, SnM_Cane_W),
	_Anim(SnM, SpankedP),
	_Anim(SnM, SpankedW),
	_Anim(SnM, Spanked_IdleP),
	_Anim(SnM, Spanked_IdleW),
	_Anim(SnM, SpankingP),
	_Anim(SnM, SpankingW),
	_Anim(SnM, Spanking_endP),
	_Anim(SnM, Spanking_endW),
	_Anim(SnM, Spanking_IdleP),
	_Anim(SnM, Spanking_IdleW),
	_Anim(SnM, Spanking_SittingIdleP),
	_Anim(SnM, Spanking_SittingIdleW),
	_Anim(SnM, Spanking_SittingP),
	_Anim(SnM, Spanking_SittingW),
#endif
#if !defined DC_ANIMS_DISABLE__SPRAYCAN
// Name: SPRAYCAN, animations count: 2
	_Anim(SPRAYCAN, spraycan_fire),
	_Anim(SPRAYCAN, spraycan_full),
#endif
#if !defined DC_ANIMS_DISABLE__STRIP
// Name: STRIP, animations count: 20
	_Anim(STRIP, PLY_CASH),
	_Anim(STRIP, PUN_CASH),
	_Anim(STRIP, PUN_HOLLER),
	_Anim(STRIP, PUN_LOOP),
	_Anim(STRIP, strip_A),
	_Anim(STRIP, strip_B),
	_Anim(STRIP, strip_C),
	_Anim(STRIP, strip_D),
	_Anim(STRIP, strip_E),
	_Anim(STRIP, strip_F),
	_Anim(STRIP, strip_G),
	_Anim(STRIP, STR_A2B),
	_Anim(STRIP, STR_B2A),
	_Anim(STRIP, STR_B2C),
	_Anim(STRIP, STR_C1),
	_Anim(STRIP, STR_C2),
	_Anim(STRIP, STR_C2B),
	_Anim(STRIP, STR_Loop_A),
	_Anim(STRIP, STR_Loop_B),
	_Anim(STRIP, STR_Loop_C),
#endif
#if !defined DC_ANIMS_DISABLE__SUNBATHE
// Name: SUNBATHE, animations count: 18
	_Anim(SUNBATHE, batherdown),
	_Anim(SUNBATHE, batherup),
	_Anim(SUNBATHE, Lay_Bac_in),
	_Anim(SUNBATHE, Lay_Bac_out),
	_Anim(SUNBATHE, ParkSit_M_IdleA),
	_Anim(SUNBATHE, ParkSit_M_IdleB),
	_Anim(SUNBATHE, ParkSit_M_IdleC),
	_Anim(SUNBATHE, ParkSit_M_in),
	_Anim(SUNBATHE, ParkSit_M_out),
	_Anim(SUNBATHE, ParkSit_W_idleA),
	_Anim(SUNBATHE, ParkSit_W_idleB),
	_Anim(SUNBATHE, ParkSit_W_idleC),
	_Anim(SUNBATHE, ParkSit_W_in),
	_Anim(SUNBATHE, ParkSit_W_out),
	_Anim(SUNBATHE, SBATHE_F_LieB2Sit),
	_Anim(SUNBATHE, SBATHE_F_Out),
	_Anim(SUNBATHE, SitnWait_in_W),
	_Anim(SUNBATHE, SitnWait_out_W),
#endif
#if !defined DC_ANIMS_DISABLE__SWAT
// Name: SWAT, animations count: 23
	_Anim(SWAT, gnstwall_injurd),
	_Anim(SWAT, JMP_Wall1m_180),
	_Anim(SWAT, Rail_fall),
	_Anim(SWAT, Rail_fall_crawl),
	_Anim(SWAT, swt_breach_01),
	_Anim(SWAT, swt_breach_02),
	_Anim(SWAT, swt_breach_03),
	_Anim(SWAT, swt_go),
	_Anim(SWAT, swt_lkt),
	_Anim(SWAT, swt_sty),
	_Anim(SWAT, swt_vent_01),
	_Anim(SWAT, swt_vent_02),
	_Anim(SWAT, swt_vnt_sht_die),
	_Anim(SWAT, swt_vnt_sht_in),
	_Anim(SWAT, swt_vnt_sht_loop),
	_Anim(SWAT, swt_wllpk_L),
	_Anim(SWAT, swt_wllpk_L_back),
	_Anim(SWAT, swt_wllpk_R),
	_Anim(SWAT, swt_wllpk_R_back),
	_Anim(SWAT, swt_wllshoot_in_L),
	_Anim(SWAT, swt_wllshoot_in_R),
	_Anim(SWAT, swt_wllshoot_out_L),
	_Anim(SWAT, swt_wllshoot_out_R),
#endif
#if !defined DC_ANIMS_DISABLE__SWEET
// Name: SWEET, animations count: 7
	_Anim(SWEET, ho_ass_slapped),
	_Anim(SWEET, LaFin_Player),
	_Anim(SWEET, LaFin_Sweet),
	_Anim(SWEET, plyr_hndshldr_01),
	_Anim(SWEET, sweet_ass_slap),
	_Anim(SWEET, sweet_hndshldr_01),
	_Anim(SWEET, Sweet_injuredloop),
#endif
#if !defined DC_ANIMS_DISABLE__SWIM
// Name: SWIM, animations count: 7
	_Anim(SWIM, Swim_Breast),
	_Anim(SWIM, SWIM_crawl),
	_Anim(SWIM, Swim_Dive_Under),
	_Anim(SWIM, Swim_Glide),
	_Anim(SWIM, Swim_jumpout),
	_Anim(SWIM, Swim_Tread),
	_Anim(SWIM, Swim_Under),
#endif
#if !defined DC_ANIMS_DISABLE__SWORD
// Name: SWORD, animations count: 10
	_Anim(SWORD, sword_1),
	_Anim(SWORD, sword_2),
	_Anim(SWORD, sword_3),
	_Anim(SWORD, sword_4),
	_Anim(SWORD, sword_block),
	_Anim(SWORD, Sword_Hit_1),
	_Anim(SWORD, Sword_Hit_2),
	_Anim(SWORD, Sword_Hit_3),
	_Anim(SWORD, sword_IDLE),
	_Anim(SWORD, sword_part),
#endif
#if !defined DC_ANIMS_DISABLE__TANK
// Name: TANK, animations count: 6
	_Anim(TANK, TANK_align_LHS),
	_Anim(TANK, TANK_close_LHS),
	_Anim(TANK, TANK_doorlocked),
	_Anim(TANK, TANK_getin_LHS),
	_Anim(TANK, TANK_getout_LHS),
	_Anim(TANK, TANK_open_LHS),
#endif
#if !defined DC_ANIMS_DISABLE__TATTOOS
// Name: TATTOOS, animations count: 57
	_Anim(TATTOOS, TAT_ArmL_In_O),
	_Anim(TATTOOS, TAT_ArmL_In_P),
	_Anim(TATTOOS, TAT_ArmL_In_T),
	_Anim(TATTOOS, TAT_ArmL_Out_O),
	_Anim(TATTOOS, TAT_ArmL_Out_P),
	_Anim(TATTOOS, TAT_ArmL_Out_T),
	_Anim(TATTOOS, TAT_ArmL_Pose_O),
	_Anim(TATTOOS, TAT_ArmL_Pose_P),
	_Anim(TATTOOS, TAT_ArmL_Pose_T),
	_Anim(TATTOOS, TAT_ArmR_In_O),
	_Anim(TATTOOS, TAT_ArmR_In_P),
	_Anim(TATTOOS, TAT_ArmR_In_T),
	_Anim(TATTOOS, TAT_ArmR_Out_O),
	_Anim(TATTOOS, TAT_ArmR_Out_P),
	_Anim(TATTOOS, TAT_ArmR_Out_T),
	_Anim(TATTOOS, TAT_ArmR_Pose_O),
	_Anim(TATTOOS, TAT_ArmR_Pose_P),
	_Anim(TATTOOS, TAT_ArmR_Pose_T),
	_Anim(TATTOOS, TAT_Back_In_O),
	_Anim(TATTOOS, TAT_Back_In_P),
	_Anim(TATTOOS, TAT_Back_In_T),
	_Anim(TATTOOS, TAT_Back_Out_O),
	_Anim(TATTOOS, TAT_Back_Out_P),
	_Anim(TATTOOS, TAT_Back_Out_T),
	_Anim(TATTOOS, TAT_Back_Pose_O),
	_Anim(TATTOOS, TAT_Back_Pose_P),
	_Anim(TATTOOS, TAT_Back_Pose_T),
	_Anim(TATTOOS, TAT_Back_Sit_In_P),
	_Anim(TATTOOS, TAT_Back_Sit_Loop_P),
	_Anim(TATTOOS, TAT_Back_Sit_Out_P),
	_Anim(TATTOOS, TAT_Bel_In_O),
	_Anim(TATTOOS, TAT_Bel_In_T),
	_Anim(TATTOOS, TAT_Bel_Out_O),
	_Anim(TATTOOS, TAT_Bel_Out_T),
	_Anim(TATTOOS, TAT_Bel_Pose_O),
	_Anim(TATTOOS, TAT_Bel_Pose_T),
	_Anim(TATTOOS, TAT_Che_In_O),
	_Anim(TATTOOS, TAT_Che_In_P),
	_Anim(TATTOOS, TAT_Che_In_T),
	_Anim(TATTOOS, TAT_Che_Out_O),
	_Anim(TATTOOS, TAT_Che_Out_P),
	_Anim(TATTOOS, TAT_Che_Out_T),
	_Anim(TATTOOS, TAT_Che_Pose_O),
	_Anim(TATTOOS, TAT_Che_Pose_P),
	_Anim(TATTOOS, TAT_Che_Pose_T),
	_Anim(TATTOOS, TAT_Drop_O),
	_Anim(TATTOOS, TAT_Idle_Loop_O),
	_Anim(TATTOOS, TAT_Idle_Loop_T),
	_Anim(TATTOOS, TAT_Sit_In_O),
	_Anim(TATTOOS, TAT_Sit_In_P),
	_Anim(TATTOOS, TAT_Sit_In_T),
	_Anim(TATTOOS, TAT_Sit_Loop_O),
	_Anim(TATTOOS, TAT_Sit_Loop_P),
	_Anim(TATTOOS, TAT_Sit_Loop_T),
	_Anim(TATTOOS, TAT_Sit_Out_O),
	_Anim(TATTOOS, TAT_Sit_Out_P),
	_Anim(TATTOOS, TAT_Sit_Out_T),
#endif
#if !defined DC_ANIMS_DISABLE__TEC
// Name: TEC, animations count: 4
	_Anim(TEC, TEC_crouchfire),
	_Anim(TEC, TEC_crouchreload),
	_Anim(TEC, TEC_fire),
	_Anim(TEC, TEC_reload),
#endif
#if !defined DC_ANIMS_DISABLE__TRAIN
// Name: TRAIN, animations count: 4
	_Anim(TRAIN, tran_gtup),
	_Anim(TRAIN, tran_hng),
	_Anim(TRAIN, tran_ouch),
	_Anim(TRAIN, tran_stmb),
#endif
#if !defined DC_ANIMS_DISABLE__TRUCK
// Name: TRUCK, animations count: 17
	_Anim(TRUCK, TRUCK_ALIGN_LHS),
	_Anim(TRUCK, TRUCK_ALIGN_RHS),
	_Anim(TRUCK, TRUCK_closedoor_LHS),
	_Anim(TRUCK, TRUCK_closedoor_RHS),
	_Anim(TRUCK, TRUCK_close_LHS),
	_Anim(TRUCK, TRUCK_close_RHS),
	_Anim(TRUCK, TRUCK_getin_LHS),
	_Anim(TRUCK, TRUCK_getin_RHS),
	_Anim(TRUCK, TRUCK_getout_LHS),
	_Anim(TRUCK, TRUCK_getout_RHS),
	_Anim(TRUCK, TRUCK_jackedLHS),
	_Anim(TRUCK, TRUCK_jackedRHS),
	_Anim(TRUCK, TRUCK_open_LHS),
	_Anim(TRUCK, TRUCK_open_RHS),
	_Anim(TRUCK, TRUCK_pullout_LHS),
	_Anim(TRUCK, TRUCK_pullout_RHS),
	_Anim(TRUCK, TRUCK_Shuffle),
#endif
#if !defined DC_ANIMS_DISABLE__UZI
// Name: UZI, animations count: 5
	_Anim(UZI, UZI_crouchfire),
	_Anim(UZI, UZI_crouchreload),
	_Anim(UZI, UZI_fire),
	_Anim(UZI, UZI_fire_poor),
	_Anim(UZI, UZI_reload),
#endif
#if !defined DC_ANIMS_DISABLE__VAN
// Name: VAN, animations count: 8
	_Anim(VAN, VAN_close_back_LHS),
	_Anim(VAN, VAN_close_back_RHS),
	_Anim(VAN, VAN_getin_Back_LHS),
	_Anim(VAN, VAN_getin_Back_RHS),
	_Anim(VAN, VAN_getout_back_LHS),
	_Anim(VAN, VAN_getout_back_RHS),
	_Anim(VAN, VAN_open_back_LHS),
	_Anim(VAN, VAN_open_back_RHS),
#endif
#if !defined DC_ANIMS_DISABLE__VENDING
// Name: VENDING, animations count: 6
	_Anim(VENDING, VEND_Drink2_P),
	_Anim(VENDING, VEND_Drink_P),
	_Anim(VENDING, vend_eat1_P),
	_Anim(VENDING, VEND_Eat_P),
	_Anim(VENDING, VEND_Use),
	_Anim(VENDING, VEND_Use_pt2),
#endif
#if !defined DC_ANIMS_DISABLE__VORTEX
// Name: VORTEX, animations count: 4
	_Anim(VORTEX, CAR_jumpin_LHS),
	_Anim(VORTEX, CAR_jumpin_RHS),
	_Anim(VORTEX, vortex_getout_LHS),
	_Anim(VORTEX, vortex_getout_RHS),
#endif
#if !defined DC_ANIMS_DISABLE__WAYFARER
// Name: WAYFARER, animations count: 18
	_Anim(WAYFARER, WF_Back),
	_Anim(WAYFARER, WF_drivebyFT),
	_Anim(WAYFARER, WF_drivebyLHS),
	_Anim(WAYFARER, WF_drivebyRHS),
	_Anim(WAYFARER, WF_Fwd),
	_Anim(WAYFARER, WF_getoffBACK),
	_Anim(WAYFARER, WF_getoffLHS),
	_Anim(WAYFARER, WF_getoffRHS),
	_Anim(WAYFARER, WF_hit),
	_Anim(WAYFARER, WF_jumponL),
	_Anim(WAYFARER, WF_jumponR),
	_Anim(WAYFARER, WF_kick),
	_Anim(WAYFARER, WF_Left),
	_Anim(WAYFARER, WF_passenger),
	_Anim(WAYFARER, WF_pushes),
	_Anim(WAYFARER, WF_Ride),
	_Anim(WAYFARER, WF_Right),
	_Anim(WAYFARER, WF_Still),
#endif
#if !defined DC_ANIMS_DISABLE__WEAPONS
// Name: WEAPONS, animations count: 17
	_Anim(WEAPONS, SHP_1H_Lift),
	_Anim(WEAPONS, SHP_1H_Lift_End),
	_Anim(WEAPONS, SHP_1H_Ret),
	_Anim(WEAPONS, SHP_1H_Ret_S),
	_Anim(WEAPONS, SHP_2H_Lift),
	_Anim(WEAPONS, SHP_2H_Lift_End),
	_Anim(WEAPONS, SHP_2H_Ret),
	_Anim(WEAPONS, SHP_2H_Ret_S),
	_Anim(WEAPONS, SHP_Ar_Lift),
	_Anim(WEAPONS, SHP_Ar_Lift_End),
	_Anim(WEAPONS, SHP_Ar_Ret),
	_Anim(WEAPONS, SHP_Ar_Ret_S),
	_Anim(WEAPONS, SHP_G_Lift_In),
	_Anim(WEAPONS, SHP_G_Lift_Out),
	_Anim(WEAPONS, SHP_Tray_In),
	_Anim(WEAPONS, SHP_Tray_Out),
	_Anim(WEAPONS, SHP_Tray_Pose),
#endif
#if !defined DC_ANIMS_DISABLE__WOP
// Name: WOP, animations count: 33
	_Anim(WOP, Dance_B1),
	_Anim(WOP, Dance_B10),
	_Anim(WOP, Dance_B11),
	_Anim(WOP, Dance_B12),
	_Anim(WOP, Dance_B13),
	_Anim(WOP, Dance_B14),
	_Anim(WOP, Dance_B15),
	_Anim(WOP, Dance_B16),
	_Anim(WOP, Dance_B2),
	_Anim(WOP, Dance_B3),
	_Anim(WOP, Dance_B4),
	_Anim(WOP, Dance_B5),
	_Anim(WOP, Dance_B6),
	_Anim(WOP, Dance_B7),
	_Anim(WOP, Dance_B8),
	_Anim(WOP, Dance_B9),
	_Anim(WOP, Dance_G1),
	_Anim(WOP, Dance_G10),
	_Anim(WOP, Dance_G11),
	_Anim(WOP, Dance_G12),
	_Anim(WOP, Dance_G13),
	_Anim(WOP, Dance_G14),
	_Anim(WOP, Dance_G15),
	_Anim(WOP, Dance_G16),
	_Anim(WOP, Dance_G2),
	_Anim(WOP, Dance_G3),
	_Anim(WOP, Dance_G4),
	_Anim(WOP, Dance_G5),
	_Anim(WOP, Dance_G6),
	_Anim(WOP, Dance_G7),
	_Anim(WOP, Dance_G8),
	_Anim(WOP, Dance_G9),
	_Anim(WOP, dance_loop),
#endif
#if !defined DC_ANIMS_DISABLE__WUZI
// Name: WUZI, animations count: 12
	_Anim(WUZI, CS_Dead_Guy),
	_Anim(WUZI, CS_Plyr_pt1),
	_Anim(WUZI, CS_Plyr_pt2),
	_Anim(WUZI, CS_Wuzi_pt1),
	_Anim(WUZI, CS_Wuzi_pt2),
	_Anim(WUZI, Walkstart_Idle_01),
	_Anim(WUZI, Wuzi_follow),
	_Anim(WUZI, Wuzi_Greet_Plyr),
	_Anim(WUZI, Wuzi_Greet_Wuzi),
	_Anim(WUZI, Wuzi_grnd_chk),
	_Anim(WUZI, Wuzi_stand_loop),
	_Anim(WUZI, Wuzi_Walk),
#endif
#if !defined DC_ANIMS_DISABLE__SAMP
// Name: SAMP, animations count: 1
	_Anim(SAMP, FishingIdle),
#endif
	{DC_ANIMS__INVALID_ANIMLIB_ID, {""}}
};

#undef	_Anim
#undef	_AnimLib


static dc_anims__preload_status[MAX_PLAYERS char];
static dc_anims__init_status = 0;

static stock dc_anims__PreloadLibraries(playerid)
{
	if (dc_anims__preload_status{playerid} == 0)
	{
		static i;
		for (i = 0; i < sizeof(dc_anims__libs) - 1; ++i)
			ApplyAnimation(
				playerid, dc_anims__libs[i][eAnimLib_Name], !"zzz",
				4.1, 0, 0, 0, 0, 1, 1
			);
		dc_anims__preload_status{playerid} = 1;
	}
	return 1;
}

#if !defined DC_ANIMS__NO_PRELOAD_AT_SPAWN
public OnPlayerSpawn(playerid)
{
	// Preload all animation libraries.
	dc_anims__PreloadLibraries(playerid);
#if	defined	dc_anims__OnPlayerSpawn
	dc_anims__OnPlayerSpawn(playerid);
#endif
	return 1;
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn dc_anims__OnPlayerSpawn
#if defined dc_anims__OnPlayerSpawn
	forward dc_anims__OnPlayerSpawn(playerid);
#endif
#endif // !defined DC_ANIMS__NO_PRELOAD_AT_SPAWN

public OnPlayerDisconnect(playerid, reason)
{
	dc_anims__preload_status{playerid} = 0;
#if	defined	dc_anims__OnPlayerDisconnect
	dc_anims__OnPlayerDisconnect(playerid, reason);
#endif
	return 1;
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect dc_anims__OnPlayerDisconnect
#if defined dc_anims__OnPlayerDisconnect
	forward dc_anims__OnPlayerDisconnect(playerid, reason);
#endif

static dc_anims__Initialize()
{
	static i;
#if !defined DC_ANIMS__NO_PRELOAD_AT_SPAWN
	i = GetPlayerPoolSize();
	do
	{
		if (IsPlayerConnected(i))
			dc_anims__PreloadLibraries(i);
	}
	while (i-- != 0);
#endif
	static j;
	// Convert the names of all animation libraries to lowercase.
	{
		static k, c[1], break_flag;
		for (i = 0; i < sizeof(dc_anims__libs) - 1; ++i)
		{
			break_flag = 0;
			for (j = 0; ; ++j)
			{
				c[0] = dc_anims__libs[i][eAnimLib_Name][j];
				for (k = 0; k < sizeof(c) * (cellbits / charbits); ++k)
				{
					if ('A' <= c{k} <= 'Z')
					{
						c{k} += 'a'-'A';
					}
					else if (c{k} == '\0')
					{
						break_flag = 1;
						break;
					}
				}
				dc_anims__libs[i][eAnimLib_Name][j] = c[0];
				if (break_flag)
					break;
			}
		}
	}
	static cur_animlib_id;
	cur_animlib_id = DC_ANIMS__INVALID_ANIMLIB_ID;
	goto skip_init__cur_animlib_name;
	new cur_animlib_name[MAX_ANIM_LIB_NAME+1];
skip_init__cur_animlib_name:
	cur_animlib_name[0] = '\0';
	for (i = 0; ; ++i)
	{
		if (i == sizeof(dc_anims__info) - 1)
		{
			if (cur_animlib_id != DC_ANIMS__INVALID_ANIMLIB_ID)
				dc_anims__libs[cur_animlib_id][eAnimLib_LastAnim] = i - 1;
			break;
		}
		if (dc_anims__info[i][eAnim_LibID] != cur_animlib_id)
		{
			if (cur_animlib_id != DC_ANIMS__INVALID_ANIMLIB_ID)
				dc_anims__libs[cur_animlib_id][eAnimLib_LastAnim] = i - 1;
			cur_animlib_id = dc_anims__info[i][eAnim_LibID];
			if ((cur_animlib_id == sizeof(dc_anims__libs) - 1)
			||  (dc_anims__libs[cur_animlib_id][eAnimLib_FirstAnim] != -1))
			{
#if defined DC_ANIMS_LANG_EN
				print(!"dc_anims.inc: Invalid animations table");
#else // LANG = RU
				print(!"dc_anims.inc: Неправильная таблица анимаций");
#endif
				return 0;
			}
			cur_animlib_name[0] = '\0';
			strcat(
				cur_animlib_name, dc_anims__libs[cur_animlib_id][eAnimLib_Name]
			);
			dc_anims__libs[cur_animlib_id][eAnimLib_FirstAnim] = i;
		}
	}
	dc_anims__init_status = 1;
	return 1;
}

public OnGameModeInit()
{
	dc_anims__Initialize();
#if	defined	dc_anims__OnGameModeInit
	dc_anims__OnGameModeInit();
#endif
	return 1;
}
#if	defined	_ALS_OnGameModeInit
	#undef	OnGameModeInit
#else
	#define	_ALS_OnGameModeInit
#endif
#define	OnGameModeInit	dc_anims__OnGameModeInit
#if	defined	dc_anims__OnGameModeInit
	forward dc_anims__OnGameModeInit();
#endif

public OnFilterScriptInit()
{
	dc_anims__Initialize();
#if	defined	dc_anims__OnFilterScriptInit
	dc_anims__OnFilterScriptInit();
#endif
	return 1;
}
#if	defined	_ALS_OnFilterScriptInit
	#undef	OnFilterScriptInit
#else
	#define	_ALS_OnFilterScriptInit
#endif
#define	OnFilterScriptInit	dc_anims__OnFilterScriptInit
#if	defined	dc_anims__OnFilterScriptInit
	forward dc_anims__OnFilterScriptInit();
#endif


dc_anims__command:anim(playerid, params[])
{
#if defined DC_ANIMS_LANG_EN
	static const str_initialization_error[] =
		!DC_ANIMS_ERROR_COLOR"Error: Invalid animations table!";
#else // LANG = RU
	static const str_initialization_error[] =
		!DC_ANIMS_ERROR_COLOR"Ошибка: Неправильная таблица анимаций!";
#endif
	if (dc_anims__init_status == 0)
		return SendClientMessage(playerid, -1, str_initialization_error);
	// Display the help message if parameters are empty.
	if (isnull(params))
	{
	#if defined DC_ANIMS_LANG_EN
		static const str_usage[] =
			!DC_ANIMS_COLOR"Usage: {ffffff}/anim [animlib] [animation ID]";
		static const str_animation_libs[] =
			DC_ANIMS_COLOR"Animation libraries:{ffffff}";
		static const str_total_anims[] =
			DC_ANIMS_COLOR"Total: {ffffff}%d animations in %d libraries.";
	#else // LANG = RU
		static const str_usage[] =
			!DC_ANIMS_COLOR"Использование: {ffffff}/anim [набор] [ID анимации]";
		static const str_animation_libs[] =
			DC_ANIMS_COLOR"Доступные наборы:{ffffff}";
		static const str_total_anims[] =
			DC_ANIMS_COLOR"Итого: {ffffff}%d анимаций в %d наборах.";
	#endif
		SendClientMessage(playerid, -1, str_usage);
list_animlibs:
		// List all animation libraries (dynamic systems are so dynamic...)
		// Also add the length of 2 embedded color specifiers ('{rrggbb}').
		goto skip_init__string;
		new string[144 + 1];
	skip_init__string:
		string = str_animation_libs;
		static len, i;
		len = sizeof(str_animation_libs)-1;
		for (i = 0; ; )
		{
			if (strlen(dc_anims__libs[i][eAnimLib_Name]) > sizeof(string) - len)
			{
				SendClientMessage(playerid, -1, string);
				len = strunpack(string, dc_anims__libs[i][eAnimLib_Name]);
			}
			else
			{
				if (i != 0)
					string[len++] = ',';
				string[len++] = ' ';
				string[len] = ' ';	// For some reason strunpack
									// won't work without this.
				len += strunpack(
					string[len], dc_anims__libs[i][eAnimLib_Name],
					sizeof(string)-len
				);
			}
			if (++i == sizeof(dc_anims__libs) - 1)
			{
				SendClientMessage(playerid, -1, string);
				break;
			}
		}
		format(	string, sizeof(string), str_total_anims,
				sizeof(dc_anims__info) - 1, sizeof(dc_anims__libs) - 1);
		return SendClientMessage(playerid, -1, string);
	}
	// Get the animation library name.
	static pos, animlib_id, sep_char;
	pos = 0;
	while (params[++pos] > ' ') {}
	// There is no animation library with a name shorter than 3 symbols
	// so there's no point in searching for it.
	if (pos < 3)
		goto unknown_animlib;
	// Remember the separating character to check if it's '\0' later.
	sep_char = params[pos];
	// Write '\0' at the position of the first separating character
	// so there will be a '\0'-terminated string with the animation name.
	params[pos] = '\0';
	// Find the name in the list.
	for (animlib_id = 0; animlib_id < sizeof(dc_anims__libs) - 1; ++animlib_id)
		if (0 == strcmp(params, dc_anims__libs[animlib_id][eAnimLib_Name]))
			goto found_animlib;
	// The 'if' statement below is pretty much useless.  The only reason
	// it's here is to suppress the "unreachable code" warning.
	if (animlib_id == sizeof(dc_anims__libs) - 1)
	{
unknown_animlib:
	#if defined DC_ANIMS_LANG_EN
		static const str_unknown_animlib[] =
			!DC_ANIMS_ERROR_COLOR"Unknown library name.";
	#else // LANG = RU
		static const str_unknown_animlib[] =
			!DC_ANIMS_ERROR_COLOR"Неизвестное название библиотеки.";
	#endif
		SendClientMessage(playerid, -1, str_unknown_animlib);
		goto list_animlibs;
	}
found_animlib:
	// There's no more parameters if the first separating character was '\0'.
	if (sep_char == '\0')
		goto invalid_anim_id;
	while (params[++pos] == ' ') {}
	if (params[pos] == '\0' || !('0' <= params[pos] <= '9'))
		goto invalid_anim_id;
	static i;
	for (i = pos+1; ; ++i)
	{
		if (params[i] == '\0')
			goto valid_anim_id;
		if (!('0' <= params[i] <= '9'))
			goto invalid_anim_id;
	}
	if (pos != 0) // Just to suppress the "unreachable code" warning.
	{
invalid_anim_id:
	#if defined DC_ANIMS_LANG_EN
		static const str_no_animid[] =
			DC_ANIMS_COLOR"Usage: {ffffff}/anim %s [1-%d]";
	#else // LANG = RU
		static const str_no_animid[] =
			DC_ANIMS_COLOR"Использование: {ffffff}/anim %s [1-%d]";
	#endif
		goto skip_init__string2;
		new string[sizeof(str_no_animid)-2+MAX_ANIM_LIB_NAME-2+3];
	skip_init__string2:
		strunpack(string, dc_anims__libs[animlib_id][eAnimLib_Name]);
		format(	string, sizeof(string), str_no_animid,
				string,
				dc_anims__libs[animlib_id][eAnimLib_LastAnim]
				-dc_anims__libs[animlib_id][eAnimLib_FirstAnim]+1);
		return SendClientMessage(playerid, -1, string);
	}
valid_anim_id:
	static anim_id;
	anim_id =
		dc_anims__libs[animlib_id][eAnimLib_FirstAnim] +
		(strval(params[pos]) - 1);
	if (anim_id < dc_anims__libs[animlib_id][eAnimLib_FirstAnim]
	||  anim_id > dc_anims__libs[animlib_id][eAnimLib_LastAnim])
	{
	#if defined DC_ANIMS_LANG_EN
		static const str_invalid_animid[] =
			DC_ANIMS_ERROR_COLOR"Invalid animation ID!";
	#else // LANG = RU
		static const str_invalid_animid[] =
			DC_ANIMS_ERROR_COLOR"Неправильный ID анимации!";
	#endif
		SendClientMessage(playerid, -1, str_invalid_animid);
		goto invalid_anim_id;
	}
	return ApplyAnimation(	playerid,
							dc_anims__libs[animlib_id][eAnimLib_Name],
							dc_anims__info[anim_id][eAnim_Name],
							4.1, 0, 1, 1, 1, 1);
}


dc_anims__command:stopanim(playerid, params[])
{
	#pragma	unused	params
	return ApplyAnimation(playerid,!"BD_FIRE",!"BD_FIRE1",8.2,0,0,0,0,1,1);
}

#if !defined DC_ANIMS_DISABLE_ACTIONS

#define _Action(%0,%1)	{{!#%1}, SPECIAL_ACTION_%0}

enum e_ACTION_INFO
{
	eAction_Name[(MAX_ACTION_NAME+1)/(cellbits/charbits)],
	eAction_Value
};

static const dc_anims__actions[][e_ACTION_INFO] =
{
	_Action(DANCE1,			dance1),
	_Action(DANCE2,			dance2),
	_Action(DANCE3,			dance3),
	_Action(DANCE4,			dance4),
	_Action(DRINK_BEER,		beer),
	_Action(DRINK_SPRUNK,	sprunk),
	_Action(DRINK_WINE,		wine),
	_Action(PISSING,		pee),
	_Action(SMOKE_CIGGY,	smoke)
};

#undef	_Action

dc_anims__command:action(playerid, params[])
{
	static i, len, action_id;
	if (isnull(params))
	{
	#if defined DC_ANIMS_LANG_EN
		static const str_incorrect_params[] =
			!DC_ANIMS_COLOR"Usage: {ffffff}/action [special action]";
		static const str_available_actions[] =
			DC_ANIMS_COLOR"Available actions:{ffffff}";
	#else // LANG = RU
		static const str_incorrect_params[] =
			!DC_ANIMS_COLOR"Использование: {ffffff}/action [действие]";
		static const str_available_actions[] =
			DC_ANIMS_COLOR"Доступные действия:{ffffff}";
	#endif
		SendClientMessage(playerid, -1, str_incorrect_params);
available_actions:
		// List all the actions in the same way as in /anim.
		goto skip_init__string;
		new string[144 + 1];
	skip_init__string:
		string = str_available_actions;
		len = sizeof(str_available_actions)-1;
		for (i = 0; ; )
		{
			if (strlen(dc_anims__actions[i][eAction_Name]) > sizeof(string)-len)
			{
				SendClientMessage(playerid, -1, string);
				len = strunpack(string, dc_anims__actions[i][eAction_Name]);
			}
			else
			{
				if (i != 0)
					string[len++] = ',';
				string[len++] = ' ';
				string[len] = ' ';
				len += strunpack(
					string[len], dc_anims__actions[i][eAction_Name],
					sizeof(string) - len
				);
			}
			if (++i == sizeof(dc_anims__actions))
			{
				SendClientMessage(playerid, -1, string);
				break;
			}
		}
		return 1;
	}
	// There is no action with name shorter than 3 symbols
	// so there's no point in searching for it.
	for (i = 1; params[i] != '\0'; ++i) {}
	if (i < 3)
	{
incorrect_action_name:
	#if defined DC_ANIMS_LANG_EN
		static const str_incorrect_action[] =
			!DC_ANIMS_ERROR_COLOR"Incorrect action name!";
	#else // LANG = RU
		static const str_incorrect_action[] =
			!DC_ANIMS_ERROR_COLOR"Неизвестное название действия!";
	#endif
		SendClientMessage(playerid, -1, str_incorrect_action);
		goto available_actions;
	}
	action_id = 0;
	for ( ; action_id < sizeof(dc_anims__actions); ++action_id)
		if (0 == strcmp(params, dc_anims__actions[action_id][eAction_Name]))
			goto found_action;
	if (action_id == sizeof(dc_anims__actions))
		goto incorrect_action_name;
found_action:
	return SetPlayerSpecialAction(
		playerid,
		dc_anims__actions[action_id][eAction_Value]
	);
}

#endif	//#if !defined DC_ANIMS_DISABLE_ACTIONS

#if !defined CMD

public OnPlayerCommandText(playerid, cmdtext[])
{
	static params_pos, i, j;
#if defined dc_anims__OnPlayerCommandText
	static cmd_end;
	cmd_end = 0;
#endif
	// Process the command.
	params_pos = 0;
	for (i = 0;;)
	{
		switch (cmdtext[++i])
		{
			case '\0':
			{
				params_pos = i;
				break;
			}
			case ' ':
			{
				// Remove excessive space characters at the end of cmdtext.
				j = strlen(cmdtext);
				while (cmdtext[--j] == ' ') {}
				cmdtext[j+1] = '\0';
				// Separate the command from its parameters.
				cmdtext[i] = '\0';
#if defined dc_anims__OnPlayerCommandText
				cmd_end = i;
#endif
				while (cmdtext[++i] == ' '){}
				params_pos = i;
				break;
			}
		}
	}
	// Find a matching command and call it.
	new tmp[144+1];
	format(tmp, sizeof(tmp), "command: '%s', arguments: '%s'", cmdtext, cmdtext[params_pos]);
	SendClientMessage(playerid, -1, tmp);
	if (0 == strcmp(cmdtext, "/anim"))
		return dc_anims__command_anim(playerid, cmdtext[params_pos]);
	if (0 == strcmp(cmdtext, "/stopanim"))
		return dc_anims__command_stopanim(playerid, cmdtext[params_pos]);
#if !defined DC_ANIMS_DISABLE_ACTIONS
	if (0 == strcmp(cmdtext, "/action"))
		return dc_anims__command_action(playerid, cmdtext[params_pos]);
#endif
#if	defined	dc_anims__OnPlayerCommandText
	// Restore the ' ' character between the command and its parameters.
	if (cmd_end != 0)
		cmdtext[cmd_end] = ' ';
	// Call the original OPCT.
	return dc_anims__OnPlayerCommandText(playerid, cmdtext);
#else
	return 1;
#endif
}
#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#if defined dc_anims__OnPlayerCommandText
	forward dc_anims__OnPlayerCommandText(playerid, cmdtext[]);
#endif
#define	OnPlayerCommandText dc_anims__OnPlayerCommandText

#endif	//#if !defined CMD
