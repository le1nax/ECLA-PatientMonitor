#include "../include/DisplayManager.h"

DisplayManager::DisplayManager()
{
}

void DisplayManager::initWindow()
{
    if(displayWindowThread && displayWindowThread->joinable())
    {
        displayWindowThread->join(); 
    }
    displayWindowThread = std::make_unique<std::thread>(&DisplayManager::DisplayThread, this);
}

void DisplayManager::onPressureChanged(const DataPoint& dataPointReceived)
{
    float readData = static_cast<float>(ReadByteSignedValuesFromBuffer(dataPointReceived.m_value, 0 ,dataPointReceived.m_data_lenght));
    std::cout << "handeled datapoint: " << readData << std::endl;

    m_BPData.push_back(readData);
}

void DisplayManager::DisplayThread()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return;

    // Decide GL+GLSL versions

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "BP View Debug Version", nullptr, nullptr);
    if (window == nullptr)
        return;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create a window
        ImGui::Begin("Plot BP");

        // Plot the vector
        PlotVector("BP", m_BPData);

        // End the ImGui window
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}


DisplayManager::~DisplayManager()
{
    if(displayWindowThread && displayWindowThread->joinable()) {
        displayWindowThread->join();
    }
}