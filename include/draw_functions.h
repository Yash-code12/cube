#ifndef DRAW_FUNCTIONS_H
#define DRAW_FUNCTIONS_H

#include <GLES2/gl2.h>
#include "program_file.h"
#include "mesh_file.h"
#include "buttons.h"

void drawMesh(const ProgramClass &program, const Mesh &mesh);

void drawButton(const ProgramClass &program, const Button &button);

#endif //DRAW_FUNCTION_H