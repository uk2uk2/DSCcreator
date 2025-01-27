#ifndef DS_UTILS_H
#define DS_UTILS_H

#include "ds_common.h"

// File operations
int create_directory(const char* path);
int write_template_to_file(const char* filepath, const char* content);
bool file_exists(const char* filepath);

// String operations
void to_lower_case(char* str);
void create_header_guard(char* guard, const char* filename);

#endif // DS_UTILS_H
