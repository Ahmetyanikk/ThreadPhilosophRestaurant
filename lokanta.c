#include <stdio.h>

int main()
{
    int gelenFilozofSayisi=0;
    printf("Gelicek Filozof Sayisini giriniz:");
    scanf("%d", &gelenFilozofSayisi);
    while(gelenFilozofSayisi>80){
        printf("girdiginiz sayi restoranin kapasitesini asiyor \n");
        printf("lutfen restoranin kapasitesini(80) asmayiniz\n");
        printf("Gelicek Filozof Sayisini giriniz:");
        scanf("%d", &gelenFilozofSayisi);
    }
    double a = 15;
    a=15/8;
    if(a>1){
         printf("%f",a);
    }

    return 0;
}
