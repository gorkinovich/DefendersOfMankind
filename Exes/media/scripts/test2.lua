function test()
    print("Hello defender, from lua...");
end
test();
-- x = 42;
-- print("x -> ", x);
foo();
print("testBool -> ", testBool);
print("testNumber -> ", testNumber);
print("testString -> ", testString);
print("testTable -> ", testTable);
print("testTable[\"flag\"] -> ", testTable["flag"]);
print("testTable[\"number\"] -> ", testTable["number"]);
print("testTable[\"string\"] -> ", testTable["string"]);

print("\npairs(testTable)")
for key, value in pairs(testTable) do
    print(key, " : ", value)
end

print("\npairs(testArray)")
for key, value in pairs(testArray) do
    print(key, " : ", value)
end

print("\nipairs(testArray)")
for key, value in ipairs(testArray) do
    print(key, " : ", value)
end

include("test3.lua")