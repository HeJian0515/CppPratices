print("****************元表概念*****************")
-- 任何表变量都可以作为另一个表变量的元表
-- 任何表变量都可以有自己的元表
-- 当子表进行一些特定操作时
-- 会执行元表中的内容

myTable = {}
myTable.name = 1

meta = {
    __tostring = function(t)
        return t.name
    end,

    __call = function(self, b)
        print('-------')
    end,


}
setmetatable(myTable, meta)

-- __index 当子表中 找不到某一个属性时
-- 回到元表中 __index指定的表中去找属性

-- newIndex 当赋值时，如果赋值一个不存在的索引
-- 那么就会把这个值赋值到newIndex所指的表中 不会修改自己

-- 





