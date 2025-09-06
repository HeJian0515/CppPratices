--region os.time

-- 时间表转时间戳
--[[ local t = {
    year = 2025,
    month = 9,
    day = 6,
    hour = 12,
    min = 42,
    sec = 30,
    isdst = false, -- 是否为夏令时
}
local timestamp = os.time(t)
print("timestamp:", timestamp) -- 输出时间戳 ]]

--endregion 

--region os.date

--时间戳转时间表
-- 返回当前时间
--[[ local d = os.date("*t") -- 返回一个包含日期和时间的表
print("{year=" .. d.year .. ", month=" .. d.month .. ", day=" .. d.day .. ", hour=" .. d.hour .. ", min=" .. d.min .. ", sec=" .. d.sec .. "}")

d1 = os.date("*t", 906000490)
print("{year=" .. d1.year .. ", month=" .. d1.month .. ", day=" .. d1.day .. ", hour=" .. d1.hour .. ", min=" .. d1.min .. ", sec=" .. d1.sec .. "}")
 ]]

-- 格式化时间字符串
--[[  print(os.date("a %A in %B")) -- a Saturday in September
 print(os.date("%d/%m/%Y")) -- 06/09/2025
 ]]
--endregion

 --os.time和os.date综合使用
--[[ local t = os.date("*t")
  print("当前时间:", os.date("%Y-%m-%d %H:%M:%S", os.time(t)))
 t.day = t.day + 10
 print("10天后时间:", os.date("%Y-%m-%d %H:%M:%S", os.time(t)))
  ]]

-- os.difftime
--[[ local t5_3 = os.time({year = 2015, month = 1, day = 12})
local t5_2 = os.time({year = 2011, month = 12, day = 16})
local d = os.difftime(t5_3, t5_2)
print("d:", d, d // (24 * 3600)) -- 计算两个时间点之间的天数差 ]]

--os.clock
local start = os.clock()
local sum = 0.0
for i = 1, 1e8 do
    sum = math.sqrt(i) + sum
end
local finish = os.clock()
print("sum:", sum, "time:", finish - start) -- 计算代码执行时间 秒

local start = os.clock()
local sum = 0.0
local sqrt = math.sqrt -- 局部化math.sqrt函数
for i = 1, 1e8 do
    sum = sqrt(i) + sum
end
local finish = os.clock()
print("sum:", sum, "time:", finish - start) -- 计算代码执行时间 秒