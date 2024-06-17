#include <stdio.h>
#include <math.h>

void displayMenu() {
    printf("\nMenu Utama:\n");
    printf("1. Cek Saldo\n");
    printf("2. Tarik Tunai\n");
    printf("3. Setor Tunai\n");
    printf("4. Ubah PIN\n");
    printf("5. Keluar\n");
}

int main() {
    int selectedCard = 0;  
    int cardPins[3] = {0, 1234, 5678};  
    double cardBalances[3] = {0.0, 5000000, 800000}; 

    while (1) {
        if (selectedCard == 0) {
            printf("Selamat Datang di BANK FADLI silahkan Pilih kartu anda (1 untuk Kartu 1, 2 untuk Kartu 2, 0 untuk keluar): ");
            scanf("%d", &selectedCard);

            if (selectedCard == 0) {
                printf("Keluar dari ATM. Sampai jumpa!\n");
                break;
            }
        }

        int attempts = 0;
        int pin;
        while (attempts < 3) {
            printf("Masukkan PIN: ");
            scanf("%d", &pin);

            if (pin == cardPins[selectedCard]) {
                printf("PIN diterima. Selamat datang di BANK FADLI!\n");
                break;
            } else {
                attempts++;
                printf("PIN tidak benar. Upaya tersisa: %d\n", 3 - attempts);

                if (attempts == 3) {
                    printf("Kartu diblokir. Silakan hubungi bank.\n");
                    selectedCard = 0;
                }
            }
        }

        if (selectedCard == 0) {
            continue;  
        }

        double balance = cardBalances[selectedCard];
        while (1) {
            displayMenu();

            int choice;
            printf("Pilih pilihan: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Saldo: £%.2lf\n", balance);
                    break;
                case 2:
                    double withdrawAmount;
                    printf("Masukkan jumlah tarik tunai: £");
                    scanf("%lf", &withdrawAmount);

                    if (withdrawAmount <= balance && withdrawAmount > 0 && fmod(withdrawAmount, 5.0) == 0) {
                        balance -= withdrawAmount;
                        printf("Tarik tunai: £%.2lf\n", withdrawAmount);
                    } else {
                        printf("Jumlah tarik tunai tidak valid atau saldo tidak cukup.\n");
                    }
                    break;
                case 3:
                    double depositAmount;
                    printf("Masukkan jumlah setor tunai: £");
                    scanf("%lf", &depositAmount);

                    if (depositAmount > 0) {
                        balance += depositAmount;
                        printf("Setor tunai: £%.2lf\n", depositAmount);
                    } else {
                        printf("Jumlah setor tunai tidak valid.\n");
                    }
                    break;
                case 4:
                    int newPin;
                    printf("Masukkan PIN baru (4 digit): ");
                    scanf("%d", &newPin);

                    if (newPin >= 1000 && newPin <= 9999) {
                        cardPins[selectedCard] = newPin;
                        printf("PIN dibuat ulang dengan sukses.\n");
                    } else {
                        printf("Format PIN tidak valid. PIN tidak dibuat ulang.\n");
                    }
                    break;
                case 5:
                    printf("Transaksi selesai.\n");
                    cardBalances[selectedCard] = balance;
                    selectedCard = 0;  
                    break;
                default:
                    printf("Pilihan tidak valid.\n");
            }

            char anotherTransaction;
            printf("Apakah Anda ingin melakukan transaksi lain? (Y/N): ");
            scanf(" %c", &anotherTransaction);
            if (anotherTransaction != 'Y' && anotherTransaction != 'y') {
                printf("Keluar dari ATM. Sampai jumpa!\n");
                break;
            }
        }
    }

    return 0;
}
