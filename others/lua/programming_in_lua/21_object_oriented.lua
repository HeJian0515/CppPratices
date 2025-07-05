Account = {
    balance = 0,
}

function Account:deposit(v)
    self.balance = self.balance + v
end

function Account:withdraw(v)
    if v > self.balance then error"insufficient fundss" end
    self.balance = self.balance - v
end

-- Account.deposit(Account, 200.00)
-- Account:withdraw(100.00)

function Account:new(o)
    o = o or {} -- 如果用户没有提供则创建一个新的表
    self.__index = self
    setmetatable(o, self)
    return o
end

-- b = Account:new()
-- print(b.balance) --> 0

SpecialAccount = Account:new()
s = SpecialAccount:new{limt = 1000.00}

function SpecialAccount:withdraw(v)
    if v - self.balabce >= self:getLimit() then
        error"insufficient funds"
    end
    self.balabce = self.balabce - v
end

function SpecialAccount:getLimit()
    return self.limit or 0
end

s = SpecialAccount:new{limit = 1000.00}
-- s:withdraw(200.00)

function s:getLimit()
    return self.blance * 0.10
end

-- 21.3多重继承 =========================================================================
local function search(k, plist)
    for i = 1, #plist do
        local v = plist[i][k]
        if v then return v end
    end
end

function createClass(...)
    local c = {}
    local parents = {...}

    setmetatable(c, {  __index = function(t, k)
        return search(k, parents)
    end})

    c.__index = c

    function c:new(o)
        o = o or {}
        setmetatable(o, c)
        return o
    end

    return c
end

Named = {}

function Named:getname()
    return self.name
end

function Named:setname(n)
    self.name = n
end

NamedAccount = createClass(Account, Named)
account= NamedAccount:new{name = "Paul"}
print(account:getname()) --> Paul


-- 21.4 私有性 =================================================================
-- 通过两个表实现：一个表来保存对象的状态， 另一个表用于保存对象的操作(或接口)
function newAccount(initialBalance)
    local self = {balance = initialBalance}

    local wirhdraw = function(v)
        self.balance = self.balance - v
    end

    local deposit = function(v)
        self.balance = self.balance + v
    end

    local getBalance = function () return self.balance end

    return {
        wirhdraw = wirhdraw,
        deposit = deposit,
        getBalance = getBalance
    }
end


-- 21.5单方法对象 ==================================================================
function newObject(value)
    return function (action, v)
        if action == "get" then return value
        elseif action == "set" then value = v
        else error("invalid action")
        end
    end
end

d = newObject(0)
print(d("get")) --> 0
d("set", 10) 
print(d("get")) --> 10

-- 21.6 对偶表示实现私有性 ===============================================================

local balance = {}

Account = {}

function Account:withdraw(v)
    balance[self] = balance[self] - v
end

function Account:deposit(v)
    balance[self] = balance[self] + v
end

function Account:balance()
    return balance[self]
end

function Account:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    balance[o] = 0
    return o
end

a = Account:new{}
a:deposit(100.00)
print(a:balance())