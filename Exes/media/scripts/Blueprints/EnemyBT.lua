EnemyBT = {
    ["Components"] = {
        "Position", "GeneralData", "Graphics", "DamageTrigger", "PhysicEntity", "BasicMovement",
        "Generator", "SwitchTrigger", "Life", "Death", "ParticleSystem", "StateMachineExecutor", "BTExecutor", "Sound"
    },

	--Información para poder generar la entidad desde un componente generador
	["Model"] = "BadShipInsector.mesh";
	["Material"] = "BadShipInsector";
	["Scale"] = "0.2 0.2 0.2";

	--Componente Life
	["life"] = "30";

	--Componente BasicMovement
	["movementDescriptor"] = "GoToQuadrantMovement",	--"GoToPlayerMovement", --"GoToQuadrantMovement",

	--Componente  StateMachineExecutor
	["behavior"] = "LifeCycle_ENEMY";

	--Componente PhysicEntity
	["physic_entity"] = "simple",
	["physic_type"] = "kinematic",
	["physic_trigger"] = "true",
	["physic_shape"] = "box",
	["physic_dimensions"] = "2 2 2.7",
	["physic_mass"] = "1",
	["physic_collision_group"] = "2",

	--Componente DamageTrigger
	["damage"] = "50";

	--Componente SwitchTrigger
	["target"] = "Jugador",

	--Componente Generator
	["Generator::children"] = "1";

	["Generator::child1::type"] = "Bullet";
	["Generator::child1::interval"] = "0"; --Por defecto no se dispara, pero con sobreescribir este parámetro en Ogitor basta
	["Generator::child1::relativePosition"] = "0 0 15";
	["Generator::child1::orientation"] = "0 0 0";

	--Componente ParticleSystem
	["NumberOfPS"] = "2";
		--ParticleSystem1
		["PSName1"] = "Explosion";
		["PSTimeToLife1"] = "2500";
		--ParticleSystem2
		["PSName2"] = "Chispas";
		["PSTimeToLife2"] = "1000";

	--Componente Sound
	["NumberOfSounds"] = "1";
	["SoundName1"] = "Explosion1.wav";
	
	--Componente BTExecutor
	["BTname"] = "BT_AvoidPlayer";
	["targetQ1"] = "2";
	["targetQ2"] = "1";
};