/*
 * APILibrary.h
 *
 * Created: 13/11/2019 09.12.47
 *  Author: Bruger
 */ 

#include "json/parser.h"
#include "ESP8266Library.h"

#ifndef APILIBRARY_H_
#define APILIBRARY_H_

void API_Get_Song(SpotifyReply *spotifyReply);
void API_Next_Song(SpotifyReply *spotifyReply);
void API_Previous_Song(SpotifyReply *spotifyReply);
void API_Pause_Song(void);
void API_Play_Song(void);
void API_Set_Volume(uint8_t volume);


#endif /* APILIBRARY_H_ */