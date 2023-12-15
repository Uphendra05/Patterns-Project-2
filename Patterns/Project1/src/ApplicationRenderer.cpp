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



std::vector<ModelData> ApplicationRenderer::loadModelDataFromFile(const std::string& filePath)
{

    std::ifstream file(filePath);
    std::vector<ModelData> modelData;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return modelData;
    }
    else
    {
        std::cerr << "File Opened >>>>>>>>>>>>>>>>>>>>>>>>>>>: " << filePath << std::endl;

    }

    std::string line;
    ModelData currentModel;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "ModelPath:") 
        {
            iss >> currentModel.path;
        }
        else if (token == "ModelPosition:") {
            iss >> currentModel.position.x >> currentModel.position.y >> currentModel.position.z;
        }       
        else if (token == "ModelRotation:") {

            iss >> currentModel.rotation.x >> currentModel.rotation.y >> currentModel.rotation.z;

        }
      
        else if (token == "TexturePath:") 
        {

            iss >> currentModel.texturePath;

        }
        else if (token == "Transperency:")
        {

            iss >> currentModel.isTrans;

        }
        
        else if (token == "Cutoff:")
        {

            iss >> currentModel.isCutoff;

        }
      
        else if (token == "ModelScale:") {
            iss >> currentModel.scale.x >> currentModel.scale.y >> currentModel.scale.z;
            modelData.push_back(currentModel);
        }
    }

    file.close();
    return modelData;
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

    camera.transform.SetPosition(glm::vec3(8, 2, -30));

    Model* Sphere = new Model((char*)"Models/DefaultSphere/Sphere.ply", true);
     defaultBox = new Model("Models/Box/DefaultCube.fbx");


   

     Model* directionLightModel = new Model(*Sphere);
     directionLightModel->transform.SetPosition(glm::vec3(1.0f, 3.0f, 0.0f));
     directionLightModel->transform.SetRotation(glm::vec3(-60, 0, 0));
     directionLightModel->transform.SetScale(glm::vec3(0.1f));


   
     Model* AsteroidGroupModels = new Model("Models/Asteroids/AsteroidGroup.ply");

     Model* Asteroid1Model= new Model("Models/Asteroids/Asteroid_1.ply");
     Model* Asteroid2Model= new Model("Models/Asteroids/Asteroid_2.ply");
     Model* Asteroid3Model= new Model("Models/Asteroids/Asteroid_3.ply");
     Model* Asteroid4Model= new Model("Models/Asteroids/Asteroid_4.ply");

     Model* FighterJetModel = new Model("Models/FighterJet/FighterJet.ply");

     spaceshipEntity = new SpaceShip();


  AsteroidsGroups* asteroidGroup1 = new AsteroidsGroups(AsteroidGroupModels);
  asteroidGroup1->SetPosition(glm::vec3(190, -1, 40));
  asteroidGroup1->SetRotation(glm::vec3(0, 90, 0));
  asteroidGroup1->SetScale(glm::vec3(0.024));
  asteroidGroup1->SetId("ASTEROIDGROUP1");

  AsteroidsGroups* asteroidGroup2 = new AsteroidsGroups(AsteroidGroupModels);
  asteroidGroup2->SetPosition(glm::vec3(10, -17, 80));
  asteroidGroup2->SetRotation(glm::vec3(0, 90, 0));
  asteroidGroup2->SetScale(glm::vec3(0.014));
  asteroidGroup2->SetId("ASTEROIDGROUP2");

  AsteroidsGroups* asteroidGroup3 = new AsteroidsGroups(AsteroidGroupModels);
  asteroidGroup3->SetPosition(glm::vec3(10, 17, 80));
  asteroidGroup3->SetRotation(glm::vec3(0, -90, 0));
  asteroidGroup3->SetScale(glm::vec3(0.014));
  asteroidGroup3->SetId("ASTEROIDGROUP3");


  Asteroid* asteroid1 = new Asteroid(Asteroid1Model);
  asteroid1->SetPosition(glm::vec3(60, -1, 0));
  asteroid1->SetRotation(glm::vec3(0, 90, 0));
  asteroid1->SetScale(glm::vec3(0.034));

  asteroid1->SetId("ASTEROID1");





  Asteroid* asteroid2 = new Asteroid(Asteroid2Model);
  asteroid2->SetPosition(glm::vec3(80, -1, -20));
  asteroid2->SetRotation(glm::vec3(0, 90, 0));
  asteroid2->SetScale(glm::vec3(0.011));
  asteroid2->SetId("ASTEROID2");

  Asteroid* asteroid3 = new Asteroid(Asteroid2Model);
  asteroid3->SetPosition(glm::vec3(20, -3, 15));
  asteroid3->SetRotation(glm::vec3(90, 90, 0));
  asteroid3->SetScale(glm::vec3(0.008));
  asteroid3->SetId("ASTEROID3");


  Asteroid* asteroid4 = new Asteroid(Asteroid2Model);
  asteroid4->SetPosition(glm::vec3(10, 4, -15));
  asteroid4->SetRotation(glm::vec3(90, 90, 0));
  asteroid4->SetScale(glm::vec3(0.007));
  asteroid4->SetId("ASTEROID4");
