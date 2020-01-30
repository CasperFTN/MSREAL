
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>
#define MAX_PKT_SIZE (640*480*4)
#define VELICINA_ZNAKA 50


int pomocna, pomocna2;
int random_simboli[6];
int pozicija_x, pozicija_y;
unsigned int ekran[640*480];
int *p;


void kvadrat(unsigned int *ekran, int x, int y, int duzina_stranica, unsigned int boja){

        pomocna = x;
        for(pomocna; pomocna < ( x + duzina_stranica); pomocna = pomocna + 1){
                ekran[640 * y + pomocna] = boja;
                ekran[640 * ( y + duzina_stranica - 1) + pomocna] = boja;
        }

        pomocna = y;
        for(pomocna; pomocna < (y + duzina_stranica); pomocna = pomocna + 1){
                ekran[640* pomocna + x] = boja;
                ekran[640 * pomocna + ( x + duzina_stranica - 1 )] = boja;
        }

}
void iks(unsigned *ekran, int x, int y, int velicina, unsigned int boja){

        pomocna = 0;
        for(pomocna; pomocna < velicina; pomocna = pomocna + 1){
                ekran[640 * ( y + pomocna ) + x + pomocna] = boja;
                ekran[640 * ( y + pomocna ) + x + velicina - 1 - pomocna] = boja;
        }
}
void trougao(unsigned *ekran, int x, int y, int velicina, unsigned int boja){

        pomocna = x;
        for(pomocna; pomocna < ( x + velicina ); pomocna = pomocna + 1){
                ekran[640 * ( y + velicina - 1 ) + pomocna] = boja;
        }

        pomocna = 0;
        for(pomocna; pomocna < velicina; pomocna = pomocna + 1){
                ekran[640 * 2 * ( y + pomocna ) + x + pomocna + velicina/2] = boja;
                ekran[640 * 2 * ( y + pomocna ) + x + velicina - 1 - pomocna - velicina/2] = boja;
        }

        pomocna = 640 * (velicina + 1);
        for(pomocna; pomocna < ( 640 * (( velicina * 2 ) + 1) ); pomocna = pomocna + 1 ){
                ekran[pomocna] = 0;
        }

}

//Funkcija za iscrtavanje kruga pisana od strane MagicWrath (github username)
void krug(unsigned int *display, int pos_x, int pos_y, int r, int part, unsigned int rgb) {
  float y_val;
  int prev_val_pos;
  int prev_val_neg;
  float common_op;
  int quantized_y;
  int x = pos_x - r;
  int i;

  for(x; x <= pos_x + r; x++) {

	common_op = sqrt(r*r - ( x - pos_x ) * ( x - pos_x ));

    //SOLUTIONS FOR THE POSITIVE VALUE OF THE ROOT
    if(part >= 0) {
      y_val = common_op  + pos_y;
      //printf("Calculated for x = %d, y_val = %f\n", x, y_val);
      quantized_y = (int) y_val;
      //printf("Quantized y_val is : %d\n\n", quantized_y);
      ekran[640 * quantized_y + x] = rgb;
      if(x == (pos_x - r))
        prev_val_pos = quantized_y;
      //printf("prev_val_pos : %d\n", prev_val_pos);
      //printf("quantized_y : %d\n", quantized_y);

      //draws a verical line from the previous y point to the new point
      if(prev_val_pos < quantized_y) {
        for(i = prev_val_pos; i < quantized_y; i++)
          ekran[640 * i + x] = rgb;
      } else {
        for(i = quantized_y; i < prev_val_pos; i++)
          ekran[640 * i + x] = rgb;
      }
      prev_val_pos = quantized_y;
    }

    //SOLUTIONS FOR THE NEGATIVE VALUE OF THE ROOT
    if(part <= 0) {
      y_val = pos_y - common_op;
      quantized_y = (int) y_val;
      if(x == pos_x - r)
        prev_val_neg = quantized_y;
      //printf("prev_val_neg : %d\n", prev_val_neg);
      //printf("quantized_y : %d\n", quantized_y);

      //same function as for the positive solutions
      if(prev_val_neg < quantized_y) {
        for(i = prev_val_neg; i < quantized_y;i++)
          ekran[640 * i + x] = rgb;
      } else {
        for(i = quantized_y; i < prev_val_neg ; i++)
          ekran[640 * i + x] = rgb;
      }
      prev_val_neg = quantized_y;
      ekran[640 * quantized_y + x] = rgb;
    }
}
}

