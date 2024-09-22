local Array = require("array")

local a = array_new()
print(a, a:size())
local b = Array.new()
print(b, b:size())

local va = a:at(100)
print("a[100]:", va)

b:set(64, 442)
print("b[64]:", b:at(64))

local vb = b:at(200)
