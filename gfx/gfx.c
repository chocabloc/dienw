#include "util/opengl.h"
#include "util/error.h"

#include "gfx.h"
#include "camera.h"
#include "asset/manager.h"
#include "util/vmath.h"

static GLFWwindow* w;

static shdr_id curr_shdr_id = -1;
static shader_t* curr_shdr;

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
    w =  glfwCreateWindow(800, 800, "placeholder", NULL, NULL);
    error_if(w == NULL, "couldn't create window.");
    glfwMakeContextCurrent(w);
    glfwShowWindow(w);

    // GLAD initialisation
    error_if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "couldn't initialise GLAD.");

    // set size and resize callback
    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(w, resize_callback);

    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

bool gfx_should_close() {
    return glfwWindowShouldClose(w);
}

void gfx_close() {
    glfwTerminate();
}

void gfx_clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gfx_render() {
    glfwSwapBuffers(w);
    glfwPollEvents();
}

void gfx_draw_object(camera_t* cam, const instance_t* ins) {
    object_t* obj = mgr_get_object(ins->id);
    mesh_t* mesh = &(obj->mesh);

    // object isn't present in vmem, add it
    if (mesh->gl_vao == 0) {
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

        // add vao to mesh
        mesh->gl_vao = VAO;
    }

    // see if shader needs to be changed
    if (curr_shdr_id != obj->shdr) {
        curr_shdr_id = obj->shdr;
        curr_shdr = mgr_get_shader(curr_shdr_id);
        glUseProgram(curr_shdr->prog);
    }

    // apply transformations
    // matrices are transposed since glsl expects column major order
    mat4_t vm = {0};
    cam_update(cam);
    matmul4(&(cam->view), &(ins->trans), &vm);
    //printmat(&vm);
    //printmat(&(cam->proj));
    //exit(0);
    glUniformMatrix4fv(curr_shdr->uniforms.mat_vm, 1, GL_TRUE, (GLfloat*)&vm);
    glUniformMatrix4fv(curr_shdr->uniforms.mat_p, 1, GL_TRUE, (GLfloat*)&(cam->proj));

    // bind and draw
    glBindVertexArray(mesh->gl_vao);
    glDrawElements(GL_TRIANGLES, mesh->ntris*3, GL_UNSIGNED_INT, nullptr);
}
