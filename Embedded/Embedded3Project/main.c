/*
* ATmega16_WIFI
* http://www.electronicwings.com
*
*/


#include <stdio.h>
#include "setup/stdio_setup.h"
#include "lib/printf.h"
#include "json/parser.h"
#include "ESP8266Library.h"
#include "IRLibrary.h"
#include "APILibrary.h"
#include "LCDLibrary.h"
#include "lib/ShowMenu.h"
#include "lib/song_progress_timer.h"

// Variables used to remember information
SpotifyReply spotifyReply;
uint8_t volume = 50;
bool isPlaying = true;
int playedSeconds = 0;
bool updateSong = false;

// Function used to take action
void Action(int _buttonPressed);

int main(void)
{
	UartInit(); // Init Uart. Used for printf
	InitIR(); // Init Infrared which enables the use of the remote
	USART_Init(115200);		/* Initiate USART with 115200 baud rate */
	ESP8266_Init(); // Init ESP8266 by setting up network.
	lcd_init(LCD_DISP_ON); // Init LCD Display by turning it on

	// Get info of current playing song and its volume.
	API_Get_Song(&spotifyReply);

	// Sets volume to current one
	volume = spotifyReply.Volume;
	
	// Sets the played time to the current one
	playedSeconds = spotifyReply.PlayedSeconds;
	
	// Update song on the display
	LCD_UpdateSong(&spotifyReply);
	
	// Enable interrupt to trigger every second.
	// Used to update playedSeconds.
	Init_Progress_Timer();

	while(1)
	{
		// Check if song has changed
		if (updateSong)
		{
			// Song has changed. Update it.
			// Get info of new playing song.
			API_Get_Song(&spotifyReply);
			
			// Sets the played time to the one in the new song
			playedSeconds = spotifyReply.PlayedSeconds;
			
			// Update display with the new song
			LCD_UpdateSong(&spotifyReply);
			
			// Stop updating song
			updateSong = false;
		}
		
		// Takes action whenever a button is pressed
		Action(GetButtonPressed());
	}
}

void Action(int _buttonPressed){
	switch (_buttonPressed)
	{
		case SkipLeft:
			// Go to previous Spotify song and update struct.
			API_Previous_Song(&spotifyReply);
			// Update display with info about the new song
			LCD_UpdateSong(&spotifyReply);
			// Update playedSeconds variable
			playedSeconds = spotifyReply.PlayedSeconds;
		break;
		case SkipRight:
			// Go to next Spotify song and update struct
			API_Next_Song(&spotifyReply);
			// Update display with info about the new song
			LCD_UpdateSong(&spotifyReply);
			// Update playedSeconds variable
			playedSeconds = spotifyReply.PlayedSeconds;
		break;
		case ArrowUp:
			// Increment volume variable by 20
			volume+=20;
			
			// Limit volume to maximum 100
			if (volume > 100)
				volume = 100;
			else {
				// Set volume on Spotify
				API_Set_Volume(volume);
				// Update volume on display
				LCD_SetVolume(volume);
			}
		break;
		case ArrowDown:
			// Decrement volume variable by 20
			volume-=20;
			
			// Limit volume to minimum 0
			if (volume < 0)
				volume=0;
			else {
				// Set volume on spotify
				API_Set_Volume(volume);
				// Update volume on display
				LCD_SetVolume(volume);	
			}
		break;
		case StartPause:
			// Is the song currently playing?
			if (isPlaying) {
				// Song is playing
				// Pause Spotify song
				API_Pause_Song();
				// Disable timer so it does not count up
				Disable_Progress_Timer();
			} else {
				// Song is not playing
				// Resume Spotify Song
				API_Play_Song();
				// Enable timer so it counts up again
				Enable_Progress_Timer();
			}
			
			// Set bool isPlaying to the opposite of what it was.
			// Ex. Goes from Playing to Paused og Paused to Playing
			isPlaying = !isPlaying;
		break;
	}
}

// Interrupt used to count playedSeconds and check if song has changed
ISR(TIMER1_COMPA_vect)
{
	// Count playedSeconds up by one
	playedSeconds++;
	
	// Set the playedSeconds on the spotifyReply struct
	spotifyReply.PlayedSeconds = playedSeconds;
	
	// Update the progress on the display.
	LCD_SetProgress(&spotifyReply);
	
	// Checks if the time played is equal to the seconds of the playing song.
	if (playedSeconds == spotifyReply.Seconds)
	{
		// Tell main loop to update the song.
		updateSong = true;
	}
}