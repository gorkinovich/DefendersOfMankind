CameraChange = {
    ["Components"] = {
        "Position", "GeneralData", "PhysicEntity", "CameraTrigger"
    };

	--Componente CameraTrigger
	["camera"] = "0"; --Valor por defecto. Este parámetro se debe configurar en Ogitor.

	--Componente PhysicEntity
	["physic_entity"] = "simple";
	["physic_type"] = "static";
	["physic_trigger"] = "true";
	["physic_shape"] = "box";
	["physic_dimensions"] = "512 150 10";
	["physic_mass"] = "1";
	["physic_collision_group"] = "5";
};