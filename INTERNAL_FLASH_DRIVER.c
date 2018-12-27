#include "INTERNAL_FLASH_DRIVER.h"

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//it holds a page sized data
uint32_t OnePageDataHolder[FLASH_PAGE_MAX_DATA_COUNT];

void FlashLock(void)
{
	FLASH_Lock();
}

void ReadAndTransferData(uint32_t address)
{
	//control input data first
	assert(address <= (ADDR_FLASH_PAGE_64 - sizeof(uint32_t)));
	assert(address >= FLASH_DATA_PART_START_ADDRESS);
	
  uint32_t BaseAddress = address;
	if(((address - FLASH_DATA_PART_START_ADDRESS) % FLASH_PAGE_SIZE) != 0)
	{
		int dummy = (int)((address - FLASH_DATA_PART_START_ADDRESS) / FLASH_PAGE_SIZE);
		BaseAddress = (dummy * FLASH_PAGE_SIZE) + FLASH_DATA_PART_START_ADDRESS;
	}
	
	memset(OnePageDataHolder, 0, FLASH_PAGE_MAX_DATA_COUNT);
	int i = 0;
	for(i = 0; i < FLASH_PAGE_MAX_DATA_COUNT; i++)
	{
		(OnePageDataHolder[i]) = ReadWord(BaseAddress);
    BaseAddress += 4;
	}
}

void WriteData(uint32_t address, uint32_t *data, uint32_t len)
{	
	//control the input
	assert((data != NULL) && (len != 0));

	assert(address >= FLASH_DATA_PART_START_ADDRESS);
	assert(address <= FLASH_MAX_PAGE_BASE_ADDRESS);
	assert((address % sizeof(uint32_t)) == 0);

	//In order to hold other data, save them to an array
	ReadAndTransferData(address);

	//then find the base address of the input address
	uint32_t BaseAddress = address;
	if(((address - FLASH_DATA_PART_START_ADDRESS) % FLASH_PAGE_SIZE) != 0)
	{
		int dummy = (int)((address - FLASH_DATA_PART_START_ADDRESS) / FLASH_PAGE_SIZE);
		BaseAddress = (dummy * FLASH_PAGE_SIZE) + FLASH_DATA_PART_START_ADDRESS;
	}

	/* Unlock the Flash Bank1 Program Erase controller */
	FlashUnlock();

	/* Clear All pending flags */
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

	FLASH_Status FLASHStatus = FLASH_COMPLETE; 
	/* Erase the FLASH pages */
	FLASHStatus = FLASH_ErasePage(BaseAddress);

	assert(FLASHStatus == FLASH_COMPLETE);

	int i = 0;
	int j = 0;
	//change array data with user specified data
	int dataIndex = (int)((address - BaseAddress) / sizeof(uint32_t));

	assert((dataIndex + len) <= FLASH_PAGE_MAX_DATA_COUNT);

	for(i = dataIndex; i < (len + dataIndex); i++)
	{
		OnePageDataHolder[i] = data[j++];
	}

	/* Program Flash related whole page */
	uint32_t Address = BaseAddress;

	for(i = 0; i < FLASH_PAGE_MAX_DATA_COUNT; i++)
	{
	FLASHStatus = FLASH_ProgramWord(Address, OnePageDataHolder[i]);
	Address = Address + 4;
	}

	//lock the flash
	FlashLock();
}

void ReadData(uint32_t address, uint32_t *data, uint32_t len)
{
	//control the input
	assert((data != NULL) && (len != 0));
	
	assert(address >= FLASH_DATA_PART_START_ADDRESS);
	assert(address <= FLASH_MAX_PAGE_BASE_ADDRESS);
	assert((address % sizeof(uint32_t)) == 0);
	
	uint32_t Address = address;
	int i = 0;
	for(i = 0; i < len; i++)
	{
		data[i] = ReadWord(Address);
		Address += 4;
	}
	
}

void ClearFlash()
{
	/* Unlock the Flash Bank1 Program Erase controller */
	FlashUnlock();

	/* Clear All pending flags */
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

	FLASH_Status FLASHStatus = FLASH_COMPLETE; 

	/* Erase the FLASH pages */
	int EraseCounter = 0, NbrOfPage = 0;
	NbrOfPage = (FLASH_MAX_PAGE_BASE_ADDRESS - FLASH_DATA_PART_START_ADDRESS) / FLASH_PAGE_SIZE;
	for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
	{
	FLASHStatus = FLASH_ErasePage(FLASH_DATA_PART_START_ADDRESS + (FLASH_PAGE_SIZE * EraseCounter));
	}

	//lock the flash
	FlashLock();
}

void FlashUnlock(void)
{
	FLASH_Unlock();
}

uint32_t ReadWord(uint32_t address)
{
	return (*(__IO uint32_t*) address);
}
