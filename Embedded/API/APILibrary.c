/*
 * APILibrary.c
 *
 * Created: 13/11/2019 09.12.33
 *  Author: Bruger
 */ 

#include "APILibrary.h"


// Gets information about the current song. Inserts information into given SpotifyReply struct parameter.
void API_Get_Song(SpotifyReply *spotifyReply)
{
	// Declare buffer to contain API response
	char _buffer[DEFAULT_BUFFER_SIZE];		
	
	// Sends GET call to api endpoint /api/Song and puts received data into _buffer variable
	ESP8266_Get(_buffer, "/api/Song");
	
	// Extract JSON from the received API data. Sends _buffer data and puts json into _buffer.
	Json_Get_Json_From_String(_buffer);
	
	// Converts json inside _buffer to SpotifyReply struct
	Json_Get_SpotifyReply(_buffer, spotifyReply);
}

// Goes to next Spotify song
void API_Next_Song(SpotifyReply *spotifyReply)
{
	char _buffer[DEFAULT_BUFFER_SIZE];
	ESP8266_Get(_buffer, "/api/Song/Next");
	Json_Get_Json_From_String(_buffer);
	Json_Get_SpotifyReply(_buffer, spotifyReply);
}

// Goes to previous Spotify song
void API_Previous_Song(SpotifyReply *spotifyReply)
{
	char _buffer[DEFAULT_BUFFER_SIZE];
	ESP8266_Get(_buffer, "/api/Song/Previous");
	Json_Get_Json_From_String(_buffer);
	Json_Get_SpotifyReply(_buffer, spotifyReply);
}

// Pauses Spotify song
void API_Pause_Song(void)
{
	char _buffer[DEFAULT_BUFFER_SIZE];
	ESP8266_Get(_buffer, "/api/Song/Pause");
}

// Resumes Spotiy song
void API_Play_Song(void)
{
	char _buffer[DEFAULT_BUFFER_SIZE];
	ESP8266_Get(_buffer, "/api/Song/Play");
}

// Set volume of Spotify
void API_Set_Volume(uint8_t volume)
{
	char volumeUrl[22];
	char _buffer[DEFAULT_BUFFER_SIZE];
	sprintf(volumeUrl, "/api/Volume?volume=%i", volume);
	ESP8266_Get(_buffer, volumeUrl);
}