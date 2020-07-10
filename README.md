# GLSL Parser
This is a small glsl parser that gives you the ability to include other shader files or even text files into your shader file


## How Does it work ?

**Foo.frag**
```cpp
struct Foo
{
    vec3 bar;
};
```

**Bar.frag**
```cpp
#version 330 core

out vec4 FragColour;

#include <Foo.frag>

uniform Foo foo;

void main()
{
    FragColour = vec4(foo.bar, 1.0f);
}
```
**main.cpp**
```cpp
#include "glslparser/parser.hpp"

int main()
{
    // create the parser object and pass the shader file to it
    SE::Util::Parser parser("/path/to/glsl/shader");
    
    // retrieve the data from the parser
    // the std::string here contains the correct data to pass it to opengl to compile
    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* temp = parser.content.c_str();
    glShaderSource(shader, 1, &temp,nullptr);
    
}

```
