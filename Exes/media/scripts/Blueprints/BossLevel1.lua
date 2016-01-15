BossLevel1 = {
    ["Components"] = {
        "Position", "GeneralData", "Graphics", "DamageTrigger", "PhysicEntity", "BasicMovement",
        "Generator", "SwitchTrigger", "Life", "Death", "ParticleSystem", "StateMachineExecutor", "Sound"
    },

	--Información para poder generar la entidad desde un componente generador
	["model"] = "BigBoss.mesh";
	["material"] = "BigBoss";
	["scale"] = "2 2 2";

	--Componente Life
	["life"] = "5000";

	--Componente BasicMovement
	["movementDescriptor"] = "UpDownMovement",

	--Componente  StateMachineExecutor
	["behavior"] = "LifeCycle_BOSS";

	--Componente PhysicEntity
	["physic_entity"] = "simple",
	["physic_type"] = "kinematic",
	["physic_trigger"] = "true",
	["physic_shape"] = "box",
	["physic_dimensions"] = "20 20 27",
	["physic_mass"] = "1",
	["physic_collision_group"] = "2",

	--Componente DamageTrigger
	["damage"] = "50";

	--Componente SwitchTrigger
	["target"] = "Jugador",

	--Componente Generator
	["Generator::children"] = "1";

	["Generator::child1::type"] = "BulletBoss1";
	["Generator::child1::interval"] = "2000";
	["Generator::child1::relativePosition"] = "0 -35 100";
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
};