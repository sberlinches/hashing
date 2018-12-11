#include "utils.h"

 /**
 * Calculates and returns the modulus of a and b.
  *
 * @param a
 * @param b
 * @return
 */
long mod(long a, long b) {
    return (a % b + b) % b;
}