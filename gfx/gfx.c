#include "util/opengl.h"
#include "util/error.h"

#include "gfx.h"
#include "asset/manager.h"

static GLFWwindow* w;

static void resize_callback(GLFWwindow* w, int width, int height) {
    glViewport(0, 0, width, height);
}

void gfx_init() {
    // initialise GLFW
    error_if(glfwInit() != GLFW_TRUE, "couldn't initialise GLFW.");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create the window
    w =  glfwCreateWindow(800, 600, "placeholder", NULL, NULL);
    error_if(w == NULL, "couldn't create window.");
    glfwMakeContextCurrent(w);
    glfwShowWindow(w);

    // GLAD initialisation
    error_if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "couldn't initialise GLAD.");

    // set size and resize callback
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(w, resize_callback);
}

bool gfx_should_close() {
    return glfwWindowShouldClose(w);
}

void gfx_close() {
    glfwTerminate();
}

void gfx_clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void gfx_render() {
    glfwSwapBuffers(w);
    glfwPollEvents();
}

void gfx_draw_object(instance_t* ins) {
    object_t* obj = mgr_get_obj(ins->id);
    mesh_t* mesh = &(obj->mesh);

    // object isn't present in vmem, add it
    if (!mesh->gldata.is_init) {
        // create the buffers
        GLuint VAO, VBO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // bind them to the VAO
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ARRAY_BUFFER, (mesh->nverts)*sizeof(vec3_t),
                     mesh->verts, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (mesh->ntris)*3*sizeof(int),
                     mesh->tris, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        // add to mesh
        mesh->gldata.is_init = true;
        mesh->gldata.VAO = VAO;
    }

    // TODO: apply transformations
    // TODO: object can specify a shader to be used
    glBindVertexArray(mesh->gldata.VAO);
    glDrawElements(GL_TRIANGLES, mesh->ntris*3, GL_UNSIGNED_INT, 0);
}