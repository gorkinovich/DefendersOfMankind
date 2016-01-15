PowerBullet = {
    ["Components"] = {
        "Position", "GeneralData", "BasicMovement", "PhysicEntity", "Graphics",
        "DamageTrigger", "Death", "StateMachineExecutor", "Life", "ParticleSystem", "Sound"
    };

	--Información para poder generar la entidad desde un componente generador
	["model"] = "PowerBullet.mesh";
	["material"] = "PowerBullet";
	["scale"] = "0.2 0.2 0.2";

	--Componente Life
	["life"] = "1";

	--Componente BasicMovement
	["movementDescriptor"] = "BulletHorizontalMovementPlayer";

	--Componente  StateMachineExecutor
	["behavior"] = "LifeCycle_PLAYER_BULLET";

	--Componente PhysicEntity
	["physic_entity"] = "simple",
	["physic_type"] = "kinematic",
	["physic_trigger"] = "true",
	["physic_shape"] = "capsule";
	["physic_radius"] = "1.5";
	["physic_height"] = "2";
	["physic_mass"] = "1",
	["physic_collision_group"] = "1";

	--Componente DamageTrigger
	["damage"] = "20";
	
	--Componente ParticleSystem
	["NumberOfPS"] = "1";
		--ParticleSystem1
		["PSName1"] = "PowerBullet";
		["PSTimeToLife1"] = "10000";
		
	--Componente Sound
	["NumberOfSounds"] = "1";
	["SoundName1"] = "Bullet.wav";
};

