#ifndef UTILS_H
#define UTILS_H

#define M       2                       // positive reward for similarity match
#define mu      10                       // negative reward for similarity mismatch
#define GAP_W   3                       // gap penalty constant
#define s(a,b)  (((a)==(b)) ? M : -mu)  // similarity function
#define W(k)    (-(GAP_W) * (k))         // gap penalty function. If linearity of this function is altered, check for comment "//assumes linearity"
#define min(a,b) (((a)<(b)) ? (a) : (b))
#define max(a,b) (((a)>(b)) ? (a) : (b))

typedef enum {
    UP = 0,
    DIAG = 1,
    LEFT = 2
} Direction;

#endif