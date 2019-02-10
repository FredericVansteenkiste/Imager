#include "global.h"

int iRevertColor(const int& iColor)
{
   int iOutput(iColor + 128);
   while(iOutput > 255)
   {
      iOutput -= 256;
   }

   return iOutput;
}
