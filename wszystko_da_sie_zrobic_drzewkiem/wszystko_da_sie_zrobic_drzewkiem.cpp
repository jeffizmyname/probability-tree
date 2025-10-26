#include <iostream>
#include <rational.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

#include "Node.h"

using boost::rational;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{

	sf::RenderWindow window(sf::VideoMode({800, 600}), "Test");
	ImGui::SFML::Init(window);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Clock deltaClock;

	static char nameInput[128] = "";
	static char valueInput[128] = "";
	vector<Value> values;

	while (window.isOpen()) 
	{

		while (const std::optional event = window.pollEvent()) 
		{
			ImGui::SFML::ProcessEvent(window, *event);
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("Values");
		static int itemSelected = -1;
		static char* currentItem = (values.size() > 0 ? (char*)values[itemSelected].name.c_str() : (char*)"");
		if (ImGui::BeginCombo("List of events", currentItem))
		{
			for (int i = 0 ; i < values.size(); i++)
			{
				const bool isSelected = (itemSelected == i);
				if (ImGui::Selectable(values[i].name.c_str(), isSelected))
				{
					itemSelected = i;
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
					currentItem = (char*)values[itemSelected].name.c_str();
				}
			}
			ImGui::EndCombo();
		}
		ImGui::InputText("Name", nameInput, IM_ARRAYSIZE(nameInput));
		ImGui::InputTextWithHint("Value", "in format x/y", valueInput, IM_ARRAYSIZE(valueInput));
		if (ImGui::Button("Add event"))
		{
			string valStr(valueInput);
			size_t slashPos = valStr.find('/');
			if (slashPos != string::npos)
			{
				int numerator = std::stoi(valStr.substr(0, slashPos));
				int denominator = std::stoi(valStr.substr(slashPos + 1));
				values.emplace_back(string(nameInput), rational<int>(numerator, denominator));
				//currentItem = const_cast<char*>(values.back().name.c_str());
			}
			else
			{
				//wrong imput
			}
		}
		ImGui::End();

		ImGui::Begin("Calculate");

		ImGui::End();

		window.clear();	
		window.draw(shape);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	Value valO("o", {1, 2});
	Value valR("r", {1, 3});

	Value val("root");
	Node root(val, 2);
	root.createBasicTree(vector<Value>{ valO, valR }, 2);

	root.print();

	cout << "Probability " << root.calculateProbability(vector<string>{ "r", "r" }) << endl;

	
	return 0;
}







