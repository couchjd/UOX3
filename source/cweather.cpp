//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  cweather.cpp
//
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  This File is part of UOX3
//  Ultima Offline eXperiment III
//  UO Server Emulation Program
//  
//  Copyright 1997 - 2001 by Marcus Rating (Cironian)
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//	
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//   
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

#include "uox3.h"

cWeatherAb::cWeatherAb()
{
}

cWeatherAb::~cWeatherAb()
{
  delete[] weather;
}

bool cWeatherAb::load( void )
// PRE:		weather has not been loaded
// POST:	weather has been loaded
{
	int i=0;
	weathID wthCount = 0;
	bool done = false;
	openscript("weatherab.scp");
	printf("Loading weather system now!\n");
	char sect[512];
	while ( !done )
	{
		sprintf(sect, "WEATHERAB %d", wthCount);
		if (!i_scripts[weathab_script]->find(sect))
		{
			done = true;
		}
		else
			wthCount++;
	}
	weathCount = wthCount;
	weather = new weatherSys[weathCount];

	for( i=0; i < weathCount; i++ )
	{
		sprintf(sect, "WEATHERAB %d", i);

		setColdIntensity( i, 0 );
		setHeatIntensity( i, 0 );
		setRainIntensity( i, 0 );
		setSnowIntensity( i, 0 );
		setColdChance( i, 5 );
		setRainChance( i, 10 );
		setSnowChance( i, 1 );
		setHeatChance( i, 10 );

		setMaxTemp( i, 30 );
		setMinTemp( i, 0 );
		setTemp( i, 15 );
		setMaxWindSpeed( i, 0 );
		setMinWindSpeed( i, 0 );
		setWindSpeed( i, 0 );
		setSnowThreshold( i, 15 );

		i_scripts[weathab_script]->find(sect);

		do {
			read2();

			if(!(strcmp("RAINCHANCE",script1)))	// are we affected by light?
				setRainChance( i, str2num( script2 ) );
			else if(!(strcmp("RAININTENSITY",script1)))	// how much damage to take from light
				setRainIntensity( i, str2num( script2 ) );

			else if(!(strcmp("SNOWCHANCE",script1)))	// are we affected by light?
				setSnowChance( i, str2num( script2 ) );
			else if(!(strcmp("SNOWINTENSITY",script1)))	// how much damage to take from light
				setSnowIntensity( i, str2num( script2 ) );
			else if(!(strcmp("SNOWTHRESHOLD", script1)))
				setSnowThreshold( i, (float)str2num( script2 ) );

			else if(!(strcmp("HEATCHANCE",script1)))	// are we affected by light?
				setHeatChance( i, str2num( script2 ) );
			else if(!(strcmp("HEATINTENSITY",script1)))	// how much damage to take from light
				setHeatIntensity( i, str2num( script2 ) );

			else if(!(strcmp("COLDCHANCE",script1)))	// are we affected by light?
				setColdChance( i, str2num( script2 ) );
			else if(!(strcmp("COLDINTENSITY",script1)))	// how much damage to take from light
				setColdIntensity( i, str2num( script2 ) );

			else if(!(strcmp("MAXTEMP",script1)))	// are we affected by light?
				setMaxTemp( i, (float)str2num( script2 ) );
			else if(!(strcmp("MINTEMP",script1)))	// how much damage to take from light
				setMinTemp( i, (float)str2num( script2 ) );

			else if(!(strcmp("MAXWIND",script1)))	// are we affected by light?
				setMaxWindSpeed( i, (float)str2num( script2 ) );
			else if(!(strcmp("MINWIND",script1)))	// how much damage to take from light
				setMinWindSpeed( i, (float)str2num( script2 ) );
			
		} while(script1[0]!='}');


	}
	closescript();
	return true;
}

