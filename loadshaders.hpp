#ifndef LOADSHADERS_HPP
#define LOADSHADERS_HPP

#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
GLuint	LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

#endif // LOADSHADERS_HPP
