#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
double masaUcreti=0;
int pirincMiktari=0;
double pirincMiktariKG=0;
pthread_mutex_t mutex;
void* yeme(){
    sleep(rand()%5);

}
int main()
{
    srand(time(NULL));
    int a = (rand()%5)+1;
    printf("%d",a);
    pthread_t th[80];
    int gelenFilozofSayisi=0;
    int tamMasaSayisi=0;
    int digerMasaSayisi=0;
    printf("Gelicek Filozof Sayisini giriniz:");
    scanf("%d", &gelenFilozofSayisi);
    while(gelenFilozofSayisi>80){
        printf("girdiginiz sayi restoranin kapasitesini asiyor \n");
        printf("lutfen restoranin kapasitesini(80) asmayiniz\n");
        printf("Gelicek Filozof Sayisini giriniz:");
        scanf("%d", &gelenFilozofSayisi);
    }
    if(gelenFilozofSayisi%8==0){
        tamMasaSayisi=gelenFilozofSayisi/8;
        for (int i=0;i<tamMasaSayisi ;i++ ) {
            for (int j=0;j<8 ; j++) {
                if (pthread_create(th[i*8+j], NULL, &yeme, NULL) != 0) {
                            perror("Failed to create thread");
                            return 1;
                   }
            }
             printf("Masa %d Yenilen Pirinç:%d gram",(i+1),pirincMiktari);
            masaUcreti=masaUcreti+99,90;
            if(pirincMiktari>2000){
                masaUcreti=masaUcreti+19,90;
            }
            pirincMiktariKG=pirincMiktari;
            pirincMiktariKG=pirincMiktariKG/1000;
            masaUcreti=masaUcreti+(pirincMiktariKG*20);
            printf("Masa %d Hesap:%f tl",(i+1),masaUcreti);

        }
    }
    else{
    tamMasaSayisi=gelenFilozofSayisi/8;
    digerMasaSayisi=gelenFilozofSayisi-(tamMasaSayisi*8);
    for (int i=0;i<tamMasaSayisi ;i++ ) {
        for (int j=0;j<8 ; j++) {
            if (pthread_create(th[i*8+j], NULL, &yeme, NULL) != 0) {
                        perror("Failed to create thread");
                        return 1;
               }
        }
         printf("Masa %d Yenilen Pirinç:%d gram",(i+1),pirincMiktari);
        masaUcreti=masaUcreti+99,90;
        if(pirincMiktari>2000){
            masaUcreti=masaUcreti+19,90;
        }
        pirincMiktariKG=pirincMiktari;
        pirincMiktariKG=pirincMiktariKG/1000;
        masaUcreti=masaUcreti+(pirincMiktariKG*20);
        printf("Masa %d Hesap:%f tl",(i+1),masaUcreti);
        for (int j=0;j<8 ; j++) {
            if (pthread_create(th[i*8+j], NULL, &yeme, NULL) != 0) {
                        perror("Failed to create thread");
                        return 1;
               }
    }
        printf("Masa %d Yenilen Pirinç:%d gram",(tamMasaSayisi+1),pirincMiktari);
       masaUcreti=masaUcreti+99,90;
       if(pirincMiktari>2000){
           masaUcreti=masaUcreti+19,90;
       }
       pirincMiktariKG=pirincMiktari;
       pirincMiktariKG=pirincMiktariKG/1000;
       masaUcreti=masaUcreti+(pirincMiktariKG*20);
          printf("Masa %d Hesap:%f tl",(tamMasaSayisi+1),masaUcreti);


    }

}

    return 0;
}

