#include "bracer.h"
#include "cmsis_os2.h"

#define EVENT_MESSAGE_QUEUE_SIZE 16

extern void SystemCoreClockUpdate(void);
void eventLoop(void *argument);

osThreadId_t eventLoop_threadId;
osMessageQueueId_t eventLoop_mQueueId;

typedef struct {
  void (*handler)(void* err, void* context);
  void* errorContext;
  void* eventContext;
} eventMessage_t;

void bracer_init(void (*app)(void *argument)){
  SystemCoreClockUpdate();
  osKernelInitialize();
  
  eventLoop_threadId = osThreadNew(eventLoop, NULL, NULL); 
  eventLoop_mQueueId = osMessageQueueNew(EVENT_MESSAGE_QUEUE_SIZE, sizeof(eventMessage_t), NULL);
  
  osThreadNew(app, NULL, NULL);
  
  osKernelStart();
}

void eventLoop(void *argument){
  eventMessage_t message;
  while(1){
    osMessageQueueGet(eventLoop_mQueueId, &message, NULL, osWaitForever);
    message.handler(message.errorContext, message.eventContext);
  }
}

int32_t bracer_postEvent(
  void (*handler)(void* err, void* context),
  void* errorContext,
  void* eventContext,
  uint8_t  priority)
{
  eventMessage_t message;
  message.handler = handler;
  message.errorContext = errorContext;
  message.eventContext = eventContext;
  
  return osOK == osMessageQueuePut(eventLoop_mQueueId, &message, priority, 0);
}
