/*
Main system control functions to comunication with interface.

HW InputBoard Revision A:

*/

#include ".\SystemControl.H"			// uwDeviceSignature()
#include "SystemControl.CFG"


uint8_t mubErrorCode = 0;
uint8_t mubInitDone = 0;

  /**
  * @brief Fuction which returns device signature
  * @param None
  * @retval const uwDevSig
  */
uint16_t uwSystemControl_DeviceSignatureGet(void)
{
	return uwDevSig;
}

  /**
  * @brief Fuction which returns hardware revision
  * @param None
  * @retval uwHWrev
  */
uint16_t uwSystemControl_HardwareRevisionGet(void)
{
	return uwHWrev;
}

  /**
  * @brief Fuction which returns firmware revision
  * @param None
  * @retval const uwFWrev
  */
uint16_t uwSystemControl_FirmwareRevisionGet(void)
{
	return uwFWrev;
}

  /**
  * @brief Fuction which returns setted system HSE
  * @param None
  * @retval HSE_VALUE/1000
  */
uint16_t uwSystemControl_SystemClockGet(void)
{
	return ((uint16_t)(HSE_VALUE/1000));
}

  /**
  * @brief Fuction which returns 1 when system is prepared, 0 when system is corrupted
  * @param None
  * @retval 0 or 1
  */
uint8_t ubSystemControl_DeviceStatusGet(void)
{
  if((mubErrorCode == 0) & (mubInitDone != 0))
  {
	return 0x01;
  } else {
	return 0x00;
  }
}

  /**
  * @brief Fuction which returns 1 when system is prepared, 0 when system is corrupted
  * @param None
  * @retval 0 or 1
  */
uint8_t SystemControl_ErrorCodeGet(void)
{
	return mubErrorCode;
}

void SystemControl_ErrorCodeSet(uint8_t lubErrorCode)
{
	mubErrorCode = lubErrorCode;
}

void SystemControl_InitDoneSet(uint8_t lubInitDone)
{
	mubInitDone = lubInitDone;
}