#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel
{
	class HazelNut : public Application
	{
	public:
		HazelNut()
			: Application("HazelNut")
		{
			PushLayer(new EditorLayer());
		}

		~HazelNut()
		{}
	};

	Application* CreateApplication()
	{
		return new HazelNut();
	}
}