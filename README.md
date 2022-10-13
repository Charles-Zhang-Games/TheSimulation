# The Simulatin

Raw inspiration: While testing basic map with "Enable Large Worlds" with those tall pillars, I got a moment of sacred inspiration.

## Standard Levels

0. Level Choosing Map
1. Third Person Walkaround
2. Hidden Trapdoor
5. Chasing the Car

## Manefest

Style: Raw, blocking, Unreal, Technical

**Baseline Tests**

1. Meta-huamns: Third-person basic setup
2. C++: Everything C++
3. C++ HUD
	* (Level name and Play Time) (achieved with game instanxe which stores all names and custom player controller base - so it's a meta layer, independant of the levels)

Levels:

1. Entry map: infinite extent; Functional.
2. TP Jump level: Basic navigation learning.
3. TP Jump Level: Through the trapdoor. World layer test
4. TP Jump with jump height reduced: Push the boxes; Physics test.
5. Pressure plate: Mechanism teaching.
6. Pressure plate Split Screen: Perform tasks with two characters; Tests split screen. Toggle split screen when touching the other character.
7. Seamless Travel (https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/Networking/Travelling/) - different from streaming.
8. 2km Vehicle: Basic vehicle driving learning; Nanite pyramid.
9.  4km Vehicle: Getting a sense where we are going. Foretelling.
10. 16km Vehicle: Now getting a better sense where we are going. Foretelling.
11. 32km Vehicle: Barebone open world experience. Open-world capacity test.
12. 1-2 Player switching: Mechanism teaching.
13. 1-2 Player Swtching 8km map: Long distance numerical accuracy and blueprint functioning; Modular gameplay component (location display text).
14. Spaceship: Mechnism teaching; Mechanism development (manuverou control feeling).
15. Spherical Planet: Planet size atmosphere.
16. Solar system: large world coordinates.
17. : Dynamic interior test for open world buildings.
	https://docs.unrealengine.com/4.27/en-US/BuildingWorlds/LevelStreaming/HowTo/StreamWithCPP/
13. : Gameplay tag test.
16. The Drop: Long term drop -> Infinite drop
17. The Elevator: Test basic dynamics + level streaming/data layer - sort of like how Portal 2 can allow the player dropping for so long
27. The Dream Elevator: Travelling between things in open world cityscape like levels; Tests protected and selective collision disabling
28. Procedural Foliage