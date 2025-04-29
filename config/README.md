# Database Configuration

Sau khi hoàn thành phần setup project, mọi người tạo 1 file `database.conf` giống như file `database-sample.conf`.
Các thông tin cần mọi người nhớ lưu lại lúc setup MySQL tránh quên mật khẩu mất thời gian lấy lại.

Thông thường project thật sẽ setup config như này, mọi người chịu khó tìm hiểu, làm quen cách này sau đi làm sẽ dễ hơn nhiều.

Trong đó:

```
DB_HOST=localhost giá trị default khi chạy MySQL trên máy
DB_PORT=33060 trên MacOS default là 33060, nếu ai dùng window thì kiểm tra lại nhé
DB_USER=root default user khi cài đặt MySQL
DB_PASSWORD=012345678 Mật khẩu của tài khoản dùng cho MySQL, mọi người nhớ lưu lại, tránh quên thì mất thời gian lấy lại mật khẩu mới
DB_NAME=user_management copy phần này hoặc nếu mọi người có tạo trước DB tên khác thì sửa lại
```