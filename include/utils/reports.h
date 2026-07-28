#ifndef REPORTS_H
#define REPORTS_H


void logging(int cnxt_pid, const char *fmt, ...);

void logging_wo_header(const char *fmt, ...);

int reports(double start, double end);

#endif