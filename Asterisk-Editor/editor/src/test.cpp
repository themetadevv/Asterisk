
#include <Engine/EntryPoint.h>
#include <Logger/Logger.h>

#include <Math/MatrixAliases.h>
#include <Allocator/LinearAllocator.h>

#include <Engine/Time/Time.h>
#include <Engine/UUID/UUID.h>

#include <imgui.h>

using namespace asterisk;

class EditorLayer : public Layer {
public:
	TimeStep ts;

	SharedPtr<Shader> m_Shader;

	EditorLayer() : Layer("Editor Layer") 
	{ }

	void OnAttach() override {
		auto& engine = Engine::Get();
		auto& imgui_layer = engine.GetImGuiLayer();

		ImGui::SetCurrentContext(imgui_layer.GetContext());

		m_Shader = Shader::Create("assets/test.glsl");
	}

	void OnRender(float dt) override {
		uint64_t id = (uint64_t)rand_uint64_t();

		ts.Update();

		ImGui::Begin("Editor Layer");

		ImGui::Text("Delta Time: %f", ts.GetDeltaTime());

		ImGui::End();
	}
};

class AsteriskEditor : public asterisk::Engine {
public:
	AsteriskEditor(const asterisk::EngineSetting& _setting = asterisk::EngineSetting()) : 
		asterisk::Engine(_setting)
	{
		PushLayer(new EditorLayer());
	}
};

asterisk::Engine* asterisk::Create() {
	return new AsteriskEditor();
}