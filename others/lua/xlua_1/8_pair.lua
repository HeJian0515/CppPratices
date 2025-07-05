
a = {[0] = 1, 2, [-1] = 3, 4, 5}
-- ipairs
for i,k in ipairs(a) do
    print("ipairs遍历键值" .. i .. "_" .. k)
end
-- 从1开始遍历 小于等于0的值得不到
-- 只能找到连续索引的键，如果中间断序了，它也无法遍历出后面的内容
-- ipairs遍历键值1_2
-- ipairs遍历键值2_4
-- ipairs遍历键值3_5

print("******************pairs迭代器遍历*************")
for i, v in pairs(a) do
    print("pairs遍历键值" .. i .. "_" .. v)
end

for i in pairs(a) do
    print("pairs遍历键" .. i)
end