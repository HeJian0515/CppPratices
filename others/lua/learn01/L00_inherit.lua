--region 定义类1

-- 定义父类
local Parent = {}

-- 为父类添加方法
function Parent:new(x)
    local instance = {x = x}
    setmetatable(instance, self)
    self.__index = self
    return instance
end

function Parent:printX()
    print(self.x)
end

-- 创建子类
local Child = {}

-- 子类可以添加自己的方法
function Child:new(x, y)
    setmetatable(self, Parent)  -- 确保子类继承父类
    self.__index = self
    local instance = Parent:new(x)
    instance.y = y
    setmetatable(instance, self)
    return instance
end

function Child:printY()
    print(self.y)
end

-- 使用示例
local obj = Child:new(10, 20)
obj:printX()  -- 输出：10
obj:printY()  -- 输出：20

--endregion


--region 定义类2

Account = class(function(acc, balance) 
    acc.balance = balance
end)

function Account:withdraw(amount)
    self.balance = self.balance - amount
end


--endregion