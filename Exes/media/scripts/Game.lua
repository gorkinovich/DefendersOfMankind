GameGlobalData = {
    -- Los datos relativos al mapa espacial del juego.
    ["SpaceMap"] = { {
            ["name"] = "Mission 1",
            ["description"] = "Mission bla bla bla...",
            ["file"] = "Mission01.lua",
            ["requires"] = {},
            ["button"] = "SpaceMap/Mission01"
        }, {
            ["name"] = "Mission 2",
            ["description"] = "Mission bla bla bla...",
            ["file"] = "Mission02.lua",
            ["requires"] = { "Mission 1" },
            ["button"] = "SpaceMap/Mission02"
        }, {
            ["name"] = "Mission 3",
            ["description"] = "Mission bla bla bla...",
            ["file"] = "Mission03.lua",
            ["requires"] = { "Mission 1" },
            ["button"] = "SpaceMap/Mission03"
        }, {
            ["name"] = "Mission 4",
            ["description"] = "Mission bla bla bla...",
            ["file"] = "Mission04.lua",
            ["requires"] = { "Mission 2", "Mission 3" },
            ["button"] = "SpaceMap/Mission04"
        }
    },
    -- Los datos relativos al área de investigación del juego.
    ["Research"] = { {
            ["name"] = "Research Area 1",
            ["left"] = { {
                    ["name"] = "Research A1L1",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 10,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A1L2",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 20,
                    ["buyed"] = false
                }
            },
            ["middle"] = { {
                    ["name"] = "Research A1M1",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 10,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A1M2",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 20,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A1M3",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 40,
                    ["buyed"] = false
                }
            },
            ["right"] = { {
                    ["name"] = "Research A1R1",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 10,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A1R2",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 20,
                    ["buyed"] = false
                }
            }
        }, {
            ["name"] = "Research Area 2",
            ["left"] = { {
                    ["name"] = "Research A2L1",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 10,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A2L2",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 20,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A2L3",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 40,
                    ["buyed"] = false
                }
            },
            ["middle"] = { {
                    ["name"] = "Research A2M1",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 10,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A2M2",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 20,
                    ["buyed"] = false
                }
            },
            ["right"] = { {
                    ["name"] = "Research A2R1",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 10,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A2R2",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 20,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A2R3",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 40,
                    ["buyed"] = false
                }
            }
        }, {
            ["name"] = "Research Area 3",
            ["left"] = { {
                    ["name"] = "Research A3L1",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 10,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A3L2",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 20,
                    ["buyed"] = false
                }
            },
            ["middle"] = { {
                    ["name"] = "Research A3M1",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 10,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A3M2",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 20,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A3M3",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 40,
                    ["buyed"] = false
                }
            },
            ["right"] = { {
                    ["name"] = "Research A3R1",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 10,
                    ["buyed"] = false
                }, {
                    ["name"] = "Research A3R2",
                    ["description"] = "Research bla bla bla...",
                    ["cost"] = 20,
                    ["buyed"] = false
                }
            }
        }
    },
    -- Los datos relativos a la tienda del juego.
    ["Workshop"] = {
        ["Workshop/PartButton1"] = {
            ["name"] = "Part 1",
            ["components"] = { {
                    ["name"] = "P1-X1",
                    ["description"] = "P1-X1",
                    ["cost"] = 10,
                    ["buyed"] = false,
                    ["selected"] = false
                }, {
                    ["name"] = "P1-X2",
                    ["description"] = "P1-X2",
                    ["cost"] = 100,
                    ["buyed"] = false,
                    ["selected"] = false
                }
            }
        },
        ["Workshop/PartButton2"] = {
            ["name"] = "Part 2",
            ["components"] = { {
                    ["name"] = "P2-X1",
                    ["description"] = "P2-X1",
                    ["cost"] = 10,
                    ["buyed"] = false,
                    ["selected"] = false
                }, {
                    ["name"] = "P2-X2",
                    ["description"] = "P2-X2",
                    ["cost"] = 100,
                    ["buyed"] = false,
                    ["selected"] = false
                }
            }
        },
        ["Workshop/PartButton3"] = {
            ["name"] = "Part 3",
            ["components"] = { {
                    ["name"] = "P3-X1",
                    ["description"] = "P3-X1",
                    ["cost"] = 10,
                    ["buyed"] = false,
                    ["selected"] = false
                }, {
                    ["name"] = "P3-X2",
                    ["description"] = "P3-X2",
                    ["cost"] = 100,
                    ["buyed"] = false,
                    ["selected"] = false
                }
            }
        },
        ["Workshop/PartButton4"] = {
            ["name"] = "Part 4",
            ["components"] = { {
                    ["name"] = "P4-X1",
                    ["description"] = "P4-X1",
                    ["cost"] = 10,
                    ["buyed"] = false,
                    ["selected"] = false
                }, {
                    ["name"] = "P4-X2",
                    ["description"] = "P4-X2",
                    ["cost"] = 100,
                    ["buyed"] = false,
                    ["selected"] = false
                }
            }
        }
    }
};
