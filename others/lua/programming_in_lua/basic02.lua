--region select

-- --1. 计算传递进来的参数个数
-- print(select('#', 'a', 'b', 'c')) -- 3
-- local a = {1, 2, 3, 4}

-- -- 输出结果为1，这里会将数组a看作为一个参数进行计算，因此输出1
-- print(select("#", a)) -- 1

-- local function cal_sum(...)
--     return select('#', ...) -- 返回传递进来的参数个数
-- end
-- print(cal_sum(1, 2, 3, 4, 5)) -- 5


--2. 输出第n个及其后面的所有参数
-- local function cal_sum(...)
--     print(select(3, ...)) -- 输出第2个及其后面的所有参数
-- end
-- cal_sum(1, 2, 3, 4, 5) -- 3 4 5

-- local function cal_sum2(...)
--     a, b, c, d = select(3,...) -- 输出第3个及其后面的所有参数
--     print(a, b, c, d)
-- end

-- cal_sum2(1, 2, 3, 4, 5) -- 3 4 5 nil

--endregion

