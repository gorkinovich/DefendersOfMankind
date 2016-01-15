print("\nOh my god... that's the funky shit!!!\n");

SPANISH_TEXT = {
    ["TXT001"] = "Tras muchos años de profunda reflexión...";
    ["TXT002"] = "he llegado a la irrevocable conclusión...";
    ["TXT003"] = "que jugar mola más que desarrollar... xDD";
};

-- ********************************************************************************
-- Objects in lua test
-- http://www.lua.org/manual/5.1/
-- http://lua-users.org/wiki/MetamethodsTutorial
-- http://lua-users.org/wiki/ObjectOrientationTutorial
-- http://lua-users.org/wiki/InheritanceTutorial

FooClass = {};
FooClass_MetaTable = { __index = FooClass };

function FooClass:new(a, b, c)
    return setmetatable({
            prop1 = a or "Hello",
            prop2 = b or 42,
            prop3 = c or { 1, 2, 3 }
        }, FooClass_MetaTable);
end

function FooClass:print()
    print("FooClass:print()");
    print(self.prop1);
    print(self.prop2);
    print(self.prop3);
    print();
end

function testFooPrint()
    local testFoo = {
        FooClass:new(),
        FooClass:new(1),
        FooClass:new(1, 2),
        FooClass:new(1, 2, 3)
    };
    for k, v in pairs(testFoo) do
        v:print();
    end
end

testFooPrint();