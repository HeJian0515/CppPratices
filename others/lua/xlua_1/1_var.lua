print("****************变量***********************")
-- 简单变量类型
-- 使用没有初始化的变量，默认是nil
print(b) -- nil

-- 通过type函数获取函数类型
-- nil number string boolean
print("****************nil***********************")
a = nil
print(a)
print(type(a))
print(type(type(a))) --> string

-- number 所有的数值都是number
print("****************number***********************")
a = 1
print(a)
a = 1.2
print(a)
print(type(a))

-- string 
print("****************string***********************")
a = "12312"
print(a)
print(type(a))
a = '123'
print(a)
print(type(a))

-- boolean 
print("****************boolean***********************")
a = true
print(a)
print(type(a))
a = false
print(b)



-- 函数 function
-- 表 table
-- 数据结构 userdata
-- 协同程序 thread
fxx = {}
return fxx