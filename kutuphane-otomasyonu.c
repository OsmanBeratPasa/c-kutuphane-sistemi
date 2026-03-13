#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char ad[100];
    char yazar[50];
    int durum; 
} Kitap;


void bufferTemizle() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void kitapEkle() {
    FILE *dosya = fopen("kutuphane_veriler.txt", "a");
    if (dosya == NULL) {
        printf("Hata: Veritabani dosyasi acilamadi!\n");
        return;
    }

    Kitap yeniKitap;
    printf("\n--- Yeni Kitap Kaydi ---\n");
    printf("Kitap ID: ");
    
    if (scanf("%d", &yeniKitap.id) != 1) {
        printf("Hata: Gecersiz ID. Lutfen sadece sayi girin!\n");
        bufferTemizle();
        fclose(dosya);
        return;
    }
    bufferTemizle(); 

    printf("Kitap Adi: ");
    fgets(yeniKitap.ad, 100, stdin);
    yeniKitap.ad[strcspn(yeniKitap.ad, "\n")] = 0; 

    printf("Yazar Adi: ");
    fgets(yeniKitap.yazar, 50, stdin);
    yeniKitap.yazar[strcspn(yeniKitap.yazar, "\n")] = 0;

    yeniKitap.durum = 1; 

    fprintf(dosya, "%d;%s;%s;%d\n", yeniKitap.id, yeniKitap.ad, yeniKitap.yazar, yeniKitap.durum);
    fclose(dosya);
    printf("Islem basarili: Kitap sisteme eklendi!\n");
}

void tumKitaplariListele() {
    FILE *dosya = fopen("kutuphane_veriler.txt", "r");
    if (dosya == NULL) {
        printf("Sistemde henuz kayitli kitap yok veya dosya bulunamadi.\n");
        return;
    }

    Kitap k;
    char satir[256];
    printf("\n--- Kutuphane Envanteri ---\n");
    printf("ID\t| Kitap Adi\t\t| Yazar\t\t\t| Durum\n");
    printf("------------------------------------------------------------------\n");

    while (fgets(satir, sizeof(satir), dosya)) {
        char *parca = strtok(satir, ";");
        if (parca != NULL) k.id = atoi(parca); 

        parca = strtok(NULL, ";");
        if (parca != NULL) strcpy(k.ad, parca);

        parca = strtok(NULL, ";");
        if (parca != NULL) strcpy(k.yazar, parca);

        parca = strtok(NULL, "\n"); 
        if (parca != NULL) k.durum = atoi(parca);
        
        char durumBilgisi[20];
        if (k.durum == 1) {
            strcpy(durumBilgisi, "Rafta");
        } else {
            strcpy(durumBilgisi, "Odunc Verildi");
        }

        printf("%d\t| %-20s\t| %-20s\t| %s\n", k.id, k.ad, k.yazar, durumBilgisi);
    }
    fclose(dosya);
}

void kitapAra() {
    FILE *dosya = fopen("kutuphane_veriler.txt", "r");
    if (dosya == NULL) {
        printf("Dosya hatasi!\n");
        return;
    }

    char aranan[100];
    printf("Aranacak kitap adini girin: ");
   
    fgets(aranan, 100, stdin);
    aranan[strcspn(aranan, "\n")] = 0;

    Kitap k;
    char satir[256];
    int bulundu_mu = 0;

    while (fgets(satir, sizeof(satir), dosya)) {
        char *parca = strtok(satir, ";");
        if (parca != NULL) k.id = atoi(parca);

        parca = strtok(NULL, ";");
        if (parca != NULL) strcpy(k.ad, parca);

        parca = strtok(NULL, ";");
        if (parca != NULL) strcpy(k.yazar, parca);

        parca = strtok(NULL, "\n");
        if (parca != NULL) k.durum = atoi(parca);

        if (strcmp(k.ad, aranan) == 0) {
            printf("\nBulundu! ID: %d, Yazar: %s, Durumu: %s\n", k.id, k.yazar, k.durum == 1 ? "Rafta" : "Odunc");
            bulundu_mu = 1;
            break; 
        }
    }

    if (bulundu_mu == 0) {
        printf("Aradiginiz kitap kutuphanede bulunamadi.\n");
    }
    fclose(dosya);
}

int main() {
    int secim;
    
    while (1) {
        printf("\n=================================\n");
        printf("  KUTUPHANE YONETIM OTOMASYONU\n");
        printf("=================================\n");
        printf("1. Yeni Kitap Ekle\n");
        printf("2. Tum Kitaplari Listele\n");
        printf("3. Kitap Ara\n");
        printf("4. Cikis Yap\n");
        printf("Islem Seciniz (1-4): ");
        
        
        if (scanf("%d", &secim) != 1) {
            printf("\nHata: Lutfen menuden gecerli bir rakam girin!\n");
            bufferTemizle(); 
            continue;        
        }
        bufferTemizle(); 

        switch (secim) {
            case 1:
                kitapEkle();
                break;
            case 2:
                tumKitaplariListele();
                break;
            case 3:
                kitapAra();
                break;
            case 4:
                printf("Programdan cikiliyor. Iyi gunler...\n");
                exit(0);
            default:
                printf("Hatali secim yaptiniz! Lutfen tekrar deneyin.\n");
        }
    }
    return 0;
}