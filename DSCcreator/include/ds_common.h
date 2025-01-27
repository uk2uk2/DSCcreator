 /**
 * @file ds_common.h
 * @brief Common definitions and utilities for data structures
 * @author DSCcreator
 * @version 1.0
 */

#ifndef DS_COMMON_H
#define DS_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/** @brief Success return code */
#define DS_OK       0
/** @brief Error return code */
#define DS_ERROR   -1

/**
 * @brief Safely free memory and set pointer to NULL
 * @param p Pointer to free
 */
#define SAFE_FREE(p) do { if (p) { free(p); (p) = NULL; } } while(0)

#endif // DS_COMMON_H 