//
#pragma region SCENE 2



     //SCENE 2
       Asteroid* asteroid16 = new Asteroid(Asteroid3Model);
     asteroid16->SetPosition(glm::vec3(8, 2, -25));
     asteroid16->SetRotation(glm::vec3(90, 90, 0));
     asteroid16->SetScale(glm::vec3(0.044));
     asteroid16->SetId("ASTEROID16");

     FighterJet* fighter1 = new FighterJet(FighterJetModel);

     fighter1->SetPosition(glm::vec3(5, 6, 13));
     fighter1->SetRotation(glm::vec3(40, 0, 0));
     fighter1->SetScale(glm::vec3(0.024f));
     fighter1->SetId("FIGHTER1");


     FighterJet* fighter2 = new FighterJet(FighterJetModel);
     fighter2->SetPosition(glm::vec3(0, 8, 13));
     fighter2->SetRotation(glm::vec3(40, 0, 0));
     fighter2->SetScale(glm::vec3(0.024f));
     fighter2->SetId("FIGHTER2");


     FighterJet* fighter3 = new FighterJet(FighterJetModel);
     fighter3->SetPosition(glm::vec3(-1, 7, 13));
     fighter3->SetRotation(glm::vec3(40, 0, 0));
     fighter3->SetScale(glm::vec3(0.024f));
     fighter3->SetId("FIGHTER3");


     FighterJet* fighter4 = new FighterJet(FighterJetModel);
     fighter4->SetPosition(glm::vec3(4, 0, 13));
     fighter4->SetRotation(glm::vec3(40, 0, 0));
     fighter4->SetScale(glm::vec3(0.024f));
     fighter4->SetId("FIGHTER4");
#pragma endregion
//
#pragma region SCENE 3 

     Asteroid* asteroid5 = new Asteroid(Asteroid2Model);
     asteroid5->SetPosition(glm::vec3(17, 27, -13));
     asteroid5->SetRotation(glm::vec3(0, 90, 0));
     asteroid5->SetScale(glm::vec3(0.024));
     asteroid5->SetId("ASTEROID5");
     asteroid5->AddPhysicsForthisObject();

     // SCENE 3 FIGHTERS
     FighterJet* fighter5 = new FighterJet(FighterJetModel);
     fighter5->SetPosition(glm::vec3(8, 11, -13));
     fighter5->SetRotation(glm::vec3(40, 0, 0));
     fighter5->SetScale(glm::vec3(0.024f));
     fighter5->SetId("FIGHTER5");


     FighterJet* fighter6 = new FighterJet(FighterJetModel);
     fighter6->SetPosition(glm::vec3(8, 7.0f, -10));
     fighter6->SetRotation(glm::vec3(40, -20, 0));
     fighter6->SetScale(glm::vec3(0.024f));
     fighter6->SetId("FIGHTER6");

     FighterJet* fighter7 = new FighterJet(FighterJetModel);
     fighter7->SetPosition(glm::vec3(-1, 11.0, 13));
     fighter7->SetRotation(glm::vec3(40, 0, 0));
     fighter7->SetScale(glm::vec3(0.024f));
     fighter7->SetId("FIGHTER7");


     FighterJet* fighter8 = new FighterJet(FighterJetModel,DestroyShader);
     fighter8->SetPosition(glm::vec3(4, 0, 13));
     fighter8->SetRotation(glm::vec3(40, 0, 0));
     fighter8->SetScale(glm::vec3(0.024f));
     fighter8->SetId("FIGHTER8");
     fighter8->AddPhysicsForthisObject();


