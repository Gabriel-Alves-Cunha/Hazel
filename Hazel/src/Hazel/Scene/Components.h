#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SceneCamera.h"
#include "ScriptableEntity.h"

using namespace glm;

namespace Hazel
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		vec3 Translation = { 0.0f, 0.0f, 0.0f };
		vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const vec3& translation)
			: Translation(translation) {}

		mat4 GetTransform() const
		{
			mat4 rotation = rotate(mat4(1.0f), Rotation.x, { 1,0,0 })
				* rotate(mat4(1.0f), Rotation.y, { 0,1,0 })
				* rotate(mat4(1.0f), Rotation.z, { 0,0,1 });

			return translate(mat4(1.0f), Translation)
				* rotation
				* scale(mat4(1.0f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();

		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}