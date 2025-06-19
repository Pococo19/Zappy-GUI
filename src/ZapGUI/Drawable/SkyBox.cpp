/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** SkyBox.cpp
*/

#include <ZapGUI/Drawable/SkyBox.hpp>
#include "SkyBox.hpp"
#include <cstring>

namespace zap {

SkyBox::SkyBox(bool useHDR, const char* file) : useHDR(useHDR)
{
    std::memset(currentFile, 0, sizeof(currentFile));
    Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);
    model = LoadModelFromMesh(cube);

    shaderSkybox = LoadShader(TextFormat("assets/shaders/skybox.vs", 330), TextFormat("assets/shaders/skybox.fs", 330));
    model.materials[0].shader = shaderSkybox;

    int envMap = MATERIAL_MAP_CUBEMAP;
    int gamma = useHDR ? 1 : 0;
    int flip = useHDR ? 1 : 0;

    SetShaderValue(shaderSkybox, GetShaderLocation(shaderSkybox, "environmentMap"), &envMap, SHADER_UNIFORM_INT);
    SetShaderValue(shaderSkybox, GetShaderLocation(shaderSkybox, "doGamma"), &gamma, SHADER_UNIFORM_INT);
    SetShaderValue(shaderSkybox, GetShaderLocation(shaderSkybox, "vflipped"), &flip, SHADER_UNIFORM_INT);

    shaderCubemap = LoadShader(TextFormat("assets/shaders/cubemap.vs", 330), TextFormat("assets/shaders/cubemap.fs", 330));
    int eqMap = 0;
    SetShaderValue(shaderCubemap, GetShaderLocation(shaderCubemap, "equirectangularMap"), &eqMap, SHADER_UNIFORM_INT);

    if (file)
        LoadFromFile(file);
}

SkyBox::~SkyBox()
{
    UnloadShader(shaderSkybox);
    UnloadShader(shaderCubemap);
    UnloadTexture(model.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
    UnloadModel(model);
}

void SkyBox::LoadFromFile(const char* fileName)
{
    std::strncpy(currentFile, fileName, sizeof(currentFile) - 1);

    if (useHDR) {
        panorama = LoadTexture(fileName);
        model.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = GenCubemap(shaderCubemap, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        UnloadTexture(panorama);
    } else {
        Image img = LoadImage(fileName);
        model.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
        UnloadImage(img);
    }
}

void SkyBox::ReloadDropped()
{
    if (IsFileDropped()) {
        FilePathList dropped = LoadDroppedFiles();
        if (dropped.count == 1 && IsFileExtension(dropped.paths[0], ".png;.jpg;.hdr;.bmp;.tga")) {
            UnloadTexture(model.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
            LoadFromFile(dropped.paths[0]);
        }
        UnloadDroppedFiles(dropped);
    }
}

void SkyBox::Draw()
{
    rlDisableBackfaceCulling();
    rlDisableDepthMask();

    DrawModel(model, Vector3{ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);

    rlEnableBackfaceCulling();
    rlEnableDepthMask();
}

TextureCubemap SkyBox::GenCubemap(Shader shader, Texture2D panoramaTex, int size, int format)
{
    TextureCubemap cubemap = { 0 };
    rlDisableBackfaceCulling();     // Disable backface culling to render inside the cube

    unsigned int rbo = rlLoadTextureDepth(size, size, true);
    cubemap.id = rlLoadTextureCubemap(0, size, format, 1);

    // Fixing the call to rlLoadFramebuffer
    unsigned int fbo = rlLoadFramebuffer(); // Corrected function call
    rlFramebufferAttach(fbo, rbo, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);
    rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X, 0);

    // Check if framebuffer is complete with attachments (valid)
    if (rlFramebufferComplete(fbo)) TraceLog(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", fbo);
    //------------------------------------------------------------------------------------------

    rlEnableShader(shader.id);

    // Define projection matrix and send it to shader
    Matrix matFboProjection = MatrixPerspective(90.0f * DEG2RAD, 1.0f, 0.1f, 1000.0f); // Changed to use fixed near and far values

    // Define view matrix for every side of the cubemap
    Matrix fboViews[6] = {
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  1.0f,  0.0f,  0.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ -1.0f,  0.0f,  0.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  1.0f,  0.0f }, (Vector3){ 0.0f,  0.0f,  1.0f }),
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f, -1.0f,  0.0f }, (Vector3){ 0.0f,  0.0f, -1.0f }),
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f, 0.0f,  1.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f, 0.0f, -1.0f }, (Vector3){ 0.0f, -1.0f,  0.0f })
    };

    rlViewport(0, 0, size, size);   // Set viewport to current fbo dimensions
    
    // Activate and enable texture for drawing to cubemap faces
    rlActiveTextureSlot(0);
    rlEnableTexture(panorama.id);

    for (int i = 0; i < 6; i++)
    {
        // Set the view matrix for the current cube face
        rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_VIEW], fboViews[i]);
        
        // Select the current cubemap face attachment for the fbo
        // WARNING: This function by default enables->attach->disables fbo!!!
        rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X + i, 0);
        rlEnableFramebuffer(fbo);

        // Load and draw a cube, it uses the current enabled texture
        rlClearScreenBuffers();
        rlLoadDrawCube();

        // ALTERNATIVE: Try to use internal batch system to draw the cube instead of rlLoadDrawCube
        // for some reason this method does not work, maybe due to cube triangles definition? normals pointing out?
        // TODO: Investigate this issue...
        //rlSetTexture(panorama.id); // WARNING: It must be called after enabling current framebuffer if using internal batch system!
        //rlClearScreenBuffers();
        //DrawCubeV(Vector3Zero(), Vector3One(), WHITE);
        //rlDrawRenderBatchActive();
    }
    //------------------------------------------------------------------------------------------

    // STEP 3: Unload framebuffer and reset state
    //------------------------------------------------------------------------------------------
    rlDisableShader();          // Unbind shader
    rlDisableTexture();         // Unbind texture
    rlDisableFramebuffer();     // Unbind framebuffer
    rlUnloadFramebuffer(fbo);   // Unload framebuffer (and automatically attached depth texture/renderbuffer)

    // Reset viewport dimensions to default
    rlViewport(0, 0, rlGetFramebufferWidth(), rlGetFramebufferHeight());
    rlEnableBackfaceCulling();
    //------------------------------------------------------------------------------------------

    cubemap.width = size;
    cubemap.height = size;
    cubemap.mipmaps = 1;
    cubemap.format = format;

    return cubemap;
}

}