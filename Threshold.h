/* ========================================================================= *
 * Threshold interface:
 * ========================================================================= */

#ifndef _THRESHOLD_H_
#define _THRESHOLD_H_

#include <stddef.h>

/* ------------------------------------------------------------------------- *
 * Estimates the estimated average threshold and its 5th and 95th percentiles.
 *
 * PARAMETERS
 * N         The size of the grid
 * T         The number of times the experiments must be repeated to compute
 *           the average and percentiles.
 *
 * NOTE
 * The returned structure should be cleaned $free$ after usage.
 *
 * RETURN
 * stats      A 3-elements array containing the 5th percentile,
 *            average threshold and 95th percentile in this order.
 *            On error, NULL is returned.
 * ------------------------------------------------------------------------- */
double* thresholdEstimate(size_t N, size_t T);

#endif // _THRESHOLD_H_
