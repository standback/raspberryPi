#include "fcntl.h"
#include "sys/ioctl.h"
#include "linux/i2c-dev.h"
#include "stdio.h"
#include "unistd.h"
#include "wiringPi.h"
#include "wiringPiI2C.h"

#define I2CADDRESS 	0x70
#define testgpio 7
int writeLED(int fd, unsigned char address, unsigned char data)
{
	if (wiringPiI2CWriteReg8(fd, address, data)<0){
		printf(" led write address: %d, fail \n", address);
		return -1;
	}
	return  0;
}
int 
main()
{
	int i2cfd = -1;
	int readdata= 0xdeaddead;
	printf ("---start--- \n");
	wiringPiSetup();
	if ((i2cfd = wiringPiI2CSetup(I2CADDRESS) )< 0)
	{
		printf( " ----- setup I2c fail!!!!\n");
		return -1;
	}

	if (wiringPiI2CWrite (i2cfd, 0x21)<0)
	{	
		printf("i2c init :0x21 fail\n");
		return 0;
	}
	if (wiringPiI2CWrite (i2cfd, 0x81)<0)
	{
		printf("i2c config : 0x81 fail \n");
		return 0;
	}
	unsigned char data=0xff;
	while (1){
		data ^= 0xff;
		for (int i=0; i<16; i++){
			if (writeLED(i2cfd, i, data)< 0)
				return 0;
			sleep (1);
		}
	}
	close(i2cfd);
	return 0;
}

