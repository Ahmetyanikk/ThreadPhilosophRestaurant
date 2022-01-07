#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> // random için kullandığım kütüp hane
#include <unistd.h> // sleep kodunu linuxda çalıştırmak için kullandığımız kütüphane

double masaUcreti=0;
int pirincMiktari=0;
double pirincMiktariKG=0;
// 7,8,9 genelde kullandığım kütüphane
pthread_mutex_t mutex;
time_t t;

void* yeme(){
    // threadler arası problem olmasın diye lock düzeneği kurdum
pthread_mutex_lock(&mutex);

    srand((unsigned) time(&t));// random için seed oluşturuan komut burda
    int yenilenPirinc = (rand()%5)+1;//random sayesinde 1-5 arası sayı döndürüyor
    int yemeSuresi=(rand()%5)+1;


    pirincMiktari=pirincMiktari+(yenilenPirinc*100);// yenilen pirinçi genel pirinç miktarına ekliyorum
      usleep(yemeSuresi);// yeme süresince milisaniye  bekletiyor
    pthread_mutex_unlock(&mutex);


}
int main()
{

    pthread_t th[80];// gelicek filozofları tutan thread arrayi
    int gelenFilozofSayisi=0;
    int tamMasaSayisi=0;
    int digerMasaSayisi=0;
    pthread_mutex_init(&mutex, NULL);

    printf("Gelicek Filozof Sayisini giriniz:");
    scanf("%d", &gelenFilozofSayisi);
    while(gelenFilozofSayisi>80){//gelicek filozof sayısı 80den fazla ise tekrar alıyorum
        printf("girdiginiz sayi restoranin kapasitesini asiyor \n");
        printf("lutfen restoranin kapasitesini(80) asmayiniz\n");
        printf("Gelicek Filozof Sayisini giriniz:");
        scanf("%d", &gelenFilozofSayisi);
    }

    if(gelenFilozofSayisi%8==0){     // eğer gelen filozof sayısı masaları tam dolduruyorsa burdan devam ediyor
        tamMasaSayisi=gelenFilozofSayisi/8;// masalardaki hesapları teker teker yazdırmak için  masa sayısını aldım
        for (int i=0;i<tamMasaSayisi ;i++ ) {     
            for (int j=0;j<8 ; j++) {// masalar dolu olduğu için 8er thread oluşturuyor


                if (pthread_create(&th[i*8+j], NULL, &yeme, NULL) != 0) {//burda thread oluşturuyoruz yukarıda yazdığımız arrayi alıp yeme düşünce döngüsü için yeme() kodunu çağırıyorum
                            perror("Failed to create thread");// hata olursa diye perror duruyor
                            return 1;
                   }

            }
            sleep(1); // yeme fonksiyonu içindeki usleep fonksiyonu değerleri bozmasın diye 1 saniye bekletiyorum
             printf("Masa %d Yenilen Pirinc:%d gram\n",(i+1),pirincMiktari);// masa numarası ve masa pirinç miktarını yazdırıyorum
            masaUcreti=masaUcreti+99.90;
            if(pirincMiktari>=2000){
                masaUcreti=masaUcreti+19.90;
            }
            else if(2000>pirincMiktari>=4000){
                masaUcreti=masaUcreti+39,80;
            }
            pirincMiktariKG=pirincMiktari;
            pirincMiktariKG=pirincMiktariKG/1000;
            masaUcreti=masaUcreti+(pirincMiktariKG*20);// ücreti kilo bazlı aldığımız için kioya çevirip hesabı öyle alıyorum
            printf("Masa %d Hesap:%f tl\n",(i+1),masaUcreti);// masa numarası ve masa hesabını yazdırıyorum
            masaUcreti=0;
            pirincMiktari=0;
        }
        pthread_mutex_destroy(&mutex);

    }
    else{
        // eğer masalardan biri tam dolmadıysa kod burdan devam ediyor
        //80den 103e kadar kod  diğer kısım ile aynı(81 hariç)
    tamMasaSayisi=gelenFilozofSayisi/8;
    digerMasaSayisi=gelenFilozofSayisi-(tamMasaSayisi*8);// tam dolmayan masada kaç kişi olmadığını bulmak için, gelen filozof sayısından tam masadaki insanları çıkartıyorum
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
        else if(2000>pirincMiktari>=4000){
            masaUcreti=masaUcreti+39,80;
        }
        pirincMiktariKG=pirincMiktari;
        pirincMiktariKG=pirincMiktariKG/1000;
        masaUcreti=masaUcreti+(pirincMiktariKG*20);
        printf("Masa %d Hesap:%f tl\n",(i+1),masaUcreti);
        masaUcreti=0;
        pirincMiktari=0;
    }

        for (int j=0;j<digerMasaSayisi ; j++) {// masadaki kişi sayısı değişken olduğu için 8 yerine digerMasaSayisi değişkenini kullandım
            if (pthread_create(&th[tamMasaSayisi*8+j], NULL, &yeme, NULL) != 0) {
                        perror("Failed to create thread");
                        return 1;
               }
    }
//107 ve 124  numaralı satırlar önceki hesaplar ile aynı
        printf("Masa %d Yenilen Pirinc:%d gram\n",(tamMasaSayisi+1),pirincMiktari);

       masaUcreti=masaUcreti+99.90;
       if(pirincMiktari>2000){
           masaUcreti=masaUcreti+19.90;
       }
       else if(2000>pirincMiktari>=4000){
           masaUcreti=masaUcreti+39,80;
       }
       pirincMiktariKG=pirincMiktari;
       pirincMiktariKG=pirincMiktariKG/1000;
       masaUcreti=masaUcreti+(pirincMiktariKG*20);
          printf("Masa %d Hesap:%f tl\n",(tamMasaSayisi+1),masaUcreti);// masa numarasını bulmak için tam masa sayısının bir fazlasını koydum

    pthread_mutex_destroy(&mutex);
    }



    return 0;
}

