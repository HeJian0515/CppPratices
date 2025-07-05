print("****************string***********************")
str = "双引号"
str = '单引号'

-- 获取字符串长度
print("**********************字符串长度***************")
s = "abcdEfG" -- 一个汉字占三个长度
print(#str)
print(#s)

print("**********************字符串多行打印***************")
print("123\n123")
s = [[我是
H
J
]]
print(s)

print("**********************字符串拼接***************")
print("123" .. "123")
s1 = 111
s2 = 111
print(s1 .. s2)

print(string.format("我是HJ，我今年%d岁了", 18))


print("**********************别的类型转字符串***************")
a = true
print(tostring(a))

print("**********************字符串提供的方法***************")
str = "abCdefg"
print(string.upper(str)) -- 小写转大写
print(string.lower(str))
print(string.reverse(str))
print(string.find(str, "Cde")) --> 3  5 起始结束位置
print(string.sub(str, 3)) -- Cdefg
print(string.sub(str, 3, 4)) -- Cd
print(string.rep(str, 2)) --> abCdefgabCdefg
print(string.gsub(str, "Cd", "**")) --> ab**efg 1(重复个数)

-- 字符装ASCII码
a = string.byte("Lua", 1) 
print(a) --> 76
-- ASCII码 转字符
print(string.char(a)) --> L