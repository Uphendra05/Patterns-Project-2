#include"ApplicationRenderer.h"
#include "Singleton.h"

bool ISFIGHTERCOLLIDED = false;

ApplicationRenderer::ApplicationRenderer()
{
}

ApplicationRenderer::~ApplicationRenderer()
{
}



void ApplicationRenderer::WindowInitialize(int width, int height,  std::string windowName)
{
    windowWidth = width;
    WindowHeight = height;
    lastX = windowWidth / 2.0f;
    lastY= WindowHeight / 2.0f;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int x, int y)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(w))->SetViewPort(w, x, y);
        });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->KeyCallBack(window, key, scancode, action, mods);
        });


    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xposIn, double yposIn)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseCallBack(window, xposIn, yposIn);
        });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseScroll(window, xoffset, yoffset);
        });
   
    
    //Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }




  
    defaultShader = new Shader("Shaders/Light_VertexShader.vert", "Shaders/Light_FragmentShader2.frag");
    DestroyShader = new Shader("Shaders/StarDestroyer.vert", "Shaders/StarDestroyer.frag");
    DestroyShader2 = new Shader("Shaders/StarDestroyer.vert", "Shaders/StarDestroyer.frag");
    lightShader = new Shader("Shaders/lighting.vert", "Shaders/lighting.frag", SOLID);
    StencilShader = new Shader("Shaders/StencilOutline.vert", "Shaders/StencilOutline.frag");
   
    SkyboxShader = new Shader("Shaders/SkyboxShader.vert", "Shaders/SkyboxShader.frag");


    //ScrollShader = new Shader("Shaders/ScrollTexture.vert", "Shaders/ScrollTexture.frag");
    render.AssignStencilShader(StencilShader);
   // camera.Position = glm::vec3(0, 0, - 1.0f);
}



