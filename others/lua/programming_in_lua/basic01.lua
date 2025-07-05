--! "false"代表布尔类型的false和nil
-- 逻辑运算符and，如果它的第一个操作数为"false"，则返回第一个操作数，否者返回第二个
-- or，如果第一个操作数不为"false",则返回第一个操作数，否者返回第二个
print(4 and 5) -- 5
print(nil and 13) -- nil
print(false and 13) -- false
print(0 or 5) -- 0
print(false or "hi") -- "hi"
print(nil or false) -- false

x = x or 0  -- 等价于
if not x then
    x = 0
end

--! and运算符优先级高于or

function round(x)
    local f = math.floor(x)
    if x == f then
        return f
    else
        return math.floor(x + 0.5)
    end
end

print(round(2.5)) -- 3

function unbiasedRound(x)
    local f = math.floor(x)
    if x == f or (x % 2.0 == 0.5) then
        return f -- x%2.5 == 0.5只有在x+0.5为奇数时会成立
    else
        return math.floor(x + 0.5)
    end
end

print(unbiasedRound(2.5)) -- 2
