#define GRLSN2008_cxx
#include "GRLSN2008.h"


bool GRLSN2008::HasGoodRecolectedDataList(string s, unsigned long int g)
{

  if(s=="SierraNegra_2008_01_19_08h00.root" && gps==79455486) return true;
  if(s=="SierraNegra_2008_01_26_12h00.root" && gps==80077509) return true;
  if(s=="SierraNegra_2008_01_29_08h00.root" && gps==80319411) return true;
  if(s=="SierraNegra_2008_03_06_01h00.root" && gps==83491169) return true;
  if(s=="SierraNegra_2008_11_09_19h00.root" && gps==104985740) return true;
  if(s=="SierraNegra_2008_11_10_02h00.root" && gps==105012511) return true;
  if(s=="SierraNegra_2008_11_12_19h00.root" && gps==105243124) return true;
  if(s=="SierraNegra_2008_11_14_03h00.root" && gps==105359368) return true;
  if(s=="SierraNegra_2008_11_15_00h00.root" && gps==105433831) return true;
  if(s=="SierraNegra_2008_12_06_19h00.root" && gps==107316952) return true;
  if(s=="SierraNegra_2008_12_16_22h00.root" && gps==108192300) return true;
  
  return false

}
