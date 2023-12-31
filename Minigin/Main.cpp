#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "GameObject.h"
#include "FPS.h"
#include "Input.h"
#include "Commands.h"
#include "DeathObserver.h"
#include "ScoreObserver.h"
#include "MapCreator.h"
#include "DataTypes.h"
#include "ServiceLocator.h"
#include "ComponentsIncludes.h"
#include "BlackBoard.h"

void load()
{

	auto& startscene = dae::SceneManager::GetInstance().CreateScene("StartScreen", 0);
	auto& soloScene = dae::SceneManager::GetInstance().CreateScene("SoloModeScene", 1);
	auto& versusScene = dae::SceneManager::GetInstance().CreateScene("VersusModeScene", 2);
	auto& coopScene = dae::SceneManager::GetInstance().CreateScene("CoopModeScene", 3);


	dae::SceneManager::GetInstance().loadScene("StartScreen");

	auto to = std::make_shared<dae::GameObject>();
	auto go = std::make_shared<dae::GameObject>();
	auto background = std::make_shared<dae::GameObject>();

	auto textureComponentGo = std::make_shared <dae::TextureComponent>(go);
	auto textureComponentBackground = std::make_shared <dae::TextureComponent>(background);

	auto blackBoard = std::make_shared<dae::BlackBoard>();


	//fonts
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);

	


	//BACKGROUND
	background->AddComponent(textureComponentBackground);
	background->GetComponent<dae::TextureComponent>()->SetTexture("titlescreen.jpg");
	background->SetLocalPosition({ 105, 0 });
	
	startscene.Add(background);


	//STARTSCREEN
	auto startGameHandler = std::make_shared<dae::GameObject>();

	dae::SceneManager::GetInstance().SetNextSceneName("SoloModeScene");

	auto gameModeText = std::make_shared<dae::TextObject>("GameMode: Solo Mode", font);
	startGameHandler->AddComponent(gameModeText);
	gameModeText->SetPosition(155, 300);

	auto startGameText = std::make_shared<dae::TextObject>("Press ENTER/START to start", font);
	startGameHandler->AddComponent(startGameText);
	startGameText->SetPosition(120, 240);

	auto switchGameModeText = std::make_shared<dae::TextObject>("Press TAB to switch Game Mode", smallFont);
	startGameHandler->AddComponent(switchGameModeText);
	switchGameModeText->SetPosition(200, 350);
	

	startscene.Add(startGameHandler);

	//MAP
	auto map = std::make_shared<dae::GameObject>();
	auto createMapComponent = std::make_shared<dae::MapCreator>(map);
	map->AddComponent(createMapComponent);
	soloScene.Add(map);
	versusScene.Add(map);
	coopScene.Add(map);

	//FPS COUNTER
	auto fpsCounter = std::make_shared<dae::GameObject>();
	auto fpsCalc = std::make_shared<dae::FPS>(fpsCounter);
	fpsCounter->AddComponent(fpsCalc);
	
	auto fpsText = std::make_shared <dae::TextObject>("FPS: ", fpsFont);
	fpsCounter->AddComponent(fpsText);

	fpsCounter->GetComponent<dae::TextObject>()->SetPosition(560.f, 450.f);
	soloScene.Add(fpsCounter);
	versusScene.Add(fpsCounter);
	coopScene.Add(fpsCounter);

	
//-------------Players-------------//
std::vector<std::weak_ptr<dae::GameObject>> players;

