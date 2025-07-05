print("******************while语句***************")
num = 0
while num < 5 do
    print(num)
    num = num + 1
end

print("**********************repeat until语句***************")
num = 0
repeat
    print(num)
    num = num + 1
until num > 5 --满足条件跳出 结束条件


print("**********************for语句***************")
for i = 1, 5 do -- 默认递增 i会默认+1
    print(i)
end

for i = 1, 5, 2 do -- 自定义增量
    print(i)
end

for i = 5, 1, -1 do
    print(i)
end