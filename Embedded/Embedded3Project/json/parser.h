/*
 * parser.h
 *
 * Created: 12/11/2019 08.53.05
 *  Author: Bruger
 */ 


#ifndef PARSER_H_
#define PARSER_H_

#include "mjson.h"
#include <string.h>
#include <stdio.h>

// Structs
typedef struct
{
	char SongName[50];
	char Artist[50];
	int Seconds;
	int PlayedSeconds;
	int Volume;
} SpotifyReply;


// Functions
int Json_Get_SpotifyReply(const char *buf, SpotifyReply *spotifyReply);
int getSubString(char *source, char *target,int from, int to);

void Json_Get_Json_From_String(char *buf);




#endif /* PARSER_H_ */