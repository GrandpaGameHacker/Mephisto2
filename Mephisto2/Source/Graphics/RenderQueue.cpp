#include <Graphics/RenderQueue.h>
#include <gl/glew.h>
#include <string>
#include <spdlog/spdlog.h>
#include <Graphics/ImGuiBackend/imgui_impl_opengl3.h>
#include <Graphics/ImGuiBackend/imgui_impl_sdl.h>

#include <Graphics/IWindow.h>

ME::Graphics::RenderQueue::~RenderQueue()
{
	Execute([=]
		{
			ImGui_ImplSDL2_Shutdown();
			ImGui_ImplOpenGL3_Shutdown();
			ImGui::DestroyContext();
			SDL_GL_DeleteContext(&GLContext);
		});
}

bool ME::Graphics::RenderQueue::SetupOpenGL()
{
	return Queue->Execute([=]
		{
			glewInit();

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
			glDepthFunc(GL_LESS);
			
			const std::string renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
			const std::string version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
			
			spdlog::info("GPU - {}", renderer);
			spdlog::info("OpenGL version - {}", version);
			return true;
		}).get();
}

void ME::Graphics::RenderQueue::SetupImGui()
{
	Queue->Execute([=]
		{
			IMGUI_CHECKVERSION();
			GUIContext = ImGui::CreateContext();
			ImGui::StyleColorsDark();
			ImGui_ImplSDL2_InitForOpenGL(WindowContext, GLContext);
			ImGui_ImplOpenGL3_Init();
		});
}

void ME::Graphics::RenderQueue::ImGuiProcessEvent(SDL_Event* event)
{
	Queue->Execute([=]
		{
			ImGui_ImplSDL2_ProcessEvent(event);
		});
}

void ME::Graphics::RenderQueue::NewFrame()
{
	Queue->Execute([=]
		{
			ImGui_ImplSDL2_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();
			IWindow::DrawVisible();
			ImGui::Render();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// draw game elements between new frame and swap
		});
}

void ME::Graphics::RenderQueue::Swap()
{
	Queue->Execute([=]
		{
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			SDL_GL_SwapWindow(WindowContext);
		});
}