void generisi_random(){

	srand(time(0));
        for(pomocna2 = 0; pomocna2 < 6; pomocna2 = pomocna2 + 1){
                random_simboli[pomocna2] = rand() % 4;
                switch(pomocna2){
		case 0:
			pozicija_x = 105;
			pozicija_y = 1;
			//printf("pomocna2 0\n");
			break;
		case 1:
                        pozicija_x = 175;
                        pozicija_y = 1;
		        //printf("pomocna2 1\n");
                        break;
		case 2:
                        pozicija_x = 245;
                        pozicija_y = 1;
			//printf("pomocna2 2\n");
                        break;
		case 3:
                        pozicija_x = 315;
                        pozicija_y = 1;
			//printf("pomocna2 3\n");
                        break;
		case 4:
                        pozicija_x = 375;
                        pozicija_y = 1;
			//printf("pomocna2 4\n");
                        break;
                case 5:
                        pozicija_x = 455;
                        pozicija_y = 1;
			//printf("pomocna2 5\n");
                        break;
		default:
			printf("nesto se zeznulo\n");
			break;
		}
		switch(random_simboli[pomocna2]){
		case 0:
			krug(ekran, pozicija_x + VELICINA_ZNAKA/2, pozicija_y + VELICINA_ZNAKA/2, VELICINA_ZNAKA/2, 0,  0xffff);
			printf("krug\n");
                        memcpy(p, ekran, MAX_PKT_SIZE);
			break;
		case 1:
                        iks(ekran, pozicija_x, pozicija_y, VELICINA_ZNAKA, 0xffff);
			printf("iks\n");
                        memcpy(p, ekran, MAX_PKT_SIZE);
			break;
	        case 2:
                        trougao(ekran, pozicija_x, pozicija_y, VELICINA_ZNAKA, 0xffff);
			printf("trougao\n");
                        memcpy(p, ekran, MAX_PKT_SIZE);
			break;
                case 3:
                        kvadrat(ekran, pozicija_x, pozicija_y, VELICINA_ZNAKA, 0xffff);
			printf("kvadrat\n");
                        memcpy(p, ekran, MAX_PKT_SIZE);
			break;
		}
        }
}

