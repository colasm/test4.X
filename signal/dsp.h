/*
 * File: dsp.h
 *
 * DSP engine setup for the real-time RIF filter (circular buffers in
 * X/Y memory, modulo addressing). The filtering itself runs in
 * filter.s (_RX_Callback), which reads taps/coeffs through this module.
 */

#ifndef DSP_H
#define	DSP_H

#include <stdint.h>

// NB: filter.s is plain assembly (no C preprocessor pass), so this value is
// duplicated there as ".equ FILTER_LENGTH,57" - keep both in sync by hand.
#define FILTER_LENGTH 57

extern int32_t taps[FILTER_LENGTH]; ///< Y-memory circular buffer : input samples history
extern int32_t coeffs[];            ///< X-memory filter coefficients, defined in filter.s

/**
 * @brief Place taps/coeffs as circular buffers and configure the DSP engine's
 *        modulo addressing (MODCON, X/YMODSRT, X/YMODEND) accordingly.
 */
void initCyclicBuffers(void);

#endif	/* DSP_H */
