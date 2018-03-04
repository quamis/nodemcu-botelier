#include <Arduino.h>
#include <string.h>

void p(const char *fmt, ... ) {
  char buf[256]; // resulting string limited in size
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, 256, fmt, args);
  va_end (args);
  Serial.print(buf);
}


String fmt(const char *fmt, ... ) {
  char buf[512]; // resulting string limited in size
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, 512, fmt, args);
  va_end (args);
  return String(buf);
}
