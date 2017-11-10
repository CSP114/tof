#include "bracer.h"
#include "cmsis_os2.h"

extern void SystemCoreClockUpdate(void);
void event_loop(void *argument);

void bracer_init(void (*app)(void *argument)){
  SystemCoreClockUpdate();
  osKernelInitialize();
  osThreadNew(event_loop, NULL, NULL); 
  osThreadNew(app, NULL, NULL);
  osKernelStart();
}

void event_loop(void *argument){
  while(1){
  }
}