char cWeatherAb::getIntensity( weathID toCheck, unsigned char weathType )
// PRE:		toCheck is valid, weathType is valid
// POST:	returns intensity of weathType in toCheck system
{
	return weather[toCheck].weathIntensity[weathType];
}
		
void cWeatherAb::setIntensity( weathID toCheck, unsigned char weathType, char value )
// PRE:		toCheck is valid, weathType is valid, value is valid
// POST:	intensity of weathType in toCheck is value
{
	weather[toCheck].weathIntensity[weathType] = value;
}

char cWeatherAb::getChance( weathID toCheck, unsigned char weathType )
// PRE:		toCheck is valid, weathType is valid
// POST:	returns intensity of weathType in toCheck system
{
	return weather[toCheck].weathChance[weathType];
}
		
void cWeatherAb::setChance( weathID toCheck, unsigned char weathType, char value )
// PRE:		toCheck is valid, weathType is valid, value is valid
// POST:	intensity of weathType in toCheck is value
{
	weather[toCheck].weathChance[weathType] = value;
}

float cWeatherAb::getValue( weathID toCheck, unsigned char valType, unsigned char valOff )
// PRE:		toCheck is valid, valType is valid, valOff is valid
// POST:	returns value of valType and valOff in toCheck
{
	return weather[toCheck].assortVals[valType][valOff];
}

void cWeatherAb::setValue( weathID toCheck, unsigned char valType, unsigned char valOff, float value )
// PRE:		toCheck is valid, valType and valOff is valid, value is valid
// POST:	value of valType and valOff in toCheck is value
{
	weather[toCheck].assortVals[valType][valOff] = value;
}

char cWeatherAb::getSnowIntensity( weathID toCheck )
{
	return getIntensity( toCheck, SNOW );
}

char cWeatherAb::getRainIntensity( weathID toCheck )
{
	return getIntensity( toCheck, RAIN );
}

char cWeatherAb::getHeatIntensity( weathID toCheck )
{
	return getIntensity( toCheck, HEAT );
}

char cWeatherAb::getColdIntensity( weathID toCheck )
{
	return getIntensity( toCheck, COLD );
}

float cWeatherAb::getMaxTemp( weathID toCheck )
{
	return getValue( toCheck, MAXVAL, TEMP );
}
float cWeatherAb::getMinTemp( weathID toCheck )
{
	return getValue( toCheck, MINVAL, TEMP );
}
float cWeatherAb::getTemp( weathID toCheck )
{
	return getValue( toCheck, CURRVAL, TEMP );
}
float cWeatherAb::getMaxWindSpeed( weathID toCheck )
{
	return getValue( toCheck, MAXVAL, WIND );
}
float cWeatherAb::getMinWindSpeed( weathID toCheck )
{
	return getValue( toCheck, MINVAL, WIND );
}
float cWeatherAb::getWindSpeed( weathID toCheck )
{
	return getValue( toCheck, CURRVAL, WIND );
}

void cWeatherAb::setWindSpeed( weathID toCheck, float value )
{
	setValue( toCheck, CURRVAL, WIND, value );
}
void cWeatherAb::setMaxWindSpeed( weathID toCheck, float value )
{
	setValue( toCheck, MAXVAL, WIND, value );
}
void cWeatherAb::setMinWindSpeed( weathID toCheck, float value )
{
	setValue( toCheck, MINVAL, WIND, value );
}
void cWeatherAb::setMaxTemp( weathID toCheck, float value )
{
	setValue( toCheck, MAXVAL, TEMP, value );
}
void cWeatherAb::setMinTemp( weathID toCheck, float value )
{
	setValue( toCheck, MINVAL, TEMP, value );
}
void cWeatherAb::setTemp( weathID toCheck, float value )
{
	setValue( toCheck, CURRVAL, TEMP, value );
}

