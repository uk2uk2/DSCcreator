const char* STRING_UTILS_TEMPLATE_C = R"(
#include "string_utils.h"
#include <ctype.h>
#include <string.h>

char* string_duplicate(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* dup = malloc(len + 1);
    if (dup) {
        memcpy(dup, str, len + 1);
    }
    return dup;
}

char* string_to_lower(char* str) {
    if (!str) return NULL;
    for (char* p = str; *p; p++) {
        *p = tolower(*p);
    }
    return str;
}

char* string_to_upper(char* str) {
    if (!str) return NULL;
    for (char* p = str; *p; p++) {
        *p = toupper(*p);
    }
    return str;
}

char* string_trim(char* str) {
    if (!str) return NULL;
    
    // Trim leading spaces
    while (isspace(*str)) str++;
    
    if (*str == 0) return str;
    
    // Trim trailing spaces
    char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    
    end[1] = '\0';
    return str;
}

char** string_split(const char* str, char delimiter, int* count) {
    if (!str || !count) return NULL;
    
    *count = 1;
    for (const char* p = str; *p; p++) {
        if (*p == delimiter) (*count)++;
    }
    
    char** result = malloc(*count * sizeof(char*));
    if (!result) return NULL;
    
    char* temp = string_duplicate(str);
    if (!temp) {
        free(result);
        return NULL;
    }
    
    int i = 0;
    char* token = strtok(temp, &delimiter);
    while (token) {
        result[i] = string_duplicate(token);
        if (!result[i]) {
            // Cleanup on failure
            while (--i >= 0) free(result[i]);
            free(result);
            free(temp);
            return NULL;
        }
        token = strtok(NULL, &delimiter);
        i++;
    }
    
    free(temp);
    return result;
}

void string_array_free(char** arr, int count) {
    if (!arr) return;
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}

bool string_ends_with(const char* str, const char* suffix) {
    if (!str || !suffix) return false;
    
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    
    if (suffix_len > str_len) return false;
    
    return strcmp(str + str_len - suffix_len, suffix) == 0;
}

bool string_starts_with(const char* str, const char* prefix) {
    if (!str || !prefix) return false;
    return strncmp(str, prefix, strlen(prefix)) == 0;
}
)";
