#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <Windows.h>
double masaUcreti=0;
int pirincMiktari=0;
double pirincMiktariKG=0;
pthread_mutex_t mutex;
time_t t;

void* yeme(){
pthread_mutex_lock(&mutex);

    srand((unsigned) time(&t));
    int yenilenPirinc = (rand()%5)+1;
    int yemeSuresi=(rand()%5)+1;


    pirincMiktari=pirincMiktari+(yenilenPirinc*100);
      usleep(yemeSuresi);
    pthread_mutex_unlock(&mutex);


}
int main()
{

    pthread_t th[80];
    int gelenFilozofSayisi=0;
    int tamMasaSayisi=0;
    int digerMasaSayisi=0;
    pthread_mutex_init(&mutex, NULL);

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


                if (pthread_create(&th[i*8+j], NULL, &yeme, NULL) != 0) {
                            perror("Failed to create thread");
                            return 1;
                   }

            }
            sleep(1);
             printf("Masa %d Yenilen Pirinc:%d gram\n",(i+1),pirincMiktari);
            masaUcreti=masaUcreti+99.90;
            if(pirincMiktari>2000){
                masaUcreti=masaUcreti+19.90;
            }
            pirincMiktariKG=pirincMiktari;
            pirincMiktariKG=pirincMiktariKG/1000;
            masaUcreti=masaUcreti+(pirincMiktariKG*20);
            printf("Masa %d Hesap:%f tl\n",(i+1),masaUcreti);
            masaUcreti=0;
            pirincMiktari=0;
        }
        pthread_mutex_destroy(&mutex);

    }
    else{
    tamMasaSayisi=gelenFilozofSayisi/8;
    digerMasaSayisi=gelenFilozofSayisi-(tamMasaSayisi*8);
    for (int i=0;i<tamMasaSayisi ;i++ ) {
        for (int j=0;j<8 ; j++) {
            if (pthread_create(&th[i*8+j], NULL, &yeme, NULL) != 0) {
                        perror("Failed to create thread");
                        return 1;
               }
        }
        sleep(1);
         printf("Masa %d Yenilen Pirinc:%d gram\n",(i+1),pirincMiktari);
        masaUcreti=masaUcreti+99.90;
        if(pirincMiktari>2000){
            masaUcreti=masaUcreti+19.90;
        }
        pirincMiktariKG=pirincMiktari;
        pirincMiktariKG=pirincMiktariKG/1000;
        masaUcreti=masaUcreti+(pirincMiktariKG*20);
        printf("Masa %d Hesap:%f tl\n",(i+1),masaUcreti);
        masaUcreti=0;
        pirincMiktari=0;
    }

        for (int j=0;j<digerMasaSayisi ; j++) {
            if (pthread_create(&th[tamMasaSayisi*8+j], NULL, &yeme, NULL) != 0) {
                        perror("Failed to create thread");
                        return 1;
               }
    }

        printf("Masa %d Yenilen Pirinc:%d gram\n",(tamMasaSayisi+1),pirincMiktari);

       masaUcreti=masaUcreti+99.90;
       if(pirincMiktari>2000){
           masaUcreti=masaUcreti+19.90;
       }
       pirincMiktariKG=pirincMiktari;
       pirincMiktariKG=pirincMiktariKG/1000;
       masaUcreti=masaUcreti+(pirincMiktariKG*20);
          printf("Masa %d Hesap:%f tl\n",(tamMasaSayisi+1),masaUcreti);

    pthread_mutex_destroy(&mutex);
    }



    return 0;
}