//PLAYER IN SOLO MODE
#pragma region Player1


	//create player 1
	auto firstPlayer = std::make_shared<dae::GameObject>();
	firstPlayer->SetLocalPosition({ 22, 404 });

	//texture component
	auto tankRedTexture = std::make_shared <dae::TextureComponent>(firstPlayer, 25.f, 25.f);
	firstPlayer->AddComponent(tankRedTexture);
	firstPlayer->GetComponent<dae::TextureComponent>()->SetTexture("Sprites/RedTank.png");

	//tourret Component
	auto redTankTourret = std::make_shared <dae::TourretComponent>(firstPlayer, createMapComponent->GetCubes(), 45.f, 45.f, false);
	redTankTourret->SetTexture("Sprites/RedTankGun.png");
	firstPlayer->AddComponent(redTankTourret);

	//collision component
	auto redTankCollision = std::make_shared <dae::CollisionComponent>(firstPlayer, createMapComponent->GetCubes());
	firstPlayer->AddComponent(redTankCollision);

	//Damage/health component
	auto TankRedDamageComponent = std::make_shared <dae::DamageComponent>(firstPlayer, true);
	firstPlayer->AddComponent(TankRedDamageComponent);

	//score observer / component
	auto p1Score = std::make_shared <dae::ScoreComponent>(firstPlayer, blackBoard, true);
	auto scoreTextP1 = std::make_shared <dae::TextObject>("Score: " + std::to_string(p1Score->GetCurrentScore()), fpsFont);

	std::shared_ptr<dae::ScoreObserver> observerScoreP1 = std::make_shared<dae::ScoreObserver>(p1Score, scoreTextP1);
	firstPlayer->AddComponent(p1Score);
	firstPlayer->AddComponent(scoreTextP1);
	scoreTextP1->SetPosition(10.f, 450.f);
	firstPlayer->GetComponent<dae::ScoreComponent>()->GetSubject()->AddObserver(observerScoreP1);

	soloScene.Add(firstPlayer);
	versusScene.Add(firstPlayer);
	coopScene.Add(firstPlayer);

	players.push_back(firstPlayer);

