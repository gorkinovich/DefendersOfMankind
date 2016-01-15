Obstacle = {
	["Components"] = {
		"Position", "GeneralData", "PhysicEntity", "DamageTrigger"
	};

	--Componente PhysicEntity
	["physic_entity"] = "simple";
	["physic_type"] = "static";
	["physic_trigger"] = "true";
	["physic_shape"] = "box";
	["physic_dimensions"] = "512 150 10";
	["physic_mass"] = "1";
	["physic_collision_group"] = "2";
	
	--Componente DamageTrigger
	["damage"] = "50";
};





--Obstacle = {
--    ["Components"] = {
--        "Position", "GeneralData", "Graphics", "DamageTrigger", "PhysicEntity", "Death", "StateMachineExecutor"
--    },
--	
--	--Componente Graphics
--	["scale"] = "0.001 0.001 0.001";
--
--	--Componente  StateMachineExecutor
--	["behavior"] = "LifeCycle_ENEMY";
--
--	--Componente PhysicEntity
--	["physic_entity"] = "simple",
--	["physic_type"] = "kinematic",
--	["physic_trigger"] = "true",
--	["physic_shape"] = "box",
--	["physic_dimensions"] = "3 3 4",
--	["physic_mass"] = "1",
--	["physic_collision_group"] = "2",
--
--	--Componente DamageTrigger
--	["damage"] = "100";
--
--};