#include <Arduino.h>

void p(const char *fmt, ... ) {
  char buf[256]; // resulting string limited in size
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, 256, fmt, args);
  va_end (args);
  Serial.print(buf);
}