#pragma region InputP1
	//KEYBOARD
	int ControllerIndex{ 0 };
	dae::Input::GetInstance().AddController(std::make_shared<dae::Gamepad>(ControllerIndex));

	float speed{ 80.f };
	//move left
	auto moveComm = std::make_shared<dae::MoveCommand>(firstPlayer, speed, dae::TankInput::Left);
	dae::Input::GetInstance().AddCommand(std::make_pair(SDL_SCANCODE_A, SDL_KEYMAPCHANGED), moveComm);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::DPadLeft), moveComm);

	//move right
	moveComm = std::make_shared<dae::MoveCommand>(firstPlayer, speed, dae::TankInput::Right);
	dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_D, SDL_KEYMAPCHANGED)), moveComm);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::DPadRight), moveComm);

	//move down
	moveComm = std::make_shared<dae::MoveCommand>(firstPlayer, speed, dae::TankInput::Down);
	dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_S, SDL_KEYMAPCHANGED)), moveComm);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::DPadDown), moveComm);

	//move up
	moveComm = std::make_shared<dae::MoveCommand>(firstPlayer, speed, dae::TankInput::Up);
	dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_W, SDL_KEYMAPCHANGED)), moveComm);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::DPadUp), moveComm);


	//tourret control player 1
	//move left
	auto tourretMovement = std::make_shared<dae::MoveTourretCommand>(firstPlayer, dae::TourretInput::TourretLeft);
	dae::Input::GetInstance().AddCommand(std::make_pair(SDL_SCANCODE_LEFT, SDL_KEYDOWN), tourretMovement);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::ButtonWest), tourretMovement);

	//move right
	tourretMovement = std::make_shared<dae::MoveTourretCommand>(firstPlayer, dae::TourretInput::TourretRight);
	dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_RIGHT, SDL_KEYDOWN)), tourretMovement);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::ButtonEast), tourretMovement);

	//move down
	tourretMovement = std::make_shared<dae::MoveTourretCommand>(firstPlayer, dae::TourretInput::TourretDown);
	dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_DOWN, SDL_KEYDOWN)), tourretMovement);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::ButtonSouth), tourretMovement);

	//move up
	tourretMovement = std::make_shared<dae::MoveTourretCommand>(firstPlayer, dae::TourretInput::TourretUp);
	dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_UP, SDL_KEYDOWN)), tourretMovement);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::ButtonNorth), tourretMovement);

	//DOUBLE INPUT
	//left up
	tourretMovement = std::make_shared<dae::MoveTourretCommand>(firstPlayer, dae::TourretInput::TourretLeftUp);
	auto keyPair = std::make_pair(
		std::make_pair(SDL_SCANCODE_LEFT, SDL_KEYDOWN),
		std::make_pair(SDL_SCANCODE_UP, SDL_KEYDOWN));

	dae::Input::GetInstance().AddCommand(keyPair, tourretMovement);

	//left down
	tourretMovement = std::make_shared<dae::MoveTourretCommand>(firstPlayer, dae::TourretInput::TourretLeftDown);
	keyPair = std::make_pair(
		std::make_pair(SDL_SCANCODE_LEFT, SDL_KEYDOWN),
		std::make_pair(SDL_SCANCODE_DOWN, SDL_KEYDOWN));

	dae::Input::GetInstance().AddCommand(keyPair, tourretMovement);

	//right up
	tourretMovement = std::make_shared<dae::MoveTourretCommand>(firstPlayer, dae::TourretInput::TourretRightUp);
	keyPair = std::make_pair(
		std::make_pair(SDL_SCANCODE_RIGHT, SDL_KEYDOWN),
		std::make_pair(SDL_SCANCODE_UP, SDL_KEYDOWN));

	dae::Input::GetInstance().AddCommand(keyPair, tourretMovement);

	//right down
	tourretMovement = std::make_shared<dae::MoveTourretCommand>(firstPlayer, dae::TourretInput::TourretRightDown);
	keyPair = std::make_pair(
		std::make_pair(SDL_SCANCODE_RIGHT, SDL_KEYDOWN),
		std::make_pair(SDL_SCANCODE_DOWN, SDL_KEYDOWN));

	dae::Input::GetInstance().AddCommand(keyPair, tourretMovement);


	//shoot
	auto tourretShoot = std::make_shared<dae::ShootTourretCommand>(firstPlayer);
	dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_SPACE, SDL_KEYDOWN)), tourretShoot);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::RightShoulder), tourretShoot);

	//skip map
	auto skipMap = std::make_shared<dae::SkipMapCommand>(map);
	dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_F1, SDL_KEYDOWN)), skipMap);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::Back), skipMap);

	

	#pragma endregion

#pragma endregion




#pragma region Player2

	//create player 2
	auto secondPlayer = std::make_shared<dae::GameObject>();
	secondPlayer->SetLocalPosition({ 437, 25 });

	//texture component
	auto tankGreenTexture = std::make_shared <dae::TextureComponent>(secondPlayer, 25.f, 25.f);
	secondPlayer->AddComponent(tankGreenTexture);
	secondPlayer->GetComponent<dae::TextureComponent>()->SetTexture("Sprites/GreenTank.png");

	//tourret Component
	auto greenTankTourret = std::make_shared <dae::TourretComponent>(secondPlayer, createMapComponent->GetCubes(), 45.f, 45.f, false);
	greenTankTourret->SetTexture("Sprites/GreenTankGun.png");
	secondPlayer->AddComponent(greenTankTourret);

	//collision component
	auto greenTankCollision = std::make_shared <dae::CollisionComponent>(secondPlayer, createMapComponent->GetCubes());
	secondPlayer->AddComponent(greenTankCollision);

	//Damage/health component
	auto TankGreenDamageComponent = std::make_shared <dae::DamageComponent>(secondPlayer, true);
	secondPlayer->AddComponent(TankGreenDamageComponent);


	//score observer / component
	//auto p2Score = std::make_shared <dae::ScoreComponent>(secondPlayer, blackBoard);
	//auto scoreTextP1 = std::make_shared <dae::TextObject>("Score: " + std::to_string(p2Score->GetCurrentScore()), fpsFont);

	//std::shared_ptr<dae::ScoreObserver> observerScoreP2 = std::make_shared<dae::ScoreObserver>(p1Score, scoreTextP1);
	secondPlayer->AddComponent(p1Score);
	secondPlayer->AddComponent(scoreTextP1);
	//secondPlayer->GetComponent<dae::ScoreComponent>()->GetSubject()->AddObserver(observerScoreP2);

	versusScene.Add(secondPlayer);
	coopScene.Add(secondPlayer);
	players.push_back(secondPlayer);

	///regular commands not specific to player 2
	//startGame
	auto startGameCommand = std::make_shared<dae::StartGameCommand>(firstPlayer, secondPlayer);
	dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_RETURN, SDL_KEYDOWN)), startGameCommand);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::Start), startGameCommand);

	//choose gameMode
	auto switchGameModeCommand = std::make_shared<dae::SwitchGameModeCommand>(startGameHandler);
	dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_TAB, SDL_KEYDOWN)), switchGameModeCommand);

	//second controller index
	++ControllerIndex;

