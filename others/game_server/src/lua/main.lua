---@param x number
---@param y number
---@return number
function add(x, y)
    return x + y
end

--print(add(1, 2)) -- Output: 3

local test = require("test")
local t = test.new()
t:test() -- Output: test

global = {}
global.width = 1920