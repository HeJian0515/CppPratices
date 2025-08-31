--region 字符串长度

--[[ local str = "Hello, World!"
print(#str)  -- 输出: 13 ]]

--[[local s1 = "你好"
print(utf8.len(s1))  -- 输出: 2
print(#s1)  -- 输出: 6 (每个汉字占3个字节)
print(string.len(s1))  -- 输出: 6]]

--endregion

-- 大小写转换
--[[ local str = "My Name Is Lua"
local upperStr = string.upper(str)
local lowerStr = string.lower(str)
print(upperStr)  -- 输出: MY NAME IS LUA
print(lowerStr)  -- 输出: my name is lua ]]

-- 字符串替换
--[[ local str = "Hello, World!"
local replacedStr = string.gsub(str, "World", "Lua")
print(replacedStr)  -- 输出: Hello, Lua! ]]

-- 字符串查找
--[[ local str = "Hello, World!"
local startPos, endPos = string.find(str, "World")
print(startPos, endPos)  -- 输出: 8 12
 ]]

-- 字符串反转
--[[ local str = "Lua Programming"
local reversedStr = string.reverse(str)
print(reversedStr)  -- 输出: gnimmargorP auL ]]



--region 字符串拼接

-- 1.使用 .. 操作符来进行字符串连接
--[[ local str1 = "Hello"
local str2 = "World"
local result = str1 .. " " .. str2
print(result)  -- 输出: Hello World

print(3 .. 4)  -- 输出: 34 ]]

-- 2. 使用table.concat来连接字符串
--[[ local tb = {"Hello", "World", "Lua", "Programming"}
local result = table.concat(tb, " ")
print(result)  -- 输出: Hello World Lua Programming ]]

-- 3. 使用string.format来格式化字符串
--[[ local name = "Alice"
local age = 30
local formattedString = string.format("My name is %s and I am %d years old.", name, age)
print(formattedString)  -- 输出: My name is Alice and I am 30 years old. ]]

-- 4. string.rep对某一个字符串做N次拼接。
--[[ local str = "Lua"
local repeatedStr = string.rep(str, 3)
print(repeatedStr)  -- 输出: LuaLuaLua ]]

--endregion


--region 字符转换

-- 将整型数字转成字符
--[[ local s1 = string.char(97) -- 'a' 的 ASCII 码是 97
print(s1)  -- 输出: a
s1 = string.char(97, 98, 99) -- 'abc'
print(s1)  -- 输出: abc ]]

-- 2
--[[ local s1 = string.byte("ABCD") -- 获取字符串的第一个字符的 ASCII 码
print(s1)  -- 输出: 65
s1 = string.byte("ABCD", 2) -- 获取字符串的第二个字符的 ASCII 码
print(s1)  -- 输出: 66 ]]

--endregion


--region nil和字符串拼接

--[[ local s1 = nil
local s2 = "非空字符串"
-- print(s1 .. s2) --异常
print(string.format("%s@%s", s1, s2)) -- nil@非空字符串 ]]

--endregion
