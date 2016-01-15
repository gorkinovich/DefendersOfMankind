Player = {
    ["Components"] = {
        "Position", "GeneralData", "Graphics", "AvatarController", "Life", "PhysicCharacter",
        "Generator", "ChangeMaterial", "ParticleSystem", "Death", "StateMachineExecutor", "DamageTrigger",
		"PowerUpController", "Sound"
    };

	--Player
	["isPlayer"] = "true";

	--Componente Life
	["life"] = "100";

	--Componente AvatarController
	["speed"] = "0.05";

	--Componente PhysicCharacter
	["physic_entity"] = "controller";
	["physic_type"] = "kinematic";
	["physic_shape"] = "capsule";
	["physic_radius"] = "4";
	["physic_height"] = "3";
	["physic_collision_group"] = "0";

	--Componente StateMachineExecutor
	["behavior"] = "LifeCycle_PLAYER";

	--Componente Generator
	["Generator::children"] = "4";

	["Generator::child1::type"] = "Bullet2";
	["Generator::child1::interval"] = "0";
	["Generator::child1::relativePosition"] = "0 2.5 -15";
	["Generator::child1::orientation"] = "0 0 0";

	["Generator::child2::type"] = "Bullet2";
	["Generator::child2::interval"] = "0";
	["Generator::child2::relativePosition"] = "0 -2.5 -15";
	["Generator::child2::orientation"] = "0 0 0";

	["Generator::child3::type"] = "PowerBullet";
	["Generator::child3::interval"] = "0";
	["Generator::child3::relativePosition"] = "0 2.5 -15";
	["Generator::child3::orientation"] = "0 0 0";

	["Generator::child4::type"] = "PowerBullet";
	["Generator::child4::interval"] = "0";
	["Generator::child4::relativePosition"] = "0 -2.5 -15";
	["Generator::child4::orientation"] = "0 0 0";

	--Componente ChangeMaterial
	["NewMaterial0"] = "Material#90";
	["NewMaterial1"] = "Material#91";
	["NewMaterial2"] = "Material#92";
	["NewMaterial3"] = "Material#93";
	["NewMaterial4"] = "Material#94";

	--Componente ParticleSystem
	["NumberOfPS"] = "7";
		--ParticleSystem1
		["PSName1"] = "Chispas";
		["PSTimeToLife1"] = "1000";
		--ParticleSystem2
		["PSName2"] = "Explosion";
		["PSTimeToLife2"] = "2500";
		--ParticleSystem3
		["PSName3"] = "Rocket";
		["PSTimeToLife3"] = "1000000";
		--ParticleSystem4			---- Power Ups ----
		["PSName4"] = "Shield";
		["PSTimeToLife4"] = "10000";
		--ParticleSystem5
		["PSName5"] = "Berserker";
		["PSTimeToLife5"] = "10000";
		--ParticleSystem6
		["PSName6"] = "AutoHeal";
		["PSTimeToLife6"] = "10000";
		--ParticleSystem7
		["PSName7"] = "Turbo";
		["PSTimeToLife7"] = "10000";
		
	--Componente DamageTrigger
	["damage"] = "10";

	--Componente Sound
	["NumberOfSounds"] = "2";
	["SoundName1"] = "Explosion1.wav";
	["SoundName2"] = "Bullet.wav";

};
