--协程有四种状态
--suspended：挂起状态，表示协程正在等待其他协程的唤醒，刚刚创建的或遇到函数中的yield关键字时处于此状态
--running：运行状态，表示协程正在执行
--normal：正常状态，表示协程没有挂起或正在运行
--dead：死亡状态，表示协程已经执行完毕或在运行代码时发生了错误

--创建协程
--[[local co = coroutine.create(function()
     print("123")
end)
print(coroutine.status(co)) -- suspended
coroutine.resume(co)
print(coroutine.status(co)) -- dead]]

--wrap创建一个协程
-- 不过它返回的是一个函数，而不是协程。并且如果协程中出现错误，会中止协程并且将错误抛出。
--[[
local wrap = coroutine.wrap(function()
     for i = 1, 2 do
          print(i)
          coroutine.yield()
     end
end)
wrap() -- 1
wrap() -- 2
wrap() -- 什么都没打印，协程执行完毕（这是因为碰到yield后，协程的状态为挂起，而不是死亡）
wrap() --error cannot resume dead coroutine
]]


--region resume-yield交换数据

-- 第一个 resume 函数（没有对应等待它的 yield ）会把所有的额外参数传递给协程的主函数
--[[ co = coroutine.create(function (a, b, c)
    print("co", a, b, c+2)
end)
coroutine.resume(co, 1, 2, 3) -- co 1 2 5 ]]

-- 在函数coroutine.resume的返回值中，
-- 第一个值是一个布尔值，表示协程是否成功运行，
-- 之后的返回值对应协程函数中yield的返回值。
--[[ co = coroutine.create(function (a, b)
    coroutine.yield(a + b, a - b)
end)
print(coroutine.resume(co, 10, 5)) -- true 15 5 ]]

-- 与之对应的是，函数 coroutine.yield 的返回值是对应resume函数的参数。
--[[ co = coroutine.create(function (x)
    print("co1", x)
    print("co2", coroutine.yield())
end)

coroutine.resume(co, "hi") -- co1 hi
coroutine.resume(co, 4, 5) -- co2 4, 5 ]]

--endregion


--region 生产者消费者

-- 当一个协程调用函数yield时，它不是进入了一个新函数
-- 而是返回一个挂起的调用（调用的是函数resume）
-- 同样地，对函数resume的调用也不是启动一个新函数，
-- 而是返回一个对应函数yield的调用
--[[local newProductor

function productor()
     local i = 0
     while true do
          i = i + 1
          send(i)     -- 将生产的物品发送给消费者
     end
end

function consumer()
     while true do
          local i = receive()     -- 从生产者那里得到物品
          print(i)
     end
end

function receive()
     local status, value = coroutine.resume(newProductor)
     return value
end

function send(x)
    coroutine.yield(x)     -- x表示需要发送的值，值返回以后，就挂起该协同程序
end

-- 启动程序
newProductor = coroutine.create(productor)
consumer()]]

--endregion