void cWeatherAb::setSnowIntensity( weathID toCheck, char value )
{
	setIntensity( toCheck, SNOW, value );
}
void cWeatherAb::setRainIntensity( weathID toCheck, char value )
{
	setIntensity( toCheck, RAIN, value );
}
void cWeatherAb::setHeatIntensity( weathID toCheck, char value )
{
	setIntensity( toCheck, HEAT, value );
}
void cWeatherAb::setColdIntensity( weathID toCheck, char value )
{
	setIntensity( toCheck, COLD, value );
}
void cWeatherAb::setRainChance( weathID toCheck, char value )
{
	setChance( toCheck, RAIN, value );
}
void cWeatherAb::setSnowChance( weathID toCheck, char value )
{
	setChance( toCheck, SNOW, value );
}
void cWeatherAb::setHeatChance( weathID toCheck, char value )
{
	setChance( toCheck, HEAT, value );
}
void cWeatherAb::setColdChance( weathID toCheck, char value )
{
	setChance( toCheck, COLD, value );
}

char cWeatherAb::getRainChance( weathID toCheck )
{
	return getChance( toCheck, RAIN );
}
char cWeatherAb::getSnowChance( weathID toCheck )
{
	return getChance( toCheck, SNOW );
}
char cWeatherAb::getHeatChance( weathID toCheck )
{
	return getChance( toCheck, HEAT );
}
char cWeatherAb::getColdChance( weathID toCheck )
{
	return getChance( toCheck, COLD );
}

float cWeatherAb::getSnowThreshold( weathID toCheck )
{
	return weather[toCheck].snowThreshold;
}

void cWeatherAb::setSnowThreshold( weathID toCheck, float value )
{
	weather[toCheck].snowThreshold = value;
}

