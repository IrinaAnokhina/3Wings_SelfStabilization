/*
 * Accel.c
 *
 *  Created on: 4 окт. 2018 г.
 *      Author: AnokhinaIrina
 */
#include"Accel.h"
#include"math.h"

extern int fGX_Cal, fGY_Cal, fGZ_Cal;

extern I2C_HandleTypeDef hi2c1;
extern HAL_StatusTypeDef status;
extern int16_t xval, yval, zval;
extern int16_t xtemp, ytemp, ztemp;
extern int16_t xdata, ydata, zdata;
extern int16_t xGyro, yGyro, zGyro;
extern int16_t YG, XG, ZG;
 extern int16_t YGf, XGf, ZGf;
void Accel_ini()
{
	uint8_t data[1] =  {0};

	//reset the whole module first
	data[0] =  1<<7;
	status = HAL_I2C_Mem_Write(&hi2c1, (uint16_t)adress, (uint16_t)0x6B, I2C_MEMADD_SIZE_8BIT, data, 0x01, 0x10000);


	HAL_Delay(50);    //wait for 50ms for the gyro to stable
	data[0] = 0x00;
	status = HAL_I2C_Mem_Write(&hi2c1, adress, 0x6B, I2C_MEMADD_SIZE_8BIT, data, 0x01, 0x10000);
	//GYRO_CONFIG: FSR 500
	data[0] = 0x08;
		status = HAL_I2C_Mem_Write(&hi2c1, adress, 0x1B, I2C_MEMADD_SIZE_8BIT, data, 0x01, 0x10000);
	//ACCEL_CONFIG: 2g
		data[0] = 0x0;
		status =  HAL_I2C_Mem_Write(&hi2c1, adress, 0x1C, I2C_MEMADD_SIZE_8BIT, data, 0x01, 0x10000);
}

void Accel_GetXYZ(int16_t* pData1)

{
 uint8_t buffer1[6] = {0};
  /* Read output register X, Y & Z acceleration */
status = HAL_I2C_Mem_Read(&hi2c1, adress, 0x3B, I2C_MEMADD_SIZE_8BIT, buffer1, (uint16_t)0x06, 0x10000);

for(uint8_t i=0; i<3; i++)
    {
      pData1[i]=(int16_t)(((uint16_t)buffer1[2*i] << 8) + buffer1[2*i+1]);
    }
}

void Gyro_GetXYZ(int16_t* pData2)

{
 uint8_t buffer2[6] = {0};
  /* Read output register X, Y & Z gyroscope */
status = HAL_I2C_Mem_Read(&hi2c1, adress, 0x43, I2C_MEMADD_SIZE_8BIT, buffer2, (uint16_t)0x06, 0x10000);

for(uint8_t i=0; i<3; i++)
    {
      pData2[i]=(int16_t)(((uint16_t)buffer2[2*i] << 8) + buffer2[2*i+1]);
    }

}
void Accel_ReadAcc(void)
{
int16_t buffer[3] = {0};
 xval = yval = zval = 0x00;

 Accel_GetXYZ(buffer);

 /*xval = buffer[0];
 yval = buffer[1];
 zval = buffer[2];*/
 ydata = atan2(buffer[1], sqrt(pow(buffer[0], 2) + pow(buffer[2], 2))) * R2DEG;
 xdata = atan2(buffer[0], sqrt(pow(buffer[1], 2) + pow(buffer[2], 2))) * R2DEG;
 zdata = buffer[2];

 xtemp = XGf + xdata;
 ytemp = YGf + ydata;
 xval= XGf * (1 - KOEF_COMPL) + xdata*KOEF_COMPL;
yval = YGf * (1-KOEF_COMPL) + ydata*KOEF_COMPL;
}

void ReadGyro(void)
{
int16_t buffer[3] = {0};
 xGyro = yGyro = zGyro = 0x00;

 Gyro_GetXYZ(buffer);

 xGyro = buffer[0];
 yGyro = buffer[1];
 zGyro = buffer[2];

 XG = (xGyro - fGX_Cal);
 YG = (yGyro - fGY_Cal);
 ZG = (zGyro - fGZ_Cal);

	 XGf += XG/65.5 * 0.1;

	 YGf += YG/65.5 * 0.1;

	 ZGf += ZG/65.5* 0.1;
}

void GyroCalibrate()
{
	  uint16_t iNumCM = 10000;
	  for (int i = 0; i < iNumCM ; i++)
	  {
		  ReadGyro();
	    fGX_Cal += xGyro;
	    fGY_Cal += yGyro;
	    fGZ_Cal += zGyro;
	  }
}

void deriveGyro()
{
	  uint16_t iNumCM = 10000;
	fGX_Cal /= iNumCM;
		  fGY_Cal /= iNumCM;
		  fGZ_Cal /= iNumCM;
}
