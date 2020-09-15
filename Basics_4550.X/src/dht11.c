#include "dht11.h"

float dht_temp = 0.0;
float dht_humidity = 0.0;

void DHT11_Init(void)
{
	DHT11Pin_Tris = 0;
	DHT11Pin_Out = 1;
}

int DHT11_Wait4Resp(bool HtoL, int timeout_10us)
{
	int retryTimeout = 0;
	while(DHT11Pin_In == HtoL)
	{
		if(retryTimeout == timeout_10us)
			return 0;
		else
		{
			__delay_us(10);
			retryTimeout++;
		}
	}
	return retryTimeout;
}

bool DHT11_MReq(void)
{
	uint8_t checksum;
	uint8_t data[5] = {0,0,0,0,0};
	int i, j, voltLen = 0;
	bool error = 0;

	// Set Data Single-bus voltage level from high to low at least 18ms
	DHT11Pin_Out = 0;
	__delay_ms(20);

	// pull up voltage and wait 20-40us for DHT’s response.
	DHT11Pin_Out = 1;
	DHT11Pin_Tris = 1;
	if(DHT11_Wait4Resp(1, 4) == 0)
		error = 1;
	
	// Wait for low to high response signal, which lasts 80us
	if(DHT11_Wait4Resp(0, 8) == 0)
		error = 1;

	// DHT11 pulls up voltage and keeps it for 80us and prepares for data transmission
	DHT11_Wait4Resp(1, 8);

	// DHT start to send data to MCU
	for(i = 0; i<5; i++) //loop to get the 5 bytes
	{
		for(j = 7; j>=0; j--)//Loop to get each of the bits
		{
			// Wait for low to high response signal, which lasts 50us
			DHT11_Wait4Resp(0, 5);

			// The length of the following high-voltage-level signal determines whether data bit is "0" or "1" 
			voltLen = DHT11_Wait4Resp(1, 7);

			// 26us-28us valtage-length means data "0" / 70us voltage-length means "1"
			if(voltLen > 3)
				data[i] |= (1<<j);
			
		}
	}

	DHT11Pin_Tris = 0;
	DHT11Pin_Out = 1;

	checksum = data[0] + data[1] + data[2] + data[3];

	if((checksum == data[4]) && (error == 0))
	{
		dht_humidity = (float) data[0] + (float)(data[1]/10.0);
		dht_temp = (float) data[2] + (float)(data[3]/10.0);
	}
	else
		error = 1;

	return error;
}


float DHT11_GetTemp(void)
{
	return dht_temp;
}

float DHT11_GetRHum(void)
{
	return dht_humidity;
}

