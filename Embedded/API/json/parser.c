/*
* parser.c
*
* Created: 12/11/2019 08.52.57
*  Author: Bruger
*/

#include "parser.h"

// Converts string to SpotifyReplay struct
int Json_Get_SpotifyReply(const char *buf, SpotifyReply *spotifyReply)
{
	/* Mapping of JSON attributes to my_object's struct members */
	const struct json_attr_t json_attrs_object[] = {
		
		{"songName", t_string, .addr.string = spotifyReply->SongName,.len = sizeof(spotifyReply->SongName)},
		{"artist", t_string, .addr.string = spotifyReply->Artist,.len = sizeof(spotifyReply->Artist)},
		{"volume", t_integer, .addr.integer = &(spotifyReply->Volume)},
		{"seconds", t_integer, .addr.integer = &(spotifyReply->Seconds)},
		{"playedSeconds", t_integer, .addr.integer = &(spotifyReply->PlayedSeconds)},
		{NULL},
	};

	/* Parse the JSON string from buffer */
	return json_read_object(buf, json_attrs_object, NULL);
}

// Gets part of string.
// Returns 0 for all went well and returns 1 for error.
int  getSubString(char *source, char *target,int from, int to)
{
	int length=0;
	int i=0,j=0;
	
	//get length
	while(source[i++]!='\0')
	length++;
	
	// Is start index less than 0 or higher than the length of the string
	if(from<0 || from>length){
		printf("Invalid \'from\' index\n");
		return 1;
	}
	// Is end index higher than the length of the string
	if(to>length){
		printf("Invalid \'to\' index\n");
		return 1;
	}
	
	// Copies each character into the target from start to end index.
	for(i=from,j=0;i<=to;i++,j++){
		target[j]=source[i];
	}
	
	// Assign NULL at the end of string
	target[j]='\0';
	
	return 0;
}

// Gets Json part of a string
void Json_Get_Json_From_String(char *buf)
{
	char *e;
	int startIndex;
	int endIndex;

	// Get start index of Json ( { symbol)
	e = strchr(buf, '{');
		startIndex = (int)(e - buf);
		
	// Get end index/last index of Json ( } symbol)
	e = strrchr(buf, '}');
	endIndex = (int)(e - buf);
	
	// Gets part of string using the start and end index found from { and }
	getSubString(buf, buf, startIndex, endIndex);
}