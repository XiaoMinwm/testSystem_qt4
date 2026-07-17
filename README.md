# 基于 Qt4 的考试系统

一个使用 Qt4 + MySQL 开发的简易考试管理系统，支持管理员、教师、学生三种角色。

## 功能概述

| 角色 | 功能 |
|---|---|
| 管理员 | 添加/删除教师账号、添加/删除学生账号 |
| 教师 | 上传题目、删除题目、查询学生成绩、修改密码 |
| 学生 | 查看个人信息与成绩、参加考试、修改密码 |

## 项目结构

```text
.
├── testSystem_Qt4/          # Qt4 源码与 .pro 工程文件
├── test.sql                 # 数据库初始化脚本
├── db.conf.example          # 数据库连接配置模板
└── README.md
```

## 环境依赖

- Qt 4.x（需包含 `qmake`）
- MySQL 5.x（或兼容版本）
- Qt MySQL 驱动（如 `libqt4-sql-mysql`）

## 快速开始

### 1) 初始化数据库

在 MySQL 中执行：

```sql
source test.sql;
```

### 2) 配置数据库连接

复制模板并填写真实连接信息：

```bash
cp db.conf.example db.conf
```

`db.conf` 示例：

```ini
[database]
host=localhost
user=your_db_user
password=your_db_password
dbname=mydb
```

> `db.conf` 已加入 `.gitignore`，请勿提交真实凭据。

### 3) 编译与运行

```bash
cd testSystem_Qt4
qmake testSystem_Qt4.pro
make
./testSystem_Qt4
```

## 常见问题

- **启动提示数据库配置缺失**  
  请确认根目录存在 `db.conf`，且已填写 `database/user`、`database/password` 等字段。

- **提示 QMYSQL 驱动不可用**  
  请安装 Qt 对应版本的 MySQL 驱动包，并确保运行环境可加载该插件。

## 安全说明

- 数据库凭据通过 `db.conf` 读取，不在源码中硬编码。
- 查询操作使用预处理参数绑定，降低 SQL 注入风险。
- 密码修改流程要求验证旧密码。

## 参考资料

- 《Linux 环境下 Qt4 图形界面与 MySQL 编程》，机械工业出版社，2012
