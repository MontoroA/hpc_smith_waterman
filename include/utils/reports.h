#ifndef REPORTS_H
#define REPORTS_H

#include "collections/list.h"

typedef struct {
    double start_time;
    double end_time;
    List* matched_seq1;
    List* matched_seq2;
    //TODO otra data: resultado algoritmo, metadata de ejecucion, hiperparametros
} SWAReport;

void logging(int cnxt_pid, const char *fmt, ...);

void logging_wo_header(const char *fmt, ...);

void reports(SWAReport* report);

void free_Reports(SWAReport* report);

#endif