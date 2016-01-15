BossLevel2 = {
    ["Components"] = {
        "Position", "GeneralData", "Graphics", "DamageTrigger", "PhysicEntity", "BasicMovement",
        "Generator", "SwitchTrigger", "Life", "Death", "ParticleSystem", "StateMachineExecutor", "Sound", "BTExecutor"
    },

	--Información para poder generar la entidad desde un componente generador
	["model"] = "NaveNodriza.mesh";
	["material"] = "NaveNodriza";
	["scale"] = "15 15 15";

	--Componente Life
	["life"] = "8000";

	--Componente BasicMovement
	["movementDescriptor"] = "GoToQuadrantMovement",

	--Componente  StateMachineExecutor
	["behavior"] = "LifeCycle_BOSS";

	--Componente PhysicEntity
	["physic_entity"] = "simple",
	["physic_type"] = "kinematic",
	["physic_trigger"] = "true",
	["physic_shape"] = "box",
	["physic_dimensions"] = "50 40 10",
	["physic_mass"] = "1",
	["physic_collision_group"] = "2",

	--Componente DamageTrigger
	["damage"] = "50";

	--Componente SwitchTrigger
	["target"] = "Jugador",

	--Componente Generator
	["Generator::children"] = "1";

	["Generator::child1::type"] = "BulletBoss2";
	["Generator::child1::interval"] = "1000";
	["Generator::child1::relativePosition"] = "0 0 50";
	["Generator::child1::orientation"] = "0 0 0";

	

	--Componente ParticleSystem
	["NumberOfPS"] = "2";
		--ParticleSystem1
		["PSName1"] = "BigExplosion";
		["PSTimeToLife1"] = "2500";
		--ParticleSystem2
		["PSName2"] = "BigChispas";
		["PSTimeToLife2"] = "1000";

	--Componente Sound
	["NumberOfSounds"] = "1";
	["SoundName1"] = "Explosion1.wav";
	
	--Componente BTExecutor
	["BTname"] = "BT_Boss_Level2";
	["targetQ1"] = "0";
	["targetQ2"] = "3";
};