#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "utils/reports.h"
#include "runtime/mpi_handler.h"

void write_in_file(const char* filepath, char* data, const int length) {
    FILE *filePointer = fopen(filepath, "ab");
    if(filePointer == NULL){
        logging(0, "Could not open file for writing: %s\n", filepath);
    }

    fwrite(data, 1, length, filePointer);
    fclose(filePointer);
}


char* now(){
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);

    struct tm tm;
    localtime_r(&ts.tv_sec, &tm);    

    static char buffer[100];
    snprintf(buffer, sizeof(buffer), "%04d/%02d/%02d %02d:%02d:%02d:%03ld\n",
           tm.tm_year + 1900,
           tm.tm_mon + 1,
           tm.tm_mday,
           tm.tm_hour,
           tm.tm_min,
           tm.tm_sec,
           ts.tv_nsec / 1000000);

    return strtok(buffer, "\n");
}


// void logging(int cnxt_pid, const char *fmt, ...)
// {
//     va_list args;
//     va_start(args, fmt);
    
//     if (cnxt_pid == MASTER_RANK)
//     {
//         printf("[  MASTER  %s] - ", now());
//         vprintf(fmt, args);
//     }
//     else
//     {
//         printf("[PROCESS %d %s] - ", cnxt_pid, now());
//         vprintf(fmt, args);
//     }
//     va_end(args);
//     printf("\n");
// }

void logging(int cnxt_pid, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char message[4096];
    vsnprintf(message, sizeof(message), fmt, args);

    va_end(args);

    char output[8192];
    char filepath[256];

    if (cnxt_pid == MASTER_RANK)
    {
        snprintf(filepath, sizeof(filepath), "./data/temp/master");
        snprintf(output, sizeof(output),
                 "[  MASTER  %s] - %s\n",
                 now(),
                 message);
    }
    else
    {
        snprintf(filepath, sizeof(filepath),
                 "./data/temp/%d", cnxt_pid);

        snprintf(output, sizeof(output),
                 "[PROCESS %d %s] - %s\n",
                 cnxt_pid,
                 now(),
                 message);
    }

    write_in_file(filepath, output, strlen(output));
}


void logging_wo_header(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void reports(SWAReport* report)
{
    //TODO: implementar primitiva en messages para recibir reportes de los workers
    double tiempo = report->end_time - report->start_time;
    printf("Tiempo de ejecución: %f segundos\n", tiempo);

    save_list(report->matched_seq1, "./data/temp/matched_seq1.txt");
    save_list(report->matched_seq2, "./data/temp/matched_seq2.txt");

}

void free_Reports(SWAReport* report)
{
    free(report);
}