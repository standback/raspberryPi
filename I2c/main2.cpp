#include "stdio.h"
#include "linux/i2c-dev.h"
#include "fcntl.h"
#include "sys/ioctl.h"
#include "unistd.h"
#define I2C_ADDRESS 0X70
#define I2C_DEV "/dev/i2c-1"
void cleanpanel(int fd)
{
	unsigned char buf[10];
	for (int index = 0 ; index< 16; index ++)
	{
		buf[0] = index;
		buf[1] = 0;
		if (write (fd, buf,2)<0)
			printf (" i2c write address: %d fail\n");
	}
}
int main()
{
	int i2cfd =-1;
	unsigned char buf[10];
	i2cfd = open(I2C_DEV,O_RDWR);
	if (i2cfd < 0)
		printf("i2c device open fail \n");
	if (ioctl(i2cfd, I2C_SLAVE, I2C_ADDRESS) < 0)
		printf("i2c set slave address fail \n");
	cleanpanel(i2cfd);
/*

	unsigned char readdata = 0xda; 
	readdata = i2c_smbus_read_byte_data(i2cfd, 0);
	printf("readata: %x \n", readdata);
	if (readdata <  0)
		printf(" i2c smbus read byte data fail  \n");
*/
	buf[0] = 0x21;
	if (write(i2cfd, buf, 1)<0)
		printf("i2c write 0x21 fail \n");

	buf[0] = 0x81;
	if (write (i2cfd, buf, 1)<0)
		printf("i2c write 0x81 fail \n");

	buf [0] = 0;
	buf [1] = 0b10101010;
	if (write (i2cfd, buf,2)<0)
		printf ("i2cfd write address: 0; fail \n");
	close(i2cfd);
return 0;
}


