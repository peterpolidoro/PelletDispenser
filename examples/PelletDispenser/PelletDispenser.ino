#include <PelletDispenser.h>


PelletDispenser dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
