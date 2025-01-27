const char* FILE_UTILS_TEMPLATE_C = R"(
#include "file_utils.h"
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

bool file_exists(const char* path) {
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

bool create_directory(const char* path) {
#ifdef _WIN32
    return _mkdir(path) == 0 || errno == EEXIST;
#else
    return mkdir(path, 0755) == 0 || errno == EEXIST;
#endif
}

bool write_template_to_file(const char* path, const char* content) {
    FILE* file = fopen(path, "w");
    if (!file) return false;
    
    size_t result = fprintf(file, "%s", content);
    fclose(file);
    
    return result > 0;
}

char* read_file_content(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) return NULL;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    char* content = malloc(size + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }
    
    size_t read_size = fread(content, 1, size, file);
    content[read_size] = '\0';
    
    fclose(file);
    return content;
}

bool copy_file(const char* src, const char* dest) {
    FILE* source = fopen(src, "rb");
    if (!source) return false;
    
    FILE* destination = fopen(dest, "wb");
    if (!destination) {
        fclose(source);
        return false;
    }
    
    char buffer[4096];
    size_t bytes;
    
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytes, destination) != bytes) {
            fclose(source);
            fclose(destination);
            return false;
        }
    }
    
    fclose(source);
    fclose(destination);
    return true;
}
)";
