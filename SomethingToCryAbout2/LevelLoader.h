#pragma once
#include <string>
#include <fstream>
#include "Trigger.h"
#include "Entity.h"
#include "Player.h"
#include "TestAI.h"
class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();
	void LoadLevel(std::string path){
		std::fstream level(path);
		if (level.good()){
			std::string temp;
			while (level >> temp){
				lvlData.push_back(temp);
			}
		}
		level.close();
	}
	void ProcessLevel(std::vector<Entity> &entities, std::vector<TestAI> &entitiesTestAi, std::vector<Trigger> &triggers, Player& player){
		for (int y = 0; y < lvlData.size(); y++){
			for (int x = 0; x < lvlData[y].size(); x++){
				switch (lvlData[y][x]){
				case '@':
					player.SetPos(x*STANDARD_SIZE, y*STANDARD_SIZE);
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "dev", false));
					break;
				case '#':
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "dev", true));
					break;
				case '0':
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "wall-dev", false));
					break;
				case '+':
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(0, 255, 0), 100, "triggerHeal_box", false));
					triggers.push_back(Trigger(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(0, 255, 0), 0, "triggerHeal", false));
					break;
				case '!':
					entitiesTestAi.push_back(TestAI(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "guy", true));
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "dev", false));
					break;
				case '_':
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(12, 30, 255), 100, "triggerWater_box", false));
					triggers.push_back(Trigger(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "triggerWater", false));
					break;
				default:
					break;
				}
			}
		}
	}
private:
	std::vector<std::string> lvlData;
};

