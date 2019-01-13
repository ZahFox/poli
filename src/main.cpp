#include <iostream>
#include "log.h"
#include "notes.h"

int main() {
  Log::Init();
  LOG_INFO("Application Started")
  Notes::Init();
  return 0;
}
