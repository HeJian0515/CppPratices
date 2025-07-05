-- 元表是面向对象中的受限制类
-- 元表定义的是实例的行为，只能预先定义的操作集合的行为，不支持继承

-- t = {}
-- print(getmetatable(t)) -->nil
-- t1 = {}
-- setmetatable(t, t1)
-- print(getmetatable(t) == t1) --> true

-- print(getmetatable("hi")) -- table: 0000000000e7a640
-- print(getmetatable("xuxu")) -- table: 0000000000e7a640
-- print(getmetatable(10)) -- nil
-- print(getmetatable(print)) -- nil


-- ======================================================================
-- local mt = {} -- 集合的元表
-- local Set = {}
-- -- 使用指定的列表创建一个新的集合
-- function Set.new(l)
--     local set = {}
--     setmetatable(set, mt)
--     for _, v in ipairs(l) do
--         set[v] = true
--     end
--     return set
-- end

-- function Set.union(a, b)
--     if getmetatable(a) ~= mt or getmetatable(b) ~= mt then
--         error("attempt to 'add' a set with a non-set value", 2)
--     end

--     local res = Set.new{}
--     for k in pairs(a) do
--         res[k] = true
--     end
--     for k in pairs(b) do
--         res[k] = true
--     end

--     return res
-- end


-- function Set.intersection(a, b)
--     local res = Set.new{}
--     for k in pairs(a) do
--         res[k] = b[k]
--     end
--     return res
-- end

-- function Set.tostring(set)
--     local l = {}
--     for e in pairs(set) do
--         l[#l + 1] = tostring(e)
--     end
--     return "{" .. table.concat(l, ", ") .. "}";
-- end

-- mt.__add = Set.union
-- mt.__mul = Set.intersection
-- mt.__le = function(a, b) -- 子集
--     for k in pairs(a) do
--         if not b[k] then
--             return false
--         end
--     end
--     return true
-- end


-- mt.__lt = function(a, b) -- 真子集
--     return a <= b and not (b <= a)
-- end

-- mt.__eq = function(a, b)
--     return a <= b and b <= a
-- end

-- mt.__tostring = Set.tostring
-- mt.__metatable = "not your business" -- 让用户不能看到也不能修改集合的元表

-- return Set

-- s1 = Set.new{10, 20, 30, 50}
-- s2 = Set.new{30, 1}
-- print(getmetatable(s1)) -- table: 0000000000e1a940
-- print(getmetatable(s2)) -- table: 0000000000e1a940

-- s3 = s1 + s2
-- print(Set.tostring(s3)) -- {1, 30, 10, 20, 50}   

-- s = Set.new{1, 2, 3}
--// s = s + 8
--// print(s)

-- s1 = Set.new{2, 4}
-- s2 = Set.new{4, 10, 2}
-- print(s1 < s2)
-- print(s1 <= s2)
-- print(s1 >= s1)
-- print(s1 > s1)
-- print(s1 == s2 * s1)

-- __index元方法 ==================================================================

--[[ prototype = {x = 0, y = 0, width = 100, height = 100}

local mt = {}

function new(o)
    setmetatable(o, mt)
    return o
end

mt.__index = function(_, key)
    return prototype[key]
end ]]

-- mt.__index = prototype
-- 当 Lua 语言查找元表的一 index 字段时，会发现字段的值是表 prototype 。
-- 因此，Lua语言就会在这个表中继续查找，即等价地执行 prototype ［” width ＂］ 

-- w = new {x = 10, y = 20}
-- print(w.width) --> 100

-- __newindex元方法===========================================================
-- 当对一个表中不存在的索引赋值时，解释器就会查找_newindex元方法；
-- 如果这个元方法存在，那么解释器就调用它而不执行赋值
-- 如果这个元方法是一个表，解释器就在此表中执行赋值
-- rawset(t, k, v) <=> t[k] = v, 绕过元方法

-- 20.4.3 具有默认值的表 ===========================================
-- function setDefault(t, d)
--     local mt = {__index = function() return d end}
--     setmetatable(t, mt)
-- end

-- local mt = { __index = function(t) return t.___ end}
-- function setDefault(t, d)
--     t.___ = d
--     setmetatable(t, mt)
-- end

--[[ local key = {}
local mt = { __index = function(t) return t[key] end}
function setDefault(t, d)
    t[key] = d
    setmetatable(t, mt)
end ]]


--[[ tab = {x = 10, y = 20}
print(tab.x, tab.z) --> 10 , nil
setDefault(tab, 0)
print(tab.x, tab.z) --> 10, 0 ]]

-- 20.4.4 跟踪对表的访问 ========================================================
--[[ function track(t)
    local proxy = {} -- 't'的代理表

    local mt = {
        __index = function(_, k)
            print("*access to element " .. tostring(k))
            return t[k] -- 访问原来的表
        end,


        __newindex = function(_, k, v)
            print("*update of element " .. tostring(k) .. " to " .. tostring(v))
            t[k] = v -- 更新原来的表
        end,


        __pairs = function()
            return function (_, k)
                local nextkey, nextvalue = next(t, k)
                if nextkey ~= nil then
                    print("*traversing element " .. tostring(nextkey))
                end
            return nextkey, nextvalue
            end
        end,

        __len = function() return #t end
    }

    setmetatable(proxy, mt)

    return proxy
end

t = {}
t = track(t)
t[2] = "hello"
print(t[2])
t = track({10, 20})
print(#t)
for k, v in pairs(t) do print(k, v) end
 ]]


-- 2.4.5只读的表 =============================================================
-- function readOnly(t)
--     local proxy = {}
--     local mt = {
--         __index = t, 
--         __newindex = function(t, k, v)
--             error("attempt to update a read-only table", 2)
--         end
--     }
--     setmetatable(proxy, mt)
--     return proxy
-- end

-- days = readOnly{"Sunday", "Monday", "Tuesday", "Wednesday", "Thusday", "Friday", "Saturday"}
-- print(days[1])
-- days[2] = "Noday"

local mt = {}
mt.x = 1
mt.__index = mt
local t = {}
t.__index = t
setmetatable(t, mt)
print(t.x)