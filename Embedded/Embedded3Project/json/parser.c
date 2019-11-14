/*
* parser.c
*
* Created: 12/11/2019 08.52.57
*  Author: Bruger
*/

#include "parser.h"

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

int  getSubString(char *source, char *target,int from, int to)
{
	int length=0;
	int i=0,j=0;
	
	//get length
	while(source[i++]!='\0')
	length++;
	
	if(from<0 || from>length){
		printf("Invalid \'from\' index\n");
		return 1;
	}
	if(to>length){
		printf("Invalid \'to\' index\n");
		return 1;
	}
	
	for(i=from,j=0;i<=to;i++,j++){
		target[j]=source[i];
	}
	
	//assign NULL at the end of string
	target[j]='\0';
	
	return 0;
}

void Json_Get_Json_From_String(char *buf)
{
	char *e;
	int startIndex;
	int endIndex;

	// Get start index of Json ( { symbol)
	e = strchr(buf, '{');
		startIndex = (int)(e - buf);
		
		// Get end index of Json ( } symbol)
	e = strrchr(buf, '}');
	endIndex = (int)(e - buf);
	
	getSubString(buf, buf, startIndex, endIndex);
}