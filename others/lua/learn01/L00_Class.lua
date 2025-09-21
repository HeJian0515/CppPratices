--region 简单的类实现

-- 定义一个object新类型
local object = {}
object.__index = object

-- 定义一个构造函数
local function new_object(self)
    return setmetatable(self or {}, object)
end

-- 定义一个方法
function object:get(what)
    return self[what]
end

local obj = new_object{x = "x"}
assert(obj:get("x") == "x")

--endregion

--region 类简单的封装

local class = {}
setmetatable(class, class)

function class:__index(name)
    local class_methods = {}
    class_methods.__index = class_methods
    local class_object = {}
    local class_meta =  {
        __newindex = class_methods,
        __index = class_methods,
        __call = function(self, init)
            return setmetatable(init or {}, class_methods)
        end
    }
    class[name] = setmetatable(class_object, class_meta)
    return class_object
end

function class:__call(name)
    return self[name]
end

-- 等价于 local object = class.object
local object = class("object")
function object:get(what)
    return self[what]
    
end
local obj = object{x = "x"}
assert(obj:get("x") == "x")

--endregion

--region 集合类型

local set = class("set")
function set:new()
    return self {
        container = {},
        n = 0,
    }
end

function set:set(key, value)
    local container = self.container
    if value == nil then
        if container[key] ~= nil then
            container[key] = nil
            self.n = self.n - 1
        end
    else
        if container[key] == nil then
            self.n = self.n + 1
        end
        container[key] = value
    end
end

function set:get(key)
    return self.container[key]
end

local obj = class.set:new()
obj:set("x", 1)
obj:set("y", 2)
assert(obj.n == 2)
assert(obj:get("x") == 1)

--endregion

--region 集合类型2

local set2 = class("set2")

function set2:new()
    return self {
        _n = 0,
    }
end

function set2:set(key, value)
    if value == nil then
        if self[key] ~= nil then
            self[key] = nil
            self._n = self._n - 1
        end
    else
        if self[key] == nil then
            self._n = self._n + 1
        end
        self[key] = value
    end
end

local obj = class.set2:new()
obj:set("x", 1)
obj:set("y", 2)
assert(obj._n == 2)
assert(obj.x == 1)

--endregion

--region 集合类型3

local set3 = class("set3")
local SET = setmetatable({}, {__mode = "k"})

function set3:new()
    local object = self()
    SET[object] =  {n = 0}
    return object
end

function set3:set(key, value)
    if value == nil then
        if self[key] ~= nil then
            self[key] = nil
            SET[self].n = SET[self].n - 1
        end
    else
        if self[key] == nil then
            SET[self].n = SET[self].n + 1
        end
        self[key] = value
    end
end

function set3:__len()
    return SET[self].n
end

local obj = class.set3:new()
obj:set("x", 1)
obj:set("y", 2)
assert(#obj == 2)
assert(obj.x == 1)

for k, v in pairs(obj) do
    print(k, v)
end

--endregion


--region 集合类型4

local set4 = class("set4")
function set4:new()
    return self {
        [false] = 0,
    }
end

function set4:set(key, value)
    if value == nil then
        if self[key] ~= nil then
            self[key] = nil
            self[false] = self[false] - 1
        end
    else
        if self[key] == nil then
            self[false] = self[false] + 1
        end
        self[key] = value
    end
end

function set4:__len()
    return self[false]
end

local obj = class.set4:new()
obj:set("x", 1)
obj:set("y", 2)
assert(#obj == 2)
for k, v in pairs(obj) do
    if k then
        print(k, v)
    end
end

-- 定义一个 __pairs 方法滤掉 false
function set3:next(k)
    local nk, v = next(self, k)
    if nk == false then
        next(self, false)
    else
        return nk, v
    end
end

function set4:__pairs()
    return self.next, self
end

--endregion