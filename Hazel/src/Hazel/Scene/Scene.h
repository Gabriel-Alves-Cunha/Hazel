#pragma once

#include "entt.hpp"

#include "hzpch.h"
#include "Hazel\Core\TimeStep.h"

namespace Hazel
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdate(TimeStep ts);
		void OnViewPortResize(ui32 width, ui32 height);

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;

		ui32 m_ViewPortWidth = 0, m_ViewPortHeight = 0;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};
}