int main(void)
{

        int fd;
        FILE *tasteri;
        int maksimalna_vrednost_x = 639;
        int maksimalna_vrednost_y = 479;
        int i;
        char stanje_tastera[7];
	int k = 0;
	int pritisnuto_dugme = 0;
	int kraj = 0;

        fd = open("/dev/vga_dma", O_RDWR|O_NDELAY);
        if (fd < 0)
        {
                printf("Ne mogu otvoriti /dev/vga za upis! \n");
                return -1;
        }

        tasteri = fopen("/dev/button", "r");
        if(tasteri == NULL){
                printf("Ne mogu otvoriti /dev/button! \n");
                return -1;
        }
        p=(int*)mmap(0,640*480*4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        nova_igra: i = 0;
	for(i; i <= 640 * maksimalna_vrednost_y + maksimalna_vrednost_x; i = i + 1){
                ekran[i] = 0;
        }
        k = 1;
	//printf("stigao sam do ovde\n");
        memcpy(p, ekran, MAX_PKT_SIZE);
	//printf("prosao sam\n");
	generisi_random();
	memcpy(p, ekran, MAX_PKT_SIZE);
	sleep(2);

        i = 0;
        for(i; i <= 640 * maksimalna_vrednost_y + maksimalna_vrednost_x; i = i + 1){
                ekran[i] = 0;
        }
	memcpy(p, ekran, MAX_PKT_SIZE);
	//-------------POCINJEMO----------------------
	pozicija_x = 105;
	pozicija_y = 1;
	k = 0;
	while(1) {
	fread(stanje_tastera, 1, 7, tasteri);
	stanje_tastera[6] = '\0';
	if(pritisnuto_dugme == 0 && (strncmp("0b0000", stanje_tastera, 6) != 0)){
		pritisnuto_dugme = 1;
		sleep(0.05);

	if(strncmp("0b0001", stanje_tastera, 6) == 0){
        	if(random_simboli[k] == 0){
			krug(ekran, pozicija_x + VELICINA_ZNAKA/2, pozicija_y + VELICINA_ZNAKA/2, VELICINA_ZNAKA/2, 0,  0x07e0);
		}
		else{
			krug(ekran, pozicija_x + VELICINA_ZNAKA/2, pozicija_y + VELICINA_ZNAKA/2, VELICINA_ZNAKA/2, 0,  0xf000);
			kraj = 1;
		}
		k = k + 1;
		memcpy(p, ekran, MAX_PKT_SIZE);
		pozicija_x = pozicija_x + 70;
	}
	if(strncmp("0b0010", stanje_tastera, 6) == 0){
                if(random_simboli[k] == 2){
                        trougao(ekran, pozicija_x, pozicija_y, VELICINA_ZNAKA, 0x07e0);
                }
                else{
                        trougao(ekran, pozicija_x, pozicija_y, VELICINA_ZNAKA, 0xf000);
                        kraj = 1;
                }
		k = k + 1;
                memcpy(p, ekran, MAX_PKT_SIZE);
                pozicija_x = pozicija_x + 70;
        }
	 if(strncmp("0b0100", stanje_tastera, 6) == 0){
                if(random_simboli[k] == 1){
                        iks(ekran, pozicija_x, pozicija_y, VELICINA_ZNAKA, 0x07e0);
                }
                else{
                        iks(ekran, pozicija_x, pozicija_y, VELICINA_ZNAKA, 0xf000);
                        kraj = 1;
                }
		k = k + 1;
                memcpy(p, ekran, MAX_PKT_SIZE);
                pozicija_x = pozicija_x + 70;
        }
	if(strncmp("0b1000", stanje_tastera, 6) == 0){
                if(random_simboli[k] == 3){
                        kvadrat(ekran, pozicija_x, pozicija_y, VELICINA_ZNAKA, 0x07e0);
                }
                else{
                        kvadrat(ekran, pozicija_x, pozicija_y, VELICINA_ZNAKA, 0xf000);
                        kraj = 1;
                }
		k = k + 1;
                memcpy(p, ekran, MAX_PKT_SIZE);
                pozicija_x = pozicija_x + 70;
        }
	}

		if(strncmp("0b0000", stanje_tastera, 6) == 0){
			pritisnuto_dugme = 0;
		}
		if(k == 6){
			if(kraj == 1){
				printf("UNSUCCESSFUL \n");
				krug(ekran, 320, 240, 80, 0,  0xffe0);
                                krug(ekran, 295, 220, 5, 0, 0xffe0);
                                krug(ekran, 345, 220, 5, 0, 0xffe0);
                                krug(ekran, 320, 285, 30, -1, 0xffe0);
                                memcpy(p, ekran, MAX_PKT_SIZE);
				kraj = 0;
				sleep(5);

			}
			else{
				printf("GREAT GAME! \n");
				krug(ekran, 320, 240, 80 , 0,  0xffe0);
				krug(ekran, 295, 220, 5, 0, 0xffe0);
				krug(ekran, 345, 220, 5, 0, 0xffe0);
				krug(ekran, 320, 260, 30, 1, 0xffe0);
				memcpy(p, ekran, MAX_PKT_SIZE);
				sleep(5);

			}
		goto nova_igra;
		}
        }
        munmap(p, MAX_PKT_SIZE);
        fclose(tasteri);
        close(fd);
	//printf("Uspesan kraj programa!\n");
        return 0;
}

