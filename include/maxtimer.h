
extern "C" void DisableInterrupts_IMR_Low(int);

#define DISABLE_SYS_TIMER()  DisableInterrupts_IMR_Low(1 << 10); *((int*)(0x40000800)) = 0;
//? *((int*)(0x40000802)) = 1;
