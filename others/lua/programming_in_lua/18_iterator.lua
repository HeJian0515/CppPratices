--region 18.1迭代器与闭包

--[[
function values(t)
    local i = 0
    return function ()
        i = i + 1
        return t[i]
    end
end

t = {10, 20, 30}
iter = values(t) -- 创建迭代器
while true do
    local element = iter() -- 调用迭代器
    if element == nil then
        break
    end
    print(element)
end

-- 泛型for
t = {10, 20, 30}
for element in values(t) do
    print(element)
end ]]

--endregion


--region 示例18.1

--[[ function allwords()
    local line = io.read() -- 当前行
    local pos = 1 -- 当前行的位置
    return function ()
        while line do -- 当还有行时循环
            local w, e = string.match(line, "(%w+)()", pos)
            if w then -- 发现一个单词
                pos = e -- 下一个位置位于该单词后
                return w -- 返回改单词
            else
                line = io.read() -- 没找到单词；尝试下一行
                pos = 1 --从第一个位置重新开始
            end
        end
    end
end

for word in allwords() do
    print(word)
end
 ]]

--endregion


--region 泛型for的语法

--[[ for var-list in exp-list do
    body
end ]]

-- for k, v in pairs(t) do print(k, v) end

--[[ for var_1, ..., var_n in explist do block end 
等价于
do
    local _f, _s, _var = explist
    while true do
        local var_1, ..., var_n = _f(_s, _var)
        _var = var_1
        if _var == nil then break end
    end
end ]]

--endregion


--region 18.3 无状态迭代器

--[[ a = {"one", "two", "three"}
for i, v in ipairs(a) do
    print(i, v)
end ]]


--[[ local function iter(t, i)
    i = i + 1
    local v = t[i]
    if v then
        return i, v
    end
end

function my_ipairs(t)
    return iter, t, 0
end

for i, v in my_ipairs(a) do
    print(i, v)
end ]]

--endregion


--region  18.4 按顺序遍历表

--[[ lines =  {
    ["luaH_set"] = 10,
    ["luaH_get"] = 24,
    ["luaH_present"] = 48,
} ]]

--[[ a = {}
for n in pairs(lines) do a[#a + 1] = n end
table.sort(a)
for _, n in ipairs(a) do print(n) end ]]

-- function pairsByKeys(t, f)
--     local a = {}
--     for n in pairs(t) do
--         a[#a + 1] = n
--     end
--     table.sort(a, f)
--     local i = 0
--     return function ()
--         i = i + 1
--         return a[i], t[a[i]]
--     end
-- end

-- for name, line in pairsByKeys(lines) do
--     print(name, line)
-- end

--endregion