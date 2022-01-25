#include <sys/cdefs.h>
int __system_property_get(const char* __name, char* __value);
int atoi(const char* __s) __attribute_pure__;
int android_get_device_api_level() {
  char value[92] = { 0 };
  if (__system_property_get("ro.build.version.sdk", value) < 1) return -1;
  int api_level = atoi(value);
  return (api_level > 0) ? api_level : -1;
}
  
