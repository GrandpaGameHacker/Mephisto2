#include <Graphics/RenderQueue.h>
#include <gl/glew.h>
#include <string>
#include <spdlog/spdlog.h>

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