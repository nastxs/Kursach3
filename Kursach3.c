// Kursach3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define FILENAME "projectors.dat"

typedef struct {
    char manufacturer[50];
    int electronic_drive; // 1 - да, 0 - нет
    float screen_diagonal;
    int technology_ALR; // 1 - да, 0 - нет
    char coating[50];
    float viewing_angle;
} Projector;

Projector projectors[MAX_RECORDS];
int total_records = 0;


void create_record();
void search_record();
void read_records_from_file();
void write_records_to_file();
void print_records();
void update_record();
void add_records();
void sort_records();





void create_record() {
    if (total_records >= MAX_RECORDS) {
        printf("Достигнуто максимальное количество записей.\n");
        return;
    }

    Projector p;
    printf("Введите производителя: ");
    scanf("%s", p.manufacturer);
    printf("Электронный привод (1 - да, 0 - нет): ");
    scanf("%d", &p.electronic_drive);
    printf("Диагональ экрана: ");
    scanf("%f", &p.screen_diagonal);
    printf("Технология ALR (1 - да, 0 - нет): ");
    scanf("%d", &p.technology_ALR);
    printf("Покрытие: ");
    scanf("%s", p.coating);
    printf("Угол обзора: ");
    scanf("%f", &p.viewing_angle);

    projectors[total_records++] = p;
}

void save_records(Projector* projectors, int count) {
    FILE* file = fopen(FILENAME, "wb");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }
    fwrite(projectors, sizeof(Projector), count, file);
    fclose(file);
    printf("Данные успешно сохранены в файл.\n");
}

int load_records(Projector* projectors) {
    FILE* file = fopen(FILENAME, "rb");
    if (!file) {
        perror("Ошибка открытия файла");
        return 0;
    }
    int count = fread(projectors, sizeof(Projector), MAX_RECORDS, file);
    fclose(file);
    return count;
}

int compare_by_manufacturer(const void* a, const void* b) {
    return strcmp(((Projector*)a)->manufacturer, ((Projector*)b)->manufacturer);
}

int compare_by_viewing_angle(const void* a, const void* b) {
    if (((Projector*)a)->viewing_angle < ((Projector*)b)->viewing_angle) return -1;
    if (((Projector*)a)->viewing_angle > ((Projector*)b)->viewing_angle) return 1;
    return 0;
}



void search_record() {
    char manufacturer[50];
    printf("Введите производителя для поиска: ");
    scanf("%s", manufacturer);

    for (int i = 0; i < total_records; ++i) {
        if (strcmp(projectors[i].manufacturer, manufacturer) == 0) {
            printf("Найдена запись: %s, %d, %.2f, %d, %s, %.2f\n",
                projectors[i].manufacturer,
                projectors[i].electronic_drive,
                projectors[i].screen_diagonal,
                projectors[i].technology_ALR,
                projectors[i].coating,
                projectors[i].viewing_angle);
            return;
        }
    }
    printf("Запись не найдена.\n");
}
void write_records_to_file() {
    FILE* file = fopen(FILENAME, "wb");
    if (!file) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }
    fwrite(projectors, sizeof(Projector), total_records, file);
    fclose(file);
}

void read_records_from_file() {
    FILE* file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Не удалось открыть файл для чтения.\n");
        return;
    }
    total_records = fread(projectors, sizeof(Projector), MAX_RECORDS, file);
    fclose(file);
}

void sort_records() {
    // Сортировка по производителю и углу обзора (пузырьком)
    for (int i = 0; i < total_records - 1; i++) {
        for (int j = 0; j < total_records - i - 1; j++) {
            if (strcmp(projectors[j].manufacturer, projectors[j + 1].manufacturer) > 0 ||
                (strcmp(projectors[j].manufacturer, projectors[j + 1].manufacturer) == 0 &&
                    projectors[j].viewing_angle > projectors[j + 1].viewing_angle)) {
                Projector temp = projectors[j];
                projectors[j] = projectors[j + 1];
                projectors[j + 1] = temp;
            }
        }
    }
}

void print_records() {
    sort_records();
    for (int i = 0; i < total_records; i++) {
        printf("%s, %d, %.2f, %d, %s, %.2f\n",
            projectors[i].manufacturer,
            projectors[i].electronic_drive,
            projectors[i].screen_diagonal,
            projectors[i].technology_ALR,
            projectors[i].coating,
            projectors[i].viewing_angle);
    }
}

void update_record() {
    char manufacturer[50];
    printf("Введите производителя для изменения: ");
    scanf("%s", manufacturer);

    for (int i = 0; i < total_records; ++i) {
        if (strcmp(projectors[i].manufacturer, manufacturer) == 0) {
            printf("Введите новый производитель: ");
            scanf("%s", projectors[i].manufacturer);
            printf("Электронный привод (1 - да, 0 - нет): ");
            scanf("%d", &projectors[i].electronic_drive);
            printf("Диагональ экрана: ");
            scanf("%f", &projectors[i].screen_diagonal);
            printf("Технология ALR (1 - да, 0 - нет): ");
            scanf("%d", &projectors[i].technology_ALR);
            printf("Покрытие: ");
            scanf("%s", projectors[i].coating);
            printf("Угол обзора: ");
            scanf("%f", &projectors[i].viewing_angle);
            printf("Запись обновлена.\n");
            return;
        }
    }
    printf("Запись не найдена.\n");
}

void add_records() {
    int n;
    printf("Введите количество записей для добавления: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        create_record();
    }
}






int main() {
    system("chcp 1251");
    int count = 0;
    int choice;
    read_records_from_file(); // загружаем существующие записи

    while (1) {
        printf("Выберите действие:\n");
        printf("1. Создать новую запись\n");
        printf("2. Поиск записи\n");
        printf("3. Печать всех записей\n");
        printf("4. Изменить запись\n");
        printf("5. Добавить новые записи\n");
        
        
        printf("6. Записать данные в файл\n");
        printf("7. Прочитать данные из файла\n");
        printf("8. Печать всех записей, отсортированных по производителю\n");
        printf("9. Печать всех записей, отсортированных по углу обзора\n");
        printf("10. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            create_record();
            break;
        case 2:
            search_record();
            break;
        case 3:
            print_records();
            break;
        case 4:
            update_record();
            break;
        case 5:
            add_records();
            break;

        case 6:
            save_records(projectors, count);
            break;

        case 7:
            count = load_records(projectors);
            printf("Загружено %d записей.\n", count);
            break;

        case 8:
            qsort(projectors, count, sizeof(Projector), compare_by_manufacturer);
            print_records(projectors, count);
            break;

        case 9:
            qsort(projectors, count, sizeof(Projector), compare_by_viewing_angle);
            print_records(projectors, count);
            break;

                

        case 10:
            write_records_to_file(); // сохраняем все записи перед выходом
            exit(0);
        default:
            printf("Неверный выбор!\n");
        }
    }
    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
