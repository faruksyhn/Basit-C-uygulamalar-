#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
typedef struct
{
    char isim[100];
    long int kod;
    long int numara;
} telephone;

//
int main()
{
    setlocale(LC_ALL, "Turkish");
    telephone tel;
    FILE *ptel;
    ptel = fopen("TelefonRehber.txt","wb+");
    if(ptel==NULL)
    {
        printf("dosya yazma hatasi");
    }

    menu(ptel);
}
int menu(FILE *ptel)
{
    system("CLS");
    printf("\t   MENU\n\n");
	printf(" ------------------------- \n");
	printf("| 1. Kayit Ekle           |\n");
	printf("| 2. Telefonlari listele  |\n");
	printf("| 3. Kaydi duzenle        |\n");
	printf("| 4. Numara ile kayit bul |\n");
	printf("| 5. Isim ile kayit bul   |\n");
	printf("| 6. Kayit sil            |\n");
	printf("| 0. Cikis                |\n");
	printf(" ------------------------- \n");
        int secim;
        char isim[100];
        int no;

        printf("Seciminiz :");
        scanf("%d",&secim);
        if (secim == 1 || secim == 2 || secim == 3 || secim == 4 || secim == 5 || secim == 6 || secim == 0)
        {
            switch(secim)
            {
                case 1 : ekle(ptel); break;
                case 2 : listele(ptel); break;
                case 3 : duzenle(ptel); break;
                case 4 : numaraarama(ptel); break;
                case 5 : isimarama(ptel); break;
                case 6 : sil(ptel);break;
            }
        }
        else
        {
            system("CLS");
            printf("Yanlis secim yaptiniz!\n");
            printf("ana ekrana donmek icin 1\nCikis yapmak icin 2\n");
            int karar;
            scanf("%d",&karar);
            if(karar==1) menu(ptel);
            if(karar==2) exit(1);

        }
}

void ekle(FILE *ptel)
{
    system("CLS");
    FILE *ptel2;
    telephone tel;
    ptel=fopen("TelefonRehber.txt","rb+");
    if(ptel==NULL)
    {
        printf("dosya yazma hatasi");
    }
        printf("ismi Giriniz:");
        scanf("%s",&tel.isim);
        printf("Kodu Giriniz:");
        scanf("%d",&tel.kod);
        printf("Numarayi Giriniz:");
        scanf("%d",&tel.numara);
        fseek(ptel,(tel.kod)*sizeof(tel),SEEK_SET);
        fwrite(&tel,sizeof(tel),1,ptel);
        fclose(ptel);
    printf("\n\n Devam icin herhangi bir tusa basin");
    getch();
    menu(ptel);
}
//kodu sýfýr olan üyeler gösterilmiyor.

void listele(FILE *ptel)
{
    system("CLS");
    telephone tel;
    ptel=fopen("TelefonRehber.txt","rb+");
    while(!feof(ptel))
    {
        while(fread(&tel,sizeof(tel),1,ptel)==1)
        {
            if(tel.kod!=0)
            {
                printf("%s\t\t\t",tel.isim);
                printf("%d\t\t\t",tel.kod);
                printf("%d\n",tel.numara);break;
            }
        }
    }
    printf("\n\n Devam icin herhangi bir tusa basin");
    getch();
    menu(ptel);
}

//düzenleme yapýlan ismin kodu sýfýr olur ve ekranda görünmez yeni eklenen kayýt görünür.

