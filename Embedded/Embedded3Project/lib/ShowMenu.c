/*
 * ShowMenu.c
 *
 * Created: 14/11/2019 09.16.42
 *  Author: Bruger
 */ 

#include "ShowMenu.h"

// Updates all the information about a song from the SpotifyReply struct
void LCD_UpdateSong(SpotifyReply *spotifyReply){
	// Clear LCD display
	lcd_clrscr();
	
	// Set Songname starting at column 0 row 0
	lcd_gotoxy(0,0);
	lcd_putformat("%s", &(spotifyReply->SongName));

	// Set Artist starting at column 0 row 1
	lcd_gotoxy(0,1);
	lcd_putformat("%s", &(spotifyReply->Artist));
	
	// Sets progress and volume using the functions below.
	LCD_SetProgress(spotifyReply);
	LCD_SetVolume(spotifyReply->Volume);
}

// Sets the volume in the display.
void LCD_SetVolume(uint8_t volume){
	// Sets volume at column 13 row 0 (top right corner)
	lcd_gotoxy(13,0);
	lcd_putformat("%3i", volume); // Right align and always fill 3 digits/places
}

// Sets progress in the display
void LCD_SetProgress(SpotifyReply *spotifyReply){
	// Only update the display if the playedSeconds are lower or the same as the seconds of the song
	if (spotifyReply->PlayedSeconds <= spotifyReply->Seconds)
	{
		// Set progress in following format played/total starting at column 9 row 1 (lower right corner)
		lcd_gotoxy(9,1);
		// Right align and always fill 3 digits/places before and after backslash	
		lcd_putformat("%3i/%3i", spotifyReply->PlayedSeconds, spotifyReply->Seconds);
	}
}