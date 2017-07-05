#pragma once
#include <string>
#include <fstream>
#include "Trigger.h"
#include "Entity.h"
#include "Player.h"
#include "TestAI.h"
#include "Turret.h"
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
	void ProcessLevel(std::vector<Entity> &entities, std::vector<TestAI> &entitiesTestAi, std::vector<Trigger> &triggers, std::vector<Turret> &turrets, Player& player, Trigger &goal){
		for (int y = 0; y < lvlData.size(); y++){
			for (int x = 0; x < lvlData[y].size(); x++){
				switch (lvlData[y][x]){
				case '@':
					player.SetPos(x*STANDARD_SIZE, y*STANDARD_SIZE);
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "smooth-stone", false));
					break;
				case '#':
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "dev", true));
					break;
				case '0':
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "smooth-stone", false));
					break;
				case '+':
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(0, 255, 0), 100, "triggerHeal_box", false));
					triggers.push_back(Trigger(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(0, 255, 0), 0, "triggerHeal", false));
					break;
				case '!':
					entitiesTestAi.push_back(TestAI(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "guy", true));
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "smooth-stone", false));
					break;
				case '~':
					turrets.push_back(Turret(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "gun", true));
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "smooth-stone", false));
					break;
				case '_':
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(100, 100, 255), 100, "water", false));
					triggers.push_back(Trigger(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "triggerWater", false));
					break;
				case ',':
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "wood-floor", false));
					break;
				case '=':
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "warning", false));
					break;
				case '?':
					goal.SetPos(x*STANDARD_SIZE, y*STANDARD_SIZE);
					entities.push_back(Entity(glm::vec2(x*STANDARD_SIZE, y*STANDARD_SIZE), glm::vec2(STANDARD_SIZE), glm::vec3(0, 255, 122), 100, "goal", false));
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

