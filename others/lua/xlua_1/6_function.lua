print("**********************函数***************")
-- function 函数名()
-- end

-- a = function()
-- end

print("**********************无参数无返回值***************")

-- F1() -- 会报错
function F1()
    print("F1函数")
end
F1()

F2 = function()
    print("F2函数")
end
F2()

print("**********************有参数***************")
function F3(a)
    print(a)
end
F3(1)
F3("123")
F3(true)
-- 形参和实参个数不匹配，不会报错，只会补空 或者丢弃
F3()
F3(1, 2, 3)

print("**********************有返回值***************")
function F4(a)
    return a, "123", true
end
temp = F4()
print(temp)

print("**********************函数的类型***************")
F5 = function()
    print("123")
end
print(type)

print("**********************函数的重载***************")

-- 不支持重载
-- 默认调用最后一个声明的函数

print("**********************变长参数***************")

function F7(...)
    -- 用一个表存起来再用
    local arg = {...}
    for i=1, #arg do
        print(arg[i])
    end
end

F7(1,"123", true, 4, 5, 6)

print("**********************函数嵌套***************")
-- 闭包
function F8()
    return function()
        print(123)
    end
end

f9 = F8()
f9()