#ifndef BUTTTON_H_
#define BUTTTON_H_

void button_init(void);
void button_onChange(void(*callback)(int buttonState));
int button_read(void);

#endif
