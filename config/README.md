# Database Configuration

Sau khi hoàn thành phần setup project, mọi người tạo 1 file `database.conf` giống như file `database-example.conf`.

Trong đó:

```
DB_HOST=localhost giá trị default khi chạy MySQL trên máy
DB_PORT=33060 trên MacOS default là 33060, nếu ai dùng window thì kiểm tra lại nhé
DB_USER=root default user khi cài đặt MySQL
DB_PASSWORD=012345678 Mật khẩu của tài khoản dùng cho MySQL, mọi người nhớ lưu lại, tránh quên thì mất thời gian lấy lại mật khẩu mới
DB_SCHEMA=account_management copy phần này vào là được
```