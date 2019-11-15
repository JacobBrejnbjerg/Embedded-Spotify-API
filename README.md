
# Embedded Spotify API
This project is made in C and C#. C is used to interact with the several components which goes into this project. C# is used for the .NET Core v3 backend which is responsible for interacting with the Spotify API.

With a remote NEC control it is possible to control your Spotify account. As of now, it is possible to
- Pause/Resume
- Skip song
- Play previous song
- Get information about current playing song
- Turn volume up/down

The API comes with Swagger. Start the project and access URL:PORT or URL:PORT/index.html in order to see the Swagger documentation.

### Table of Contents
- [Prerequisites](#prerequisites)
- [Getting Started](#getting-started)
    - [Wiring](#wiring)
	     * [LCD Display](#lcd-display)
	     * [Infrared Receiver](#infrared-receiver)
	     * [ESP8266](#esp8266)
     - [Embedded solution](#embedded-solution)
     - [API Project](#api-project)
- [Get Spotify Access Token](#get-spotify-access-token)
- [Overall codeflow](#overall-codeflow)
- [ESP8266](#esp8266-1)
- [LCD Display](#lcd-display-1)
- [Infrared Receiver](#infrared-receiver-1)
- [Structs](#structs)
- [API Library](#api-library)
- [ShowMenu Library](#showmenu-library)
- [Debugging](#debugging)
- [AT Commands](#at-commands)
- [Image of the project](#image-of-the-project)

## Prerequisites
- ATmega 2560
- ESP8266
- NEC Remote
- Infrared Receiver
- Webserver
- Spotify Account

## Getting Started

1. #### Wiring
Wire the modules as described in the pictures below:
##### LCD Display:
![LCD Wiring](https://i.imgur.com/xeyEJ4t.png)

##### Infrared Receiver
![IR Wiring](https://i.imgur.com/H42HEmB.png)

##### ESP8266
![ESP8266 Wiring](https://i.imgur.com/DIQGXDo.png)

2. #### Embedded solution
Open up the Embedded Solution. In the ESP8266 Project change the following in the ESP8266Library.h file:
**DOMAIN** The DNS Name or IP of the webserver having the API
**PORT** The port which the API is accesible at. This is usually 80 or 443. This project does not support HTTPS.
**SSID** The SSID of the network which the ESP8266 should connect to.
**PASSWORD** The password to the SSID which the ESP8266 should connect to.


3. #### API Project
Open up the API project. In the appsettings file, insert the values as described below:
**DeviceID** The Device ID of the current device playing the music. This can be found by calling the Spotify API.
**AccessToken** The Access Token which the API should use in order to contact Spotify. You can find more on how to get this in the section "*Get Spotify Access Token*

## Get Spotify Access Token
[https://developer.spotify.com/console/get-user-player/?market=ES](https://developer.spotify.com/console/get-user-player/?market=ES)
Press GET TOKEN. For ease, just check all the check boxes. The token is valid for 1 hour.

## Overall codeflow
![enter image description here](https://i.imgur.com/5GCTB6R.jpg)

## ESP8266
The ESP8266 runs USART with a BAUD rate of 115200. The ESP8266 is in charge of sending the package to the web API. The codeflow is as follows:
![ESP8266 Codeflow](https://i.imgur.com/2EAXqOJ.png)

The ESP8266 is controlled by AT Commands.

## LCD Display
The LCD Display displays Songname, artist, volume, progress in song (in seconds) and total length of song (in seconds).

![LCD Display](https://i.imgur.com/CaHvGnf.png)

## Infrared Receiver
The infrared receiver is in control of handling the NEC communication from the remote to the embedded software. It runs on a TIMER4 interrupt which triggers whenever pin PL0 goes high. This is used to register all the times received from the NEC remote.

![Infrared Receiver Codeflow](https://i.imgur.com/04Loh1n.png)

## Structs

    typedef struct
	{
		char SongName[50];
		char Artist[50];
		int Seconds;
		int PlayedSeconds;
		uint8_t Volume;
	} SpotifyReply;


## API Library
**void API_Get_Song(SpotifyReply \*spotifyReply)**
Gets information about the current song. Inserts information into given SpotifyReply struct parameter.

**void API_Next_Song(SpotifyReply \*spotifyReply)**
 Goes to next Spotify song.

**void API_Previous_Song(SpotifyReply \*spotifyReply)**
Goes to previous Spotify song.

**void API_Pause_Song(void)**
Pauses Spotify song.

**void API_Play_Song(void)**
Resumes Spotiy song.

**void API_Set_Volume(uint8_t volume)**
Set volume of Spotify.

## ShowMenu Library
**void LCD_UpdateSong(SpotifyReply \*spotifyReply)**
Updates all the information about a song from the SpotifyReply struct.

**void LCD_SetVolume(uint8_t volume)**
Sets the volume in the display.

**void LCD_SetProgress(SpotifyReply \*spotifyReply)**
Sets progress in the display using the values in the SpotifyReply parameter.

## Debugging
If it is necessary to debug the ESP8266 module, it is possible; simply move RX1/TX1 to RX/TX on the ATmega. They have to be paired as below:
ESP8266 RX -> ATmega RX
ESP8266 TX -> ATmega TX

This way it is possible through a serial interface to interact with the ESP8266 through AT commands and see its response.

## AT Commands
![enter image description here](https://i.imgur.com/gtW6glL.jpg)

Example of serial communication between ATmega2560 and ESP8266. In this case the ATmega2560 sent the AT command *CIPMUX:0* and the ESP8266 responded *OK*
![AT communication](https://i.imgur.com/qNlJ0SU.png)

## Image of the project
![Image of the setup](https://i.imgur.com/xRg087G.jpg)
