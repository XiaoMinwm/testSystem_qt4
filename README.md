# 基于 Qt4 的考试系统

一个使用 Qt4 + MySQL 开发的简易考试管理系统，支持管理员、教师、学生三种角色。

---

## 功能概述

| 角色 | 功能 |
|------|------|
| 管理员 | 添加/删除教师账号、添加/删除学生账号 |
| 教师 | 上传题目、删除题目、查询学生成绩、修改密码 |
| 学生 | 查看个人信息与成绩、参加考试、修改密码 |

---

## 环境依赖

- Qt 4.x
- MySQL 5.x（或兼容版本）
- Qt MySQL 驱动（`libqt4-sql-mysql` 或等价包）

---

## 快速开始

### 1. 初始化数据库

```sql
-- 以 MySQL root 账户执行
source test.sql;
```

### 2. 配置数据库连接

将 `db.conf.example` 复制为 `db.conf`，并填写实际的数据库连接信息：

```bash
cp db.conf.example db.conf
```

编辑 `db.conf`：

```ini
[database]
host=localhost
user=your_db_user
password=your_db_password
dbname=mydb
```

> **重要**：`db.conf` 已加入 `.gitignore`，请勿将真实凭据提交到版本库。

### 3. 编译运行

```bash
qmake testSystem_Qt4.pro
make
./testSystem_Qt4
```

---

## 安全说明

- **数据库凭据**：连接信息从 `db.conf` 读取，不再硬编码在源码中。
- **SQL 注入防护**：所有数据库查询均使用参数化预处理语句（`QSqlQuery::prepare` + `addBindValue`），避免 SQL 注入攻击。
- **密码保护**：修改密码时需验证旧密码；学生信息页面不再展示明文密码。

---

## 参考资料

- 《Linux 环境下 Qt4 图形界面与 MySQL 编程》，机械工业出版社，2012
