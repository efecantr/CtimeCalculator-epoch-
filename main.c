#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <math.h>

// Girilen tarih bilgilerinin saklayan struct
typedef struct {
    int year, month, day, hour, minute, second;
} DateTime;

// Struct ve epoch zamanýný bir arada tutan union
typedef union {
    DateTime dt;
    time_t epoch;
} TimeConverter;

// Girilen tarihleri epoch zamanýna çeviren fonksiyon
time_t convertToEpoch(const DateTime *dt) {
    struct tm timeInfo = {0};
    timeInfo.tm_year = dt->year - 1900;
    timeInfo.tm_mon = dt->month - 1;
    timeInfo.tm_mday = dt->day;
    timeInfo.tm_hour = dt->hour;
    timeInfo.tm_min = dt->minute;
    timeInfo.tm_sec = dt->second;
    timeInfo.tm_isdst = -1;

    time_t result = mktime(&timeInfo);
    if(result == -1) {
        fprintf(stderr, "Gecersiz tarih/saat girisi!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void inputDateTime(DateTime *dt) {
    printf("Tarih ve saati girin (YYYY MM DD HH MM SS): ");
    if(scanf("%d %d %d %d %d %d", 
        &dt->year, &dt->month, &dt->day,
        &dt->hour, &dt->minute, &dt->second) != 6) {
        fprintf(stderr, "Hatali giris formatý!\n");
        exit(EXIT_FAILURE);
    }
    
    // Basit tarih sýnamasý
    if(dt->year < 1900 || dt->month < 1 || dt->month > 12 || 
       dt->day < 1 || dt->day > 31 || dt->hour < 0 || dt->hour > 23 || 
       dt->minute < 0 || dt->minute > 59 || dt->second < 0 || dt->second > 59) {
        fprintf(stderr, "Gecersiz tarih/saat degeri!\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    TimeConverter time1, time2;

    inputDateTime(&time1.dt);
    inputDateTime(&time2.dt);

    time1.epoch = convertToEpoch(&time1.dt);
    time2.epoch = convertToEpoch(&time2.dt);

    double difference = difftime(time1.epoch, time2.epoch);

    printf("\nBirinci tarihin Epoch zamani: %lld\n", (long long)time1.epoch);
    printf("Ikinci tarihin Epoch zamani: %lld\n", (long long)time2.epoch);
    printf("Iki tarih arasindaki zaman farki: %.0f saniye\n", fabs(difference));

    return 0;
}
