--region 弱引用表

-- 弱引用表就是一种用来告知Lua语言一个引用不应阻止对一个对象回收的机制
-- 如果对一个对象的所有引用都是弱引用，那么垃圾收集器将会回收这个对象并删除这些弱引用

-- Lua 用语言通过弱引用表实现弱引用，弱引用表就是元素均为弱引用的表，
-- 这意味着如果一个对象只被一个弱引用表持有，那么Lua语言最终会回收这个对 。
--[[ a = {}
mt = {__mode = "k"}
setmetatable(a, mt) -- 现在a的键是弱引用的了
key = {}
a[key] = 1
key = {}
a[key] = 2
collectgarbage()
for k, v in pairs(a) do
    print(v) -- 2
end ]]
-- 一个具有弱引用键和强引用值的表是一个瞬表

--[[ a = {}
mt = {__mode = "v"} -- 现在a的值是弱引用的
setmetatable(a, mt)
val = {x = 10, y = 20}
a[1] = val
a[2] = {x = 30, y = 40}
collectgarbage()
for k, v in pairs(a) do
    if v then
        print(v.x, v.y) -- 10 20
    else
        print("nil")
    end
end ]]

--endregion


--region 析构器

-- 析构器是一个与对象关联的函数，当该对象即将被回收时该函数会被调用。
--[[ o = {x = "hi"}
setmetatable(o, {__gc = function (o)
    print(o.x)
end})
o = nil
collectgarbage() -- hi ]]

--endregion