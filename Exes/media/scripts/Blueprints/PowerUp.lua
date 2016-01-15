PowerUp = {
	["Components"] = {
		"Position", "GeneralData", "Graphics", "PhysicEntity", "PowerUpTrigger"
	};

	--Componente PowerUpTrigger
	["powerup"] = "0";	--Valor por defecto. Este valor debe cargarse desde Ogitor.
	
	--Componente PhysicEntity
	["physic_entity"] = "simple";
	["physic_type"] = "static";
	["physic_trigger"] = "true";
	["physic_shape"] = "box";
	["physic_dimensions"] = "5 5 5";
	["physic_mass"] = "1";
	["physic_collision_group"] = "5";
};
