#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
  FILE *fp;
  char *str;
  char sval1,sval2,sval3,sval4,tval1,tval2,tval3,tval4;
  size_t num_of_bytes = 6;
  float korak = 0;
  float proizvod = 0;
  float period = 20000;
  int sd1, sd2 = 0;

  while(1)
    {

      //Citanje vrednosti tastera
      fp = fopen ("/dev/switch", "r");
      if(fp==NULL)
	{
	  puts("Problem pri otvaranju /dev/switch");
	  return -1;
	}


      str = (char *)malloc(num_of_bytes+1); 
      getline(&str, &num_of_bytes, fp); 

      if(fclose(fp))
	{
	  puts("Problem pri zatvaranju /dev/switch");
	  return -1;
	}


      sval1 = str[2] - 48;
      sval2 = str[3] - 48;
      sval3 = str[4] - 48;
      sval4 = str[5] - 48;
      free(str);

      //printf("Vrednosti prekidaca: %d %d %d %d \n",sval1,sval2,sval3,sval4);

      if(sval4 == 0 && sval3 == 0){
	korak = 0;
      }
      if(sval4 == 0 && sval3 == 1 ){
	korak = 0.1;
      }
      if(sval4 == 1 && sval3 == 0){
	korak = 0.2;
      }
      if(sval4 == 1 && sval3 == 1){
	korak = 0.3;
      }
      //printf("Korak inkrementacije osvetljenja: %f \n", korak);


      //Citanje vrednosti tastera
      fp = fopen ("/dev/button", "r");
      if(fp==NULL)
	{
	  puts("Problem pri otvaranju /dev/button");
	  return -1;
	}


      str = (char *)malloc(num_of_bytes+1); 
      getline(&str, &num_of_bytes, fp); 

      if(fclose(fp))
	{
	  puts("Problem pri zatvaranju /dev/button");
	  return -1;
	}


      tval1 = str[2] - 48;
      tval2 = str[3] - 48;
      tval3 = str[4] - 48;
      tval4 = str[5] - 48;
      free(str);

      //printf("Vrednosti tastera: %d %d %d %d \n",tval1,tval2,tval3,tval4);

		
      if(tval4 == 1 && sd1 == 0){
	if(proizvod < 1){
	  proizvod = proizvod + korak;
	  sd1 = 1;
	}}
      else
	sd1 = 0; 
		
      if(tval3 == 1 && sd2 == 0){
	if(proizvod > 0){
	  proizvod = proizvod - korak;
	  sd2 = 1;  }}
      else
	sd2 = 0;
			

   
  //----------------------------------------------------------------

  // Upali diode
  fp = fopen("/dev/led","w");
  if(fp == NULL){
    printf("Problem pri otvaranju /dev/led \n");
    return -1;}
  fputs("0x0F\n",fp);
  if(fclose(fp)){
    printf("Problem pri zatvaranju /dev/led \n");
    return -1; }
  usleep(proizvod*period);
		
  //Ugasi diode
  fp = fopen("/dev/led" , "w");
  if(fp == NULL){
    printf("Problem pri otvaranju /dev/led \n");
    return -1; }
  fputs("0x00\n", fp);
  if(fclose(fp)){
    printf("Problem pri zatvaranju /dev/led\n");
    return -1; }
  usleep((1-proizvod)*period);

}
}
