function foo()
    print("foo start")
    local value = coroutine.yield("foo pause")
    print("foo resume value: " .. tostring(value))
    print("foo end")
end

-- 创建协同程序
local co = coroutine.create(foo)

-- 启动协同程序
local status, result = coroutine.resume(co)
print("1:", result) -- 输出：暂停foo的执行

-- 恢复协同程序的执行，并传入一个值
status, result = coroutine.resume(co, 42)
print("2", result)


---------------------------------------------------
co = coroutine.create(
    function (i)
        print(i);
    end
)
coroutine.resume(co, 1) -- 1
print(coroutine.status(co)) -- dead


co = coroutine.wrap(
    function ()
        print(i);
    end
)

co(1)


co2 = coroutine.create(
    function ()
        for i = 1, 10, 1 do
            print(i)
            if i == 3 then
                print(coroutine.status(co2)) -- running
                print(coroutine.running()) -- thread:XXXXX
            end
            coroutine.yield()
        end
    end
)

coroutine.resume(co2) -- 1
coroutine.resume(co2) -- 2
coroutine.resume(co2) -- 3

print(coroutine.status(co2)) -- suspended
print(coroutine.running())

---------------------------------------------------
local newProductor

function productor()
    local i = 0
    while true do
        i = i + 1
        send(i)   -- 将生产的物品发给消费者
    end
end

function consumer()
    while true do
        local i = receive()  -- 从生产者那里拿到物品
        print(i)
    end
end

function receive()
    local status, value = coroutine.resume(newProductor)
    return value
end


function send(x)
    coroutine.yield(x)  -- x表示需要发送的值，值返回以后，就挂起该协同程序
end

--[[ newProductor = coroutine.create(productor)
consumer() ]]

