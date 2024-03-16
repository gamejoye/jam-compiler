# jam手册
> 本项目仅仅用于学习目的

1. Class
    1. `Class <typeId> [ extends <typeId> ] { feature list; };`
    2. 支持函数重写(方法名字、参数类型、返回类型与父类一致)
    3. 不支持函数重载
    4. 不允许在子类中重复定义属性(包括从父类继承过来的属性)
    5. 内置类型:
        1. `Int { Int val_; }`
        2. `Bool { Bool val_;}`
        3. `String { String str_; }`
        4. `Object {}`
    6. 不允许自定类跟`Int` `Bool` `String` `Main`名字重复
    7. 不允许自定类继承`Int` `Bool` `String` `Main`
    8. 所有未显示继承的类都默认继承`Object`

2. Feature
    1. attr feature
        1. `let <objectId>: <typeId> [ = expression];`
    2. method feature
        1. `<objectId>(formal list): <typeId> { statement list };`

3. Formal
    1. `<objectId>: <typeId>`

4. Expression
    1. `expr + expr`
    2. `expr - expr`
    3. `expr / expr`
    4. `expr * expr`
    5. `expr == expr`
    6. `expr != expr`
    7. `expr < expr`
    8. `expr <= expr`
    9. `expr > expr`
    10. `expr >= expr`
    11. `<objectId> = expr`
    12. `!expr`
    13. `expr.<objectId>(formal list)`
    14. `new <typeId>`
    15. `(expr)`
    16. `<objectId>`
    17. `INT_CONST`
    18. `BOOL_CONST`
    19. `STRING_CONST`
    
5. Statement
    1. `return expr;`
    2. `if expr then { statement list; } [ else { statement list; } ];`
    3. `for ( expression list; expression; expression list ) in { statement list; };`
    4. `var <objectId>: <typeId> [ = expression ];`