/*
 * esp8266.h
 *
 * Created: 11/11/2019 14.41.15
 *  Author: Bruger
 */ 


#ifndef ESP8266Library_H_
#define ESP8266Library_H_

#define F_CPU 16000000UL		/* Define CPU Frequency e.g. here its Ext. 16MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */
#include <stdbool.h>			/* Include standard boolean library */
#include <string.h>			/* Include string library */
#include <stdio.h>			/* Include standard IO library */
#include <stdlib.h>			/* Include standard library */
#include <avr/interrupt.h>		/* Include avr interrupt header file */
#include "USART_RS232.h"		/* Include USART header file */


#define SREG    _SFR_IO8(0x3F)

#define DEFAULT_BUFFER_SIZE		340
#define DEFAULT_TIMEOUT			10000

/* Connection Mode */
#define SINGLE				0
#define MULTIPLE			1

/* Application Mode */
#define NORMAL				0
#define TRANSPERANT			1

/* Application Mode */
#define STATION				1
#define ACCESSPOINT			2
#define BOTH_STATION_AND_ACCESPOINT	3

/* Define Required fields shown below */
#define DOMAIN				"WEBSERVER IP/DNS NAME"
#define PORT				"80"

#define SSID				"WIRELESS NETWORK NAME"
#define PASSWORD			"WIRELESS NETWORK PASSWORD"

enum ESP8266_RESPONSE_STATUS{
	ESP8266_RESPONSE_WAITING,
	ESP8266_RESPONSE_FINISHED,
	ESP8266_RESPONSE_TIMEOUT,
	ESP8266_RESPONSE_BUFFER_FULL,
	ESP8266_RESPONSE_STARTING,
	ESP8266_RESPONSE_ERROR
};

enum ESP8266_CONNECT_STATUS {
	ESP8266_CONNECTED_TO_AP,
	ESP8266_CREATED_TRANSMISSION,
	ESP8266_TRANSMISSION_DISCONNECTED,
	ESP8266_NOT_CONNECTED_TO_AP,
	ESP8266_CONNECT_UNKNOWN_ERROR
};

enum ESP8266_JOINAP_STATUS {
	ESP8266_WIFI_CONNECTED,
	ESP8266_CONNECTION_TIMEOUT,
	ESP8266_WRONG_PASSWORD,
	ESP8266_NOT_FOUND_TARGET_AP,
	ESP8266_CONNECTION_FAILED,
	ESP8266_JOIN_UNKNOWN_ERROR
};

void ESP8266_Get(char* _buffer, char* urlEndpoint);
void Read_Response(char* _Expected_Response);
void ESP8266_Clear();
void ESP8266_Init();
void GetResponseBody(char* Response, uint16_t ResponseLength);

bool ESP8266_PrepareForSend();
bool WaitForExpectedResponse(char* ExpectedResponse);
bool SendATandExpectResponse(char* ATCommand, char* ExpectedResponse);
bool ESP8266_ApplicationMode(uint8_t Mode);
bool ESP8266_ConnectionMode(uint8_t Mode);
bool ESP8266_Begin();
bool ESP8266_Close();
bool ESP8266_WIFIMode(uint8_t _mode);

uint8_t ESP8266_JoinAccessPoint(char* _SSID, char* _PASSWORD);
uint8_t ESP8266_connected();
uint8_t ESP8266_Start(uint8_t _ConnectionNumber, char* Domain, char* Port);
uint8_t ESP8266_Send(char* Data);
uint8_t ESP8266_DataRead();

int16_t ESP8266_DataAvailable();
uint16_t Read_Data(char* _buffer);


#endif /* ESP8266_H_ */