
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


int pomocna;

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

int main(void)
{

        int fd;
        int *p;
        FILE *tasteri;
        int maksimalna_vrednost_x = 639;
        int maksimalna_vrednost_y = 479;
        unsigned int ekran[680*480];
        int i;
        char stanje_tastera[7];

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

        i = 0;
        for(i; i <= 640 * maksimalna_vrednost_y + maksimalna_vrednost_x; i = i + 1){
                ekran[i] = 0;
        }
        i = 1;
        while(i > 0){

        //memcpy(p, image, MAX_PKT_SIZE);
        //sleep(5);
        memcpy(p, ekran, MAX_PKT_SIZE);
        sleep(2);
        kvadrat(ekran,1, 1, VELICINA_ZNAKA, 0xffff);
        memcpy(p, ekran, MAX_PKT_SIZE);
        sleep(2);
        iks(ekran, 60, 1, VELICINA_ZNAKA, 0xffff);
        memcpy(p, ekran, MAX_PKT_SIZE);
        sleep(2);
        trougao(ekran, 115, 1, VELICINA_ZNAKA, 0xffff);
        memcpy(p, ekran, MAX_PKT_SIZE);
        sleep(5);
        i = i - 1;
        }
        munmap(p, MAX_PKT_SIZE);
        fclose(tasteri);
        close(fd);
        return 0;
}

    
