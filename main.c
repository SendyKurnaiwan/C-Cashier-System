#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct benda {
    char nama[50];
    int harga;
    int kuantity;
};

void delay(int seconds) {
    clock_t start_time = clock();
    while (clock() < start_time + seconds * CLOCKS_PER_SEC);
}
void rekapstruk(struct benda belanja[],struct tm *local_time,  int bendaselec[], int nomorselec, const char *fnama) {

    for (int i = 0; i < nomorselec - 1; i++) {
        for (int j = 0; j < nomorselec - i - 1; j++) {
            if (belanja[bendaselec[j]].kuantity < belanja[bendaselec[j + 1]].kuantity) {
                int temp = bendaselec[j];
                bendaselec[j] = bendaselec[j + 1];
                bendaselec[j + 1] = temp;
            }
        }
    }

    printf("Rekap Pesanan Barang           :\n");
    printf("=================================================================================================\n");
    printf("|No.| Jumlah | Nama Barang\t\t\t| Harga\t\t| Total Harga\t| Diskon\t|\n");
    printf("=================================================================================================\n");
     int totalharga = 0,totaldiskon = 0,totalbayar = 0,bayar = 0, kuanharga = 0,subtotal = 0, diskon = 0;
    for(int i = 0; i < nomorselec; i++) {
        int index = bendaselec[i];
        subtotal = belanja[index].harga * belanja[index].kuantity;
        kuanharga = subtotal;
        if (belanja[index].kuantity >= 5) {
            subtotal *= 0.85;
        } else if (belanja[index].kuantity >= 3) {
            subtotal *= 0.9;
        }
        totalharga += belanja[index].harga;
        diskon = kuanharga - subtotal;
        totaldiskon += diskon;
        totalbayar += subtotal;
        printf("| %d |\t%d    | %s\t\t\t| Rp.%d\t| Rp.%d\t| Rp.%d\t|\n",i + 1,belanja[index].kuantity, belanja[index].nama, belanja[index].harga,kuanharga, diskon);
    }
    printf("=================================================================================================\n");
    printf("Total Harga : Rp.%d,-\n", totalharga);
    printf("Total diskon : Rp.%d,-\n", totaldiskon);
    printf("Total Bayar : Rp.%d,-\n\n", totalbayar);
    printf("=================================================================================================\n");
    printf("Masukan Uang Bayar : ");
    scanf("%d", &bayar);
    int hasil = bayar - totalbayar;
    int hutang = totalbayar - bayar;
    if(hasil < 0){
        printf("Hutang : %d\n", hutang);
    }else{
        printf("Kembalian : %d\n", hasil);
    }

        //file txt struk
FILE *file = fopen(fnama, "w");
    fprintf(file, "Nama Struk: %s\n", fnama);
    fprintf(file, "=================================================================================\n");
    fprintf(file, "|\tNama Barang\t\t| Harga \t| Total \t| Diskon \t|\n");
    fprintf(file, "=================================================================================\n");
     for(int i = 0; i < nomorselec; i++) {
        int index = bendaselec[i];
        subtotal = belanja[index].harga * belanja[index].kuantity;
        kuanharga = subtotal;
        if (belanja[index].kuantity >= 5) {
            subtotal *= 0.85;

        } else if (belanja[index].kuantity >= 3) {
            subtotal *= 0.9;
        }
        totalharga += belanja[index].harga;
        diskon = kuanharga - subtotal;
        totaldiskon += diskon;
        totalbayar += subtotal;
        fprintf(file, "|\t%d x %s\t| Rp.%d\t| Rp.%d\t| Rp.%d\t|\n", belanja[index].kuantity, belanja[index].nama, belanja[index].harga, kuanharga, diskon);
    }

    fprintf(file, "=================================================================================\n");
    fprintf(file, "Total Harga : Rp.%d\n", totalharga);
    fprintf(file, "Total diskon : Rp.%d\n", totaldiskon);
    fprintf(file, "Total Bayar : Rp.%d\n", totalbayar);

    fprintf(file, "Waktu Hari: %s\n", asctime(local_time));
    fprintf(file, "=================================================================================\n");
    fclose(file);

}