#pragma region InputP2
	//KEYBOARD
	dae::Input::GetInstance().AddController(std::make_shared<dae::Gamepad>(ControllerIndex));

	//move left
	moveComm = std::make_shared<dae::MoveCommand>(secondPlayer, speed, dae::TankInput::Left);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::DPadLeft), moveComm);

	//move right
	moveComm = std::make_shared<dae::MoveCommand>(secondPlayer, speed, dae::TankInput::Right);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::DPadRight), moveComm);

	//move down
	moveComm = std::make_shared<dae::MoveCommand>(secondPlayer, speed, dae::TankInput::Down);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::DPadDown), moveComm);

	//move up
	moveComm = std::make_shared<dae::MoveCommand>(secondPlayer, speed, dae::TankInput::Up);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::DPadUp), moveComm);


	//tourret control player 1
	//move left
	tourretMovement = std::make_shared<dae::MoveTourretCommand>(secondPlayer, dae::TourretInput::TourretLeft);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::ButtonWest), tourretMovement);

	//move right
	tourretMovement = std::make_shared<dae::MoveTourretCommand>(secondPlayer, dae::TourretInput::TourretRight);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::ButtonEast), tourretMovement);

	//move down
	tourretMovement = std::make_shared<dae::MoveTourretCommand>(secondPlayer, dae::TourretInput::TourretDown);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::ButtonSouth), tourretMovement);

	//move up
	tourretMovement = std::make_shared<dae::MoveTourretCommand>(secondPlayer, dae::TourretInput::TourretUp);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::ButtonNorth), tourretMovement);


	//shoot
	tourretShoot = std::make_shared<dae::ShootTourretCommand>(secondPlayer);
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::RightShoulder), tourretShoot);


	//startGame
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::Start), startGameCommand);

	//skip map
	dae::Input::GetInstance().AddCommand(std::make_pair(ControllerIndex, dae::Gamepad::ControllerButton::Back), skipMap);
#pragma endregion

	
#pragma endregion

