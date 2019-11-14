/*
 * ShowMenu.h
 *
 * Created: 14/11/2019 09.16.56
 *  Author: Bruger
 */ 


#ifndef SHOWMENU_H_
#define SHOWMENU_H_

#include "LCDLibrary.h"
#include "json/parser.h"

void LCD_UpdateSong(SpotifyReply *spotifyReply);
void LCD_SetVolume(uint8_t volume);
void LCD_SetProgress(SpotifyReply *spotifyReply);


#endif /* SHOWMENU_H_ */