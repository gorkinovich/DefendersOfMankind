BulletBoss2 = {
    ["Components"] = {
        "Position", "GeneralData", "Graphics", "BasicMovement", "PhysicEntity",
        "DamageTrigger", "Death", "StateMachineExecutor", "Life", "ParticleSystem"
    };

	--Información para poder generar la entidad desde un componente generador
	["model"] = "RedBullet.mesh";
	["material"] = "RedBullet";
	["scale"] = "0.02 0.02 0.02";

	--Componente Life
	["life"] = "1";

	--Componente BasicMovement
	["movementDescriptor"] = "BulletGoToPlayerMovement", -- "BulletHorizontalMovement", -- "BulletGoToPlayerMovement"

	--Componente  StateMachineExecutor
	["behavior"] = "LifeCycle_BULLET_BOSS_1";

	--Componente PhysicEntity
	["physic_entity"] = "simple",
	["physic_type"] = "kinematic",
	["physic_trigger"] = "true",
	["physic_shape"] = "capsule";
	["physic_radius"] = "5";
	["physic_height"] = "2";
	["physic_mass"] = "1",
	["physic_collision_group"] = "3";

	--Componente DamageTrigger
	["damage"] = "50";

	--Componente ParticleSystem
	["NumberOfPS"] = "1";
		--ParticleSystem1
		["PSName1"] = "BulletBoss1";
		["PSTimeToLife1"] = "10000";
};

