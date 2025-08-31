--region error

-- error(message, level) 用于在程序中手动抛出错误
-- level 用于指定错误的级别，默认为 1，即为调用error函数的位置；2即为调用error函数的函数的位置；0则不打印出错位置信息！
--[[error("Error message", 1)
print("This line will not be executed!")]]

--endregion


--region assert

-- assert是error的包装，将判断之类的操作包装了进去！
-- assert(condition, message) 用于在条件为 false 时抛出错误
-- 第一个参数为nil或判断的结果为false的时候抛出错误，中止运行，调用error函数；否则继续执行！
--第二个参数为可选的错误提示信息，如果提供这个参数，调用error函数的时候则打印出message；否则使用默认的"assertion failed!"。
--[[local a = 1
local b = 2
assert(a == b, "a 不等于 b")]]

--endregion


--region pcall

-- pcall(func, ...) 用于调用函数，并捕获错误
-- 第一个参数为要调用的函数，后面可以跟任意数量的参数
-- 如果调用成功，则返回true和函数的返回值；如果调用失败，则返回false和错误信息。
-- 注意：如果函数调用成功，则不会抛出错误，而是返回true和函数的返回值。
-- 注意：如果函数调用失败，则会抛出错误，并返回false和错误信息。
-- 注意：如果函数调用失败，则不会继续执行后续代码，而是直接返回错误信息。

--[[local function testFunc(a, b)
    print(a, b)
    error("pcall error")
    return a .. b
end

local ok, result = pcall(testFunc, 1, 2)
if ok then
    print("pcall success:", result)
else
    print("pcall failed:", result)
end]]

--endregion


--region xpcall

-- xpcall(func, errfunc, ...) 用于调用函数，并捕获错误
-- 第一个参数为要调用的函数，第二个参数为错误处理函数，后面可以跟任意数量的参数
-- 如果调用成功，则返回true和函数的返回值；如果调用失败，则调用errfunc函数，并将错误信息作为参数传入；如果errfunc也失败，则返回false和错误信息。
-- 注意：如果函数调用成功，则不会抛出错误，而是返回true和函数的返回值。
-- 注意：如果函数调用失败，则会调用errfunc函数，并将错误信息作为参数传入。
-- 注意：如果函数调用失败，则不会继续执行后续代码，而是直接返回错误信息。

--[[local function testXPCallFunc()
    error("xpcall error")
    return "xpcall success"
end

local function dealError(msg)
    print("dealError:", msg)
    error("dealError failed")
    --return "dealError success"
end

local ok, result = xpcall(testXPCallFunc, dealError)
if ok then
    print("xpcall success: ", result)
else
    print("xpcall failed: ", result)
end]]


--endregion


--region debug.traceback

-- debug.traceback(message, level) 用于生成一个错误堆栈信息
-- message 为可选参数，用于指定错误信息；level 为可选参数，用于指定堆栈信息的层级，默认为 1，即当前函数的调用栈信息。
-- 返回值是一个字符串，包含了错误堆栈信息。

-- 注意：debug.traceback() 函数只能在调试模式下才能使用，即在调用 require("debug") 之后才能使用。
--require("debug")
--[[local function testTraceback()
    print(debug.traceback("testTraceback error", 1))
    --error("testTraceback error")
end

testTraceback()]]

--[[
local function testXpcallTraceback()
    error("testXpcallTraceback error")
end

local ok, result = xpcall(testXpcallTraceback, debug.traceback)
if ok then
    print("xpcall success: ", result)
else
    print("testXpcallTraceback call failed: ", result)
end
]]


--endregion