int main () {
    time_t current_time;
    struct tm *local_time;
    current_time = time(NULL);
     local_time = localtime(&current_time);
    int pilihan,jumlahbenda = 5,nomorselec,bendaselec[5],totalbelanja;
    struct benda belanja[5];

    strcpy(belanja[0].nama, "Buku Tulis   ");
    belanja[0].harga = 5000;
    belanja[0].kuantity = 0;

    strcpy(belanja[1].nama, "Pensil       ");
    belanja[1].harga = 2000;
    belanja[1].kuantity = 0;

    strcpy(belanja[2].nama, "Penhapus     ");
    belanja[2].harga = 1000;
    belanja[2].kuantity = 0;

    strcpy(belanja[3].nama, "Penggaris    ");
    belanja[3].harga = 1000;
    belanja[3].kuantity = 0;

    strcpy(belanja[4].nama, "Bujur Sangkar");
    belanja[4].harga = 500;
    belanja[4].kuantity = 0;
    totalbelanja = 0;
    do{
        printf("=========================================================\n");
        printf("|No.| Barang\t\t| Harga\t\t\t\t|\n");
        printf("---------------------------------------------------------\n");
        for(int i = 0; i < jumlahbenda;i++)
        {
            printf("| %d | %s\t| Rp.%d\t\t\t|\n", i + 1 , belanja[i].nama, belanja[i].harga);
        }
        printf("=========================================================\n");
        printf("\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\n");
        printf("=========================================================\n");
        printf("| No.| Operasi\t\t\t\t\t\t|\n");
        printf("---------------------------------------------------------\n");
        printf("| 44 | Hapus Barang Keranjang\t\t\t\t|\n");
        printf("| 99 | Struk Pembayaran\t\t\t\t\t|\n");
        printf("| 55 | Kosongkan Keranjang\t\t\t\t|\n");
        printf("| 00 | Keluar\t\t\t\t\t\t|\n");
        printf("=========================================================\n");
        printf("Input Pilihan Yang Anda Inginkan : ");
        scanf("%d", &pilihan);
        switch(pilihan) {
            case 1 ... 5 :{
                int index = pilihan - 1 ;
                int i;
                for ( i = 0; i < nomorselec; i++) {
                    if (bendaselec[i] == index) {
                        belanja[index].kuantity++;
                        break;
                    }
                }
                if (i == nomorselec) {
                    bendaselec[nomorselec++] = index;
                    belanja[index].kuantity++;
                }
                printf("=========================================================\n");
                printf("%s telah ditambahkan\n", belanja[index].nama);
                printf("=========================================================\n");
                delay(1);
                system("cls");
            break;}
            case 44: {
                if (nomorselec > 0) {
                    printf("=========================================================\n");
                    printf("No\tBarang\t\tJumlah\n");
                    printf("=========================================================\n");
                    for (int i = 0; i < nomorselec; i++) {
                        int index = bendaselec[i];
                        printf("%d.\t%s\t\t%d\n", i + 1, belanja[index].nama, belanja[index].kuantity);
                    }
                    printf("=========================================================\n");
                    printf("Pilih barang yang ingin dihapus: ");
                    int delindex;
                    scanf("%d", &delindex);
                    if (delindex >= 1 && delindex <= nomorselec) {
                        int indexdel = bendaselec[delindex - 1];
                        belanja[indexdel].kuantity--;
                        if (belanja[indexdel].kuantity == 0) {
                            for (int i = delindex - 1; i < nomorselec - 1; i++) {
                                bendaselec[i] = bendaselec[i + 1];
                            }
                            nomorselec--;
                        }
                        printf("=========================================================\n");
                        printf("%s telah dihapus dari keranjang\n", belanja[indexdel].nama);
                        printf("=========================================================\n");
                        delay(1);
                        system("cls");
                    } else {
                        printf("=========================================================\n");
                        printf("Pilihan tidak valid\n");
                        printf("=========================================================\n");
                        delay(1);
                        system("cls");
                    }
                } else {
                    printf("=========================================================\n");
                    printf("Tidak Ada Barang Dikeranjang\n");
                    printf("=========================================================\n");
                    delay(1);
                    system("cls");
                }
                break;
            }

            case 99 : {
                if(nomorselec > 0 ){
                    char fnama[50];
                    sprintf(fnama, "Struk_%02d_%02d_%04d_%02d-%02d-%02d.txt", local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900,  local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
                    rekapstruk(belanja, local_time, bendaselec, nomorselec, fnama);
                        printf("=========================================================\n");
                        printf("Struk telah disimpan sebagai %s\n", fnama);
                        printf("=========================================================\n");
                    }else{
                    printf("=========================================================\n");
                    printf("Tidak Ada Barang Dikeranjang\n");
                    printf("=========================================================\n");
                    delay(1);
                    system("cls");
                }
            break;}
            case 55 : {
                totalbelanja = 0;
                nomorselec = 0;
                for(int i = 0; i < jumlahbenda;i++){
                    belanja[i].kuantity = 0;
                }
                printf("=========================================================\n");
                printf("Telah Di Reset");
                printf("=========================================================\n");
                delay(1);
                system("cls");
            break;}
            case 00 :
                printf("=========================================================\n");
                printf("Terimakasih Telah Menggunakan Program Kami\n");
                printf("=========================================================\n");
                delay(1);
                system("cls");
            break;
            }
        }while(pilihan != 9);
    }