//-------------Enemys-------------//
#pragma region Enemies

	std::vector<dae::EnemyData> enemyDataList = {
	   {std::make_pair("BlueTankEnemy", glm::vec2{100, 358})},
	   {std::make_pair("BlueTankEnemy", glm::vec2{340, 165})},
	   {std::make_pair("BlueTankEnemy", glm::vec2{140, 22})},
	   {std::make_pair("BlueTankEnemy", glm::vec2{240, 117})},
	   {std::make_pair("Recognizer", glm::vec2{240, 358})},
	};

	std::vector<std::weak_ptr<dae::GameObject>> enemyList;
	//std::vector<std::weak_ptr<dae::GameObject>> pinkTankEnemies;
	//std::vector<std::weak_ptr<dae::GameObject>> redTankEnemies;


	for (const auto& enemyData : enemyDataList)
	{
		auto enemy = std::make_shared<dae::GameObject>();
		auto enemyTexture = std::make_shared<dae::TextureComponent>(enemy, 25.f, 25.f);
		enemy->AddComponent(enemyTexture);
		soloScene.Add(enemy);
		versusScene.Add(enemy);
		coopScene.Add(enemy);

		enemy->SetLocalPosition(enemyData.enemyData.second);

		auto enemyCollisionComp = std::make_shared<dae::CollisionComponent>(enemy, createMapComponent->GetCubes());
		enemy->AddComponent(enemyCollisionComp);

		auto enemyTourretComponent = std::make_shared<dae::TourretComponent>(enemy, createMapComponent->GetCubes(), 45.f, 45.f, true);
		enemyTourretComponent->SetTexture("Sprites/BlueTankGun.png");

		if (enemyData.enemyData.first != "Recognizer")
		{

			enemy->GetComponent<dae::TextureComponent>()->SetTexture("Sprites/BlueTank.png");

			enemy->AddComponent(enemyTourretComponent);

			auto enemyAiMovement = std::make_shared<dae::EnemyAiComponent>(enemy, dae::EnemyType::tank);
			enemy->AddComponent(enemyAiMovement);

		}
		else
		{
			enemy->GetComponent<dae::TextureComponent>()->SetTexture("Sprites/Recognizer.png");

			auto enemyAiMovement = std::make_shared<dae::EnemyAiComponent>(enemy, dae::EnemyType::recognizer);
			enemy->AddComponent(enemyAiMovement);

			enemy->GetComponent<dae::CollisionComponent>()->SetPlayersToCollideWith(players);
		}

		auto enemyDamageComponent = std::make_shared<dae::DamageComponent>(enemy, false);
		enemy->AddComponent(enemyDamageComponent);

		//set the enemies enemies
		enemyTourretComponent->SetEnemies(players);
		enemyTourretComponent->SetEnemyCollisionSize({ 25, 25 });


		enemyList.push_back(enemy);
		//pinkTankEnemies.push_back(enemy);
		//redTankEnemies.push_back(enemy);
	}

	
	//set the players enemies 
	redTankTourret->SetEnemies(enemyList);
	redTankTourret->SetEnemyCollisionSize({ 25, 25 });

	greenTankTourret->SetEnemies(enemyList);
	greenTankTourret->SetEnemyCollisionSize({ 25, 25 });

	//add player to list for versus mode 
	enemyList.push_back(firstPlayer);
	enemyList.push_back(secondPlayer);
	enemyDataList.push_back({ std::make_pair("player1", glm::vec2{ 22, 404 }) });
	enemyDataList.push_back({ std::make_pair("player2", glm::vec2{ 437, 25  }) });

