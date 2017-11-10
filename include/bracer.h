#ifndef BRACER_H_
#define BRACER_H_

#include "cmsis_os2.h"
void bracer_init(void (*app)(void *argument));

int32_t bracer_postEvent(
  void (*handler)(void* err, void* context),
  void* errorContext,
  void* eventContext,
  uint8_t  priority);

#endif
