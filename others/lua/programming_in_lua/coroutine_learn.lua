-- resume-yield交换数据
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


---------------------------------------------------
-- 当一个协程调用函数yield时，它不是进入了一个新函数
-- 而是返回一个挂起的调用（调用的是函数resume）
-- 同样地，对函数resume的调用也不是启动一个新函数，
-- 而是返回一个对应函数yield的调用

function send(x)
    coroutine.yield(x)
end

function producer()
    while true do
        local x = io.read() -- 产生新值
        send(x) -- 发送给消费者
    end
end

function receive()
    local status, value = coroutine.resume(producer)
    return value
end

function consumer()
    while true do
        local x = receive() -- 接收新值
        io.write(x, "\n") -- 消费
    end
end

producer = coroutine.create(producer)