int duzenle(FILE *ptel)
{
    char isim[100]; int sayac=0;
    telephone tel;
    if((ptel=fopen("TelefonRehber.txt","rb+"))==NULL)
    {
        printf("yazma hatasi");
        exit(1);
    }
    system("CLS");
    printf("Duzenlemek itediginiz ismi giriniz:");
    scanf("%s",isim);
    while(!feof(ptel))
    {
        fread(&tel,sizeof(tel),1,ptel);
        if(strcmp(tel.isim,isim)==0 && tel.kod!=0)
        {
            fseek(ptel,(tel.kod)*sizeof(tel),SEEK_SET);
            tel.kod=0;
            fwrite(&tel,sizeof(tel),1,ptel);
            printf("ismi Giriniz:");
            scanf("%s",&tel.isim);
            printf("Kodu Giriniz:");
            scanf("%d",&tel.kod);
            printf("Numarayi Giriniz:");
            scanf("%d",&tel.numara);
            fseek(ptel,(tel.kod)*sizeof(tel),SEEK_SET);
            fwrite(&tel,sizeof(tel),1,ptel);break;
        }
        if(feof(ptel))
        {
            int karar;
            system("CLS");
            printf("Girmis oldugunuz isim bulunamadi\nana ekrana donmek icin 1\ntekrar arama yapmak icin 2\n");
            scanf("%d",&karar);
            if(karar==1) menu(ptel);
            if(karar==2) duzenle(ptel);
        }
    }


    fclose(ptel);
    menu(ptel);
}

//girilen numara ile kayýtlý olan numaralar karþýlaþtýrlýr ama kodu sýfýr olanlar iþleme daihil olmazlar.

int numaraarama(FILE *ptel)
{
    int no;
    telephone tel;
    printf("\naranacak numarayi giriniz:");
    scanf("%d",&no);
    system("CLS");
    ptel=fopen("TelefonRehber.txt","r");
    while(!feof(ptel))
    {
        fread(&tel,sizeof(tel),1,ptel);
        if(no == tel.numara && tel.kod!=0)
        {
            printf("%s\t\t\t",tel.isim);
            printf("%d\t\t\t",tel.kod);
            printf("%d\n",tel.numara);
            break;
        }
        if(feof(ptel)) printf("Kayit bulunamadi");
    }
    printf("\n\n Devam icin herhangi bir tusa basin");
    getch();
    menu(ptel);
}

//girilen isim ile kayýtlý olan isimler karþýlaþtýrlýr ama kodu sýfýr olanlar iþleme daihil olmazlar.

int isimarama(FILE *ptel)
{
    char isim[100];
    telephone tel;
    if((ptel=fopen("TelefonRehber.txt","rb+"))==NULL)
    {
        printf("yazma hatasi");
        exit(1);
    }
    printf("Aranacan ismi giriniz:");
    scanf("%s",isim);
    system("CLS");
    while(fread(&tel,sizeof(tel),1,ptel)==1)
    {
        if(strcmp(tel.isim,isim)==0 && tel.kod!=0)
        {
            printf("%s\t\t\t",tel.isim);
            printf("%d\t\t\t",tel.kod);
            printf("%d\n",tel.numara);
        }
    }
    fclose(ptel);
    printf("\n\n Devam icin herhangi bir tusa basin");
    getch();
    menu(ptel);
}

//silinmesi istenen kodu sýfýr yapar ve ekranda görünmesini engeller.

int sil(FILE *ptel)
{
    int kod;
    telephone tel;
    if((ptel=fopen("TelefonRehber.txt","rb+"))==NULL)
    {
        printf("yazma hatasi");
        exit(1);
    }
    printf("Silmek istediginiz kaydin kodunu giriniz:");
    scanf("%d",&kod);
    system("CLS");
    while(!feof(ptel))
    {
        fread(&tel,sizeof(tel),1,ptel);
        if(kod==tel.kod)
        {
            fseek(ptel,(tel.kod)*sizeof(tel),SEEK_SET);
            tel.kod=0;
            fwrite(&tel,sizeof(tel),1,ptel);
            printf("Silme basarili");
            getch();break;
        }
        if(feof(ptel))
        {
            int karar;
            printf("Girmis oldugunuz kod bulunamadi\ntekrar islem yapmak icin 1\nana ekrana donmek icin 2\n");
            scanf("%d",&karar);
            if(karar==1) sil(ptel);
            if(karar==2) menu(ptel);
        }
    }

    fclose(ptel);
    menu(ptel);
}