void cNetworkStuff::UDPInit()
{
	int bcode;

	UDPsock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (UDPsock<0)
	{
		printf("ERROR: Unable to create socket\n");
		return;
	}
#ifndef __NT__
	int on = 1;
	setsockopt(UDPsock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
#endif
	lenConnAddr = sizeof (struct sockaddr_in);
	connUDP.sin_family=AF_INET;
	connUDP.sin_addr.s_addr=INADDR_ANY;
	connUDP.sin_port=(((UDP_PORT%256)<<8))+(UDP_PORT>>8); //Port
	bcode=bind( UDPsock, (struct sockaddr *)&connUDP, lenConnAddr);

	if (bcode<0)
	{
		printf("ERROR: Unable to bind socket 1 - Error code: %i\n",bcode);
		return;
	}
    
	
	listen( UDPsock, 42);
}

void cNetworkStuff::UDPCheckConn() // Check for connection requests
{
	int s;
	int len;
	int currClient;	
	int count;
	char dataRecv[MAXBUFFER];
	int total, ho, mi, se;
//	if (now<MAXIMUM)
//	{
		FD_ZERO(&UDPconn);
		FD_SET( UDPsock, &UDPconn);
		UDPnfds=UDPsock+1;
		s=select(UDPnfds, &UDPconn, NULL, NULL, &uoxtimeout);
		if (s>0)
		{
			len=sizeof (struct sockaddr_in);
#ifdef __LINUX__
			currClient=accept( UDPsock, (struct sockaddr *)&client_addr, (unsigned int *)&len);
#else
			currClient = accept( UDPsock, (struct sockaddr *)&client_addr, &len );
#endif
			if (currClient<0)
			{
				printf("ERROR: Error at client connection!\n");
				error=1;
				return;
			}
			count=recv( currClient, dataRecv, 4, 0);
			if ((dataRecv[0]=='\x21')&&(count<4)) // UOMon
			{
				total=(uiCurrentTime-starttime)/CLOCKS_PER_SEC;
				ho=total/3600;
				total-=ho*3600;
				mi=total/60;
				total-=mi*60;
				se=total;
				sprintf(uoxmonitor, "UOX3 LoginServer\r\nUOX3 Server: up for %ih %im %is\r\n", ho,mi,se);
//				Network->xSend( s, uoxmonitor, strlen(uoxmonitor), 0);
				send( s, uoxmonitor, strlen( uoxmonitor ), 0);
			}
			return;
		}
/*		if (s<0)
		{
//			printf("ERROR: Select (Conn) failed!\n");
			error=1;
			return;
		}
		*/
//	}
}

bool cWeatherAb::newDay( void )
{
	weathID currval;
	char chanceForWeath;
	bool isSnowing, isRaining, isHeatWave, isColdDay;
	float effTempMax, effTempMin;

	for( currval=0; currval < weathCount; currval++ )
	{
		effTempMax = getMaxTemp( currval );
		effTempMin = getMinTemp( currval );
		setSnowActive( currval, false );
		setRainActive( currval, false );
		chanceForWeath = RandomNum( 0, 100 );
		if( chanceForWeath < getHeatChance( currval ) )
		{
			isHeatWave = true;
			setHeatIntensity( currval, RandomNum( 1, 4 ) );
			effTempMax += RandomNum( 0, (int)(effTempMax / 10 * getHeatIntensity( currval ) ) );
		}
		if( chanceForWeath < getColdChance( currval ) )
		{
			isColdDay = true;
			setColdIntensity( currval, RandomNum( 1, 4 ) );
			effTempMin -= RandomNum( 0, (int)(effTempMin / 10 * getColdIntensity( currval ) ) );
		}
		if( chanceForWeath < getSnowChance( currval ) )
		{
			isSnowing = true;
			setSnowIntensity( currval, RandomNum( 1, 4 ) );
			setSnowActive( currval, true );
		}
		if( chanceForWeath < getRainChance( currval ) )
		{
			isRaining = true;
			setRainIntensity( currval, RandomNum( 1, 4 ) );
			setRainActive( currval, true );
		}
		setEffectiveMaxTemp( currval, effTempMax );
		setEffectiveMinTemp( currval, effTempMin );
	}

	return true;
}

void cWeatherAb::setEffectiveMaxTemp( weathID toCheck, float value )
{
	setValue( toCheck, MAXVAL, EFFECTIVE, value );
}
void cWeatherAb::setEffectiveMinTemp( weathID toCheck, float value )
{
	setValue( toCheck, MINVAL, EFFECTIVE, value );
}

float cWeatherAb::getEffectiveMaxTemp( weathID toCheck )
{
	return getValue( toCheck, MAXVAL, EFFECTIVE );
}
float cWeatherAb::getEffectiveMinTemp( weathID toCheck )
{
	return getValue( toCheck, MINVAL, EFFECTIVE );
}

bool cWeatherAb::doStuff( void )
{
	weathID currval;
	char chanceForWeath;
	bool isSnowing, isRaining;
	float effTempMax, effTempMin, currTemp;
	char myHour;

	if( ampm )
		myHour = hour + 12;
	else
		myHour = hour;

	for( currval=0; currval < weathCount; currval++ )
	{
		effTempMax = getEffectiveMaxTemp( currval );
		effTempMin = getEffectiveMinTemp( currval );
		chanceForWeath = RandomNum( 0, 100 );
//		printf("chanceForWeath %i\n", chanceForWeath );
		isSnowing = getSnowActive( currval );
		isRaining = getRainActive( currval );
		if( ampm )
			currTemp = (effTempMax - effTempMin) / 12 * ( 12 - hour ) + effTempMin;
		else
			currTemp = (effTempMax - effTempMin) / 12 * hour + effTempMin;
		setTemp( currval, currTemp );
		if( isSnowing && getSnowThreshold( currval ) > currTemp )
		{
//			printf("It's snowing in weather type %i with current temperature %i", currval, (int)currTemp );
			setSnowIntensity( currval, RandomNum( 1, 4 ) );
		} 
		else if( isRaining )
		{
//			printf("It's raining in weather type %i with current temperature %i", currval, (int)currTemp );
			setRainIntensity( currval, RandomNum( 1, 4 ) );
		}
	}

	return true;
}

void cWeatherAb::setRainActive( weathID toCheck, bool value )
{
	weather[toCheck].weathActive[RAIN] = value;
}
void cWeatherAb::setSnowActive( weathID toCheck, bool value )
{
	weather[toCheck].weathActive[SNOW] = value;
}

bool cWeatherAb::getRainActive( weathID toCheck )
{
	return weather[toCheck].weathActive[RAIN];
}
bool cWeatherAb::getSnowActive( weathID toCheck )
{
	return weather[toCheck].weathActive[SNOW];
}

bool cWeatherAb::doPlayerStuff( CHARACTER p )
{
	if( chars[p].npc )
		return true;
	weathID currval;
	bool isSnowing, isRaining;
	currval = region[chars[p].region].weather;
	if( currval > weathCount || weathCount == 0 )
	{
		char wdry[5]     = "\x65\xFF\x00\x10";	// it's dry
		UOXSOCKET s = calcSocketFromChar( p );
		Network->xSend( s, wdry, 4, 0 );
		return false;
	}

	isSnowing = getSnowActive( currval );
	isRaining = getRainActive( currval );
	if( isSnowing && getSnowThreshold( currval ) > getTemp( currval ) )
	{
		doPlayerWeather( calcSocketFromChar( p ), 2 );
		if( chars[p].weathDamage[SNOW] == 0 )
			chars[p].weathDamage[SNOW] = uiCurrentTime + CLOCKS_PER_SEC * ( Races->getSnowSecs( chars[p].race ) );
	} 
	else if( isRaining )
	{
		doPlayerWeather( calcSocketFromChar( p ), 1 );
		if( chars[p].weathDamage[RAIN] == 0 )
			chars[p].weathDamage[RAIN] = uiCurrentTime + CLOCKS_PER_SEC * ( Races->getRainSecs( chars[p].race ) );
	}
	else
	{
		doPlayerWeather( calcSocketFromChar( p ), 0 );
		if( chars[p].weathDamage[SNOW] != 0 )
			chars[p].weathDamage[SNOW] = 0;
		if( chars[p].weathDamage[RAIN] != 0 )
			chars[p].weathDamage[RAIN] = 0;
	}

	return true;
}

void cWeatherAb::doPlayerWeather( UOXSOCKET s, unsigned char weathType )
// Weather Types 
// 0 - dry
// 1 - rain
// 2 - snow
// 3 - rain and snow
{
	char wdry[5]     = "\x65\xFF\x00\x10";	// it's dry
	char wrain[5]    = "\x65\x00\x40\x10";	// it's raining!
	char wstorm[5]   = "\x65\x01\x40\x10";	// it's stormy!
	char wsnow[5]    = "\x65\x02\x40\x10";	// snow coming
	char wstrmbrw[5] = "\x65\x03\x40\x10";	// storm brewing
	
	Network->xSend( s, wdry, 4, 0 );
	switch( weathType )
	{
	case 0: 		break;
	case 1:
		raindroptime=uiCurrentTime+CLOCKS_PER_SEC*(3+rand()%3);
		Network->xSend(s, wrain, 4, 0);
		break;
	case 2:
		if (rand()%2)
			soundeffect2(currchar[s], 0x00, 0x14);
		else
			soundeffect2(currchar[s], 0x00, 0x15);
		Network->xSend(s, wsnow, 4, 0);
		break;
	case 3:
		raindroptime=uiCurrentTime+CLOCKS_PER_SEC*(3+rand()%3);
		Network->xSend(s, wrain, 4, 0);
		if (rand()%2)
			soundeffect2(currchar[s], 0x00, 0x14);
		else
			soundeffect2(currchar[s], 0x00, 0x15);
		Network->xSend(s, wsnow, 4, 0);
		break;
	default:		break;
	}
}