#pragma endregion
//
//
#pragma region SCENE 4

     Asteroid* asteroid40 = new Asteroid(Asteroid2Model);
     asteroid40->SetPosition(glm::vec3(-1, 8, 12));
     asteroid40->SetRotation(glm::vec3(0, 90, 0));
     asteroid40->SetScale(glm::vec3(0.040f));
     asteroid40->SetId("ASTEROID40");


     Asteroid* asteroid6 = new Asteroid(Asteroid1Model);
     asteroid6->SetPosition(glm::vec3(18, 0, 10));
     asteroid6->SetRotation(glm::vec3(90, 90, 0));
     asteroid6->SetScale(glm::vec3(0.009f));
     asteroid6->SetId("ASTEROID6");

      

     Asteroid* asteroid7 = new Asteroid(Asteroid1Model);
     asteroid7->SetPosition(glm::vec3(15, -5, -14));
     asteroid7->SetRotation(glm::vec3(90, 90, 0));
     asteroid7->SetScale(glm::vec3(0.005f));
     asteroid7->SetId("ASTEROID7");


     Asteroid* asteroid8 = new Asteroid(Asteroid1Model);
     asteroid8->SetPosition(glm::vec3(20, -10, 0));
     asteroid8->SetRotation(glm::vec3(90, 90, 0));
     asteroid8->SetScale(glm::vec3(0.002f));
     asteroid8->SetId("ASTEROID8");


     FighterJet* fighter9 = new FighterJet(FighterJetModel);
     fighter9->SetPosition(glm::vec3(50, 2, 35));
     fighter9->SetRotation(glm::vec3(90, 45, 0));
     fighter9->SetScale(glm::vec3(0.024f));
     fighter9->SetId("FIGHTER9");

     FighterJet* fighter10 = new FighterJet(FighterJetModel);
     fighter10->SetPosition(glm::vec3(15, -2, 35));
     fighter10->SetRotation(glm::vec3(90, 25, 0));
     fighter10->SetScale(glm::vec3(0.024f));
     fighter10->SetId("FIGHTER10");


     FighterJet* fighter11 = new FighterJet(FighterJetModel);
     fighter11->SetPosition(glm::vec3(50, 10, 70));
     fighter11->SetRotation(glm::vec3(90, 45, 0));
     fighter11->SetScale(glm::vec3(0.024f));
     fighter11->SetId("FIGHTER11");

     SpaceShip* spaceshipEntity2 = new SpaceShip("SPACESHIP2");
     spaceshipEntity2->model->transform.SetPosition(glm::vec3(12, 6, 30));
     spaceshipEntity2->model->transform.SetRotation(glm::vec3(-20, 90, 0));
     spaceshipEntity2->model->transform.SetScale(glm::vec3(0.04f));


#pragma endregion

#pragma region SCENE 5


     FighterJet* fighter12 = new FighterJet(FighterJetModel, DestroyShader2);
     fighter12->SetPosition(glm::vec3(5, 2, -33));
     fighter12->SetRotation(glm::vec3(90, 0, 0));
     fighter12->SetScale(glm::vec3(0.034f));
     fighter12->SetId("FIGHTER12");
     fighter12->AddPhysicsForthisObject();


     Asteroid* asteroid10 = new Asteroid(Asteroid1Model);
     asteroid10->SetPosition(glm::vec3(9, 1, -27));
     asteroid10->SetRotation(glm::vec3(90, 90, 0));
     asteroid10->SetScale(glm::vec3(0.002f));
     asteroid10->SetId("ASTEROID10");
     //asteroid10->AddPhysicsForthisObject();

     Model* box = new Model(*defaultBox);
     box->transform.SetPosition(glm::vec3(8, 2, 10));
     box->id = "BOX_TRIGGER";
     box->isVisible = false;
     render.AddModelsAndShader(box, defaultShader);

     PhysicsObject* BoxPhyiscs = new PhysicsObject(box);
     BoxPhyiscs->Initialize(AABB, true, STATIC);
     BoxPhyiscs->gravityValue = 0;
     PhysicsEngine.AddPhysicsObjects(BoxPhyiscs);


     Asteroid* asteroidStatic = new Asteroid(Asteroid4Model);
     asteroidStatic->SetPosition(glm::vec3(15, -1.9, -22));
     asteroidStatic->SetRotation(glm::vec3(0, 0, 0));
     asteroidStatic->SetScale(glm::vec3(1));
     asteroidStatic->SetId("ASTEROID_STATIC");



#pragma endregion



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

    
    

     LuaManager::GetInstance().SetModelList(render.GetModelList()); // Setting All the game objects

     WorldLuaHandler = new LuaHandler("World.lua");
     WorldLuaHandler->RegisterFunctionInScript();
     WorldLuaHandler->ExecuteScirpt();

     CommandManager::GetInstance().Start();
}

void ApplicationRenderer::PreRender()
{

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

        glm::mat4 _projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)WindowHeight, 0.1f, 1000.0f);
        glm::mat4 _view = camera.GetViewMatrix();
        glm::mat4 _skyboxview = glm::mat4(glm::mat3(camera.GetViewMatrix()));


        PreRender(); //Update call BEFORE  DRAW

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
        

       

         
  
         
         // make models that it should not write in the stencil buffer
         render.Draw();
       

         if (cameraMoveToTarget)
         {
             camera.UpdateCameraPosition(deltaTime);

         }
       
        
        
      
     

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

    if (!updateCommands)
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

             camera.transform.SetPosition(glm::vec3(8, 2, -37));
             camera.transform.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));

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
