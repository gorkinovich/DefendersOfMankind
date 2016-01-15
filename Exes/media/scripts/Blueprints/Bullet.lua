Bullet = {
    ["Components"] = {
        "Position", "GeneralData", "Graphics", "BasicMovement", "PhysicEntity",
        "DamageTrigger", "Death", "StateMachineExecutor", "Life", "ParticleSystem"
    };

	--Información para poder generar la entidad desde un componente generador
	["model"] = "RedBullet.mesh";
	["material"] = "RedBullet";
	["scale"] = "0.2 0.2 0.2";

	--Componente Life
	["life"] = "1";

	--Componente BasicMovement
	["movementDescriptor"] = "BulletHorizontalMovement";

	--Componente  StateMachineExecutor
	["behavior"] = "LifeCycle_BULLET";

	--Componente PhysicEntity
	["physic_entity"] = "simple",
	["physic_type"] = "kinematic",
	["physic_trigger"] = "true",
	["physic_shape"] = "capsule";
	["physic_radius"] = "1.5";
	["physic_height"] = "2";
	["physic_mass"] = "1",
	["physic_collision_group"] = "3";

	--Componente DamageTrigger
	["damage"] = "10";

	--Componente ParticleSystem
	["NumberOfPS"] = "1";
		--ParticleSystem1
		["PSName1"] = "RedBullet";
		["PSTimeToLife1"] = "10000";
};