#pragma endregion

	auto gameStateComponent = std::make_shared<dae::GameStateComponent>(map, enemyList, enemyDataList);
	map->AddComponent(gameStateComponent);

	auto muteAudioCommand = std::make_shared<dae::MuteAudioCommand>();
	dae::Input::GetInstance().AddCommand(std::make_pair(SDL_SCANCODE_F2, SDL_KEYDOWN), muteAudioCommand);

	//sounds
	Engine::ServiceLocator::RegisterAudioSystem(new Engine::Sdl_AudioNavigator());
	Engine::ServiceLocator::GetAudioSystem().AddSound("Background.mp3", (Engine::SoundId)Engine::Sound::background, true);
	Engine::ServiceLocator::GetAudioSystem().AddSound("FailMusic.mp3", (Engine::SoundId)Engine::Sound::loseGame);
	Engine::ServiceLocator::GetAudioSystem().AddSound("MainMenuMusic.mp3", (Engine::SoundId)Engine::Sound::mainMenu, true);
	Engine::ServiceLocator::GetAudioSystem().AddSound("Shoot.mp3", (Engine::SoundId)Engine::Sound::shoot);
	Engine::ServiceLocator::GetAudioSystem().AddSound("Teleport.mp3", (Engine::SoundId)Engine::Sound::teleport);

	//play menu music
	Engine::ServiceLocator::GetAudioSystem().Play((Engine::SoundId)Engine::Sound::mainMenu, 6.f);

	

	std::cout << "\nPress F2 to mute audio\n";
	std::cout << "Press F1 to skip level\n";

	std::cout << "\n[CONTROLS]\n";
	std::cout << "\n[MOVEMENT]\n";
	std::cout << "wasd or D-Pad\n";
	std::cout << "\n[TOURRET MOVEMENT]\n";
	std::cout << "arrow keys or X = left, Y = up, B = right, A = down]\n";
	std::cout << "\n[SHOOT]\n";
	std::cout << "spacebar or right shoulder button\n";


}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}



	#pragma region unusedCode
	//LOGO
	/*go->AddComponent(textureComponentGo);
	go->GetComponent<dae::TextureComponent>().get()->SetTexture("logo.tga");
	go->SetLocalPosition({ 216, 180 });
	scene.Add(go);*/

	//text
	/*auto text = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	to->AddComponent(text);
	to->GetComponent<dae::TextObject>()->SetPosition(125, 50);
	scene.Add(to);*/

	//-------------sprite parent P1-------------//
	//auto qBert = std::make_shared<dae::GameObject>();
	//auto parentTexture = std::make_shared <dae::TextureComponent>(qBert);
	//auto parentHealth = std::make_shared <dae::HealthComponent>(spriteParent);
	//auto liveTextP1 = std::make_shared <dae::TextObject>("Remaining Lives: " + std::to_string(parentHealth->GetCurrentHealth()), fpsFont);
	//auto scoreTextP1 = std::make_shared <dae::TextObject>("Score: " + std::to_string(parentScore->GetCurrentScore()), fpsFont);
	
	//auto parentScore = std::make_shared <dae::ScoreComponent>(spriteParent);
	//std::shared_ptr<dae::ScoreObserver> observerScoreP1 = std::make_shared<dae::ScoreObserver>(parentScore, scoreTextP1);
	//spriteParent->GetComponent<dae::ScoreComponent>()->GetSubject()->AddObserver(observerScoreP1);
	//spriteParent->AddComponent(parentScore);

	//qBert->AddComponent(parentTexture); 
	//spriteParent->AddComponent(parentHealth);
	//spriteParent->AddComponent(liveTextP1);
	//spriteParent->AddComponent(scoreTextP1);

	//liveTextP1->SetPosition(455.f, 450.f);
	//scoreTextP1->SetPosition(455.f, 420.f);

	//adding observer
	//std::shared_ptr<dae::DeathObserver> observerHealthP1 = std::make_shared<dae::DeathObserver>(parentHealth, liveTextP1);
	//spriteParent->GetComponent<dae::HealthComponent>()->GetSubject()->AddObserver(observerHealthP1);

	//qBert->GetComponent<dae::TextureComponent>()->SetTexture("Qbert.png");
	//qBert->SetLocalPosition({ 160, 160 });

	//map extra component
	//auto GameStateComponent = std::make_shared<dae::GameStateComponent>(map, spriteChild);
	//map->AddComponent(GameStateComponent);

	//auto childHealth = std::make_shared <dae::HealthComponent>(spriteChild);
	//auto childScore = std::make_shared <dae::ScoreComponent>(spriteChild);
	//auto liveTextP2 = std::make_shared <dae::TextObject>("Remaining Lives: " + std::to_string(childHealth->GetCurrentHealth()), fpsFont);
	//auto scoreTextP2 = std::make_shared <dae::TextObject>("Score: " + std::to_string(childScore->GetCurrentScore()), fpsFont);

	//spriteChild->AddComponent(collisionComponentP2);
	//spriteChild->AddComponent(childHealth);
	//spriteChild->AddComponent(childScore);
	//spriteChild->AddComponent(liveTextP2);
	//spriteChild->AddComponent(scoreTextP2);
	
	//liveTextP2->SetPosition(5.f, 450.f);
	//scoreTextP2->SetPosition(5.f, 420.f);

	//adding observer
	//std::shared_ptr<dae::DeathObserver> observerHealthP2 = std::make_shared<dae::DeathObserver>(childHealth, liveTextP2);
	//spriteChild->GetComponent<dae::HealthComponent>()->GetSubject()->AddObserver(observerHealthP2);

	//std::shared_ptr<dae::ScoreObserver> observerScoreP2 = std::make_shared<dae::ScoreObserver>(childScore, scoreTextP2);
	//spriteChild->GetComponent<dae::ScoreComponent>()->GetSubject()->AddObserver(observerScoreP2);

	//spriteChild->SetParent(spriteParent);

	//CONTROLLER

	////move left
	//auto moveComm = std::make_shared<dae::MoveCommand>(qBert, speed, dae::PlayerInput::Left);
	//dae::Input::GetInstance().AddCommand(std::make_pair(Controller1Index, dae::Gamepad::ControllerButton::DPadLeft), moveComm);

	////move right
	//moveComm = std::make_shared<dae::MoveCommand>(qBert, speed, dae::PlayerInput::Right);
	//dae::Input::GetInstance().AddCommand(std::make_pair(Controller1Index, dae::Gamepad::ControllerButton::DPadRight), moveComm);

	////move down
	//moveComm = std::make_shared<dae::MoveCommand>(qBert, speed, dae::PlayerInput::Down);
	//dae::Input::GetInstance().AddCommand(std::make_pair(Controller1Index, dae::Gamepad::ControllerButton::DPadDown), moveComm);

	////move up
	//moveComm = std::make_shared<dae::MoveCommand>(qBert, speed, dae::PlayerInput::Up);
	//dae::Input::GetInstance().AddCommand(std::make_pair(Controller1Index, dae::Gamepad::ControllerButton::DPadUp), moveComm);

	////Damage player1
	//auto damageComm = std::make_shared<dae::DamageCommand>(qBert);
	//dae::Input::GetInstance().AddCommand(std::make_pair(Controller1Index, dae::Gamepad::ControllerButton::ButtonSouth), damageComm);

	////add Score
	//// add a score command then bind to p1
	//auto addScoreComm = std::make_shared<dae::AddScoreCommand>(qBert);
	//dae::Input::GetInstance().AddCommand(std::make_pair(Controller1Index, dae::Gamepad::ControllerButton::ButtonWest), addScoreComm);
	//	

	//Damage Player2
	// damageComm = std::make_shared<dae::DamageCommand>(spriteChild);
	//dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_H, SDL_KEYDOWN)), damageComm);
	
	//add Score
	// add a score command then bind to p2
	//addScoreComm = std::make_shared<dae::AddScoreCommand>(spriteChild);
	//dae::Input::GetInstance().AddCommand((std::make_pair(SDL_SCANCODE_Y, SDL_KEYDOWN)), addScoreComm);

	//Sounds 
	//note: sound give a memory leak 
	//Engine::ServiceLocator::RegisterAudioSystem(new Engine::Sdl_AudioNavigator());
	//Engine::ServiceLocator::GetAudioSystem().AddSound("Swearing.wav", (unsigned short)Engine::Sound::QbertHit);
	//Engine::ServiceLocator::GetAudioSystem().AddSound("QBertJump.wav", (unsigned short)Engine::Sound::QbertJump);
	//Engine::ServiceLocator::GetAudioSystem().AddSound("QBertFall.wav", (unsigned short)Engine::Sound::QbertFall);
	//Engine::ServiceLocator::GetAudioSystem().AddSound("RoundCompleteTune.wav", (unsigned short)Engine::Sound::QbertWin);

#pragma endregion