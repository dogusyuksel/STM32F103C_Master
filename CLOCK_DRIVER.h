
#ifndef _CLOCK_DRIVER
#define _CLOCK_DRIVER
      
		/*
		* Note that: This enum refers to SYSCLK frequency.
		* After setting this, other prescalars will be minimum to set maximum frequency of other busses.
		* some critical restrictions here:
		*			HCLK  --> cannot exceed 72MHz
		*			PCLK1 --> cannot exceed 36MHz
		*			PCLK2 --> cannot exceed 72MHz
		*/
			typedef enum {
				MHz_8,
				MHz_12,
				MHz_16,
				MHz_24,
				MHz_32,
				MHz_48,
				MHz_64,
				MHz_72
			} ClockFrequency;
			
			typedef enum {
				EXTERNAL,
				INTERNAL
			} OscillatorSelection;
			
      void InitClock(OscillatorSelection oscillatorType, ClockFrequency oscillatorFrequency);
	  
#endif