void ApplicationRenderer::Start()
{
   // GLCALL(glEnable(GL_DEPTH_TEST));
    GLCALL(glDepthFunc(GL_LESS));
    GLCALL(glEnable(GL_STENCIL_TEST));
    GLCALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
    GLCALL(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // brain.LuaTestInit();
    skybox = new Skybox(); 
    
    skybox->AssignSkyboxShader(SkyboxShader);
    skybox->SkyboxPrerender();
    

    render.AssignCamera(&camera);

    Singleton::GetInstance().SetRendererPhysicsEngineAndDefaultShader(render, defaultShader, PhysicsEngine);

    Singleton::GetInstance().SetCamera(camera);
   

    camera.transform.SetPosition(glm::vec3(0, 0, -20));

    Model* Sphere = new Model((char*)"Models/DefaultSphere/Sphere.ply", true);
     defaultBox = new Model("Models/Box/DefaultCube.fbx");


   

     Model* directionLightModel = new Model(*Sphere);
     directionLightModel->transform.SetPosition(glm::vec3(1.0f, 3.0f, 0.0f));
     directionLightModel->transform.SetRotation(glm::vec3(-60, 0, 0));
     directionLightModel->transform.SetScale(glm::vec3(0.1f));


   
     






#pragma region Lights

Light directionLight;
directionLight.lightType = LightType::DIRECTION_LIGHT;
directionLight.lightModel = directionLightModel;
directionLight.ambient =  glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
directionLight.diffuse =  glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
directionLight.specular = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
directionLight.intensity = 0.5f;


directionLightModel->id = "DIRECTIONLIGHT";
directionLightModel->isVisible = false;
//directionLightModel->transform.SetRotation(glm::vec3(-90, 0, 90));




#pragma endregion



     Ball* ball = new Ball();

     render.selectedModel = nullptr;

     render.AddModelsAndShader(directionLightModel, lightShader);



     

     //LightRenderer
     lightManager.AddNewLight(directionLight);

     defaultShader->Bind();
     defaultShader->setInt("skybox", 0);
     lightManager.SetUniforms(defaultShader->ID);

     DestroyShader->Bind();
     lightManager.SetUniforms(DestroyShader->ID);

    
     

     moveCam.AssignCam(&camera);

    
    
     LuaManager::GetInstance().SetGameObjectList(Singleton::GetInstance().GetGameObjectList());



     GameObjectList = Singleton::GetInstance().GetGameObjectList(); // Setting All the game objects


   //  LuaManager::GetInstance().SetModelList(render.GetModelList()); // Setting All the game objects

     WorldLuaHandler = new LuaHandler("NEWWORLD.lua");
     WorldLuaHandler->RegisterFunctionInScript();
     WorldLuaHandler->ExecuteScirpt();

     CommandManager::GetInstance().Start();
}

void ApplicationRenderer::PreRender()
{
    glm::mat4 _projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)WindowHeight, 0.1f, 1000.0f);
    glm::mat4 _view = camera.GetViewMatrix();
    glm::mat4 _skyboxview = glm::mat4(glm::mat3(camera.GetViewMatrix()));

    glDepthFunc(GL_LEQUAL);
    SkyboxShader->Bind();
    SkyboxShader->setMat4("view", _skyboxview);
    SkyboxShader->setMat4("projection", _projection);

    skybox->Skyboxrender();
    glDepthFunc(GL_LESS);


    defaultShader->Bind();
    // material.SetMaterialProperties(*defaultShader);
  //   lightManager.UpdateUniformValuesToShader(defaultShader);
    lightManager.UpdateUniformValues(defaultShader->ID);


    defaultShader->setMat4("projection", _projection);
    defaultShader->setMat4("view", _view);
    defaultShader->setVec3("viewPos", camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
    defaultShader->setFloat("time", scrollTime);
    defaultShader->setBool("isDepthBuffer", false);

    DestroyShader->Bind();
    lightManager.UpdateUniformValues(DestroyShader->ID);
    DestroyShader->setMat4("projection", _projection);
    DestroyShader->setMat4("view", _view);
    DestroyShader->setVec3("viewPos", camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
    DestroyShader->setFloat("time", scrollTime);
    DestroyShader->setBool("isDepthBuffer", false);
    //   DestroyShader->setFloat("explosionOffset", explosionOffset);


    DestroyShader2->Bind();
    lightManager.UpdateUniformValues(DestroyShader2->ID);
    DestroyShader2->setMat4("projection", _projection);
    DestroyShader2->setMat4("view", _view);
    DestroyShader2->setVec3("viewPos", camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
    DestroyShader2->setFloat("time", scrollTime);
    DestroyShader2->setBool("isDepthBuffer", false);



    lightShader->Bind();
    lightShader->setVec3("objectColor", glm::vec3(1, 1, 1));
    lightShader->setMat4("projection", _projection);
    lightShader->setMat4("view", _view);

    StencilShader->Bind();
    StencilShader->setMat4("projection", _projection);
    StencilShader->setMat4("view", _view);

    /* ScrollShader->Bind();
     ScrollShader->setMat4("ProjectionMatrix", _projection);*/



}

void ApplicationRenderer::Render()
{
    Start();
    Material material(128.0f);
    glm::vec3 pos(5, 0, 0);
   // glEnable(GL_BLEND);
  //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (!glfwWindowShouldClose(window))
    {
        Clear();


        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        scrollTime += deltaTime;

        ProcessInput(window);

        PreRender(); //Update call BEFORE  DRAW

         // make models that it should not write in the stencil buffer
         render.Draw();
       

         PostRender(); // Update Call AFTER  DRAW

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void ApplicationRenderer::PostRender()
{
   // glDisable(GL_BLEND);

    PhysicsEngine.Update(deltaTime);

    //spaceshipEntity->Update(deltaTime);
    //DrawDebugModelAABB(spaceshipEntity->SpaceShipPhysics->UpdateAABB());

    if (updateCommands)
    {
        CommandManager::GetInstance().Update(deltaTime);
    }
}

void ApplicationRenderer::Clear()
{
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 0.1f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void ApplicationRenderer::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

  //  if (!updateCommands)
    {
        float cameraSpeed = 20;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(FORWARD, deltaTime * cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(BACKWARD, deltaTime * cameraSpeed);
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(LEFT, deltaTime * cameraSpeed);

        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(RIGHT, deltaTime * cameraSpeed);

        }
    }


   


}






 void ApplicationRenderer::SetViewPort(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

 void ApplicationRenderer::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
 {  
         if (key == GLFW_KEY_V && action == GLFW_PRESS)
         {

            
             std::cout << "V pressed" << std::endl;

             std::vector<Model*> listOfModels = render.GetModelList();
            


             selectedModelCount++;

             if (selectedModelCount > listOfModels.size()-1)
             {
                 selectedModelCount = 0;
             }

            
             render.selectedModel = listOfModels[selectedModelCount];


         }

         if (key == GLFW_KEY_O && action == GLFW_PRESS)
         {

            // camera.transform.SetPosition(glm::vec3(8, 2, -37));
          //   camera.transform.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));

             updateCommands = !updateCommands;
         }

         
 }

 void ApplicationRenderer::MouseCallBack(GLFWwindow* window, double xposIn, double yposIn)
 {

    float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);
     
        if (firstMouse)
        {

        }

         if (firstMouse)
         {
             lastX = xpos;
             lastY = ypos;
             firstMouse = false;
         }
     
         float xoffset = xpos - lastX;
         float yoffset = lastY - ypos;
     
         lastX = xpos;
         lastY = ypos;
     
        // if (!updateCommands)
         {
             if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
             {
                 camera.ProcessMouseMovement(xoffset, yoffset);
             }
         }
         
 }

 void ApplicationRenderer::MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
 {
     camera.ProcessMouseScroll(static_cast<float>(yoffset));
 }
